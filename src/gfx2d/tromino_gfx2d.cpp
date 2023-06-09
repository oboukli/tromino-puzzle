// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "tromino_gfx2d.hpp"

#include <cassert>

namespace tromino::gfx2d {

[[nodiscard]] ::SDL_Texture*
CreateTexture(::SDL_Renderer* const renderer, int const width) noexcept {
    ::SDL_Texture* const texture{::SDL_CreateTexture(
        renderer, ::SDL_PixelFormatEnum::SDL_PIXELFORMAT_RGBA8888,
        ::SDL_TextureAccess::SDL_TEXTUREACCESS_TARGET, width, width)};

    assert(texture);

    return texture;
}

[[nodiscard]] ::SDL_Texture* CreateTrominoTexture(
    ::SDL_Renderer* const renderer, int const squareWidth,
    ::SDL_Color const& color) noexcept {
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
    int const squareWidth, int const order, ::SDL_Color const& wke1Color,
    ::SDL_Color const& bke8Color) noexcept {
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
    ::SDL_Renderer* const renderer, int const squareWidth, int const x,
    int const y, ::SDL_Color const& color) noexcept {
    ::SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    const ::SDL_Rect square{
        x * squareWidth, y * squareWidth, squareWidth, squareWidth};

    ::SDL_RenderFillRect(renderer, &square);
}

void InitSolutionTexture(
    ::SDL_Renderer* const renderer, ::SDL_Texture* const texture,
    ::SDL_Color const& color) noexcept {
    ::SDL_SetTextureBlendMode(texture, ::SDL_BlendMode::SDL_BLENDMODE_BLEND);

    ::SDL_SetRenderTarget(renderer, texture);

    ::SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    ::SDL_RenderClear(renderer);
}

void DrawTrominoOutline(
    ::SDL_Renderer* const renderer, ::SDL_Texture* const texture,
    int const squareWidth, int const thickness,
    ::SDL_Color const& color) noexcept {
    ::SDL_SetRenderTarget(renderer, texture);
    ::SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    ::SDL_Rect segment{squareWidth, 0, squareWidth, thickness};
    ::SDL_RenderFillRect(renderer, &segment);

    segment.x = (squareWidth * 2) - thickness;
    segment.y = thickness;
    segment.w = thickness;
    segment.h = squareWidth * 2;
    ::SDL_RenderFillRect(renderer, &segment);

    segment.x = 0;
    segment.y = (squareWidth * 2) - thickness;
    segment.w = (squareWidth * 2) - thickness;
    segment.h = thickness;
    ::SDL_RenderFillRect(renderer, &segment);

    segment.x = 0;
    segment.y = squareWidth;
    segment.w = thickness;
    segment.h = squareWidth - thickness;
    ::SDL_RenderFillRect(renderer, &segment);

    segment.x = thickness;
    segment.y = squareWidth;
    segment.w = squareWidth;
    segment.h = thickness;
    ::SDL_RenderFillRect(renderer, &segment);

    segment.x = squareWidth;
    segment.y = thickness;
    segment.w = thickness;
    segment.h = squareWidth - thickness;
    ::SDL_RenderFillRect(renderer, &segment);
}

} // namespace tromino::gfx2d
