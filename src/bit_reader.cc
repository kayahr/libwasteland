/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include "bit_reader.h"

using std::istream;

namespace wasteland
{

/**
 * Constructor.
 *
 * @param stream
 *            The input stream to wrap.
 */
bit_reader::bit_reader(istream &stream) :
    stream(stream), index(7), value(0)
{
}

/**
 * Reads a single bit from the wrapped stream and returns it.
 *
 * @return The read bit or -1 when end of stream has been reached.
 */
int bit_reader::read_bit()
{
    if (!stream) return -1;

    // Read byte from wrapped stream if needed
    if (index == 7) if (!(stream >> value)) return -1;

    // Increment the bit index
    index = (index + 1) % 8;

    // Read bit at current index and return it
    return (value >> index) & 1;
}

/**
 * Reads the specified number of bits from the wrapped stream and returns it.
 *
 * @param bits
 *            The number of bits to read.
 * @return The read bits. -1 if end of stream has been reached.
 */
int bit_reader::read_bits(const int bits)
{
    int value = 0;
    for (int i = 0; i != bits; ++i)
    {
        int bit = read_bit();
        if (bit == -1) return -1;
        value |= bit << i;
    }
    return value;
}

}
