# Copyright (c) Omar Boukli-Hacene. All rights reserved.
# Distributed under an MIT-style license that can be
# found in the LICENSE file.

# SPDX-License-Identifier: MIT

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
include_HEADERS =
lib_LTLIBRARIES =

libtromino_la_SOURCES = core/tromino.c
libtromino_la_CPPFLAGS = \
	-I$(top_srcdir)/include/tromino/core
include_HEADERS += $(top_srcdir)/include/tromino/core/tromino.h
lib_LTLIBRARIES += libtromino.la

libtromino_validation_la_SOURCES = validation/validation.c
libtromino_validation_la_CPPFLAGS = \
	$(AM_CPPFLAGS) \
	-I$(top_srcdir)/include/tromino/validation
include_HEADERS += $(top_srcdir)/include/tromino/validation/validation.h
lib_LTLIBRARIES += libtromino-validation.la

tromino_SOURCES = \
	cli/cli_models.hpp \
	cli/cli_options.cpp \
	cli/cli_options.hpp \
	cli/init.cpp \
	cli/init.hpp \
	cli/main.cpp \
	cli/params.hpp \
	cli/trmn_graph_vt.cpp \
	cli/trmn_graph_vt.hpp \
	cli/trmn_graph.hpp \
	cli/wrapper.cpp \
	cli/wrapper.hpp
tromino_CPPFLAGS = \
	$(AM_CPPFLAGS) \
	-I$(top_srcdir)/include
tromino_CXXFLAGS = \
	$(AM_CXXFLAGS) \
	-std=c++20
tromino_LDADD = \
	libtromino.la \
	libtromino-validation.la
bin_PROGRAMS += tromino

libtromino_gfx2d_la_SOURCES = \
	gfx2d/gfx2d.cpp \
	gfx2d/view_model.cpp \
	gfx2d/window.cpp
libtromino_gfx2d_la_CPPFLAGS = \
	$(AM_CPPFLAGS) \
	-I/usr/include/SDL2 \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/include/tromino/gfx2d
libtromino_gfx2d_la_LDFLAGS = \
	$(AM_LDFLAGS) \
	-lSDL2
include_HEADERS += \
	$(top_srcdir)/include/tromino/gfx2d/board.hpp \
	$(top_srcdir)/include/tromino/gfx2d/gfx2d.hpp \
	$(top_srcdir)/include/tromino/gfx2d/step.hpp \
	$(top_srcdir)/include/tromino/gfx2d/style.hpp \
	$(top_srcdir)/include/tromino/gfx2d/view_model.hpp \
	$(top_srcdir)/include/tromino/gfx2d/window.hpp
lib_LTLIBRARIES += libtromino-gfx2d.la

tromino2d_SOURCES = \
	gui/callback.cpp \
	gui/callback.hpp \
	gui/cli_models.hpp \
	gui/cli_options.cpp \
	gui/cli_options.hpp \
	gui/init.cpp \
	gui/init.hpp \
	gui/main.cpp \
	gui/params.hpp
tromino2d_CPPFLAGS = \
	$(AM_CPPFLAGS) \
	-I/usr/include/SDL2 \
	-I$(top_srcdir)/include
tromino2d_CXXFLAGS = \
	$(AM_CXXFLAGS) \
	-std=c++20
tromino2d_LDFLAGS = \
	$(AM_LDFLAGS) \
	-lpthread \
	-lSDL2
tromino2d_LDADD = \
	libtromino.la \
	libtromino-gfx2d.la \
	libtromino-validation.la
bin_PROGRAMS += tromino2d
