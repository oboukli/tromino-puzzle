// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef INIT_H_
#define INIT_H_

#include <cstddef>

#include "board.h"

int init(
    const tromino::gfx2d::board_t& board, int width,
    const char* title) noexcept;

#endif // INIT_H_
