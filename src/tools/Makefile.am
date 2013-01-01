common_SOURCES = \
    program.cc \
    program_option.cc \
    gdutils.cc \
    fileutils.cc

bin_PROGRAMS = \
    decodepic \
    encodepic \
    unpacksprites \
    packsprites
    
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

packsprites_LDADD = ../wasteland/libwasteland.la
packsprites_CPPFLAGS = -I..
packsprites_LDFLAGS = -static
packsprites_SOURCES = $(common_SOURCES) packsprites.cc

AM_CFLAGS = -Wall -Werror -O2
