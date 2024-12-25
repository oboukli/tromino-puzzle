// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef CLI_TRMN_GRAPH_HPP_
#define CLI_TRMN_GRAPH_HPP_

#ifdef _WIN64
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif // _WIN64

#include <array>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <memory>

#include <tromino/core/tromino.h>

#ifndef NDEBUG
#include <tromino/validation/validation.h>
#endif // !NDEBUG

namespace tromino::cli {

struct board_t {
    std::unique_ptr<char[]> board_matrix;
    std::size_t size{};
    int order{};
    int mark_x{};
    int mark_y{};
};

struct graph_state_t {
    std::ostream& os;
    board_t& board;
#ifdef _WIN64
    ::HANDLE hOutput{};
#endif // _WIN64
};

template <typename T>
inline std::size_t calc_index(T const x, T const y, T const o) noexcept
{
    assert(::trmn_is_valid_config(o, x, y));
    return (static_cast<std::size_t>(y) * static_cast<std::size_t>(o))
        + static_cast<std::size_t>(x);
}

constexpr std::size_t const SPRITE_SIZE{4};

template <
    char neutral,
    char empty,
    char mark,
    char horizontal,
    char vertical,
    char top_left,
    char top_right,
    char bottom_left,
    char bottom_right>
[[nodiscard]] inline std::array<char, SPRITE_SIZE>
get_sprite(int const flip_x, int const flip_y) noexcept
{
    assert(flip_x == -1 || flip_x == 1);
    assert(flip_y == -1 || flip_y == 1);

    std::array<char, SPRITE_SIZE> sprite{};

    if (flip_x == -1)
    {
        if (flip_y == -1)
        {
            // -1, -1
            // X |
            // - +
            sprite[0] = neutral;
            sprite[1] = vertical;
            sprite[2] = horizontal;
            sprite[3] = bottom_right;
        }
        else
        {
            // -1, 1
            // - +
            // X |
            sprite[0] = horizontal;
            sprite[1] = top_right;
            sprite[2] = neutral;
            sprite[3] = vertical;
        }
    }
    else
    {
        if (flip_y == -1)
        {
            // 1, -1
            // | X
            // + -
            sprite[0] = vertical;
            sprite[1] = neutral;
            sprite[2] = bottom_left;
            sprite[3] = horizontal;
        }
        else
        {
            // 1, 1
            // + -
            // | X
            sprite[0] = top_left;
            sprite[1] = horizontal;
            sprite[2] = vertical;
            sprite[3] = neutral;
        }
    }

    return sprite;
}

} // namespace tromino::cli

#endif // CLI_TRMN_GRAPH_HPP_
