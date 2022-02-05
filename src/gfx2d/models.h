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

    Step(trmn_position_t p, trmn_flip_t f) noexcept : p(p), f(f) {
    }

    Step(Step&& other) noexcept = default;

    Step& operator=(Step&& other) noexcept = delete;

    Step(Step& other) noexcept = delete;

    Step& operator=(Step& other) noexcept = delete;

    ~Step() noexcept = default;
};

} // namespace tromino::gfx2d

#endif // MODELS_H_
