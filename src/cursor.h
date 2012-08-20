/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_CURSOR_H
#define LIBWASTELAND_CURSOR_H

#include <iostream>
#include <stdint.h>
#include "transparent_image.h"

namespace wasteland
{

/**
 * Container for a 16x16 Wasteland mouse cursor image.
 *
 * Wasteland uses 8 mouse cursor images in the <code>curs</code> file.
 *
 * To read a single mouse cursor image simply create an instance of this class
 * and then stream the file into it:
 *
 * @code
 * cursor img;
 * ifstream in("/path/curs");
 * in >> img;
 * @endcode
 *
 * Repeat reading cursor images from the stream until the stream reaches EOF
 * state.
 *
 * The colors of all pixels can be read with the {@link get_color} method
 * and can be changed with the {@link set_color} method. So you can invert
 * a color for example like this:
 *
 * @code
 * img.set_color(x, y, img.get_color(x, y) ^ 0xf);
 * @endcode
 *
 * To write a mouse cursor image back into a file you can simply use streams
 * again:
 *
 * @code
 * ofstream out("/path/newcurs");
 * out << img;
 * @endcode
 */
class cursor: public transparent_image
{
    /**
     * Reads a mouse cursor from the specified input stream.
     *
     * @return The input stream.
     */
    friend std::istream& operator>>(std::istream&, cursor&);

    /**
     * Writes the mouse cursor to the specified output stream.
     *
     * @return The output streams.
     */
    friend std::ostream& operator<<(std::ostream&, const cursor&);

public:
    /**
     * Type for a opacity mask of a pixel in an image. Only the first 4 bits
     * are used. Each bit defines if the corresponding color bit is transparent
     * (0) or opaque (1). Bit 0 = Blue, Bit 1 = Green, Bit 2 = Red,
     * Bit 3 = Intensity
     */
    typedef uint8_t opacity;

    /**
     * Constructs a new empty mouse cursor. All colors are set to black and
     * all transparency flags are set to opaque.
     */
    cursor();

    /**
     * Constructs a new mouse cursor initialized with the image data from the
     * specified mouse cursor.
     *
     * @param other
     *            The mouse cursor to copy the image data from.
     */
    cursor(const cursor &other);

    /**
     * Destructs this mouse cursor.
     */
    virtual ~cursor();

    /**
     * Copies the image data of the given mouse cursor to this one.
     *
     * @param other
     *            The mouse cursor to copy the image data from.
     */
    virtual cursor& operator=(const cursor& other);

    /**
     * Compares this mouse cursor with the given mouse cursor.
     *
     * @param other
     *            The other mouse cursor to compare this one with.
     * @return True if mouse cursors are equal, false if not.
     */
    virtual bool operator==(const cursor& other) const;

    /**
     * Compares this mouse cursor with the given mouse cursor.
     *
     * @param other
     *            The other mouse cursor to compare this one with.
     * @return False if mouse cursors are equal, true if not.
     */
     virtual bool operator!=(const cursor& other) const;

    /**
     * Returns the opacity mask of the pixel at the specified position.
     * Each bit defines if the corresponding color component is opaque
     * (Bit 0 = Blue, Bit 1 = Green, Bit 2 = Red, Bit 3 = Intensity). So 0
     * means fully transparent and 15 means fully opaque.
     *
     * If the specified position is outside of the image then 0 (transparent)
     * is returned.
     *
     * @param x
     *            The X position.
     * @param y
     *            The Y position.
     * @return
     *            The opacity mask of the pixel. 0 (transparent) if specified
     *            position is outside of the image.
     */
    opacity get_opacity(const coord x, const coord y) const;

    /**
     * Sets the opacity mask of the pixel at the specified position.
     * Each bit defines if the corresponding color component is opaque
     * (Bit 0 = Blue, Bit 1 = Green, Bit 2 = Red, Bit 3 = Intensity). So 0
     * means fully transparent and 15 means fully opaque.
     *
     * If the specified position is outside of the image then this method does
     * nothing.
     *
     * @param x
     *            The X position.
     * @param y
     *            The Y position.
     * @param opacity
     *            The opacity mask of the pixel to set.
     */
    void set_opacity(const coord x, const coord y, const opacity opacity);

    virtual size get_width() const;
    virtual size get_height() const;
    virtual color get_color(const coord x, const coord y) const;
    virtual void set_color(const coord x, const coord y, const color color);
    virtual bool is_transparent(const coord x, const coord y) const;
    virtual void set_transparent(const coord x, const coord y,
        const bool transparent = true);

private:
    char *data;
};

}

#endif
