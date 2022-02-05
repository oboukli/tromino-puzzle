// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "cli_options.h"

#include <iostream>

namespace tromino::tromino2d {

void print_usage() noexcept {
    // clang-format off
    std::cout
        << "Usage: tromino2d <order> <x> <y>\n"
        << "Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.\n"
        << std::endl;
    // clang-format on
}

bool read_options(
    const int argc, const char* const argv[], options& options,
    std::string& error) noexcept {
    constexpr int REQUIRED_ARG_COUNT = 4;

    if (argc < REQUIRED_ARG_COUNT) {
        using namespace std::string_literals;
        error = "Incorrect argument count."s;
        return true;
    }

    options.order = std::stoi(argv[1]);
    options.x = std::stoi(argv[2]);
    options.y = std::stoi(argv[3]);

    return false;
}

} // namespace tromino::tromino2d
