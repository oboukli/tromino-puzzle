// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <stdlib.h>

#include <iostream>

#include "init.h"

int main(int argc, const char* argv[]) {
    // TODO: Config values
    // TODO: App name
    // TODO: Refactor out of main
    constexpr int REQUIRED_ARG_COUNT = 4;

    if (REQUIRED_ARG_COUNT > argc) {
        std::cout
            << "Usage: tromino <order> <x> <y>"
            << std::endl
#ifdef _WINDOWS
            << " [options]" << std::endl
            << "  --use-wch    Use legacy Windows Console Host" << std::endl
#endif // _WINDOWS
            << "Copyright (c) 2021 Omar Boukli-Hacene. All rights reserved."
            << std::endl;

        return EXIT_FAILURE;
    }

    int order = std::stoi(argv[1]);
    int x = std::stoi(argv[2]);
    int y = std::stoi(argv[3]);

#ifdef _WINDOWS
    bool use_wch = argc > REQUIRED_ARG_COUNT && std::string(argv[4]) == "--use-wch";

    emulation_mode em = use_wch ? emulation_mode::windows_console_host : emulation_mode::vt_100;
#else
    constexpr emulation_mode em = emulation_mode::vt_100;
#endif // _WINDOWS

    init(order, x, y, em);

    return EXIT_SUCCESS;
}
