// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef TEST_LIBTROMINO_UNITTEST_HELPER_HPP
#define TEST_LIBTROMINO_UNITTEST_HELPER_HPP

#include <iostream>
#include <vector>

#include "tromino.h"

class ShimStep final {
public:
    int pos_x;
    int pos_y;
    int flip_x;
    int flip_y;

    ShimStep() = delete;

    constexpr ShimStep(
        int const pos_x, int const pos_y, int const flip_x,
        int const flip_y) noexcept :
        pos_x{pos_x}, pos_y{pos_y}, flip_x{flip_x}, flip_y{flip_y} {
    }

    ShimStep(ShimStep const& other) = delete;

    constexpr ShimStep(ShimStep&& other) noexcept :
        pos_x{other.pos_x},
        pos_y{other.pos_y},
        flip_x{other.flip_x},
        flip_y{other.flip_y} {
    }

    ~ShimStep() = default;

    ShimStep& operator=(ShimStep const& other) = delete;

    ShimStep& operator=(ShimStep&& other) noexcept = delete;

    bool operator!=(ShimStep const& rhs) const noexcept {
        return rhs.pos_x != this->pos_x || rhs.pos_y != this->pos_y
            || rhs.flip_x != this->flip_x || rhs.flip_y != this->flip_y;
    }

    friend std::ostream&
    operator<<(std::ostream& os, ShimStep const& s) noexcept {
        // clang-format off
        return os
            << "Tromino position: (" << s.pos_x << ", " << s.pos_y
            << "). Flip: (" << s.flip_x << ", " << s.flip_y << ")";
        // clang-format on
    }
};

void shim_add_tromino(
    int const pos_x, int const pos_y, int const flip_x, int const flip_y,
    void* const state) noexcept;

void print_shim_step_vector(std::vector<ShimStep> const& steps) noexcept;

#endif // TEST_LIBTROMINO_UNITTEST_HELPER_HPP
