// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef WASM_TRMN_TRMN_HPP_
#define WASM_TRMN_TRMN_HPP_

#include <emscripten.h>

EMSCRIPTEN_KEEPALIVE extern "C" void
playTromino(int order, int markX, int markY, int width);

#endif // WASM_TRMN_TRMN_HPP_
