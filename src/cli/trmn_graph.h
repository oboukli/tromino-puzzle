// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

#ifndef trmn_graph_h
#define trmn_graph_h

#include <memory>

#ifdef _WINDOWS
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#endif // _WINDOWS

#ifdef _WINDOWS
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#endif // _WINDOWS

#include "trimino.h"
#include "trmn_graph.h"

namespace trimino {

    struct board {
        std::unique_ptr<char[]> board_matrix;
        int size;
        int order;
        position mark;
    };

    struct graph_state_t {
        board* board; // TODO: Use smart pointer?
#ifdef _WINDOWS
        HANDLE hOutput;
#endif // _WINDOWS
    };

    template <typename T>
    inline T calc_index(T x, T y, T o) {
        return y * o + x;
    }

} // namespace trimino
#endif // trmn_graph_h
