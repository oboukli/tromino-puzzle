// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef STYLE_H_
#define STYLE_H_

#include <SDL2/SDL.h>

namespace tromino::gfx2d {

struct Style {
    const ::SDL_Color wke1_color;
    const ::SDL_Color bke8_color;
    const ::SDL_Color mark_color;
    const ::SDL_Color tromino_color;
    const ::SDL_Color tromino_outline_color;
};

} // namespace tromino::gfx2d

#endif // STYLE_H_
