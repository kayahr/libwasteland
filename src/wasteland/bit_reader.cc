/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <assert.h>
#include "bit_reader.h"
#include "exceptions.h"

using std::streambuf;

namespace wasteland
{

bit_reader::bit_reader(streambuf &wrap) :
    wrapped(wrap),
    mask(0),
    buffer(0)
{
}

int bit_reader::read_bit()
{
    if (!mask)
    {
        buffer = wrapped.sbumpc();
        if (buffer == streambuf::traits_type::eof()) return buffer;
        mask = 0x80;
    }
    unsigned char tmp = buffer & mask;
    mask >>= 1;
    return tmp ? 1 : 0;

}

int bit_reader::read_bits(const int bits)
{
    assert(bits > 0 && bits <= 8);

    int value = 0;
    for (int i = 0; i != bits; ++i)
    {
        int bit = read_bit();
        if (bit == streambuf::traits_type::eof()) return -1;
        value = value << 1 | bit;
    }
    return value;
}

int bit_reader::read_byte()
{
    return read_bits(8);
}

void bit_reader::reset()
{
    mask = 0;
    buffer = 0;
}

}
