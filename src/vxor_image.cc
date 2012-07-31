/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <iostream>
#include "vxor_image.h"

namespace wasteland
{

using std::istream;
using std::ostream;


/**
 * Constructs a new vertical-xor encoded image with the specified width and
 * height.
 *
 * @param width
 *            The image width.
 * @param height
 *            The image height.
 */
vxor_image::vxor_image(const int width, const int height) :
    image(width, height)
{
}

/**
 * Reads an vertical-xor encoded image from the specified stream.
 *
 * @return The input stream.
 */
istream& operator>>(istream& stream, vxor_image& image)
{
    int rows = image.height;
    int columns = image.width / 2;

    stream.read(image.data, rows * columns);

    for (int y = 1; y != rows; y += 1)
    {
        for (int x = 0; x != columns; x += 1)
        {
            image.data[y * columns + x] ^= image.data[(y - 1) * columns + x];
        }
    }

    return stream;
}

/**
 * Writes the specified vertical-xor encoded image to the specified output
 * stream.
 *
 * @return The output stream.
 */
ostream& operator<<(ostream& stream, const vxor_image& image)
{
    int rows = image.height;
    int columns = image.width / 2;

    for (int y = 0; y != rows; y += 1)
    {
        for (int x = 0; x != columns; x += 1)
        {
            char key = y ? image.data[(y - 1) * columns + x] : 0;
            stream.put(image.data[y * columns + x] ^ key);
        }
    }
    return stream;
}

}
