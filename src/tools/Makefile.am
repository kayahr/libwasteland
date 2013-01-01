common_SOURCES = \
    program.cc \
    program_option.cc \
    gdutils.cc \
    fileutils.cc

bin_PROGRAMS = \
    decodepic \
    encodepic \
    unpacksprites \
    packsprites \
    unpackfont \
    packfont \
    unpackcursors \
    packcursors
    
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

unpackfont_LDADD = ../wasteland/libwasteland.la
unpackfont_CPPFLAGS = -I..
unpackfont_LDFLAGS = -static
unpackfont_SOURCES = $(common_SOURCES) unpackfont.cc

packfont_LDADD = ../wasteland/libwasteland.la
packfont_CPPFLAGS = -I..
packfont_LDFLAGS = -static
packfont_SOURCES = $(common_SOURCES) packfont.cc

unpackcursors_LDADD = ../wasteland/libwasteland.la
unpackcursors_CPPFLAGS = -I..
unpackcursors_LDFLAGS = -static
unpackcursors_SOURCES = $(common_SOURCES) unpackcursors.cc

packcursors_LDADD = ../wasteland/libwasteland.la
packcursors_CPPFLAGS = -I..
packcursors_LDFLAGS = -static
packcursors_SOURCES = $(common_SOURCES) packcursors.cc

AM_CFLAGS = -Wall -Werror -O2
