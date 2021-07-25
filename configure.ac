AC_PREREQ([2.69])

m4_define(_TRMNPZZL_VERSION_MAJOR, 0)
m4_define(_TRMNPZZL_VERSION_MINOR, 2)
m4_define(_TRMNPZZL_VERSION_PATCH, 1)
m4_define(_TRMNPZZL_VERSION_BUILD, 0)
m4_define(_TRMNPZZL_VERSION_RC, 0)
m4_define(_TRMNPZZL_VERSION_IS_RELEASE, true)
m4_define(_COPYRIGHT_YEAR, 2021)

AC_INIT([Tromino Puzzle], m4_join([.], _TRMNPZZL_VERSION_MAJOR, _TRMNPZZL_VERSION_MINOR, _TRMNPZZL_VERSION_PATCH, _TRMNPZZL_VERSION_BUILD)m4_if(_TRMNPZZL_VERSION_RC, [0], [], [rc]_TRMNPZZL_VERSION_RC), [https://github.com/oboukli/tromino-puzzle/issues], [trmnpzzl], [https://omar.fun/tromino-puzzle])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([src/cli/trmn_graph.cpp])
AC_CONFIG_HEADERS([src/config/config.h])

AC_SUBST([LIBTROMINO_CURRENT],[1])
AC_SUBST([LIBTROMINO_REVISION], [1])
AC_SUBST([LIBTROMINO_AGE], [1])

AM_PROG_AR

AC_PROG_CC
AC_PROG_CC_STDC
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE

AC_PROG_CXX
AX_CXX_COMPILE_STDCXX([17], [noext], [mandatory])

AC_PROG_SED

LT_INIT(disable-shared)

AC_CONFIG_FILES([Makefile src/lib/Makefile src/cli/Makefile])

AC_OUTPUT
