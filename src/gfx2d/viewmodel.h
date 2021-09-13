// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef viewmodel_h
#define viewmodel_h

#include <SDL2/SDL.h>

#include "board.h"
#include "models.h"
#include "tromino_gfx2d.h"

namespace tromino::gfx2d {

class TrominoBoardViewModel
{
public:
    TrominoBoardViewModel(const tromino::gfx2d::board_t& board, int squareWidth, SDL_Window * window);
    ~TrominoBoardViewModel();

    void Init() noexcept;

    void Dispose() noexcept;

    void Update(const SolutionState& solutionState) noexcept;

    void Render() noexcept;
private:
    bool _bRender;
    const tromino::gfx2d::board_t& _board;
    SDL_Renderer * _renderer; // TODO:
    SDL_Texture * _boardTexture; // TODO:
    SDL_Texture * _tromino;
    std::size_t _currentStepNum = 0;
    std::size_t _numSteps = 0;
    int _squareWidth;
    int _width;
    SDL_Window * _window; // TODO:
};

[[nodiscard]] inline SDL_RendererFlip get_flip(const flip_t& flip) noexcept {
    int f = flip.x == 1 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    if (flip.y == 1) {
        f |= SDL_FLIP_VERTICAL;
    }

    return static_cast<SDL_RendererFlip>(f);
}

} // namespace tromino::gfx2d

#endif // viewmodel_h
