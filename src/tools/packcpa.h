/*
 * Copyright (C) 2013 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef TOOLS_PACKCPA_H
#define TOOLS_PACKCPA_H

#include "program.h"

namespace tools
{

class packcpa : public program
{
public:
    packcpa();
    virtual void exec(int argc, char *argv[]);
};

}

#endif
