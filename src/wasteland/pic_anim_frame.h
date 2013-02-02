/*
 * Copyright (C) 2013 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_PIC_ANIM_FRAME_H
#define LIBWASTELAND_PIC_ANIM_FRAME_H

#include <iostream>
#include "vxor_image.h"

namespace wasteland
{

/**
 * Container for a complete frame of a PIC animation.
 */
class pic_anim_frame: public vxor_image
{
public:
    /**
     * Constructs a new empty PIC animation frame. All colors are set to
     * black.
     */
    pic_anim_frame();

    /**
     * Constructs a new PIC animation frame with the image data from the
     * specified PIC animation frame.
     *
     * @param other
     *            The end animation frame to copy the image data from.
     */
    pic_anim_frame(const pic_anim_frame& other);

    /**
     * Destructs this PIC animation frame.
     */
    virtual ~pic_anim_frame();

    /**
     * Copies the image data of the given PIC animation frame into this one..
     *
     * @param other
     *            The PIC animation frame to copy the image data from.
     */
    virtual pic_anim_frame& operator=(const pic_anim_frame& other);
};

}

#endif
