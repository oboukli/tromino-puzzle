// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "trmn.hpp"

#include <emscripten.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_hints.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_stdinc.h>

#include <cstddef>
#include <memory>
#include <optional>
#include <utility>
#include <vector>

#include <tromino/core/tromino.h>

#include <tromino/gfx2d/board.hpp>
#include <tromino/gfx2d/step.hpp>
#include <tromino/gfx2d/view_model.hpp>
#include <tromino/gfx2d/window.hpp>

#include "callback.hpp"

extern "C" void render_frame_callback(void* arg) noexcept;

namespace {

struct trmn_context final {
    static constexpr std::size_t const max_order{128};

    static constexpr double const dt{67.0};

    trmn_context(
        std::unique_ptr<tromino::gfx2d::Window>&& window_temp,
        std::unique_ptr<tromino::gfx2d::TrominoBoardViewModel>&& viewModel_temp
    ) noexcept :
        window{std::move(window_temp)}, viewModel{std::move(viewModel_temp)}
    {
        steps.reserve(trmn_context::max_order * trmn_context::max_order);
    }

    double frame_callback_timestamp;

    double prev_timestamp;

    double accumulator{0.0};

    std::unique_ptr<tromino::gfx2d::Window> window{};

    std::unique_ptr<tromino::gfx2d::TrominoBoardViewModel> viewModel{};

    std::vector<tromino::gfx2d::Step> steps{};
};

[[nodiscard]] std::unique_ptr<trmn_context> create_trmn_context(int const width)
{
    ::SDL_Init(SDL_INIT_VIDEO);

    ::SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

    auto window{std::make_unique<tromino::gfx2d::Window>(std::nullopt, width)};
    auto viewModel{std::make_unique<tromino::gfx2d::TrominoBoardViewModel>(
        window->GetSdlWindow()
    )};

    std::unique_ptr ctx{
        std::make_unique<trmn_context>(std::move(window), std::move(viewModel))
    };

    return ctx;
}

void start(
    trmn_context& ctx,
    tromino::gfx2d::Board const& board,
    tromino::gfx2d::Style const& style
)
{
    ::trmn_solve_puzzle(
        board.order, board.mark_x, board.mark_y, add_tromino, &ctx.steps
    );

    ctx.viewModel->SetBoard(board, style);

    auto const now{::emscripten_get_now()};
    ctx.prev_timestamp = now;
    ctx.frame_callback_timestamp = now;

    // Utilize requestAnimationFrame (HTML Standard)
    ::emscripten_set_main_loop_arg(
        render_frame_callback,
        &ctx,
        /*fps*/ 0,
        /*simulate_infinite_loop*/ false
    );
}

void stop(trmn_context& ctx) noexcept
{
    ::emscripten_cancel_main_loop();

    ::trmn_request_stop();

    ctx.steps.clear();
}

} // namespace

extern "C" void render_frame_callback(void* const arg) noexcept
{
    trmn_context& ctx{*static_cast<trmn_context*>(arg)};
    double const timestamp{ctx.frame_callback_timestamp};
    double const frame_time{timestamp - ctx.prev_timestamp};

    ctx.prev_timestamp = timestamp;
    ctx.accumulator += frame_time;
    if (ctx.accumulator >= trmn_context::dt)
    {
        ctx.accumulator -= trmn_context::dt;

        ctx.viewModel->StepForward();
        ctx.viewModel->Render(ctx.steps);
    }
    ctx.frame_callback_timestamp = ::emscripten_get_now();
}

EMSCRIPTEN_KEEPALIVE extern "C" void
playTromino(int const order, int const markX, int const markY, int const width)
{
    static constexpr tromino::gfx2d::Style const style{
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

    std::size_t const order_internal{static_cast<std::size_t>(order)};
    tromino::gfx2d::Board board{
        .size = order_internal * order_internal,
        .order = order,
        .mark_x = markX,
        .mark_y = markY
    };

    static std::unique_ptr<trmn_context> ctx{create_trmn_context(width)};

    stop(*ctx);
    start(*ctx, board, style);
}
