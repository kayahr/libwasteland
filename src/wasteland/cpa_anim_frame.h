/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_CPA_ANIM_FRAME_H
#define LIBWASTELAND_CPA_ANIM_FRAME_H

#include <iostream>
#include "vxor_image.h"

namespace wasteland
{

/**
 * Container for a complete frame of the end animation.
 */
class cpa_anim_frame: public vxor_image
{
public:
    /**
     * Constructs a new empty end animation frame. All colors are set to
     * black.
     */
    cpa_anim_frame();

    /**
     * Constructs a new end animation frame with the image data from the
     * specified end animation frame.
     *
     * @param other
     *            The end animation frame to copy the image data from.
     */
    cpa_anim_frame(const cpa_anim_frame& other);

    /**
     * Destructs this end animation frame.
     */
    virtual ~cpa_anim_frame();

    /**
     * Copies the image data of the given end animation frame into this one..
     *
     * @param other
     *            The end animation frame to copy the image data from.
     */
    virtual cpa_anim_frame& operator=(const cpa_anim_frame& other);
};

}

#endif
