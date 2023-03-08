// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef GUI_SOLVER_H
#define GUI_SOLVER_H

#include "tromino.h"

#include "step.h"

namespace tromino::tromino2d {

template <typename T>
using add_tromino_func = void (*)(
    const int pos_x, const int pos_y, const int flip_x, const int flip_y,
    T* const state) noexcept;

template <typename T>
void solver(
    const int order, const int mark_x, const int mark_y,
    const add_tromino_func<T> add_tromino, T* const state) noexcept {
    ::trmn_solve_puzzle(
        order, mark_x, mark_y,
        reinterpret_cast<trmn_add_tromino_func>(add_tromino), state);
}

} // namespace tromino::tromino2d

#endif // GUI_SOLVER_H
