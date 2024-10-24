// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "trmn.hpp"

#include <SDL2/SDL.h>

#include <cstddef>
#include <memory>
#include <optional>
#include <vector>

#include <tromino/core/tromino.h>

#include <tromino/gfx2d/board.hpp>
#include <tromino/gfx2d/gfx2d.hpp>
#include <tromino/gfx2d/step.hpp>
#include <tromino/gfx2d/view_model.hpp>
#include <tromino/gfx2d/window.hpp>

namespace {

std::unique_ptr<tromino::gfx2d::Window> window{};
std::unique_ptr<tromino::gfx2d::TrominoBoardViewModel> viewModel{};
std::unique_ptr<std::vector<tromino::gfx2d::Step>> steps{};
bool isInitialized{false};
int solver_stop_flag{0};

void add_tromino(
    int const pos_x,
    int const pos_y,
    int const flip_x,
    int const flip_y,
    void* const state
) noexcept
{
    auto const steps_{static_cast<std::vector<tromino::gfx2d::Step>*>(state)};

    steps_->emplace_back(pos_x, pos_y, flip_x, flip_y);
}

void init(int const width) noexcept
{
    steps = std::make_unique<std::vector<tromino::gfx2d::Step>>();

    ::SDL_Init(SDL_INIT_VIDEO);

    ::SDL_SetHint(SDL_HINT_RENDER_LOGICAL_SIZE_MODE, "overscan");
    ::SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
    ::SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

    window = std::make_unique<tromino::gfx2d::Window>(std::nullopt, width);
    viewModel = std::make_unique<tromino::gfx2d::TrominoBoardViewModel>(
        window->GetSdlWindow()
    );

    isInitialized = true;
}

void terminate() noexcept
{
    solver_stop_flag = 1;

    ::emscripten_cancel_main_loop();

    viewModel.reset();
    window.reset();

    ::SDL_Quit();

    steps.reset();

    isInitialized = false;
}

void render_frame() noexcept
{
    viewModel->StepForward();
    viewModel->Render(*steps);
}

void start(tromino::gfx2d::Board const& board, int const width) noexcept
{
    static constexpr int const SWAP_INTERVAL{4};

    if (isInitialized)
    {
        terminate();
    }

    init(width);

    std::size_t const order_internal{static_cast<std::size_t>(board.order)};
    std::size_t const numSteps{
        ((order_internal * order_internal) - std::size_t{1}) / std::size_t{3}
    };
    steps->reserve(numSteps);

    solver_stop_flag = 0;

    ::trmn_solve_puzzle(
        board.order,
        board.mark_x,
        board.mark_y,
        add_tromino,
        steps.get(),
        &solver_stop_flag
    );

    tromino::gfx2d::Style const style{
        .wke1_color{
            ::Uint8{0x4e},
            ::Uint8{0x7d},
            ::Uint8{0xa6},
            ::Uint8{SDL_ALPHA_OPAQUE}
        },
        .bke8_color{
            ::Uint8{0x01},
            ::Uint8{0x23},
            ::Uint8{0x40},
            ::Uint8{SDL_ALPHA_OPAQUE}
        },
        .mark_color{
            ::Uint8{0x8c},
            ::Uint8{0x1b},
            ::Uint8{0x1b},
            ::Uint8{SDL_ALPHA_OPAQUE}
        },
        .tromino_color{
            ::Uint8{0xd9}, ::Uint8{0x93}, ::Uint8{0x3d}, ::Uint8{0x80}
        },
        .tromino_outline_color{
            ::Uint8{0xd9},
            ::Uint8{0x36},
            ::Uint8{0x36},
            ::Uint8{SDL_ALPHA_OPAQUE}
        }
    };
    viewModel->SetBoard(board, style);

    ::emscripten_set_main_loop(render_frame, -1, 0);
    ::emscripten_set_main_loop_timing(EM_TIMING_RAF, SWAP_INTERVAL);
}

} // namespace

EMSCRIPTEN_KEEPALIVE extern "C" void playTromino(
    int const order, int const markX, int const markY, int const width
) noexcept
{
    std::size_t const order_internal{static_cast<std::size_t>(order)};
    std::size_t const size{order_internal * order_internal};

    tromino::gfx2d::Board board{
        .size = size, .order = order, .mark_x = markX, .mark_y = markY
    };

    start(board, width);
}
