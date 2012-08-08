/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <cstring>
#include "sprite.h"

namespace wasteland
{

sprite::sprite()
{
    data = new char[128];
    transparency = new char[32];
    memset(data, 0, 128);
    memset(transparency, 0, 32);
}

sprite::sprite(const sprite &other)
{
    data = new char[128];
    transparency = new char[32];
    memcpy(data, other.data, 128);
    memcpy(transparency, other.transparency, 32);
}

sprite::~sprite()
{
    delete[] data;
    delete[] transparency;
}

sprite& sprite::operator=(const sprite& other)
{
    delete[] data;
    data = new char[128];
    transparency = new char[32];
    memcpy(data, other.data, 128);
    memcpy(transparency, other.transparency, 32);
    return *this;
}


bool sprite::operator==(const sprite& other) const
{
    return !memcmp(data, other.data, 128) &&
        !memcmp(transparency, other.transparency, 32);
}

bool sprite::operator!=(const sprite& other) const
{
    return !(*this == other);
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

    int i = (y << 1) + (x >> 3);
    int b = 7 - (x % 8);
    return (((data[i] >> b) & 1) << 0)      // Blue
        | (((data[i + 32] >> b) & 1) << 1)  // Green
        | (((data[i + 64] >> b) & 1) << 2) // Red
        | (((data[i + 96] >> b) & 1) << 3) // Intensity
        ;
}

void sprite::set_color(const coord x, const coord y, const color color)
{
    if (x >= 16 || y >= 16) return;

    int i = (y << 1) + (x >> 3);
    int b = 1 << (7 - (x & 7));
    if (color & 1) data[i] |= b; else data[i] &= ~b;             // Blue
    if (color & 2) data[i + 32] |= b; else data[i + 32] &= ~b;   // Green
    if (color & 4) data[i + 64] |= b; else data[i + 64] &= ~b; // Red
    if (color & 8) data[i + 96] |= b; else data[i + 96] &= ~b; // Intensity
}

bool sprite::is_transparent(const coord x, const coord y) const
{
    if (x >= 16 || y >= 16) return true;

    int i = (y << 1) + (x >> 3);
    int b = 7 - (x % 8);
    return ((transparency[i] >> b) & 1) << 0;
}

void sprite::set_transparent(const coord x, const coord y,
    const bool transparent)
{
    if (x >= 16 || y >= 16) return;

    int i = (y << 1) + (x >> 3);
    int b = 1 << (7 - (x & 7));
    if (transparent) transparency[i] |= b; else transparency[i] &= ~b;
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
