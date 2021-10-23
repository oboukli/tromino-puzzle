// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstddef>
#include <cstdlib>
#include <iostream>

#include "init.h"

int main(int argc, const char * argv[]) {
    // TODO: Config values
    // TODO: App name
    // TODO: Refactor out of main
    constexpr int REQUIRED_ARG_COUNT = 4;

    if (REQUIRED_ARG_COUNT > argc) {
        std::cout
            << "Usage: tromino <order> <x> <y>"
            << std::endl;

        return EXIT_FAILURE;
    }

    int order = std::stoi(argv[1]);
    int x = std::stoi(argv[2]);
    int y = std::stoi(argv[3]);

    std::size_t order_internal = static_cast<std::size_t>((order));
    std::size_t size = order_internal * order_internal;
    tromino::gfx2d::board_t board{
        .size = size,
        .order = order,
        .mark = {
            .x = x,
            .y = y
        }
    };

    return init(board);
}
