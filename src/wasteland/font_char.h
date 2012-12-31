/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_FONT_CHAR_H
#define LIBWASTELAND_FONT_CHAR_H

#include <iostream>
#include "image.h"

namespace wasteland
{

/**
 * Container for a 8x8 Wasteland font character image.
 *
 * Wasteland uses 172 font character images in the colorf.fnt file. These
 * font characters are used to draw the GUI (Frames, the clock, buttons, Logo).
 * This doesn't include the font for real text. For this the game uses the
 * standard text rendering of DOS.
 *
 * To read a single font character simply create an instance of this class and
 * then stream the file into it:
 *
 * @code
 * font_char img;
 * ifstream in("/path/colorf.fnt");
 * in >> img;
 * @endcode
 *
 * Repeat reading font characters from the stream until the stream reaches EOF
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
 * To write a font character back into a file you can simply use streams
 * again:
 *
 * @code
 * ofstream out("/path/newcolorf.fnt");
 * out << img;
 * @endcode
 */
class font_char: public image
{
    /**
     * Reads a font character image from the specified input stream.
     *
     * @return The input stream.
     */
    friend std::istream& operator>>(std::istream&, font_char&);

    /**
     * Writes a font character image to the specified output stream.
     *
     * @return The output stream.
     */
    friend std::ostream& operator<<(std::ostream&, const font_char&);

public:
    /**
     * Constructs a new empty fpnt character. All colors are set to black.
     */
    font_char();

    /**
     * Constructs a new font character initialized with the image data from
     * the specified font character.
     *
     * @param other
     *            The font character to copy the image data from.
     */
    font_char(const font_char& other);

    /**
     * Destructs this font character.
     */
    virtual ~font_char();

    /**
     * Copies the image data of the given sprite to this sprite.
     *
     * @param other
     *            The font character to copy the image data from.
     */
    virtual font_char& operator=(const font_char& other);

    /**
     * Compares this font character with the given font character.
     *
     * @param other
     *            The other font character to compare this one with.
     * @return True if font characters are equal, false if not.
     */
    virtual bool operator==(const font_char& other) const;

    /**
     * Compares this font character with the given font character.
     *
     * @param other
     *            The other font character to compare this one with.
     * @return  False if font characters are equal, true if not.
     */
    virtual bool operator!=(const font_char& other) const;

    virtual size get_width() const;
    virtual size get_height() const;
    virtual color get_color(const coord x, const coord y) const;
    virtual void set_color(const coord x, const coord y, const color color);

private:
    char *data;
};

}

#endif
