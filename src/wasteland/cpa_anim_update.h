/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_CPA_ANIM_UPDATE_H
#define LIBWASTELAND_CPA_ANIM_UPDATE_H

#include <vector>
#include <stdint.h>
#include <istream>
#include <ostream>
#include "cpa_anim_block.h"
#include "cpa_anim_frame.h"

namespace wasteland
{

/**
 * Container for a single end animation frame.
 */
class cpa_anim_update
{
    /**
     * Reads the animation block from the specified input stream.
     *
     * @return The input stream.
     */
    friend std::istream& operator>>(std::istream&, cpa_anim_update&);

    /**
     * Writes the animation block to the specified output stream.
     *
     * @return The output streams.
     */
    friend std::ostream& operator<<(std::ostream&, const cpa_anim_update&);

public:
    /**
     * Constructs a new animation frame update.
     */
    cpa_anim_update();

    /**
     * Constructs a new animation frame update with the given delay.
     *
     * @param delay
     *            The frame delay.
     */
    cpa_anim_update(const uint16_t delay);

    /**
     * Destructs this animation frame update.
     */
    virtual ~cpa_anim_update();

    /**
     * Returns the frame delay.
     *
     * @return The frame delay.
     */
    virtual uint16_t get_delay() const;

    /**
     * Sets the frame delay.
     *
     * @param delay
     *            The frame delay to set.
     */
    virtual void set_delay(const uint16_t delay);

    /**
     * Compares this animation update with the given one.
     *
     * @param other
     *            The other animation update to compare this one with.
     * @return True if animation updates are equal, false if not.
     */
    virtual bool operator==(const cpa_anim_update& other) const;

    /**
     * Compares this animation update with the given one.
     *
     * @param other
     *            The other animation update to compare this one with.
     * @return False if animation updates are equal, false if not.
     */
    virtual bool operator!=(const cpa_anim_update& other) const;

    /**
     * Applies this animation update to the specified frame.
     *
     * @param frame
     *            The frame to apply this animation update to.
     */
    virtual void apply(cpa_anim_frame& frame) const;

    /**
     * Returns the update blocks.
     *
     * @return The update blocks.
     */
    virtual std::vector<cpa_anim_block>& get_blocks();

    /**
     * Returns the update blocks.
     *
     * @return The update blocks.
     */
    virtual const std::vector<cpa_anim_block>& get_blocks() const;

    /**
     * Sets the update blocks by calculating the difference between the two
     * specified frames.
     *
     * @param old
     *            The old frame.
     * @param new
     *            The new frame.
     */
    void set_blocks(const cpa_anim_frame& old_frame,
        const cpa_anim_frame& new_frame);

private:
    uint16_t delay;
    std::vector<cpa_anim_block> blocks;
};

}

#endif
