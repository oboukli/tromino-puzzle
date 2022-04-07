// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "cli_options.h"

#include <iostream>

#include "params.h"

namespace tromino::tromino2d {

void print_usage() noexcept {
    // clang-format off
    std::cout <<
        "Usage: tromino2d <order> <x> <y> [options]\n"
        "\n"
        "Options:\n"
        "  -f    Force large puzzle (unstable)\n"
        "\n"
        "Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.\n"
        << std::endl;
    // clang-format on
}

bool read_options(
    const int argc, const char* const argv[], options& options,
    std::string& error) noexcept {
    using namespace std::string_literals;
    using namespace tromino::tromino2d::params;

    if (argc < REQUIRED_ARG_COUNT) {
        error = "Incorrect argument count."s;

        return true;
    }

    options.order = std::stoi(argv[ORDER_ARG_IDX]);
    options.x = std::stoi(argv[MARKX_ARG_IDX]);
    options.y = std::stoi(argv[MARKY_ARG_IDX]);
    options.force
            = argc > REQUIRED_ARG_COUNT && std::string(argv[FORCE_ARG_IDX]) == "-f"s;

    if (options.order > MAX_SUPPORTED_ORDER && !options.force) {
        error = "Order is too large that it might crash the app. Use the  -f option to force the puzzle."s;

        return true;
    }

    return false;
}

} // namespace tromino::tromino2d
