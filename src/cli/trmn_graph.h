// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef TRMN_GRAPH_H
#define TRMN_GRAPH_H

#ifdef _WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif // _WINDOWS

#include <array>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <memory>

#include "tromino.h"

#ifndef NDEBUG
#include "tromino_validation.h"
#endif // !NDEBUG

namespace tromino::cli {

struct board_t {
    std::unique_ptr<char[]> board_matrix;
    const std::size_t size;
    const int order;
    const int mark_x;
    const int mark_y;
};

struct graph_state_t {
    std::ostream& os;
    board_t& board;
#ifdef _WINDOWS
    const HANDLE hOutput;
#endif // _WINDOWS
};

template <typename T>
inline std::size_t calc_index(const T x, const T y, const T o) noexcept {
    assert(::trmn_is_valid_config(o, x, y));
    return static_cast<std::size_t>(y) * static_cast<std::size_t>(o)
        + static_cast<std::size_t>(x);
}

constexpr std::size_t SPRITE_SIZE{4};

template <
    char neutral, char empty, char mark, char horizontal, char vertical,
    char top_left, char top_right, char bottom_left, char bottom_right>
inline std::array<char, SPRITE_SIZE> get_sprite(
    const int flip_x, const int flip_y) noexcept {
    assert(flip_x == -1 || flip_x == 1);
    assert(flip_y == -1 || flip_y == 1);

    if (flip_x == -1) {
        if (flip_y == -1) {
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

    if (flip_y == -1) {
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

#endif // TRMN_GRAPH_H
