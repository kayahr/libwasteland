/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include "vxor_ostream.h"

using std::ostream;

namespace wasteland
{

vxor_ostream::vxor_ostream(ostream &stream, const int width) : ostream()
{
    buffer = new vxor_streambuf(stream.rdbuf(), width);
    rdbuf(buffer);
}

vxor_ostream::~vxor_ostream()
{
    rdbuf(NULL);
    delete buffer;
}

void vxor_ostream::reset()
{
    buffer->reset();
}

}
