/*
 * Copyright (C) 2013 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <cstring>
#include "pic_anim_frame.h"

using std::istream;
using std::ostream;

namespace wasteland
{

pic_anim_frame::pic_anim_frame() : vxor_image(96, 84)
{
}

pic_anim_frame::pic_anim_frame(const pic_anim_frame &other) :
    vxor_image(96, 84)
{
    memcpy(data, other.data, size);
}

pic_anim_frame::~pic_anim_frame()
{
}

pic_anim_frame& pic_anim_frame::operator=(const pic_anim_frame& other)
{
    memcpy(data, other.data, size);
    return *this;
}

}
