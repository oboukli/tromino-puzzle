// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
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
#include "viewmodel.h"
#include "window.h"

#include "solver.h"

namespace tromino::tromino2d {

namespace {

struct SharedState {
    std::mutex mut;
    std::condition_variable lockCond;
    std::vector<tromino::gfx2d::Step> steps;
};

void addTromino(
    const int pos_x, const int pos_y, const int flip_x, const int flip_y,
    SharedState* const sharedState) noexcept {
    using namespace tromino::gfx2d;

    {
        std::lock_guard lk(sharedState->mut);
        sharedState->steps.emplace_back(pos_x, pos_y, flip_x, flip_y);
    }
    sharedState->lockCond.notify_one();
}

void pollSdlEvents(bool& isMainLoopRunning) noexcept {
    ::SDL_Event event;

    while (::SDL_PollEvent(&event)) {
        if (::SDL_QUIT == event.type) {
            isMainLoopRunning = false;
        }
    }
}

inline void start_game_loop(
    const tromino::gfx2d::Board& board, SharedState& sharedState,
    const int width, const std::string& title) {
    using namespace tromino::gfx2d;
    using namespace std::chrono_literals;

    constexpr auto WAIT_TIME = 4ms;
    constexpr int FRAME_DELAY = 68;

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

    bool isMainLoopRunning = true;
    while (isMainLoopRunning) {
        pollSdlEvents(isMainLoopRunning);

        if (viewModel->IsPlaying()) {
            std::unique_lock lk(sharedState.mut);
            if (sharedState.lockCond.wait_for(lk, WAIT_TIME, [&sharedState] {
                    return !sharedState.steps.empty();
                })) {
                viewModel->StepForward();
            }

            lk.unlock();
        }

        viewModel->Render(sharedState.steps);

        ::SDL_Delay(FRAME_DELAY);
    }
}

} // namespace

int init(
    const tromino::gfx2d::Board& board, const int width,
    const std::string& title) noexcept {
    const auto board_order = static_cast<std::size_t>(board.order);
    const std::size_t numSteps = ((board_order * board_order) - 1) / 3;

    SharedState sharedState;
    sharedState.steps.reserve(numSteps);

    std::thread solver_thread(
        solver<SharedState>, board.order, board.mark_x, board.mark_y,
        addTromino, &sharedState);

    bool sdl2_success = false;
    if (::SDL_Init(SDL_INIT_VIDEO) == 0) {
        ::SDL_SetHint(SDL_HINT_RENDER_LOGICAL_SIZE_MODE, "overscan");
        ::SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
        ::SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

        start_game_loop(board, sharedState, width, title);

        sdl2_success = true;
    }
    ::SDL_Quit();

    solver_thread.join();

    return sdl2_success ? EXIT_SUCCESS : EXIT_FAILURE;
}

} // namespace tromino::tromino2d
