// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "view_model.hpp"

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <vector>

#include "board.hpp"
#include "gfx2d.hpp"
#include "step.hpp"
#include "style.hpp"

namespace tromino::gfx2d {

namespace {

[[nodiscard]] constexpr ::SDL_RendererFlip
get_flip(int flip_x, int flip_y) noexcept;

[[nodiscard]] constexpr ::SDL_RendererFlip
get_flip(int const flip_x, int const flip_y) noexcept
{
    // clang-format off
    std::uint32_t f{flip_x == 1
        ? static_cast<std::uint32_t>(::SDL_RendererFlip::SDL_FLIP_HORIZONTAL)
        : static_cast<std::uint32_t>(::SDL_RendererFlip::SDL_FLIP_NONE)};
    // clang-format on

    if (flip_y == 1)
    {
        f |= static_cast<std::uint32_t>(::SDL_RendererFlip::SDL_FLIP_VERTICAL);
    }

    // NOLINTNEXTLINE(clang-analyzer-optin.core.EnumCastOutOfRange)
    return static_cast<::SDL_RendererFlip>(f);
}

} // namespace

TrominoBoardViewModel::TrominoBoardViewModel(
    ::SDL_Window* const window
) noexcept :
    window_(window)
{
    static constexpr ::Uint32 const render_flags{
        static_cast<::Uint32>(::SDL_RendererFlags::SDL_RENDERER_ACCELERATED)
        | static_cast<::Uint32>(::SDL_RendererFlags::SDL_RENDERER_PRESENTVSYNC)
        | static_cast<::Uint32>(::SDL_RendererFlags::SDL_RENDERER_TARGETTEXTURE)
    };
    renderer_.reset(
        ::SDL_CreateRenderer(window_, rendering_driver_idx, render_flags)
    );
}

void
TrominoBoardViewModel::SetBoard(Board const& board, Style const& style) noexcept
{
    int const order{board.order};
    int const logicalWidth{square_logical_width * order};

    current_step_ = 0;
    num_step_ = ((order * order) - 1) / 3;

    ::SDL_RenderSetLogicalSize(renderer_.get(), logicalWidth, logicalWidth);
    ::SDL_RenderSetIntegerScale(renderer_.get(), ::SDL_bool::SDL_FALSE);

    ::SDL_SetRenderDrawColor(
        renderer_.get(),
        ::Uint8{0},
        ::Uint8{0},
        ::Uint8{0},
        ::Uint8{SDL_ALPHA_TRANSPARENT}
    );
    ::SDL_RenderClear(renderer_.get());

    view_texture_.reset(CreateTexture(renderer_.get(), logicalWidth));

    InitCheckeredBoard(
        renderer_.get(),
        view_texture_.get(),
        square_logical_width,
        order,
        style.wke1_color,
        style.bke8_color
    );

    DrawMark(
        renderer_.get(),
        square_logical_width,
        board.mark_x,
        board.mark_y,
        style.mark_color
    );

    solution_texture_.reset(CreateTexture(renderer_.get(), logicalWidth));
    ::SDL_Color const color{
        .r = ::Uint8{0},
        .g = ::Uint8{0},
        .b = ::Uint8{0},
        .a = ::Uint8{SDL_ALPHA_TRANSPARENT},
    };
    InitSolutionTexture(renderer_.get(), solution_texture_.get(), color);

    tromino_texture_.reset(CreateTrominoTexture(
        renderer_.get(), square_logical_width, style.tromino_color
    ));

    DrawTrominoOutline(
        renderer_.get(),
        tromino_texture_.get(),
        square_logical_width,
        outline_logical_width,
        style.tromino_outline_color
    );
}

void TrominoBoardViewModel::StepForward() noexcept
{
    assert(current_step_ <= num_step_);

    if (current_step_ < num_step_)
    {
        ++current_step_;
    }
}

void
TrominoBoardViewModel::Render(std::vector<Step> const& steps) const noexcept
{
    using std::cbegin;
    using std::next;

    ::SDL_SetRenderTarget(renderer_.get(), solution_texture_.get());
    ::SDL_Rect trominoDest{
        .x = 0,
        .y = 0,
        .w = square_logical_width * 2,
        .h = square_logical_width * 2,
    };

    auto const steps_cend{next(cbegin(steps), current_step_)};
    for (auto steps_iter{cbegin(steps)}; steps_iter != steps_cend; ++steps_iter)
    {
        trominoDest.x = steps_iter->px * square_logical_width;
        trominoDest.y = steps_iter->py * square_logical_width;
        ::SDL_RenderCopyEx(
            renderer_.get(),
            tromino_texture_.get(),
            nullptr,
            &trominoDest,
            0.0,
            nullptr,
            get_flip(steps_iter->fx, steps_iter->fy)
        );
    }

    ::SDL_SetRenderTarget(renderer_.get(), view_texture_.get());
    ::SDL_RenderCopy(
        renderer_.get(), solution_texture_.get(), nullptr, nullptr
    );

    ::SDL_SetRenderTarget(renderer_.get(), nullptr);
    ::SDL_RenderClear(renderer_.get());
    ::SDL_RenderCopy(renderer_.get(), view_texture_.get(), nullptr, nullptr);

    ::SDL_RenderPresent(renderer_.get());
}

[[nodiscard]] bool TrominoBoardViewModel::IsPlaying() const noexcept
{
    return current_step_ != num_step_;
}

} // namespace tromino::gfx2d
