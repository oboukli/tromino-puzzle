// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstddef>

#include "init.h"

int main(int argc, const char * argv[]) {
    int order = 32;
    std::size_t size = order * order;
    tromino::gfx2d::board_t board{
        .size = size,
        .order = order,
        .mark = {
            .x = 11,
            .y = 17
        }
    };

    return init(board);
}
