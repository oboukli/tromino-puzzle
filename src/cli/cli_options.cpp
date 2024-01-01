// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "cli_options.hpp"

#include <iostream>

#include "params.hpp"

namespace tromino::cli {

void print_usage(std::ostream& os) noexcept
{
    // clang-format off
    os <<
        "Usage: tromino <order> <x> <y>"
#ifdef _WIN64
        " [options]\n"
        "\n"
        "Options:\n"
        "  --use-wch    Use legacy Windows Console Host instead of VT-100 emulation\n"
        "\n"
#else
        "\n\n"
#endif // _WIN64
        "Copyright (c) 2021-2024 Omar Boukli-Hacene. All rights reserved.\n"
        << std::endl;
    // clang-format on
}

bool read_options(
    int const argc,
    char const* const argv[],
    options& options,
    std::string& error) noexcept
{
    using std::string_literals::operator""s;

    bool has_error{true};

    if (argc < params::REQUIRED_ARG_COUNT)
    {
        error = "Incorrect argument count."s;
    }
    else
    {
#ifdef _WIN64
        options.use_wch = argc > params::REQUIRED_ARG_COUNT
            && std::string(argv[params::USE_WCH_ARG_IDX]) == "--use-wch"s;

        // clang-format off
        options.emulation_mode = options.use_wch
            ? emulation_mode_type::wch
            : emulation_mode_type::vt100;
        // clang-format on
#endif // _WIN64

        options.order = std::stoi(argv[params::ORDER_ARG_IDX]);
        options.x = std::stoi(argv[params::MARKX_ARG_IDX]);
        options.y = std::stoi(argv[params::MARKY_ARG_IDX]);

        has_error = false;
    }

    return has_error;
}

} // namespace tromino::cli
