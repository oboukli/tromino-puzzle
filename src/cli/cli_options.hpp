// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef CLI_CLI_OPTIONS_HPP_
#define CLI_CLI_OPTIONS_HPP_

#include "cli_models.hpp"

#include <iostream>
#include <string>

namespace tromino::cli {

void print_usage(std::ostream& os);

bool read_options(
    int argc, char const* const* argv, options& options, std::string& error
);

} // namespace tromino::cli

#endif // CLI_CLI_OPTIONS_HPP_
