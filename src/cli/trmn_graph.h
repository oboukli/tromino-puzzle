// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef TRMN_GRAPH_H_
#define TRMN_GRAPH_H_

#include "trmn_graph.h"

#ifdef _WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif // _WINDOWS

#include <array>
#include <cassert>
#include <cstddef>
#include <memory>

#include "tromino.h"

namespace tromino::cli {

struct board_t {
    const trmn_position_t mark;
    const std::size_t size;
    std::unique_ptr<char[]> board_matrix;
    const int order;
};

struct graph_state_t {
    board_t& board;
#ifdef _WINDOWS
    const HANDLE hOutput;
#endif // _WINDOWS
};

template <typename T>
inline T calc_index(const T x, const T y, const T o) noexcept {
    return y * o + x;
}

constexpr std::size_t SPRITE_SIZE{4};

template <
    char neutral, char empty, char mark, char horizontal, char vertical,
    char top_left, char top_right, char bottom_left, char bottom_right>
static std::array<char, SPRITE_SIZE> get_sprite(
    const trmn_flip_t& flip) noexcept {
    assert(-1 == flip.x || 1 == flip.x);
    assert(-1 == flip.y || 1 == flip.y);

    if (-1 == flip.x) {
        if (-1 == flip.y) {
            // -1, -1
            // X |
            // - +
            return {neutral, vertical, horizontal, bottom_right};
        }

        // -1, 1
        // - +
        // X |
        return {horizontal, top_right, neutral, vertical};
    }

    if (-1 == flip.y) {
        // 1, -1
        // | X
        // + -
        return {vertical, neutral, bottom_left, horizontal};
    }

    // 1, 1
    // + -
    // | X
    return {top_left, horizontal, vertical, neutral};
}

} // namespace tromino::cli

#endif // TRMN_GRAPH_H_
