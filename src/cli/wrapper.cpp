// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "wrapper.hpp"

#include <tromino/wrapper/callback.hpp>

#include "trmn_graph.hpp"

extern "C" void solve_puzzle_cb(
    int const pos_x,
    int const pos_y,
    int const flip_x,
    int const flip_y,
    void* const state
) noexcept
{
    using T = solver_state_wrapper_t<tromino::cli::graph_state_t>;

    static_assert(alignof(T*) == alignof(void*));
    static_assert(std::is_standard_layout_v<T>);

    T* const solver_state{static_cast<T*>(state)};

    solver_state->callback(pos_x, pos_y, flip_x, flip_y, solver_state->state);
}
