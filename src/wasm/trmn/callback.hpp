// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef WASM_TRMN_CALLBACK_HPP_
#define WASM_TRMN_CALLBACK_HPP_

extern "C" void
add_tromino(int pos_x, int pos_y, int flip_x, int flip_y, void* state) noexcept;

#endif // WASM_TRMN_CALLBACK_HPP_
