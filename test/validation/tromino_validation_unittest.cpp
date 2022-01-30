// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <boost/test/unit_test.hpp>

#include "tromino_validation.h"

#include <climits>
#include <cmath>

BOOST_AUTO_TEST_SUITE(trmn_is_valid_order_test_suite)

BOOST_AUTO_TEST_CASE(Given_trmn_is_valid_order_WhenValidOrder_ThenTrue) {
    const bool is_valid = ::trmn_is_valid_order(0x40000000);

    BOOST_TEST(is_valid == true);
}

BOOST_AUTO_TEST_CASE(Given_trmn_is_valid_order_WhenOrder64_ThenTrue) {
    const bool is_valid = ::trmn_is_valid_order(64);

    BOOST_TEST(is_valid == true);
}

BOOST_AUTO_TEST_CASE(Given_trmn_is_valid_order_WhenNegativeOrder_ThenFalse) {
    const bool is_valid = ::trmn_is_valid_order(-2);

    BOOST_TEST(is_valid == false);
}

BOOST_AUTO_TEST_CASE(Given_trmn_is_valid_order_WhenOrder0_ThenFalse) {
    const bool is_valid = ::trmn_is_valid_order(0);

    BOOST_TEST(is_valid == false);
}

BOOST_AUTO_TEST_CASE(Given_trmn_is_valid_order_WhenOrder1_ThenFalse) {
    const bool is_valid = ::trmn_is_valid_order(1);

    BOOST_TEST(is_valid == false);
}

BOOST_AUTO_TEST_CASE(Given_trmn_is_valid_order_WhenOrder3_ThenFalse) {
    const bool is_valid = ::trmn_is_valid_order(3);

    BOOST_TEST(is_valid == false);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(trmn_is_valid_coordinate_test_suite)

BOOST_AUTO_TEST_CASE(Given_trmn_is_valid_coordinate_WhenValid_ThenTrue) {
    const bool is_valid = ::trmn_is_valid_coordinate(0, 2);

    BOOST_TEST(is_valid == true);
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_is_valid_coordinate_WhenBelowLowerBound_ThenFalse) {
    const bool is_valid = ::trmn_is_valid_coordinate(-1, 2);

    BOOST_TEST(is_valid == false);
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_is_valid_coordinate_WhenAboveUpperBound_ThenFalse) {
    const bool is_valid = ::trmn_is_valid_coordinate(2, 2);

    BOOST_TEST(is_valid == false);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(trmn_is_order_overflow_safe_test_suite)

BOOST_AUTO_TEST_CASE(
    Given_trmn_is_order_overflow_safe_WhenSafeInteger_ThenTrue) {
    const bool is_valid = ::trmn_is_order_overflow_safe(2);

    BOOST_TEST(is_valid == true);
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_is_order_overflow_safe_WhenUnsafeInteger_ThenFalse) {
    bool is_valid = ::trmn_is_order_overflow_safe(0x40000000);

    BOOST_TEST(is_valid == false);
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_is_order_overflow_safe_WhenMaxSafeOrder_ThenTrue) {
    const int maxSafeOrder = std::sqrt(INT_MAX);

    bool is_valid = ::trmn_is_order_overflow_safe(maxSafeOrder);

    BOOST_TEST(is_valid == true);
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_is_order_overflow_safe_WhenMinUnsafeOrder_ThenFalse) {
    const int maxSafeOrder = std::sqrt(INT_MAX) + 1;

    bool is_valid = ::trmn_is_order_overflow_safe(maxSafeOrder);

    BOOST_TEST(is_valid == false);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(trmn_is_valid_config_test_suite)

BOOST_AUTO_TEST_CASE(Given_trmn_is_valid_config_WhenValid_ThenTrue) {
    const bool is_valid = ::trmn_is_valid_config(2, 0, 0);

    BOOST_TEST(is_valid == true);
}

BOOST_AUTO_TEST_CASE(Given_trmn_is_valid_config_WhenInvalidOrder_ThenFalse) {
    const bool is_valid = ::trmn_is_valid_config(0, 0, 0);

    BOOST_TEST(is_valid == false);
}

BOOST_AUTO_TEST_CASE(Given_trmn_is_valid_config_WhenUnsafeOrder_ThenFalse) {
    const bool is_valid = ::trmn_is_valid_config(INT_MAX, 0, 0);

    BOOST_TEST(is_valid == false);
}

BOOST_AUTO_TEST_CASE(Given_trmn_is_valid_config_WhenInvalidMarkX_ThenFalse) {
    const bool is_valid = ::trmn_is_valid_config(4, 11, 0);

    BOOST_TEST(is_valid == false);
}

BOOST_AUTO_TEST_CASE(Given_trmn_is_valid_config_WhenInvalidMarkY_ThenFalse) {
    const bool is_valid = ::trmn_is_valid_config(4, 0, 11);

    BOOST_TEST(is_valid == false);
}

BOOST_AUTO_TEST_SUITE_END()
