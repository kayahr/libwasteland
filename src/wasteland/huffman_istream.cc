/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include "huffman_istream.h"

using std::istream;

namespace wasteland
{

huffman_istream::huffman_istream(istream &stream) :
    istream()
{
    buffer = new huffman_streambuf(stream.rdbuf());
    rdbuf(buffer);
}

huffman_istream::~huffman_istream()
{
    rdbuf(NULL);
    delete buffer;
}

void huffman_istream::reset()
{
    buffer->reset();
}

}
