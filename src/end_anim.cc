/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <cstring>
#include "huffman_reader.h"
#include "exceptions.h"
#include "end_anim.h"

using std::istream;
using std::ostream;

namespace wasteland
{

end_anim::end_anim()
{
    data = new char[144 * 128];
    memset(data, 0, 144 * 128);
}

end_anim::end_anim(const end_anim &animation)
{
    data = new char[144 * 128];
    memcpy(data, animation.data, 144 * 128);
}

end_anim::~end_anim()
{
    delete[] data;
}

end_anim& end_anim::operator=(const end_anim& animation)
{
    delete[] data;
    data = new char[144 * 128];
    memcpy(data, animation.data, 144 * 128);
    return *this;
}

bool end_anim::operator==(const end_anim& animation) const
{
    return !memcmp(data, animation.data, 144 * 128);
}

bool end_anim::operator!=(const end_anim& animation) const
{
    return !(*this == animation);
}

end_anim::size end_anim::get_width() const
{
    return 288;
}

end_anim::size end_anim::get_height() const
{
    return 128;
}

end_anim::color end_anim::get_color(const coord x, const coord y) const
{
    if (x >= 288 || y >= 128) return 0;

    int index = y * 144 + (x >> 1);
    if (x & 1)
        return data[index] & 0xf;
    else
        return (data[index] & 0xf0) >> 4;
}

void end_anim::set_color(const coord x, const coord y, const color color)
{
    if (x >= 288 || y >= 128) return;

    int index = y * 144 + (x >> 1);
    if (x & 1)
        data[index] = (data[index] & 0xf0) | (color & 0xf);
    else
        data[index] = (data[index] & 0xf) | ((color & 0xf) << 4);
}

const std::vector<end_anim_frame> end_anim::get_frames() const
{
    return frames;
}

std::vector<end_anim_frame> end_anim::get_frames()
{
    return frames;
}

istream& operator>>(istream& stream, end_anim& pic)
{
    // Read the size of the base frame block
    uint8_t b[4];
    if (!stream.read((istream::char_type*) b, 4)) throw eos_error();
    int size = b[0] | (b[1] << 8) | (b[2] << 16) | (b[3] << 24);
    if (size != 288 * 128 / 2)
        throw io_error("Base frame block has invalid size");

    // Read and validate the MSQ header of the base frame block
    if (!stream.read((istream::char_type*) b, 4)) throw eos_error();
    if (b[0] != 'm' || b[1] != 's' || b[2] != 'q' || (b[3] != 0))
        throw io_error("MSQ header of base frame block not found");

    // Read the base frame
    huffman_reader reader(stream);
    reader.read((uint8_t *) pic.data, 144 * 128);
    for (int y = 1; y != 128; y += 1)
    {
        for (int x = 0; x != 144; x += 1)
        {
            pic.data[y * 144 + x] ^= pic.data[(y - 1) * 144 + x];
        }
    }
    reader.reset();

    // Read the size of the animation data block
    if (!stream.read((istream::char_type*) b, 4)) throw eos_error();
    size = b[0] | (b[1] << 8) | (b[2] << 16) | (b[3] << 24);

    // Read and validate the MSQ header of the animation data block
    if (!stream.read((istream::char_type*) b, 4)) throw eos_error();
    if (b[0] != 0x08 || b[1] != 0x67 || b[2] != 0x01 || (b[3] != 0))
        throw io_error("MSQ header of animation data block not found");

    // Read the animation data size
    reader.read(b, 2);
    int data_size = b[0] | (b[1] << 8);
    if (data_size != size - 4)
        throw io_error("Animation data block size not matching MSQ size");

    // Read the frames
    reader.read(b, 2);
    uint16_t delay = b[0] | (b[1] << 8);
    reader.read(b, 2);
    uint16_t offset = b[0] | (b[1] << 8);
    while (offset != 0x0000)
    {
        end_anim_frame frame(delay);

        while (offset != 0xffff)
        {
            // Read update sequence
            reader.read(b, 4);
            uint32_t update = b[0] | (b[1] << 8) | (b[2] << 16) | (b[3] << 24);

            // Add update sequence to frame
            frame.push_back(end_anim_update(offset, update));

            // Read next offset
            reader.read(b, 2);
            offset = b[0] | (b[1] << 8);
        }

        // Add frame to list of frames
        pic.frames.push_back(frame);

        // Read next delay and offset
        reader.read(b, 2);
        delay = b[0] | (b[1] << 8);
        reader.read(b, 2);
        offset = b[0] | (b[1] << 8);
    }

    return stream;
}

ostream& operator<<(ostream& stream, const end_anim& pic)
{
//    for (int y = 0; y != 128; y += 1)
//    {
//        for (int x = 0; x != 144; x += 1)
//        {
//            char key = y ? pic.data[(y - 1) * 144 + x] : 0;
//            stream.put(pic.data[y * 144 + x] ^ key);
//        }
//    }
    return stream;
}

}
