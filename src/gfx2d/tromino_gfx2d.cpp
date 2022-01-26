// Copyright (c) Omar Boukli-Hacene 2021-2022. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "tromino_gfx2d.h"

#include <array>
#include <cassert>
#include <cstddef>

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
    ::SDL_Texture* const texture = CreateTexture(renderer, squareWidth * 2);

    ::SDL_SetTextureBlendMode(texture, ::SDL_BlendMode::SDL_BLENDMODE_BLEND);

    ::SDL_SetRenderTarget(renderer, texture);

    ::SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
    ::SDL_RenderClear(renderer);

    ::SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    const ::SDL_Rect square = {squareWidth, 0, squareWidth, squareWidth};
    ::SDL_RenderFillRect(renderer, &square);

    const ::SDL_Rect rectangle = {0, squareWidth, squareWidth * 2, squareWidth};
    ::SDL_RenderFillRect(renderer, &rectangle);

    return texture;
}

void InitCheckeredBoard(
    ::SDL_Renderer* const renderer, ::SDL_Texture* const texture,
    const int squareWidth, int order, const ::SDL_Color& wke1Color,
    const ::SDL_Color& bke8Color) noexcept {
    ::SDL_SetTextureBlendMode(texture, ::SDL_BlendMode::SDL_BLENDMODE_BLEND);

    ::SDL_SetRenderTarget(renderer, texture);

    ::SDL_SetRenderDrawColor(
        renderer, wke1Color.r, wke1Color.g, wke1Color.b, wke1Color.a);
    ::SDL_RenderClear(renderer);

    ::SDL_SetRenderDrawColor(
        renderer, bke8Color.r, bke8Color.g, bke8Color.b, bke8Color.a);
    ::SDL_Rect square = {0, 0, squareWidth, squareWidth};

    for (int j, i = 0; i < order; ++i) {
        for (j = 0; j < order; ++j) {
            if ((j & 1) != (i & 1)) {
                square.x = j * squareWidth;
                square.y = i * squareWidth;
                ::SDL_RenderFillRect(renderer, &square);
            }
        }
    }
}

void InitSolutionTexture(
    ::SDL_Renderer* const renderer, ::SDL_Texture* const texture,
    const int width, const ::SDL_Color& color) noexcept {
    ::SDL_SetTextureBlendMode(texture, ::SDL_BlendMode::SDL_BLENDMODE_BLEND);

    ::SDL_SetRenderTarget(renderer, texture);

    ::SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    ::SDL_RenderClear(renderer);
}

void DrawMark(
    ::SDL_Renderer* const renderer, const int squareWidth, const int x,
    const int y, const ::SDL_Color& color) noexcept {
    ::SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    const ::SDL_Rect square
        = {x * squareWidth, y * squareWidth, squareWidth, squareWidth};

    ::SDL_RenderFillRect(renderer, &square);
}

void DrawTrominoOutline(
    ::SDL_Renderer* const renderer, ::SDL_Texture* const texture,
    const int squareWidth, const int thickness,
    const ::SDL_Color& color) noexcept {
    constexpr std::size_t numSegments{6};

    // clang-format off
    const std::array<::SDL_Rect, numSegments> segments{{
        {squareWidth, 0, squareWidth, thickness},
        {(squareWidth * 2) - thickness, thickness, thickness, squareWidth * 2},
        {0, (squareWidth * 2) - thickness, (squareWidth * 2) - thickness, thickness},
        {0, squareWidth, thickness, squareWidth - thickness},
        {thickness, squareWidth, squareWidth, thickness},
        {squareWidth, thickness, thickness, squareWidth - thickness},
    }};
    // clang-format on

    ::SDL_SetRenderTarget(renderer, texture);
    ::SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    for (const auto& s : segments) {
        ::SDL_RenderFillRect(renderer, &s);
    }
}

} // namespace tromino::gfx2d
