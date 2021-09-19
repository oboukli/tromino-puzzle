// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "tromino_gfx2d.h"

namespace tromino::gfx2d {

SDL_Texture * CreateViewTexture(SDL_Renderer * renderer, int width) noexcept {
    SDL_Texture * texture = SDL_CreateTexture(
        renderer, SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        width,
        width);

    return texture;
}

SDL_Texture * InitCheckeredBoard(SDL_Renderer * renderer, int squareWidth, int order, const SDL_Color& wke1Color, const SDL_Color& bke8Color) noexcept {
    int width = squareWidth * order;
    SDL_Texture * texture = SDL_CreateTexture(
        renderer, SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        width,
        width);

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    SDL_SetRenderTarget(renderer, texture);

    SDL_SetRenderDrawColor(renderer, wke1Color.r, wke1Color.g, wke1Color.b, wke1Color.a);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, bke8Color.r, bke8Color.g, bke8Color.b, bke8Color.a);
    SDL_Rect square = {0, 0, squareWidth, squareWidth};

    for (int j, i = 0; i < order; ++i) {
        for (j = 0; j < order; ++j) {
            if ((j & 1) != (i & 1)) {
                square.x = j * squareWidth;
                square.y = i * squareWidth;
                SDL_RenderFillRect(renderer, &square);
            }
        }
    }

    return texture;
}

SDL_Texture * InitSolutionLayer(SDL_Renderer * renderer, int width, const SDL_Color& color) noexcept {
    SDL_Texture * texture = SDL_CreateTexture(
        renderer, SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        width,
        width);

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    SDL_SetRenderTarget(renderer, texture);

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);

    return texture;
}

SDL_Texture * InitFilledTromino(SDL_Renderer * renderer, int squareWidth, const SDL_Color& color) noexcept {
    SDL_Texture * texture = SDL_CreateTexture(
        renderer, SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET, // TODO:
        squareWidth * 2,
        squareWidth * 2);

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    SDL_SetRenderTarget(renderer, texture);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    SDL_Rect square = {squareWidth, 0, squareWidth, squareWidth};
    SDL_RenderFillRect(renderer, &square);

    SDL_Rect rectangle = {0, squareWidth, squareWidth * 2, squareWidth};
    SDL_RenderFillRect(renderer, &rectangle);

    return texture;
}

void DrawMark(SDL_Renderer * renderer, int squareWidth, int x, int y, const SDL_Color& color) noexcept {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect square = {x * squareWidth, y * squareWidth, squareWidth, squareWidth};

    SDL_RenderFillRect(renderer, &square);
}

void DrawTrominoOutline(SDL_Renderer * renderer, SDL_Texture * texture, int squareWidth, int thickness, const SDL_Color& color) noexcept {
    constexpr std::size_t numSegments = 6;

    SDL_Rect segments[numSegments] = {
        {squareWidth, 0, squareWidth, thickness},
        {(squareWidth * 2) - thickness, thickness, thickness, squareWidth * 2},
        {0, (squareWidth * 2) - thickness, squareWidth * 2 - thickness, thickness},
        {0, squareWidth, thickness, squareWidth - thickness},
        {thickness, squareWidth, squareWidth, thickness},
        {squareWidth, thickness, thickness, squareWidth - thickness},
    };

    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    for (std::size_t i = 0; i < numSegments; ++i) {
        SDL_RenderFillRect(renderer, &segments[i]);
    }
}

} // namespace tromino::gfx2d