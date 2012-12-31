/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include "vxor_istream.h"

using std::istream;

namespace wasteland
{

vxor_istream::vxor_istream(istream &stream, const int width) :
    istream()
{
    buffer = new vxor_streambuf(stream.rdbuf(), width);
    rdbuf(buffer);
}

vxor_istream::~vxor_istream()
{
    rdbuf(NULL);
    delete buffer;
}

void vxor_istream::reset()
{
    buffer->reset();
}

}
