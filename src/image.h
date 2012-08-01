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
 * Abstract base class for all images with 4 bit colors.
 */
class image
{
public:
    /** Type representing a single 4 bit color with valid values 0 - 15. */
    typedef char color;

    image(const int width, const int height);
    image(const image& image);
    image& operator=(const image& image);
    virtual ~image();
    int get_width() const;
    int get_height() const;
    color get_color(const int x, const int y) const;
    void set_color(const int x, const int y, const color color);

protected:
    /** The width of the image. */
    int width;

    /** The height of the image. */
    int height;

    /** The image pixel data. Each byte represents two 4-bit pixels. */
    char* data;

private:
    int get_data_size(const int width, const int height) const;
    int get_data_index(const int x, const int y) const;
};

}

#endif
