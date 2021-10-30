// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <boost/test/unit_test.hpp>

#include "unittest_helper.h"

#include "tromino.h"

BOOST_AUTO_TEST_SUITE(tromino_2x2_test_suite)

//
// X |
// - +
BOOST_AUTO_TEST_CASE(GivenK2_WhenTopLeft_ThenSolutionIsK)
{
    constexpr int order = 2;
    constexpr trmn_position_t mark = { 0, 0 };

    const std::vector<ShimStep> expected = {{{0, 0}, {-1, -1}}};
    std::vector<ShimStep> actual;

    trmn_solve_puzzle(order, mark, shim_add_tromino, &actual);

    BOOST_CHECK_EQUAL(actual.size(), 1);
    BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(), expected.begin(), expected.end());
}

//
// | X
// + -
BOOST_AUTO_TEST_CASE(GivenL2_WhenTopRight_ThenSolutionIsL)
{
    constexpr int order = 2;
    constexpr trmn_position_t mark = { 1, 0 };

    const std::vector<ShimStep> expected = {{{0, 0}, {1, -1}}};
    std::vector<ShimStep> actual;

    trmn_solve_puzzle(order, mark, shim_add_tromino, &actual);

    BOOST_CHECK_EQUAL(actual.size(), 1);
    BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(), expected.begin(), expected.end());
}

//
// - +
// X |
BOOST_AUTO_TEST_CASE(GivenM2_WhenBottomLeft_ThenSolutionIsM)
{
    constexpr int order = 2;
    constexpr trmn_position_t mark = { 0, 1 };

    const std::vector<ShimStep> expected = {{{0, 0}, {-1, 1}}};
    std::vector<ShimStep> actual;

    trmn_solve_puzzle(order, mark, shim_add_tromino, &actual);

    BOOST_CHECK_EQUAL(actual.size(), 1);
    BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(), expected.begin(), expected.end());
}

//
// + -
// | X
BOOST_AUTO_TEST_CASE(GivenN2_WhenBottomRight_ThenSolutionIsN)
{
    constexpr int order = 2;
    constexpr trmn_position_t mark = { 1, 1 };

    const std::vector<ShimStep> expected = {{{0, 0}, {1, 1}}};
    std::vector<ShimStep> actual;

    trmn_solve_puzzle(order, mark, shim_add_tromino, &actual);

    BOOST_CHECK_EQUAL(actual.size(), 1);
    BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_SUITE_END()
