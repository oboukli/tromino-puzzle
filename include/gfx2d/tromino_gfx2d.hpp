// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef GFX2D_TROMINO_GFX2D_HPP
#define GFX2D_TROMINO_GFX2D_HPP

#include <SDL2/SDL.h>

namespace tromino::gfx2d {

[[nodiscard]] ::SDL_Texture*
CreateTexture(::SDL_Renderer* const renderer, int const width) noexcept;

[[nodiscard]] ::SDL_Texture* CreateTrominoTexture(
    ::SDL_Renderer* const renderer, int const squareWidth,
    ::SDL_Color const& color) noexcept;

void InitCheckeredBoard(
    ::SDL_Renderer* const renderer, ::SDL_Texture* const texture,
    int const squareWidth, int const order, ::SDL_Color const& wke1Color,
    ::SDL_Color const& bke8Color) noexcept;

void InitSolutionTexture(
    ::SDL_Renderer* renderer, ::SDL_Texture* const texture,
    ::SDL_Color const& color) noexcept;

void DrawMark(
    ::SDL_Renderer* const renderer, int const squareWidth, int const x,
    int const y, ::SDL_Color const& color) noexcept;

void DrawTrominoOutline(
    ::SDL_Renderer* const renderer, ::SDL_Texture* const texture,
    int const squareWidth, int const thickness,
    ::SDL_Color const& color) noexcept;

} // namespace tromino::gfx2d

#endif // GFX2D_TROMINO_GFX2D_HPP
