// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef TROMINO_GFX2D_BOARD_HPP_
#define TROMINO_GFX2D_BOARD_HPP_

#include <cstddef>

namespace tromino::gfx2d {

struct Board {
    std::size_t size{};
    int order{};
    int mark_x{};
    int mark_y{};
};

} // namespace tromino::gfx2d

#endif // TROMINO_GFX2D_BOARD_HPP_
