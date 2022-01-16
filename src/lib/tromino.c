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

#include "tromino.h"

#include <assert.h>

static void solve_tromino(
    int order, trmn_position_t pos, trmn_flip_t flip,
    trmn_add_tromino_func add_tromino, void* state) {
    if (2 == order) {
        add_tromino(pos, flip, state);
        return;
    }

    const int n = order >> 1;

    const trmn_position_t p = {
        .x = pos.x + (n * ((flip.x + 1) >> 1)),
        .y = pos.y + (n * ((flip.y + 1) >> 1)),
    };

    solve_tromino(
        n,
        (trmn_position_t){
            .x = p.x - (flip.x * n),
            .y = p.y - (flip.y * n),
        },
        flip, add_tromino, state);

    solve_tromino(
        n,
        (trmn_position_t){
            .x = p.x - (flip.x * n),
            .y = p.y,
        },
        (trmn_flip_t){
            .x = flip.x,
            .y = flip.y * -1,
        },
        add_tromino, state);

    solve_tromino(
        n,
        (trmn_position_t){
            .x = p.x,
            .y = p.y - (flip.y * n),
        },
        (trmn_flip_t){
            .x = flip.x * -1,
            .y = flip.y,
        },
        add_tromino, state);

    const int o = n >> 1;
    solve_tromino(
        n,
        (trmn_position_t){
            .x = p.x - (flip.x * o),
            .y = p.y - (flip.y * o),
        },
        flip, add_tromino, state);
}

static void solve_board(
    int order, trmn_position_t pos, trmn_flip_t flip, trmn_position_t mark,
    trmn_add_tromino_func add_tromino, void* state) {
    if (order > 2) {
        const int n = order >> 1;

        const trmn_position_t p = {
            .x = pos.x + (n * ((flip.x + 1) >> 1)),
            .y = pos.y + (n * ((flip.y + 1) >> 1)),
        };

        const int o = n >> 1;
        const int x = mark.x - p.x;
        const int y = mark.y - p.y;
        const trmn_flip_t f = {
            .x = (int)(x >= o) - (int)(x < o),
            .y = (int)(y >= o) - (int)(y < o),
        };

        solve_board(n, p, f, mark, add_tromino, state);
    }

    solve_tromino(order, pos, flip, add_tromino, state);
}

void trmn_solve_puzzle(
    int order, trmn_position_t mark, trmn_add_tromino_func add_tromino,
    void* state) {
    assert(add_tromino);

    const trmn_position_t pos = {
        .x = 0,
        .y = 0,
    };

    const int o = order >> 1;
    const trmn_flip_t flip = {
        .x = (int)(mark.x >= o) - (int)(mark.x < o),
        .y = (int)(mark.y >= o) - (int)(mark.y < o),
    };

    solve_board(order, pos, flip, mark, add_tromino, state);
}
