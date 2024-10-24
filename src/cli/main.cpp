// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <iostream>
#include <string>

#include <tromino/validation/validation.h>

#include "cli_models.hpp"
#include "cli_options.hpp"
#include "init.hpp"

int main(int const argc, char const* const argv[]) noexcept
{
    int exit_status{EXIT_FAILURE};
    tromino::cli::options options{};

    std::string error;
    if (bool const is_error{
            tromino::cli::read_options(argc, argv, options, error)
        };
        is_error
        || (!::trmn_is_valid_config(options.order, options.x, options.y)))
    {
        std::cerr << error << std::endl;
        tromino::cli::print_usage(std::cout);
    }
    else
    {
#ifdef _WIN64
        tromino::cli::app::init(
            options.order, options.x, options.y, options.emulation_mode
        );
#else
        tromino::cli::app::init(options.order, options.x, options.y);
#endif // _WIN64

        exit_status = EXIT_SUCCESS;
    }

    return exit_status;
}
