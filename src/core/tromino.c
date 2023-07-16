/*
Copyright (c) Omar Boukli-Hacene. All rights reserved.

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
    int const order, int const px, int const py, int const fx, int const fy,
    trmn_add_tromino_func_t const add_tromino, void* const state) {
    if (order == 2) {
        add_tromino(px, py, fx, fy, state);
        return;
    }

    int const n = order >> 1;

    int const _px = px + (n * ((fx + 1) >> 1));
    int const _py = py + (n * ((fy + 1) >> 1));

    solve_tromino(
        n, _px - (fx * n), _py - (fy * n), fx, fy, add_tromino, state);

    solve_tromino(n, _px - (fx * n), _py, fx, fy * -1, add_tromino, state);

    solve_tromino(n, _px, _py - (fy * n), fx * -1, fy, add_tromino, state);

    int const o = n >> 1;
    solve_tromino(
        n, _px - (fx * o), _py - (fy * o), fx, fy, add_tromino, state);
}

static void solve_board(
    int const order, int const px, int const py, int const fx, int const fy,
    int const mx, int const my, trmn_add_tromino_func_t const add_tromino,
    void* const state) {
    if (order > 2) {
        int const n = order >> 1;

        int const _px = px + (n * ((fx + 1) >> 1));
        int const _py = py + (n * ((fy + 1) >> 1));

        int const o = n >> 1;
        int const x = mx - _px;
        int const y = my - _py;
        int const _fx = (x >= o) - (x < o);
        int const _fy = (y >= o) - (y < o);

        solve_board(n, _px, _py, _fx, _fy, mx, my, add_tromino, state);
    }

    solve_tromino(order, px, py, fx, fy, add_tromino, state);
}

void trmn_solve_puzzle(
    int const order, int const mx, int const my,
    trmn_add_tromino_func_t const add_tromino, void* const state) {
    assert(add_tromino);

    int const o = order >> 1;

    solve_board(
        order, 0, 0, (mx >= o) - (mx < o), (my >= o) - (my < o), mx, my,
        add_tromino, state);
}
