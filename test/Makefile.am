# Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
# Distributed under an MIT-style license that can be
# found in the LICENSE file.

# SPDX-License-Identifier: MIT

check_PROGRAMS = libtromino_test

libtromino_test_CPPFLAGS = $(BOOST_CPPFLAGS) -I$(top_srcdir)/src/lib

libtromino_test_SOURCES = \
	lib/testmain_libtromino.cpp \
	lib/tromino_2x2_unittest.cpp \
	lib/tromino_4x4_unittest.cpp \
	lib/tromino_64x64_unittest.cpp \
	lib/unittest_helper.cpp \
	lib/unittest_helper.h

libtromino_test_LDFLAGS = $(BOOST_LDFLAGS) $(BOOST_UNIT_TEST_FRAMEWORK_LDFLAGS)
libtromino_test_LDADD = $(BOOST_UNIT_TEST_FRAMEWORK_LIB) $(top_builddir)/src/libtromino.la

TESTS = $(check_PROGRAMS)
