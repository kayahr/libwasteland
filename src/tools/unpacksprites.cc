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
#include "unpacksprites.h"

using namespace std;
using namespace wasteland;

namespace tools
{

unpacksprites::unpacksprites() : program()
{
    set_arg_range(3, 3);
    set_syntax("[OPTION]... SPRITESFILE MASKSFILE OUTPUTDIR");
    set_description("Unpacks sprites into PNG images.");
};

void unpacksprites::exec(int argc, char *argv[])
{
    char *colors = argv[0];
    char *masks = argv[1];
    char *dest = argv[2];

    mkdir(dest);

    ifstream colors_file(colors);
    if (!colors_file) throw io_error(string("Unable to open ") + colors);
    ifstream masks_file(masks);
    if (!masks_file) throw io_error(string("Unable to open ") + masks);
    sprite_istreams streams(colors_file, masks_file);
    for (int i = 0; i < 10; i += 1)
    {
        sprite sprite;
        streams >> sprite;
        if (!streams) throw io_error("Unable to read sprites");
        ostringstream filename;
        filename << dest << DIR_SEPARATOR << i << ".png";
        image_to_png(sprite, filename.str().c_str());
    }
    colors_file.close();
    masks_file.close();
}

}

int main(int argc, char *argv[])
{  
    return tools::unpacksprites().run(argc, argv);
}
