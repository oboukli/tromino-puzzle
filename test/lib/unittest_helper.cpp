// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <vector>

#include "unittest_helper.h"

void shim_add_tromino(position_t abspos, flip_t flip, void * state) {
    ShimStep step = { abspos, flip };
    static_cast<std::vector<ShimStep>*>(state)->push_back(step);
}

void print_shim_step_vector(const std::vector<ShimStep>& steps) {
    for (auto s: steps) {
        std::cout
        << "{ { " << s.abspos.x <<", " << s.abspos.y << " }, { " << s.flip.x << ", " << s.flip.y << " } },"
        << std::endl;
    }
}
