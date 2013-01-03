/*
 * Copyright (C) 2013 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_END_ANIM_BLOCK_H
#define LIBWASTELAND_END_ANIM_BLOCK_H

#include <istream>
#include <ostream>
#include <stdint.h>
#include "image.h"
#include "end_anim_frame.h"

namespace wasteland
{

/**
 * Container for a single end animation frame update block.
 */
class end_anim_block
{
    /**
     * Reads the animation block from the specified input stream.
     *
     * @return The input stream.
     */
    friend std::istream& operator>>(std::istream&, end_anim_block&);

    /**
     * Writes the animation block to the specified output stream.
     *
     * @return The output streams.
     */
    friend std::ostream& operator<<(std::ostream&, const end_anim_block&);

public:
    /**
     * Constructs a new empty animation block.
     */
    end_anim_block();

    /**
     * Constructs a new animation frame update sequence.
     *
     * @param offset
     *            The offset address. Formula: (y * 320 + x) / 8.
     * @param data
     *            The update data. Each 4 bit of this 32 bit value
     *            represents one pixel.
     */
    end_anim_block(const uint16_t offset, const uint32_t data);

    /**
     * Destructs this update sequence.
     */
    virtual ~end_anim_block();

    /**
     * Returns the raw offset address where to apply the update sequence.
     * Formula: (y * 320 + x) / 8.
     *
     * @return The offset address.
     */
    virtual uint16_t get_offset() const;

    /**
     * Returns the horizontal offset where to apply the update sequence.
     *
     * @return The horizontal offset.
     */
    virtual image::coord get_offset_x() const;

    /**
     * Returns the vertical offset where to apply the update sequence.
     *
     * @return The vertical offset.
     */
    virtual image::coord get_offset_y() const;

    /**
     * Returns the update data. Each 4 bit of the returned 32 bit value
     * represents one pixel.
     *
     * @return The update data.
     */
    virtual uint32_t get_data() const;

    /**
     * Returns the update color of the pixel with the specified index.
     *
     * @param index
     *            The pixel index (0-7)
     * @return The update color
     */
    virtual image::color get_color(const uint8_t index) const;

    /**
     * Compares this animation block with the given one.
     *
     * @param other
     *            The other animation block to compare this one with.
     * @return True if animation blocks are equal, false if not.
     */
    virtual bool operator==(const end_anim_block& other) const;

    /**
     * Compares this animation block with the given one.
     *
     * @param other
     *            The other animation block to compare this one with.
     * @return False if animation blocks are equal, false if not.
     */
    virtual bool operator!=(const end_anim_block& other) const;

    /**
     * Applies this animation block to the specified frame.
     *
     * @param frame
     *            The frame to apply this animation block to.
     */
    virtual void apply(end_anim_frame& frame) const;

private:
    uint16_t offset;
    uint32_t data;
};

}

#endif
