/*
 * Copyright (C) 2013 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <fstream>
#include <sstream>
#include <wasteland/exceptions.h>
#include <wasteland/sprite.h>
#include "gdutils.h"
#include "fileutils.h"
#include "packsprites.h"

using namespace std;
using namespace wasteland;

namespace tools
{

packsprites::packsprites() : program()
{
    set_arg_range(3, 3);
    set_syntax("[OPTION]... INPUTDIR SPRITESFILE MASKSFILE");
    set_description("Packs PNG files into sprites.");
    set_documentation("PNG files must be named from 0.png to 9.png and can "
        "have any dimension and\ncolors. They are automatically converted.");
};

void packsprites::exec(int argc, char *argv[])
{
    char *source = argv[0];
    char *colors = argv[1];
    char *masks = argv[2];

    ofstream colors_file(colors);
    if (!colors_file) throw io_error(string("Unable to create ") + colors);
    ofstream masks_file(masks);
    if (!masks_file) throw io_error(string("Unable to create ") + masks);
    sprite_ostreams streams(colors_file, masks_file);
    for (int i = 0; i < 10; i += 1)
    {
        ostringstream filename;
        filename << source << DIR_SEPARATOR << i << ".png";
        sprite sprite;
        png_to_image(filename.str().c_str(), sprite);
        streams << sprite;
        if (!streams) throw io_error("Unable to write sprites");
    }
    colors_file.close();
    masks_file.close();
}

}

int main(int argc, char *argv[])
{  
    return tools::packsprites().run(argc, argv);
}
