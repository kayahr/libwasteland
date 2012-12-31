/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <string>
#include <gd.h>
#include <wasteland/exceptions.h>
#include "gdutils.h"

using namespace std;
using namespace wasteland;

namespace tools
{

rgb ega_palette[16] = {
    { 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0xaa },
    { 0x00, 0xaa, 0x00 },
    { 0x00, 0xaa, 0xaa },
    { 0xaa, 0x00, 0x00 },
    { 0xaa, 0x00, 0xaa },
    { 0xaa, 0x55, 0x00 },
    { 0xaa, 0xaa, 0xaa },
    { 0x55, 0x55, 0x50 },
    { 0x55, 0x55, 0xff },
    { 0x55, 0xff, 0x55 },
    { 0x55, 0xff, 0xff },
    { 0xff, 0x55, 0x55 },
    { 0xff, 0x55, 0xff },
    { 0xff, 0xff, 0x55 },
    { 0xff, 0xff, 0xff }
};

void image_to_png(const char *filename, const image &img)
{
    int x, y, i;
    int palette[16];
    FILE *file;

    gdImagePtr output = gdImageCreate(img.get_width(), img.get_height());
    for (i = 0; i < 16; i++)
    {
        palette[i] = gdImageColorAllocate(output, ega_palette[i].red,
                ega_palette[i].green, ega_palette[i].blue);
    }
    for (y = 0; y < img.get_height(); y++)
    {
        for (x = 0; x < img.get_width(); x++)
        {
            gdImageSetPixel(output, x, y, palette[img.get_color(x, y)]);
        }
    }
    file = fopen(filename, "wb");
    if (!file) throw io_error(string("Unable to write ") + filename);
    gdImagePng(output, file);
    gdImageDestroy(output);
    fclose(file);
}

}
