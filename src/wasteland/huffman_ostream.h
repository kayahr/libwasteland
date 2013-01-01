/*
 * Copyright (C) 2013 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_HUFFMAN_OSTREAM_H
#define LIBWASTELAND_HUFFMAN_OSTREAM_H

#include <ostream>
#include "huffman_streambuf.h"

namespace wasteland
{

/**
 * This output stream wraps another output stream and performs huffman
 * encoding on the written data. Make sure to call the <code>flush()</code>
 * method or destroy the instance of this class before you close the wrapped
 * output stream.
 */
class huffman_ostream: public std::ostream
{
public:
    /**
     * Constructs a new huffman output stream wrapping the given
     * output stream. Make sure to call the <code>flush()</code> method or
     * destroy the stream when you are done with the stream to make sure the
     * content is written before the wrapped output stream is closed.
     *
     * @param stream
     *            The output stream to wrap.
     */
    huffman_ostream(std::ostream &stream);

    /**
     * Deconstructs the huffman output stream.
     */
    virtual ~huffman_ostream();

    /**
     * Resets the output stream so it can be used for another huffman encoded
     * data structure. Also calls flush to write any pending data.
     */
    virtual void reset();

private:
    /** The huffman stream buffer. */
    huffman_streambuf *buffer;
};

}

#endif
