// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef style_h
#define style_h

#include <SDL2/SDL.h>

namespace tromino::gfx2d {

struct Style {
    SDL_Color wke1_color;
    SDL_Color bke8_color;
    SDL_Color mark_color;
    SDL_Color tromino_color;
    SDL_Color tromino_outline_color;
};

} // namespace tromino::gfx2d

#endif /* style_h */