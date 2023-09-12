// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "cli_options.hpp"

#include "params.hpp"

namespace tromino::tromino2d {

void print_usage(std::ostream& os) noexcept
{
    // clang-format off
    os <<
        "Usage: tromino2d <order> <x> <y> [options]\n"
        "\n"
        "Options:\n"
        "  -f    Force large puzzle (unstable)\n"
        "\n"
        "Copyright (c) 2021-2023 Omar Boukli-Hacene. All rights reserved.\n"
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

        has_error = true;
    }
    else
    {
        options.order = std::stoi(argv[params::ORDER_ARG_IDX]);
        options.x = std::stoi(argv[params::MARKX_ARG_IDX]);
        options.y = std::stoi(argv[params::MARKY_ARG_IDX]);
        options.force = (argc > params::REQUIRED_ARG_COUNT)
            && (std::string(argv[params::FORCE_ARG_IDX]) == "-f"s);

        if ((options.order > params::MAX_SUPPORTED_ORDER) && (!options.force))
        {
            error
                = "Order is too large that it might crash the app. Use the -f option to force the puzzle."s;

            has_error = true;
        }
        else
        {
            has_error = false;
        }
    }

    return has_error;
}

} // namespace tromino::tromino2d
