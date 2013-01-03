/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <cstring>
#include "end_anim_frame.h"

using std::istream;
using std::ostream;

namespace wasteland
{

end_anim_frame::end_anim_frame() : vxor_image(288, 128)
{
}

end_anim_frame::end_anim_frame(const end_anim_frame &other) : vxor_image(288, 128)
{
    memcpy(data, other.data, size);
}

end_anim_frame::~end_anim_frame()
{
}

end_anim_frame& end_anim_frame::operator=(const end_anim_frame& other)
{
    memcpy(data, other.data, size);
    return *this;
}

}
