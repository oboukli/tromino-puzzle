// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <queue>

#include <SDL2/SDL.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "board.h"
#include "tromino_gfx2d.h"
#include "models.h"

#include "window.h"
#include "viewmodel.h"

#include "init.h"

static bool main_loop_running = true; // TODO:

using namespace tromino::gfx2d;

static void add_tromino(trmn_position_t abspos, trmn_flip_t flip, void* state) noexcept {
    SolutionState& solutionState = *static_cast<SolutionState*>(state);

    Step step{
        abspos,
        flip
    };

    ++solutionState.progress;
    solutionState.steps->push_back(step);
}

static void main_loop() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                main_loop_running = false;
                break;

            default:
                break;
        }
    }
}

int init(const tromino::gfx2d::board_t& board) {
    SolutionState solutionState;
    solutionState.progress = 0; // TODO: ctor
    solutionState.steps = std::make_unique<std::vector<Step>>();
    trmn_solve_puzzle(board.order, board.mark, add_tromino, &solutionState);

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return 1;
    }

    constexpr int width = 512; // TODO:
    int squareWidth = width / board.order;
    tromino::gfx2d::Window * window = new tromino::gfx2d::Window(width);
    window->Init();

    tromino::gfx2d::TrominoBoardViewModel * viewModel = new tromino::gfx2d::TrominoBoardViewModel(board, squareWidth, window->GetSdlWindow());

    viewModel->Init();

    while (main_loop_running) {
        main_loop();

        viewModel->Update(solutionState);
        viewModel->Render(solutionState);

#ifdef __EMSCRIPTEN__
        emscripten_sleep(68); // TODO:
#else
        SDL_Delay(68); // TODO:
#endif
    }

    viewModel->Dispose();
    window->Dispose();
    delete viewModel;
    delete window;

    SDL_Quit();

    return 0;
}
