/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <iostream>
#include "cursor.h"

using std::istream;
using std::ostream;

namespace wasteland
{

cursor::cursor()
{
    data = new char[256];
}

cursor::~cursor()
{
    delete[] data;
}

cursor::size cursor::get_width() const
{
    return 16;
}

cursor::size cursor::get_height() const
{
    return 16;
}

cursor::color cursor::get_color(const coord x, const coord y) const
{
    if (x >= 16 || y >= 16) return 0;

    int i = (y << 2) + 3 - (x >> 3);
    int b = 7 - (x % 8);
    return (((data[i] >> b) & 1) << 0)      // Blue
        | (((data[i + 64] >> b) & 1) << 1)  // Green
        | (((data[i + 128] >> b) & 1) << 2) // Red
        | (((data[i + 192] >> b) & 1) << 3) // Intensity
        ;
}

void cursor::set_color(const coord x, const coord y, const color color)
{
    if (x >= 16 || y >= 16) return;

    int i = (y << 2) + 3 - (x >> 3);
    int b = 1 << (7 - (x & 7));
    if (color & 1) data[i] |= b; else data[i] &= ~b;             // Blue
    if (color & 2) data[i + 64] |= b; else data[i + 64] &= ~b;   // Green
    if (color & 4) data[i + 128] |= b; else data[i + 128] &= ~b; // Red
    if (color & 8) data[i + 192] |= b; else data[i + 192] &= ~b; // Intensity
}

cursor::opacity cursor::get_opacity(const coord x, const coord y) const
{
    if (x >= 16 || y >= 16) return 0;

    int i = (y << 2) + 1 - (x >> 3);
    int b = 7 - (x & 7);
    return (((data[i] >> b) & 1) << 0)      // Blue
        | (((data[i + 64] >> b) & 1) << 1)  // Green
        | (((data[i + 128] >> b) & 1) << 2) // Red
        | (((data[i + 192] >> b) & 1) << 3) // Intensity
        ;
}

void cursor::set_opacity(const coord x, const coord y, const opacity opacity)
{
    if (x >= 16 || y >= 16) return;

    int i = (y << 2) + 1 - (x >> 3);
    int b = 1 << (7 - (x & 7));
    if (opacity & 1) data[i] |= b; else data[i] &= ~b;             // Blue
    if (opacity & 2) data[i + 64] |= b; else data[i + 64] &= ~b;   // Green
    if (opacity & 4) data[i + 128] |= b; else data[i + 128] &= ~b; // Red
    if (opacity & 8) data[i + 192] |= b; else data[i + 192] &= ~b; // Intensity
}

bool cursor::is_transparent(const coord x, const coord y) const
{
    return !get_opacity(x, y);
}

void cursor::set_transparent(const coord x, const coord y,
    const bool transparent)
{
    set_opacity(x, y, transparent ? 0 : 15);
}

istream& operator>>(istream& stream, cursor& c)
{
    stream.read(c.data, 256);
    return stream;
}

ostream& operator<<(ostream& stream, const cursor& c)
{
    stream.write(c.data, 256);
    return stream;
}

}
