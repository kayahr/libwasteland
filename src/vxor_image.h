/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_VXOR_IMAGE_H
#define LIBWASTELAND_VXOR_IMAGE_H

#include <istream>
#include "image.h"

namespace wasteland
{

/**
 * Image encoded with the vertical XOR algorithm.
 */
class vxor_image: public image
{
    friend std::istream& operator>>(std::istream&, vxor_image&);
    friend std::ostream& operator<<(std::ostream&, const vxor_image&);

public:
    vxor_image(const int width, const int height);
};

std::istream& operator>>(std::istream& stream, vxor_image& image);
std::ostream& operator<<(std::ostream& stream, const vxor_image& image);

}

#endif
