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
    const tromino::gfx2d::board_t& board) noexcept {
    const int order{board.order};
    const int logicalWidth{SQUARE_LOGICAL_WIDTH * order};

    _currentStepNum = 0;
    _numSteps = ((order * order) - 1) / 3;

    ::SDL_RenderSetLogicalSize(_renderer.get(), logicalWidth, logicalWidth);
    ::SDL_RenderSetIntegerScale(_renderer.get(), ::SDL_bool::SDL_FALSE);

    ::SDL_SetRenderDrawColor(_renderer.get(), 0, 0, 0, SDL_ALPHA_TRANSPARENT);
    ::SDL_RenderClear(_renderer.get());

    _viewTexture.reset(CreateTexture(_renderer.get(), logicalWidth));

    ::SDL_Color color{0x4e, 0x7d, 0xa6, SDL_ALPHA_OPAQUE};
    ::SDL_Color altColor{0x01, 0x23, 0x40, SDL_ALPHA_OPAQUE};
    InitCheckeredBoard(
        _renderer.get(), _viewTexture.get(), SQUARE_LOGICAL_WIDTH, order, color,
        altColor);

    color = {0x8c, 0x1b, 0x1b, SDL_ALPHA_OPAQUE};
    DrawMark(
        _renderer.get(), SQUARE_LOGICAL_WIDTH, board.mark.x, board.mark.y,
        color);

    _solutionTexture.reset(CreateTexture(_renderer.get(), logicalWidth));
    color = {0, 0, 0, SDL_ALPHA_TRANSPARENT};
    InitSolutionTexture(_renderer.get(), _solutionTexture.get(), color);

    if (_trominoTexture == nullptr) {
        color = {0xd9, 0x93, 0x3d, 0x80};
        _trominoTexture.reset(
            CreateTrominoTexture(_renderer.get(), SQUARE_LOGICAL_WIDTH, color));

        color = {0xd9, 0x36, 0x36, SDL_ALPHA_OPAQUE};
        DrawTrominoOutline(
            _renderer.get(), _trominoTexture.get(), SQUARE_LOGICAL_WIDTH,
            OUTLINE_LOGICAL_WIDTH, color);
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
