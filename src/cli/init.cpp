// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

#include "init.h"

void init() {
    constexpr int order = 8;
    int size = order * order;

    position mark {
        .x = 0,
        .y = 0
    };

    trimino::trimino_board board {
        .board = std::make_unique<char[]>(size),
        .size = size,
        .order = order,
        .mark = mark
    };

    trimino::init_board(&board);

    trimino:draw_board(&board);

    solve_trimino_puzzle(order, mark, trimino::add_trimino, &board);

    trimino::draw_board(&board);
}
