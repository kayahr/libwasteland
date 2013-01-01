/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef TOOLS_GDUTILS_H
#define TOOLS_GDUTILS_H

#include <wasteland/image.h>
#include <wasteland/transparent_image.h>

namespace tools {

struct rgb
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

extern rgb ega_palette[];

void image_to_png(const wasteland::transparent_image &img, const char *filename);
void image_to_png(const wasteland::image &img, const char *filename);
void png_to_image(const char *filename, wasteland::transparent_image &img);
void png_to_image(const char *filename, wasteland::image &img);

}

#endif
