# Copyright (c) Omar Boukli-Hacene. All rights reserved.
# Distributed under an MIT-style license that can be
# found in the LICENSE file.

# SPDX-License-Identifier: MIT

AM_CPPFLAGS =
AM_CFLAGS = \
	-std=c99 \
	-Wpedantic \
	-Werror
AM_CXXFLAGS = \
	-Wall \
	-Wcast-align \
	-Wconversion \
	-Wdouble-promotion \
	-Wduplicated-branches \
	-Wduplicated-cond \
	-Weffc++ \
	-Werror \
	-Wformat=2 \
	-Wimplicit-fallthrough \
	-Wlogical-op \
	-Wmisleading-indentation \
	-Wnon-virtual-dtor \
	-Wnull-dereference \
	-Wold-style-cast \
	-Woverloaded-virtual \
	-Wpedantic \
	-Wshadow \
	-Wsign-conversion \
	-Wunused \
	-Wuseless-cast
AM_LDFLAGS = \
	-Wl,--fatal-warnings \
	-no-undefined \
	-Wl,--warn-common

if CODE_COVERAGE_ENABLED
AM_CPPFLAGS += $(CODE_COVERAGE_CPPFLAGS)
AM_CFLAGS += $(CODE_COVERAGE_CFLAGS)
AM_CXXFLAGS += $(CODE_COVERAGE_CXXFLAGS)
AM_LDFLAGS += $(CODE_COVERAGE_LIBS)
endif

check_PROGRAMS = libtromino_test

libtromino_test_SOURCES = \
	core/tromino_2x2_unittest.cpp \
	core/tromino_4x4_unittest.cpp \
	core/tromino_64x64_unittest.cpp \
	core/tromino_stop_flag.cpp \
	core/unittest_helper.cpp \
	core/unittest_helper.hpp \
	main.cpp \
	validation/validation_unittest.cpp

libtromino_test_CXXFLAGS = \
	$(AM_CXXFLAGS) \
	-std=c++20

libtromino_test_CPPFLAGS = \
	$(AM_CPPFLAGS) \
	$(BOOST_CPPFLAGS) \
	-I$(top_srcdir)/include

libtromino_test_LDFLAGS = \
	$(AM_LDFLAGS) \
	$(BOOST_LDFLAGS) \
	$(BOOST_UNIT_TEST_FRAMEWORK_LDFLAGS)

libtromino_test_LDADD = \
	$(BOOST_UNIT_TEST_FRAMEWORK_LIB) \
	$(top_builddir)/src/libtromino.la \
	$(top_builddir)/src/libtromino-validation.la

TESTS = $(check_PROGRAMS)
