TESTS = test_libwasteland
check_PROGRAMS = $(TESTS)
test_libwasteland_CXXFLAGS = $(CPPUNIT_CFLAGS)
test_libwasteland_LDADD = ../src/libwasteland.la
test_libwasteland_LDFLAGS = $(CPPUNIT_LIBS)
test_libwasteland_SOURCES = \
	bit_reader_test.cc \
	image_test.cc \
	transparent_image_test.cc \
	title_pic_test.cc \
	test_libwasteland.cc
