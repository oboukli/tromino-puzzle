// Copyright (c) Omar Boukli-Hacene 2022. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "init.h"

#include <SDL2/SDL.h>

#include <cassert>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <thread>

#include "board.h"
#include "models.h"
#include "tromino_gfx2d.h"
#include "viewmodel.h"
#include "window.h"

#include "solver.h"

static bool isMainLoopRunning = true;

std::mutex mut;
std::condition_variable lockCond;

static void addTromino(trmn_position_t pos, trmn_flip_t flip, void* state) noexcept {
    using namespace tromino::gfx2d;

    {
        SolutionState& solutionState = *static_cast<SolutionState*>(state);

        std::lock_guard<std::mutex> lk(mut);

        solutionState.steps->emplace_back(pos, flip);
    }
    lockCond.notify_one();
}

static void pollSdlEvents() noexcept {
    ::SDL_Event event;

    while (::SDL_PollEvent(&event)) {
        switch (event.type) {
            case ::SDL_QUIT:
                isMainLoopRunning = false;
                break;

            default:
                break;
        }
    }
}

inline static void start_game_loop(const tromino::gfx2d::board_t& board, const tromino::gfx2d::SolutionState & solutionState, int width, const char * title) {
    using namespace tromino::gfx2d;
    using namespace std::chrono_literals;

    constexpr auto WAIT_TIME = 4ms;
    constexpr int FRAME_DELAY = 68;

    std::unique_ptr<tromino::gfx2d::Window> window = std::make_unique<tromino::gfx2d::Window>(title, width);
    assert(window->GetSdlWindow() != nullptr);

    std::unique_ptr<tromino::gfx2d::TrominoBoardViewModel> viewModel = std::make_unique<tromino::gfx2d::TrominoBoardViewModel>(window->GetSdlWindow());

    viewModel->SetBoard(board);

    while (isMainLoopRunning) {
        pollSdlEvents();

        if (viewModel->IsPlaying()) {
            std::unique_lock<std::mutex> lk(mut);
            if (lockCond.wait_for(
                    lk,
                    WAIT_TIME,
                    [&] { return !solutionState.steps->empty(); }
                )) {
                viewModel->StepForward();
            }

            lk.unlock();
        }

        viewModel->Render(solutionState);

        ::SDL_Delay(FRAME_DELAY);
    }
}

int init(const tromino::gfx2d::board_t& board, int width, const char * title) noexcept {
    const size_t numSteps = ((board.order * board.order) - 1) / 3;
    tromino::gfx2d::SolutionState solutionState;
    solutionState.steps = std::make_unique<std::vector<tromino::gfx2d::Step>>();
    solutionState.steps->reserve(numSteps);

    std::thread solver_thread(solver, board.order, board.mark, addTromino, &solutionState);

    if (::SDL_Init(SDL_INIT_VIDEO) != 0) {
        return 1;
    }

    ::SDL_SetHint(SDL_HINT_RENDER_LOGICAL_SIZE_MODE, "overscan");
    ::SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
    ::SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

    start_game_loop(board, solutionState, width, title);

    ::SDL_Quit();

    solver_thread.join();

    return 0;
}
