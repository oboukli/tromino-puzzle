// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "litro.h"

#include "tromino.h"

static void add_tromino(
    const int pos_x, const int pos_y, const int flip_x, const int flip_y,
    void* const cb) {
    ((add_tromino_extern_callback)cb)(pos_x, pos_y, flip_x, flip_y);
}

EMSCRIPTEN_KEEPALIVE void solve(
    const int order, const int mark_x, const int mark_y,
    add_tromino_extern_callback add_tromino_cb) {
    trmn_solve_puzzle(order, mark_x, mark_y, add_tromino, add_tromino_cb);
}
