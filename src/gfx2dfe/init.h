// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef init_h
#define init_h

#include <cstddef>

#include "tromino.h"

struct board_t {
    std::size_t size;
    int order;
    position_t mark;
};

int init(const board_t& board);

#endif /* init_h */
