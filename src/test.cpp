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
#include "sprite.h"

using namespace std;
using namespace wasteland;

int main()
{
    ifstream in1("/home/k/.dosemu/drive_c/wland/ic0_9.wlf");
    ifstream in2("/home/k/.dosemu/drive_c/wland/masks.wlf");
    sprite_istreams in(in1, in2);

    sprite c;
    base_transparent_image *b = &c;
    while (in >> c)
    {
        for (int y = 0; y < b->get_height(); y++)
        {
            for (int x = 0; x < b->get_width(); x++)
            {
                if (b->is_opaque(x, y))
                {
                    cout << (char) (' ' + b->get_color(x, y));
                    cout << (char) (' ' + b->get_color(x, y));
                }
                else
                {
                    cout << "__";
                }
            }
            cout << endl;
        }

        cout << endl;
        cout << "------------------------------" << endl;
        cout << endl;
    }

    return 0;
}
