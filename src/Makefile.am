bin_PROGRAMS = test
test_LDADD = libwasteland.la
test_LDFLAGS = -all-static
test_SOURCES = \
        test.cpp

lib_LTLIBRARIES = libwasteland.la
libwasteland_la_LDFLAGS = -version-info 1:0:0 -no-undefined
libwasteland_la_SOURCES = \
  bit_reader.cc \
  base_image.cc \
  base_transparent_image.cc \
  image.cc \
  vxor_image.cc \
  title_pic.cc \
  transparent_image.cc \
  sprite_istreams.cc \
  sprite_ostreams.cc \
  sprite.cc \
  font_char.cc \
  cursor.cc
libwastelandincludedir = $(includedir)
libwastelandinclude_HEADERS = \
  bit_reader.h \
  base_image.h \
  image.h \
  base_transparent_image.h \
  vxor_image.h \
  title_pic.h \
  transparent_image.h \
  sprite_istreams.h \
  sprite_ostreams.h \
  sprite.h \
  font_char.h \
  cursor.h 
AM_CFLAGS = -Wall -Werror -O2
