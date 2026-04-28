// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef TROMINO_GFX2D_VIEW_MODEL_HPP_
#define TROMINO_GFX2D_VIEW_MODEL_HPP_

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

#include "board.hpp"
#include "step.hpp"
#include "style.hpp"

namespace tromino::gfx2d {

class [[nodiscard]] TrominoBoardViewModel final {
public:
    using step_container_type = std::vector<Step>;

    TrominoBoardViewModel() = delete;

    explicit TrominoBoardViewModel(::SDL_Window* window) noexcept;

    TrominoBoardViewModel(TrominoBoardViewModel const&) = delete;

    TrominoBoardViewModel(TrominoBoardViewModel&&) = delete;

    ~TrominoBoardViewModel() = default;

    TrominoBoardViewModel& operator=(TrominoBoardViewModel const&) = delete;

    TrominoBoardViewModel& operator=(TrominoBoardViewModel&&) = delete;

    void SetBoard(Board const& board, Style const& style) noexcept;

    void StepForward() noexcept;

    void Render(step_container_type const& steps) const noexcept;

    [[nodiscard]] bool IsPlaying() const noexcept;

private:
    using renderer_ptr
        = std::unique_ptr<::SDL_Renderer, decltype(&::SDL_DestroyRenderer)>;

    using texture_ptr
        = std::unique_ptr<::SDL_Texture, decltype(&::SDL_DestroyTexture)>;

    using step_num_type = step_container_type::const_iterator::difference_type;

    static constexpr int const outline_logical_width{1};

    static constexpr int const square_logical_width{8};

    static constexpr int const rendering_driver_idx{-1};

    step_num_type num_step_{0};

    step_num_type current_step_{0};

    ::SDL_Window* window_{};

    renderer_ptr renderer_{nullptr, &::SDL_DestroyRenderer};

    texture_ptr view_texture_{nullptr, &::SDL_DestroyTexture};

    texture_ptr solution_texture_{nullptr, &::SDL_DestroyTexture};

    texture_ptr tromino_texture_{nullptr, &::SDL_DestroyTexture};
};

} // namespace tromino::gfx2d

#endif // TROMINO_GFX2D_VIEW_MODEL_HPP_
