/*
Copyright (c) Omar Boukli-Hacene. All rights reserved.
Distributed under an MIT-style license that can be
found in the LICENSE file.
*/

/* SPDX-License-Identifier: MIT */

#include "litro.h"

#include <tromino/core/tromino.h>

static void add_tromino(
    int const pos_x, int const pos_y, int const flip_x, int const flip_y,
    void* const cb) {
    ((add_tromino_extern_callback)cb)(pos_x, pos_y, flip_x, flip_y);
}

EMSCRIPTEN_KEEPALIVE void solve(
    int const order, int const mark_x, int const mark_y,
    add_tromino_extern_callback add_tromino_cb) {
    static int const stop_flag = 0;
    trmn_solve_puzzle(
        order, mark_x, mark_y, add_tromino, add_tromino_cb, &stop_flag);
}
