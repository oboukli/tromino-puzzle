// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "callback.hpp"

#include <type_traits>

#include "solver_state.hpp"

extern "C" void tromino_solve_puzzle_cb(
    int const pos_x,
    int const pos_y,
    int const flip_x,
    int const flip_y,
    void* const state
) noexcept
{
    using T = solver_state_wrapper_t<tromino::tromino2d::SolverState>;

    static_assert(alignof(T*) == alignof(void*));
    static_assert(std::is_standard_layout_v<T>);

    T* const solver_state_wrapper{static_cast<T*>(state)};

    solver_state_wrapper->callback(
        pos_x, pos_y, flip_x, flip_y, solver_state_wrapper->state
    );
}
