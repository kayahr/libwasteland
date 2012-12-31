common_SOURCES = \
    program.cc \
    program_option.cc \
    gdutils.cc

bin_PROGRAMS = wl_decodepic
wl_decodepic_LDADD = ../wasteland/libwasteland.la
wl_decodepic_CPPFLAGS = -I..
wl_decodepic_LDFLAGS = -static
wl_decodepic_SOURCES = $(common_SOURCES) decodepic.cc

AM_CFLAGS = -Wall -Werror -O2
