// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>

#include "tromino_validation.h"

#include "board.hpp"

#include "cli_models.hpp"
#include "cli_options.hpp"
#include "init.hpp"
#include "params.hpp"

int main(int const argc, char const* const argv[]) noexcept {
    using namespace std::string_literals;

    tromino::tromino2d::options options{};
    std::string error{};
    if (bool is_error{
            tromino::tromino2d::read_options(argc, argv, options, error)};
        is_error
        || !::trmn_is_valid_config(options.order, options.x, options.y)) {
        std::cerr << error << std::endl;
        tromino::tromino2d::print_usage(std::cout);

        return EXIT_FAILURE;
    }

    auto const order_internal{static_cast<std::size_t>(options.order)};
    const std::size_t size{order_internal * order_internal};
    const tromino::gfx2d::Board board{
        .size = size,
        .order = options.order,
        .mark_x = options.x,
        .mark_y = options.y};

    return tromino::tromino2d::init(
        board, tromino::tromino2d::params::CANVAS_WIDTH, "Tromino Puzzle"s);
}
