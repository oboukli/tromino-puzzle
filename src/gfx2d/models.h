// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef MODELS_H_
#define MODELS_H_

#include <memory>
#include <utility>
#include <vector>

#include "tromino.h"
namespace tromino::gfx2d {

struct Step {
    const trmn_position_t p;
    const trmn_flip_t f;

    Step(const trmn_position_t p, const trmn_flip_t f) :
        p(std::move(p)),
        f(std::move(f)) {
    }

    Step(const Step&& other) : p(std::move(other.p)), f(std::move(other.f)) {
    }

    Step(const Step& other) = delete;

    Step& operator=(const Step& other) = delete;
};

struct SolutionState {
    std::unique_ptr<std::vector<Step>> steps;
};

} // namespace tromino::gfx2d

#endif // MODELS_H_
