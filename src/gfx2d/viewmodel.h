// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef VIEWMODEL_H_
#define VIEWMODEL_H_

#include <SDL2/SDL.h>

#include <memory>
#include <vector>

#include "board.h"
#include "step.h"
#include "style.h"
#include "tromino_gfx2d.h"

namespace tromino::gfx2d {

class TrominoBoardViewModel final {
public:
    explicit TrominoBoardViewModel(::SDL_Window* const window) noexcept;

    ~TrominoBoardViewModel() noexcept = default;

    void SetBoard(const Board& board, const Style& style) noexcept;

    void StepForward() noexcept;

    void Render(const std::vector<Step>& steps) const noexcept;

    [[nodiscard]] bool IsPlaying() const noexcept;

private:
    std::size_t _numSteps{0};
    std::size_t _currentStepNum{0};
    SDL_Window* const _window;
    std::unique_ptr<::SDL_Renderer, decltype(&::SDL_DestroyRenderer)> _renderer{
        nullptr, &::SDL_DestroyRenderer};
    std::unique_ptr<::SDL_Texture, decltype(&::SDL_DestroyTexture)>
        _viewTexture{nullptr, &::SDL_DestroyTexture};
    std::unique_ptr<::SDL_Texture, decltype(&::SDL_DestroyTexture)>
        _solutionTexture{nullptr, &::SDL_DestroyTexture};
    std::unique_ptr<::SDL_Texture, decltype(&::SDL_DestroyTexture)>
        _trominoTexture{nullptr, &::SDL_DestroyTexture};
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
