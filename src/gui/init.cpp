// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "init.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_hints.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>

#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <memory>
#include <optional>
#include <string>
#include <thread>
#include <type_traits>

#include <tromino/core/tromino.h>

#include <tromino/gfx2d/board.hpp>
#include <tromino/gfx2d/style.hpp>
#include <tromino/gfx2d/view_model.hpp>
#include <tromino/gfx2d/window.hpp>

#include "callback.hpp"
#include "solver_state.hpp"

namespace tromino::tromino2d {

namespace {

void poll_sdl_events(bool& is_main_loop_running) noexcept
{
    ::SDL_Event event{} /*[[indeterminate]]*/;
    while (::SDL_PollEvent(&event) == 1) [[unlikely]]
    {
        if (event.type == ::SDL_EventType::SDL_QUIT) [[unlikely]]
        {
            is_main_loop_running = false;
        }
    }
}

void start_game_loop(
    tromino::gfx2d::Board const& board,
    SolverState const& solver_state,
    int const width,
    std::optional<std::string const> const& title
)
{
    static constexpr int const FRAME_DELAY{68};

    auto const window{std::make_unique<tromino::gfx2d::Window>(title, width)};
    assert(window->GetSdlWindow() != nullptr);

    auto const viewModel{
        std::make_unique<tromino::gfx2d::TrominoBoardViewModel>(
            window->GetSdlWindow()
        )
    };

    tromino::gfx2d::Style const style{
        .wke1_color{
            ::Uint32{0x4e},
            ::Uint32{0x7d},
            ::Uint32{0xa6},
            ::Uint32{SDL_ALPHA_OPAQUE}
        },
        .bke8_color{
            ::Uint32{0x01},
            ::Uint32{0x23},
            ::Uint32{0x40},
            ::Uint32{SDL_ALPHA_OPAQUE}
        },
        .mark_color{
            ::Uint32{0x8c},
            ::Uint32{0x1b},
            ::Uint32{0x1b},
            ::Uint32{SDL_ALPHA_OPAQUE}
        },
        .tromino_color{
            ::Uint32{0xd9}, ::Uint32{0x93}, ::Uint32{0x3d}, ::Uint32{0x80}
        },
        .tromino_outline_color{
            ::Uint32{0xd9},
            ::Uint32{0x36},
            ::Uint32{0x36},
            ::Uint32{SDL_ALPHA_OPAQUE}
        }
    };

    viewModel->SetBoard(board, style);

    bool is_main_loop_running{true};
    while (is_main_loop_running)
    {
        poll_sdl_events(is_main_loop_running);

        if (viewModel->IsPlaying())
        {
            viewModel->StepForward();
        }

        viewModel->Render(solver_state);

        ::SDL_Delay(FRAME_DELAY);

#ifdef TROMINO_2D_HEADLESS
        if (!viewModel->IsPlaying())
        {
            ::SDL_Event event{::SDL_EventType::SDL_QUIT};
            ::SDL_PushEvent(&event);
        }
#endif
    }
}

void update_solver_state(
    int const pos_x,
    int const pos_y,
    int const flip_x,
    int const flip_y,
    SolverState* const solver_state
) noexcept
{
    solver_state->emplace_back(pos_x, pos_y, flip_x, flip_y);

    std::this_thread::yield();
}

void solver_thread_callable(
    int const order,
    int const mark_x,
    int const mark_y,
    tromino_callback_t<SolverState> const tromino_callback,
    SolverState* const state,
    int const* const stop_flag
) noexcept
{
    solver_state_wrapper_t<SolverState> solver_state_wrapper{
        .state = state, .callback = tromino_callback
    };

    static_assert(alignof(decltype(&solver_state_wrapper)) == alignof(void*));
    static_assert(std::is_standard_layout_v<decltype(solver_state_wrapper)>);

    ::trmn_solve_puzzle(
        order,
        mark_x,
        mark_y,
        &::tromino_solve_puzzle_cb,
        static_cast<void*>(&solver_state_wrapper),
        stop_flag
    );
}

} // namespace

int init(
    tromino::gfx2d::Board const& board,
    int const width,
    std::optional<std::string const> const& title
)
{
    auto const board_order{static_cast<std::size_t>(board.order)};
    std::size_t const num_steps{
        ((board_order * board_order) - std::size_t{1}) / std::size_t{3}
    };

    SolverState solver_state{};
    solver_state.reserve(num_steps);

    int solver_stop_flag{0};

    std::thread solver_thread{
        solver_thread_callable,
        board.order,
        board.mark_x,
        board.mark_y,
        &update_solver_state,
        &solver_state,
        &solver_stop_flag,
    };

    bool sdl2_success{false};
    if (::SDL_Init(SDL_INIT_VIDEO) == 0)
    {
        ::SDL_SetHint(SDL_HINT_RENDER_LOGICAL_SIZE_MODE, "overscan");
        ::SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
        ::SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

        start_game_loop(board, solver_state, width, title);

        sdl2_success = true;
    }
    solver_stop_flag = 1;
    ::SDL_Quit();
    solver_thread.join();

    return sdl2_success ? EXIT_SUCCESS : EXIT_FAILURE;
}

} // namespace tromino::tromino2d
