/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include "cpa_anim_update.h"

using std::vector;
using std::istream;
using std::ostream;

namespace wasteland
{

cpa_anim_update::cpa_anim_update() : delay(0)
{
}

cpa_anim_update::cpa_anim_update(const uint16_t delay) : delay(delay)
{
}

cpa_anim_update::~cpa_anim_update()
{
    // Nothing to do.
}

uint16_t cpa_anim_update::get_delay() const
{
    return delay;
}

void cpa_anim_update::set_delay(const uint16_t delay)
{
    this->delay = delay;
}

vector<cpa_anim_block>& cpa_anim_update::get_blocks()
{
    return blocks;
}

const vector<cpa_anim_block>& cpa_anim_update::get_blocks() const
{
    return blocks;
}

void cpa_anim_update::set_blocks(const cpa_anim_frame& old_frame,
    const cpa_anim_frame& new_frame)
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
                    blocks.push_back(cpa_anim_block(new_frame, x, y));
                    break;
                }
            }
        }
    }
}

bool cpa_anim_update::operator==(const cpa_anim_update& other) const
{
    return delay == other.delay && blocks == other.blocks;
}

bool cpa_anim_update::operator!=(const cpa_anim_update& other) const
{
    return !(*this == other);
}

void cpa_anim_update::apply(cpa_anim_frame& frame) const
{
    for(vector<cpa_anim_block>::const_iterator block = blocks.begin(),
        end = blocks.end(); block != end; ++block)
    {
        block->apply(frame);
    }
}

istream& operator>>(istream& stream, cpa_anim_update& update)
{
    stream.read((char *) &update.delay, 2);
    update.blocks.clear();
    do
    {
        cpa_anim_block block;
        stream >> block;
        if (block.get_offset() != 0xffff && block.get_offset() != 0x0000)
            update.blocks.push_back(block);
        else
            break;
    }
    while (true);
    return stream;
}

ostream& operator<<(ostream& stream, const cpa_anim_update& update)
{
    stream.write((char *) &update.delay, 2);
    for(vector<cpa_anim_block>::const_iterator block = update.blocks.begin(),
        end = update.blocks.end(); block != end; ++block)
    {
        stream << *block;
    }
    stream << cpa_anim_block(0xffff, 0);
    return stream;
}

}
