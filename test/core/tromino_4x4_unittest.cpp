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

BOOST_AUTO_TEST_SUITE(tromino_4x4_test_suite)

using boost::unit_test::label;

//
// X | - +
// - + | |
// | - + |
// + - - +
BOOST_AUTO_TEST_CASE(
    Given_trmn_solve_puzzle_WhenOrderIs4AndMarkIs0_0_ThenSolution,
    *label("core"))
{
    static constexpr int const order{4};
    static constexpr int const mark_x{0};
    static constexpr int const mark_y{0};
    int const stop_flag{0};

    static constexpr std::array<ShimStep, std::size_t{5}> const expected{{
        {0, 0, -1, -1},
        {2, 2, -1, -1},
        {2, 0, -1, 1},
        {0, 2, 1, -1},
        {1, 1, -1, -1},
    }};

    std::vector<ShimStep> actual{};

    ::trmn_solve_puzzle(
        order, mark_x, mark_y, shim_add_tromino, &actual, &stop_flag);

    BOOST_WARN_EQUAL(actual.size(), std::size_t{5});
    BOOST_CHECK_EQUAL_COLLECTIONS(
        actual.cbegin(), actual.cend(), expected.cbegin(), expected.cend());
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_solve_puzzle_WhenOrderIs4AndMarkIs0_7_ThenSolution,
    *label("core"))
{
    static constexpr int const order{4};
    static constexpr int const mark_x{0};
    static constexpr int const mark_y{7};
    int const stop_flag{0};

    static constexpr std::array<ShimStep, std::size_t{5}> const expected{{
        {0, 2, -1, 1},
        {2, 0, -1, 1},
        {2, 2, -1, -1},
        {0, 0, 1, 1},
        {1, 1, -1, 1},
    }};

    std::vector<ShimStep> actual{};

    ::trmn_solve_puzzle(
        order, mark_x, mark_y, shim_add_tromino, &actual, &stop_flag);

    BOOST_WARN_EQUAL(actual.size(), std::size_t{5});
    BOOST_CHECK_EQUAL_COLLECTIONS(
        actual.cbegin(), actual.cend(), expected.cbegin(), expected.cend());
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_solve_puzzle_WhenOrderIs4AndMarkIs7_0_ThenSolution,
    *label("core"))
{
    static constexpr int const order{4};
    static constexpr int const mark_x{7};
    static constexpr int const mark_y{0};
    int const stop_flag{0};

    static constexpr std::array<ShimStep, std::size_t{5}> const expected{{
        {2, 0, 1, -1},
        {0, 2, 1, -1},
        {0, 0, 1, 1},
        {2, 2, -1, -1},
        {1, 1, 1, -1},
    }};

    std::vector<ShimStep> actual{};

    ::trmn_solve_puzzle(
        order, mark_x, mark_y, shim_add_tromino, &actual, &stop_flag);

    BOOST_WARN_EQUAL(actual.size(), std::size_t{5});
    BOOST_CHECK_EQUAL_COLLECTIONS(
        actual.cbegin(), actual.cend(), expected.cbegin(), expected.cend());
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_solve_puzzle_WhenOrderIs4AndMarkIs7_7_ThenSolution,
    *label("core"))
{
    static constexpr int const order{4};
    static constexpr int const mark_x{7};
    static constexpr int const mark_y{7};
    int const stop_flag{0};

    static constexpr std::array<ShimStep, std::size_t{5}> const expected{{
        {2, 2, 1, 1},
        {0, 0, 1, 1},
        {0, 2, 1, -1},
        {2, 0, -1, 1},
        {1, 1, 1, 1},
    }};

    std::vector<ShimStep> actual{};

    ::trmn_solve_puzzle(
        order, mark_x, mark_y, shim_add_tromino, &actual, &stop_flag);

    BOOST_WARN_EQUAL(actual.size(), std::size_t{5});
    BOOST_CHECK_EQUAL_COLLECTIONS(
        actual.cbegin(), actual.cend(), expected.cbegin(), expected.cend());
}

//
// + - - +
// | + - |
// | | | X
// + - + -
BOOST_AUTO_TEST_CASE(
    Given_trmn_solve_puzzle_WhenOrderIs4AndMarkIs3_2_ThenSolution,
    *label("core"))
{
    static constexpr int const order{4};
    static constexpr int const mark_x{3};
    static constexpr int const mark_y{2};
    int const stop_flag{0};

    static constexpr std::array<ShimStep, std::size_t{5}> const expected{{
        {2, 2, 1, -1},
        {0, 0, 1, 1},
        {0, 2, 1, -1},
        {2, 0, -1, 1},
        {1, 1, 1, 1},
    }};

    std::vector<ShimStep> actual{};

    ::trmn_solve_puzzle(
        order, mark_x, mark_y, shim_add_tromino, &actual, &stop_flag);

    BOOST_WARN_EQUAL(actual.size(), std::size_t{5});
    BOOST_CHECK_EQUAL_COLLECTIONS(
        actual.cbegin(), actual.cend(), expected.cbegin(), expected.cend());
}

BOOST_AUTO_TEST_SUITE_END()
