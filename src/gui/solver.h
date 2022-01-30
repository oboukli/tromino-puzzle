// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef SOLVER_H_
#define SOLVER_H_

#include "tromino.h"

namespace tromino::tromino2d {

void solver(
    const int order, const trmn_position_t mark,
    const trmn_add_tromino_func add_tromino, void* const state) noexcept;

} // namespace tromino::tromino2d

#endif // SOLVER_H_
