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
    /**
     * Reads a sprite from the specified streams.
     *
     * @return The sprite streams.
     */
    friend sprite_istreams& operator>>(sprite_istreams& streams,
        sprite& sprite);

    /**
     * Writes the sprite to the specified streams.
     *
     * @return The sprite output streams.
     */
    friend sprite_ostreams& operator<<(sprite_ostreams& streams,
        const sprite& sprite);

public:
    /**
     * Constructs a new empty sprite. All colors are set to black and all
     * transparency flags are set to opaque.
     */
    sprite();

    /**
     * Constructs a new sprite initialized with the image data from the
     * specified sprite.
     *
     * @param other
     *            The sprite to copy the image data from.
     */
    sprite(const sprite &other);

    /**
     * Destructs this sprite.
     */
    virtual ~sprite();

    /**
     * Copies the image data of the given sprite to this sprite.
     *
     * @param other
     *            The sprite to copy the image data from.
     */
    virtual sprite& operator=(const sprite& other);

    /**
     * Compares this sprite with the given sprite.
     *
     * @param other
     *            The other sprite to compare this one with.
     * @return True if sprites are equal, false if not.
     */
    virtual bool operator==(const sprite& other) const;

    /**
     * Compares this sprite with the given sprite.
     *
     * @param other
     *            The other sprite to compare this one with.
     * @return False if sprites are equal, true if not.
     */
    virtual bool operator!=(const sprite& other) const;

    virtual size get_width() const;
    virtual size get_height() const;
    virtual color get_color(const coord x, const coord y) const;
    virtual void set_color(const coord x, const coord y, const color color);
    virtual bool is_transparent(const coord x, const coord y) const;
    virtual void set_transparent(const image::coord x,
        const image::coord y, const bool transparent = true);

private:
    char *data;
    char *transparency;
};

}

#endif
