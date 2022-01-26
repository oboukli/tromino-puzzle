// Copyright (c) Omar Boukli-Hacene 2021-2022. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef TRMN_GRAPH_VT_H_
#define TRMN_GRAPH_VT_H_

#ifdef _WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif // _WINDOWS

#include <algorithm>

#include "tromino.h"

#include "trmn_graph.h"

#define BEL "\a"
#define ESC "\x1b"
#define CSI "\x1b["

#define BOARD_BACKGROUND_COLOR "23"

#define MARK_BACKGROUND_COLOR "199"
#define MARK_FOREGROUND_COLOR "216"

#define TROMINO_BACKGROUND_COLOR "18"
#define TROMINO_FOREGROUND_COLOR "226"

namespace tromino::vt {

constexpr char neutral = 'N';
constexpr char empty = ' ';

constexpr char mark = 'X';

#ifdef TROMINO_USE_ASCII
constexpr char horizontal = '-';
constexpr char vertical = '|';
constexpr char top_left = '+';
constexpr char top_right = '+';
constexpr char bottom_left = '+';
constexpr char bottom_right = '+';
#else
constexpr char horizontal = '\x71';
constexpr char vertical = '\x78';
constexpr char top_left = '\x6c';
constexpr char top_right = '\x6b';
constexpr char bottom_left = '\x6d';
constexpr char bottom_right = '\x6a';
#endif // TROMINO_USE_ASCII

void draw_board(const board_t& board) noexcept;

void add_tromino(
    const trmn_position_t pos, const trmn_flip_t flip,
    void* const graph_state) noexcept;

inline void init_board(board_t& board) noexcept {
    std::fill_n(board.board_matrix.get(), board.size, empty);

    board.board_matrix[calc_index(board.mark.x, board.mark.y, board.order)]
        = mark;
}

void use_vt(tromino::board_t& tromino_board) noexcept;

} // namespace tromino::vt

#endif // TRMN_GRAPH_VT_H_
