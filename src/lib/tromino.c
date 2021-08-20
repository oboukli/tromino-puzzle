/*
 * Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
 *
 * Distributed under an MIT-style license that can be
 * found in the LICENSE file.
 */

#include <assert.h>

#include "tromino.h"

static void solve_tromino(int order, position_t pos, flip_t flip, add_tromino_func add_tromino, void * state) {
    if (order == 2) {
        add_tromino(pos, flip, state);

        return;
    }

    int n = order >> 1;
    int o = n >> 1;

    position_t p = {
        .x = flip.x == -1 ? pos.x : pos.x + n,
        .y = flip.y == -1 ? pos.y : pos.y + n,
    };

    solve_tromino(
        n,
        (position_t) {
            .x = p.x - (flip.x * o),
            .y = p.y - (flip.y * o),
        },
        flip,
        add_tromino,
        state);

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
}

static void solve_board(int order, position_t pos, flip_t flip, position_t mark, add_tromino_func add_tromino, void * state) {
    if (order > 2) {
        int s = order >> 1;
        position_t p = {
            .x = flip.x == -1 ? pos.x : pos.x + s,
            .y = flip.y == -1 ? pos.y : pos.y + s,
        };

        int ss = s >> 1;
        flip_t r = {
            .x = (mark.x - p.x) < ss ? -1 : 1,
            .y = (mark.y - p.y) < ss ? -1 : 1,
        };

        solve_board(s, p, r, mark, add_tromino, state);
    }

    solve_tromino(order, pos, flip, add_tromino, state);
}

void solve_tromino_puzzle(int board_order, position_t mark, add_tromino_func add_tromino, void * state) {
    assert(add_tromino);

    position_t pos = {
        .x = 0,
        .y = 0,
    };

    int s = board_order >> 1;

    flip_t flip = {
        .x = mark.x < s ? -1 : 1,
        .y = mark.y < s ? -1 : 1,
    };

    solve_board(board_order, pos, flip, mark, add_tromino, state);
}
