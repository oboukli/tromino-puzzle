// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "unittest_helper.h"

void shim_add_tromino(
    const int pos_x, const int pos_y, const int flip_x, const int flip_y,
    void* const state) noexcept {
    static_cast<std::vector<ShimStep>*>(state)->emplace_back(
        pos_x, pos_y, flip_x, flip_y);
}

void print_shim_step_vector(const std::vector<ShimStep>& steps) noexcept {
    // clang-format off
    for (const auto& s : steps) {
        std::cout
            << "{"
            << s.pos_x
            << ", "
            << s.pos_y
            << ", "
            << s.flip_x
            << ", "
            << s.flip_y
            << "},"
            << std::endl;
    }
    // clang-format on
}
