/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <iostream>
#include "tile_writer.h"
#include "exceptions.h"

using std::ostream;

namespace wasteland
{

tile_writer::tile_writer(ostream &stream, const int disk):
    stream(stream),
    size(0),
    disk(disk)
{
    writer = new huffman_writer(stream);
}

tile_writer::~tile_writer()
{
    delete writer;
}

void tile_writer::flush()
{
    // Write the size
    stream.put(size & 0xff);
    stream.put((size >> 8) & 0xff);
    stream.put((size >> 16) & 0xff);
    stream.put((size >> 24) & 0xff);

    // Write MSQ header
    stream.put('m');
    stream.put('s');
    stream.put('q');

    // Write disk number
    stream.put(disk);

    // Write the compressed tile data
    writer->flush();

    // Reset the size
    size = 0;
}

void tile_writer::write_tile_data(uint8_t *data)
{
    for (int y = 0; y != 16; y += 1)
    {
        for (int x = 0; x != 8; x += 1)
        {
            char key = y ? data[(y - 1) * 8 + x] : 0;
            writer->write_byte(data[y * 8 + x] ^ key);
        }
    }

    // Increase data size counter
    size += 16 * 8;
}

}
