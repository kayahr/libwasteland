/*
 * Copyright (C) 2013 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_PIC_ANIM_BLOCK_H
#define LIBWASTELAND_PIC_ANIM_BLOCK_H

#include <istream>
#include <ostream>
#include <stdint.h>
#include "image.h"

namespace wasteland
{

/**
 * Container for a single encounter animation frame update block.
 */
class pic_anim_block
{
    /**
     * Reads the animation block from the specified input stream.
     *
     * @return The input stream.
     */
    friend std::istream& operator>>(std::istream&, pic_anim_block&);

    /**
     * Writes the animation block to the specified output stream.
     *
     * @return The output streams.
     */
    friend std::ostream& operator<<(std::ostream&, const pic_anim_block&);

public:
    /**
     * Constructs a new empty animation block.
     */
    pic_anim_block();

    /**
     * Constructs a new animation frame update sequence.
     *
     * @param offset
     *            The offset address. Formula: (y * 96 + x) / 2.
     * @param size
     *            The number of update bytes.
     * @param data
     *            The update bytes.
     */
    pic_anim_block(const uint16_t offset, const uint8_t size,
        const uint8_t* data);

    /**
     * Destructs this update sequence.
     */
    virtual ~pic_anim_block();

    /**
     * Returns the raw offset address where to apply the update sequence.
     * Formula: (y * 96 + x) / 2.
     *
     * @return The offset address.
     */
    virtual uint16_t get_offset() const;

    /**
     * Sets raw offset address.
     *
     * @param offset
     *            The offset address to set.
     */
    virtual void set_offset(const uint16_t offset);

    /**
     * Sets raw offset by calculating it for the specified coordinates.
     *
     * @param x
     *            The X offset.
     * @param y
     *            The y offset.
     */
    virtual void set_offset(const image::coord x, const image::coord y);

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
     * Returns the number of update bytes.
     *
     * @return The number of update bytes.
     */
    virtual uint8_t get_size() const;

    /**
     * Returns the update data. Each 4 bit of the returned 32 bit value
     * represents one pixel.
     *
     * @return The update data.
     */
    virtual uint8_t* get_data() const;

    /**
     * Sets the update data.
     *
     * @param size
     *            The number of update bytes.
     * @param data
     *            The update data.
     */
    virtual void set_data(const uint8_t size, const uint8_t* data);

    /**
     * Compares this animation block with the given one.
     *
     * @param other
     *            The other animation block to compare this one with.
     * @return True if animation blocks are equal, false if not.
     */
    virtual bool operator==(const pic_anim_block& other) const;

    /**
     * Compares this animation block with the given one.
     *
     * @param other
     *            The other animation block to compare this one with.
     * @return False if animation blocks are equal, false if not.
     */
    virtual bool operator!=(const pic_anim_block& other) const;

    /**
     * Applies this animation block to the specified frame.
     *
     * @param frame
     *            The frame to apply this animation block to.
     */
//    virtual void apply(pic_anim_frame& frame) const;

private:
    uint16_t offset;
    uint8_t size;
    uint8_t* data;
};

}

#endif
