// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <span>
#include <string>

#include <tromino/gfx2d/board.hpp>
#include <tromino/validation/validation.h>

#include "cli_models.hpp"
#include "cli_options.hpp"
#include "init.hpp"
#include "params.hpp"

auto main(int const argc, char const* const* const argv) noexcept -> int
{
    int exit_status{EXIT_FAILURE};
    tromino::tromino2d::options options{};
    std::string error{};
    if (bool is_error{tromino::tromino2d::read_options(
            std::span<char const* const>(argv, static_cast<std::size_t>(argc)),
            options,
            error
        )};
        is_error
        or (not::trmn_is_valid_config(options.order, options.x, options.y)))
    {
        std::cerr << error << std::endl;
        tromino::tromino2d::print_usage(std::cout);

        exit_status = EXIT_FAILURE;
    }
    else
    {
        auto const order_internal{static_cast<std::size_t>(options.order)};
        std::size_t const size{order_internal * order_internal};
        tromino::gfx2d::Board const board{
            .size = size,
            .order = options.order,
            .mark_x = options.x,
            .mark_y = options.y
        };

        using std::string_literals::operator""s;
        exit_status = tromino::tromino2d::init(
            board, tromino::tromino2d::params::CANVAS_WIDTH, "Tromino Puzzle"s
        );
    }

    return exit_status;
}
