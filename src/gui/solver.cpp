// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "solver.h"

#include <chrono>
#include <thread>

void solver(
    int order, trmn_position_t mark, trmn_add_tromino_func add_tromino,
    void* state) noexcept {
    trmn_solve_puzzle(order, mark, add_tromino, state);
}
