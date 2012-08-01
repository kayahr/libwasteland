/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <cstring>
#include <stdexcept>
#include "image.h"

using std::invalid_argument;

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
image::image(const int width, const int height)
{
    if (width < 1 || height < 1)
        throw invalid_argument("width and height must be > 0");
    this->width = width;
    this->height = height;
    int size = get_data_size(width, height);
    data = new char[size];
    memset(data, 0, size);
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
    int size = get_data_size(width, height);
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
    int size = get_data_size(width, height);
    data = new char[size];
    memcpy(data, image.data, size);
    return *this;
}

/**
 * Calculates and returns the data size for the specified image size.
 *
 * @param width
 *            The image width.
 * @param height
 *            The image height.
 * @return The data size.
 */
int image::get_data_size(const int width, const int height) const
{
    int data_width = width / 2 + ((width % 2) ? 1 : 0);
    return data_width * height;
}

/**
 * Calculates and returns the index in the data for the specified image
 * position.
 *
 * @param x
 *            The X position in the image.
 * @param y
 *            The Y position in the image.
 * @return THe index.
 */
int image::get_data_index(const int x, const int y) const
{
    int data_width = width / 2 + ((width % 2) ? 1 : 0);
    return data_width * y + x / 2;
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
    int index = get_data_index(x, y);
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
    int index = get_data_index(x, y);
    if (x & 1)
        data[index] = (data[index] & 0xf) | ((color & 0xf) << 4);
    else
        data[index] = (data[index] & 0xf0) | (color & 0xf);
}

}
