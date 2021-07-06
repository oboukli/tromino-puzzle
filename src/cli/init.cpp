// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

#include "init.h"

#ifdef _WINDOWS // TODO: Refactor out
void use_windows_console(int order, position mark, trimino::board* trimino_board_ptr) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    trimino::graph_state graph_state{
        .board = trimino_board_ptr,
        .hOutput = hStdout,
    };

    trimino::windows::init_board(trimino_board_ptr);

    trimino::windows::draw_board(trimino_board_ptr);

    solve_trimino_puzzle(order, mark, trimino::windows::add_trimino, &graph_state);

    trimino::windows::draw_board(trimino_board_ptr);
}
#endif // _WINDOWS

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
        use_windows_console(order, mark, &trimino_board);
    }
#endif // _WINDOWS
}
