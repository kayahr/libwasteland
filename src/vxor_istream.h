/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_VXOR_ISTREAM_H
#define LIBWASTELAND_VXOR_ISTREAM_H

#include <istream>
#include "vxor_streambuf.h"

namespace wasteland
{

/**
 * This input stream wraps another input stream and performs vertical-xor
 * decoding on the read data.
 */
class vxor_istream: public std::istream
{
public:
    /**
     * Constructs a new vertical-xor input stream wrapping the given
     * input stream and using the given image width.
     *
     * @param stream
     *            The input stream to wrap.
     * @param width
     *            The image width in pixels.
     */
    vxor_istream(std::istream &stream, const int width);

    /**
     * Deconstructs the vertical-xor input stream.
     */
    virtual ~vxor_istream();

    /**
     * Resets the input stream so it can be used for another vertical-xor
     * encoded image.
     */
    virtual void reset();

private:
    /** The vertical-xor stream buffer. */
    vxor_streambuf *buffer;
};

}

#endif
