// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef GUI_CALLBACK_HPP_
#define GUI_CALLBACK_HPP_

extern "C" void tromino_solve_puzzle_cb(
    int pos_x, int pos_y, int flip_x, int flip_y, void* state
) noexcept;

#endif // GUI_CALLBACK_HPP_
