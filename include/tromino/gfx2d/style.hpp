// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef TROMINO_GFX2D_STYLE_HPP
#define TROMINO_GFX2D_STYLE_HPP

#include <SDL2/SDL.h>

namespace tromino::gfx2d {

/// Model after an 8 * 8 chess board.
struct Style {
    ::SDL_Color wke1_color{};
    ::SDL_Color bke8_color{};
    ::SDL_Color mark_color{};
    ::SDL_Color tromino_color{};
    ::SDL_Color tromino_outline_color{};
};

} // namespace tromino::gfx2d

#endif // TROMINO_GFX2D_STYLE_HPP
