/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <iostream>
#include "pic_reader.h"

using std::istream;

namespace wasteland
{

/**
 * Constructor.
 *
 * @param stream
 *            The input stream to wrap.
 */
pic_reader::pic_reader(istream &stream) :
    stream_(stream)
{
}

/**
 * Reads a single bit from the wrapped stream and returns it.
 *
 * @return The read bit or -1 when end of stream has been reached.
 */
pic_reader &pic_reader::operator>>(image &pic)
{
	char byte;
	unsigned char xor1, xor2;

    for (int y = 0, max_y = pic.height(); y != max_y; y += 1)
    {
        for (int x = 0, max_x = pic.width(); x != max_x; x += 2)
        {
        	byte = stream_.get();
            xor1 = (y == 0 ? 0 : pic(x, y - 1));
            xor2 = (y == 0 ? 0 : pic(x + 1, y - 1));
            pic(x, y) = (byte >> 4) ^ xor1;
            pic(x + 1, y) = (byte & 0xf) ^ xor2;
        }
    }

	return *this;
}

}
