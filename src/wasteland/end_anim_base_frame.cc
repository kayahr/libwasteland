/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <cstring>
#include "end_anim_base_frame.h"

using std::istream;
using std::ostream;

namespace wasteland
{

end_anim_base_frame::end_anim_base_frame()
{
    data = new char[144 * 128];
    memset(data, 0, 144 * 128);
}

end_anim_base_frame::end_anim_base_frame(const end_anim_base_frame &pic)
{
    data = new char[144 * 128];
    memcpy(data, pic.data, 144 * 128);
}

end_anim_base_frame::~end_anim_base_frame()
{
    delete[] data;
}

end_anim_base_frame& end_anim_base_frame::operator=(const end_anim_base_frame& pic)
{
    delete[] data;
    data = new char[144 * 128];
    memcpy(data, pic.data, 144 * 128);
    return *this;
}

bool end_anim_base_frame::operator==(const end_anim_base_frame& pic) const
{
    return !memcmp(data, pic.data, 144 * 128);
}

bool end_anim_base_frame::operator!=(const end_anim_base_frame& pic) const
{
    return !(*this == pic);
}

end_anim_base_frame::size end_anim_base_frame::get_width() const
{
    return 288;
}

end_anim_base_frame::size end_anim_base_frame::get_height() const
{
    return 128;
}

end_anim_base_frame::color end_anim_base_frame::get_color(const coord x, const coord y) const
{
    if (x >= 288 || y >= 128) return 0;

    int index = y * 144 + (x >> 1);
    if (x & 1)
        return data[index] & 0xf;
    else
        return (data[index] & 0xf0) >> 4;
}

void end_anim_base_frame::set_color(const coord x, const coord y, const color color)
{
    if (x >= 288 || y >= 128) return;

    int index = y * 144 + (x >> 1);
    if (x & 1)
        data[index] = (data[index] & 0xf0) | (color & 0xf);
    else
        data[index] = (data[index] & 0xf) | ((color & 0xf) << 4);
}

istream& operator>>(istream& stream, end_anim_base_frame& pic)
{
    stream.read(pic.data, 144 * 128);

    for (int y = 1; y != 128; y += 1)
    {
        for (int x = 0; x != 144; x += 1)
        {
            pic.data[y * 144 + x] ^= pic.data[(y - 1) * 144 + x];
        }
    }

    return stream;
}

ostream& operator<<(ostream& stream, const end_anim_base_frame& pic)
{
    for (int y = 0; y != 128; y += 1)
    {
        for (int x = 0; x != 144; x += 1)
        {
            char key = y ? pic.data[(y - 1) * 144 + x] : 0;
            stream.put(pic.data[y * 144 + x] ^ key);
        }
    }
    return stream;
}

}
