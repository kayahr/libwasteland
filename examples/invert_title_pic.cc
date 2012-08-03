#include <iostream>
#include <fstream>
#include <title_pic.h>

using namespace std;
using namespace wasteland;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cerr << "Syntax: " << argv[0] << " input output" << endl;
        return 1;
    }

    // Read the picture
    title_pic pic;
    ifstream in(argv[1]);
    in >> pic;
    in.close();

    // Invert all pixels
    for (int y = 0; y < pic.get_height(); y += 1)
    {
        for (int x = 0; x < pic.get_width(); x += 1)
        {
            title_pic::color c = pic.get_color(x, y);
            pic.set_color(x, y, c ^ 15);
        }
    }

    // Write the new picture
    ofstream out(argv[2]);
    out << pic;
    out.close();
}
