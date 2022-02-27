// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef BOARD_H_
#define BOARD_H_

#include <cstddef>

#include "tromino.h"

namespace tromino::gfx2d {

struct Board {
    const trmn_position_t mark;
    const std::size_t size;
    const int order;
};

} // namespace tromino::gfx2d

#endif // BOARD_H_
