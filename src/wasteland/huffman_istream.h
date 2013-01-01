/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_HUFFMAN_ISTREAM_H
#define LIBWASTELAND_HUFFMAN_ISTREAM_H

#include <istream>
#include "huffman_streambuf.h"

namespace wasteland
{

/**
 * This input stream wraps another input stream and performs huffman
 * decoding on the read data.
 */
class huffman_istream: public std::istream
{
public:
    /**
     * Constructs a new huffman input stream wrapping the given
     * input stream.
     *
     * @param stream
     *            The input stream to wrap.
     */
    huffman_istream(std::istream &stream);

    /**
     * Deconstructs the huffman input stream.
     */
    virtual ~huffman_istream();

    /**
     * Resets the input stream so it can be used for another huffman encoded
     * data structure.
     */
    virtual void reset();

private:
    /** The huffman stream buffer. */
    huffman_streambuf *buffer;
};

}

#endif
