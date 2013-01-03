/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include "end_anim_block.h"

using std::istream;
using std::ostream;

namespace wasteland
{

end_anim_block::end_anim_block() :
    offset(0),
    data(0)
{
}

end_anim_block::end_anim_block(const uint16_t offset, const uint32_t data) :
    offset(offset),
    data(data)
{
}

end_anim_block::~end_anim_block()
{
    // Nothing to do.
}

uint16_t end_anim_block::get_offset() const
{
    return offset;
}

image::coord end_anim_block::get_offset_x() const
{
    return offset * 8 % 320;
}

image::coord end_anim_block::get_offset_y() const
{
    return offset * 8 / 320;
}

uint32_t end_anim_block::get_data() const
{
    return data;
}

image::color end_anim_block::get_color(const uint8_t index) const
{
    uint8_t value = (data >> (index / 2) * 8) & 0xff;
    if (index & 1)
        return value  & 0xf;
    else
        return (value & 0xf0) >> 4;
}

bool end_anim_block::operator==(const end_anim_block& other) const
{
    return data == other.data && offset == other.offset;
}

bool end_anim_block::operator!=(const end_anim_block& other) const
{
    return !(*this == other);
}

void end_anim_block::apply(end_anim_frame& frame) const
{
    image::coord x = get_offset_x();
    image::coord y = get_offset_y();
    for (uint8_t i = 0; i != 8; i += 1)
    {
        frame.set_color(x + i, y, get_color(i));
    }
}

istream& operator>>(istream& stream, end_anim_block& block)
{
    stream.read((char *) &block.offset, 2);
    if (block.offset != 0xffff) stream.read((char *) &block.data, 4);
    return stream;
}

ostream& operator<<(ostream& stream, const end_anim_block& block)
{
    stream.write((char *) &block.offset, 2);
    if (block.offset != 0xffff) stream.write((char *) &block.data, 4);
    return stream;
}

}
