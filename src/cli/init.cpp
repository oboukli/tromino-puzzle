// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

#include "init.h"

void use_vt(int order, position mark, trimino::board * trimino_board_ptr) {
#ifdef _WINDOWS
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    DWORD dwConsoleOriginalMode = 0;
    DWORD dwConsoleModifiedMode;
    GetConsoleMode(hStdout, &dwConsoleOriginalMode);

    dwConsoleModifiedMode = dwConsoleOriginalMode
        | ENABLE_PROCESSED_OUTPUT
        | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hStdout, dwConsoleModifiedMode);
#endif // _WINDOWS

    trimino::graph_state graph_state{
        .board = trimino_board_ptr,
// #ifdef _WINDOWS // TODO: && win console
//         .hOutput = hStdout,
// #endif // _WINDOWS
    };

    trimino::vt::init_board(trimino_board_ptr);

    trimino::vt::draw_board(trimino_board_ptr);

    solve_trimino_puzzle(order, mark, trimino::vt::add_trimino, &graph_state);

    trimino::vt::draw_board(trimino_board_ptr);

#ifdef _WINDOWS
    assert(0 != dwConsoleOriginalMode);
    SetConsoleMode(hStdout, dwConsoleOriginalMode);
#endif // _WINDOWS
}

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

void init() {
    constexpr int order = 8; // TODO:
    int size = order * order;

    position mark{ // TODO:
        .x = 0,
        .y = 0
    };

    trimino::board trimino_board{
        .board_matrix = std::make_unique<char[]>(size),
        .size = size,
        .order = order,
        .mark = mark
    };

    bool emulate_vt = true; // TODO:
    if (emulate_vt) {
        use_vt(order, mark, &trimino_board);
    }

#ifdef _WINDOWS
    bool use_windows = true; // TODO:
    if (use_windows) {
        use_windows_console(order, mark, &trimino_board);
    }
#endif // _WINDOWS
}
