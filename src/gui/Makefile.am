bin_PROGRAMS = tromino-gui

tromino_gui_SOURCES = \
	init.cpp \
	init.h \
	main.cpp \
	solver.cpp \
	solver.h

tromino_gui_CPPFLAGS = \
	-I/usr/include/SDL2 \
	-I$(top_srcdir)/src/lib \
	-I$(top_srcdir)/src/gfx2d

tromino_gui_LDADD = \
	$(top_builddir)/src/lib/libtromino.la \
	$(top_builddir)/src/gfx2d/libtromino-gfx2d.la

tromino_gui_LDFLAGS = \
	-lpthread \
	-lSDL2 \
	-no-undefined
