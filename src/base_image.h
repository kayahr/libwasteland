/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_BASE_IMAGE_H
#define LIBWASTELAND_BASE_IMAGE_H

#include <stdint.h>

namespace wasteland
{

/**
 * Abstract base class for all images with 4 bit colors.
 */
class base_image
{
public:
    /** Type for a color of a pixel in an image. This is a 4 bit CGA color .*/
    typedef uint8_t color;

    /** Type for a coordinate (X or Y) in an image. */
    typedef uint16_t coord;

    /** Type for the size (width or height) of an image. */
    typedef uint16_t size;

    virtual ~base_image() = 0;

    /**
     * Returns the width of the image.
     *
     * @return The width of the image.
     */
    virtual size get_width() const = 0;

    /**
     * Returns the height of the image.
     *
     * @return The height of the image.
     */
    virtual size get_height() const = 0;

    /**
     * Returns the color of the pixel at the specified position. If the
     * position is outside of the image then 0 (black) is returned.
     *
     * @param x
     *            The X position of the pixel.
     * @param y
     *            The Y position of the pixel.
     * @return The color of the pixel at the specified position or 0 (black)
     *         if position is outside of the image.
     */
    virtual color get_color(const coord x, const coord y) const = 0;

    /**
     * Sets the color of the pixel at the specified position. If the
     * position is outside of the image then this method does nothing.
     *
     * @param x
     *            The X position of the pixel.
     * @param y
     *            The Y position of the pixel.
     * @param color
     *            The color to set.
     */
    virtual void set_color(const coord x, const coord y, const color color) = 0;
};

}

#endif
