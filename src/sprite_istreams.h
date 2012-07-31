/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_SPRITE_ISTREAMS_H
#define LIBWASTELAND_SPRITE_ISTREAMS_H

#include <istream>

namespace wasteland
{

/**
 * Container for the input streams needed to read Wasteland sprite images. The
 * first stream is for reading the sprite colors and the second one is for
 * reading the sprite opacity information. In Wasteland these two information
 * are held in separate files.
 */
class sprite_istreams
{
public:
    sprite_istreams(std::istream &color_stream, std::istream &opacity_stream);
    operator bool() const;
    std::istream &color() const;
    std::istream &opacity() const;

private:
    std::istream &color_stream;
    std::istream &opacity_stream;

    sprite_istreams(sprite_istreams &);
    void operator=(const sprite_istreams&);
};

}

#endif
