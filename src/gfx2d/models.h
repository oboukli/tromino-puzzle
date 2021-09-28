// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef models_h
#define models_h

#include <memory>
#include <vector>

#include "tromino.h"

namespace tromino::gfx2d {

struct Step {
    position_t p;
    flip_t f;
};

struct SolutionState {
    std::unique_ptr<std::vector<Step>> steps;
    size_t progress; // TODO:
};

} // namespace tromino::gfx2d

#endif // models_h
