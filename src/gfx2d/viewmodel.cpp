// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "viewmodel.h"

#include <cassert>

namespace tromino::gfx2d {

TrominoBoardViewModel::TrominoBoardViewModel(::SDL_Window * window):
    _board{
        .size = 0,
        .order = 0,
        .mark = {
            .x = 0,
            .y = 0
    }},
    _window(window),
    _renderer(nullptr),
    _viewTexture(nullptr),
    _boardTexture(nullptr),
    _solutionTexture(nullptr),
    _trominoTexture(nullptr),
    _numSteps(0),
    _currentStepNum(0) {
}

TrominoBoardViewModel::~TrominoBoardViewModel() {
    Dispose();
}

void TrominoBoardViewModel::Init() noexcept {
    Uint32 render_flags =
        ::SDL_RendererFlags::SDL_RENDERER_ACCELERATED
        | ::SDL_RendererFlags::SDL_RENDERER_PRESENTVSYNC
        | ::SDL_RendererFlags::SDL_RENDERER_TARGETTEXTURE;
    _renderer = ::SDL_CreateRenderer(_window, -1, render_flags);
}

void TrominoBoardViewModel::Dispose() noexcept {
    ::SDL_DestroyTexture(_trominoTexture);
    ::SDL_DestroyTexture(_solutionTexture);
    ::SDL_DestroyTexture(_boardTexture);
    ::SDL_DestroyTexture(_viewTexture);
    ::SDL_DestroyRenderer(_renderer);
    ::SDL_DestroyWindow(_window);

    _trominoTexture = nullptr;
    _solutionTexture = nullptr;
    _boardTexture = nullptr;
    _viewTexture = nullptr;
    _renderer = nullptr;
    _window = nullptr;
}

void TrominoBoardViewModel::SetBoard(const tromino::gfx2d::board_t& board) noexcept {
    const int order = board.order;
    const int logicalWidth = SQUARE_LOGICAL_WIDTH * order;

    _currentStepNum = 0;
    _board = board;
    _numSteps = ((order * order) - 1) / 3;

    ::SDL_RenderSetLogicalSize(_renderer, logicalWidth, logicalWidth);
    ::SDL_RenderSetIntegerScale(_renderer, ::SDL_bool::SDL_TRUE);

    if (_viewTexture != nullptr) {
        ::SDL_DestroyTexture(_viewTexture);
    }
    _viewTexture = CreateTexture(_renderer, logicalWidth);

    if (_boardTexture != nullptr) {
        ::SDL_DestroyTexture(_boardTexture);
    }
    _boardTexture = CreateTexture(_renderer, logicalWidth);

    ::SDL_Color color, altColor;
    color = { 0x4e, 0x7d, 0xa6, SDL_ALPHA_OPAQUE };
    altColor = { 0x01, 0x23, 0x40, SDL_ALPHA_OPAQUE };
    InitCheckeredBoard(_renderer, _boardTexture, SQUARE_LOGICAL_WIDTH, order, color, altColor);

    color = { 0x8c, 0x1b, 0x1b, SDL_ALPHA_OPAQUE };
    DrawMark(_renderer, SQUARE_LOGICAL_WIDTH, _board.mark.x, _board.mark.y, color);

    if (_solutionTexture != nullptr) {
        ::SDL_DestroyTexture(_solutionTexture);
    }
    _solutionTexture = CreateTexture(_renderer, logicalWidth);
    color = { 0, 0, 0, SDL_ALPHA_TRANSPARENT };
    InitSolutionTexture(_renderer, _solutionTexture, logicalWidth, color);

    if (_trominoTexture == nullptr) {
        color = { 0xd9, 0x93, 0x3d, 0x80 };
        _trominoTexture = CreateTrominoTexture(_renderer, SQUARE_LOGICAL_WIDTH, color);

        color = { 0xd9, 0x36, 0x36, SDL_ALPHA_OPAQUE };
        DrawTrominoOutline(_renderer, _trominoTexture, SQUARE_LOGICAL_WIDTH, OUTLINE_LOGICAL_WIDTH, color);
    }
}

void TrominoBoardViewModel::StepForward() noexcept {
    assert(_currentStepNum <= _numSteps);

    if (_currentStepNum < _numSteps) {
        ++_currentStepNum;
    }
}

void TrominoBoardViewModel::Render(const SolutionState& solutionState) const noexcept {
    ::SDL_SetRenderTarget(_renderer, _solutionTexture);
    ::SDL_Rect trominoDest = { 0, 0, SQUARE_LOGICAL_WIDTH * 2, SQUARE_LOGICAL_WIDTH * 2 };
    std::vector<Step>::iterator begin = solutionState.steps->begin();
    std::vector<Step>::iterator targetIdx = begin + _currentStepNum;
    for (std::vector<Step>::iterator it = begin;  it != targetIdx; ++it) {
        Step & s = *it;
        trominoDest.x = s.p.x * SQUARE_LOGICAL_WIDTH;
        trominoDest.y = s.p.y * SQUARE_LOGICAL_WIDTH;
        ::SDL_RenderCopyEx(_renderer, _trominoTexture, nullptr, &trominoDest, 0, nullptr, get_flip(s.f));
    }

    ::SDL_SetRenderTarget(_renderer, _viewTexture);
    ::SDL_RenderCopy(_renderer, _boardTexture, nullptr, nullptr);
    ::SDL_RenderCopy(_renderer, _solutionTexture, nullptr, nullptr);

    ::SDL_SetRenderTarget(_renderer, nullptr);
    ::SDL_RenderCopy(_renderer, _viewTexture, nullptr, nullptr);

    ::SDL_RenderPresent(_renderer);
}

[[nodiscard]] bool TrominoBoardViewModel::IsPlaying() const noexcept {
    return _currentStepNum != _numSteps;
}

} // namespace tromino::gfx2d
