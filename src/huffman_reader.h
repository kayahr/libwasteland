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
    /**
     * Constructor.
     *
     * @param stream
     *            The input stream to wrap.
     */
    explicit huffman_reader(std::istream &stream);

    /**
     * Destructor.
     */
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

    /**
     * Reads a block of data.
     *
     * @param data
     *            The byte array to store the read bytes int.
     * @param size
     *            The number of bytes to read.
     */
    void read(uint8_t *data, const int size);

    /**
     * Resets the reader so it can be re-used.
     */
    void reset();

private:
    /** The bit reader to read bits from the wrapped input stream. */
    bit_reader *reader;

    /** The root node of the huffman tree read from the stream. */
    huffman_node *root;

    /**
     * Reads a single huffman node from the stream.
     *
     * @return The read huffman node.
     */
    huffman_node * read_node();

    /**
     * Returns the root node of the huffman tree. If not already done then
     * the huffman tree is read from the stream.
     *
     * @return The root node of the huffman tree.
     */
    huffman_node * get_root();
};

}

#endif
