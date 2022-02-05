// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "init.h"

#include <SDL2/SDL.h>

#include <cassert>
#include <condition_variable>
#include <cstddef>
#include <cstdlib>
#include <memory>
#include <mutex>
#include <thread>

#include "board.h"
#include "models.h"
#include "tromino_gfx2d.h"
#include "viewmodel.h"
#include "window.h"

#include "solver.h"

namespace tromino::tromino2d {

static std::mutex mut;
static std::condition_variable lockCond;

static void addTromino(
    const trmn_position_t pos, const trmn_flip_t flip,
    gfx2d::SolutionState* const solutionState) noexcept {
    using namespace tromino::gfx2d;

    {
        std::lock_guard lk(mut);
        solutionState->steps->emplace_back(pos, flip);
    }
    lockCond.notify_one();
}

static void pollSdlEvents(bool& isMainLoopRunning) noexcept {
    ::SDL_Event event;

    while (::SDL_PollEvent(&event)) {
        if (::SDL_QUIT == event.type) {
            isMainLoopRunning = false;
        }
    }
}

inline static void start_game_loop(
    const tromino::gfx2d::board_t& board,
    const tromino::gfx2d::SolutionState& solutionState, const int width,
    const char* const title) {
    using namespace tromino::gfx2d;
    using namespace std::chrono_literals;

    constexpr auto WAIT_TIME = 4ms;
    constexpr int FRAME_DELAY = 68;

    const auto window = std::make_unique<tromino::gfx2d::Window>(title, width);
    assert(window->GetSdlWindow() != nullptr);

    const auto viewModel
        = std::make_unique<tromino::gfx2d::TrominoBoardViewModel>(
            window->GetSdlWindow());

    viewModel->SetBoard(board);

    bool isMainLoopRunning = true;
    while (isMainLoopRunning) {
        pollSdlEvents(isMainLoopRunning);

        if (viewModel->IsPlaying()) {
            std::unique_lock lk(mut);
            if (lockCond.wait_for(lk, WAIT_TIME, [&solutionState] {
                    return !solutionState.steps->empty();
                })) {
                viewModel->StepForward();
            }

            lk.unlock();
        }

        viewModel->Render(solutionState);

        ::SDL_Delay(FRAME_DELAY);
    }
}

int init(
    const tromino::gfx2d::board_t& board, const int width,
    const char* const title) noexcept {
    const std::size_t numSteps = ((board.order * board.order) - 1) / 3;
    tromino::gfx2d::SolutionState solutionState;
    solutionState.steps = std::make_unique<std::vector<tromino::gfx2d::Step>>();
    solutionState.steps->reserve(numSteps);

    std::thread solver_thread(
        solver<tromino::gfx2d::SolutionState>, board.order, board.mark,
        addTromino, &solutionState);

    if (::SDL_Init(SDL_INIT_VIDEO) != 0) {
        return EXIT_FAILURE;
    }

    ::SDL_SetHint(SDL_HINT_RENDER_LOGICAL_SIZE_MODE, "overscan");
    ::SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
    ::SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

    start_game_loop(board, solutionState, width, title);

    ::SDL_Quit();

    solver_thread.join();

    return EXIT_SUCCESS;
}

} // namespace tromino::tromino2d
