/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef TOOLS_OPTION_H
#define TOOLS_OPTION_H

#include <string>

namespace tools
{

class program_option
{
public:
    program_option(const char short_name, const std::string &long_name,
        const bool has_arg, const std::string &description);
    const char get_short_name() const;
    const std::string &get_long_name() const;
    const std::string &get_description() const;
    const bool get_has_arg() const;

private:
    char short_name;
    std::string long_name;
    std::string description;
    bool has_arg;
};

}

#endif
