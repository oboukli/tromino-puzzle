// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef UNITTEST_HELPER_H_
#define UNITTEST_HELPER_H_

#include <iostream>
#include <vector>

#include "tromino.h"

class ShimStep
{
public:
    trmn_position_t pos;
    trmn_flip_t flip;

    bool operator!=(const ShimStep &rhs) {
        return rhs.pos.x != this->pos.x
            || rhs.pos.y != this->pos.y
            || rhs.flip.x != this->flip.x
            || rhs.flip.y != this->flip.y;
    }

    friend std::ostream & operator<<(std::ostream &os, const ShimStep &s) {
        return os
            << "Tromino position: (" << s.pos.x << ", " << s.pos.y
            << "). Flip: (" << s.flip.x << ", " << s.flip.y << ")";
    }
};

void shim_add_tromino(trmn_position_t pos, trmn_flip_t flip, void * state);

void print_shim_step_vector(const std::vector<ShimStep>& steps);

#endif // UNITTEST_HELPER_H_
