// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <iostream>
#include <string>

#include "tromino_validation.h"

#include "cli_models.h"
#include "cli_options.h"

// #include "trmn_graph.h"
#include "trmn_graph_windows.h"

namespace {

void init(const int order, const int x, const int y) noexcept {
    const auto order_internal = static_cast<std::size_t>(order);
    const std::size_t size = order_internal * order_internal;

    board_t tromino_board{
        .board_matrix = std::make_unique<char[]>(size),
        .size = size,
        .order = order,
        .mark_x = x,
        .mark_y = y};

    tromino::cli::windows::use_wch(tromino_board, std::cout);
}

} // namespace

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

    tromino::cli::app::init(options.order, options.x, options.y);

    return EXIT_SUCCESS;
}
