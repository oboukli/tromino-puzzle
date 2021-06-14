// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

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

#include "trimino.h"
#include "trmn_graph.h"

namespace trimino::windows {

    constexpr char neutral = 'N';
    constexpr char empty = ' ';

    constexpr char mark = '\xFE';
    constexpr char horizontal = '\xCD';
    constexpr char vertical = '\xBA';
    constexpr char top_left = '\xC9';
    constexpr char top_right = '\xBB';
    constexpr char bottom_left = '\xC8';
    constexpr char bottom_right = '\xBC';

    constexpr auto sprite_size = 4;

    std::array<char, sprite_size> get_sprite(rotation rot);

    void draw_at(int x, int y, char c, HANDLE hOutput);

    void draw_board(const board* board);

    void add_trimino(position abspos, rotation rot, void* graph_state);

    inline void init_board(board* board) {
        std::fill_n(board->board_matrix.get(), board->size, empty);

        board->board_matrix[calc_index(board->mark.x, board->mark.y, board->order)] = mark;
    }

} // namespace trimino::windows
#endif // trmn_graph_windows_h
