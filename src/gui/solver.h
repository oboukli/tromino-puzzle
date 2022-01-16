// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef SOLVER_H_
#define SOLVER_H_

#include "tromino.h"

void solver(
    int order, trmn_position_t mark, trmn_add_tromino_func add_tromino,
    void* state) noexcept;

#endif // SOLVER_H_
