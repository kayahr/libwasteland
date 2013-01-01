/*
 * Copyright (C) 2013 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef TOOLS_UNPACKTILES_H
#define TOOLS_UNPACKTILES_H

#include "program.h"

namespace tools
{

class unpacktiles : public program
{
public:
    unpacktiles();
    virtual void exec(int argc, char *argv[]);
};

}

#endif
