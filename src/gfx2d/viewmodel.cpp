// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "viewmodel.h"

namespace tromino::gfx2d {

TrominoBoardViewModel::TrominoBoardViewModel(const tromino::gfx2d::board_t& board, int squareWidth, SDL_Window * window)
: _board(board), _squareWidth(squareWidth), _window(window), _bRender(true) {
    SolutionState solutionState;
    solutionState.progress = 0;
    solutionState.steps = std::make_unique<std::deque<Step>>();
}

TrominoBoardViewModel::~TrominoBoardViewModel() {
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

    _boardTexture = CreateBoardTextureAndSetRenderTarget(_renderer, _width);
    InitCheckeredBoard(_renderer, _squareWidth, order);
    DrawMark(_renderer, _squareWidth, _board.mark.x, _board.mark.y);
    SDL_SetRenderTarget(_renderer, nullptr);

    _tromino = InitFilledTromino(_renderer, _squareWidth);
    DrawTrominoOutline(_renderer, _tromino, _squareWidth, borderWidth);
}

void TrominoBoardViewModel::Dispose() noexcept {
    SDL_DestroyTexture(_tromino);
    SDL_DestroyTexture(_boardTexture);
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
}

void TrominoBoardViewModel::Update(const SolutionState& solutionState) noexcept {
    _numSteps = solutionState.steps->size();
    
    if (_currentStepNum < _numSteps) {
        Step currentStep = (*solutionState.steps)[_currentStepNum];

        SDL_SetRenderTarget(_renderer, _boardTexture);
        
        SDL_Rect trominoDest = { 0, 0, _squareWidth * 2, _squareWidth * 2 };

        trominoDest.x = currentStep.p.x * _squareWidth;
        trominoDest.y = currentStep.p.y * _squareWidth;
        SDL_RenderCopyEx(_renderer, _tromino, nullptr, &trominoDest, 0, nullptr, get_flip(currentStep.f));

        SDL_SetRenderTarget(_renderer, nullptr);

        ++_currentStepNum;
    }
}

void TrominoBoardViewModel::Render() noexcept {
    if (_currentStepNum <= _numSteps && _bRender) {
        SDL_Rect boardTextureDest { 0, 0, _width, _width };
        SDL_RenderCopy(_renderer, _boardTexture, nullptr, &boardTextureDest);

        SDL_RenderPresent(_renderer);

        if (_currentStepNum == _numSteps) {
            _bRender = false;
        }
    }
}

} // namespace tromino::gfx2d
