/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_BIT_READER_H
#define LIBWASTELAND_BIT_READER_H

#include <streambuf>
#include <stdint.h>

namespace wasteland
{

/**
 * Reader for bit-wise access to a stream buffer. Wraps a stream buffer and
 * provides methods to read single bits from it.
 */
class bit_reader
{
public:
    /**
     * Constructor.
     *
     * @param wrap
     *            The stream buffer to wrap.
     */
    explicit bit_reader(std::streambuf &wrap);

    /**
     * Reads a single bit from the wrapped stream buffer and returns it.
     *
     * @return The read bit or EOF when end of stream has been reached.
     */
    int read_bit();

    /**
     * Reads the specified number of bits from the wrapped stream buffer and
     * returns it.
     *
     * @param bits
     *            The number of bits to read. Must be between 1 and 8.
     * @return The read bits or EOF if end of stream has been reached.
     */
    int read_bits(const int bits);

    /**
     * Reads a byte from the wrapped stream buffer and returns it.
     *
     * @return The read byte or EOF if end of stream has been reached.
     */
    int read_byte();

    /**
     * Resets the reader so it can be re-used.
     */
    void reset();

private:
    /** The wrapped stream buffer. */
    std::streambuf &wrapped;

    /** Buffered bits. */
    int buffer;

    /** Current buffer mask. */
    int mask;
};

}

#endif
