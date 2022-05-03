// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef CLI_MODELS_H_
#define CLI_MODELS_H_

namespace tromino::cli {

#ifdef _WINDOWS
// clang-format off
enum class emulation_mode_type {
    vt100 = 0,
    wch = 1
};
// clang-format on
#endif // _WINDOWS

struct options {
    int order;
    int x;
    int y;
#ifdef _WINDOWS
    emulation_mode_type emulation_mode;
    bool use_wch;
#endif // _WINDOWS
};

} // namespace tromino::cli

#endif // CLI_MODELS_H_
