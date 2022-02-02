// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef TRMN_GRAPH_WINDOWS_H_
#define TRMN_GRAPH_WINDOWS_H_

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

void draw_at(
    const int x, const int y, const char c, const HANDLE hOutput) noexcept;

void draw_board(const board_t& board) noexcept;

void add_tromino(
    const trmn_position_t pos, const trmn_flip_t flip,
    void* const graph_state) noexcept;

inline void init_board(board_t& board) noexcept {
    std::fill_n(board.board_matrix.get(), board.size, empty);

    board.board_matrix[calc_index(board.mark.x, board.mark.y, board.order)]
        = mark;
}

void use_wch(board_t& tromino_board) noexcept;

} // namespace tromino::cli::windows

#endif // TRMN_GRAPH_WINDOWS_H_
