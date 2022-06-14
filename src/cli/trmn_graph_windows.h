// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef TRMN_GRAPH_WINDOWS_H
#define TRMN_GRAPH_WINDOWS_H

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <algorithm>

#include "tromino.h"

#include "trmn_graph.h"

namespace tromino::cli::windows {

constexpr char neutral = 'N';
constexpr char empty = '\xB0';

constexpr char mark = '\xFE';
constexpr char horizontal = '\xCD';
constexpr char vertical = '\xBA';
constexpr char top_left = '\xC9';
constexpr char top_right = '\xBB';
constexpr char bottom_left = '\xC8';
constexpr char bottom_right = '\xBC';

void draw_board(const board_t& board) noexcept;

void add_tromino(
    const int pos_x, const int pos_y, const int flip_x, const int flip_y,
    void* const graph_state) noexcept;

inline void init_board(const board_t& board) noexcept {
    std::fill_n(board.board_matrix.get(), board.size, empty);

    board.board_matrix[calc_index(board.mark_x, board.mark_y, board.order)]
        = mark;
}

void use_wch(board_t& tromino_board, std::ostream& os) noexcept;

} // namespace tromino::cli::windows

#endif // TRMN_GRAPH_WINDOWS_H
