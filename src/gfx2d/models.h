// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef MODELS_H
#define MODELS_H

#include "tromino.h"

#include <memory>
#include <vector>

namespace tromino::gfx2d {

struct Step {
    trmn_position_t p;
    trmn_flip_t f;
};

struct SolutionState {
    std::unique_ptr<std::vector<Step>> steps;
};

} // namespace tromino::gfx2d

#endif // MODELS_H
