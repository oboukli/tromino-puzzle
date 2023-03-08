// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef GUI_CLI_OPTIONS_H
#define GUI_CLI_OPTIONS_H

#include "cli_models.h"

#include <iostream>
#include <string>

namespace tromino::tromino2d {

void print_usage(std::ostream& os) noexcept;

bool read_options(
    const int argc, const char* const argv[], options& options,
    std::string& error) noexcept;

} // namespace tromino::tromino2d

#endif // GUI_CLI_OPTIONS_H
