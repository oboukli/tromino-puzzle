// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <emscripten.h>

#include <cstddef>
#include <memory>

#include <SDL2/SDL.h>

#include "tromino.h"

#include "board.h"
#include "models.h"
#include "tromino_gfx2d.h"
#include "viewmodel.h"
#include "window.h"

static std::unique_ptr<tromino::gfx2d::Window> window = nullptr;
static std::unique_ptr<tromino::gfx2d::TrominoBoardViewModel> viewModel
    = nullptr;
static std::unique_ptr<tromino::gfx2d::SolutionState> solutionState = nullptr;
static bool isMainLoopRunning = true;
static bool isInitialized = false;

static void addTromino(
    const trmn_position_t pos, const trmn_flip_t flip,
    void* const state) noexcept {
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

static void init(const int width) noexcept {
    solutionState = std::make_unique<tromino::gfx2d::SolutionState>();
    solutionState->steps
        = std::make_unique<std::vector<tromino::gfx2d::Step>>();

    ::SDL_Init(SDL_INIT_VIDEO);

    ::SDL_SetHint(SDL_HINT_RENDER_LOGICAL_SIZE_MODE, "overscan");
    ::SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
    ::SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

    window = std::make_unique<tromino::gfx2d::Window>(nullptr, width);
    viewModel = std::make_unique<tromino::gfx2d::TrominoBoardViewModel>(
        window->GetSdlWindow());

    isMainLoopRunning = true;
    isInitialized = true;
}

static void terminate() noexcept {
    ::emscripten_cancel_main_loop();

    viewModel.reset();
    window.reset();

    ::SDL_Quit();

    solutionState.reset();

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

static void start(
    const tromino::gfx2d::board_t& board, const int width) noexcept {
    using namespace tromino::gfx2d;
    constexpr int SWAP_INTERVAL = 4;

    if (isInitialized) {
        terminate();
    }

    init(width);

    const std::size_t numSteps = ((board.order * board.order) - 1) / 3;
    solutionState->steps->reserve(numSteps);

    ::trmn_solve_puzzle(
        board.order, board.mark, addTromino, solutionState.get());

    viewModel->SetBoard(board);

    ::emscripten_set_main_loop(loopSimulatorCallback, -1, 0);
    ::emscripten_set_main_loop_timing(EM_TIMING_RAF, SWAP_INTERVAL);
}

EMSCRIPTEN_KEEPALIVE extern "C" void playTromino(
    const int order, const int markX, const int markY,
    const int width) noexcept {
    const std::size_t size = order * order;
    tromino::gfx2d::board_t board{
        .mark = {.x = markX, .y = markY}, .size = size, .order = order};

    start(board, width);
}
