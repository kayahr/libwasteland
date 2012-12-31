/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_VXOR_OSTREAM_H
#define LIBWASTELAND_VXOR_OSTREAM_H

#include <ostream>
#include "vxor_streambuf.h"

namespace wasteland
{

/**
 * This output stream wraps another output stream and performs vertical-xor
 * encoding on the written data. Make sure to call the <code>flush()</code>
 * method or destroy the instance of this class before you close the wrapped
 * output stream.
 */
class vxor_ostream: public std::ostream
{
public:
    /**
     * Constructs a new vertical-xor output stream wrapping the given
     * output stream and using the given image width. Make sure to call
     * the <code>flush()</code> method or destroy the stream when you are done
     * with the stream to make sure the content is written before the wrapped
     * output stream is closed.
     *
     * @param stream
     *            The output stream to wrap.
     * @param width
     *            The image width in pixels.
     */
    vxor_ostream(std::ostream &stream, const int width);

    /**
     * Deconstructs the vertical-xor output stream.
     */
    virtual ~vxor_ostream();

    /**
     * Resets the output stream so it can be used for another vertical xor
     * encoded image. Also calls flush to write any pending data.
     */
    virtual void reset();

private:
    /** The vertical-xor stream buffer. */
    vxor_streambuf *buffer;
};

}

#endif
