// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "callback.hpp"

#include <vector>

#include <tromino/gfx2d/step.hpp>

extern "C" void add_tromino(
    int const pos_x,
    int const pos_y,
    int const flip_x,
    int const flip_y,
    void* const state
) noexcept
{
    auto* const steps_{static_cast<std::vector<tromino::gfx2d::Step>*>(state)};

    steps_->emplace_back(pos_x, pos_y, flip_x, flip_y);
}
