/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <ios>
#include <iostream>
#include <fstream>
#include <sstream>
#include "sprite.h"
#include "bit_reader.h"
#include "title_pic.h"
#include "transparent_image.h"

using namespace std;
using namespace wasteland;

int main()
{
    sprite img;
    ifstream ic0_9("/home/k/.dosemu/drive_c/wland/ic0_9.wlf");
    ifstream masks("/home/k/.dosemu/drive_c/wland/masks.wlf");
    sprite_istreams streams(ic0_9, masks);

    ofstream ic0_9out("/tmp/ic0_9.wlf");
    ofstream masksout("/tmp/masks.wlf");
    sprite_ostreams streamsout(ic0_9out, masksout);

    while (streams >> img)
    {
        streamsout << img;
        for (int y = 0; y < img.get_height(); y++)
        {
            for (int x = 0; x < img.get_width(); x++)
            {
                cout << (char) (' ' + img.get_color(x, y));
            }
            cout << endl;
        }

        cout << endl;
    }

    return 0;
}
