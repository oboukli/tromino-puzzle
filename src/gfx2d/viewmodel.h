// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef viewmodel_h
#define viewmodel_h

#include "board.h"
#include "models.h"
#include "tromino_gfx2d.h"

#include <SDL2/SDL.h>

namespace tromino::gfx2d {

class TrominoBoardViewModel
{
public:
    TrominoBoardViewModel(int width, ::SDL_Window * window);

    ~TrominoBoardViewModel();

    void Init() noexcept;

    void Dispose() noexcept;

    void SetBoard(const tromino::gfx2d::board_t& board) noexcept;

    void Update(const SolutionState& solutionState) noexcept;

    void Render(const SolutionState& solutionState) noexcept;

private:
    tromino::gfx2d::board_t _board;
    ::SDL_Window * _window;
    ::SDL_Renderer * _renderer;
    ::SDL_Texture * _viewTexture;
    ::SDL_Texture * _boardTexture;
    ::SDL_Texture * _solutionTexture;
    ::SDL_Texture * _trominoTexture;
    std::size_t _currentStepNum = 0;
    std::size_t _numSteps = 0;
    int _squareWidth;
    int _width;
};

[[nodiscard]] inline ::SDL_RendererFlip get_flip(const trmn_flip_t& flip) noexcept {
    int f = flip.x == 1 ? ::SDL_RendererFlip::SDL_FLIP_HORIZONTAL : ::SDL_RendererFlip::SDL_FLIP_NONE;

    if (flip.y == 1) {
        f |= ::SDL_RendererFlip::SDL_FLIP_VERTICAL;
    }

    return static_cast<::SDL_RendererFlip>(f);
}

} // namespace tromino::gfx2d

#endif // viewmodel_h
