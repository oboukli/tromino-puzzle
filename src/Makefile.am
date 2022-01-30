# Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
# Distributed under an MIT-style license that can be
# found in the LICENSE file.

# SPDX-License-Identifier: MIT

bin_PROGRAMS =
include_HEADERS =
lib_LTLIBRARIES =

libtromino_la_SOURCES = lib/tromino.c
libtromino_la_LDFLAGS = \
	-no-undefined \
	-version-info $(LIBTROMINO_CURRENT):$(LIBTROMINO_REVISION):$(LIBTROMINO_AGE)
include_HEADERS += lib/tromino.h
lib_LTLIBRARIES += libtromino.la

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
tromino_CPPFLAGS = -I$(top_srcdir)/src/lib
tromino_LDADD = libtromino.la
bin_PROGRAMS += tromino

libtromino_gfx2d_la_SOURCES = \
	gfx2d/board.cpp \
	gfx2d/board.h \
	gfx2d/models.cpp \
	gfx2d/models.h \
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
libtromino_gfx2d_la_LIBADD = \
	libtromino.la
libtromino_gfx2d_la_LDFLAGS = \
	-lSDL2 \
	-no-undefined \
	-version-info $(LIBTROMINO_CURRENT):$(LIBTROMINO_REVISION):$(LIBTROMINO_AGE)
include_HEADERS += \
	gfx2d/board.h \
	gfx2d/models.h \
	gfx2d/tromino_gfx2d.h \
	gfx2d/viewmodel.h \
	gfx2d/window.h
lib_LTLIBRARIES += libtromino-gfx2d.la
