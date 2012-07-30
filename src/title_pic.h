/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_TITLE_PIC_H
#define LIBWASTELAND_TITLE_PIC_H

#include "image.h"

namespace wasteland
{

/**
 * Container for the title.pic file of Wasteland.
 */
class title_pic : public image
{
public:
	title_pic(): image(288, 128, false) {};
};

}

#endif
