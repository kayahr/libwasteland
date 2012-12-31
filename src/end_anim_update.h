/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_END_ANIM_UPDATE_H
#define LIBWASTELAND_END_ANIM_UPDATE_H

#include <iostream>
#include <stdint.h>
#include "image.h"

namespace wasteland
{

/**
 * Container for a single end animation frame update sequence.
 */
class end_anim_update
{
public:
    /**
     * Constructs a new animation frame update sequence.
     *
     * @param offset
     *            The offset address. Formula: (y * 320 + x) / 8.
     * @param update
     *            The update sequence. Each 4 bit of this 32 bit value
     *            represents one pixel.
     */
    end_anim_update(const uint16_t offset, const uint32_t update);

    /**
     * Destructs this update sequence.
     */
    virtual ~end_anim_update();

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
     * Returns the update sequence. Each 4 bit of the returned 32 bit value
     * represents one pixel.
     *
     * @return The update sequence.
     */
    virtual uint32_t get_update() const;

    /**
     * Returns the update color of the pixel with the specified index.
     *
     * @param index
     *            The pixel index (0-7)
     * @return The update color
     */
    virtual image::color get_color(const uint8_t index) const;

private:
    uint16_t offset;
    uint32_t update;
};

}

#endif
