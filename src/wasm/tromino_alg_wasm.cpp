// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <emscripten.h>

#include <cassert>
#include <cstddef>

#include "tromino.h"

typedef void (*add_tromino_extern_callback)(
    const trmn_position_t pos, const double angle) noexcept;

static void add_tromino(
    const trmn_position_t pos, const trmn_flip_t flip,
    void* const state) noexcept {
    constexpr double pi = 3.14159265358979323846;
    constexpr double pi2 = 1.57079632679489661923;

    const add_tromino_extern_callback add_tromino_cb
        = reinterpret_cast<add_tromino_extern_callback>(state);
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
            [[fallthrough]];
        default:
            // -1, 1
            // - +
            // X |

            angle = pi;
            break;
        };
        break;

    case 1:
        [[fallthrough]];
    default:
        switch (flip.y) {
        case -1:
            // 1, -1
            // | X
            // + -

            angle = 0;
            break;

        case 1:
            [[fallthrough]];
        default:
            // 1, 1
            // + -
            // | X

            angle = pi2;
            break;
        };
        break;
    };

    add_tromino_cb(pos, angle);
}

EMSCRIPTEN_KEEPALIVE extern "C" void solve(
    const int order, const trmn_position_t mark,
    add_tromino_extern_callback add_tromino_cb) noexcept {
    ::trmn_solve_puzzle(
        order, mark, add_tromino, reinterpret_cast<void*>(add_tromino_cb));
}
