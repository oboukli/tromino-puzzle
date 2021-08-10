// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

#include <boost/test/unit_test.hpp>

#include "tromino.h"

class Step
{
public:
    position_t abspos;
    rotation_t rot;

    bool operator!=(const Step &rhs) {
        return rhs.abspos.x != this->abspos.x
            || rhs.abspos.y != this->abspos.y
            || rhs.rot.x != this->rot.x
            || rhs.rot.y != this->rot.y;
    }

    friend std::ostream & operator<<(std::ostream &os, const Step &s) {
        return os
            << "Tromino position: (" << s.abspos.x << ", " << s.abspos.y
            << "). Rotation: (" << s.rot.x << ", " << s.rot.y << ")";
    }
};

void add_tromino(position_t abspos, rotation_t rot, void * state) {
    Step step = { abspos, rot };
    static_cast<std::vector<Step>*>(state)->push_back(step);
}

BOOST_AUTO_TEST_SUITE(tromino2x2_test_suite)

//
// X |
// - +
BOOST_AUTO_TEST_CASE(GivenK2_WhenTopLeft_ThenSolutionIsK)
{
    constexpr int order = 2;
    constexpr position_t mark = { 0, 0 };
    std::vector<Step> expected = {{{0, 0}, {-1, -1}}};
    std::vector<Step> actual;

    solve_tromino_puzzle(order, mark, add_tromino, &actual);

    BOOST_CHECK_EQUAL(actual.size(), 1);
    BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(), expected.begin(), expected.end());
}

//
// | X
// + -
BOOST_AUTO_TEST_CASE(GivenL2_WhenTopRight_ThenSolutionIsL)
{
    constexpr int order = 2;
    constexpr position_t mark = { 1, 0 };
    const std::vector<Step> expected = {{{0, 0}, {1, -1}}};
    std::vector<Step> actual;

    solve_tromino_puzzle(order, mark, add_tromino, &actual);

    BOOST_CHECK_EQUAL(actual.size(), 1);
    BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(), expected.begin(), expected.end());
}

//
// - +
// X |
BOOST_AUTO_TEST_CASE(GivenM2_WhenBottomLeft_ThenSolutionIsM)
{
    constexpr int order = 2;
    constexpr position_t mark = { 0, 1 };
    const std::vector<Step> expected = {{{0, 0}, {-1, 1}}};
    std::vector<Step> actual;

    solve_tromino_puzzle(order, mark, add_tromino, &actual);

    BOOST_CHECK_EQUAL(actual.size(), 1);
    BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(), expected.begin(), expected.end());
}

//
// + -
// | X
BOOST_AUTO_TEST_CASE(GivenN2_WhenBottomRight_ThenSolutionIsN)
{
    constexpr int order = 2;
    constexpr position_t mark = { 1, 1 };
    const std::vector<Step> expected = {{{0, 0}, {1, 1}}};
    std::vector<Step> actual;

    solve_tromino_puzzle(order, mark, add_tromino, &actual);

    BOOST_CHECK_EQUAL(actual.size(), 1);
    BOOST_CHECK_EQUAL_COLLECTIONS(actual.begin(), actual.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_SUITE_END()
