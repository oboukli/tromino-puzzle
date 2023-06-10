// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef CLI_INIT_HPP
#define CLI_INIT_HPP

#include "cli_models.hpp"

namespace tromino::cli::app {

void init(int const order, int const x, int const y) noexcept;

#ifdef _WINDOWS
void init(
    int const order, int const x, int const y,
    emulation_mode_type const emulation_mode) noexcept;
#endif // _WINDOWS

} // namespace tromino::cli::app

#endif // CLI_INIT_HPP
