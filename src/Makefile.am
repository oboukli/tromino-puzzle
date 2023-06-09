# Copyright (c) Omar Boukli-Hacene. All rights reserved.
# Distributed under an MIT-style license that can be
# found in the LICENSE file.

# SPDX-License-Identifier: MIT

if CODE_COVERAGE_ENABLED
AM_CPPFLAGS = $(CODE_COVERAGE_CPPFLAGS)
AM_CFLAGS = $(CODE_COVERAGE_CFLAGS)
AM_CXXFLAGS = $(CODE_COVERAGE_CXXFLAGS)
AM_LDFLAGS = $(CODE_COVERAGE_LIBS)
endif

bin_PROGRAMS =
include_HEADERS =
lib_LTLIBRARIES =

libtromino_la_SOURCES = libtromino/tromino.c
libtromino_la_LDFLAGS = \
	-no-undefined \
	-version-info $(LIBTROMINO_CURRENT):$(LIBTROMINO_REVISION):$(LIBTROMINO_AGE)
include_HEADERS += libtromino/tromino.h
lib_LTLIBRARIES += libtromino.la

libtromino_validation_la_SOURCES = validation/tromino_validation.c
libtromino_validation_la_LDFLAGS = \
	-no-undefined \
	-version-info $(LIBTROMINO_CURRENT):$(LIBTROMINO_REVISION):$(LIBTROMINO_AGE)
include_HEADERS += validation/tromino_validation.h
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
	cli/trmn_graph.hpp
tromino_CPPFLAGS = \
	-I$(top_srcdir)/src/libtromino \
	-I$(top_srcdir)/src/validation
tromino_LDADD = \
	libtromino.la \
	libtromino-validation.la
bin_PROGRAMS += tromino

libtromino_gfx2d_la_SOURCES = \
	gfx2d/board.hpp \
	gfx2d/step.hpp \
	gfx2d/style.hpp \
	gfx2d/tromino_gfx2d.cpp \
	gfx2d/tromino_gfx2d.hpp \
	gfx2d/view_model.cpp \
	gfx2d/view_model.hpp \
	gfx2d/window.cpp \
	gfx2d/window.hpp
libtromino_gfx2d_la_CPPFLAGS = \
	-I/usr/include/SDL2 \
	-I$(top_srcdir)/src/libtromino
libtromino_gfx2d_la_LDFLAGS = \
	-lSDL2 \
	-no-undefined \
	-version-info $(LIBTROMINO_CURRENT):$(LIBTROMINO_REVISION):$(LIBTROMINO_AGE)
libtromino_gfx2d_la_LIBADD = libtromino.la
include_HEADERS += \
	gfx2d/board.hpp \
	gfx2d/step.hpp \
	gfx2d/tromino_gfx2d.hpp \
	gfx2d/view_model.hpp \
	gfx2d/window.hpp
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
	-I/usr/include/SDL2 \
	-I$(top_srcdir)/src/libtromino \
	-I$(top_srcdir)/src/gfx2d \
	-I$(top_srcdir)/src/validation
tromino2d_LDFLAGS = \
	-lpthread \
	-lSDL2 \
	-no-undefined
tromino2d_LDADD = \
	libtromino.la \
	libtromino-gfx2d.la \
	libtromino-validation.la
bin_PROGRAMS += tromino2d
