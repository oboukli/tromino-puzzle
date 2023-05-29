// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef GUI_INIT_H
#define GUI_INIT_H

#include <string>

#include "board.h"

namespace tromino::tromino2d {

int init(
    tromino::gfx2d::Board const& board, int const width,
    std::string const& title) noexcept;

} // namespace tromino::tromino2d

#endif // GUI_INIT_H
