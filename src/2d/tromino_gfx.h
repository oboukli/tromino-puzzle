#ifndef tromino_gfx_h
#define tromino_gfx_h

#include <assert.h>
#include <stdio.h>
#include <algorithm>

#include <SDL2/SDL.h>
#include <SDL_render.h>

SDL_Texture * InitFilledTromino(SDL_Renderer * renderer, int squareWidth);

SDL_Texture * CreateBoardTextureAndSetRenderTarget(SDL_Renderer * renderer, int width);

void InitCheckeredBoard(SDL_Renderer * renderer, int width, int order);

void DrawMark(SDL_Renderer * renderer, int squareWidth, int x, int y);

void DrawTrominoOutline(SDL_Renderer * renderer, SDL_Texture * texture, int squareWidth, int thickness);

#endif /* tromino_gfx_h */
