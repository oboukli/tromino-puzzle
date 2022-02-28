// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "tromino_gfx2d.h"

#include <cassert>

namespace tromino::gfx2d {

[[nodiscard]] ::SDL_Texture* CreateTexture(
    ::SDL_Renderer* const renderer, const int width) noexcept {
    ::SDL_Texture* const texture = ::SDL_CreateTexture(
        renderer, ::SDL_PixelFormatEnum::SDL_PIXELFORMAT_RGBA8888,
        ::SDL_TextureAccess::SDL_TEXTUREACCESS_TARGET, width, width);

    assert(texture);

    return texture;
}

[[nodiscard]] ::SDL_Texture* CreateTrominoTexture(
    ::SDL_Renderer* const renderer, const int squareWidth,
    const ::SDL_Color& color) noexcept {
    ::SDL_Texture* const texture{CreateTexture(renderer, squareWidth * 2)};

    ::SDL_SetTextureBlendMode(texture, ::SDL_BlendMode::SDL_BLENDMODE_BLEND);

    ::SDL_SetRenderTarget(renderer, texture);

    ::SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
    ::SDL_RenderClear(renderer);

    ::SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    ::SDL_Rect rect{squareWidth, 0, squareWidth, squareWidth};
    ::SDL_RenderFillRect(renderer, &rect);

    rect.x = 0;
    rect.y = squareWidth;
    rect.w = squareWidth * 2;
    rect.h = squareWidth;
    ::SDL_RenderFillRect(renderer, &rect);

    return texture;
}

void InitCheckeredBoard(
    ::SDL_Renderer* const renderer, ::SDL_Texture* const texture,
    const int squareWidth, const int order, const ::SDL_Color& wke1Color,
    const ::SDL_Color& bke8Color) noexcept {
    ::SDL_SetTextureBlendMode(texture, ::SDL_BlendMode::SDL_BLENDMODE_BLEND);

    ::SDL_SetRenderTarget(renderer, texture);

    ::SDL_SetRenderDrawColor(
        renderer, wke1Color.r, wke1Color.g, wke1Color.b, wke1Color.a);
    ::SDL_RenderClear(renderer);

    ::SDL_SetRenderDrawColor(
        renderer, bke8Color.r, bke8Color.g, bke8Color.b, bke8Color.a);
    ::SDL_Rect square{0, 0, squareWidth, squareWidth};

    for (int i = 0; i < order; ++i) {
        for (int j = 0; j < order; ++j) {
            if ((j & 1) != (i & 1)) {
                square.x = j * squareWidth;
                square.y = i * squareWidth;
                ::SDL_RenderFillRect(renderer, &square);
            }
        }
    }
}

void DrawMark(
    ::SDL_Renderer* const renderer, const int squareWidth, const int x,
    const int y, const ::SDL_Color& color) noexcept {
    ::SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    const ::SDL_Rect square{
        x * squareWidth, y * squareWidth, squareWidth, squareWidth};

    ::SDL_RenderFillRect(renderer, &square);
}

void InitSolutionTexture(
    ::SDL_Renderer* const renderer, ::SDL_Texture* const texture,
    const ::SDL_Color& color) noexcept {
    ::SDL_SetTextureBlendMode(texture, ::SDL_BlendMode::SDL_BLENDMODE_BLEND);

    ::SDL_SetRenderTarget(renderer, texture);

    ::SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    ::SDL_RenderClear(renderer);
}

void DrawTrominoOutline(
    ::SDL_Renderer* const renderer, ::SDL_Texture* const texture,
    const int squareWidth, const int thickness,
    const ::SDL_Color& color) noexcept {
    ::SDL_SetRenderTarget(renderer, texture);
    ::SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    ::SDL_Rect segment{squareWidth, 0, squareWidth, thickness};
    const ::SDL_Rect* pSegment{&segment};
    ::SDL_RenderFillRect(renderer, pSegment);

    segment = SDL_Rect{
        (squareWidth * 2) - thickness, thickness, thickness, squareWidth * 2};
    ::SDL_RenderFillRect(renderer, pSegment);

    segment = SDL_Rect{
        0, (squareWidth * 2) - thickness, (squareWidth * 2) - thickness,
        thickness};
    ::SDL_RenderFillRect(renderer, pSegment);

    segment = SDL_Rect{0, squareWidth, thickness, squareWidth - thickness};
    ::SDL_RenderFillRect(renderer, pSegment);

    segment = SDL_Rect{thickness, squareWidth, squareWidth, thickness};
    ::SDL_RenderFillRect(renderer, pSegment);

    segment
        = SDL_Rect{squareWidth, thickness, thickness, squareWidth - thickness};
    ::SDL_RenderFillRect(renderer, pSegment);
}

} // namespace tromino::gfx2d
