// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef CLI_TRMN_GRAPH_WINDOWS_HPP
#define CLI_TRMN_GRAPH_WINDOWS_HPP

#ifndef _WIN64
#error "Included Windows-only header"
#endif // ndef _WIN64

#include <iostream>

#include "trmn_graph.hpp"

namespace tromino::cli::windows {

void use_wch(board_t& tromino_board, std::ostream& os) noexcept;

} // namespace tromino::cli::windows

#endif // CLI_TRMN_GRAPH_WINDOWS_HPP
