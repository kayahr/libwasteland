/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <cstring>
#include "huffman_istream.h"
#include "exceptions.h"
#include "end_anim.h"

using std::istream;
using std::ostream;

namespace wasteland
{

end_anim::end_anim()
{
}

end_anim::end_anim(const end_anim &other)
{
    base_frame = other.get_base_frame();
    frame_updates = other.get_frame_updates();
}

end_anim::~end_anim()
{
}

end_anim& end_anim::operator=(const end_anim& other)
{
    base_frame = other.get_base_frame();
    frame_updates = other.get_frame_updates();
    return *this;
}

bool end_anim::operator==(const end_anim& other) const
{
    return base_frame == other.get_base_frame() &&
        frame_updates == other.get_frame_updates();
}

bool end_anim::operator!=(const end_anim& other) const
{
    return !(*this == other);
}

const std::vector<end_anim_update>& end_anim::get_frame_updates() const
{
    return frame_updates;
}

std::vector<end_anim_update>& end_anim::get_frame_updates()
{
    return frame_updates;
}

const end_anim_frame end_anim::get_base_frame() const
{
    return base_frame;
}

end_anim_frame end_anim::get_base_frame()
{
    return base_frame;
}

istream& operator>>(istream& stream, end_anim& pic)
{
    // Read the size of the base frame block
    uint32_t size;
    if (!stream.read((char *) &size, 4)) throw eos_error();
    if (size != 288 * 128 / 2)
        throw error("Base frame block has invalid size");

    // Read and validate the MSQ header of the base frame block
    char msq[4];
    if (!stream.read(msq, 4)) throw eos_error();
    if (msq[0] != 'm' || msq[1] != 's' || msq[2] != 'q' || msq[3] != 0)
        throw error("MSQ header of base frame block not found");

    // Read the base frame
    huffman_istream huffman(stream);
    huffman >> pic.base_frame;

    // Read the size of the animation data block
    if (!stream.read((char *) &size, 4)) throw eos_error();

    // Reset the huffman stream, new MSQ block begins
    huffman.reset();

    // Read and validate the MSQ header of the animation data block
    if (!stream.read(msq, 4)) throw eos_error();
    if (msq[0] != 0x08 || msq[1] != 0x67 || msq[2] != 0x01 || msq[3] != 0)
        throw error("MSQ header of animation data block not found");

    // Read the animation data size
    uint16_t data_size;
    huffman.read((char *) &data_size, 2);
    if (data_size != size - 4)
        throw error("Animation data block size not matching MSQ size");

    // Read the frames
    do
    {
        end_anim_update update;
        huffman >> update;
        if (update.get_delay() != 0xffff)
            pic.frame_updates.push_back(update);
        else
            break;
    }
    while (true);

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
