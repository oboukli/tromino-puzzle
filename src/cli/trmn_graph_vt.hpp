// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef CLI_TRMN_GRAPH_VT_HPP
#define CLI_TRMN_GRAPH_VT_HPP

#include <iostream>

#include "trmn_graph.hpp"

namespace tromino::cli::vt {

void add_tromino(
    int const pos_x,
    int const pos_y,
    int const flip_x,
    int const flip_y,
    graph_state_t* const graph_state) noexcept;

void use_vt(board_t& tromino_board, std::ostream& os) noexcept;

} // namespace tromino::cli::vt

#endif // CLI_TRMN_GRAPH_VT_HPP
