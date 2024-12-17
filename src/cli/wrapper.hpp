// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef CLI_WRAPPER_HPP_
#define CLI_WRAPPER_HPP_

extern "C" void solve_puzzle_cb(
    int pos_x, int pos_y, int flip_x, int flip_y, void* state
) noexcept;

#endif // CLI_WRAPPER_HPP_
