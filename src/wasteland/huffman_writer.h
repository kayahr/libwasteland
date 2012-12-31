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
 * Writer to write huffman-compressed data to an output stream.
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

    /**
     * Resets the writer so it can be re-used.
     */
    void reset();

    /**
     * Writes the huffman tree and the compressed bytes to the output stream.
     * and resets the writer so it can be re-used.
     */
    void flush();

private:
    /** The buffer holding the uncompressed data to write. */
    std::vector<uint8_t> buffer;

    /** The list of generated huffman nodes. */
    std::list<huffman_node *> nodes;

    /** Index mapping a payload to a huffman node. */
    std::map<uint8_t, huffman_node *> node_index;

    /** The bit writer used to write compressed data to the output stream. */
    bit_writer *writer;

    /**
     * Writes the specified huffman node to the output stream.
     *
     * @param node
     *            The huffman node to write to the stream.
     */
    void write_node(const huffman_node *node);

    /**
     * Compresses the specified byte and writes the compressed bits of it to
     * the output stream.
     *
     * @param byte
     *            The byte to compress and write to the output stream.
     */
    void write_compressed_byte(const uint8_t byte);
};


}

#endif
