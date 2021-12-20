// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef TROMINO_GFX2D_H_
#define TROMINO_GFX2D_H_

#include <SDL_render.h>

namespace tromino::gfx2d {

[[nodiscard]] ::SDL_Texture * CreateTexture(::SDL_Renderer * renderer, int width) noexcept;

void InitCheckeredBoard(::SDL_Renderer * renderer, ::SDL_Texture * texture, int width, int order, const ::SDL_Color & wke1Color, const ::SDL_Color & bke8Color) noexcept;

void InitSolutionTexture(::SDL_Renderer * renderer, ::SDL_Texture * texture, int width, const ::SDL_Color & color) noexcept;

[[nodiscard]] ::SDL_Texture * CreateTrominoTexture(::SDL_Renderer * renderer, int squareWidth, const ::SDL_Color & color) noexcept;

void DrawMark(::SDL_Renderer * renderer, int squareWidth, int x, int y, const ::SDL_Color & color) noexcept;

void DrawTrominoOutline(::SDL_Renderer * renderer, ::SDL_Texture * texture, int squareWidth, int thickness, const ::SDL_Color & color) noexcept;

} // namespace tromino::gfx2d

#endif // TROMINO_GFX2D_H_
