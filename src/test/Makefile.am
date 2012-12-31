TESTS = test_libwasteland
check_PROGRAMS = $(TESTS)
test_libwasteland_CPPFLAGS = $(CPPUNIT_CFLAGS) -I..
test_libwasteland_LDADD = ../wasteland/libwasteland.la
test_libwasteland_LDFLAGS = $(CPPUNIT_LIBS) -static
test_libwasteland_SOURCES = \
	bit_reader_test.cc \
	bit_writer_test.cc \
	huffman_reader_test.cc \
	huffman_writer_test.cc \
	title_pic_test.cc \
	sprite_test.cc \
	cursor_test.cc \
	font_char_test.cc \
	tile_test.cc \
	test_libwasteland.cc
AM_CFLAGS = -Wall -Werror -O2
