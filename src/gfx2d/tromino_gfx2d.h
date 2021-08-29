// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef tromino_gfx2d_h
#define tromino_gfx2d_h

#include <SDL_render.h>

namespace tromino::gfx2d {

SDL_Texture * CreateBoardTextureAndSetRenderTarget(SDL_Renderer * renderer, int width) noexcept;

void InitCheckeredBoard(SDL_Renderer * renderer, int width, int order) noexcept;

SDL_Texture * InitFilledTromino(SDL_Renderer * renderer, int squareWidth) noexcept;

void DrawMark(SDL_Renderer * renderer, int squareWidth, int x, int y) noexcept;

void DrawTrominoOutline(SDL_Renderer * renderer, SDL_Texture * texture, int squareWidth, int thickness) noexcept;

} // namespace tromino::gfx2d

#endif /* tromino_gfx2d_h */
