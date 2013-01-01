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
#include "unpackcursors.h"

using namespace std;
using namespace wasteland;

namespace tools
{

unpackcursors::unpackcursors() : program()
{
    set_arg_range(2, 2);
    set_syntax("[OPTION]... CURSORSFILE OUTPUTDIR");
    set_description("Unpacks mouse cursors into PNG images.");
};

void unpackcursors::exec(int argc, char *argv[])
{
    char *source = argv[0];
    char *dest = argv[1];

    mkdir(dest);

    ifstream file(source);
    if (!source) throw io_error(string("Unable to open ") + source);
    for (int i = 0; i < 8; i += 1)
    {
        cursor c;
        file >> c;
        if (!file) throw io_error("Unable to read cursors");
        ostringstream filename;
        filename << dest << DIR_SEPARATOR << i << ".png";
        image_to_png(c, filename.str().c_str());
    }
    file.close();
}

}

int main(int argc, char *argv[])
{  
    return tools::unpackcursors().run(argc, argv);
}
