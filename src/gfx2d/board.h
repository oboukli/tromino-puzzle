// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef BOARD_H_
#define BOARD_H_

#include <cstddef>

#include "tromino.h"

namespace tromino::gfx2d {

struct board_t {
    trmn_position_t mark;
    std::size_t size;
    int order;
};

} // namespace tromino::gfx2d

#endif // BOARD_H_
