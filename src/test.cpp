/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <ios>
#include <iostream>
#include <fstream>
#include <sstream>
#include "title_pic.h"
#include "sprite.h"
#include "bit_reader.h"
#include "transparent_image.h"
#include "sprite.h"
#include "huffman_reader.h"
#include "huffman_writer.h"
#include <errno.h>
#include "tile.h"

using namespace std;
using namespace wasteland;

int main()
{
    tile img;
    ofstream out("/tmp/newallhtds1");
    tile_writer writer(out);

    ifstream in("/home/k/.dosemu/drive_c/wland/allhtds1");
    //ifstream in("/tmp/newallhtds1");
    tile_reader reader(in);
    while(reader)
    {
        int tiles = reader.count_tiles();
        int disk = reader.get_disk();
        cout << "Tiles: " << tiles << endl;
        for (int i = 0; i < tiles; i++)
        {
            cout << "Tile: " << reader.get_tile_no() << endl;
            reader >> img;
            writer << img;
        }
        writer.flush();
    //
    //    reader >> img;
    //    reader >> img;
    //    reader >> img;
    //
    //    for (int y = 0; y < 16; y++)
    //    {
    //        for (int x = 0; x < 16; x++)
    //        {
    //            cout << (char) (' ' + img.get_color(x, y));
    //            cout << (char) (' ' + img.get_color(x, y));
    //        }
    //        cout << endl;
    //    }
    }
    in.close();
    out.close();

    return 0;
}
