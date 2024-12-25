// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef CLI_CLI_MODELS_HPP_
#define CLI_CLI_MODELS_HPP_

namespace tromino::cli {

#ifdef _WIN64
enum class emulation_mode_type {
    vt100 = 0,
    wch = 1,
};
#endif // _WIN64

struct options {
    int order{};
    int x{};
    int y{};
#ifdef _WIN64
    emulation_mode_type emulation_mode{};
    bool use_wch{};
#endif // _WIN64
};

} // namespace tromino::cli

#endif // CLI_CLI_MODELS_HPP_
