/*
Copyright (c) 2021 Omar Boukli-Hacene. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/* SPDX-License-Identifier: MIT */

#include <assert.h>

#include "tromino.h"

static void solve_tromino(int order, position_t pos, flip_t flip, add_tromino_func add_tromino, void * state) {
    if (2 == order) {
        add_tromino(pos, flip, state);

        return;
    }

    const int n = order >> 1;
    const int o = n >> 1;

    const position_t p = {
        .x = flip.x == -1 ? pos.x : pos.x + n,
        .y = flip.y == -1 ? pos.y : pos.y + n,
    };

    solve_tromino(
        n,
        (position_t) {
            .x = p.x - (flip.x * n),
            .y = p.y - (flip.y * n),
        },
        flip,
        add_tromino,
        state);

    solve_tromino(
        n,
        (position_t) {
            .x = p.x - (flip.x * n),
            .y = p.y,
        },
        (flip_t) {
            .x = flip.x,
            .y = flip.y * -1,
        },
        add_tromino,
        state);

    solve_tromino(n,
        (position_t) {
            .x = p.x,
            .y = p.y - (flip.y * n),
        },
        (flip_t) {
            .x = flip.x * -1,
            .y = flip.y,
        },
        add_tromino,
        state);

    solve_tromino(
        n,
        (position_t) {
            .x = p.x - (flip.x * o),
            .y = p.y - (flip.y * o),
        },
        flip,
        add_tromino,
        state);
}

static void solve_board(int order, position_t pos, flip_t flip, position_t mark, add_tromino_func add_tromino, void * state) {
    if (order > 2) {
        const int s = order >> 1;
        const position_t p = {
            .x = flip.x == -1 ? pos.x : pos.x + s,
            .y = flip.y == -1 ? pos.y : pos.y + s,
        };

        const int ss = s >> 1;
        const flip_t r = {
            .x = (mark.x - p.x) < ss ? -1 : 1,
            .y = (mark.y - p.y) < ss ? -1 : 1,
        };

        solve_board(s, p, r, mark, add_tromino, state);
    }

    solve_tromino(order, pos, flip, add_tromino, state);
}

void solve_tromino_puzzle(int board_order, position_t mark, add_tromino_func add_tromino, void * state) {
    assert(add_tromino);

    const position_t pos = {
        .x = 0,
        .y = 0,
    };

    const int s = board_order >> 1;

    const flip_t flip = {
        .x = mark.x < s ? -1 : 1,
        .y = mark.y < s ? -1 : 1,
    };

    solve_board(board_order, pos, flip, mark, add_tromino, state);
}
