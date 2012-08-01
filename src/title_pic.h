/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_TITLE_PIC_H
#define LIBWASTELAND_TITLE_PIC_H

#include "vxor_image.h"

namespace wasteland
{

/**
 * Container for the title picture of Wasteland (title.pic file).
 *
 * The title picture of Wasteland is a vertical-xor encoded image with a
 * fixed size of 288x128 which supports no transparency.
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
class title_pic : public vxor_image
{
public:
    title_pic();
};

}

/**
 * @example invert_title_pic.cc
 * This example shows how to read a title.pic file, invert all pixels and
 * write the new picure back to a different file.
 */

#endif
