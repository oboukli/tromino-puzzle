// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef CLI_TRMN_GRAPH_VT_HPP
#define CLI_TRMN_GRAPH_VT_HPP

#ifdef _WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif // _WINDOWS

#include <algorithm>
#include <iostream>

#include "tromino.h"

#include "trmn_graph.hpp"

namespace tromino::cli::vt {

constexpr auto const BEL{"\a"};
constexpr auto const ESC{"\x1b"};
constexpr auto const CSI{"\x1b["};

constexpr auto const BOARD_BACKGROUND_COLOR{"23"};

constexpr auto const MARK_BACKGROUND_COLOR{"199"};
constexpr auto const MARK_FOREGROUND_COLOR{"216"};

constexpr auto const TROMINO_BACKGROUND_COLOR{"18"};
constexpr auto const TROMINO_FOREGROUND_COLOR{"226"};

constexpr char const NEUTRAL{'N'};
constexpr char const EMPTY{' '};

constexpr char const MARK{'X'};

#ifdef TROMINO_USE_ASCII
constexpr char const HORIZONTAL{'-'};
constexpr char const VERTICAL{'|'};
constexpr char const TOP_LEFT{'+'};
constexpr char const TOP_RIGHT{'+'};
constexpr char const BOTTOM_LEFT{'+'};
constexpr char const BOTTOM_RIGHT{'+'};
#else
constexpr char const HORIZONTAL{'\x71'};
constexpr char const VERTICAL{'\x78'};
constexpr char const TOP_LEFT{'\x6c'};
constexpr char const TOP_RIGHT{'\x6b'};
constexpr char const BOTTOM_LEFT{'\x6d'};
constexpr char const BOTTOM_RIGHT{'\x6a'};
#endif // TROMINO_USE_ASCII

void draw_board(board_t const& board, std::ostream& os) noexcept;

void add_tromino(
    int const pos_x, int const pos_y, int const flip_x, int const flip_y,
    void* const state) noexcept;

inline void init_board(board_t const& board) noexcept {
    std::fill_n(board.board_matrix.get(), board.size, EMPTY);

    board.board_matrix[calc_index(board.mark_x, board.mark_y, board.order)]
        = MARK;
}

void use_vt(board_t& tromino_board, std::ostream& os) noexcept;

} // namespace tromino::cli::vt

#endif // CLI_TRMN_GRAPH_VT_HPP