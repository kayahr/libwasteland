/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_TRANSPARENT_IMAGE_H
#define LIBWASTELAND_TRANSPARENT_IMAGE_H

#include "image.h"

namespace wasteland
{

/**
 * Base class for transparent images.
 */
class transparent_image: public image
{
public:
    transparent_image(const int width, const int height);
    transparent_image(const transparent_image& image);
    virtual ~transparent_image();
    transparent_image& operator=(const transparent_image& image);
    bool is_transparent(const int x, const int y) const;
    void set_transparent(const int x, const int y, const bool opaque);

protected:
    /** The opacity information of the image. */
    char *transparency;

    int get_transparency_size(const int width, const int height) const;
    int get_transparency_index(const int x, const int y) const;
};

}

#endif
