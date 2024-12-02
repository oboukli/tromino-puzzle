// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef TROMINO_GFX2D_GFX2D_HPP_
#define TROMINO_GFX2D_GFX2D_HPP_

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>

namespace tromino::gfx2d {

[[nodiscard]] ::SDL_Texture*
CreateTexture(::SDL_Renderer* renderer, int width) noexcept;

[[nodiscard]] ::SDL_Texture* CreateTrominoTexture(
    ::SDL_Renderer* renderer, int squareWidth, ::SDL_Color const& color
) noexcept;

void InitCheckeredBoard(
    ::SDL_Renderer* renderer,
    ::SDL_Texture* texture,
    int squareWidth,
    int order,
    ::SDL_Color const& wke1Color,
    ::SDL_Color const& bke8Color
) noexcept;

void InitSolutionTexture(
    ::SDL_Renderer* renderer, ::SDL_Texture* texture, ::SDL_Color const& color
) noexcept;

void DrawMark(
    ::SDL_Renderer* renderer,
    int squareWidth,
    int x,
    int y,
    ::SDL_Color const& color
) noexcept;

void DrawTrominoOutline(
    ::SDL_Renderer* renderer,
    ::SDL_Texture* texture,
    int squareWidth,
    int thickness,
    ::SDL_Color const& color
) noexcept;

} // namespace tromino::gfx2d

#endif // TROMINO_GFX2D_GFX2D_HPP_
