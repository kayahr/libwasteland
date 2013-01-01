AC_DEFUN([AC_CHECK_EXTRA],[
  AC_ARG_WITH(
    extra-libs,
    [  --with-extra-libs=DIR   comma separated list of additional lib directories ],
    [
      EXTRA=`echo $withval | sed -e ':a;s/,/ -L/;t a'`
      LDFLAGS="$LDFLAGS -L$EXTRA"
    ]
  )
  AC_ARG_WITH(
    extra-includes,
    [  --with-extra-includes=DIR  comma separated list of additional include directories ],
    [
      EXTRA=`echo $withval | sed -e ':a;s/,/ -I/;t a'`
      CFLAGS="$CFLAGS -I$EXTRA"
    ]
  )
])

AC_DEFUN([AC_WL_TOOLS],[
  AC_ARG_WITH(
    tools,
    [  --without-tools         Skip building wasteland tools ],
    [
      AM_CONDITIONAL(BUILD_TOOLS, false)
    ],
    [
      AM_CONDITIONAL(BUILD_TOOLS, true)
      AC_CHECK_HEADERS(gd.h,,echo "ERROR: gd.h not found"; exit 1;)
      AC_CHECK_LIB(gd,gdImageCreate,,echo "ERROR: GD library not found"; exit 1;)
      AC_CHECK_HEADERS(getopt.h,,echo "ERROR: getopt.h not found"; exit 1;)
    ]
  )
])
