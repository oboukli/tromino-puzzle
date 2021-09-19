// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "viewmodel.h"

namespace tromino::gfx2d {

TrominoBoardViewModel::TrominoBoardViewModel(const tromino::gfx2d::board_t& board, int squareWidth, SDL_Window * window):
    _board(board),
    _window(window),
    _renderer(nullptr),
    _viewTexture(nullptr),
    _boardTexture(nullptr),
    _solutionLayerTexture(nullptr),
    _trominoTexture(nullptr),
    _squareWidth(squareWidth) {
    SolutionState solutionState;
    solutionState.progress = 0;
    solutionState.steps = std::make_unique<std::deque<Step>>();
}

TrominoBoardViewModel::~TrominoBoardViewModel() {
    Dispose();
}

void TrominoBoardViewModel::Init() noexcept {
    int order = this->_board.order; // TODO: ?
    _width = _squareWidth * order;
    int borderWidth = _squareWidth / 8;

    Uint32 render_flags =
        SDL_RENDERER_ACCELERATED
        | SDL_RENDERER_PRESENTVSYNC
        | SDL_RENDERER_TARGETTEXTURE;
    _renderer = SDL_CreateRenderer(_window, -1, render_flags);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
    SDL_RenderSetLogicalSize(_renderer, _width, _width); // TODO: define logical width

    _viewTexture = CreateViewTexture(_renderer, _width);
    SDL_SetRenderTarget(_renderer, _viewTexture);

    SDL_Color color, altColor;
    color = { 78, 125, 166, SDL_ALPHA_OPAQUE };
    altColor = { 1, 35, 64, SDL_ALPHA_OPAQUE };
    _boardTexture = InitCheckeredBoard(_renderer, _squareWidth, order, color, altColor);

    color = { 0, 0, 0, SDL_ALPHA_TRANSPARENT };
    _solutionLayerTexture = InitSolutionLayer(_renderer, _width, color);

    color = { 140, 27, 27, SDL_ALPHA_OPAQUE };
    DrawMark(_renderer, _squareWidth, _board.mark.x, _board.mark.y, color);

    color = { 217, 147, 61, 128 };
    _trominoTexture = InitFilledTromino(_renderer, _squareWidth, color);

    color = { 217, 54, 54, SDL_ALPHA_OPAQUE };
    DrawTrominoOutline(_renderer, _trominoTexture, _squareWidth, borderWidth, color);
}

void TrominoBoardViewModel::Dispose() noexcept {
    SDL_DestroyTexture(_trominoTexture);
    SDL_DestroyTexture(_solutionLayerTexture);
    SDL_DestroyTexture(_boardTexture);
    SDL_DestroyTexture(_viewTexture);
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
}

void TrominoBoardViewModel::Update(const SolutionState& solutionState) noexcept {
    _numSteps = solutionState.steps->size();

    if (_currentStepNum < _numSteps) {
        ++_currentStepNum;
    }
}

void TrominoBoardViewModel::Render(const SolutionState& solutionState) noexcept {
    SDL_SetRenderTarget(_renderer, _viewTexture);

    SDL_Rect defaultDest { 0, 0, _width, _width };
    SDL_RenderCopy(_renderer, _boardTexture, nullptr, &defaultDest);

    SDL_SetRenderTarget(_renderer, _solutionLayerTexture);

    SDL_Rect trominoDest = { 0, 0, _squareWidth * 2, _squareWidth * 2 };

    std::deque<Step>::iterator targetIdx = solutionState.steps->begin() + _currentStepNum;
    for (std::deque<Step>::iterator it = solutionState.steps->begin();  it != targetIdx; ++it) {
        Step s = *it;
        trominoDest.x = s.p.x * _squareWidth;
        trominoDest.y = s.p.y * _squareWidth;
        SDL_RenderCopyEx(_renderer, _trominoTexture, nullptr, &trominoDest, 0, nullptr, get_flip(s.f));
    }
    SDL_SetRenderTarget(_renderer, _viewTexture);
    SDL_RenderCopy(_renderer, _solutionLayerTexture, nullptr, &defaultDest);

    SDL_SetRenderTarget(_renderer, nullptr);
    SDL_RenderCopy(_renderer, _viewTexture, nullptr, &defaultDest);

    SDL_RenderPresent(_renderer);
}

} // namespace tromino::gfx2d
