/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_PROGRAM_H
#define LIBWASTELAND_PROGRAM_H

#include <stdexcept>
#include <string>
#include <vector>
#include "program_option.h"

namespace tools
{

class option_error: public std::runtime_error
{
public:
    explicit option_error(const std::string &message) : std::runtime_error(message) {};
};

class program
{
public:
    program();
    virtual ~program();
    void set_name(const std::string &name);
    void set_arg_range(int min_args, int max_args);
    void set_syntax(const std::string &syntax);
    void set_description(const std::string &description);
    void set_documentation(const std::string &documentation);
    void display_usage() const;
    void display_version() const;
    void add_option(const char short_name, const std::string &long_name,
        const bool has_arg, const std::string &description);
    int run(int argc, char *argv[]);
    virtual void exec(int argc, char *argv[]) = 0;
    int process_options(int argc, char *argv[]);
    virtual bool process_option(char option);

private:
    int min_args;
    int max_args;
    std::string name;
    std::string syntax;
    std::string description;
    std::string documentation;
    std::vector<program_option> options;
};

}

#endif
