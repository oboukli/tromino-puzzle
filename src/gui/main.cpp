// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstddef>
#include <cstdlib>
#include <iostream>

#include "init.h"

int main(const int argc, const char* const argv[]) {
    // TODO: App name
    // TODO: Refactor out of main
    constexpr int REQUIRED_ARG_COUNT = 4;
    constexpr int WIDTH = 512;

    if (REQUIRED_ARG_COUNT > argc) {
        std::cout << "Usage: tromino <order> <x> <y>" << std::endl;

        return EXIT_FAILURE;
    }

    const int order = std::stoi(argv[1]);
    const int x = std::stoi(argv[2]);
    const int y = std::stoi(argv[3]);

    const std::size_t order_internal = static_cast<std::size_t>(order);
    const std::size_t size = order_internal * order_internal;
    const tromino::gfx2d::board_t board{
        .mark = {.x = x, .y = y}, .size = size, .order = order};

    return tromino::tromino2d::init(board, WIDTH, "Tromino Puzzle");
}
