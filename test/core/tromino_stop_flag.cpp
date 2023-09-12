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

namespace {

struct ShimState {
    std::vector<ShimStep>* shim_steps{nullptr};
    int* stop_flag{nullptr};
};

void shim_stopping_add_tromino(
    int const pos_x,
    int const pos_y,
    int const flip_x,
    int const flip_y,
    void* const state) noexcept
{
    ShimState* shim_state{static_cast<ShimState*>(state)};
    if (shim_state->shim_steps->size() == std::size_t{15})
    {
        *shim_state->stop_flag = 1;
    }
    shim_state->shim_steps->emplace_back(pos_x, pos_y, flip_x, flip_y);
}

} // namespace

BOOST_AUTO_TEST_SUITE(tromino_stop_test_suite)

BOOST_AUTO_TEST_CASE(
    Given_trmn_solve_puzzle_WhenStopFlagIsSetBeforeComputation_ThenDoNotCompute)
{
    static constexpr int const order{64};
    static constexpr int const mark_x{61};
    static constexpr int const mark_y{37};
    int const stop_flag{1};

    static constexpr std::array<ShimStep, std::size_t{0}> const expected{{}};

    std::vector<ShimStep> actual_steps{};

    ::trmn_solve_puzzle(
        order, mark_x, mark_y, shim_add_tromino, &actual_steps, &stop_flag);

    BOOST_CHECK_EQUAL(actual_steps.size(), std::size_t{0});
    BOOST_CHECK_EQUAL_COLLECTIONS(
        actual_steps.cbegin(),
        actual_steps.cend(),
        expected.cbegin(),
        expected.cend());
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_solve_puzzle_WhenStopFlagIsSetDuringComputation_ThenStop)
{
    static constexpr int const order{64};
    static constexpr int const mark_x{61};
    static constexpr int const mark_y{37};
    int stop_flag{0};

    static constexpr std::array<ShimStep, std::size_t{16}> const expected{{
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
    }};

    std::vector<ShimStep> actual_steps{};
    ShimState actual{
        .shim_steps = &actual_steps,
        .stop_flag = &stop_flag,
    };

    ::trmn_solve_puzzle(
        order, mark_x, mark_y, shim_stopping_add_tromino, &actual, &stop_flag);

    BOOST_CHECK_EQUAL(actual_steps.size(), std::size_t{16});
    BOOST_CHECK_EQUAL(stop_flag, 1);
    BOOST_CHECK_EQUAL_COLLECTIONS(
        actual_steps.cbegin(),
        actual_steps.cend(),
        expected.cbegin(),
        expected.cend());
}

BOOST_AUTO_TEST_SUITE_END()
