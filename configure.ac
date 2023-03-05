dnl Copyright (c) Omar Boukli-Hacene. All rights reserved.
dnl Distributed under an MIT-style license that can be
dnl found in the LICENSE file.
dnl
dnl SPDX-License-Identifier: MIT

AC_PREREQ([2.69])

m4_define(_TRMNPZZL_VERSION_MAJOR, 0)
m4_define(_TRMNPZZL_VERSION_MINOR, 12)
m4_define(_TRMNPZZL_VERSION_PATCH, 8)
m4_define(_TRMNPZZL_VERSION_BUILD, 0)
m4_define(_TRMNPZZL_VERSION_RC, 0)
m4_define(_TRMNPZZL_VERSION_IS_RELEASE, true)
m4_define(_COPYRIGHT_YEAR, 2023)

AC_INIT([trmnpzzl],[m4_join(., _TRMNPZZL_VERSION_MAJOR, _TRMNPZZL_VERSION_MINOR, _TRMNPZZL_VERSION_PATCH, _TRMNPZZL_VERSION_BUILD)m4_if(_TRMNPZZL_VERSION_RC, 0, , rc_TRMNPZZL_VERSION_RC)],[https://github.com/oboukli/tromino-puzzle/issues],[trmnpzzl],[https://omar.fun/tromino-puzzle])
AM_INIT_AUTOMAKE([foreign subdir-objects -Wall -Werror])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([src/libtromino/tromino.c])
AC_CONFIG_HEADERS([src/config/config.h])

AC_SUBST([LIBTROMINO_CURRENT],[1])
AC_SUBST([LIBTROMINO_REVISION], [2])
AC_SUBST([LIBTROMINO_AGE], [1])

AM_PROG_AR

if test "x$enable_code_coverage" = xyes; then
    CFLAGS=""
    CXXFLAGS=""
fi

AC_PROG_CC

AC_CHECK_HEADER_STDBOOL
AC_C_INLINE

AC_PROG_CXX
AX_CXX_COMPILE_STDCXX([17], [noext], [mandatory])

AC_PROG_SED

LT_INIT(disable-shared)
AC_CONFIG_FILES([Makefile src/Makefile test/Makefile])

AX_BOOST_BASE([1.71.0], [], [AC_MSG_ERROR([Boost is not available])])
AX_BOOST_UNIT_TEST_FRAMEWORK

AX_CODE_COVERAGE

AC_OUTPUT
