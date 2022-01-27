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

#include <cstddef>
#include <memory>

#include "tromino.h"

namespace tromino {

struct board_t {
    const trmn_position_t mark;
    const std::size_t size;
    std::unique_ptr<char[]> board_matrix;
    const int order;
};

struct graph_state_t {
    board_t& board;
#ifdef _WINDOWS
    HANDLE hOutput;
#endif // _WINDOWS
};

template <typename T>
inline const T calc_index(const T x, const T y, const T o) noexcept {
    return y * o + x;
}

} // namespace tromino

#endif // TRMN_GRAPH_H_
