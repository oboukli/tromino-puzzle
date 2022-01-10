// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
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

#include <memory>

#include "tromino.h"

namespace tromino {

    struct board_t {
        trmn_position_t mark;
        std::size_t size;
        std::unique_ptr<char[]> board_matrix;
        int order;
    };

    struct graph_state_t {
        board_t& board;
#ifdef _WINDOWS
        HANDLE hOutput;
#endif // _WINDOWS
    };

    template <typename T>
    inline T calc_index(T x, T y, T o) {
        return y * o + x;
    }

} // namespace tromino

#endif // TRMN_GRAPH_H_
