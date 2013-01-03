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
    uint8_t b[4];
    if (!stream.read((istream::char_type*) b, 4)) throw eos_error();
    int size = b[0] | (b[1] << 8) | (b[2] << 16) | (b[3] << 24);
    if (size != 288 * 128 / 2)
        throw error("Base frame block has invalid size");

    // Read and validate the MSQ header of the base frame block
    if (!stream.read((istream::char_type*) b, 4)) throw eos_error();
    if (b[0] != 'm' || b[1] != 's' || b[2] != 'q' || (b[3] != 0))
        throw error("MSQ header of base frame block not found");

    // Read the base frame
    huffman_istream huffman(stream);
    huffman >> pic.base_frame;

    // Read the size of the animation data block
    if (!stream.read((istream::char_type*) b, 4)) throw eos_error();
    size = b[0] | (b[1] << 8) | (b[2] << 16) | (b[3] << 24);

    // Read and validate the MSQ header of the animation data block
    if (!stream.read((istream::char_type*) b, 4)) throw eos_error();
    if (b[0] != 0x08 || b[1] != 0x67 || b[2] != 0x01 || (b[3] != 0))
        throw error("MSQ header of animation data block not found");

    // Reset the huffman stream, new MSQ block begins
    huffman.reset();

    // Read the animation data size
    huffman.read((char *) b, 2);
    int data_size = b[0] | (b[1] << 8);
    if (data_size != size - 4)
        throw error("Animation data block size not matching MSQ size");

    // Read the frames
    do
    {
        end_anim_update update;
        huffman >> update;
        if (update.get_delay() != 0)
            pic.frame_updates.push_back(update);
        else
            break;
        std::cout << "Frame update" << update.get_delay() << std::endl;
    }
    while (true);
    std::cout << "end" << std::endl;

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
