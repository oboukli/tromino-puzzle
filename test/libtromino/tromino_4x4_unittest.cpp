// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <cstddef>
#include <vector>

#include <boost/test/unit_test.hpp>

#include "tromino.h"

#include "unittest_helper.h"

BOOST_AUTO_TEST_SUITE(tromino_4x4_test_suite)

//
// X | - +
// - + | |
// | - + |
// + - - +
BOOST_AUTO_TEST_CASE(
    Given_trmn_solve_puzzle_WhenOrderIs4AndMarkIs0_0_ThenSolution) {
    constexpr int order{4};
    constexpr int mark_x{0};
    constexpr int mark_y{0};

    // clang-format off
    constexpr std::array<ShimStep, std::size_t{5}> expected{{
        {0, 0, -1, -1},
        {2, 2, -1, -1},
        {2, 0, -1, 1},
        {0, 2, 1, -1},
        {1, 1, -1, -1},
    }};
    // clang-format on

    std::vector<ShimStep> actual;

    ::trmn_solve_puzzle(order, mark_x, mark_y, shim_add_tromino, &actual);

    BOOST_CHECK_EQUAL(actual.size(), std::size_t{5});
    BOOST_CHECK_EQUAL_COLLECTIONS(
        actual.begin(), actual.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_solve_puzzle_WhenOrderIs4AndMarkIs0_7_ThenSolution) {
    constexpr int order{4};
    constexpr int mark_x{0};
    constexpr int mark_y{7};

    // clang-format off
    constexpr std::array<ShimStep, std::size_t{5}> expected{{
        {0, 2, -1, 1},
        {2, 0, -1, 1},
        {2, 2, -1, -1},
        {0, 0, 1, 1},
        {1, 1, -1, 1},
    }};
    // clang-format on

    std::vector<ShimStep> actual;

    ::trmn_solve_puzzle(order, mark_x, mark_y, shim_add_tromino, &actual);

    BOOST_CHECK_EQUAL(actual.size(), std::size_t{5});
    BOOST_CHECK_EQUAL_COLLECTIONS(
        actual.begin(), actual.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_solve_puzzle_WhenOrderIs4AndMarkIs7_0_ThenSolution) {
    constexpr int order{4};
    constexpr int mark_x{7};
    constexpr int mark_y{0};

    // clang-format off
    constexpr std::array<ShimStep, std::size_t{5}> expected{{
        {2, 0, 1, -1},
        {0, 2, 1, -1},
        {0, 0, 1, 1},
        {2, 2, -1, -1},
        {1, 1, 1, -1},
    }};
    // clang-format on

    std::vector<ShimStep> actual;

    ::trmn_solve_puzzle(order, mark_x, mark_y, shim_add_tromino, &actual);

    BOOST_CHECK_EQUAL(actual.size(), std::size_t{5});
    BOOST_CHECK_EQUAL_COLLECTIONS(
        actual.begin(), actual.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_solve_puzzle_WhenOrderIs4AndMarkIs7_7_ThenSolution) {
    constexpr int order{4};
    constexpr int mark_x{7};
    constexpr int mark_y{7};

    // clang-format off
    constexpr std::array<ShimStep, std::size_t{5}> expected{{
        {2, 2, 1, 1},
        {0, 0, 1, 1},
        {0, 2, 1, -1},
        {2, 0, -1, 1},
        {1, 1, 1, 1},
    }};
    // clang-format on

    std::vector<ShimStep> actual;

    ::trmn_solve_puzzle(order, mark_x, mark_y, shim_add_tromino, &actual);

    BOOST_CHECK_EQUAL(actual.size(), std::size_t{5});
    BOOST_CHECK_EQUAL_COLLECTIONS(
        actual.begin(), actual.end(), expected.begin(), expected.end());
}

//
// + - - +
// | + - |
// | | | X
// + - + -
BOOST_AUTO_TEST_CASE(
    Given_trmn_solve_puzzle_WhenOrderIs4AndMarkIs3_2_ThenSolution) {
    constexpr int order{4};
    constexpr int mark_x{3};
    constexpr int mark_y{2};

    // clang-format off
    constexpr std::array<ShimStep, std::size_t{5}> expected{{
        {2, 2, 1, -1},
        {0, 0, 1, 1},
        {0, 2, 1, -1},
        {2, 0, -1, 1},
        {1, 1, 1, 1},
    }};
    // clang-format on

    std::vector<ShimStep> actual;

    ::trmn_solve_puzzle(order, mark_x, mark_y, shim_add_tromino, &actual);

    BOOST_CHECK_EQUAL(actual.size(), std::size_t{5});
    BOOST_CHECK_EQUAL_COLLECTIONS(
        actual.begin(), actual.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_SUITE_END()
