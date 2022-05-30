// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <emscripten.h>

#include <SDL2/SDL.h>

#include <memory>
#include <vector>

#include "tromino.h"

#include "board.h"
#include "step.h"
#include "tromino_gfx2d.h"
#include "view_model.h"
#include "window.h"

namespace {

std::unique_ptr<tromino::gfx2d::Window> window = nullptr;
std::unique_ptr<tromino::gfx2d::TrominoBoardViewModel> viewModel = nullptr;
std::unique_ptr<std::vector<tromino::gfx2d::Step>> steps = nullptr;
bool isInitialized = false;

void addTromino(
    const int pos_x, const int pos_y, const int flip_x, const int flip_y,
    void* const state) noexcept {
    using namespace tromino::gfx2d;

    const auto steps = static_cast<std::vector<tromino::gfx2d::Step>*>(state);

    steps->emplace_back(pos_x, pos_y, flip_x, flip_y);
}

void init(const int width) noexcept {
    steps = std::make_unique<std::vector<tromino::gfx2d::Step>>();

    ::SDL_Init(SDL_INIT_VIDEO);

    ::SDL_SetHint(SDL_HINT_RENDER_LOGICAL_SIZE_MODE, "overscan");
    ::SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
    ::SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

    window = std::make_unique<tromino::gfx2d::Window>("", width);
    viewModel = std::make_unique<tromino::gfx2d::TrominoBoardViewModel>(
        window->GetSdlWindow());

    isInitialized = true;
}

void terminate() noexcept {
    ::emscripten_cancel_main_loop();

    viewModel.reset();
    window.reset();

    ::SDL_Quit();

    steps.reset();

    isInitialized = false;
}

void loopSimulatorCallback() noexcept {
    viewModel->StepForward();
    viewModel->Render(*steps);
}

void start(const tromino::gfx2d::Board& board, const int width) noexcept {
    using namespace tromino::gfx2d;
    constexpr int SWAP_INTERVAL = 4;

    if (isInitialized) {
        terminate();
    }

    init(width);

    const std::size_t order_internal = static_cast<std::size_t>(board.order);
    const std::size_t numSteps = ((order_internal * order_internal) - 1) / 3;
    steps->reserve(numSteps);

    ::trmn_solve_puzzle(
        board.order, board.mark_x, board.mark_y, addTromino, steps.get());

    const tromino::gfx2d::Style style{
        .wke1_color{0x4e, 0x7d, 0xa6, SDL_ALPHA_OPAQUE},
        .bke8_color{0x01, 0x23, 0x40, SDL_ALPHA_OPAQUE},
        .mark_color{0x8c, 0x1b, 0x1b, SDL_ALPHA_OPAQUE},
        .tromino_color{0xd9, 0x93, 0x3d, 0x80},
        .tromino_outline_color{0xd9, 0x36, 0x36, SDL_ALPHA_OPAQUE}};
    viewModel->SetBoard(board, style);

    ::emscripten_set_main_loop(loopSimulatorCallback, -1, 0);
    ::emscripten_set_main_loop_timing(EM_TIMING_RAF, SWAP_INTERVAL);
}

EMSCRIPTEN_KEEPALIVE extern "C" void playTromino(
    const int order, const int markX, const int markY,
    const int width) noexcept {
    const std::size_t order_internal = static_cast<std::size_t>(order);
    const std::size_t size = order_internal * order_internal;

    tromino::gfx2d::Board board{
        .size = size, .order = order, .mark_x = markX, .mark_y = markY};

    start(board, width);
}

} // namespace
