// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "init.hpp"

#include <cstddef>
#include <iostream>
#include <memory>

#include "trmn_graph.hpp"
#include "trmn_graph_vt.hpp"

namespace tromino::cli::app {

void init(int const order, int const x, int const y) noexcept
{
    auto const order_internal{static_cast<std::size_t>(order)};
    std::size_t const size{order_internal * order_internal};

    board_t tromino_board{
        .board_matrix = std::make_unique<char[]>(size),
        .size = size,
        .order = order,
        .mark_x = x,
        .mark_y = y};

    tromino::cli::vt::use_vt(tromino_board, std::cout);
}

} // namespace tromino::cli::app
