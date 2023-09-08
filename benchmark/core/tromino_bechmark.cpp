// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <nameof.hpp>

#include <nanobench.h>

#include <tromino.h>

void dummy_callback(
    int const px, int const py, int const fx, int const fy, void* const state) {
}

int main() {
    ankerl::nanobench::Bench()
        .run(
            NAMEOF(trmn_solve_puzzle).c_str(),
            []() {
                int const stop_flag{0};
                trmn_solve_puzzle(
                    16, 1, 7, dummy_callback, nullptr, &stop_flag);
            })

        ;
}
