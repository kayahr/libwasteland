/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef TOOLS_DECODEPIC_H
#define TOOLS_DECODEPIC_H

#include "program.h"

namespace tools
{

class decodepic : public program
{
public:
    decodepic();
    virtual void exec(int argc, char *argv[]);
};

}

#endif
