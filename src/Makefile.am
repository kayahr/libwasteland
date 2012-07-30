bin_PROGRAMS = test
test_LDADD = libwasteland.la
test_LDFLAGS = -all-static
test_SOURCES = \
        test.cpp

lib_LTLIBRARIES = libwasteland.la
libwasteland_la_LDFLAGS = -version-info 1:0:0 -no-undefined
libwasteland_la_SOURCES = \
  bit_reader.cc \
  pic_reader.cc \
  image.cc
libwastelandincludedir = $(includedir)
libwastelandinclude_HEADERS = image.h title_pic.h
AM_CFLAGS = -Wall -Werror -O2

doc:
	rm -f ../../doc/html/*.html ../../doc/html/*.gif
	mkdir -p ../../doc/html
	doc++ -M -H --dir ../../doc/html/ *.h *.c
