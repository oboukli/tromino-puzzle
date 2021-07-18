/*
 * Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
 *
 * Distributed under an MIT-style license that can be
 * found in the LICENSE file.
 */

#include "tromino.h"

static void solve_tromino(int order, position pos, rotation rot, add_tromino_func add_tromino, void * state) {
    if (order == 2) {
        if (add_tromino != NULL) {
            (*add_tromino)(pos, rot, state);
        }

        return;
    }

    int n = order >> 1;
    int o = n >> 1;

    position p = {
        .x = rot.x == -1 ? pos.x : pos.x + n,
        .y = rot.y == -1 ? pos.y : pos.y + n,
    };

    solve_tromino(
        n,
        (position) {
            .x = p.x - (rot.x * o),
            .y = p.y - (rot.y * o),
        },
        rot,
        add_tromino,
        state);

    solve_tromino(
        n,
        (position) {
            .x = p.x - (rot.x * n),
            .y = p.y - (rot.y * n),
        },
        rot,
        add_tromino,
        state);

    solve_tromino(
        n,
        (position) {
            .x = p.x - (rot.x * n),
            .y = p.y,
        },
        (rotation) {
            .x = rot.x,
            .y = rot.y * -1,
        },
        add_tromino,
        state);

    solve_tromino(n,
        (position) {
            .x = p.x,
            .y = p.y - (rot.y * n),
        },
        (rotation) {
            .x = rot.x * -1,
            .y = rot.y,
        },
        add_tromino,
        state);
}

static void solve_board(int order, position pos, rotation rot, position mark, add_tromino_func add_tromino, void * state) {
    if (order > 2) {
        int s = order >> 1;
        position p = {
            .x = rot.x == -1 ? pos.x : pos.x + s,
            .y = rot.y == -1 ? pos.y : pos.y + s,
        };

        int ss = s >> 1;
        rotation r = {
            .x = (mark.x - p.x) < ss ? -1 : 1,
            .y = (mark.y - p.y) < ss ? -1 : 1,
        };

        solve_board(s, p, r, mark, add_tromino, state);
    }

    solve_tromino(order, pos, rot, add_tromino, state);
}

void solve_tromino_puzzle(int board_order, position mark, add_tromino_func add_tromino, void * state) {
    position pos = {
        .x = 0,
        .y = 0,
    };

    int s = board_order >> 1;

    rotation rot = {
        .x = mark.x < s ? -1 : 1,
        .y = mark.y < s ? -1 : 1,
    };

    solve_board(board_order, pos, rot, mark, add_tromino, state);
}
