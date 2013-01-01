/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_TILE_WRITER_H
#define LIBWASTELAND_TILE_WRITER_H

#include <ostream>
#include "huffman_ostream.h"

namespace wasteland
{

/**
 * Writer to write tiles into a ALLHTDS stream.
 */
class tile_writer
{
public:
    /**
     * Constructs a new tile writer writing its data into the specified
     * output stream.
     *
     * @param stream
     *            The stream to write the tile data to.
     * @param disk
     *            Optioinal disk number to write to the tileset headers.
     */
    explicit tile_writer(std::ostream &stream, const int disk = 0);

    /**
     * Destructor.
     */
    virtual ~tile_writer();

    /**
     * Writes the data of a tile to the stream. The specified byte array
     * must connain 8*16 bytes (16x16 pixels, 2 pixels per byte).
     *
     * @param data
     *            The byte array with the tile data to write.
     */
    void write_tile_data(uint8_t *data);

    /**
     * Completes the tileset and writes it to the output stream.
     */
    void flush();

private:
    /** The output stream to write data to. */
    std::ostream &stream;

    /** The huffman stream to write huffman compressed data. */
    huffman_ostream *huffman;

    /** The number of uncompressed bytes written to the tile buffer. */
    int size;

    /** The disk number. */
    int disk;
};

}

#endif
