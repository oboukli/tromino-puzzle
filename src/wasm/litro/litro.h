// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef LITRO_H
#define LITRO_H

#include <emscripten.h>

typedef void (*add_tromino_extern_callback)(
    const int pos_x, const int pos_y, const int flip_x, const int flip_y);

EMSCRIPTEN_KEEPALIVE void solve(
    const int order, const int mark_x, const int mark_y,
    add_tromino_extern_callback add_tromino_cb);

#endif // LITRO_H
