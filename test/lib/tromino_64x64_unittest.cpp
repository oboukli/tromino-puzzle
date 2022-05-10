// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <boost/test/unit_test.hpp>

#include "tromino.h"

#include "unittest_helper.h"

namespace {

// clang-format off
const std::array<ShimStep, std::size_t{((64 * 64) - 1) / 3}>
    g_expected_for_order_64_and_mark_61_37{{
        {60, 36, 1, 1},
        {62, 38, -1, -1},
        {62, 36, -1, 1},
        {60, 38, 1, -1},
        {61, 37, -1, -1},
        {56, 32, 1, 1},
        {56, 34, 1, -1},
        {58, 32, -1, 1},
        {57, 33, 1, 1},
        {56, 38, 1, -1},
        {56, 36, 1, 1},
        {58, 38, -1, -1},
        {57, 37, 1, -1},
        {62, 32, -1, 1},
        {62, 34, -1, -1},
        {60, 32, 1, 1},
        {61, 33, -1, 1},
        {58, 34, 1, 1},
        {58, 36, 1, -1},
        {60, 34, -1, 1},
        {59, 35, 1, 1},
        {48, 46, 1, -1},
        {48, 44, 1, 1},
        {50, 46, -1, -1},
        {49, 45, 1, -1},
        {48, 40, 1, 1},
        {48, 42, 1, -1},
        {50, 40, -1, 1},
        {49, 41, 1, 1},
        {54, 46, -1, -1},
        {54, 44, -1, 1},
        {52, 46, 1, -1},
        {53, 45, -1, -1},
        {50, 44, 1, -1},
        {50, 42, 1, 1},
        {52, 44, -1, -1},
        {51, 43, 1, -1},
        {48, 32, 1, 1},
        {48, 34, 1, -1},
        {50, 32, -1, 1},
        {49, 33, 1, 1},
        {48, 38, 1, -1},
        {48, 36, 1, 1},
        {50, 38, -1, -1},
        {49, 37, 1, -1},
        {54, 32, -1, 1},
        {54, 34, -1, -1},
        {52, 32, 1, 1},
        {53, 33, -1, 1},
        {50, 34, 1, 1},
        {50, 36, 1, -1},
        {52, 34, -1, 1},
        {51, 35, 1, 1},
        {62, 46, -1, -1},
        {62, 44, -1, 1},
        {60, 46, 1, -1},
        {61, 45, -1, -1},
        {62, 40, -1, 1},
        {62, 42, -1, -1},
        {60, 40, 1, 1},
        {61, 41, -1, 1},
        {56, 46, 1, -1},
        {56, 44, 1, 1},
        {58, 46, -1, -1},
        {57, 45, 1, -1},
        {60, 44, -1, -1},
        {60, 42, -1, 1},
        {58, 44, 1, -1},
        {59, 43, -1, -1},
        {52, 42, 1, -1},
        {52, 40, 1, 1},
        {54, 42, -1, -1},
        {53, 41, 1, -1},
        {52, 36, 1, 1},
        {52, 38, 1, -1},
        {54, 36, -1, 1},
        {53, 37, 1, 1},
        {58, 42, -1, -1},
        {58, 40, -1, 1},
        {56, 42, 1, -1},
        {57, 41, -1, -1},
        {54, 40, 1, -1},
        {54, 38, 1, 1},
        {56, 40, -1, -1},
        {55, 39, 1, -1},
        {32, 62, 1, -1},
        {32, 60, 1, 1},
        {34, 62, -1, -1},
        {33, 61, 1, -1},
        {32, 56, 1, 1},
        {32, 58, 1, -1},
        {34, 56, -1, 1},
        {33, 57, 1, 1},
        {38, 62, -1, -1},
        {38, 60, -1, 1},
        {36, 62, 1, -1},
        {37, 61, -1, -1},
        {34, 60, 1, -1},
        {34, 58, 1, 1},
        {36, 60, -1, -1},
        {35, 59, 1, -1},
        {32, 48, 1, 1},
        {32, 50, 1, -1},
        {34, 48, -1, 1},
        {33, 49, 1, 1},
        {32, 54, 1, -1},
        {32, 52, 1, 1},
        {34, 54, -1, -1},
        {33, 53, 1, -1},
        {38, 48, -1, 1},
        {38, 50, -1, -1},
        {36, 48, 1, 1},
        {37, 49, -1, 1},
        {34, 50, 1, 1},
        {34, 52, 1, -1},
        {36, 50, -1, 1},
        {35, 51, 1, 1},
        {46, 62, -1, -1},
        {46, 60, -1, 1},
        {44, 62, 1, -1},
        {45, 61, -1, -1},
        {46, 56, -1, 1},
        {46, 58, -1, -1},
        {44, 56, 1, 1},
        {45, 57, -1, 1},
        {40, 62, 1, -1},
        {40, 60, 1, 1},
        {42, 62, -1, -1},
        {41, 61, 1, -1},
        {44, 60, -1, -1},
        {44, 58, -1, 1},
        {42, 60, 1, -1},
        {43, 59, -1, -1},
        {36, 58, 1, -1},
        {36, 56, 1, 1},
        {38, 58, -1, -1},
        {37, 57, 1, -1},
        {36, 52, 1, 1},
        {36, 54, 1, -1},
        {38, 52, -1, 1},
        {37, 53, 1, 1},
        {42, 58, -1, -1},
        {42, 56, -1, 1},
        {40, 58, 1, -1},
        {41, 57, -1, -1},
        {38, 56, 1, -1},
        {38, 54, 1, 1},
        {40, 56, -1, -1},
        {39, 55, 1, -1},
        {32, 32, 1, 1},
        {32, 34, 1, -1},
        {34, 32, -1, 1},
        {33, 33, 1, 1},
        {32, 38, 1, -1},
        {32, 36, 1, 1},
        {34, 38, -1, -1},
        {33, 37, 1, -1},
        {38, 32, -1, 1},
        {38, 34, -1, -1},
        {36, 32, 1, 1},
        {37, 33, -1, 1},
        {34, 34, 1, 1},
        {34, 36, 1, -1},
        {36, 34, -1, 1},
        {35, 35, 1, 1},
        {32, 46, 1, -1},
        {32, 44, 1, 1},
        {34, 46, -1, -1},
        {33, 45, 1, -1},
        {32, 40, 1, 1},
        {32, 42, 1, -1},
        {34, 40, -1, 1},
        {33, 41, 1, 1},
        {38, 46, -1, -1},
        {38, 44, -1, 1},
        {36, 46, 1, -1},
        {37, 45, -1, -1},
        {34, 44, 1, -1},
        {34, 42, 1, 1},
        {36, 44, -1, -1},
        {35, 43, 1, -1},
        {46, 32, -1, 1},
        {46, 34, -1, -1},
        {44, 32, 1, 1},
        {45, 33, -1, 1},
        {46, 38, -1, -1},
        {46, 36, -1, 1},
        {44, 38, 1, -1},
        {45, 37, -1, -1},
        {40, 32, 1, 1},
        {40, 34, 1, -1},
        {42, 32, -1, 1},
        {41, 33, 1, 1},
        {44, 34, -1, 1},
        {44, 36, -1, -1},
        {42, 34, 1, 1},
        {43, 35, -1, 1},
        {36, 36, 1, 1},
        {36, 38, 1, -1},
        {38, 36, -1, 1},
        {37, 37, 1, 1},
        {36, 42, 1, -1},
        {36, 40, 1, 1},
        {38, 42, -1, -1},
        {37, 41, 1, -1},
        {42, 36, -1, 1},
        {42, 38, -1, -1},
        {40, 36, 1, 1},
        {41, 37, -1, 1},
        {38, 38, 1, 1},
        {38, 40, 1, -1},
        {40, 38, -1, 1},
        {39, 39, 1, 1},
        {62, 62, -1, -1},
        {62, 60, -1, 1},
        {60, 62, 1, -1},
        {61, 61, -1, -1},
        {62, 56, -1, 1},
        {62, 58, -1, -1},
        {60, 56, 1, 1},
        {61, 57, -1, 1},
        {56, 62, 1, -1},
        {56, 60, 1, 1},
        {58, 62, -1, -1},
        {57, 61, 1, -1},
        {60, 60, -1, -1},
        {60, 58, -1, 1},
        {58, 60, 1, -1},
        {59, 59, -1, -1},
        {62, 48, -1, 1},
        {62, 50, -1, -1},
        {60, 48, 1, 1},
        {61, 49, -1, 1},
        {62, 54, -1, -1},
        {62, 52, -1, 1},
        {60, 54, 1, -1},
        {61, 53, -1, -1},
        {56, 48, 1, 1},
        {56, 50, 1, -1},
        {58, 48, -1, 1},
        {57, 49, 1, 1},
        {60, 50, -1, 1},
        {60, 52, -1, -1},
        {58, 50, 1, 1},
        {59, 51, -1, 1},
        {48, 62, 1, -1},
        {48, 60, 1, 1},
        {50, 62, -1, -1},
        {49, 61, 1, -1},
        {48, 56, 1, 1},
        {48, 58, 1, -1},
        {50, 56, -1, 1},
        {49, 57, 1, 1},
        {54, 62, -1, -1},
        {54, 60, -1, 1},
        {52, 62, 1, -1},
        {53, 61, -1, -1},
        {50, 60, 1, -1},
        {50, 58, 1, 1},
        {52, 60, -1, -1},
        {51, 59, 1, -1},
        {58, 58, -1, -1},
        {58, 56, -1, 1},
        {56, 58, 1, -1},
        {57, 57, -1, -1},
        {58, 52, -1, 1},
        {58, 54, -1, -1},
        {56, 52, 1, 1},
        {57, 53, -1, 1},
        {52, 58, 1, -1},
        {52, 56, 1, 1},
        {54, 58, -1, -1},
        {53, 57, 1, -1},
        {56, 56, -1, -1},
        {56, 54, -1, 1},
        {54, 56, 1, -1},
        {55, 55, -1, -1},
        {40, 54, 1, -1},
        {40, 52, 1, 1},
        {42, 54, -1, -1},
        {41, 53, 1, -1},
        {40, 48, 1, 1},
        {40, 50, 1, -1},
        {42, 48, -1, 1},
        {41, 49, 1, 1},
        {46, 54, -1, -1},
        {46, 52, -1, 1},
        {44, 54, 1, -1},
        {45, 53, -1, -1},
        {42, 52, 1, -1},
        {42, 50, 1, 1},
        {44, 52, -1, -1},
        {43, 51, 1, -1},
        {40, 40, 1, 1},
        {40, 42, 1, -1},
        {42, 40, -1, 1},
        {41, 41, 1, 1},
        {40, 46, 1, -1},
        {40, 44, 1, 1},
        {42, 46, -1, -1},
        {41, 45, 1, -1},
        {46, 40, -1, 1},
        {46, 42, -1, -1},
        {44, 40, 1, 1},
        {45, 41, -1, 1},
        {42, 42, 1, 1},
        {42, 44, 1, -1},
        {44, 42, -1, 1},
        {43, 43, 1, 1},
        {54, 54, -1, -1},
        {54, 52, -1, 1},
        {52, 54, 1, -1},
        {53, 53, -1, -1},
        {54, 48, -1, 1},
        {54, 50, -1, -1},
        {52, 48, 1, 1},
        {53, 49, -1, 1},
        {48, 54, 1, -1},
        {48, 52, 1, 1},
        {50, 54, -1, -1},
        {49, 53, 1, -1},
        {52, 52, -1, -1},
        {52, 50, -1, 1},
        {50, 52, 1, -1},
        {51, 51, -1, -1},
        {44, 50, 1, -1},
        {44, 48, 1, 1},
        {46, 50, -1, -1},
        {45, 49, 1, -1},
        {44, 44, 1, 1},
        {44, 46, 1, -1},
        {46, 44, -1, 1},
        {45, 45, 1, 1},
        {50, 50, -1, -1},
        {50, 48, -1, 1},
        {48, 50, 1, -1},
        {49, 49, -1, -1},
        {46, 48, 1, -1},
        {46, 46, 1, 1},
        {48, 48, -1, -1},
        {47, 47, 1, -1},
        {0, 0, 1, 1},
        {0, 2, 1, -1},
        {2, 0, -1, 1},
        {1, 1, 1, 1},
        {0, 6, 1, -1},
        {0, 4, 1, 1},
        {2, 6, -1, -1},
        {1, 5, 1, -1},
        {6, 0, -1, 1},
        {6, 2, -1, -1},
        {4, 0, 1, 1},
        {5, 1, -1, 1},
        {2, 2, 1, 1},
        {2, 4, 1, -1},
        {4, 2, -1, 1},
        {3, 3, 1, 1},
        {0, 14, 1, -1},
        {0, 12, 1, 1},
        {2, 14, -1, -1},
        {1, 13, 1, -1},
        {0, 8, 1, 1},
        {0, 10, 1, -1},
        {2, 8, -1, 1},
        {1, 9, 1, 1},
        {6, 14, -1, -1},
        {6, 12, -1, 1},
        {4, 14, 1, -1},
        {5, 13, -1, -1},
        {2, 12, 1, -1},
        {2, 10, 1, 1},
        {4, 12, -1, -1},
        {3, 11, 1, -1},
        {14, 0, -1, 1},
        {14, 2, -1, -1},
        {12, 0, 1, 1},
        {13, 1, -1, 1},
        {14, 6, -1, -1},
        {14, 4, -1, 1},
        {12, 6, 1, -1},
        {13, 5, -1, -1},
        {8, 0, 1, 1},
        {8, 2, 1, -1},
        {10, 0, -1, 1},
        {9, 1, 1, 1},
        {12, 2, -1, 1},
        {12, 4, -1, -1},
        {10, 2, 1, 1},
        {11, 3, -1, 1},
        {4, 4, 1, 1},
        {4, 6, 1, -1},
        {6, 4, -1, 1},
        {5, 5, 1, 1},
        {4, 10, 1, -1},
        {4, 8, 1, 1},
        {6, 10, -1, -1},
        {5, 9, 1, -1},
        {10, 4, -1, 1},
        {10, 6, -1, -1},
        {8, 4, 1, 1},
        {9, 5, -1, 1},
        {6, 6, 1, 1},
        {6, 8, 1, -1},
        {8, 6, -1, 1},
        {7, 7, 1, 1},
        {0, 30, 1, -1},
        {0, 28, 1, 1},
        {2, 30, -1, -1},
        {1, 29, 1, -1},
        {0, 24, 1, 1},
        {0, 26, 1, -1},
        {2, 24, -1, 1},
        {1, 25, 1, 1},
        {6, 30, -1, -1},
        {6, 28, -1, 1},
        {4, 30, 1, -1},
        {5, 29, -1, -1},
        {2, 28, 1, -1},
        {2, 26, 1, 1},
        {4, 28, -1, -1},
        {3, 27, 1, -1},
        {0, 16, 1, 1},
        {0, 18, 1, -1},
        {2, 16, -1, 1},
        {1, 17, 1, 1},
        {0, 22, 1, -1},
        {0, 20, 1, 1},
        {2, 22, -1, -1},
        {1, 21, 1, -1},
        {6, 16, -1, 1},
        {6, 18, -1, -1},
        {4, 16, 1, 1},
        {5, 17, -1, 1},
        {2, 18, 1, 1},
        {2, 20, 1, -1},
        {4, 18, -1, 1},
        {3, 19, 1, 1},
        {14, 30, -1, -1},
        {14, 28, -1, 1},
        {12, 30, 1, -1},
        {13, 29, -1, -1},
        {14, 24, -1, 1},
        {14, 26, -1, -1},
        {12, 24, 1, 1},
        {13, 25, -1, 1},
        {8, 30, 1, -1},
        {8, 28, 1, 1},
        {10, 30, -1, -1},
        {9, 29, 1, -1},
        {12, 28, -1, -1},
        {12, 26, -1, 1},
        {10, 28, 1, -1},
        {11, 27, -1, -1},
        {4, 26, 1, -1},
        {4, 24, 1, 1},
        {6, 26, -1, -1},
        {5, 25, 1, -1},
        {4, 20, 1, 1},
        {4, 22, 1, -1},
        {6, 20, -1, 1},
        {5, 21, 1, 1},
        {10, 26, -1, -1},
        {10, 24, -1, 1},
        {8, 26, 1, -1},
        {9, 25, -1, -1},
        {6, 24, 1, -1},
        {6, 22, 1, 1},
        {8, 24, -1, -1},
        {7, 23, 1, -1},
        {30, 0, -1, 1},
        {30, 2, -1, -1},
        {28, 0, 1, 1},
        {29, 1, -1, 1},
        {30, 6, -1, -1},
        {30, 4, -1, 1},
        {28, 6, 1, -1},
        {29, 5, -1, -1},
        {24, 0, 1, 1},
        {24, 2, 1, -1},
        {26, 0, -1, 1},
        {25, 1, 1, 1},
        {28, 2, -1, 1},
        {28, 4, -1, -1},
        {26, 2, 1, 1},
        {27, 3, -1, 1},
        {30, 14, -1, -1},
        {30, 12, -1, 1},
        {28, 14, 1, -1},
        {29, 13, -1, -1},
        {30, 8, -1, 1},
        {30, 10, -1, -1},
        {28, 8, 1, 1},
        {29, 9, -1, 1},
        {24, 14, 1, -1},
        {24, 12, 1, 1},
        {26, 14, -1, -1},
        {25, 13, 1, -1},
        {28, 12, -1, -1},
        {28, 10, -1, 1},
        {26, 12, 1, -1},
        {27, 11, -1, -1},
        {16, 0, 1, 1},
        {16, 2, 1, -1},
        {18, 0, -1, 1},
        {17, 1, 1, 1},
        {16, 6, 1, -1},
        {16, 4, 1, 1},
        {18, 6, -1, -1},
        {17, 5, 1, -1},
        {22, 0, -1, 1},
        {22, 2, -1, -1},
        {20, 0, 1, 1},
        {21, 1, -1, 1},
        {18, 2, 1, 1},
        {18, 4, 1, -1},
        {20, 2, -1, 1},
        {19, 3, 1, 1},
        {26, 4, -1, 1},
        {26, 6, -1, -1},
        {24, 4, 1, 1},
        {25, 5, -1, 1},
        {26, 10, -1, -1},
        {26, 8, -1, 1},
        {24, 10, 1, -1},
        {25, 9, -1, -1},
        {20, 4, 1, 1},
        {20, 6, 1, -1},
        {22, 4, -1, 1},
        {21, 5, 1, 1},
        {24, 6, -1, 1},
        {24, 8, -1, -1},
        {22, 6, 1, 1},
        {23, 7, -1, 1},
        {8, 8, 1, 1},
        {8, 10, 1, -1},
        {10, 8, -1, 1},
        {9, 9, 1, 1},
        {8, 14, 1, -1},
        {8, 12, 1, 1},
        {10, 14, -1, -1},
        {9, 13, 1, -1},
        {14, 8, -1, 1},
        {14, 10, -1, -1},
        {12, 8, 1, 1},
        {13, 9, -1, 1},
        {10, 10, 1, 1},
        {10, 12, 1, -1},
        {12, 10, -1, 1},
        {11, 11, 1, 1},
        {8, 22, 1, -1},
        {8, 20, 1, 1},
        {10, 22, -1, -1},
        {9, 21, 1, -1},
        {8, 16, 1, 1},
        {8, 18, 1, -1},
        {10, 16, -1, 1},
        {9, 17, 1, 1},
        {14, 22, -1, -1},
        {14, 20, -1, 1},
        {12, 22, 1, -1},
        {13, 21, -1, -1},
        {10, 20, 1, -1},
        {10, 18, 1, 1},
        {12, 20, -1, -1},
        {11, 19, 1, -1},
        {22, 8, -1, 1},
        {22, 10, -1, -1},
        {20, 8, 1, 1},
        {21, 9, -1, 1},
        {22, 14, -1, -1},
        {22, 12, -1, 1},
        {20, 14, 1, -1},
        {21, 13, -1, -1},
        {16, 8, 1, 1},
        {16, 10, 1, -1},
        {18, 8, -1, 1},
        {17, 9, 1, 1},
        {20, 10, -1, 1},
        {20, 12, -1, -1},
        {18, 10, 1, 1},
        {19, 11, -1, 1},
        {12, 12, 1, 1},
        {12, 14, 1, -1},
        {14, 12, -1, 1},
        {13, 13, 1, 1},
        {12, 18, 1, -1},
        {12, 16, 1, 1},
        {14, 18, -1, -1},
        {13, 17, 1, -1},
        {18, 12, -1, 1},
        {18, 14, -1, -1},
        {16, 12, 1, 1},
        {17, 13, -1, 1},
        {14, 14, 1, 1},
        {14, 16, 1, -1},
        {16, 14, -1, 1},
        {15, 15, 1, 1},
        {0, 62, 1, -1},
        {0, 60, 1, 1},
        {2, 62, -1, -1},
        {1, 61, 1, -1},
        {0, 56, 1, 1},
        {0, 58, 1, -1},
        {2, 56, -1, 1},
        {1, 57, 1, 1},
        {6, 62, -1, -1},
        {6, 60, -1, 1},
        {4, 62, 1, -1},
        {5, 61, -1, -1},
        {2, 60, 1, -1},
        {2, 58, 1, 1},
        {4, 60, -1, -1},
        {3, 59, 1, -1},
        {0, 48, 1, 1},
        {0, 50, 1, -1},
        {2, 48, -1, 1},
        {1, 49, 1, 1},
        {0, 54, 1, -1},
        {0, 52, 1, 1},
        {2, 54, -1, -1},
        {1, 53, 1, -1},
        {6, 48, -1, 1},
        {6, 50, -1, -1},
        {4, 48, 1, 1},
        {5, 49, -1, 1},
        {2, 50, 1, 1},
        {2, 52, 1, -1},
        {4, 50, -1, 1},
        {3, 51, 1, 1},
        {14, 62, -1, -1},
        {14, 60, -1, 1},
        {12, 62, 1, -1},
        {13, 61, -1, -1},
        {14, 56, -1, 1},
        {14, 58, -1, -1},
        {12, 56, 1, 1},
        {13, 57, -1, 1},
        {8, 62, 1, -1},
        {8, 60, 1, 1},
        {10, 62, -1, -1},
        {9, 61, 1, -1},
        {12, 60, -1, -1},
        {12, 58, -1, 1},
        {10, 60, 1, -1},
        {11, 59, -1, -1},
        {4, 58, 1, -1},
        {4, 56, 1, 1},
        {6, 58, -1, -1},
        {5, 57, 1, -1},
        {4, 52, 1, 1},
        {4, 54, 1, -1},
        {6, 52, -1, 1},
        {5, 53, 1, 1},
        {10, 58, -1, -1},
        {10, 56, -1, 1},
        {8, 58, 1, -1},
        {9, 57, -1, -1},
        {6, 56, 1, -1},
        {6, 54, 1, 1},
        {8, 56, -1, -1},
        {7, 55, 1, -1},
        {0, 32, 1, 1},
        {0, 34, 1, -1},
        {2, 32, -1, 1},
        {1, 33, 1, 1},
        {0, 38, 1, -1},
        {0, 36, 1, 1},
        {2, 38, -1, -1},
        {1, 37, 1, -1},
        {6, 32, -1, 1},
        {6, 34, -1, -1},
        {4, 32, 1, 1},
        {5, 33, -1, 1},
        {2, 34, 1, 1},
        {2, 36, 1, -1},
        {4, 34, -1, 1},
        {3, 35, 1, 1},
        {0, 46, 1, -1},
        {0, 44, 1, 1},
        {2, 46, -1, -1},
        {1, 45, 1, -1},
        {0, 40, 1, 1},
        {0, 42, 1, -1},
        {2, 40, -1, 1},
        {1, 41, 1, 1},
        {6, 46, -1, -1},
        {6, 44, -1, 1},
        {4, 46, 1, -1},
        {5, 45, -1, -1},
        {2, 44, 1, -1},
        {2, 42, 1, 1},
        {4, 44, -1, -1},
        {3, 43, 1, -1},
        {14, 32, -1, 1},
        {14, 34, -1, -1},
        {12, 32, 1, 1},
        {13, 33, -1, 1},
        {14, 38, -1, -1},
        {14, 36, -1, 1},
        {12, 38, 1, -1},
        {13, 37, -1, -1},
        {8, 32, 1, 1},
        {8, 34, 1, -1},
        {10, 32, -1, 1},
        {9, 33, 1, 1},
        {12, 34, -1, 1},
        {12, 36, -1, -1},
        {10, 34, 1, 1},
        {11, 35, -1, 1},
        {4, 36, 1, 1},
        {4, 38, 1, -1},
        {6, 36, -1, 1},
        {5, 37, 1, 1},
        {4, 42, 1, -1},
        {4, 40, 1, 1},
        {6, 42, -1, -1},
        {5, 41, 1, -1},
        {10, 36, -1, 1},
        {10, 38, -1, -1},
        {8, 36, 1, 1},
        {9, 37, -1, 1},
        {6, 38, 1, 1},
        {6, 40, 1, -1},
        {8, 38, -1, 1},
        {7, 39, 1, 1},
        {30, 62, -1, -1},
        {30, 60, -1, 1},
        {28, 62, 1, -1},
        {29, 61, -1, -1},
        {30, 56, -1, 1},
        {30, 58, -1, -1},
        {28, 56, 1, 1},
        {29, 57, -1, 1},
        {24, 62, 1, -1},
        {24, 60, 1, 1},
        {26, 62, -1, -1},
        {25, 61, 1, -1},
        {28, 60, -1, -1},
        {28, 58, -1, 1},
        {26, 60, 1, -1},
        {27, 59, -1, -1},
        {30, 48, -1, 1},
        {30, 50, -1, -1},
        {28, 48, 1, 1},
        {29, 49, -1, 1},
        {30, 54, -1, -1},
        {30, 52, -1, 1},
        {28, 54, 1, -1},
        {29, 53, -1, -1},
        {24, 48, 1, 1},
        {24, 50, 1, -1},
        {26, 48, -1, 1},
        {25, 49, 1, 1},
        {28, 50, -1, 1},
        {28, 52, -1, -1},
        {26, 50, 1, 1},
        {27, 51, -1, 1},
        {16, 62, 1, -1},
        {16, 60, 1, 1},
        {18, 62, -1, -1},
        {17, 61, 1, -1},
        {16, 56, 1, 1},
        {16, 58, 1, -1},
        {18, 56, -1, 1},
        {17, 57, 1, 1},
        {22, 62, -1, -1},
        {22, 60, -1, 1},
        {20, 62, 1, -1},
        {21, 61, -1, -1},
        {18, 60, 1, -1},
        {18, 58, 1, 1},
        {20, 60, -1, -1},
        {19, 59, 1, -1},
        {26, 58, -1, -1},
        {26, 56, -1, 1},
        {24, 58, 1, -1},
        {25, 57, -1, -1},
        {26, 52, -1, 1},
        {26, 54, -1, -1},
        {24, 52, 1, 1},
        {25, 53, -1, 1},
        {20, 58, 1, -1},
        {20, 56, 1, 1},
        {22, 58, -1, -1},
        {21, 57, 1, -1},
        {24, 56, -1, -1},
        {24, 54, -1, 1},
        {22, 56, 1, -1},
        {23, 55, -1, -1},
        {8, 54, 1, -1},
        {8, 52, 1, 1},
        {10, 54, -1, -1},
        {9, 53, 1, -1},
        {8, 48, 1, 1},
        {8, 50, 1, -1},
        {10, 48, -1, 1},
        {9, 49, 1, 1},
        {14, 54, -1, -1},
        {14, 52, -1, 1},
        {12, 54, 1, -1},
        {13, 53, -1, -1},
        {10, 52, 1, -1},
        {10, 50, 1, 1},
        {12, 52, -1, -1},
        {11, 51, 1, -1},
        {8, 40, 1, 1},
        {8, 42, 1, -1},
        {10, 40, -1, 1},
        {9, 41, 1, 1},
        {8, 46, 1, -1},
        {8, 44, 1, 1},
        {10, 46, -1, -1},
        {9, 45, 1, -1},
        {14, 40, -1, 1},
        {14, 42, -1, -1},
        {12, 40, 1, 1},
        {13, 41, -1, 1},
        {10, 42, 1, 1},
        {10, 44, 1, -1},
        {12, 42, -1, 1},
        {11, 43, 1, 1},
        {22, 54, -1, -1},
        {22, 52, -1, 1},
        {20, 54, 1, -1},
        {21, 53, -1, -1},
        {22, 48, -1, 1},
        {22, 50, -1, -1},
        {20, 48, 1, 1},
        {21, 49, -1, 1},
        {16, 54, 1, -1},
        {16, 52, 1, 1},
        {18, 54, -1, -1},
        {17, 53, 1, -1},
        {20, 52, -1, -1},
        {20, 50, -1, 1},
        {18, 52, 1, -1},
        {19, 51, -1, -1},
        {12, 50, 1, -1},
        {12, 48, 1, 1},
        {14, 50, -1, -1},
        {13, 49, 1, -1},
        {12, 44, 1, 1},
        {12, 46, 1, -1},
        {14, 44, -1, 1},
        {13, 45, 1, 1},
        {18, 50, -1, -1},
        {18, 48, -1, 1},
        {16, 50, 1, -1},
        {17, 49, -1, -1},
        {14, 48, 1, -1},
        {14, 46, 1, 1},
        {16, 48, -1, -1},
        {15, 47, 1, -1},
        {62, 0, -1, 1},
        {62, 2, -1, -1},
        {60, 0, 1, 1},
        {61, 1, -1, 1},
        {62, 6, -1, -1},
        {62, 4, -1, 1},
        {60, 6, 1, -1},
        {61, 5, -1, -1},
        {56, 0, 1, 1},
        {56, 2, 1, -1},
        {58, 0, -1, 1},
        {57, 1, 1, 1},
        {60, 2, -1, 1},
        {60, 4, -1, -1},
        {58, 2, 1, 1},
        {59, 3, -1, 1},
        {62, 14, -1, -1},
        {62, 12, -1, 1},
        {60, 14, 1, -1},
        {61, 13, -1, -1},
        {62, 8, -1, 1},
        {62, 10, -1, -1},
        {60, 8, 1, 1},
        {61, 9, -1, 1},
        {56, 14, 1, -1},
        {56, 12, 1, 1},
        {58, 14, -1, -1},
        {57, 13, 1, -1},
        {60, 12, -1, -1},
        {60, 10, -1, 1},
        {58, 12, 1, -1},
        {59, 11, -1, -1},
        {48, 0, 1, 1},
        {48, 2, 1, -1},
        {50, 0, -1, 1},
        {49, 1, 1, 1},
        {48, 6, 1, -1},
        {48, 4, 1, 1},
        {50, 6, -1, -1},
        {49, 5, 1, -1},
        {54, 0, -1, 1},
        {54, 2, -1, -1},
        {52, 0, 1, 1},
        {53, 1, -1, 1},
        {50, 2, 1, 1},
        {50, 4, 1, -1},
        {52, 2, -1, 1},
        {51, 3, 1, 1},
        {58, 4, -1, 1},
        {58, 6, -1, -1},
        {56, 4, 1, 1},
        {57, 5, -1, 1},
        {58, 10, -1, -1},
        {58, 8, -1, 1},
        {56, 10, 1, -1},
        {57, 9, -1, -1},
        {52, 4, 1, 1},
        {52, 6, 1, -1},
        {54, 4, -1, 1},
        {53, 5, 1, 1},
        {56, 6, -1, 1},
        {56, 8, -1, -1},
        {54, 6, 1, 1},
        {55, 7, -1, 1},
        {62, 30, -1, -1},
        {62, 28, -1, 1},
        {60, 30, 1, -1},
        {61, 29, -1, -1},
        {62, 24, -1, 1},
        {62, 26, -1, -1},
        {60, 24, 1, 1},
        {61, 25, -1, 1},
        {56, 30, 1, -1},
        {56, 28, 1, 1},
        {58, 30, -1, -1},
        {57, 29, 1, -1},
        {60, 28, -1, -1},
        {60, 26, -1, 1},
        {58, 28, 1, -1},
        {59, 27, -1, -1},
        {62, 16, -1, 1},
        {62, 18, -1, -1},
        {60, 16, 1, 1},
        {61, 17, -1, 1},
        {62, 22, -1, -1},
        {62, 20, -1, 1},
        {60, 22, 1, -1},
        {61, 21, -1, -1},
        {56, 16, 1, 1},
        {56, 18, 1, -1},
        {58, 16, -1, 1},
        {57, 17, 1, 1},
        {60, 18, -1, 1},
        {60, 20, -1, -1},
        {58, 18, 1, 1},
        {59, 19, -1, 1},
        {48, 30, 1, -1},
        {48, 28, 1, 1},
        {50, 30, -1, -1},
        {49, 29, 1, -1},
        {48, 24, 1, 1},
        {48, 26, 1, -1},
        {50, 24, -1, 1},
        {49, 25, 1, 1},
        {54, 30, -1, -1},
        {54, 28, -1, 1},
        {52, 30, 1, -1},
        {53, 29, -1, -1},
        {50, 28, 1, -1},
        {50, 26, 1, 1},
        {52, 28, -1, -1},
        {51, 27, 1, -1},
        {58, 26, -1, -1},
        {58, 24, -1, 1},
        {56, 26, 1, -1},
        {57, 25, -1, -1},
        {58, 20, -1, 1},
        {58, 22, -1, -1},
        {56, 20, 1, 1},
        {57, 21, -1, 1},
        {52, 26, 1, -1},
        {52, 24, 1, 1},
        {54, 26, -1, -1},
        {53, 25, 1, -1},
        {56, 24, -1, -1},
        {56, 22, -1, 1},
        {54, 24, 1, -1},
        {55, 23, -1, -1},
        {32, 0, 1, 1},
        {32, 2, 1, -1},
        {34, 0, -1, 1},
        {33, 1, 1, 1},
        {32, 6, 1, -1},
        {32, 4, 1, 1},
        {34, 6, -1, -1},
        {33, 5, 1, -1},
        {38, 0, -1, 1},
        {38, 2, -1, -1},
        {36, 0, 1, 1},
        {37, 1, -1, 1},
        {34, 2, 1, 1},
        {34, 4, 1, -1},
        {36, 2, -1, 1},
        {35, 3, 1, 1},
        {32, 14, 1, -1},
        {32, 12, 1, 1},
        {34, 14, -1, -1},
        {33, 13, 1, -1},
        {32, 8, 1, 1},
        {32, 10, 1, -1},
        {34, 8, -1, 1},
        {33, 9, 1, 1},
        {38, 14, -1, -1},
        {38, 12, -1, 1},
        {36, 14, 1, -1},
        {37, 13, -1, -1},
        {34, 12, 1, -1},
        {34, 10, 1, 1},
        {36, 12, -1, -1},
        {35, 11, 1, -1},
        {46, 0, -1, 1},
        {46, 2, -1, -1},
        {44, 0, 1, 1},
        {45, 1, -1, 1},
        {46, 6, -1, -1},
        {46, 4, -1, 1},
        {44, 6, 1, -1},
        {45, 5, -1, -1},
        {40, 0, 1, 1},
        {40, 2, 1, -1},
        {42, 0, -1, 1},
        {41, 1, 1, 1},
        {44, 2, -1, 1},
        {44, 4, -1, -1},
        {42, 2, 1, 1},
        {43, 3, -1, 1},
        {36, 4, 1, 1},
        {36, 6, 1, -1},
        {38, 4, -1, 1},
        {37, 5, 1, 1},
        {36, 10, 1, -1},
        {36, 8, 1, 1},
        {38, 10, -1, -1},
        {37, 9, 1, -1},
        {42, 4, -1, 1},
        {42, 6, -1, -1},
        {40, 4, 1, 1},
        {41, 5, -1, 1},
        {38, 6, 1, 1},
        {38, 8, 1, -1},
        {40, 6, -1, 1},
        {39, 7, 1, 1},
        {54, 8, -1, 1},
        {54, 10, -1, -1},
        {52, 8, 1, 1},
        {53, 9, -1, 1},
        {54, 14, -1, -1},
        {54, 12, -1, 1},
        {52, 14, 1, -1},
        {53, 13, -1, -1},
        {48, 8, 1, 1},
        {48, 10, 1, -1},
        {50, 8, -1, 1},
        {49, 9, 1, 1},
        {52, 10, -1, 1},
        {52, 12, -1, -1},
        {50, 10, 1, 1},
        {51, 11, -1, 1},
        {54, 22, -1, -1},
        {54, 20, -1, 1},
        {52, 22, 1, -1},
        {53, 21, -1, -1},
        {54, 16, -1, 1},
        {54, 18, -1, -1},
        {52, 16, 1, 1},
        {53, 17, -1, 1},
        {48, 22, 1, -1},
        {48, 20, 1, 1},
        {50, 22, -1, -1},
        {49, 21, 1, -1},
        {52, 20, -1, -1},
        {52, 18, -1, 1},
        {50, 20, 1, -1},
        {51, 19, -1, -1},
        {40, 8, 1, 1},
        {40, 10, 1, -1},
        {42, 8, -1, 1},
        {41, 9, 1, 1},
        {40, 14, 1, -1},
        {40, 12, 1, 1},
        {42, 14, -1, -1},
        {41, 13, 1, -1},
        {46, 8, -1, 1},
        {46, 10, -1, -1},
        {44, 8, 1, 1},
        {45, 9, -1, 1},
        {42, 10, 1, 1},
        {42, 12, 1, -1},
        {44, 10, -1, 1},
        {43, 11, 1, 1},
        {50, 12, -1, 1},
        {50, 14, -1, -1},
        {48, 12, 1, 1},
        {49, 13, -1, 1},
        {50, 18, -1, -1},
        {50, 16, -1, 1},
        {48, 18, 1, -1},
        {49, 17, -1, -1},
        {44, 12, 1, 1},
        {44, 14, 1, -1},
        {46, 12, -1, 1},
        {45, 13, 1, 1},
        {48, 14, -1, 1},
        {48, 16, -1, -1},
        {46, 14, 1, 1},
        {47, 15, -1, 1},
        {16, 16, 1, 1},
        {16, 18, 1, -1},
        {18, 16, -1, 1},
        {17, 17, 1, 1},
        {16, 22, 1, -1},
        {16, 20, 1, 1},
        {18, 22, -1, -1},
        {17, 21, 1, -1},
        {22, 16, -1, 1},
        {22, 18, -1, -1},
        {20, 16, 1, 1},
        {21, 17, -1, 1},
        {18, 18, 1, 1},
        {18, 20, 1, -1},
        {20, 18, -1, 1},
        {19, 19, 1, 1},
        {16, 30, 1, -1},
        {16, 28, 1, 1},
        {18, 30, -1, -1},
        {17, 29, 1, -1},
        {16, 24, 1, 1},
        {16, 26, 1, -1},
        {18, 24, -1, 1},
        {17, 25, 1, 1},
        {22, 30, -1, -1},
        {22, 28, -1, 1},
        {20, 30, 1, -1},
        {21, 29, -1, -1},
        {18, 28, 1, -1},
        {18, 26, 1, 1},
        {20, 28, -1, -1},
        {19, 27, 1, -1},
        {30, 16, -1, 1},
        {30, 18, -1, -1},
        {28, 16, 1, 1},
        {29, 17, -1, 1},
        {30, 22, -1, -1},
        {30, 20, -1, 1},
        {28, 22, 1, -1},
        {29, 21, -1, -1},
        {24, 16, 1, 1},
        {24, 18, 1, -1},
        {26, 16, -1, 1},
        {25, 17, 1, 1},
        {28, 18, -1, 1},
        {28, 20, -1, -1},
        {26, 18, 1, 1},
        {27, 19, -1, 1},
        {20, 20, 1, 1},
        {20, 22, 1, -1},
        {22, 20, -1, 1},
        {21, 21, 1, 1},
        {20, 26, 1, -1},
        {20, 24, 1, 1},
        {22, 26, -1, -1},
        {21, 25, 1, -1},
        {26, 20, -1, 1},
        {26, 22, -1, -1},
        {24, 20, 1, 1},
        {25, 21, -1, 1},
        {22, 22, 1, 1},
        {22, 24, 1, -1},
        {24, 22, -1, 1},
        {23, 23, 1, 1},
        {16, 46, 1, -1},
        {16, 44, 1, 1},
        {18, 46, -1, -1},
        {17, 45, 1, -1},
        {16, 40, 1, 1},
        {16, 42, 1, -1},
        {18, 40, -1, 1},
        {17, 41, 1, 1},
        {22, 46, -1, -1},
        {22, 44, -1, 1},
        {20, 46, 1, -1},
        {21, 45, -1, -1},
        {18, 44, 1, -1},
        {18, 42, 1, 1},
        {20, 44, -1, -1},
        {19, 43, 1, -1},
        {16, 32, 1, 1},
        {16, 34, 1, -1},
        {18, 32, -1, 1},
        {17, 33, 1, 1},
        {16, 38, 1, -1},
        {16, 36, 1, 1},
        {18, 38, -1, -1},
        {17, 37, 1, -1},
        {22, 32, -1, 1},
        {22, 34, -1, -1},
        {20, 32, 1, 1},
        {21, 33, -1, 1},
        {18, 34, 1, 1},
        {18, 36, 1, -1},
        {20, 34, -1, 1},
        {19, 35, 1, 1},
        {30, 46, -1, -1},
        {30, 44, -1, 1},
        {28, 46, 1, -1},
        {29, 45, -1, -1},
        {30, 40, -1, 1},
        {30, 42, -1, -1},
        {28, 40, 1, 1},
        {29, 41, -1, 1},
        {24, 46, 1, -1},
        {24, 44, 1, 1},
        {26, 46, -1, -1},
        {25, 45, 1, -1},
        {28, 44, -1, -1},
        {28, 42, -1, 1},
        {26, 44, 1, -1},
        {27, 43, -1, -1},
        {20, 42, 1, -1},
        {20, 40, 1, 1},
        {22, 42, -1, -1},
        {21, 41, 1, -1},
        {20, 36, 1, 1},
        {20, 38, 1, -1},
        {22, 36, -1, 1},
        {21, 37, 1, 1},
        {26, 42, -1, -1},
        {26, 40, -1, 1},
        {24, 42, 1, -1},
        {25, 41, -1, -1},
        {22, 40, 1, -1},
        {22, 38, 1, 1},
        {24, 40, -1, -1},
        {23, 39, 1, -1},
        {46, 16, -1, 1},
        {46, 18, -1, -1},
        {44, 16, 1, 1},
        {45, 17, -1, 1},
        {46, 22, -1, -1},
        {46, 20, -1, 1},
        {44, 22, 1, -1},
        {45, 21, -1, -1},
        {40, 16, 1, 1},
        {40, 18, 1, -1},
        {42, 16, -1, 1},
        {41, 17, 1, 1},
        {44, 18, -1, 1},
        {44, 20, -1, -1},
        {42, 18, 1, 1},
        {43, 19, -1, 1},
        {46, 30, -1, -1},
        {46, 28, -1, 1},
        {44, 30, 1, -1},
        {45, 29, -1, -1},
        {46, 24, -1, 1},
        {46, 26, -1, -1},
        {44, 24, 1, 1},
        {45, 25, -1, 1},
        {40, 30, 1, -1},
        {40, 28, 1, 1},
        {42, 30, -1, -1},
        {41, 29, 1, -1},
        {44, 28, -1, -1},
        {44, 26, -1, 1},
        {42, 28, 1, -1},
        {43, 27, -1, -1},
        {32, 16, 1, 1},
        {32, 18, 1, -1},
        {34, 16, -1, 1},
        {33, 17, 1, 1},
        {32, 22, 1, -1},
        {32, 20, 1, 1},
        {34, 22, -1, -1},
        {33, 21, 1, -1},
        {38, 16, -1, 1},
        {38, 18, -1, -1},
        {36, 16, 1, 1},
        {37, 17, -1, 1},
        {34, 18, 1, 1},
        {34, 20, 1, -1},
        {36, 18, -1, 1},
        {35, 19, 1, 1},
        {42, 20, -1, 1},
        {42, 22, -1, -1},
        {40, 20, 1, 1},
        {41, 21, -1, 1},
        {42, 26, -1, -1},
        {42, 24, -1, 1},
        {40, 26, 1, -1},
        {41, 25, -1, -1},
        {36, 20, 1, 1},
        {36, 22, 1, -1},
        {38, 20, -1, 1},
        {37, 21, 1, 1},
        {40, 22, -1, 1},
        {40, 24, -1, -1},
        {38, 22, 1, 1},
        {39, 23, -1, 1},
        {24, 24, 1, 1},
        {24, 26, 1, -1},
        {26, 24, -1, 1},
        {25, 25, 1, 1},
        {24, 30, 1, -1},
        {24, 28, 1, 1},
        {26, 30, -1, -1},
        {25, 29, 1, -1},
        {30, 24, -1, 1},
        {30, 26, -1, -1},
        {28, 24, 1, 1},
        {29, 25, -1, 1},
        {26, 26, 1, 1},
        {26, 28, 1, -1},
        {28, 26, -1, 1},
        {27, 27, 1, 1},
        {24, 38, 1, -1},
        {24, 36, 1, 1},
        {26, 38, -1, -1},
        {25, 37, 1, -1},
        {24, 32, 1, 1},
        {24, 34, 1, -1},
        {26, 32, -1, 1},
        {25, 33, 1, 1},
        {30, 38, -1, -1},
        {30, 36, -1, 1},
        {28, 38, 1, -1},
        {29, 37, -1, -1},
        {26, 36, 1, -1},
        {26, 34, 1, 1},
        {28, 36, -1, -1},
        {27, 35, 1, -1},
        {38, 24, -1, 1},
        {38, 26, -1, -1},
        {36, 24, 1, 1},
        {37, 25, -1, 1},
        {38, 30, -1, -1},
        {38, 28, -1, 1},
        {36, 30, 1, -1},
        {37, 29, -1, -1},
        {32, 24, 1, 1},
        {32, 26, 1, -1},
        {34, 24, -1, 1},
        {33, 25, 1, 1},
        {36, 26, -1, 1},
        {36, 28, -1, -1},
        {34, 26, 1, 1},
        {35, 27, -1, 1},
        {28, 28, 1, 1},
        {28, 30, 1, -1},
        {30, 28, -1, 1},
        {29, 29, 1, 1},
        {28, 34, 1, -1},
        {28, 32, 1, 1},
        {30, 34, -1, -1},
        {29, 33, 1, -1},
        {34, 28, -1, 1},
        {34, 30, -1, -1},
        {32, 28, 1, 1},
        {33, 29, -1, 1},
        {30, 30, 1, 1},
        {30, 32, 1, -1},
        {32, 30, -1, 1},
        {31, 31, 1, 1},
    }};
// clang-format on

} // namespace

BOOST_AUTO_TEST_SUITE(tromino_64x64_test_suite)

BOOST_AUTO_TEST_CASE(
    Given_trmn_solve_puzzle_WhenOrderIs64AndMarkIs61_37_ThenSolution) {
    constexpr int order{64};
    constexpr int mark_x{61};
    constexpr int mark_y{37};

    std::vector<ShimStep> actual;
    actual.reserve(std::size_t{1365});

    ::trmn_solve_puzzle(order, mark_x, mark_y, shim_add_tromino, &actual);

    BOOST_CHECK_EQUAL(actual.size(), std::size_t{1365});
    BOOST_CHECK_EQUAL_COLLECTIONS(
        actual.begin(), actual.end(),
        g_expected_for_order_64_and_mark_61_37.begin(),
        g_expected_for_order_64_and_mark_61_37.end());
}

BOOST_AUTO_TEST_SUITE_END()
