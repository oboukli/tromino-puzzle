// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef tromino_gfx2d_h
#define tromino_gfx2d_h

#include <SDL_render.h>

namespace tromino::gfx2d {

SDL_Texture * CreateViewTexture(SDL_Renderer * renderer, int width) noexcept;

SDL_Texture * InitCheckeredBoard(SDL_Renderer * renderer, int width, int order, const SDL_Color& wke1Color, const SDL_Color& bke8Color) noexcept;

SDL_Texture * InitSolutionLayer(SDL_Renderer * renderer, int width, const SDL_Color& color) noexcept;

SDL_Texture * InitFilledTromino(SDL_Renderer * renderer, int squareWidth, const SDL_Color& color) noexcept;

void DrawMark(SDL_Renderer * renderer, int squareWidth, int x, int y, const SDL_Color& color) noexcept;

void DrawTrominoOutline(SDL_Renderer * renderer, SDL_Texture * texture, int squareWidth, int thickness, const SDL_Color& color) noexcept;

} // namespace tromino::gfx2d

#endif /* tromino_gfx2d_h */
