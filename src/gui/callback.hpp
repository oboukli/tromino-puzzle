// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef GUI_CALLBACK_HPP
#define GUI_CALLBACK_HPP

template <typename T>
using tromino_cb_t
    = auto (*)(int pos_x, int pos_y, int flip_x, int flip_y, T* state) noexcept
    -> void;

template <typename T>
struct SolverState final {
    T* state{};
    tromino_cb_t<T> callback{};
};

extern "C" void solve_puzzle_cb(
    int pos_x, int pos_y, int flip_x, int flip_y, void* state
) noexcept;

#endif // GUI_CALLBACK_HPP
