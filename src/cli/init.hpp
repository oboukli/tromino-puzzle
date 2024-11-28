// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef CLI_INIT_HPP_
#define CLI_INIT_HPP_

#include "cli_models.hpp"

namespace tromino::cli::app {

void init(int order, int x, int y);

#ifdef _WIN64
void init(int order, int x, int y, emulation_mode_type emulation_mode);
#endif // _WIN64

} // namespace tromino::cli::app

#endif // CLI_INIT_HPP_
