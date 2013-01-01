/*
 * Copyright (C) 2013 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef TOOLS_ENCODEPIC_H
#define TOOLS_ENCODEPIC_H

#include "program.h"

namespace tools
{

class encodepic : public program
{
public:
    encodepic();
    virtual void exec(int argc, char *argv[]);
};

}

#endif

