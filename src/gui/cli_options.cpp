// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "cli_options.hpp"

#include <ostream>
#include <span>
#include <string>

#include "cli_models.hpp"
#include "params.hpp"

namespace tromino::tromino2d {

void print_usage(std::ostream& os)
{
    // clang-format off
    os <<
        "Usage: tromino2d <order> <x> <y> [options]\n"
        "\n"
        "Options:\n"
        "  -f    Force large puzzle (unstable)\n"
        "\n"
        "Copyright (c) 2021-2024 Omar Boukli-Hacene. All rights reserved.\n"
        << std::endl;
    // clang-format on
}

bool read_options(
    std::span<char const* const> const args,
    options& options,
    std::string& error
)
{
    using std::string_literals::operator""s;

    bool has_error{true};
    if (args.size() < params::REQUIRED_ARG_COUNT)
    {
        error = "Incorrect argument count."s;

        has_error = true;
    }
    else
    {
        options.order = std::stoi(args[params::ORDER_ARG_IDX]);
        options.x = std::stoi(args[params::MARKX_ARG_IDX]);
        options.y = std::stoi(args[params::MARKY_ARG_IDX]);
        options.force = (args.size() > params::REQUIRED_ARG_COUNT)
            && (std::string(args[params::FORCE_ARG_IDX]) == "-f"s);

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
