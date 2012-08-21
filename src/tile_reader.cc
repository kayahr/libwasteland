/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <iostream>
#include "tile_reader.h"
#include "exceptions.h"

using std::istream;

namespace wasteland
{

tile_reader::tile_reader(istream &stream):
    stream(stream),
    tiles(0),
    tile_no(0),
    disk(0)
{
    reader = new huffman_reader(stream);
}

tile_reader::~tile_reader()
{
    delete reader;
}

tile_reader::operator bool() const
{
    return (bool) stream;
}

void tile_reader::read_header()
{
    // Nothing to do if header is already read.
    if (tiles) return;

    // Read the size from the stream.
    uint8_t b[4];
    if (!stream.read((istream::char_type*) b, 4))
    {
        disk = 0;
        tiles = 0;
        return;
    }
    int size = b[0] | (b[1] << 8) | (b[2] << 16) | (b[3] << 24);

    // Read and validate the MSQ header.
    if (!stream.read((istream::char_type*) b, 4)) throw eos_error();
    if (b[0] != 'm' || b[1] != 's' || b[2] != 'q' || (b[3] != 0 && b[3] != 1))
        throw io_error("MSQ header of tileset not found");
    disk = b[3];

    // Calculate the number of tiles in the current tileset
    tiles = size * 2 / 16 / 16;
}

int tile_reader::count_tiles()
{
    read_header();
    return tiles;
}

int tile_reader::get_tile_no()
{
    return tile_no;
}

void tile_reader::read_tile_data(uint8_t *data)
{
    read_header();
    reader->read(data, 8 * 16);
    for (int y = 1; y != 16; y += 1)
    {
        for (int x = 0; x != 8; x += 1)
        {
            data[y * 8 + x] ^= data[(y - 1) * 8 + x];
        }
    }

    // Increase current tile number and reset tileset if last tile was read
    tile_no += 1;
    if (tile_no == tiles)
    {
        tiles = 0;
        tile_no = 0;
        reader->reset();
        read_header();
    }
}

int tile_reader::get_disk()
{
    read_header();
    return disk;
}

}
