
// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cassert>
#include <cstddef>

#include <emscripten.h>

#include "tromino.h"

typedef void (*add_tromino_extern_callback)(trmn_position_t abspos, double angle);

static void add_tromino(trmn_position_t abspos, trmn_flip_t flip, void * state) {
    const double pi = 3.14159265358979323846;
    const double pi2 = 1.57079632679489661923;

    add_tromino_extern_callback add_tromino_cb = (add_tromino_extern_callback)state;
        double angle;

        assert(flip.x == -1 || flip.x == 1);
        assert(flip.y == -1 || flip.y == 1);

        switch (flip.x) {
        case -1:
            switch (flip.y) {
            case -1:
                // -1, -1
                // X |
                // - +

                angle = 3 * pi2;
                break;

            case 1:
            default:
                // -1, 1
                // - +
                // X |

                angle = pi;
                break;
            };
            break;

        case 1:
        default:
            switch (flip.y) {
            case -1:
                // 1, -1
                // | X
                // + -

                angle = 0;
                break;

            case 1:
            default:
                // 1, 1
                // + -
                // | X

                angle = pi2;
                break;
            };
            break;
        };

    add_tromino_cb(abspos, angle);
}

EMSCRIPTEN_KEEPALIVE extern "C" void solve(int order, trmn_position_t mark, add_tromino_extern_callback add_tromino_cb) {
    trmn_solve_puzzle(order, mark, add_tromino, reinterpret_cast<void *>(add_tromino_cb));
}
