/*
 * Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
 *
 * Distributed under an MIT-style license that can be
 * found in the LICENSE file.
 */

#include <assert.h>
#include <math.h>

#include <emscripten.h>

#include "tromino.h"

typedef void (*add_tromino_extern_callback)(position_t abspos, double angle);

static void add_tromino(position_t abspos, rotation_t rot, void * state) {
    add_tromino_extern_callback add_tromino_cb = (add_tromino_extern_callback)state;
        double angle;

        assert(rot.x == -1 || rot.x == 1);
        assert(rot.y == -1 || rot.y == 1);

        switch (rot.x) {
        case -1:
            switch (rot.y) {
            case -1:
                // -1, -1
                // X |
                // - +

                angle = 3 * M_PI_2;
                break;

            case 1:
                // -1, 1
                // - +
                // X |

                angle = M_PI;
                break;
            };
            break;

        case 1:
            switch (rot.y) {
            case -1:
                // 1, -1
                // | X
                // + -

                angle = 0;
                break;

            case 1:
                // 1, 1
                // + -
                // | X

                angle = M_PI_2;
                break;
            };
            break;
        };

    add_tromino_cb(abspos, angle);
}

EMSCRIPTEN_KEEPALIVE void solve(int order, position_t mark, add_tromino_extern_callback add_tromino_cb) {
    solve_tromino_puzzle(order, mark, add_tromino, add_tromino_cb);
}
