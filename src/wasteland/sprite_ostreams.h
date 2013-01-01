/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_SPRITE_OSTREAMS_H
#define LIBWASTELAND_SPRITE_OSTREAMS_H

#include <ostream>

namespace wasteland
{

/**
 * Container for the output streams needed to write Wasteland sprite images.
 * The first stream is for writing the sprite colors and the second one is for
 * writing the sprite opacity information. In Wasteland these two information
 * are held in separate files.
 */
class sprite_ostreams
{
public:
    sprite_ostreams(std::ostream &color_stream, std::ostream &opacity_stream);
    operator bool() const;
    std::ostream &color() const;
    std::ostream &opacity() const;

private:
    std::ostream &color_stream;
    std::ostream &opacity_stream;

    sprite_ostreams(sprite_ostreams &);
    void operator=(const sprite_ostreams&);
};

}

#endif
