// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef SOLVER_H
#define SOLVER_H

#include "tromino.h"

void solver(int order, trmn_position_t mark, trmn_add_tromino_func add_tromino, void * state);

#endif // SOLVER_H
