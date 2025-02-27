// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "cli_options.hpp"

#include <charconv>
#include <cstdlib>
#include <limits>
#include <ostream>
#include <string>

#ifdef _WIN64
#include <cstring>
#endif // _WIN64

#include "cli_models.hpp"
#include "params.hpp"

namespace tromino::cli {

namespace {

/*constexpr*/ int parse_positive_int(char const* const first) noexcept
{
    int val{0};
    if ((first != nullptr) && (*first != '-'))
    {
        std::from_chars(first, first + std::numeric_limits<int>::digits10, val);
    }

    return val;
}

} // namespace

void print_usage(std::ostream& os)
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
        "Copyright (c) 2021-2025 Omar Boukli-Hacene. All rights reserved.\n"
        << std::endl;
    // clang-format on
}

bool read_options(
    int const argc,
    char const* const* const argv,
    options& options,
    std::string& error
)
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
        options.use_wch = (argc > params::REQUIRED_ARG_COUNT)
            && (std::strncmp(
                    params::USE_WCH_OPTION,
                    argv[params::USE_WCH_ARG_IDX],
                    sizeof *params::USE_WCH_OPTION
                )
                == 0);

        // clang-format off
        options.emulation_mode = options.use_wch
            ? emulation_mode_type::wch
            : emulation_mode_type::vt100;
        // clang-format on
#endif // _WIN64

        options.order = parse_positive_int(argv[params::ORDER_ARG_IDX]);
        options.x = parse_positive_int(argv[params::MARKX_ARG_IDX]);
        options.y = parse_positive_int(argv[params::MARKY_ARG_IDX]);

        has_error = false;
    }

    return has_error;
}

} // namespace tromino::cli
