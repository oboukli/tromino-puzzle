// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "viewmodel.h"

#include <cassert>

namespace tromino::gfx2d {

TrominoBoardViewModel::TrominoBoardViewModel(
    ::SDL_Window* const window) noexcept :
    _window(window) {
    Uint32 render_flags = ::SDL_RendererFlags::SDL_RENDERER_ACCELERATED
        | ::SDL_RendererFlags::SDL_RENDERER_PRESENTVSYNC
        | ::SDL_RendererFlags::SDL_RENDERER_TARGETTEXTURE;
    _renderer.reset(::SDL_CreateRenderer(_window, -1, render_flags));
}

void TrominoBoardViewModel::SetBoard(
    const Board& board, const Style& style) noexcept {
    const int order{board.order};
    const int logicalWidth{SQUARE_LOGICAL_WIDTH * order};

    _currentStepNum = 0;
    _numSteps = ((order * order) - 1) / 3;

    ::SDL_RenderSetLogicalSize(_renderer.get(), logicalWidth, logicalWidth);
    ::SDL_RenderSetIntegerScale(_renderer.get(), ::SDL_bool::SDL_FALSE);

    ::SDL_SetRenderDrawColor(_renderer.get(), 0, 0, 0, SDL_ALPHA_TRANSPARENT);
    ::SDL_RenderClear(_renderer.get());

    _viewTexture.reset(CreateTexture(_renderer.get(), logicalWidth));

    InitCheckeredBoard(
        _renderer.get(), _viewTexture.get(), SQUARE_LOGICAL_WIDTH, order,
        style.wke1_color, style.bke8_color);

    DrawMark(
        _renderer.get(), SQUARE_LOGICAL_WIDTH, board.mark.x, board.mark.y,
        style.mark_color);

    _solutionTexture.reset(CreateTexture(_renderer.get(), logicalWidth));
    ::SDL_Color color = {0, 0, 0, SDL_ALPHA_TRANSPARENT};
    InitSolutionTexture(_renderer.get(), _solutionTexture.get(), color);

    if (_trominoTexture == nullptr) {
        _trominoTexture.reset(CreateTrominoTexture(
            _renderer.get(), SQUARE_LOGICAL_WIDTH, style.tromino_color));

        DrawTrominoOutline(
            _renderer.get(), _trominoTexture.get(), SQUARE_LOGICAL_WIDTH,
            OUTLINE_LOGICAL_WIDTH, style.tromino_outline_color);
    }
}

void TrominoBoardViewModel::StepForward() noexcept {
    assert(_currentStepNum <= _numSteps);

    if (_currentStepNum < _numSteps) {
        ++_currentStepNum;
    }
}

void TrominoBoardViewModel::Render(
    const std::vector<tromino::gfx2d::Step>& steps) const noexcept {
    ::SDL_SetRenderTarget(_renderer.get(), _solutionTexture.get());
    ::SDL_Rect trominoDest{
        0, 0, SQUARE_LOGICAL_WIDTH * 2, SQUARE_LOGICAL_WIDTH * 2};
    auto begin{steps.begin()};
    auto targetIdx{begin + _currentStepNum};
    for (auto it{begin}; it != targetIdx; ++it) {
        const Step& s{*it};
        trominoDest.x = s.p.x * SQUARE_LOGICAL_WIDTH;
        trominoDest.y = s.p.y * SQUARE_LOGICAL_WIDTH;
        ::SDL_RenderCopyEx(
            _renderer.get(), _trominoTexture.get(), nullptr, &trominoDest, 0,
            nullptr, get_flip(s.f));
    }

    ::SDL_SetRenderTarget(_renderer.get(), _viewTexture.get());
    ::SDL_RenderCopy(_renderer.get(), _solutionTexture.get(), nullptr, nullptr);

    ::SDL_SetRenderTarget(_renderer.get(), nullptr);
    ::SDL_RenderCopy(_renderer.get(), _viewTexture.get(), nullptr, nullptr);

    ::SDL_RenderPresent(_renderer.get());
}

[[nodiscard]] bool TrominoBoardViewModel::IsPlaying() const noexcept {
    return _currentStepNum != _numSteps;
}

} // namespace tromino::gfx2d
