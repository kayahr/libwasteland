/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include "transparent_image.h"

namespace wasteland
{

bool transparent_image::is_opaque(const coord x, const coord y) const
{
    return !is_transparent(x, y);
}

void transparent_image::set_opaque(const coord x, const coord y,
    const bool opaque)
{
    set_transparent(x, y, !opaque);
}

}
