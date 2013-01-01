/*
 * Copyright (C) 2013 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

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
