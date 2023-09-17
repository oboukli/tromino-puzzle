// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "unittest_helper.hpp"

void shim_add_tromino(
    int const pos_x,
    int const pos_y,
    int const flip_x,
    int const flip_y,
    void* const state) noexcept
{
    static_cast<std::vector<ShimStep>*>(state)->emplace_back(
        pos_x, pos_y, flip_x, flip_y);
}

void print_shim_step_vector(std::vector<ShimStep> const& steps) noexcept
{
    for (auto const& s : steps)
    {
        // clang-format off
        std::cout
            << "{"
            << s.pos_x << ", " << s.pos_y
            << ", "
            << s.flip_x << ", " << s.flip_y
            << "},\n";
        // clang-format on
    }
}
