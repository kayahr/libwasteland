/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_VXOR_STREAMBUF_H
#define LIBWASTELAND_VXOR_STREAMBUF_H

#include <streambuf>
#include <istream>

namespace wasteland
{

/**
 * Stream buffer implementation to read and write vertical-xor encoded
 * data. Instead of using this class you can use the {@link vxor_istream} and
 * {@link vxor_ostream} classes.
 */
class vxor_streambuf: public std::streambuf
{
public:
    /**
     * Constructs a vertical XOR stream buffer wrapping the specified stream
     * buffer.
     *
     * @param buffer
     *            The wrapped stream buffer
     * @param width
     *            The image width in pixels.
     */
    vxor_streambuf(std::streambuf *buffer, const int width);

    /**
     * Deconstructs the vertical XOR stream buffer.
     */
    virtual ~vxor_streambuf();

    /**
     * Resets the buffer so it can be re-used to read or write another
     * vertical-xor encoded image.
     */
    virtual void reset();

    /**
     * Reads the next line from the wrapped stream buffer into this buffer
     * and decodes it.
     *
     * @return The value of the character pointed to by the get pointer after
     *         the call on success, or traits::eof() otherwise.
     */
    virtual std::streambuf::int_type underflow();

    /**
     * Encodes the current buffer and writes it to the wrapped buffer.
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

    /** The image width in pixels. */
    int size;

    /** The pixels of the previous line. */
    char *previous_line;

    /** The pixels of the current line. */
    char *current_line;
};

}

#endif
