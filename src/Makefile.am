bin_PROGRAMS = test
test_LDADD = libwasteland.la
test_LDFLAGS = -static
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
  vxor_streambuf.cc \
  vxor_istream.cc \
  vxor_ostream.cc \
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
  tile.cc \
  end_anim.cc \
  end_anim_update.cc \
  end_anim_frame.cc \
  end_anim_base_frame.cc
libwastelandincludedir = $(includedir)
libwastelandinclude_HEADERS = \
  bit_reader.h \
  bit_writer.h \
  huffman_node.h \
  huffman_reader.h \
  huffman_writer.h \
  vxor_streambuf.h \
  vxor_istream.h \
  vxor_ostream.h \
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
  tile.h \
  end_anim.h \
  end_anim_update.h \
  end_anim_frame.h \
  end_anim_base_frame.h  
AM_CFLAGS = -Wall -Werror -O2
