/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef TOOLS_FILEUTILS_H
#define TOOLS_FILEUTILS_H

namespace tools {

#ifdef WIN32
#define DIR_SEPARATOR '\\'
#else
#define DIR_SEPARATOR '/'
#endif

void mkdir(const char *filename);
std::string basename(const std::string &filename);

}

#endif
