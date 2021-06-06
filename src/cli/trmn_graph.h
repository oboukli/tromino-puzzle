// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

#ifndef trmn_graph_h
#define trmn_graph_h

#include <array>
#include <cassert>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "trimino.h"
#include "trmn_graph.h"

namespace trimino {

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

struct trimino_board {
    std::unique_ptr<char[]> board;
    int size;
    int order;
    position mark;
};

std::array<char, sprite_size> get_sprite(rotation rot);

void draw_at(int x, int y, char c);

void draw_board(const trimino_board * board);

void add_trimino(position abspos, rotation rot, void * state);

template <typename T>
inline T calc_index(T x, T y, T o) {
    return y * o + x;
}

inline void init_board(trimino_board * board) {
    std::fill_n(board->board.get(), board->size, trimino::empty);

    board->board[calc_index(board->mark.x, board->mark.y, board->order)] = trimino::mark;
}

} // namespace trimino
#endif /* trmn_graph_h */
