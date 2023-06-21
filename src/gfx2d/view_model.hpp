// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef GFX2D_VIEW_MODEL_HPP
#define GFX2D_VIEW_MODEL_HPP

#include <SDL2/SDL.h>

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

#include "board.hpp"
#include "step.hpp"
#include "style.hpp"
#include "tromino_gfx2d.hpp"

namespace tromino::gfx2d {

class [[nodiscard]] TrominoBoardViewModel final {
public:
    TrominoBoardViewModel() noexcept = delete;

    explicit TrominoBoardViewModel(::SDL_Window* const window) noexcept;

    ~TrominoBoardViewModel() noexcept = default;

    void SetBoard(Board const& board, Style const& style) noexcept;

    void StepForward() noexcept;

    void Render(std::vector<Step> const& steps) const noexcept;

    [[nodiscard]] bool IsPlaying() const noexcept;

private:
    using renderer_ptr
        = std::unique_ptr<::SDL_Renderer, decltype(&::SDL_DestroyRenderer)>;
    using texture_ptr
        = std::unique_ptr<::SDL_Texture, decltype(&::SDL_DestroyTexture)>;

    std::size_t _numSteps{0};
    std::size_t _currentStepNum{0};
    ::SDL_Window* const _window{};
    renderer_ptr _renderer{nullptr, &::SDL_DestroyRenderer};
    texture_ptr _viewTexture{nullptr, &::SDL_DestroyTexture};
    texture_ptr _solutionTexture{nullptr, &::SDL_DestroyTexture};
    texture_ptr _trominoTexture{nullptr, &::SDL_DestroyTexture};

    static constexpr int const OUTLINE_LOGICAL_WIDTH{1};
    static constexpr int const SQUARE_LOGICAL_WIDTH{8};
    static constexpr int const RENDERING_DRIVER_IDX{-1};
};

[[nodiscard]] inline ::SDL_RendererFlip
get_flip(int const flip_x, int const flip_y) noexcept {
    // clang-format off
    std::uint32_t f{flip_x == 1
        ? static_cast<std::uint32_t>(::SDL_RendererFlip::SDL_FLIP_HORIZONTAL)
        : static_cast<std::uint32_t>(::SDL_RendererFlip::SDL_FLIP_NONE)};
    // clang-format on

    if (flip_y == 1) {
        f |= static_cast<std::uint32_t>(::SDL_RendererFlip::SDL_FLIP_VERTICAL);
    }

    return static_cast<::SDL_RendererFlip>(f);
}

} // namespace tromino::gfx2d

#endif // GFX2D_VIEW_MODEL_HPP
