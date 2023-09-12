// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef CLI_TRMN_GRAPH_WINDOWS_HPP
#define CLI_TRMN_GRAPH_WINDOWS_HPP

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <algorithm>

#include <tromino/core/tromino.h>

#include "trmn_graph.hpp"

namespace tromino::cli::windows {

constexpr char const neutral{'N'};
constexpr char const empty{'\xB0'};

constexpr char const mark{'\xFE'};
constexpr char const horizontal{'\xCD'};
constexpr char const vertical{'\xBA'};
constexpr char const top_left{'\xC9'};
constexpr char const top_right{'\xBB'};
constexpr char const bottom_left{'\xC8'};
constexpr char const bottom_right{'\xBC'};

void draw_board(board_t const& board) noexcept;

void add_tromino(
    int const pos_x,
    int const pos_y,
    int const flip_x,
    int const flip_y,
    void* const state) noexcept;

inline void init_board(board_t const& board) noexcept
{
    std::fill_n(board.board_matrix.get(), board.size, empty);

    board.board_matrix[calc_index(board.mark_x, board.mark_y, board.order)]
        = mark;
}

void use_wch(board_t& tromino_board, std::ostream& os) noexcept;

} // namespace tromino::cli::windows

#endif // CLI_TRMN_GRAPH_WINDOWS_HPP
