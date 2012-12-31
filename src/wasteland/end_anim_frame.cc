/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include "end_anim_frame.h"

namespace wasteland
{

end_anim_frame::end_anim_frame()
{
    this->delay = 0;
}

end_anim_frame::end_anim_frame(const uint16_t delay)
{
    this->delay = delay;
}

end_anim_frame::~end_anim_frame()
{
    // Nothing to do.
}

uint16_t end_anim_frame::get_delay() const
{
    return delay;
}

void end_anim_frame::set_delay(const uint16_t delay)
{
    this->delay = delay;
}

}
