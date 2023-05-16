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
    const int order, const int px, const int py, const int fx, const int fy,
    const trmn_add_tromino_func_t add_tromino, void* const state) {
    if (order == 2) {
        add_tromino(px, py, fx, fy, state);
        return;
    }

    const int n = order >> 1;

    const int _px = px + (n * ((fx + 1) >> 1));
    const int _py = py + (n * ((fy + 1) >> 1));

    solve_tromino(
        n, _px - (fx * n), _py - (fy * n), fx, fy, add_tromino, state);

    solve_tromino(n, _px - (fx * n), _py, fx, fy * -1, add_tromino, state);

    solve_tromino(n, _px, _py - (fy * n), fx * -1, fy, add_tromino, state);

    const int o = n >> 1;
    solve_tromino(
        n, _px - (fx * o), _py - (fy * o), fx, fy, add_tromino, state);
}

static void solve_board(
    const int order, const int px, const int py, const int fx, const int fy,
    const int mx, const int my, const trmn_add_tromino_func_t add_tromino,
    void* const state) {
    if (order > 2) {
        const int n = order >> 1;

        const int _px = px + (n * ((fx + 1) >> 1));
        const int _py = py + (n * ((fy + 1) >> 1));

        const int o = n >> 1;
        const int x = mx - _px;
        const int y = my - _py;
        const int _fx = (int)(x >= o) - (int)(x < o);
        const int _fy = (int)(y >= o) - (int)(y < o);

        solve_board(n, _px, _py, _fx, _fy, mx, my, add_tromino, state);
    }

    solve_tromino(order, px, py, fx, fy, add_tromino, state);
}

void trmn_solve_puzzle(
    const int order, const int mx, const int my,
    const trmn_add_tromino_func_t add_tromino, void* const state) {
    assert(add_tromino);

    const int o = order >> 1;

    solve_board(
        order, 0, 0, (int)(mx >= o) - (int)(mx < o),
        (int)(my >= o) - (int)(my < o), mx, my, add_tromino, state);
}
