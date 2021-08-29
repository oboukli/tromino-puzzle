// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef tromino_gfx2d_h
#define tromino_gfx2d_h

#include <SDL_render.h>

namespace tromino::gfx2d {

SDL_Texture * CreateBoardTextureAndSetRenderTarget(SDL_Renderer * renderer, int width);

void InitCheckeredBoard(SDL_Renderer * renderer, int width, int order);

SDL_Texture * InitFilledTromino(SDL_Renderer * renderer, int squareWidth);

void DrawMark(SDL_Renderer * renderer, int squareWidth, int x, int y);

void DrawTrominoOutline(SDL_Renderer * renderer, SDL_Texture * texture, int squareWidth, int thickness);

} // namespace tromino::gfx::2d

#endif /* tromino_gfx2d_h */
