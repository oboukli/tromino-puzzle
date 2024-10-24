// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef WASM_TRMN_TRMN_HPP
#define WASM_TRMN_TRMN_HPP

#include <emscripten.h>

EMSCRIPTEN_KEEPALIVE extern "C" void playTromino(
    int const order, int const markX, int const markY, int const width
) noexcept;

#endif // WASM_TRMN_TRMN_HPP
