// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "unittest_helper.h"

#include <vector>

void shim_add_tromino(trmn_position_t pos, trmn_flip_t flip, void* state) {
    ShimStep step = {pos, flip};
    static_cast<std::vector<ShimStep>*>(state)->push_back(step);
}

void print_shim_step_vector(const std::vector<ShimStep>& steps) {
    // clang-format off
    for (auto s: steps) {
        std::cout
            << "{ { "
            << s.pos.x
            << ", "
            << s.pos.y
            << " }, { "
            << s.flip.x
            << ", "
            << s.flip.y
            << " } },"
            << std::endl;
    }
    // clang-format on
}
