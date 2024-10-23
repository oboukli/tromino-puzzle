// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef CLI_WRAPPER_HPP
#define CLI_WRAPPER_HPP

template <typename T>
using tromino_cb_t
    = void (*)(int pos_x, int pos_y, int flip_x, int flip_y, T* state) noexcept;

template <typename T>
struct SolverState final {
    T* state{};
    tromino_cb_t<T> callback{};
};

extern "C" void solve_puzzle_cb(
    int pos_x, int pos_y, int flip_x, int flip_y, void* state
) noexcept;

#endif // CLI_WRAPPER_HPP
