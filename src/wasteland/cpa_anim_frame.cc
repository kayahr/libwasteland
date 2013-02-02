/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <cstring>
#include "cpa_anim_frame.h"

using std::istream;
using std::ostream;

namespace wasteland
{

cpa_anim_frame::cpa_anim_frame() : vxor_image(288, 128)
{
}

cpa_anim_frame::cpa_anim_frame(const cpa_anim_frame &other) : vxor_image(288, 128)
{
    memcpy(data, other.data, size);
}

cpa_anim_frame::~cpa_anim_frame()
{
}

cpa_anim_frame& cpa_anim_frame::operator=(const cpa_anim_frame& other)
{
    memcpy(data, other.data, size);
    return *this;
}

}
