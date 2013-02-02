/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <cassert>
#include "cpa_anim_block.h"

using std::istream;
using std::ostream;

namespace wasteland
{

cpa_anim_block::cpa_anim_block() :
    offset(0),
    data(0)
{
}

cpa_anim_block::cpa_anim_block(const uint16_t offset, const uint32_t data) :
    offset(offset),
    data(data)
{
}

cpa_anim_block::cpa_anim_block(const cpa_anim_frame &frame,
    const image::coord x, const image::coord y)
{
    set_offset(x, y);
    for (int i = 0; i < 8; i++) set_color(i, frame.get_color(x + i, y));
}

cpa_anim_block::~cpa_anim_block()
{
    // Nothing to do.
}

uint16_t cpa_anim_block::get_offset() const
{
    return offset;
}

void cpa_anim_block::set_offset(const uint16_t offset)
{
    this->offset = offset;
}

void cpa_anim_block::set_offset(const image::coord x, const image::coord y)
{
    offset = (y * 320 + x) / 8;
}

image::coord cpa_anim_block::get_offset_x() const
{
    return offset * 8 % 320;
}

image::coord cpa_anim_block::get_offset_y() const
{
    return offset * 8 / 320;
}

uint32_t cpa_anim_block::get_data() const
{
    return data;
}

image::color cpa_anim_block::get_color(const uint8_t index) const
{
    assert(index < 8);

    uint8_t value = (data >> (index / 2) * 8) & 0xff;
    if (index & 1)
        return value  & 0xf;
    else
        return (value & 0xf0) >> 4;
}

void cpa_anim_block::set_color(const uint8_t index, const image::color color)
{
    assert(index < 8);

    uint32_t value = (color & 0xf) << (index / 2) * 8;
    uint32_t mask = 0xf << (index / 2) * 8;
    if (!(index & 1))
    {
        value <<= 4;
        mask <<= 4;
    }
    data &= ~mask;
    data |= value;
}

bool cpa_anim_block::operator==(const cpa_anim_block& other) const
{
    return data == other.data && offset == other.offset;
}

bool cpa_anim_block::operator!=(const cpa_anim_block& other) const
{
    return !(*this == other);
}

void cpa_anim_block::apply(cpa_anim_frame& frame) const
{
    image::coord x = get_offset_x();
    image::coord y = get_offset_y();
    for (uint8_t i = 0; i != 8; i += 1)
    {
        frame.set_color(x + i, y, get_color(i));
    }
}

istream& operator>>(istream& stream, cpa_anim_block& block)
{
    stream.read((char *) &block.offset, 2);
    if (block.offset != 0xffff) stream.read((char *) &block.data, 4);
    return stream;
}

ostream& operator<<(ostream& stream, const cpa_anim_block& block)
{
    stream.write((char *) &block.offset, 2);
    if (block.offset != 0xffff) stream.write((char *) &block.data, 4);
    return stream;
}

}
