// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "callback.hpp"

class SharedState;

extern "C" void solve_puzzle_cb(
    int const pos_x, int const pos_y, int const flip_x, int const flip_y,
    void* const state) noexcept {
    SolverState<SharedState>* const solver_state{
        static_cast<SolverState<SharedState>*>(state)};

    solver_state->callback(pos_x, pos_y, flip_x, flip_y, solver_state->state);
}
