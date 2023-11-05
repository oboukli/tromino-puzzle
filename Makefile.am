# Copyright (c) Omar Boukli-Hacene. All rights reserved.
# Distributed under an MIT-style license that can be
# found in the LICENSE file.

# SPDX-License-Identifier: MIT

ACLOCAL_AMFLAGS = -I m4
dist_doc_DATA = README.md

AM_CPPFLAGS =
AM_CFLAGS = \
	-std=c99 \
	-Wall \
	-Wcast-align \
	-Wconversion \
	-Wdouble-promotion \
	-Wduplicated-branches \
	-Wduplicated-cond \
	-Werror \
	-Wformat=2 \
	-Wimplicit-fallthrough \
	-Wlogical-op \
	-Wmisleading-indentation \
	-Wnull-dereference \
	-Wpedantic \
	-Wshadow \
	-Wsign-conversion \
	-Wunused
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
	-no-undefined \
	-version-info $(LIBTROMINO_CURRENT):$(LIBTROMINO_REVISION):$(LIBTROMINO_AGE) \
	-Wl,--fatal-warnings \
	-Wl,--no-undefined \
	-Wl,--warn-alternate-em \
	-Wl,--warn-common \
	-Wl,--warn-unresolved-symbols

if CODE_COVERAGE_ENABLED
AM_CPPFLAGS += $(CODE_COVERAGE_CPPFLAGS)
AM_CFLAGS += $(CODE_COVERAGE_CFLAGS)
AM_CXXFLAGS += $(CODE_COVERAGE_CXXFLAGS)
AM_LDFLAGS += $(CODE_COVERAGE_LIBS)
endif

bin_PROGRAMS =
lib_LTLIBRARIES =

coreincludedir = tromino/core
libtromino_la_SOURCES = \
	src/core/tromino.c
libtromino_la_CPPFLAGS = \
	$(AM_CPPFLAGS) \
	-I$(top_srcdir)/include/tromino/core
coreinclude_HEADERS = \
	include/tromino/core/tromino.h
lib_LTLIBRARIES += libtromino.la

validationincludedir = tromino/validation
libtromino_validation_la_SOURCES = \
	src/validation/validation.c
libtromino_validation_la_CPPFLAGS = \
	$(AM_CPPFLAGS) \
	-I$(top_srcdir)/include/tromino/validation
validationinclude_HEADERS = \
	include/tromino/validation/validation.h
lib_LTLIBRARIES += libtromino-validation.la

cliincludedir = tromino/cli
tromino_SOURCES = \
	src/cli/cli_options.cpp \
	src/cli/init.cpp \
	src/cli/main.cpp \
	src/cli/trmn_graph_vt.cpp \
	src/cli/wrapper.cpp
tromino_CPPFLAGS = \
	$(AM_CPPFLAGS) \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/include/tromino/cli
tromino_CXXFLAGS = \
	$(AM_CXXFLAGS) \
	-std=c++20
tromino_LDADD = \
	$(top_builddir)/libtromino.la \
	$(top_builddir)/libtromino-validation.la
cliinclude_HEADERS = \
	include/tromino/cli/cli_models.hpp \
	include/tromino/cli/cli_options.hpp \
	include/tromino/cli/init.hpp \
	include/tromino/cli/params.hpp \
	include/tromino/cli/trmn_graph_vt.hpp \
	include/tromino/cli/trmn_graph.hpp \
	include/tromino/cli/wrapper.hpp
bin_PROGRAMS += tromino

gfx2dincludedir = tromino/gfx2d
libtromino_gfx2d_la_SOURCES = \
	src/gfx2d/gfx2d.cpp \
	src/gfx2d/view_model.cpp \
	src/gfx2d/window.cpp
libtromino_gfx2d_la_CPPFLAGS = \
	$(AM_CPPFLAGS) \
	-I$(top_srcdir)/include/tromino/gfx2d
libtromino_gfx2d_la_LDFLAGS = \
	$(AM_LDFLAGS) \
	-lSDL2
gfx2dinclude_HEADERS = \
	include/tromino/gfx2d/board.hpp \
	include/tromino/gfx2d/gfx2d.hpp \
	include/tromino/gfx2d/step.hpp \
	include/tromino/gfx2d/style.hpp \
	include/tromino/gfx2d/view_model.hpp \
	include/tromino/gfx2d/window.hpp
lib_LTLIBRARIES += libtromino-gfx2d.la

guiincludedir = tromino/gui
tromino2d_SOURCES = \
	src/gui/callback.cpp \
	src/gui/cli_options.cpp \
	src/gui/init.cpp \
	src/gui/main.cpp
tromino2d_CPPFLAGS = \
	$(AM_CPPFLAGS) \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/include/tromino/gui
tromino2d_CXXFLAGS = \
	$(AM_CXXFLAGS) \
	-std=c++20
tromino2d_LDFLAGS = \
	$(AM_LDFLAGS) \
	-lpthread \
	-lSDL2
tromino2d_LDADD = \
	$(top_builddir)/libtromino.la \
	$(top_builddir)/libtromino-gfx2d.la \
	$(top_builddir)/libtromino-validation.la
guiinclude_HEADERS = \
	include/tromino/gui/callback.hpp \
	include/tromino/gui/cli_models.hpp \
	include/tromino/gui/cli_options.hpp \
	include/tromino/gui/init.hpp \
	include/tromino/gui/params.hpp
bin_PROGRAMS += tromino2d

check_PROGRAMS = libtromino_test

libtromino_test_SOURCES = \
	test/core/tromino_2x2_unittest.cpp \
	test/core/tromino_4x4_unittest.cpp \
	test/core/tromino_64x64_unittest.cpp \
	test/core/tromino_stop_flag.cpp \
	test/core/unittest_helper.cpp \
	test/core/unittest_helper.hpp \
	test/main.cpp \
	test/validation/validation_unittest.cpp

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
	$(top_builddir)/libtromino.la \
	$(top_builddir)/libtromino-validation.la

TESTS = $(check_PROGRAMS)
