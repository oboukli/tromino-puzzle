// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef CLI_OPTIONS_HPP
#define CLI_OPTIONS_HPP

#include "cli_models.hpp"

#include <iostream>
#include <string>

namespace tromino::cli {

void print_usage(std::ostream& os) noexcept;

bool read_options(
    int argc, char const* const argv[], options& options, std::string& error
) noexcept;

} // namespace tromino::cli

#endif // CLI_OPTIONS_HPP
