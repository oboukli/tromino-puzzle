// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <boost/test/unit_test.hpp>

#include "unittest_helper.h"

#include "tromino.h"

BOOST_AUTO_TEST_SUITE(tromino_4x4_test_suite)

//
// X | - +
// - + | |
// | - + |
// + - - +
BOOST_AUTO_TEST_CASE(Given_trmn_solve_puzzle_WhenOrderIs4AndMarkIs0_0_ThenSolution)
{
    constexpr int order = 4;
    constexpr trmn_position_t mark = { 0, 0 };

    const std::vector<ShimStep> expected = {
        { { 0, 0 }, { -1, -1 } },
        { { 2, 2 }, { -1, -1 } },
        { { 2, 0 }, { -1, 1 } },
        { { 0, 2 }, { 1, -1 } },
        { { 1, 1 }, { -1, -1 } },
    };
    std::vector<ShimStep> actual;

    trmn_solve_puzzle(order, mark, shim_add_tromino, &actual);

    BOOST_CHECK_EQUAL(actual.size(), 5);
    BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(Given_trmn_solve_puzzle_WhenOrderIs4AndMarkIs0_7_ThenSolution)
{
    constexpr int order = 4;
    constexpr trmn_position_t mark = { 0, 7 };

    const std::vector<ShimStep> expected = {
        { { 0, 2 }, { -1, 1 } },
        { { 2, 0 }, { -1, 1 } },
        { { 2, 2 }, { -1, -1 } },
        { { 0, 0 }, { 1, 1 } },
        { { 1, 1 }, { -1, 1 } },
    };
    std::vector<ShimStep> actual;

    trmn_solve_puzzle(order, mark, shim_add_tromino, &actual);

    BOOST_CHECK_EQUAL(actual.size(), 5);
    BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(Given_trmn_solve_puzzle_WhenOrderIs4AndMarkIs7_0_ThenSolution)
{
    constexpr int order = 4;
    constexpr trmn_position_t mark = { 7, 0 };

    const std::vector<ShimStep> expected = {
        { { 2, 0 }, { 1, -1 } },
        { { 0, 2 }, { 1, -1 } },
        { { 0, 0 }, { 1, 1 } },
        { { 2, 2 }, { -1, -1 } },
        { { 1, 1 }, { 1, -1 } },
    };
    std::vector<ShimStep> actual;

    trmn_solve_puzzle(order, mark, shim_add_tromino, &actual);

    BOOST_CHECK_EQUAL(actual.size(), 5);
    BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(Given_trmn_solve_puzzle_WhenOrderIs4AndMarkIs7_7_ThenSolution)
{
    constexpr int order = 4;
    constexpr trmn_position_t mark = { 7, 7 };

    const std::vector<ShimStep> expected = {
        { { 2, 2 }, { 1, 1 } },
        { { 0, 0 }, { 1, 1 } },
        { { 0, 2 }, { 1, -1 } },
        { { 2, 0 }, { -1, 1 } },
        { { 1, 1 }, { 1, 1 } },
    };
    std::vector<ShimStep> actual;

    trmn_solve_puzzle(order, mark, shim_add_tromino, &actual);

    BOOST_CHECK_EQUAL(actual.size(), 5);
    BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(), expected.begin(), expected.end());
}

//
// + - - +
// | + - |
// | | | X
// + - + -
BOOST_AUTO_TEST_CASE(Given_trmn_solve_puzzle_WhenOrderIs4AndMarkIs3_2_ThenSolution)
{
    constexpr int order = 4;
    constexpr trmn_position_t mark = { 3, 2 };

    std::vector<ShimStep> expected = {
        { { 2, 2 }, { 1, -1 } },
        { { 0, 0 }, { 1, 1 } },
        { { 0, 2 }, { 1, -1 } },
        { { 2, 0 }, { -1, 1 } },
        { { 1, 1 }, { 1, 1 } },
    };
    std::vector<ShimStep> actual;

    trmn_solve_puzzle(order, mark, shim_add_tromino, &actual);

    BOOST_CHECK_EQUAL(actual.size(), 5);
    BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_SUITE_END()
