// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef GFX2D_BOARD_H
#define GFX2D_BOARD_H

#include <cstddef>

namespace tromino::gfx2d {

struct Board {
    const std::size_t size;
    const int order;
    const int mark_x;
    const int mark_y;
};

} // namespace tromino::gfx2d

#endif // GFX2D_BOARD_H
