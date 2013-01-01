/*
 * Copyright (C) 2013 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef TOOLS_PACKFONT_H
#define TOOLS_PACKFONT_H

#include "program.h"

namespace tools
{

class packfont : public program
{
public:
    packfont();
    virtual void exec(int argc, char *argv[]);
};

}

#endif
