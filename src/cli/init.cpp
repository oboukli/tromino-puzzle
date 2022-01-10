// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "init.h"

void init(int order, int x, int y, emulation_mode emulation_mode) {
    std::size_t order_internal = static_cast<std::size_t>(order);
    std::size_t size = order_internal * order_internal;

    tromino::board_t tromino_board{
        .mark = {
            .x = x,
            .y = y
        },
        .size = size,
        .board_matrix = std::make_unique<char[]>(size),
        .order = order
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
