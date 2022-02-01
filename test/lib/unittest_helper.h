// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef UNITTEST_HELPER_H_
#define UNITTEST_HELPER_H_

#include <iostream>
#include <vector>

#include "tromino.h"

struct ShimStep {
    const trmn_position_t pos;
    const trmn_flip_t flip;

    ShimStep(trmn_position_t pos, trmn_flip_t flip) :
        pos(std::move(pos)),
        flip(std::move(flip)) {
    }

    ShimStep(ShimStep&& other) :
        pos(std::move(other.pos)),
        flip(std::move(other.flip)) {
    }

    ShimStep(const ShimStep& other) = delete;

    ShimStep& operator=(const ShimStep& other) = delete;

    bool operator!=(const ShimStep& rhs) const noexcept {
        return rhs.pos.x != this->pos.x || rhs.pos.y != this->pos.y
            || rhs.flip.x != this->flip.x || rhs.flip.y != this->flip.y;
    }

    friend std::ostream& operator<<(std::ostream& os, const ShimStep& s) noexcept {
        // clang-format off
        return os
            << "Tromino position: (" << s.pos.x << ", " << s.pos.y
            << "). Flip: (" << s.flip.x << ", " << s.flip.y << ")";
        // clang-format on
    }
};

void shim_add_tromino(
    trmn_position_t pos, trmn_flip_t flip, void* state) noexcept;

void print_shim_step_vector(const std::vector<ShimStep>& steps) noexcept;

#endif // UNITTEST_HELPER_H_
