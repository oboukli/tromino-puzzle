#include "tromino_gfx.h"

SDL_Texture * CreateBoardTextureAndSetRenderTarget(SDL_Renderer * renderer, int width) {
    SDL_Texture * texture = SDL_CreateTexture(
        renderer, SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        width,
        width);
    
    SDL_SetRenderTarget(renderer, texture);
    
    return texture;
}

SDL_Texture * InitFilledTromino(SDL_Renderer * renderer, int squareWidth) {
    SDL_Texture * texture = SDL_CreateTexture(
        renderer, SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        squareWidth * 2,
        squareWidth * 2);

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    SDL_SetRenderTarget(renderer, texture);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 127, 63, 128);

    SDL_Rect square = {squareWidth, 0, squareWidth, squareWidth};
    SDL_RenderFillRect(renderer, &square);

    SDL_Rect rectangle = {0, squareWidth, squareWidth * 2, squareWidth};
    SDL_RenderFillRect(renderer, &rectangle);

    SDL_SetRenderTarget(renderer, NULL);

    return texture;
}

void InitCheckeredBoard(SDL_Renderer * renderer, int squareWidth, int order) {
    SDL_SetRenderDrawColor(renderer, 127, 255, 127, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 31, 31, 128, SDL_ALPHA_OPAQUE);
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
}

void DrawMark(SDL_Renderer * renderer, int squareWidth, int x, int y) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 31, SDL_ALPHA_OPAQUE);
    SDL_Rect square = {x * squareWidth, y * squareWidth, squareWidth, squareWidth};

    SDL_RenderFillRect(renderer, &square);
}

void DrawTrominoOutline(SDL_Renderer * renderer, SDL_Texture * texture, int squareWidth, int thickness) {
    constexpr size_t numSegments = 6;

    SDL_Rect segments[numSegments] = {
        {squareWidth, 0, squareWidth, thickness},
        {(squareWidth * 2) - thickness, thickness, thickness, squareWidth * 2},
        {0, (squareWidth * 2) - thickness, squareWidth * 2 - thickness, thickness},
        {0, squareWidth, thickness, squareWidth - thickness},
        {thickness, squareWidth, squareWidth, thickness},
        {squareWidth, thickness, thickness, squareWidth - thickness},
    };
    
    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, 255, 127, 127, SDL_ALPHA_OPAQUE);
    
    for (size_t i = 0; i < numSegments; ++i) {
        SDL_RenderFillRect(renderer, &segments[i]);
    }

    SDL_SetRenderTarget(renderer, NULL);
}
