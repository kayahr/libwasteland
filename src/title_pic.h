/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_TITLE_PIC_H
#define LIBWASTELAND_TITLE_PIC_H

#include <iostream>
#include "image.h"

namespace wasteland
{

/**
 * Container for the title picture of Wasteland (title.pic file).
 *
 * The title picture of Wasteland is a vertical-xor encoded image with a
 * size of 288x128 which supports no transparency.
 *
 * To read the title picture simply create an instance of this class and then
 * stream the file into it:
 *
 * @code
 * title_pic pic;
 * ifstream in("/path/title.pic");
 * in >> pic;
 * @endcode
 *
 * The colors of all pixels can be read with the {@link get_color} method
 * and can be changed with the {@link set_color} method. So you can invert
 * a color for example like this:
 *
 * @code
 * pic.set_color(x, y, pic.get_color(x, y) ^ 0xf);
 * @endcode
 *
 * To write the title picture back into a file you can simply use streams
 * again:
 *
 * @code
 * ofstream out("/path/newtitle.pic");
 * out << pic;
 * @endcode
 */
class title_pic: public image
{
    /**
     * Reads the title image from the specified input stream.
     *
     * @return The input stream.
     */
    friend std::istream& operator>>(std::istream&, title_pic&);

    /**
     * Writes the title image to the specified output stream.
     *
     * @return The output streams.
     */
    friend std::ostream& operator<<(std::ostream&, const title_pic&);

public:
    /**
     * Constructs a new empty title picture. All colors are set to black.
     */
    title_pic();

    /**
     * Constructs a new title picture initialized with the image data from
     * the specified title picture.
     *
     * @param other
     *            The picture to copy the image data from.
     */
    title_pic(const title_pic& other);

    /**
     * Destructs this title picture.
     */
    virtual ~title_pic();

    /**
     * Copies the image data of the given title picture to this title
     * picture.
     *
     * @param other
     *            The picture to copy the image data from.
     */
    virtual title_pic& operator=(const title_pic& other);

    /**
     * Compares this title picture with the given title picture.
     *
     * @param other
     *            The other title picture to compare this one with.
     * @return True if title pictures are equal, false if not.
     */
    virtual bool operator==(const title_pic& other) const;

    /**
     * Compares this title picture with the given title picture.
     *
     * @param other
     *            The other title picture to compare this one with.
     * @return  False if title pictures are equal, true if not.
     */
    virtual bool operator!=(const title_pic& other) const;

    virtual size get_width() const;
    virtual size get_height() const;
    virtual color get_color(const coord x, const coord y) const;
    virtual void set_color(const coord x, const coord y, const color color);

private:
    char *data;
};

}

#endif
