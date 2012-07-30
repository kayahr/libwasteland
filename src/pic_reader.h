/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_PIC_READER_H
#define LIBWASTELAND_PIC_READER_H

#include <istream>
#include "image.h"

namespace wasteland
{

/**
 * Reader for the Wasteland title.pic file.
 */
class pic_reader
{
public:
    explicit pic_reader(std::istream &stream);
    pic_reader &operator>>(wasteland::image &image);

private:
    std::istream &stream_;
};

}

#endif
