/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include "sprite.h"

namespace wasteland
{

sprite::sprite()
{
    data = new char[128];
    transparency = new char[32];
}

sprite::~sprite()
{
    delete[] data;
    delete[] transparency;
}

sprite::size sprite::get_width() const
{
    return 16;
}

sprite::size sprite::get_height() const
{
    return 16;
}

sprite::color sprite::get_color(const coord x, const coord y) const
{
    if (x >= 16 || y >= 16) return 0;

    int index = (y << 1) + (x >> 3);
    int b = 7 - (x & 7);
    return ((data[index] >> b) & 1) // Blue
        | (((data[index + 32] >> b) & 1) << 1) // Green
        | (((data[index + 64] >> b) & 1) << 2) // Red
        | (((data[index + 96] >> b) & 1) << 3) // Intensity
        ;
}

void sprite::set_color(const coord x, const coord y, const color color)
{
    if (x >= 16 || y >= 16) return;

    int i = (y << 2) + 3 - (x >> 3);
    int b = 1 << (7 - (x & 7));
    if (color & 1) data[i] |= b; else data[i] &= ~b;             // Blue
    if (color & 2) data[i + 64] |= b; else data[i + 64] &= ~b;   // Green
    if (color & 4) data[i + 128] |= b; else data[i + 128] &= ~b; // Red
    if (color & 8) data[i + 192] |= b; else data[i + 192] &= ~b; // Intensity
}

bool sprite::is_transparent(const coord x, const coord y) const
{
    if (x >= 16 || y >= 16) return true;

    int index = (y << 1) + (x >> 3);
    int b = 7 - (x & 7);
    return (transparency[index] >> b) & 1;
}

void sprite::set_transparent(const coord x, const coord y,
    const bool transparent)
{
    if (x >= 16 || y >= 16) return;
}

sprite_istreams& operator>>(sprite_istreams& streams, sprite& sprite)
{
    streams.color().read(sprite.data, 128);
    streams.opacity().read(sprite.transparency, 32);
    return streams;
}

sprite_ostreams& operator<<(sprite_ostreams& streams, const sprite& sprite)
{
    streams.color().write(sprite.data, 128);
    streams.opacity().write(sprite.transparency, 32);
    return streams;
}

}
