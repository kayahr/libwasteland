common_SOURCES = \
    program.cc \
    program_option.cc \
    gdutils.cc \
    fileutils.cc

bin_PROGRAMS = \
    decodepic \
    encodepic \
    unpacksprites
    
decodepic_LDADD = ../wasteland/libwasteland.la
decodepic_CPPFLAGS = -I..
decodepic_LDFLAGS = -static
decodepic_SOURCES = $(common_SOURCES) decodepic.cc

encodepic_LDADD = ../wasteland/libwasteland.la
encodepic_CPPFLAGS = -I..
encodepic_LDFLAGS = -static
encodepic_SOURCES = $(common_SOURCES) encodepic.cc

unpacksprites_LDADD = ../wasteland/libwasteland.la
unpacksprites_CPPFLAGS = -I..
unpacksprites_LDFLAGS = -static
unpacksprites_SOURCES = $(common_SOURCES) unpacksprites.cc

AM_CFLAGS = -Wall -Werror -O2
