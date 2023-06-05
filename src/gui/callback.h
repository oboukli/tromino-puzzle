// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef GUI_CALLBACK_H
#define GUI_CALLBACK_H

template <typename T>
using tromino_cb_t = void (*)(
    int const pos_x, int const pos_y, int const flip_x, int const flip_y,
    T* const state) noexcept;

template <typename T> struct SolverState final {
    T* state{};
    tromino_cb_t<T> callback{};
};

extern "C" void solve_puzzle_cb(
    int const pos_x, int const pos_y, int const flip_x, int const flip_y,
    void* const state) noexcept;

#endif // GUI_CALLBACK_H
