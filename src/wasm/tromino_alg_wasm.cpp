// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <emscripten.h>

#include <cassert>
#include <cstddef>

#include "tromino.h"

typedef void (*add_tromino_extern_callback)(
    const int pos_x, const int pos_y, const double angle) noexcept;

static void add_tromino(
    const int pos_x, const int pos_y, const int flip_x, const int flip_y,
    void* const state) noexcept {
    constexpr double pi = 3.14159265358979323846;
    constexpr double pi2 = 1.57079632679489661923;

    const add_tromino_extern_callback add_tromino_cb
        = reinterpret_cast<add_tromino_extern_callback>(state);
    double angle;

    assert(flip_x == -1 || flip_x == 1);
    assert(flip_y == -1 || flip_y == 1);

    switch (flip_x) {
    case -1:
        switch (flip_y) {
        case -1:
            // -1, -1
            // X |
            // - +

            angle = 0;
            break;

        case 1:
            [[fallthrough]];
        default:
            // -1, 1
            // - +
            // X |

            angle = 3 * pi2;
            break;
        };
        break;

    case 1:
        [[fallthrough]];
    default:
        switch (flip_y) {
        case -1:
            // 1, -1
            // | X
            // + -

            angle = pi2;
            break;

        case 1:
            [[fallthrough]];
        default:
            // 1, 1
            // + -
            // | X

            angle = pi;
            break;
        };
        break;
    };

    add_tromino_cb(pos_x, pos_y, angle);
}

EMSCRIPTEN_KEEPALIVE extern "C" void solve(
    const int order, const int mark_x, const int mark_y,
    add_tromino_extern_callback add_tromino_cb) noexcept {
    ::trmn_solve_puzzle(
        order, mark_x, mark_y, add_tromino,
        reinterpret_cast<void*>(add_tromino_cb));
}
