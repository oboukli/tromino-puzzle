// Copyright (c) Omar Boukli-Hacene 2022. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef VIEWMODEL_H_
#define VIEWMODEL_H_

#include <SDL2/SDL.h>

#include "board.h"
#include "models.h"
#include "tromino_gfx2d.h"

namespace tromino::gfx2d {

class TrominoBoardViewModel final {
public:
    TrominoBoardViewModel(::SDL_Window* window) noexcept;

    ~TrominoBoardViewModel() noexcept;

    void SetBoard(const tromino::gfx2d::board_t& board) noexcept;

    void StepForward() noexcept;

    void Render(const SolutionState& solutionState) const noexcept;

    [[nodiscard]] bool IsPlaying() const noexcept;

private:
    tromino::gfx2d::board_t _board;
    std::size_t _numSteps;
    std::size_t _currentStepNum;
    SDL_Window* const _window;
    std::unique_ptr<::SDL_Renderer, decltype(&::SDL_DestroyRenderer)> _renderer;
    std::unique_ptr<::SDL_Texture, decltype(&::SDL_DestroyTexture)>
        _viewTexture;
    std::unique_ptr<::SDL_Texture, decltype(&::SDL_DestroyTexture)>
        _boardTexture;
    std::unique_ptr<::SDL_Texture, decltype(&::SDL_DestroyTexture)>
        _solutionTexture;
    std::unique_ptr<::SDL_Texture, decltype(&::SDL_DestroyTexture)>
        _trominoTexture;

private:
    static constexpr int OUTLINE_LOGICAL_WIDTH = 1;
    static constexpr int SQUARE_LOGICAL_WIDTH = 8;
};

[[nodiscard]] inline ::SDL_RendererFlip get_flip(
    const trmn_flip_t& flip) noexcept {
    // clang-format off
    int f = flip.x == 1
        ? ::SDL_RendererFlip::SDL_FLIP_HORIZONTAL
        : ::SDL_RendererFlip::SDL_FLIP_NONE;
    // clang-format on

    if (flip.y == 1) {
        f |= ::SDL_RendererFlip::SDL_FLIP_VERTICAL;
    }

    return static_cast<::SDL_RendererFlip>(f);
}

} // namespace tromino::gfx2d

#endif // VIEWMODEL_H_
