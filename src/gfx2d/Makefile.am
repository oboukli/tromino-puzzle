lib_LTLIBRARIES = libtromino-gfx2d.la

libtromino_gfx2d_la_SOURCES = \
	board.cpp \
	board.h \
	models.cpp \
	models.h \
	style.cpp \
	style.h \
	tromino_gfx2d.cpp \
	tromino_gfx2d.h \
	viewmodel.cpp \
	viewmodel.h \
	window.cpp \
	window.h

include_HEADERS = \
	board.h \
	models.h \
	tromino_gfx2d.h \
	viewmodel.h \
	window.h

libtromino_gfx2d_la_CPPFLAGS = \
	-I/usr/include/SDL2 \
	-I$(top_srcdir)/src/lib

libtromino_gfx2d_la_LIBADD = \
	$(top_builddir)/src/lib/libtromino.la

libtromino_gfx2d_la_LDFLAGS = \
	-lSDL2 \
	-no-undefined \
	-version-info $(LIBTROMINO_CURRENT):$(LIBTROMINO_REVISION):$(LIBTROMINO_AGE)
