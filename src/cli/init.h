// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef CLI_INIT_H
#define CLI_INIT_H

#include "cli_models.h"

namespace tromino::cli::app {

void init(int const size, int const x, int const y) noexcept;

#ifdef _WINDOWS
void init(
    int const size, int const x, int const y,
    const emulation_mode_type emulation_mode) noexcept;
#endif // _WINDOWS

} // namespace tromino::cli::app

#endif // CLI_INIT_H
