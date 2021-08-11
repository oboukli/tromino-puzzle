// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

#include "init.h"

void init(int order, int x, int y, emulation_mode emulation_mode) {
    size_t size = order * order;

    tromino::board_t tromino_board{
        .board_matrix = std::make_unique<char[]>(size),
        .size = size,
        .order = order,
        .mark = {
            .x = x,
            .y = y
        }
    };

    switch (emulation_mode) {
#ifdef _WINDOWS
            case emulation_mode::windows_console_host:
                tromino::windows::use_wch(tromino_board);
                break;
#endif // _WINDOWS

            case emulation_mode::vt_100:
            default:
                tromino::vt::use_vt(tromino_board);
                break;
        }
}
