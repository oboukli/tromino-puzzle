// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef INIT_H
#define INIT_H

#include <string>

#include "board.h"

namespace tromino::tromino2d {

int init(
    const tromino::gfx2d::Board& board, const int width,
    const std::string& title) noexcept;

} // namespace tromino::tromino2d

#endif // INIT_H
