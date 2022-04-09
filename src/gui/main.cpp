// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>

#include "tromino_validation.h"

#include "cli_models.h"
#include "cli_options.h"
#include "init.h"
#include "params.h"

int main(const int argc, const char* const argv[]) {
    using namespace std::string_literals;

    tromino::tromino2d::options options;
    std::string error;
    if (bool is_error
        = tromino::tromino2d::read_options(argc, argv, options, error);
        is_error
        || !::trmn_is_valid_config(options.order, options.x, options.y)) {
        std::cerr << error << std::endl;
        tromino::tromino2d::print_usage();

        return EXIT_FAILURE;
    }

    const std::size_t order_internal = static_cast<std::size_t>(options.order);
    const std::size_t size = order_internal * order_internal;
    const tromino::gfx2d::Board board{
        .mark_x = options.x,
        .mark_y = options.y,
        .size = size,
        .order = options.order};

    return tromino::tromino2d::init(
        board, tromino::tromino2d::params::CANVAS_WIDTH, "Tromino Puzzle"s);
}
