// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "viewmodel.h"

namespace tromino::gfx2d {

TrominoBoardViewModel::TrominoBoardViewModel(int width, ::SDL_Window * window):
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
    _squareWidth(0),
    _width(width) {
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

    ::SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
    ::SDL_RenderSetLogicalSize(_renderer, _width, _width); // TODO: define logical width

    _viewTexture = CreateTexture(_renderer, _width);
    ::SDL_SetRenderTarget(_renderer, _viewTexture);

    _boardTexture = CreateTexture(_renderer, _width);

    _solutionTexture = CreateTexture(_renderer, _width);
}

void TrominoBoardViewModel::Dispose() noexcept {
    ::SDL_DestroyTexture(_trominoTexture);
    ::SDL_DestroyTexture(_solutionTexture);
    ::SDL_DestroyTexture(_boardTexture);
    ::SDL_DestroyTexture(_viewTexture);
    ::SDL_DestroyRenderer(_renderer);
    ::SDL_DestroyWindow(_window);
}

void TrominoBoardViewModel::SetBoard(const tromino::gfx2d::board_t& board) noexcept {
    _board = board;
    _squareWidth = _width / _board.order;
    int borderWidth = _squareWidth / 8;

    ::SDL_Color color, altColor;
    color = { 0x4e, 0x7d, 0xa6, SDL_ALPHA_OPAQUE };
    altColor = { 0x01, 0x23, 0x40, SDL_ALPHA_OPAQUE };
    InitCheckeredBoard(_renderer, _boardTexture, _squareWidth, _board.order, color, altColor);

    color = { 0, 0, 0, SDL_ALPHA_TRANSPARENT };
    InitSolutionTexture(_renderer, _solutionTexture, _width, color);

    color = { 0x8c, 0x1b, 0x1b, SDL_ALPHA_OPAQUE };
    DrawMark(_renderer, _squareWidth, _board.mark.x, _board.mark.y, color);

    if (_trominoTexture != nullptr) {
        ::SDL_DestroyTexture(_trominoTexture);
    }
    color = { 0xd9, 0x93, 0x3d, 0x80 };
    _trominoTexture = CreateTrominoTexture(_renderer, _squareWidth, color);

    color = { 0xd9, 0x36, 0x36, SDL_ALPHA_OPAQUE };
    DrawTrominoOutline(_renderer, _trominoTexture, _squareWidth, borderWidth, color);
}

void TrominoBoardViewModel::Update(const SolutionState& solutionState) noexcept {
    _numSteps = solutionState.steps->size();

    if (_currentStepNum < _numSteps) {
        ++_currentStepNum;
    }
}

void TrominoBoardViewModel::Render(const SolutionState& solutionState) noexcept {
    ::SDL_SetRenderTarget(_renderer, _viewTexture);

    ::SDL_Rect defaultDest { 0, 0, _width, _width };
    ::SDL_RenderCopy(_renderer, _boardTexture, nullptr, &defaultDest);

    ::SDL_SetRenderTarget(_renderer, _solutionTexture);

    ::SDL_Rect trominoDest = { 0, 0, _squareWidth * 2, _squareWidth * 2 };

    std::vector<Step>::iterator targetIdx = solutionState.steps->begin() + _currentStepNum;
    for (std::vector<Step>::iterator it = solutionState.steps->begin();  it != targetIdx; ++it) {
        Step s = *it;
        trominoDest.x = s.p.x * _squareWidth;
        trominoDest.y = s.p.y * _squareWidth;
        ::SDL_RenderCopyEx(_renderer, _trominoTexture, nullptr, &trominoDest, 0, nullptr, get_flip(s.f));
    }
    ::SDL_SetRenderTarget(_renderer, _viewTexture);
    ::SDL_RenderCopy(_renderer, _solutionTexture, nullptr, &defaultDest);

    ::SDL_SetRenderTarget(_renderer, nullptr);
    ::SDL_RenderCopy(_renderer, _viewTexture, nullptr, &defaultDest);

    ::SDL_RenderPresent(_renderer);
}

} // namespace tromino::gfx2d
