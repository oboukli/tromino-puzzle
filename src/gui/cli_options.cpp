// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "cli_options.hpp"

#include <algorithm>
#include <charconv>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <ostream>
#include <span>
#include <string>

#include "cli_models.hpp"
#include "params.hpp"

namespace tromino::tromino2d {

namespace {

int parse_int(char const* const first)
{
    int const offset{*first == '-' ? 1 : 0};
    char const* const last{std::find(
        first, first + (std::numeric_limits<int>::digits10 + offset), '\0'
    )};

    int val{0};
    std::from_chars(first, last, val);

    return val;
}

} // namespace

void print_usage(std::ostream& os)
{
    // clang-format off
    os <<
        "Usage: tromino2d <order> <x> <y> [options]\n"
        "\n"
        "Options:\n"
        "  -f    Force large puzzle (unstable)\n"
        "\n"
        "Copyright (c) 2021-2025 Omar Boukli-Hacene. All rights reserved.\n"
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
        options.order = parse_int(args[params::ORDER_ARG_IDX]);
        options.x = parse_int(args[params::MARKX_ARG_IDX]);
        options.y = parse_int(args[params::MARKY_ARG_IDX]);

        options.force = (args.size() > params::REQUIRED_ARG_COUNT)
            && (std::strncmp(
                    "-f",
                    args[params::FORCE_ARG_IDX],
                    params::FORCE_OPTION_STR_SIZE
                )
                == 0);

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
