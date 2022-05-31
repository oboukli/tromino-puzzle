// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef CLI_OPTIONS_H_
#define CLI_OPTIONS_H_

#include "cli_models.h"

#include <iostream>
#include <string>

namespace tromino::cli {

void print_usage(std::ostream& os) noexcept;

bool read_options(
    const int argc, const char* const argv[], options& options,
    std::string& error) noexcept;

} // namespace tromino::cli

#endif // CLI_OPTIONS_H_
