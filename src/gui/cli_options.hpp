// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef GUI_CLI_OPTIONS_HPP
#define GUI_CLI_OPTIONS_HPP

#include "cli_models.hpp"

#include <iostream>
#include <span>
#include <string>

namespace tromino::tromino2d {

void print_usage(std::ostream& os) noexcept;

bool read_options(
    std::span<char const* const> args, options& options, std::string& error
) noexcept;

} // namespace tromino::tromino2d

#endif // GUI_CLI_OPTIONS_HPP
