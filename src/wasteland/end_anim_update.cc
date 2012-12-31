/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include "end_anim_update.h"
#include <iostream>

namespace wasteland
{

end_anim_update::end_anim_update(const uint16_t offset, const uint32_t update)
{
    this->offset = offset;
    this->update = update;
}

end_anim_update::~end_anim_update()
{
    // Nothing to do.
}

uint16_t end_anim_update::get_offset() const
{
    return offset;
}

image::coord end_anim_update::get_offset_x() const
{
    return offset * 8 % 320;
}

image::coord end_anim_update::get_offset_y() const
{
    return offset * 8 / 320;
}

uint32_t end_anim_update::get_update() const
{
    return update;
}

image::color end_anim_update::get_color(const uint8_t index) const
{
    uint8_t value = (update >> (4 - index / 2)) & 0xff;
    if (index & 1)
        return value  & 0xf;
    else
        return (value & 0xf0) >> 4;
}

}
