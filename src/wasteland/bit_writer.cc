/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <assert.h>
#include "bit_writer.h"

using std::ostream;

namespace wasteland
{

bit_writer::bit_writer(ostream &stream) :
    stream(stream),
    mask(0),
    buffer(0)
{
    assert(stream != NULL);
}

void bit_writer::write_bit(const int bit)
{
    assert(bit >= 0 && bit <= 1);

    buffer <<= 1;
    buffer |= bit & 1;
    mask = mask == 0 ? 1 : (mask << 1);
    if (mask == 0x80)
    {
        stream.put(buffer);
        buffer = 0;
        mask = 0;
    }
}

void bit_writer::write_bits(const int value, const int bits)
{
    assert(value <= 0xff);
    assert(bits >= 1 && bits <= 8);

    for (int i = bits - 1; i >= 0; i -= 1) write_bit((value >> i) & 1);
}

void bit_writer::write_byte(const int byte)
{
    assert(byte >= 0 && byte <= 0xff);

    write_bits(byte, 8);
}

void bit_writer::flush()
{
    while (mask) write_bit(0);
}

}
