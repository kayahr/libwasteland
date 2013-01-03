/*
 * Copyright (C) 2013 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <cstring>
#include "vxor_istream.h"
#include "vxor_ostream.h"
#include "vxor_image.h"

using std::istream;
using std::ostream;

namespace wasteland
{

vxor_image::vxor_image(const image::size width, const image::size height) :

    width(width),
    height(height),
    size(width * height / 2)
{
    data = new char[size];
    memset(data, 0, size);
}

vxor_image::~vxor_image()
{
    delete[] data;
}

bool vxor_image::operator==(const vxor_image& other) const
{
    if (other.get_width() != width || other.get_height() != height)
        return false;
    return !memcmp(data, other.data, size);
}

bool vxor_image::operator!=(const vxor_image& pic) const
{
    return !(*this == pic);
}

image::size vxor_image::get_width() const
{
    return width;
}

image::size vxor_image::get_height() const
{
    return height;
}

vxor_image::color vxor_image::get_color(const coord x, const coord y) const
{
    if (x >= width || y >= height) return 0;

    int index = y * width / 2 + (x >> 1);
    if (x & 1)
        return data[index] & 0xf;
    else
        return (data[index] & 0xf0) >> 4;
}

void vxor_image::set_color(const coord x, const coord y, const color color)
{
    if (x >= width || y >= height) return;

    int index = y * width / 2 + (x >> 1);
    if (x & 1)
        data[index] = (data[index] & 0xf0) | (color & 0xf);
    else
        data[index] = (data[index] & 0xf) | ((color & 0xf) << 4);
}

istream& operator>>(istream& stream, vxor_image& img)
{
    vxor_istream in(stream, img.width);
    in.read(img.data, img.size);
    return stream;
}

ostream& operator<<(ostream& stream, const vxor_image& img)
{
    vxor_ostream out(stream, img.width);
    out.write(img.data, img.size);
    return stream;
}

}
