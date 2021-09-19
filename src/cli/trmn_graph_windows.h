// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef trmn_graph_windows_h
#define trmn_graph_windows_h

#include <array>
#include <cassert>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "tromino.h"
#include "trmn_graph.h"

namespace tromino::windows {

    constexpr char neutral = 'N';
    constexpr char empty = '\xB0';

    constexpr char mark = '\xFE';
    constexpr char horizontal = '\xCD';
    constexpr char vertical = '\xBA';
    constexpr char top_left = '\xC9';
    constexpr char top_right = '\xBB';
    constexpr char bottom_left = '\xC8';
    constexpr char bottom_right = '\xBC';

    constexpr auto sprite_size = 4;

    std::array<char, sprite_size> get_sprite(flip_t flip);

    void draw_at(int x, int y, char c, HANDLE hOutput);

    void draw_board(const board_t* board);

    void add_tromino(position_t abspos, flip_t flip, void* graph_state);

    inline void init_board(board_t& board) {
        std::fill_n(board.board_matrix.get(), board.size, empty);

        board.board_matrix[calc_index(board.mark.x, board.mark.y, board.order)] = mark;
    }

    void use_wch(tromino::board_t& tromino_board);

} // namespace tromino::windows

#endif // trmn_graph_windows_h