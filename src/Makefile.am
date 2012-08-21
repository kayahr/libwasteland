bin_PROGRAMS = test
test_LDADD = libwasteland.la
test_LDFLAGS = -all-static
test_SOURCES = \
        test.cpp

lib_LTLIBRARIES = libwasteland.la
libwasteland_la_LDFLAGS = -version-info 1:0:0 -no-undefined
libwasteland_la_SOURCES = \
  bit_reader.cc \
  bit_writer.cc \
  huffman_node.cc \
  huffman_reader.cc \
  huffman_writer.cc \
  image.cc \
  transparent_image.cc \
  sprite_istreams.cc \
  sprite_ostreams.cc \
  title_pic.cc \
  sprite.cc \
  font_char.cc \
  cursor.cc \
  tile_reader.cc \
  tile_writer.cc \
  tile.cc
libwastelandincludedir = $(includedir)
libwastelandinclude_HEADERS = \
  bit_reader.h \
  bit_writer.h \
  huffman_node.h \
  huffman_reader.h \
  huffman_writer.h \
  image.h \
  transparent_image.h \
  sprite_istreams.h \
  sprite_ostreams.h \
  title_pic.h \
  sprite.h \
  font_char.h \
  cursor.h \
  tile_reader.h \
  tile_writer.h \
  tile.h
AM_CFLAGS = -Wall -Werror -O2
