/*
 * Copyright (C) 2013 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef TOOLS_UNPACKSPRITES_H
#define TOOLS_UNPACKSPRITES_H

#include "program.h"

namespace tools
{

class unpacksprites : public program
{
public:
    unpacksprites();
    virtual void exec(int argc, char *argv[]);
};

}

#endif
