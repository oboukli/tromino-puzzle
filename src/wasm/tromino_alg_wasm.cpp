// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <emscripten.h>

#include <cassert>
#include <cstddef>

#include "tromino.h"

typedef void (*add_tromino_extern_callback)(
    const int pos_x, const int pos_y, const int flip_x,
    const int flip_y) noexcept;

static void add_tromino(
    const int pos_x, const int pos_y, const int flip_x, const int flip_y,
    void* const state) noexcept {
    const add_tromino_extern_callback add_tromino_cb
        = reinterpret_cast<add_tromino_extern_callback>(state);

    add_tromino_cb(pos_x, pos_y, flip_x, flip_y);
}

EMSCRIPTEN_KEEPALIVE extern "C" void solve(
    const int order, const int mark_x, const int mark_y,
    add_tromino_extern_callback add_tromino_cb) noexcept {
    ::trmn_solve_puzzle(
        order, mark_x, mark_y, add_tromino,
        reinterpret_cast<void*>(add_tromino_cb));
}
