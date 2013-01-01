/*
 * Copyright (C) 2013 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef TOOLS_UNPACKFONT_H
#define TOOLS_UNPACKFONT_H

#include "program.h"

namespace tools
{

class unpackfont : public program
{
public:
    unpackfont();
    virtual void exec(int argc, char *argv[]);
};

}

#endif
