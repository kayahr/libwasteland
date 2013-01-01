/*
 * Copyright (C) 2013 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <string>
#include <sys/stat.h>
#include <sys/types.h>

#include <wasteland/exceptions.h>

using namespace std;
using namespace wasteland;

namespace tools
{

void mkdir(const char *dirname)
{
    struct stat st;
    if (stat(dirname, &st))
    {
        if (::mkdir(dirname, 0755))
        {
            throw io_error(string("Unable to create directory ") + dirname);
        }
    }
}

}
