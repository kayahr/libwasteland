/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_END_ANIM_FRAME_H
#define LIBWASTELAND_END_ANIM_FRAME_H

#include <vector>
#include <stdint.h>
#include "end_anim_update.h"

namespace wasteland
{

/**
 * Container for a single end animation frame.
 */
class end_anim_frame: public std::vector<end_anim_update>
{
public:
    /**
     * Constructs a new animation frame.
     */
    end_anim_frame();

    /**
     * Constructs a new animation frame with the given delay.
     *
     * @param delay
     *            The frame delay.
     */
    end_anim_frame(const uint16_t delay);

    /**
     * Destructs this animation frame.
     */
    virtual ~end_anim_frame();

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

private:
    uint16_t delay;
};

}

#endif
