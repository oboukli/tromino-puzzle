// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <cstddef>
#include <vector>

#include <boost/test/unit_test.hpp>

#include <tromino/core/tromino.h>

#include "unittest_helper.hpp"

BOOST_AUTO_TEST_SUITE(tromino_2x2_test_suite)

using boost::unit_test::label;

//
// X |
// - +
BOOST_AUTO_TEST_CASE(GivenK2_WhenTopLeft_ThenSolutionIsK, *label("core"))
{
    static constexpr int const order{2};
    static constexpr int const mark_x{0};
    static constexpr int const mark_y{0};
    int const stop_flag{0};

    static constexpr std::array<ShimStep, std::size_t{1}> const expected{
        {{0, 0, -1, -1}}};
    std::vector<ShimStep> actual{};

    ::trmn_solve_puzzle(
        order, mark_x, mark_y, shim_add_tromino, &actual, &stop_flag);

    BOOST_WARN_EQUAL(actual.size(), std::size_t{1});
    BOOST_CHECK_EQUAL_COLLECTIONS(
        actual.cbegin(), actual.cend(), expected.cbegin(), expected.cend());
}

//
// | X
// + -
BOOST_AUTO_TEST_CASE(GivenL2_WhenTopRight_ThenSolutionIsL, *label("core"))
{
    static constexpr int const order{2};
    static constexpr int const mark_x{1};
    static constexpr int const mark_y{0};
    int const stop_flag{0};

    static constexpr std::array<ShimStep, std::size_t{1}> const expected{
        {{0, 0, 1, -1}}};
    std::vector<ShimStep> actual{};

    ::trmn_solve_puzzle(
        order, mark_x, mark_y, shim_add_tromino, &actual, &stop_flag);

    BOOST_WARN_EQUAL(actual.size(), std::size_t{1});
    BOOST_CHECK_EQUAL_COLLECTIONS(
        actual.cbegin(), actual.cend(), expected.cbegin(), expected.cend());
}

//
// - +
// X |
BOOST_AUTO_TEST_CASE(GivenM2_WhenBottomLeft_ThenSolutionIsM, *label("core"))
{
    static constexpr int const order{2};
    static constexpr int const mark_x{0};
    static constexpr int const mark_y{1};
    int const stop_flag{0};

    static constexpr std::array<ShimStep, std::size_t{1}> const expected{
        {{0, 0, -1, 1}}};
    std::vector<ShimStep> actual{};

    ::trmn_solve_puzzle(
        order, mark_x, mark_y, shim_add_tromino, &actual, &stop_flag);

    BOOST_WARN_EQUAL(actual.size(), std::size_t{1});
    BOOST_CHECK_EQUAL_COLLECTIONS(
        actual.cbegin(), actual.cend(), expected.cbegin(), expected.cend());
}

//
// + -
// | X
BOOST_AUTO_TEST_CASE(GivenN2_WhenBottomRight_ThenSolutionIsN, *label("core"))
{
    static constexpr int const order{2};
    static constexpr int const mark_x{1};
    static constexpr int const mark_y{1};
    int const stop_flag{0};

    static constexpr std::array<ShimStep, std::size_t{1}> const expected{
        {{0, 0, 1, 1}}};
    std::vector<ShimStep> actual{};

    ::trmn_solve_puzzle(
        order, mark_x, mark_y, shim_add_tromino, &actual, &stop_flag);

    BOOST_WARN_EQUAL(actual.size(), std::size_t{1});
    BOOST_CHECK_EQUAL_COLLECTIONS(
        actual.cbegin(), actual.cend(), expected.cbegin(), expected.cend());
}

BOOST_AUTO_TEST_SUITE_END()
