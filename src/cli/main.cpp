// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <iostream>
#include <string>

#include "init.h"

int main(const int argc, const char* const argv[]) {
    // TODO: Config values
    // TODO: App name
    // TODO: Refactor out of main
    constexpr int REQUIRED_ARG_COUNT = 4;

    if (REQUIRED_ARG_COUNT > argc) {
        // clang-format off
        std::cout
            << "Usage: tromino <order> <x> <y>" << std::endl
#ifdef _WINDOWS
            << " [options]" << std::endl
            << "  --use-wch    Use legacy Windows Console Host" << std::endl
#endif // _WINDOWS
            << "Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved."
            << std::endl;
        // clang-format on

        return EXIT_FAILURE;
    }

    const int order = std::stoi(argv[1]);
    const int x = std::stoi(argv[2]);
    const int y = std::stoi(argv[3]);

#ifdef _WINDOWS
    bool use_wch
        = argc > REQUIRED_ARG_COUNT && std::string(argv[4]) == "--use-wch";

    // clang-format off
    emulation_mode em =
        use_wch ? emulation_mode::windows_console_host : emulation_mode::vt_100;
    // clang-format on
#else
    constexpr const emulation_mode em = emulation_mode::vt_100;
#endif // _WINDOWS

    init(order, x, y, em);

    return EXIT_SUCCESS;
}
