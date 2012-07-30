/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_IMAGE_H
#define LIBWASTELAND_IMAGE_H

#include <istream>

namespace wasteland
{

/**
 * A Wasteland image with a width, a height and a bunch of pixels.
 */
class image
{
public:
	typedef char color;

    image(const int width, const int height, const bool transparent = false);
    virtual ~image();
    int width() const;
    int height() const;
    const color& operator()(const int x, const int y) const;
    color& operator()(const int x, const int y);

private:
    int width_;
    int height_;
    color *pixels_;
    color transparency_;
    color dummy_;
};

}

#endif
