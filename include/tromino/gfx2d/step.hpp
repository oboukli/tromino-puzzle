// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef TROMINO_GFX2D_STEP_HPP
#define TROMINO_GFX2D_STEP_HPP

namespace tromino::gfx2d {

class Step final {
public:
    int px;
    int py;
    int fx;
    int fy;

    constexpr Step(
        int const px, int const py, int const fx, int const fy) noexcept :
        px{px}, py{py}, fx{fx}, fy{fy}
    {
    }

    Step(Step const& other) noexcept = delete;

    Step(Step&& other) noexcept = default;

    ~Step() noexcept = default;

    Step& operator=(Step const& other) noexcept = delete;

    Step& operator=(Step&& other) noexcept = delete;
};

} // namespace tromino::gfx2d

#endif // TROMINO_GFX2D_STEP_HPP
