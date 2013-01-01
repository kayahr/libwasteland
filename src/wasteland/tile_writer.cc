/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <iostream>
#include "tile_writer.h"
#include "vxor_ostream.h"
#include "exceptions.h"

using std::ostream;

namespace wasteland
{

tile_writer::tile_writer(ostream &stream, const int disk):
    stream(stream),
    size(0),
    disk(disk)
{
    huffman = new huffman_ostream(stream);
}

tile_writer::~tile_writer()
{
    delete huffman;
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
    huffman->flush();

    // Reset the size
    size = 0;
}

void tile_writer::write_tile_data(uint8_t *data)
{
    vxor_ostream vxor(*huffman, 16);
    vxor.write((char *) data, 16 * 8);
    vxor.flush();

    // Increase data size counter
    size += 16 * 8;
}

}
