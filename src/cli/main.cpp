// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <iostream>
#include <string>

#include "cli_models.h"
#include "cli_options.h"
#include "init.h"

int main(const int argc, const char* const argv[]) {
    tromino::cli::options options;
    int read_options_result = tromino::cli::read_options(argc, argv, options);

    if (read_options_result != 0) {
        tromino::cli::print_usage();

        return EXIT_FAILURE;
    }

    tromino::cli::app::init(
        options.order, options.x, options.y, options.emulation_mode);

    return EXIT_SUCCESS;
}
