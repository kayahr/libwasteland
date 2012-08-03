#include <iostream>
#include <fstream>
#include <vector>
#include <sprite.h>

using namespace std;
using namespace wasteland;

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        cerr << "Syntax: " << argv[0] << " ic0_9-input masks-input ic0_9-output masks-output" << endl;
        return 1;
    }

    // Read the sprites
    vector<sprite> sprites;
    sprite s;
    ifstream colors_in(argv[1]);
    ifstream masks_in(argv[2]);
    sprite_istreams in(colors_in, masks_in);
    while (in >> s)
    {
        sprite test;
        test = s;
        sprites.push_back(s);
    }
    colors_in.close();
    masks_in.close();

    // Invert all sprites
    for (vector<sprite>::iterator s = sprites.begin(); s != sprites.end(); ++s)
    {
        for (int y = 0; y < s->get_height(); y += 1)
        {
            for (int x = 0; x < s->get_width(); x += 1)
            {
                sprite::color c = s->get_color(x, y);
                s->set_color(x, y, c ^ 15);
            }
        }
    }

    // Write the new sprites
    ofstream colors_out(argv[3]);
    ofstream masks_out(argv[4]);
    sprite_ostreams out(colors_out, masks_out);
    for (vector<sprite>::iterator it = sprites.begin(); it != sprites.end(); ++it)
    {
        out << *it;
    }
    colors_out.close();
    masks_out.close();
}
