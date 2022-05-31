// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "init.h"

#include <cstddef>
#include <memory>

#include "trmn_graph.h"
#include "trmn_graph_vt.h"

#ifdef _WINDOWS
#include "trmn_graph_windows.h"
#endif // _WINDOWS

namespace tromino::cli::app {

void init(const int order, const int x, const int y) noexcept {
    const auto order_internal = static_cast<std::size_t>(order);
    const std::size_t size = order_internal * order_internal;

    board_t tromino_board{
        .board_matrix = std::make_unique<char[]>(size),
        .size = size,
        .order = order,
        .mark_x = x,
        .mark_y = y};

    tromino::cli::vt::use_vt(tromino_board, std::cout);
}

#ifdef _WINDOWS
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

    if (emulation_mode == emulation_mode_type::wch) {
        tromino::cli::windows::use_wch(tromino_board, std::cout);
        return;
    }

    tromino::cli::vt::use_vt(tromino_board, std::cout);
}
#endif // _WINDOWS

} // namespace tromino::cli::app
