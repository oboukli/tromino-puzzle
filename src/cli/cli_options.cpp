// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "cli_options.h"

#include "params.h"

namespace tromino::cli {

void print_usage(std::ostream& os) noexcept {
    // clang-format off
    os <<
        "Usage: tromino <order> <x> <y>\n"
        "\n"
        "Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.\n"
        << std::endl;
    // clang-format on
}

bool read_options(
    const int argc, const char* const argv[], options& options,
    std::string& error) noexcept {
    using namespace std::string_literals;
    using namespace tromino::cli::params;

    if (argc < REQUIRED_ARG_COUNT) {
        using namespace std::string_literals;
        error = "Incorrect argument count."s;

        return true;
    }

    options.order = std::stoi(argv[ORDER_ARG_IDX]);
    options.x = std::stoi(argv[MARKX_ARG_IDX]);
    options.y = std::stoi(argv[MARKY_ARG_IDX]);

    return false;
}

} // namespace tromino::cli
