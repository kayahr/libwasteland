/*
 * Copyright (C) 2013 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef TOOLS_UNPACKCPA_H
#define TOOLS_UNPACKCPA_H

#include "program.h"

namespace tools
{

class unpackcpa : public program
{
public:
    unpackcpa();
    virtual void exec(int argc, char *argv[]);
};

}

#endif
