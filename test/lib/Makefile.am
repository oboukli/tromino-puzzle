check_PROGRAMS = libtromino_test

libtromino_test_CPPFLAGS = $(BOOST_CPPFLAGS) -I$(top_srcdir)/src/lib

libtromino_test_SOURCES = \
	testmain_libtromino.cpp \
	tromino_2x2_unittest.cpp

libtromino_test_LDFLAGS = $(BOOST_LDFLAGS) $(BOOST_UNIT_TEST_FRAMEWORK_LDFLAGS)
libtromino_test_LDADD = $(BOOST_UNIT_TEST_FRAMEWORK_LIB) $(top_builddir)/src/lib/libtromino.la

TESTS = $(check_PROGRAMS)
