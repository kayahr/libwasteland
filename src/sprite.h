/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_SPRITE_H
#define LIBWASTELAND_SPRITE_H

#include "transparent_image.h"
#include "sprite_istreams.h"
#include "sprite_ostreams.h"

namespace wasteland
{

/**
 * Container for a 16x16 Wasteland sprite image.
 *
 * Sprite data is separated into colors (Stored in the ic0_9.wlf file) and
 * transparency masks (Stored in the masks.wlf file). These files contain the
 * data for 10 sprites. Because reading and writing sprite data always needs
 * two different streams you have to use the classes
 * {@link wasteland::sprite_istreams sprite_istreams} and
 * {@link wasteland::sprite_ostreams sprite_ostreams} to bundle these two
 * streams into a single object which can be used like a stream.
 *
 * Here is an example how to read the first sprite from the Wasteland data
 * files:
 *
 * @code
 * sprite img;
 * ifstream colors_in("/path/ic0_9.wlf");
 * ifstream masks_in("/path/masks.wlf");
 * sprite_istreams in(colors_in, masks_in);
 * in >> img;
 * @endcode
 *
 * The colors of all pixels of a sprite can be read with the {@link get_color} method
 * and can be changed with the {@link set_color} method. So you can invert
 * a color for example like this:
 *
 * @code
 * img.set_color(x, y, img.get_color(x, y) ^ 0xf);
 * @endcode
 *
 * The transparency flag of all pixels can be read with the
 * {@link is_transparent} method and can be changed with the
 * {@link set_transparent} method. So to invert the transparency of a single
 * pixel you can do this:
 *
 * @code
 * img.set_transparent(x, y, !img.is_transparent(x, y));
 * @endcode
 *
 * Writing a sprite back into files works like this:
 *
 * @code
 * ofstream colors_out("/path/new_ic0_9.wlf");
 * ofstream masks_out("/path/new_masks.wlf");
 * sprite_ostreams out(colors_out, masks_out);
 * out << img;
 * @endcode
 */
class sprite: public transparent_image
{
    friend sprite_istreams& operator>>(sprite_istreams&, sprite&);
    friend sprite_ostreams& operator<<(sprite_ostreams&, const sprite&);

public:
    sprite();
};

sprite_istreams& operator>>(sprite_istreams& streams, sprite& sprite);
sprite_ostreams& operator<<(sprite_ostreams& streams, const sprite& sprite);

}

/**
 * @example invert_sprites.cc
 * This example shows how to read the Wasteland sprites, invert all pixels and
 * write the new sprites back to some other files.
 */

#endif
