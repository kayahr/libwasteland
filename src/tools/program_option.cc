/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include "program_option.h"

using namespace std;

namespace tools
{

program_option::program_option(const char short_name, const string &long_name,
        const bool has_arg, const string &description) :
   short_name(short_name),
   long_name(long_name),
   description(description),
   has_arg(has_arg)
{
}

const char program_option::get_short_name() const
{
    return short_name;
}

const string &program_option::get_long_name() const
{
    return long_name;
}

const string &program_option::get_description() const
{
    return description;
}

const bool program_option::get_has_arg() const
{
    return has_arg;
}

}
