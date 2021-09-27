lib_LTLIBRARIES = libtromino-gfx2dfe.la

libtromino_gfx2dfe_la_SOURCES = \
	init.cpp \
	init.h

include_HEADERS = init.h

libtromino_gfx2dfe_la_CPPFLAGS = \
	-I/usr/include/SDL2 \
	-I$(top_srcdir)/src/lib \
	-I$(top_srcdir)/src/gfx2d

libtromino_gfx2dfe_la_LIBADD = \
	$(top_builddir)/src/lib/libtromino.la \
	$(top_builddir)/src/gfx2d/libtromino-gfx2d.la

libtromino_gfx2dfe_la_LDFLAGS = \
	-lSDL2 \
	-no-undefined \
	-version-info $(LIBTROMINO_CURRENT):$(LIBTROMINO_REVISION):$(LIBTROMINO_AGE)
