/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <cstring>
#include "tile.h"

using std::istream;
using std::ostream;

namespace wasteland
{

tile::tile()
{
    data = new uint8_t[8 * 16];
    memset(data, 0, 8 * 16);
}

tile::tile(const tile &other)
{
    data = new uint8_t[8 * 16];
    memcpy(data, other.data, 8 * 16);
}

tile::~tile()
{
    delete[] data;
}

tile& tile::operator=(const tile& other)
{
    delete[] data;
    data = new uint8_t[8 * 16];
    memcpy(data, other.data, 8 * 16);
    return *this;
}

bool tile::operator==(const tile& other) const
{
    return !memcmp(data, other.data, 8 * 16);
}

bool tile::operator!=(const tile& other) const
{
    return !(*this == other);
}

tile::size tile::get_width() const
{
    return 16;
}

tile::size tile::get_height() const
{
    return 16;
}

tile::color tile::get_color(const coord x, const coord y) const
{
    if (x >= 16 || y >= 16) return 0;

    int index = y * 8 + (x >> 1);
    if (x & 1)
        return data[index] & 0xf;
    else
        return (data[index] & 0xf0) >> 4;
}

void tile::set_color(const coord x, const coord y, const color color)
{
    if (x >= 16 || y >= 16) return;

    int index = y * 8 + (x >> 1);
    if (x & 1)
        data[index] = (data[index] & 0xf0) | (color & 0xf);
    else
        data[index] = (data[index] & 0xf) | ((color & 0xf) << 4);
}

tile_reader& operator>>(tile_reader& reader, tile& image)
{
    reader.read_tile_data(image.data);
    return reader;
}

tile_writer& operator<<(tile_writer& writer, const tile& image)
{
    writer.write_tile_data(image.data);
    return writer;
}

}
