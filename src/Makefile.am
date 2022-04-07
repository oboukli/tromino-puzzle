# Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
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

libtromino_la_SOURCES = lib/tromino.c
libtromino_la_LDFLAGS = \
	-no-undefined \
	-version-info $(LIBTROMINO_CURRENT):$(LIBTROMINO_REVISION):$(LIBTROMINO_AGE)
include_HEADERS += lib/tromino.h
lib_LTLIBRARIES += libtromino.la

libtromino_validation_la_SOURCES = validation/tromino_validation.c
libtromino_validation_la_LDFLAGS = \
	-no-undefined \
	-version-info $(LIBTROMINO_CURRENT):$(LIBTROMINO_REVISION):$(LIBTROMINO_AGE)
include_HEADERS += validation/tromino_validation.h
lib_LTLIBRARIES += libtromino-validation.la

tromino_SOURCES = \
	cli/cli_models.cpp \
	cli/cli_models.h \
	cli/cli_options.cpp \
	cli/cli_options.h \
	cli/init.cpp \
	cli/init.h \
	cli/main.cpp \
	cli/trmn_graph.cpp \
	cli/trmn_graph.h \
	cli/trmn_graph_vt.cpp \
	cli/trmn_graph_vt.h
tromino_CPPFLAGS = \
	-I$(top_srcdir)/src/lib \
	-I$(top_srcdir)/src/validation
tromino_LDADD = \
	libtromino.la \
	libtromino-validation.la
bin_PROGRAMS += tromino

libtromino_gfx2d_la_SOURCES = \
	gfx2d/board.cpp \
	gfx2d/board.h \
	gfx2d/step.cpp \
	gfx2d/step.h \
	gfx2d/style.cpp \
	gfx2d/style.h \
	gfx2d/tromino_gfx2d.cpp \
	gfx2d/tromino_gfx2d.h \
	gfx2d/viewmodel.cpp \
	gfx2d/viewmodel.h \
	gfx2d/window.cpp \
	gfx2d/window.h
libtromino_gfx2d_la_CPPFLAGS = \
	-I/usr/include/SDL2 \
	-I$(top_srcdir)/src/lib
libtromino_gfx2d_la_LDFLAGS = \
	-lSDL2 \
	-no-undefined \
	-version-info $(LIBTROMINO_CURRENT):$(LIBTROMINO_REVISION):$(LIBTROMINO_AGE)
libtromino_gfx2d_la_LIBADD = libtromino.la
include_HEADERS += \
	gfx2d/board.h \
	gfx2d/step.h \
	gfx2d/tromino_gfx2d.h \
	gfx2d/viewmodel.h \
	gfx2d/window.h
lib_LTLIBRARIES += libtromino-gfx2d.la

tromino2d_SOURCES = \
	gui/cli_models.cpp \
	gui/cli_models.h \
	gui/cli_options.cpp \
	gui/cli_options.h \
	gui/init.cpp \
	gui/init.h \
	gui/main.cpp \
	gui/params.cpp \
	gui/params.h \
	gui/solver.cpp \
	gui/solver.h
tromino2d_CPPFLAGS = \
	-I/usr/include/SDL2 \
	-I$(top_srcdir)/src/lib \
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
