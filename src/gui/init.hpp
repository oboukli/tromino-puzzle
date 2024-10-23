// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef GUI_INIT_HPP
#define GUI_INIT_HPP

#include <optional>
#include <string>

#include <tromino/gfx2d/board.hpp>

namespace tromino::tromino2d {

int init(
    tromino::gfx2d::Board const& board,
    int width,
    std::optional<std::string const> const& title
) noexcept;

} // namespace tromino::tromino2d

#endif // GUI_INIT_HPP
