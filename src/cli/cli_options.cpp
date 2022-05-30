// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "cli_options.h"

#include <iostream>

#include "params.h"

namespace tromino::cli {

void print_usage() noexcept {
    // clang-format off
    std::cout <<
        "Usage: tromino <order> <x> <y>"
#ifdef _WINDOWS
        " [options]\n"
        "\n"
        "Options:\n"
        "  --use-wch    Use legacy Windows Console Host instead of VT-100 emulation\n"
        "\n"
#else
        "\n\n"
#endif // _WINDOWS
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

#ifdef _WINDOWS
    options.use_wch = argc > REQUIRED_ARG_COUNT
        && std::string(argv[USE_WCH_ARG_IDX]) == "--use-wch"s;

    // clang-format off
    options.emulation_mode =
        options.use_wch ? emulation_mode_type::wch: emulation_mode_type::vt100;
    // clang-format on
#endif // _WINDOWS

    options.order = std::stoi(argv[ORDER_ARG_IDX]);
    options.x = std::stoi(argv[MARKX_ARG_IDX]);
    options.y = std::stoi(argv[MARKY_ARG_IDX]);

    return false;
}

} // namespace tromino::cli
