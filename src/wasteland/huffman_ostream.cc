/*
 * Copyright (C) 2013 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include "huffman_ostream.h"

using std::ostream;

namespace wasteland
{

huffman_ostream::huffman_ostream(ostream &stream) : ostream()
{
    buffer = new huffman_streambuf(stream.rdbuf());
    rdbuf(buffer);
}

huffman_ostream::~huffman_ostream()
{
    rdbuf(NULL);
    delete buffer;
}

void huffman_ostream::reset()
{
    buffer->reset();
}

}
