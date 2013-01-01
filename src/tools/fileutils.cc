/*
 * Copyright (C) 2013 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include "fileutils.h"

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

string basename(const string &filename)
{
    string::size_type index = filename.find_last_of(DIR_SEPARATOR);
    if (index == string::npos) return filename;
    return filename.substr(index + 1);
}

}
