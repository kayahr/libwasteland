/*
 * Copyright (C) 2013 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_VXOR_IMAGE_H
#define LIBWASTELAND_VXOR_IMAGE_H

#include <istream>
#include <ostream>
#include "image.h"

namespace wasteland
{

/**
 * Base class for vertical XOR encoded images.
 */
class vxor_image: public image
{
    /**
     * Reads the image from the specified input stream.
     *
     * @return The input stream.
     */
    friend std::istream& operator>>(std::istream&, vxor_image&);

    /**
     * Writes the image to the specified output stream.
     *
     * @return The output streams.
     */
    friend std::ostream& operator<<(std::ostream&, const vxor_image&);

public:
    /**
     * Constructs a new empty image with the specified size. All colors are set
     * to black.
     */
    vxor_image(const size width, const size height);

    /**
     * Destructs this image.
     */
    virtual ~vxor_image();

    /**
     * Compares this image with the given image.
     *
     * @param other
     *            The other image to compare this one with.
     * @return True if images are equal, false if not.
     */
    virtual bool operator==(const vxor_image& other) const;

    /**
     * Compares this image with the given image.
     *
     * @param other
     *            The other image to compare this one with.
     * @return  False if images are equal, true if not.
     */
    virtual bool operator!=(const vxor_image& other) const;

    virtual size get_width() const;
    virtual size get_height() const;
    virtual color get_color(const coord x, const coord y) const;
    virtual void set_color(const coord x, const coord y, const color color);

protected:
    /** The image data. */
    char *data;

    /** The image width in pixels. */
    size width;

    /** The image height in pixels. */
    size height;

    /** The image data size in bytes. */
    int size;
};

}

#endif
