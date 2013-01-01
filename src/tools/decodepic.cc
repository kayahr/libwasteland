/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <fstream>
#include <wasteland/exceptions.h>
#include <wasteland/title_pic.h>
#include "gdutils.h"
#include "decodepic.h"

using namespace std;
using namespace wasteland;

namespace tools
{

decodepic::decodepic() : program("wl_decodepic")
{
    set_arg_range(2, 2);
    set_syntax("[OPTION]... PICFILE PNGFILE");
    set_description("Converts a wasteland PIC image file into a PNG image file.");
};

void decodepic::exec(int argc, char *argv[])
{
    char *source = argv[0];
    char *dest = argv[1];

    // Read the title_pic file
    ifstream infile(source);
    if (!infile) throw io_error(string("Unable to open ") + source);
    title_pic pic;
    infile >> pic;
    if (!infile) throw io_error(string("Unable to read ") + source);
    infile.close();

    // Write the PNG file
    image_to_png(pic, dest);
}

}

int main(int argc, char *argv[])
{  
    return tools::decodepic().run(argc, argv);
}
