// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef BOARD_H
#define BOARD_H

#include <cstddef>

#include "tromino.h"

namespace tromino::gfx2d {

struct Board {
    const std::size_t size;
    const int order;
    const int mark_x;
    const int mark_y;
};

} // namespace tromino::gfx2d

#endif // BOARD_H
