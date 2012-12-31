/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef TOOLS_GDUTILS_H
#define TOOLS_GDUTILS_H

namespace tools {

struct rgb
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

extern rgb ega_palette[];

void image_to_png(const char *filename, const wasteland::image &img);

}

#endif
