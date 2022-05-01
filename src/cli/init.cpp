// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "init.h"

#include <cstddef>

namespace tromino::cli::app {

void init(
    const int order, const int x, const int y,
    const emulation_mode_type emulation_mode) noexcept {
    const auto order_internal = static_cast<std::size_t>(order);
    const std::size_t size = order_internal * order_internal;

    board_t tromino_board{
        .board_matrix = std::make_unique<char[]>(size),
        .size = size,
        .order = order,
        .mark_x = x,
        .mark_y = y};

#ifdef _WINDOWS
    if (emulation_mode == emulation_mode_type::wch) {
        tromino::cli::windows::use_wch(tromino_board);
        return;
    }
#endif // _WINDOWS

    tromino::cli::vt::use_vt(tromino_board);
}

} // namespace tromino::cli::app
