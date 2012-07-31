/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <cstring>
#include "transparent_image.h"

namespace wasteland
{

/**
 * Constructs a new transparent image with the specified size.
 *
 * @param width
 *            The image width.
 * @param height
 *            The image height.
 */
transparent_image::transparent_image(const int width, const int height) :
    image(width, height)
{
    transparency = new char[height * width / 8];
}

/**
 * Copy constructor.
 *
 * @param source
 *            The transparent image to copy from.
 */
transparent_image::transparent_image(const transparent_image &source) :
    image(source)
{
    int size = height * width / 8;
    transparency = new char[size];
    memcpy(transparency, source.transparency, size);
}

/**
 * Destructs this transparent image.
 */
transparent_image::~transparent_image()
{
    delete[] transparency;
}

/**
 * Assignment operator.
 */
transparent_image& transparent_image::operator=(const transparent_image &image)
{
    image::operator=(image);
    delete[] transparency;
    int size = height * width / 8;
    transparency = new char[size];
    memcpy(transparency, image.transparency, size);
    return *this;
}

/**
 * Checks if the pixel at the specified position is transparent. If the
 * specified position is outside of the image then false is returned.
 *
 * @param x
 *            The X position in the image.
 * @param y
 *            The Y position in the image.
 * @return True if pixel is transparent, false if not.
 */
bool transparent_image::is_transparent(const int x, const int y) const
{
    if (y < 0 || x < 0 || x >= width || y >= height) return false;
    int index = (width * y + x) / 8;
    int bit = 128 >> (x % 8);
    return transparency[index] & bit;
}

/**
 * Sets the opacity of the pixel at the specified position of the image. If
 * the specified position is outside of the image then this method does
 * nothing.
 *
 * @param x
 *            The X position in the image.
 * @param y
 *            The Y position in the image.
 * @param transparent
 *            True for a transparent pixel, false for opaque pixel.
 */
void transparent_image::set_transparent(const int x, const int y, const bool transparent)
{
    if (y < 0 || x < 0 || x >= width || y >= height) return;
    int index = (width * y + x) / 8;
    int bit = 128 >> (x % 8);
    if (transparent)
        transparency[index] |= bit;
    else
        transparency[index] &= 0xff ^ bit;
}

}
