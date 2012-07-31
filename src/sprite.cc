/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include "sprite.h"

namespace wasteland
{

/**
 * Constructs a new Wasteland sprite image with a fixed size of 16x16 pixels.
 */
sprite::sprite() :
    transparent_image(16, 16)
{
}

/**
 * Reads a sprite from the specified streams.
 *
 * @return The sprite streams.
 */
sprite_istreams& operator>>(sprite_istreams& streams, sprite& sprite)
{
    int width = sprite.width;
    int height = sprite.height;

    for (int i = width * height / 2 - 1; i >= 0; i -= 1)
        sprite.data[i] = 0;

    for (int bit = 0; bit != 4; bit += 1)
    {
        for (int y = 0; y != height; y += 1)
        {
            for (int x = 0; x != width; x += 8)
            {
                int byte = streams.color().get();
                for (int pixel = 0; pixel != 8; pixel += 1)
                {
                    int value = ((byte >> (7 - pixel)) & 1) << bit;
                    int index = (y * width + x + pixel) / 2;
                    if (pixel & 1)
                        sprite.data[index] |= value << 4;
                    else
                        sprite.data[index] |= value;
                }
            }
        }
    }
    streams.opacity().read(sprite.transparency, width * height / 8);
    return streams;
}

/**
 * Writes the sprite to the specified streams.
 *
 * @return The sprite output streams.
 */
sprite_ostreams& operator<<(sprite_ostreams& streams, const sprite& sprite)
{
    int width = sprite.width;
    int height = sprite.height;

    for (int bit = 0; bit != 4; bit += 1)
    {
        for (int y = 0; y != height; y += 1)
        {
            for (int x = 0; x != width; x += 8)
            {
                int byte = 0;
                for (int pixel = 0; pixel != 8; pixel += 1)
                {
                    int index = (y * width + x + pixel) / 2;
                    int value = sprite.data[index];
                    if (pixel & 1)
                        value >>= 4;
                    else
                        value &= 0xf;
                    value = ((value >> bit) & 1) << (7 - pixel);
                    byte |= value;
                }
                streams.color().put(byte);
            }
        }
    }
    streams.opacity().write(sprite.transparency, width * height / 8);
    return streams;
}

}
