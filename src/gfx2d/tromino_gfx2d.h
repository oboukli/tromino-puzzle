// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef TROMINO_GFX2D_H_
#define TROMINO_GFX2D_H_

#include <SDL_render.h>

namespace tromino::gfx2d {

[[nodiscard]] ::SDL_Texture* CreateTexture(
    ::SDL_Renderer* const renderer, const int width) noexcept;

[[nodiscard]] ::SDL_Texture* CreateTrominoTexture(
    ::SDL_Renderer* const renderer, const int squareWidth,
    const ::SDL_Color& color) noexcept;

void InitCheckeredBoard(
    ::SDL_Renderer* const renderer, ::SDL_Texture* const texture,
    const int width, const int order, const ::SDL_Color& wke1Color,
    const ::SDL_Color& bke8Color) noexcept;

void InitSolutionTexture(
    ::SDL_Renderer* renderer, ::SDL_Texture* const texture,
    const ::SDL_Color& color) noexcept;

void DrawMark(
    ::SDL_Renderer* const renderer, const int squareWidth, const int x,
    const int y, const ::SDL_Color& color) noexcept;

void DrawTrominoOutline(
    ::SDL_Renderer* const renderer, ::SDL_Texture* const texture,
    const int squareWidth, const int thickness,
    const ::SDL_Color& color) noexcept;

} // namespace tromino::gfx2d

#endif // TROMINO_GFX2D_H_
