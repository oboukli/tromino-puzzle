// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef STEP_H_
#define STEP_H_

#include "tromino.h"

namespace tromino::gfx2d {

struct Step {
    const int px;
    const int py;
    const int fx;
    const int fy;

    Step(int px, int py, int fx, int fy) noexcept :
        px(px),
        py(py),
        fx(fx),
        fy(fy) {
    }

    Step(Step&& other) noexcept = default;

    Step& operator=(Step&& other) noexcept = delete;

    Step(Step& other) noexcept = delete;

    Step& operator=(Step& other) noexcept = delete;

    ~Step() noexcept = default;
};

} // namespace tromino::gfx2d

#endif // STEP_H_
