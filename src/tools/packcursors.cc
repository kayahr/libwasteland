/*
 * Copyright (C) 2013 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <fstream>
#include <sstream>
#include <wasteland/exceptions.h>
#include <wasteland/cursor.h>
#include "gdutils.h"
#include "fileutils.h"
#include "packcursors.h"

using namespace std;
using namespace wasteland;

namespace tools
{

packcursors::packcursors() : program()
{
    set_arg_range(2, 2);
    set_syntax("[OPTION]... INPUTDIR CURSORSFILE");
    set_description("Packs PNG files into mouse cursors.");
    set_documentation("PNG files must be named from 0.png to 7.png and can "
        "have any dimension and\ncolors. They are automatically converted.");
};

void packcursors::exec(int argc, char *argv[])
{
    char *source = argv[0];
    char *dest = argv[1];

    ofstream file(dest);
    if (!file) throw io_error(string("Unable to create ") + dest);
    for (int i = 0; i < 8; i += 1)
    {
        ostringstream filename;
        filename << source << DIR_SEPARATOR << i << ".png";
        cursor c;
        png_to_image(filename.str().c_str(), c);
        file << c;
        if (!file) throw io_error("Unable to write cursors");
    }
    file.close();
}

}

int main(int argc, char *argv[])
{  
    return tools::packcursors().run(argc, argv);
}
