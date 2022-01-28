// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "solver.h"

#include <chrono>
#include <thread>

void solver(
    const int order, const trmn_position_t mark,
    const trmn_add_tromino_func add_tromino, void* const state) noexcept {
    trmn_solve_puzzle(order, mark, add_tromino, state);
}
