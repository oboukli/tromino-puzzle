// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <iostream>
#include <string>

#include "tromino_validation.h"

#include "cli_models.h"
#include "cli_options.h"
#include "init.h"

int main(const int argc, const char* const argv[]) {
    tromino::cli::options options;

    std::string error;
    if (const bool is_error
        = tromino::cli::read_options(argc, argv, options, error);
        is_error
        || !::trmn_is_valid_config(options.order, options.x, options.y)) {
        std::cerr << error << std::endl;
        tromino::cli::print_usage(std::cout);

        return EXIT_FAILURE;
    }

#ifdef _WINDOWS
    tromino::cli::app::init(
        options.order, options.x, options.y, options.emulation_mode);
#else
    tromino::cli::app::init(options.order, options.x, options.y);
#endif // _WINDOWS

    return EXIT_SUCCESS;
}
