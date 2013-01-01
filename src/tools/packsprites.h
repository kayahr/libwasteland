/*
 * Copyright (C) 2013 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef TOOLS_PACKSPRITES_H
#define TOOLS_PACKSPRITES_H

#include "program.h"

namespace tools
{

class packsprites : public program
{
public:
    packsprites();
    virtual void exec(int argc, char *argv[]);
};

}

#endif
