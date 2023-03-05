// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef INIT_H
#define INIT_H

#include "cli_models.h"

namespace tromino::cli::app {

void init(const int size, const int x, const int y) noexcept;

#ifdef _WINDOWS
void init(
    const int size, const int x, const int y,
    const emulation_mode_type emulation_mode) noexcept;
#endif // _WINDOWS

} // namespace tromino::cli::app

#endif // INIT_H
