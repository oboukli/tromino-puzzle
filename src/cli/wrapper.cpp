// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "wrapper.hpp"

#include "trmn_graph.hpp"

extern "C" void solve_puzzle_cb(
    int const pos_x,
    int const pos_y,
    int const flip_x,
    int const flip_y,
    void* const state
) noexcept
{
    auto* const solver_state{
        static_cast<SolverState<tromino::cli::graph_state_t>*>(state)
    };

    solver_state->callback(pos_x, pos_y, flip_x, flip_y, solver_state->state);
}
