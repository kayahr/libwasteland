/*
 * Copyright (C) 2013 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

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
