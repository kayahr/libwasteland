/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_HUFFMAN_WRITER_H
#define LIBWASTELAND_HUFFMAN_WRITER_H

#include <ostream>
#include <stdint.h>
#include <list>
#include <map>
#include <vector>
#include "bit_writer.h"
#include "huffman_node.h"

namespace wasteland
{

/**
 * Reader for huffman input streams.
 */
class huffman_writer
{
public:
    /**
     * Constructs a new huffman writer which wraps the specified output stream.
     *
     * @param stream
     *            The output stream to wrap.
     */
    explicit huffman_writer(std::ostream &stream);

    /**
     * Destructs this huffman writer.
     */
    virtual ~huffman_writer();

    /**
     * Writes a byte.
     *
     * @param value
     *            The byte value to write.
     */
    void write_byte(const uint8_t value);

    /**
     * Writes a 16 bit little-endian value.
     *
     * @param value
     *            The 16 bit little-endian value to write.
     */
    void write_word(const uint16_t value);

    void reset();

    void flush();

private:
    std::vector<uint8_t> buffer;
    std::list<huffman_node *> nodes;
    std::map<uint8_t, huffman_node *> node_index;
    bit_writer *writer;

    void write_node(const huffman_node *node);
    void write_compressed_byte(const uint8_t byte);
};


}

#endif
