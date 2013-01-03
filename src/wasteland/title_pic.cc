/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <cstring>
#include "title_pic.h"
#include "vxor_istream.h"
#include "vxor_ostream.h"
#include "exceptions.h"

using std::istream;
using std::ostream;

namespace wasteland
{

title_pic::title_pic() : vxor_image(288, 128)
{
}

title_pic::title_pic(const title_pic &other) : vxor_image(288, 128)
{
    memcpy(data, other.data, size);
}

title_pic::~title_pic()
{
}

title_pic& title_pic::operator=(const title_pic& other)
{
    delete[] data;
    data = new char[size];
    memcpy(data, other.data, size);
    return *this;
}

}
