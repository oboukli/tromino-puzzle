// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "cli_options.h"

#include <iostream>
#include <string>

namespace tromino::cli {

void print_usage() noexcept {
    // clang-format off
    std::cout
        << "Usage: tromino <order> <x> <y>\n"
#ifdef _WINDOWS
        << " [options]\n"
        << "  --use-wch    Use legacy Windows Console Host instead of VT-100 emulation\n"
#endif // _WINDOWS
        << "Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.\n"
        << std::endl;
    // clang-format on
}

int read_options(
    const int argc, const char* const argv[], options& options) noexcept {
    using namespace std::string_literals;

    constexpr int REQUIRED_ARG_COUNT = 4;

    if (argc < REQUIRED_ARG_COUNT) {
        return 1;
    }

#ifdef _WINDOWS
    options.use_wch
        = argc > REQUIRED_ARG_COUNT && std::string(argv[4]) == "--use-wch"s;

    // clang-format off
    options.emulation_mode =
        options.use_wch ? emulation_mode_type::wch: emulation_mode_type::vt100;
    // clang-format on
#else
    options.emulation_mode = emulation_mode_type::vt100;
#endif // _WINDOWS

    options.order = std::stoi(argv[1]);
    options.x = std::stoi(argv[2]);
    options.y = std::stoi(argv[3]);

    return 0;
}

} // namespace tromino::cli
