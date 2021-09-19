// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef unittest_helper_h
#define unittest_helper_h

#include <iostream>

#include "tromino.h"

class ShimStep
{
public:
    position_t abspos;
    flip_t flip;

    bool operator!=(const ShimStep &rhs) {
        return rhs.abspos.x != this->abspos.x
            || rhs.abspos.y != this->abspos.y
            || rhs.flip.x != this->flip.x
            || rhs.flip.y != this->flip.y;
    }

    friend std::ostream & operator<<(std::ostream &os, const ShimStep &s) {
        return os
            << "Tromino position: (" << s.abspos.x << ", " << s.abspos.y
            << "). Flip: (" << s.flip.x << ", " << s.flip.y << ")";
    }
};

void shim_add_tromino(position_t abspos, flip_t flip, void * state);

void print_shim_step_vector(const std::vector<ShimStep>& steps);

#endif /* unittest_helper_h */
