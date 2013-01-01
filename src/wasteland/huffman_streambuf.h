/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_HUFFMAN_STREAMBUF_H
#define LIBWASTELAND_HUFFMAN_STREAMBUF_H

#include <vector>
#include <list>
#include <map>
#include <streambuf>
#include "bit_reader.h"
#include "bit_writer.h"
#include "huffman_node.h"

namespace wasteland
{

/**
 * Stream buffer implementation to read and write huffman encoded data.
 * Instead of using this class you can use the {@link huffman_istream} and
 * {@link huffman_ostream} classes.
 */
class huffman_streambuf: public std::streambuf
{
public:
    /**
     * Constructs a huffman stream buffer wrapping the specified stream buffer.
     *
     * @param buffer
     *            The wrapped stream buffer.
     */
    huffman_streambuf(std::streambuf *buffer);

    /**
     * Deconstructs the huffman stream buffer.
     */
    virtual ~huffman_streambuf();

    /**
     * Resets the buffer so it can be re-used for the next huffman endoded
     * data structure.
     */
    virtual void reset();

    /**
     * Reads the next byte from the wrapped stream into the huffman stream
     * buffer.
     *
     * @return The value of the character pointed to by the get pointer after
     *         the call on success, or traits::eof() otherwise.
     */
    virtual std::streambuf::int_type underflow();

    /**
     * Writes a completed byte to the wrapped buffer.
     *
     * @return Unspecified value not equal to traits::eof() on success,
     *         traits::eof() on failure.
     */
    virtual std::streambuf::int_type overflow(std::streambuf::int_type);

    /**
     * Synchronizes this buffer and the wrapped buffer.
     */
    virtual int sync();

private:
    /** The wrapped stream buffer. */
    std::streambuf *buffer;

    /** The current byte. */
    char value;

    /** The bit reader to read bits from the wrapped input stream. */
    bit_reader *reader;

    /** The root node of the huffman tree read from the stream. */
    huffman_node *root;

    /** The buffer holding the uncompressed values to write. */
    std::vector<uint8_t> values;

    /** The list of generated huffman nodes. */
    std::list<huffman_node *> nodes;

    /** Index mapping a payload to a huffman node. */
    std::map<uint8_t, huffman_node *> node_index;

    /** The bit writer used to write compressed data to the output stream. */
    bit_writer *writer;

    /**
     * Returns the root node of the huffman tree. If not already done then
     * the huffman tree is read from the stream.
     *
     * @return The root node of the huffman tree.
     */
    huffman_node * get_root();

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
