/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_BIT_WRITER_H
#define LIBWASTELAND_BIT_WRITER_H

#include <ostream>

namespace wasteland
{

/**
 * Writer for bit-wise writing to an output stream. Wraps an output stream and
 * provides methods to write single bits to it.
 */
class bit_writer
{
public:

    /**
     * Constructor.
     *
     * @param stream
     *            The output stream to wrap.
     */
    explicit bit_writer(std::ostream &stream);

    /**
     * Writes a single bit to the wrapped output stream. Make sure to call the
     * flush method after you have written the last bit to ensure that buffered
     * bits are correctly written to the stream.
     *
     * @param bit
     *            The bit to write. 0 or 1.
     */
    void write_bit(const int bit);

    /**
     * Writes a number of bits to the wrapped output stream. Make sure to call
     * the flush method after you have written the last data to ensure that
     * buffered bits are correctly written to the stream.
     *
     * @param value
     *            The value to write.
     * @param bits
     *            The number of bits from value to write.
     */
    void write_bits(const int value, const int bits);

    /**
     * Writes a byte to the wrapped output stream. Make sure to call the flush
     * method after you have written the last data to ensure that buffered bits
     * are correctly written to the stream.
     *
     * @param byte
     *            The byte to write to the stream.
     */
    void write_byte(const int byte);

    /**
     * Flushes the writer so bits which are still in the buffer are actually
     * written to the wrapped output stream. The current byte is filled with
     * cleared bits if necessary.
     */
    void flush();


private:

    /** The wrapped output stream. */
    std::ostream &stream;

    /** The buffered bits. */
    int buffer;

    /** The current buffer bit mask. */
    int mask;

};

}

#endif
