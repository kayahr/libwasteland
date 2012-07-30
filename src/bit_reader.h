/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_BIT_READER_H
#define LIBWASTELAND_BIT_READER_H

#include <istream>

namespace wasteland
{

/**
 * Reader for bit-wise access to an input stream. Wraps an input stream and
 * provides methods to read single bits from it.
 */
class bit_reader
{
public:
    explicit bit_reader(std::istream &stream);
    int read_bit();
    int read_bits(const int bits);

private:
    int index;
    unsigned char value;
    std::istream &stream;
};

}

#endif
