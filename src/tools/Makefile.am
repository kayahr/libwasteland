common_SOURCES = \
    program.cc \
    program_option.cc \
    gdutils.cc

bin_PROGRAMS = \
    wl_decodepic \
    wl_encodepic
    
wl_decodepic_LDADD = ../wasteland/libwasteland.la
wl_decodepic_CPPFLAGS = -I..
wl_decodepic_LDFLAGS = -static
wl_decodepic_SOURCES = $(common_SOURCES) decodepic.cc

wl_encodepic_LDADD = ../wasteland/libwasteland.la
wl_encodepic_CPPFLAGS = -I..
wl_encodepic_LDFLAGS = -static
wl_encodepic_SOURCES = $(common_SOURCES) encodepic.cc

AM_CFLAGS = -Wall -Werror -O2
