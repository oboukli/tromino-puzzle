/*
Copyright (c) Omar Boukli-Hacene. All rights reserved.
Distributed under an MIT-style license that can be
found in the LICENSE file.
*/

/* SPDX-License-Identifier: MIT */

#ifndef WASM_LITRO_LITRO_H
#define WASM_LITRO_LITRO_H

#include <emscripten.h>

typedef void (*add_tromino_extern_callback)(
    int pos_x, int pos_y, int flip_x, int flip_y
);

EMSCRIPTEN_KEEPALIVE void solve(
    int order,
    int mark_x,
    int mark_y,
    add_tromino_extern_callback add_tromino_cb
);

#endif /* WASM_LITRO_LITRO_H */
