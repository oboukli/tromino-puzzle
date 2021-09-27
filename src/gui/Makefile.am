bin_PROGRAMS = tromino-gui

tromino_gui_SOURCES = \
	main.cpp

tromino_gui_CPPFLAGS = \
	-I$(top_srcdir)/src/lib \
	-I$(top_srcdir)/src/gfx2d \
	-I$(top_srcdir)/src/gfx2dfe

tromino_gui_LDADD = \
	$(top_builddir)/src/lib/libtromino.la \
	$(top_builddir)/src/gfx2d/libtromino-gfx2d.la \
	$(top_builddir)/src/gfx2dfe/libtromino-gfx2dfe.la

tromino_gui_LDFLAGS = \
	-lSDL2 \
	-no-undefined
