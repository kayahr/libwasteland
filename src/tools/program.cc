/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <cstring>
#include <cerrno>
#include <cstdlib>
#include <iostream>
#include <getopt.h>
#include <gd.h>
#include <wasteland/exceptions.h>
#include "config.h"
#include "fileutils.h"
#include "program.h"

using namespace std;
using namespace wasteland;

namespace tools
{

program::program() : min_args(0), max_args(0)
{
    add_option('h', "help", false, "Display help and exit");
    add_option('V', "version", false, "Display version and exit");
}

program::~program()
{
}

void program::set_arg_range(int min_args, int max_args)
{
    this->min_args = min_args;
    this->max_args = max_args;
}

void program::set_name(const string &name)
{
    this->name = name;
}

void program::set_syntax(const string &syntax)
{
    this->syntax = syntax;
}

void program::set_description(const string &description)
{
    this->description = description;
}

void program::set_documentation(const string &documentation)
{
    this->documentation = documentation;
}

void program::display_usage() const
{
    cout
        << "Usage: " << name << " " << syntax << '\n'
        << description
        << "\n\n"
        << "Options\n" << '\n';

    int max_len = 0;
    for(vector<program_option>::const_iterator it = options.begin();
        it != options.end(); ++it)
    {
        max_len = max(max_len, (int) it->get_long_name().size());
    }

    for(vector<program_option>::const_iterator it = options.begin();
        it != options.end(); ++it)
    {
        cout << "  -";
        cout << it->get_short_name();
        cout << ", --";
        cout << it->get_long_name();
        int spaces = max_len + 2 - it->get_long_name().size();
        if (it->get_has_arg())
        {
            cout << '=';
            spaces -= 1;
        }
        while (spaces--) cout << ' ';
        cout << it->get_description();
        cout << '\n';
    }
    if (!documentation.empty()) cout << '\n' << documentation << '\n';
    cout << "\nReport bugs to Klaus Reimer <k@ailis.de>" << endl;
}

void program::display_version() const
{
    cout << name << " " << VERSION <<
        "\n\nCopyright (C) 2012-2013 Klaus Reimer <k@ailis.de>\n"
        "This is free software; see the source for copying conditions. "
        "There is NO\nwarranty; not even for MERCHANTABILITY "
        "or FITNESS FOR A PARTICULAR PURPOSE.\n\n"
        "Written by Klaus Reimer <k@ailis.de>" << endl;
}

void program::add_option(const char short_name, const string &long_name,
    const bool has_arg, const string &description)
{
    options.push_back(program_option(short_name, long_name, has_arg, description));
}

int program::run(int argc, char *argv[])
{
    try
    {
        // Set name from filename if not already present
        if (name.empty()) set_name(basename(string(argv[0])));

        int index = process_options(argc, argv);
        if (index == -1) return 0;
        argc -= index;
        argv += index;

        // Terminate if wrong number of parameters are specified
        if (argc < min_args || (max_args != -1 && argc > max_args))
            throw option_error("Wrong number of parameters");

        exec(argc, argv);
    }
    catch (option_error &e)
    {
        cerr << name << ": " << e.what()
             << "\nUse --help to show syntax." << endl;
        return 1;
    }
    catch (exception &e)
    {
        cerr << name << ": " << e.what() << endl;
        return 1;
    }
    return 0;
}

int program::process_options(int argc, char *argv[])
{
    struct option long_options[options.size() + 1];

    string short_options;
    for (int i = 0; i < options.size(); i += 1)
    {
        program_option opt = options[i];
        long_options[i].name = opt.get_long_name().c_str();
        long_options[i].has_arg = opt.get_has_arg();
        long_options[i].flag = NULL;
        long_options[i].val = opt.get_short_name();

        short_options += opt.get_short_name();
        if (opt.get_has_arg()) short_options += ':';
    }
    long_options[options.size()].name = NULL;

    int index;
    opterr = 0;
    char opt;
    while ((opt = getopt_long(argc, argv, short_options.c_str(),
        long_options, &index)) != -1)
    {
        switch (opt)
        {
            case 'V':
                display_version();
                return -1;

            case 'h':
                display_usage();
                return -1;
        }

        if (!process_option(opt))
            throw option_error(string("Unknown option: ") +argv[optind - 1]);
    }
    return optind;
}

bool program::process_option(char option)
{
    return false;
}

}
