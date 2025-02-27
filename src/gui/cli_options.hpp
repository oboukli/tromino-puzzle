// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef GUI_CLI_OPTIONS_HPP_
#define GUI_CLI_OPTIONS_HPP_

#include "cli_models.hpp"

#include <iostream>
#include <span>
#include <string>

namespace tromino::tromino2d {

void print_usage(std::ostream& os);

bool read_options(
    std::span<char const* const> args, options& options, std::string& error
);

} // namespace tromino::tromino2d

#endif // GUI_CLI_OPTIONS_HPP_
