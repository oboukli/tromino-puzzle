// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef board_h
#define board_h

#include <cstddef>

#include "tromino.h"

namespace tromino::gfx2d {

struct board_t {
    std::size_t size;
    int order;
    position_t mark;
};

} // namespace tromino::gfx2d

#endif // board_h
