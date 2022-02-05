// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
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

constexpr auto BEL = "\a";
constexpr auto ESC = "\x1b";
constexpr auto CSI = "\x1b[";

constexpr auto BOARD_BACKGROUND_COLOR = "23";

constexpr auto MARK_BACKGROUND_COLOR = "199";
constexpr auto MARK_FOREGROUND_COLOR = "216";

constexpr auto TROMINO_BACKGROUND_COLOR = "18";
constexpr auto TROMINO_FOREGROUND_COLOR = "226";

namespace tromino::cli::vt {

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

inline void init_board(const board_t& board) noexcept {
    std::fill_n(board.board_matrix.get(), board.size, empty);

    board.board_matrix[calc_index(board.mark.x, board.mark.y, board.order)]
        = mark;
}

void use_vt(board_t& tromino_board) noexcept;

} // namespace tromino::cli::vt

#endif // TRMN_GRAPH_VT_H_
