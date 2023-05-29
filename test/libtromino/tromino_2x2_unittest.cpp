// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <cstddef>
#include <vector>

#include <boost/test/unit_test.hpp>

#include "tromino.h"

#include "unittest_helper.h"

BOOST_AUTO_TEST_SUITE(tromino_2x2_test_suite)

//
// X |
// - +
BOOST_AUTO_TEST_CASE(GivenK2_WhenTopLeft_ThenSolutionIsK) {
    constexpr int const order{2};
    constexpr int const mark_x{0};
    constexpr int const mark_y{0};

    constexpr const std::array<ShimStep, std::size_t{1}> expected{
        {{0, 0, -1, -1}}};
    std::vector<ShimStep> actual{};

    ::trmn_solve_puzzle(order, mark_x, mark_y, shim_add_tromino, &actual);

    BOOST_CHECK_EQUAL(actual.size(), std::size_t{1});
    BOOST_CHECK_EQUAL_COLLECTIONS(
        actual.begin(), actual.end(), expected.begin(), expected.end());
}

//
// | X
// + -
BOOST_AUTO_TEST_CASE(GivenL2_WhenTopRight_ThenSolutionIsL) {
    constexpr int const order{2};
    constexpr int const mark_x{1};
    constexpr int const mark_y{0};

    constexpr const std::array<ShimStep, std::size_t{1}> expected{
        {{0, 0, 1, -1}}};
    std::vector<ShimStep> actual{};

    ::trmn_solve_puzzle(order, mark_x, mark_y, shim_add_tromino, &actual);

    BOOST_CHECK_EQUAL(actual.size(), std::size_t{1});
    BOOST_CHECK_EQUAL_COLLECTIONS(
        actual.begin(), actual.end(), expected.begin(), expected.end());
}

//
// - +
// X |
BOOST_AUTO_TEST_CASE(GivenM2_WhenBottomLeft_ThenSolutionIsM) {
    constexpr int const order{2};
    constexpr int const mark_x{0};
    constexpr int const mark_y{1};

    constexpr const std::array<ShimStep, std::size_t{1}> expected{
        {{0, 0, -1, 1}}};
    std::vector<ShimStep> actual{};

    ::trmn_solve_puzzle(order, mark_x, mark_y, shim_add_tromino, &actual);

    BOOST_CHECK_EQUAL(actual.size(), std::size_t{1});
    BOOST_CHECK_EQUAL_COLLECTIONS(
        actual.begin(), actual.end(), expected.begin(), expected.end());
}

//
// + -
// | X
BOOST_AUTO_TEST_CASE(GivenN2_WhenBottomRight_ThenSolutionIsN) {
    constexpr int const order{2};
    constexpr int const mark_x{1};
    constexpr int const mark_y{1};

    constexpr const std::array<ShimStep, std::size_t{1}> expected{
        {{0, 0, 1, 1}}};
    std::vector<ShimStep> actual{};

    ::trmn_solve_puzzle(order, mark_x, mark_y, shim_add_tromino, &actual);

    BOOST_CHECK_EQUAL(actual.size(), std::size_t{1});
    BOOST_CHECK_EQUAL_COLLECTIONS(
        actual.begin(), actual.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_SUITE_END()
