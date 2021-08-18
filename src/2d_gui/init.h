#ifndef init_h
#define init_h

#include <iostream>
#include <memory>
#include <queue>

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL_render.h>

#include "tromino.h"
#include "tromino_gfx.h"

struct board_t {
    size_t size;
    int order;
    position_t mark;
};

int init(const board_t& board);

#endif /* init_h */
