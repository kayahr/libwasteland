/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include "title_pic.h"

namespace wasteland
{

/**
 * Constructs a new Wasteland title picture with a fixed width of 288 pixels
 * and a height of 128 pixels.
 */
title_pic::title_pic() :
    vxor_image(288, 128)
{
}

}
