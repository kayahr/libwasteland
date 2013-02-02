/*
 * Copyright (C) 2013 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <cassert>
#include <cstring>
#include "pic_anim_block.h"

using std::istream;
using std::ostream;

namespace wasteland
{

pic_anim_block::pic_anim_block() :
    offset(0),
    size(0),
    data(NULL)
{
}

pic_anim_block::pic_anim_block(const uint16_t offset, const uint8_t size,
    const uint8_t* data) :
    offset(offset),
    size(size)
{
    this->data = new uint8_t[size];
    memcpy(this->data, data, size);
}

pic_anim_block::~pic_anim_block()
{
    if (!data) delete data;
}

uint16_t pic_anim_block::get_offset() const
{
    return offset;
}

void pic_anim_block::set_offset(const uint16_t offset)
{
    this->offset = offset;
}

void pic_anim_block::set_offset(const image::coord x, const image::coord y)
{
    offset = (y * 96 + x) / 2;
}

image::coord pic_anim_block::get_offset_x() const
{
    return offset * 2 % 96;
}

image::coord pic_anim_block::get_offset_y() const
{
    return offset * 2 / 96;
}

uint8_t* pic_anim_block::get_data() const
{
    return data;
}

void pic_anim_block::set_data(const uint8_t size, const uint8_t* data)
{
    this->size = size;
    if (this->data)
    {
        delete this->data;
        this->data = NULL;
    }
    if (data)
    {
        this->data = new uint8_t[size];
        memcpy(this->data, data, size);
    }
}

bool pic_anim_block::operator==(const pic_anim_block& other) const
{
    if (offset != other.offset || size != other.size) return false;
    if (!data && !other.data) return true;
    if (!data || !other.data) return false;
    return memcmp(data, other.data, size) == 0;
}

bool pic_anim_block::operator!=(const pic_anim_block& other) const
{
    return !(*this == other);
}

//void pic_anim_block::apply(pic_anim_frame& frame) const
//{
//    image::coord x = get_offset_x();
//    image::coord y = get_offset_y();
//    for (uint8_t i = 0; i != 8; i += 1)
//    {
//        frame.set_color(x + i, y, get_color(i));
//    }
//}

istream& operator>>(istream& stream, pic_anim_block& block)
{
    uint16_t offset;
    stream.read((char *) &offset, 2);
    if (offset != 0xffff)
    {
        uint8_t size = (offset >> 12) + 1;
        offset &= 0xfff;
        uint8_t data[size];
        stream.read((char *) data, size);
        block.set_offset(offset);
        block.set_data(size, data);
    }
    return stream;
}

ostream& operator<<(ostream& stream, const pic_anim_block& block)
{
    uint8_t size = block.get_size();
    if (size)
    {
        uint16_t offset = block.get_offset() | ((size - 1) << 12);
        stream.write((char *) &offset, 2);
        stream.write((char *) block.get_data(), size);
    }
    else
    {
        uint16_t offset = 0xffff;
        stream.write((char *) &offset, 2);
    }
    return stream;
}

}
