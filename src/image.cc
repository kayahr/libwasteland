/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <cstring>
#include "image.h"

namespace wasteland
{

/**
 * Constructs a new image with the specified size.
 *
 * @param width
 *            The image width.
 * @param height
 *            The image height.
 */
image::image(const int width, const int height) :
    width(width), height(height)
{
	data = new char[height * width / 2];
}

/**
 * Copy constructor.
 *
 * @param image
 *            The image to copy from.
 */
image::image(const image &image) :
    width(image.width), height(image.height)
{
    int size = height * width / 2;
    data = new char[size];
    memcpy(data, image.data, size);
}

/**
 * Destructor.
 */
image::~image()
{
	delete[] data;
}

/**
 * Assignment operator.
 */
image& image::operator=(const image &image)
{
    delete[] data;
    width = image.width;
    height = image.height;
    int size = height * width / 2;
    data = new char[size];
    memcpy(data, image.data, size);
    return *this;
}

/**
 * Returns the image width.
 *
 * @return The image width.
 */
int image::get_width() const
{
	return width;
}

/**
 * Returns the image height.
 *
 * @return The image height.
 */
int image::get_height() const
{
	return height;
}

/**
 * Returns the color at the specified position of the image. If the specified
 * position is outside of the image then 0 (black) is returned.
 *
 * @param x
 *            The X position in the image.
 * @param y
 *            The Y position in the image.
 * @return The color.
 */
image::color image::get_color(const int x, const int y) const
{
	if (y < 0 || x < 0 || x >= width || y >= height) return 0;
	int index = (width * y + x) / 2;
	if (x & 1)
	    return (data[index] & 0xf0) >> 4;
	else
	    return data[index] & 0xf;
}

/**
 * Sets the color at the specified position of the image. If the specified
 * position is outside of the image then this method does nothing.
 *
 * @param x
 *            The X position in the image.
 * @param y
 *            The Y position in the image.
 * @param color
 *            The color to set. Only the first 4 bit of the value is used.
 */
void image::set_color(const int x, const int y, const image::color color)
{
    if (y < 0 || x < 0 || x >= width || y >= height) return;
    int index = (width * y + x) / 2;
    if (x & 1)
        data[index] = (data[index] & 0xf) | ((color & 0xf) << 4);
    else
        data[index] = (data[index] & 0xf0) | (color & 0xf);
}

}
