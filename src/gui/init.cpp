// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "init.h"

#include <SDL2/SDL.h>

#include <cassert>
#include <chrono>
#include <condition_variable>
#include <cstddef>
#include <cstdlib>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

#include "board.h"
#include "step.h"
#include "tromino_gfx2d.h"
#include "view_model.h"
#include "window.h"

namespace tromino::tromino2d {

namespace {

extern "C" void solve_puzzle_cb(
    const int pos_x, const int pos_y, const int flip_x, const int flip_y,
    void* const state) noexcept;

template <typename T>
using add_tromino_func = void (*)(
    const int pos_x, const int pos_y, const int flip_x, const int flip_y,
    T* const state) noexcept;

template <typename T> struct SolverState final {
    T* state;
    add_tromino_func<T> callback;
};

struct SharedState {
    mutable std::mutex mut;
    std::condition_variable lock_cond;
    std::vector<tromino::gfx2d::Step> steps;
};

void poll_sdl_events(bool& is_main_loop_running) noexcept {
    ::SDL_Event event;

    while (::SDL_PollEvent(&event)) {
        if (event.type == ::SDL_EventType::SDL_QUIT) {
            is_main_loop_running = false;
        }
    }
}

inline void start_game_loop(
    const tromino::gfx2d::Board& board, SharedState& shared_state,
    const int width, const std::string& title) noexcept {
    using namespace tromino::gfx2d;
    using namespace std::chrono_literals;

    constexpr const auto WAIT_TIME{4ms};
    constexpr const int FRAME_DELAY{68};

    const auto window{std::make_unique<tromino::gfx2d::Window>(title, width)};
    assert(window->GetSdlWindow() != nullptr);

    const auto viewModel{
        std::make_unique<tromino::gfx2d::TrominoBoardViewModel>(
            window->GetSdlWindow())};

    tromino::gfx2d::Style style{
        .wke1_color{0x4e, 0x7d, 0xa6, SDL_ALPHA_OPAQUE},
        .bke8_color{0x01, 0x23, 0x40, SDL_ALPHA_OPAQUE},
        .mark_color{0x8c, 0x1b, 0x1b, SDL_ALPHA_OPAQUE},
        .tromino_color{0xd9, 0x93, 0x3d, 0x80},
        .tromino_outline_color{0xd9, 0x36, 0x36, SDL_ALPHA_OPAQUE}};

    viewModel->SetBoard(board, style);

    bool is_main_loop_running{true};
    while (is_main_loop_running) {
        poll_sdl_events(is_main_loop_running);

        if (viewModel->IsPlaying()) {
            std::unique_lock lk(shared_state.mut);
            if (shared_state.lock_cond.wait_for(lk, WAIT_TIME, [&shared_state] {
                    return !shared_state.steps.empty();
                })) {
                viewModel->StepForward();
            }

            lk.unlock();
        }

        viewModel->Render(shared_state.steps);

        ::SDL_Delay(FRAME_DELAY);

#ifdef TROMINO_2D_HEADLESS
        if (!viewModel->IsPlaying()) {
            ::SDL_Event event{::SDL_EventType::SDL_QUIT};
            ::SDL_PushEvent(&event);
        }
#endif
    }
}

void add_tromino(
    const int pos_x, const int pos_y, const int flip_x, const int flip_y,
    SharedState* const shared_state) noexcept {
    using namespace tromino::gfx2d;

    {
        std::lock_guard lk(shared_state->mut);
        shared_state->steps.emplace_back(pos_x, pos_y, flip_x, flip_y);
    }
    shared_state->lock_cond.notify_one();
}

extern "C" void solve_puzzle_cb(
    const int pos_x, const int pos_y, const int flip_x, const int flip_y,
    void* const state) noexcept {
    SolverState<SharedState>* const solver_state{
        static_cast<SolverState<SharedState>*>(state)};

    solver_state->callback(pos_x, pos_y, flip_x, flip_y, solver_state->state);
}

void solver(
    const int order, const int mark_x, const int mark_y,
    const add_tromino_func<SharedState> add_tromino_func,
    SharedState* const state) noexcept {
    SolverState<SharedState> solver_state{
        .state = state, .callback = add_tromino_func};

    ::trmn_solve_puzzle(order, mark_x, mark_y, solve_puzzle_cb, &solver_state);
}

} // namespace

int init(
    const tromino::gfx2d::Board& board, const int width,
    const std::string& title) noexcept {
    const auto board_order{static_cast<std::size_t>(board.order)};
    const std::size_t num_steps{
        ((board_order * board_order) - std::size_t{1}) / std::size_t{3}};

    SharedState shared_state;
    shared_state.steps.reserve(num_steps);

    std::thread solver_thread(
        solver, board.order, board.mark_x, board.mark_y, add_tromino,
        &shared_state);

    bool sdl2_success{false};
    if (::SDL_Init(SDL_INIT_VIDEO) == 0) {
        ::SDL_SetHint(SDL_HINT_RENDER_LOGICAL_SIZE_MODE, "overscan");
        ::SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
        ::SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

        start_game_loop(board, shared_state, width, title);

        sdl2_success = true;
    }
    ::SDL_Quit();

    solver_thread.join();

    return sdl2_success ? EXIT_SUCCESS : EXIT_FAILURE;
}

} // namespace tromino::tromino2d
