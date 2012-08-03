#include <iostream>
#include <fstream>
#include <vector>
#include <cursor.h>

using namespace std;
using namespace wasteland;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cerr << "Syntax: " << argv[0] << " input output" << endl;
        return 1;
    }

    // Read the cursors
    vector<cursor> cursors;
    cursor c;
    ifstream in(argv[1]);
    while (in >> c) cursors.push_back(c);
    in.close();

    // Invert all cursors
    for (vector<cursor>::iterator c = cursors.begin(); c != cursors.end(); ++c)
    {
        for (int y = 0; y < c->get_height(); y += 1)
        {
            for (int x = 0; x < c->get_width(); x += 1)
            {
                cursor::color color = c->get_color(x, y);
                c->set_color(x, y, color ^ 15);
            }
        }
    }

    // Write the new cursors
    ofstream out(argv[2]);
    for (vector<cursor>::iterator c = cursors.begin(); c != cursors.end(); ++c)
    {
        out << *c;
    }
    out.close();
}
