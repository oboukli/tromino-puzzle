// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

#include <stdlib.h>
#include <iostream>

#include "init.h"

int main(int argc, const char* argv[]) {
    // TODO: Add mode option (WCH, VT) always default to VT
    // TODO: CONFIG VALS
    // TODO: App name
    // TODO: Refactor out of main
    constexpr auto REQUIRED_ARG_COUNT = 4;

    if (REQUIRED_ARG_COUNT != argc) {
        std::cout << "Usage: tromino <order> <x> <y>" << std::endl;
        return EXIT_FAILURE;
    }

    int order = std::stoi(argv[1]);
    int x = std::stoi(argv[2]);
    int y = std::stoi(argv[3]);

    init(order, x, y);

    return EXIT_SUCCESS;
}
