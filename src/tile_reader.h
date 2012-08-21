/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_TILE_READER_H
#define LIBWASTELAND_TILE_READER_H

#include <istream>
#include "huffman_reader.h"

namespace wasteland
{

/**
 * Reader to read tiles from a ALLHTDS stream.
 */
class tile_reader
{
public:
    /**
     * Constructs a new tile reader reading its data from the specified
     * input stream.
     *
     * @param stream
     *            The stream to read the tile data from.
     */
    explicit tile_reader(std::istream &stream);

    /**
     * Destructor.
     */
    virtual ~tile_reader();

    /**
     * Casts this reader to a boolean so it can be used for EOF checks.
     */
    operator bool() const;

    /**
     * Returns the number of tiles in the tileset.
     *
     * @return The number of tiles.
     */
    int count_tiles();

    /**
     * Returns the tile number of the current tile in the current tileset.
     *
     * @return The tile number.
     */
    int get_tile_no();

    /**
     * Reads the data of the current tile from the current tileset and stores
     * it in the specified byte array which must have room for 8*16 bytes
     * (16x16 pixels, 2 pixels per byte).
     *
     * @param data
     *            The byte array to store the data in.
     */
    void read_tile_data(uint8_t *data);

    /**
     * Returns the disk number of the current tileset.
     *
     * @return The disk number of the current tileset.
     */
    int get_disk();

private:
    /** The input stream to read data from. */
    std::istream &stream;

    /** The reader to read huffman compressed data from. */
    huffman_reader * reader;

    /** The disk number of the current tileset. */
    int disk;

    /** The current tile number. */
    int tile_no;

    /** The number of tiles in the current tileset. */
    int tiles;

    /**
     * Reads the tileset header if not already done.
     */
    void read_header();
};

}

#endif
