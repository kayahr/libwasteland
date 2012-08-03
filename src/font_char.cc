/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include "font_char.h"

using std::istream;
using std::ostream;

namespace wasteland
{

font_char::font_char()
{
    data = new char[32];
}

font_char::~font_char()
{
    delete[] data;
}

font_char::size font_char::get_width() const
{
    return 8;
}

font_char::size font_char::get_height() const
{
    return 8;
}

font_char::color font_char::get_color(const coord x, const coord y) const
{
    if (x >= 8 || y >= 8) return 0;

    int bit = 7 - (x & 7);
    return (((data[y] >> bit) & 1) << 0)     // Blue
        | (((data[y + 8] >> bit) & 1) << 1)  // Green
        | (((data[y + 16] >> bit) & 1) << 2) // Red
        | (((data[y + 24] >> bit) & 1) << 3) // Intensity
        ;
}

void font_char::set_color(const coord x, const coord y, const color color)
{
    if (x >= 8 || y >= 8) return;

    int bit = 1 << (7 - (x & 7));
    if (color & 1) data[y] |= bit; else data[y] &= ~bit;           // Blue
    if (color & 2) data[y + 8] |= bit; else data[y + 8] &= ~bit;   // Green
    if (color & 4) data[y + 16] |= bit; else data[y + 16] &= ~bit; // Red
    if (color & 8) data[y + 24] |= bit; else data[y + 24] &= ~bit; // Intensity
}

istream& operator>>(istream& stream, font_char& c)
{
    return stream.read(c.data, 32);
}

ostream& operator<<(ostream& stream, const font_char& c)
{
    return stream.write(c.data, 32);
}

}
