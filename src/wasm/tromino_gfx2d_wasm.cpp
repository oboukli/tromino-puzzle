// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "tromino.h"

#include "board.h"
#include "models.h"
#include "tromino_gfx2d.h"
#include "viewmodel.h"
#include "window.h"

#include <emscripten.h>
#include <SDL2/SDL.h>

static bool isMainLoopRunning = true;
static bool isInitialized = false;
static tromino::gfx2d::Window * window = nullptr;
static tromino::gfx2d::TrominoBoardViewModel * viewModel = nullptr;
static tromino::gfx2d::SolutionState * solutionState = nullptr;

static void addTromino(trmn_position_t pos, trmn_flip_t flip, void* state) noexcept {
    using namespace tromino::gfx2d;

    SolutionState& solutionState = *static_cast<SolutionState*>(state);

    solutionState.steps->emplace_back(pos, flip);
}

static void pollSdlEvents() noexcept {
    ::SDL_Event event;

    while (::SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                isMainLoopRunning = false;
                break;

            default:
                break;
        }
    }
}

static void init(int width) noexcept {
    solutionState = new tromino::gfx2d::SolutionState();
    solutionState->steps = std::make_unique<std::vector<tromino::gfx2d::Step>>();

    ::SDL_Init(SDL_INIT_VIDEO);

    window = new tromino::gfx2d::Window(width);
    window->Init();

    viewModel = new tromino::gfx2d::TrominoBoardViewModel(width, window->GetSdlWindow());
    viewModel->Init();

    isMainLoopRunning = true;
    isInitialized = true;
}

static void terminate() noexcept {
    ::emscripten_cancel_main_loop();

    viewModel->Dispose();
    delete viewModel;
    viewModel = nullptr;

    window->Dispose();
    delete window;
    window = nullptr;

    ::SDL_Quit();

    delete solutionState;
    solutionState = nullptr;

    isInitialized = false;
    isMainLoopRunning = false;
}

static void loopSimulatorCallback() noexcept {
    pollSdlEvents();

    if (!isMainLoopRunning) {
        terminate();
    }

    viewModel->StepForward();
    viewModel->Render(*solutionState);
}

static void start(const tromino::gfx2d::board_t& board, int width) noexcept {
    using namespace tromino::gfx2d;
    constexpr int SWAP_INTERVAL = 4;

    if (isInitialized) {
        terminate();
    }

    init(width);

    const size_t numSteps = ((board.order * board.order) - 1) / 3;
    solutionState->steps->reserve(numSteps);

    ::trmn_solve_puzzle(board.order, board.mark, addTromino, solutionState);

    viewModel->SetBoard(board);

    ::emscripten_set_main_loop(loopSimulatorCallback, -1, 0);
    ::emscripten_set_main_loop_timing(EM_TIMING_RAF, SWAP_INTERVAL);
}

EMSCRIPTEN_KEEPALIVE extern "C" void playTromino(int order, int markX, int markY, int width) noexcept {
    std::size_t size = order * order;
    tromino::gfx2d::board_t board{
        .size = size,
        .order = order,
        .mark = {
            .x = markX,
            .y = markY
        }
    };

    start(board, width);
}
