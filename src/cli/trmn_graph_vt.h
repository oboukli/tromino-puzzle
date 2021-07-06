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

#define BEL "\a"
#define ESC "\x1b"
#define CSI "\x1b["

#define BOARD_BACKGROUND_COLOR "23"

#define MARK_BACKGROUND_COLOR "199"
#define MARK_FOREGROUND_COLOR "216"

#define TRIMINO_BACKGROUND_COLOR "18"
#define TRIMINO_FOREGROUND_COLOR "226"

namespace trimino::vt {

    constexpr char neutral = 'N';
    constexpr char empty = ' ';

    constexpr char mark = 'X';

#ifdef TRIMINO_USE_ASCII
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
#endif // TRIMINO_USE_ASCII

    constexpr auto sprite_size = 4;

    std::array<char, sprite_size> get_sprite(rotation rot);

    void draw_at(int x, int y, char c);

    void draw_board(const board* board);

    void add_trimino(position abspos, rotation rot, void* graph_state);

    inline void init_board(board* board) {
        std::fill_n(board->board_matrix.get(), board->size, empty);

        board->board_matrix[calc_index(board->mark.x, board->mark.y, board->order)] = mark;
    }

    void use_vt(int order, position mark, trimino::board * trimino_board_ptr);

} // namespace trimino
#endif // trmn_graph_vt_h
