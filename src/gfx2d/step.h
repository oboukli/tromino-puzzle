// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef GFX2D_STEP_H
#define GFX2D_STEP_H

#include "tromino.h"

namespace tromino::gfx2d {

struct Step final {
    const int px;
    const int py;
    const int fx;
    const int fy;

    constexpr Step(int px, int py, int fx, int fy) noexcept :
        px{px},
        py{py},
        fx{fx},
        fy{fy} {
    }

    Step(Step&& other) noexcept = default;

    Step& operator=(Step&& other) noexcept = delete;

    Step(Step& other) noexcept = delete;

    Step& operator=(Step& other) noexcept = delete;

    ~Step() noexcept = default;
};

} // namespace tromino::gfx2d

#endif // GFX2D_STEP_H
