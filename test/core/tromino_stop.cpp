// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <boost/test/unit_test.hpp>

#include <tromino/core/tromino.h>

using boost::unit_test::label;

BOOST_AUTO_TEST_SUITE(tromino_stop_test_suite)

BOOST_AUTO_TEST_CASE(
    Given_trmn_request_stop_WhenInvoked_ThenPassTest, *label("core")
)
{
    ::trmn_request_stop();

    BOOST_TEST_PASSPOINT();
}

BOOST_AUTO_TEST_SUITE_END()
