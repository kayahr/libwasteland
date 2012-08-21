/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <cstring>
#include "title_pic.h"

using std::istream;
using std::ostream;

namespace wasteland
{

title_pic::title_pic()
{
    data = new char[144 * 128];
    memset(data, 0, 144 * 128);
}

title_pic::title_pic(const title_pic &pic)
{
    data = new char[144 * 128];
    memcpy(data, pic.data, 144 * 128);
}

title_pic::~title_pic()
{
    delete[] data;
}

title_pic& title_pic::operator=(const title_pic& pic)
{
    delete[] data;
    data = new char[144 * 128];
    memcpy(data, pic.data, 144 * 128);
    return *this;
}

bool title_pic::operator==(const title_pic& pic) const
{
    return !memcmp(data, pic.data, 144 * 128);
}

bool title_pic::operator!=(const title_pic& pic) const
{
    return !(*this == pic);
}

title_pic::size title_pic::get_width() const
{
    return 288;
}

title_pic::size title_pic::get_height() const
{
    return 128;
}

title_pic::color title_pic::get_color(const coord x, const coord y) const
{
    if (x >= 288 || y >= 128) return 0;

    int index = y * 144 + (x >> 1);
    if (x & 1)
        return data[index] & 0xf;
    else
        return (data[index] & 0xf0) >> 4;
}

void title_pic::set_color(const coord x, const coord y, const color color)
{
    if (x >= 288 || y >= 128) return;

    int index = y * 144 + (x >> 1);
    if (x & 1)
        data[index] = (data[index] & 0xf0) | (color & 0xf);
    else
        data[index] = (data[index] & 0xf) | ((color & 0xf) << 4);
}

istream& operator>>(istream& stream, title_pic& pic)
{
    stream.read(pic.data, 144 * 128);

    for (int y = 1; y != 128; y += 1)
    {
        for (int x = 0; x != 144; x += 1)
        {
            pic.data[y * 144 + x] ^= pic.data[(y - 1) * 144 + x];
        }
    }

    return stream;
}

ostream& operator<<(ostream& stream, const title_pic& pic)
{
    for (int y = 0; y != 128; y += 1)
    {
        for (int x = 0; x != 144; x += 1)
        {
            char key = y ? pic.data[(y - 1) * 144 + x] : 0;
            stream.put(pic.data[y * 144 + x] ^ key);
        }
    }
    return stream;
}

}
