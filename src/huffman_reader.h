/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_HUFFMAN_READER_H
#define LIBWASTELAND_HUFFMAN_READER_H

#include <istream>
#include <stdint.h>
#include "bit_reader.h"
#include "huffman_node.h"

namespace wasteland
{

/**
 * Reader for huffman input streams.
 */
class huffman_reader
{
public:
    explicit huffman_reader(std::istream &stream);
    virtual ~huffman_reader();

    /**
     * Reads a byte from the wrapped stream.
     *
     * @return The byte which was read from the stream or -1 when read failed.
     */
    int read_byte();

    /**
     * Reads a 16 bit little-endian value from the wrapped stream.
     *
     * @return The 16 bit little-endian value or -1 if an error occurred while
     *         reading.
     */
    int read_word();

private:
    bit_reader *reader;
    huffman_node *root;
    huffman_node * read_node();
    huffman_node * get_root();
};

}

#endif
