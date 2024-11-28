// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef TROMINO_GFX2D_STEP_HPP_
#define TROMINO_GFX2D_STEP_HPP_

namespace tromino::gfx2d {

class Step final {
public:
    int px;
    int py;
    int fx;
    int fy;

    constexpr Step(
        int const pos_x, int const pos_y, int const flp_x, int const flp_y
    ) noexcept :
        px{pos_x}, py{pos_y}, fx{flp_x}, fy{flp_y}
    {
    }

    Step(Step const& other) = delete;

    Step(Step&& other) noexcept = default;

    ~Step() noexcept = default;

    Step& operator=(Step const& other) = delete;

    Step& operator=(Step&& other) = delete;
};

} // namespace tromino::gfx2d

#endif // TROMINO_GFX2D_STEP_HPP_
