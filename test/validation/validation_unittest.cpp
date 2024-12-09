// Copyright (c) Omar Boukli-Hacene. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <boost/test/unit_test.hpp>

#include <tromino/validation/validation.h>

#include <limits>

using boost::unit_test::label;

BOOST_AUTO_TEST_SUITE(trmn_is_valid_order_test_suite)

BOOST_AUTO_TEST_CASE(
    Given_trmn_is_valid_order_WhenMinValidOrder_ThenTrue, *label("validation")
)
{
    bool const is_valid = ::trmn_is_valid_order(2);

    BOOST_TEST(is_valid == true);
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_is_valid_order_WhenMaxValidOrder_ThenTrue, *label("validation")
)
{
    bool const is_valid = ::trmn_is_valid_order(32768);

    BOOST_TEST(is_valid == true);
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_is_valid_order_WhenOrder64_ThenTrue, *label("validation")
)
{
    bool const is_valid = ::trmn_is_valid_order(64);

    BOOST_TEST(is_valid == true);
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_is_valid_order_WhenOrderIsPowerOfTwoButTooLarge_ThenFalse,
    *label("validation")
)
{
    bool const is_valid = ::trmn_is_valid_order(0x40000000);

    BOOST_TEST(is_valid == false);
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_is_valid_order_WhenNegativeOrder_ThenFalse, *label("validation")
)
{
    bool const is_valid = ::trmn_is_valid_order(-2);

    BOOST_TEST(is_valid == false);
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_is_valid_order_WhenOrder0_ThenFalse, *label("validation")
)
{
    bool const is_valid = ::trmn_is_valid_order(0);

    BOOST_TEST(is_valid == false);
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_is_valid_order_WhenOrder1_ThenFalse, *label("validation")
)
{
    bool const is_valid = ::trmn_is_valid_order(1);

    BOOST_TEST(is_valid == false);
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_is_valid_order_WhenOrder3_ThenFalse, *label("validation")
)
{
    bool const is_valid = ::trmn_is_valid_order(3);

    BOOST_TEST(is_valid == false);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(trmn_is_valid_coordinate_test_suite)

BOOST_AUTO_TEST_CASE(
    Given_trmn_is_valid_coordinate_WhenValid_ThenTrue, *label("validation")
)
{
    bool const is_valid = ::trmn_is_valid_coordinate(0, 2);

    BOOST_TEST(is_valid == true);
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_is_valid_coordinate_WhenBelowLowerBound_ThenFalse,
    *label("validation")
)
{
    bool const is_valid = ::trmn_is_valid_coordinate(-1, 2);

    BOOST_TEST(is_valid == false);
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_is_valid_coordinate_WhenAboveUpperBound_ThenFalse,
    *label("validation")
)
{
    bool const is_valid = ::trmn_is_valid_coordinate(2, 2);

    BOOST_TEST(is_valid == false);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(trmn_is_order_overflow_safe_test_suite)

BOOST_AUTO_TEST_CASE(
    Given_trmn_is_order_overflow_safe_WhenSafeInteger_ThenTrue,
    *label("validation")
)
{
    bool const is_valid = ::trmn_is_order_overflow_safe(2);

    BOOST_TEST(is_valid == true);
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_is_order_overflow_safe_WhenNegativeInteger_ThenFalse,
    *label("validation")
)
{
    bool const is_valid = ::trmn_is_order_overflow_safe(-1);

    BOOST_TEST(is_valid == false);
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_is_order_overflow_safe_WhenUnsafeInteger_ThenFalse,
    *label("validation")
)
{
    bool is_valid = ::trmn_is_order_overflow_safe(0x40000000);

    BOOST_TEST(is_valid == false);
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_is_order_overflow_safe_WhenMaxOrder_ThenTrue,
    *label("validation")
)
{
    bool is_valid = ::trmn_is_order_overflow_safe(32768);

    BOOST_TEST(is_valid == true);
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_is_order_overflow_safe_WhenMaxOverflowSafeArgument_ThenTrue,
    *label("validation")
)
{
    bool is_valid = ::trmn_is_order_overflow_safe(46340);

    BOOST_TEST(is_valid == true);
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_is_order_overflow_safe_WhenMinOverflowUnsafeArgument_ThenFalse,
    *label("validation")
)
{
    bool is_valid = ::trmn_is_order_overflow_safe(46341);

    BOOST_TEST(is_valid == false);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(trmn_is_valid_config_test_suite)

BOOST_AUTO_TEST_CASE(
    Given_trmn_is_valid_config_WhenValid_ThenTrue, *label("validation")
)
{
    bool const is_valid = ::trmn_is_valid_config(2, 0, 0);

    BOOST_TEST(is_valid == true);
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_is_valid_config_WhenInvalidOrder_ThenFalse, *label("validation")
)
{
    bool const is_valid = ::trmn_is_valid_config(0, 0, 0);

    BOOST_TEST(is_valid == false);
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_is_valid_config_WhenOrderIs3_ThenFalse, *label("validation")
)
{
    bool const is_valid = ::trmn_is_valid_config(3, 0, 0);

    BOOST_TEST(is_valid == false);
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_is_valid_config_WhenUnsafeOrder_ThenFalse, *label("validation")
)
{
    bool const is_valid
        = ::trmn_is_valid_config(std::numeric_limits<int>::max(), 0, 0);

    BOOST_TEST(is_valid == false);
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_is_valid_config_WhenNegativeOrder_ThenFalse, *label("validation")
)
{
    bool const is_valid = ::trmn_is_valid_config(-1, 0, 0);

    BOOST_TEST(is_valid == false);
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_is_valid_config_WhenInvalidMarkX_ThenFalse, *label("validation")
)
{
    bool const is_valid = ::trmn_is_valid_config(4, 11, 0);

    BOOST_TEST(is_valid == false);
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_is_valid_config_WhenInvalidMarkY_ThenFalse, *label("validation")
)
{
    bool const is_valid = ::trmn_is_valid_config(4, 0, 11);

    BOOST_TEST(is_valid == false);
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_is_valid_config_WhenNegativeMarkX_ThenFalse, *label("validation")
)
{
    bool const is_valid = ::trmn_is_valid_config(4, -1, 0);

    BOOST_TEST(is_valid == false);
}

BOOST_AUTO_TEST_CASE(
    Given_trmn_is_valid_config_WhenNegativeMarkY_ThenFalse, *label("validation")
)
{
    bool const is_valid = ::trmn_is_valid_config(4, 0, -1);

    BOOST_TEST(is_valid == false);
}

BOOST_AUTO_TEST_SUITE_END()
