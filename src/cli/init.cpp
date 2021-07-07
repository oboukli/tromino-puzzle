// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

#include "init.h"

void init(int order, int x, int y) {
    int size = order * order;

    position mark{
        .x = x,
        .y = y
    };

    trimino::board trimino_board{
        .board_matrix = std::make_unique<char[]>(size),
        .size = size,
        .order = order,
        .mark = mark
    };

    bool emulate_vt = true; // TODO:
    if (emulate_vt) {
        trimino::vt::use_vt(order, mark, &trimino_board);
    }

#ifdef _WINDOWS
    bool use_windows = true; // TODO:
    if (use_windows) {
        trimino::windows::use_wch(order, mark, &trimino_board);
    }
#endif // _WINDOWS
}
