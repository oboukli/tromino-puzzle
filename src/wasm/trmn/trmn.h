// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef WASM_TRMN_TRMN_H
#define WASM_TRMN_TRMN_H

#include <emscripten.h>

EMSCRIPTEN_KEEPALIVE extern "C" void playTromino(
    const int order, const int markX, const int markY,
    const int width) noexcept;

#endif // WASM_TRMN_TRMN_H
