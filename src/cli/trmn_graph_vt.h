// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef CLI_TRMN_GRAPH_VT_H
#define CLI_TRMN_GRAPH_VT_H

#ifdef _WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif // _WINDOWS

#include <algorithm>
#include <iostream>

#include "tromino.h"

#include "trmn_graph.h"

namespace tromino::cli::vt {

constexpr const auto BEL = "\a";
constexpr const auto ESC = "\x1b";
constexpr const auto CSI = "\x1b[";

constexpr const auto BOARD_BACKGROUND_COLOR = "23";

constexpr const auto MARK_BACKGROUND_COLOR = "199";
constexpr const auto MARK_FOREGROUND_COLOR = "216";

constexpr const auto TROMINO_BACKGROUND_COLOR = "18";
constexpr const auto TROMINO_FOREGROUND_COLOR = "226";

constexpr const char neutral = 'N';
constexpr const char empty = ' ';

constexpr const char mark = 'X';

#ifdef TROMINO_USE_ASCII
constexpr const char horizontal = '-';
constexpr const char vertical = '|';
constexpr const char top_left = '+';
constexpr const char top_right = '+';
constexpr const char bottom_left = '+';
constexpr const char bottom_right = '+';
#else
constexpr const char horizontal = '\x71';
constexpr const char vertical = '\x78';
constexpr const char top_left = '\x6c';
constexpr const char top_right = '\x6b';
constexpr const char bottom_left = '\x6d';
constexpr const char bottom_right = '\x6a';
#endif // TROMINO_USE_ASCII

void draw_board(const board_t& board, std::ostream& os) noexcept;

void add_tromino(
    const int pos_x, const int pos_y, const int flip_x, const int flip_y,
    void* const graph_state) noexcept;

inline void init_board(const board_t& board) noexcept {
    std::fill_n(board.board_matrix.get(), board.size, empty);

    board.board_matrix[calc_index(board.mark_x, board.mark_y, board.order)]
        = mark;
}

void use_vt(board_t& tromino_board, std::ostream& os) noexcept;

} // namespace tromino::cli::vt

#endif // CLI_TRMN_GRAPH_VT_H
