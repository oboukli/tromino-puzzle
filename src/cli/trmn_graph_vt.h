// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

#ifndef trmn_graph_vt_h
#define trmn_graph_vt_h

#include <array>
#include <cassert>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#ifdef _WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif // _WINDOWS

#include "trimino.h"
#include "trmn_graph.h"

namespace trimino::vt {

    constexpr char neutral = 'N';
    constexpr char empty = ' ';

    constexpr char mark = 'X';
    constexpr char horizontal = '-';
    constexpr char vertical = '|';
    constexpr char top_left = '+';
    constexpr char top_right = '+';
    constexpr char bottom_left = '+';
    constexpr char bottom_right = '+';

    constexpr auto sprite_size = 4;

    std::array<char, sprite_size> get_sprite(rotation rot);

    void draw_at(int x, int y, char c);

    void draw_board(const board* board);

    void add_trimino(position abspos, rotation rot, void* graph_state);

    inline void init_board(board* board) {
        std::fill_n(board->board_matrix.get(), board->size, empty);

        board->board_matrix[calc_index(board->mark.x, board->mark.y, board->order)] = mark;
    }
} // namespace trimino
#endif // trmn_graph_vt_h
