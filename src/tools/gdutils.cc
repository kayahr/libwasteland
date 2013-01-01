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

void image_to_png(const image &img, const char *filename)
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
    if (!file) throw io_error(string("Unable to open ") + filename);
    gdImagePng(output, file);
    gdImageDestroy(output);
    fclose(file);
}

void png_to_image(const char *filename, image &img)
{
    // Load PNG file
    FILE *file = fopen(filename, "rb");
    if (!file) throw io_error(string("Unable to open ") + filename);
    gdImagePtr png = gdImageCreateFromPng(file);
    fclose(file);

    // Create a temporary second image for resizing and palette conversion
    gdImagePtr tmp = gdImageCreate(img.get_width(), img.get_height());
    for (int i = 0; i < 16; i++)
    {
        gdImageColorAllocate(tmp, ega_palette[i].red,
            ega_palette[i].green, ega_palette[i].blue);
    }
    for (int i = 16; i < 256; i++) gdImageColorAllocate(tmp, 0, 0, 0);
    gdImageCopyResampled(tmp, png, 0, 0, 0, 0,
        img.get_width(), img.get_height(), gdImageSX(png), gdImageSY(png));

    // Fill pixels into image
    for (int y = 0; y < img.get_height(); y++)
    {
        for (int x = 0; x < img.get_width(); x++)
        {
            img.set_color(x, y, gdImageGetPixel(tmp, x, y));
        }
    }

    gdImageDestroy(tmp);
    gdImageDestroy(png);
}

}
