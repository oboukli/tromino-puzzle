// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cassert>
#include <cstddef>

#include <emscripten.h>

#include "tromino.h"
#include "tromino_gfx2d.h"
#include "init.h"

EMSCRIPTEN_KEEPALIVE extern "C" int playTromino(int order, int markX, int markY) {
    std::size_t size = order * order;
    tromino::gfx2d::board_t board{
        .size = size,
        .order = order,
        .mark = {
            .x = markX,
            .y = markY
        }
    };

    return init(board);
}
