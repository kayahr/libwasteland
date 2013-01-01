/*
 * Copyright (C) 2012  Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <fstream>
#include <wasteland/exceptions.h>
#include <wasteland/title_pic.h>
#include "gdutils.h"
#include "encodepic.h"

using namespace std;
using namespace wasteland;

namespace tools
{

encodepic::encodepic() : program("wl_encodepic")
{
    set_arg_range(2, 2);
    set_syntax("[OPTION]... PNGFILE PICFILE");
    set_description("Converts a PNG image file into a PIC image file.");
    set_documentation("The PNG file can have any dimension and colors. "
        "It is automatically converted.");

};

void encodepic::exec(int argc, char *argv[])
{
    char *source = argv[0];
    char *dest = argv[1];

    // Create title pic from PNG
    title_pic pic;
    png_to_image(source, pic);

    // Write the title_pic file
    ofstream file(dest);
    if (!file) throw io_error(string("Unable to open ") + dest);
    file << pic;
    if (!file) throw io_error(string("Unable to read ") + dest);
    file.close();
}

}

int main(int argc, char *argv[])
{  
    return tools::encodepic().run(argc, argv);
}
