/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

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
