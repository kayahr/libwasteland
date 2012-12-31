AC_PREREQ([2.50])
AC_INIT([libwasteland], [0.1], [k@ailis.de])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])

AC_LANG_CPLUSPLUS
AM_PROG_LIBTOOL
AM_PATH_CPPUNIT(1.12.1)
AC_PROG_INSTALL

AC_CHECK_HEADERS(gd.h,,echo "ERROR: gd.h not found"; exit 1;)
AC_CHECK_LIB(gd,gdImageCreate,,echo "ERROR: GD library not found"; exit 1;)

AC_DEFINE(AUTHOR,"Klaus Reimer",Authors name)
AC_DEFINE(EMAIL,"k@ailis.de",Authors email address)
AC_DEFINE(COPYRIGHT,"Copyright (C) 2012  Klaus Reimer <k@ailis.de>",Copyright message)

AC_CONFIG_FILES(
  Makefile 
  src/Makefile
  src/wasteland/Makefile
  src/tools/Makefile
  src/test/Makefile
)
AC_OUTPUT
