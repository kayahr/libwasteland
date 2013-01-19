/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <cstring>
#include <sstream>
#include "huffman_istream.h"
#include "huffman_ostream.h"
#include "exceptions.h"
#include "end_anim.h"

using std::vector;
using std::string;
using std::istream;
using std::ostream;
using std::ostringstream;

namespace wasteland
{

end_anim::end_anim()
{
}

end_anim::end_anim(const end_anim &other)
{
    base_frame = other.get_base_frame();
    updates = other.get_updates();
}

end_anim::~end_anim()
{
}

end_anim& end_anim::operator=(const end_anim& other)
{
    base_frame = other.get_base_frame();
    updates = other.get_updates();
    return *this;
}

bool end_anim::operator==(const end_anim& other) const
{
    return base_frame == other.get_base_frame() &&
        updates == other.get_updates();
}

bool end_anim::operator!=(const end_anim& other) const
{
    return !(*this == other);
}

const std::vector<end_anim_update>& end_anim::get_updates() const
{
    return updates;
}

vector<end_anim_update>& end_anim::get_updates()
{
    return updates;
}

void end_anim::add_update(const end_anim_update& update)
{
    updates.push_back(update);
}

const end_anim_frame& end_anim::get_base_frame() const
{
    return base_frame;
}

end_anim_frame& end_anim::get_base_frame()
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
            pic.updates.push_back(update);
        else
            break;
    }
    while (true);

    return stream;
}

ostream& operator<<(ostream& stream, const end_anim& anim)
{
    // Write first MSQ block (The base frame)
    uint32_t size = 144 * 128;
    stream.write((char *) &size, 4);
    char msq1[4] = { 'm', 's', 'q', 0x00 };
    stream.write(msq1, 4);
    huffman_ostream huffman(stream);
    huffman << anim.get_base_frame();
    huffman.flush();

    // Write second MSQ block (The anomation frames)
    size = 6;
    for (vector<end_anim_update>::const_iterator update = anim.updates.begin(),
        end = anim.updates.end(); update != end; ++update)
    {
        size += 4 + update->get_blocks().size() * 6;
    }
    stream.write((char *) &size, 4);
    char msq2[4] = { 0x08, 0x67, 0x01, 0x00 };
    stream.write(msq2, 4);
    uint16_t data_size = size - 4;
    huffman.write((char *) &data_size, 2);
    for (vector<end_anim_update>::const_iterator update = anim.updates.begin(),
        end = anim.updates.end(); update != end; ++update)
    {
        huffman << *update;
    }
    char end[4] = { 0xff, 0xff, 0x00, 0x00 };
    huffman.write(end, 4);
    huffman.flush();
    return stream;
}

}
