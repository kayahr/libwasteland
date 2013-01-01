/*
 * Copyright (C) 2013 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef TOOLS_PACKCURSORS_H
#define TOOLS_PACKCURSORS_H

#include "program.h"

namespace tools
{

class packcursors : public program
{
public:
    packcursors();
    virtual void exec(int argc, char *argv[]);
};

}

#endif
