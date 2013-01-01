/*
 * Copyright (C) 2013 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <fstream>
#include <sstream>
#include <wasteland/exceptions.h>
#include <wasteland/tile.h>
#include "gdutils.h"
#include "fileutils.h"
#include "unpacktiles.h"

using namespace std;
using namespace wasteland;

namespace tools
{

unpacktiles::unpacktiles() : program()
{
    set_arg_range(2, 2);
    set_syntax("[OPTION]... HTDS-FILE OUTPUTDIR");
    set_description("Unpacks the tile images into PNG images.");
};

void unpacktiles::exec(int argc, char *argv[])
{
    char *source = argv[0];
    char *dest = argv[1];

    mkdir(dest);

    ifstream file(source);
    if (!source) throw io_error(string("Unable to open ") + source);
    tile_reader reader(file);
    int tileset = 0;
    while (reader)
    {
        ostringstream dirname;
        dirname << dest << DIR_SEPARATOR << tileset;
        mkdir(dirname.str().c_str());

        int tiles = reader.count_tiles();
        for (int i = 0; i < tiles; i += 1)
        {
            tile img;
            reader >> img;
            ostringstream filename;
            filename << dest << DIR_SEPARATOR << tileset << DIR_SEPARATOR << i << ".png";
            image_to_png(img, filename.str().c_str());
        }
        tileset += 1;
    }
    file.close();
}

}

int main(int argc, char *argv[])
{  
    return tools::unpacktiles().run(argc, argv);
}
