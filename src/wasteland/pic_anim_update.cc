/*
 * Copyright (C) 2013 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include "pic_anim_update.h"

using std::vector;
using std::istream;
using std::ostream;

namespace wasteland
{

pic_anim_update::pic_anim_update()
{
}

pic_anim_update::~pic_anim_update()
{
    // Nothing to do.
}

vector<pic_anim_block>& pic_anim_update::get_blocks()
{
    return blocks;
}

const vector<pic_anim_block>& pic_anim_update::get_blocks() const
{
    return blocks;
}

/*
void pic_anim_update::set_blocks(const pic_anim_frame& old_frame,
    const pic_anim_frame& new_frame)
{
    blocks.clear();
    for (int y = 0; y < 128; y += 1)
    {
        for (int x = 0; x < 288; x += 8)
        {
            for (int i = 0; i < 8; i += 1)
            {
                if (old_frame.get_color(x + i, y) != new_frame.get_color(x + i, y))
                {
                    blocks.push_back(pic_anim_block(new_frame, x, y));
                    break;
                }
            }
        }
    }
}
*/

bool pic_anim_update::operator==(const pic_anim_update& other) const
{
    return blocks == other.blocks;
}

bool pic_anim_update::operator!=(const pic_anim_update& other) const
{
    return !(*this == other);
}

/*
void pic_anim_update::apply(pic_anim_frame& frame) const
{
    for(vector<pic_anim_block>::const_iterator block = blocks.begin(),
        end = blocks.end(); block != end; ++block)
    {
        block->apply(frame);
    }
}
*/

istream& operator>>(istream& stream, pic_anim_update& update)
{
    update.blocks.clear();
    do
    {
        pic_anim_block block;
        stream >> block;
        if (block.get_size() != 0)
            update.blocks.push_back(block);
        else
            break;
    }
    while (true);
    return stream;
}

ostream& operator<<(ostream& stream, const pic_anim_update& update)
{
    for(vector<pic_anim_block>::const_iterator block = update.blocks.begin(),
        end = update.blocks.end(); block != end; ++block)
    {
        stream << *block;
    }
    stream << pic_anim_block();
    return stream;
}

}
