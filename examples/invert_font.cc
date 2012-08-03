#include <iostream>
#include <fstream>
#include <vector>
#include <font_char.h>

using namespace std;
using namespace wasteland;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cerr << "Syntax: " << argv[0] << " input output" << endl;
        return 1;
    }

    // Read the font characters
    vector<font_char> font;
    font_char c;
    ifstream in(argv[1]);
    while (in >> c) font.push_back(c);
    in.close();

    // Invert all font characters
    for (vector<font_char>::iterator fc = font.begin(); fc != font.end(); ++fc)
    {
        for (int y = 0; y < fc->get_height(); y += 1)
        {
            for (int x = 0; x < fc->get_width(); x += 1)
            {
                font_char::color color = fc->get_color(x, y);
                fc->set_color(x, y, color ^ 15);
            }
        }
    }

    // Write the new font characters
    ofstream out(argv[2]);
    for (vector<font_char>::iterator it = font.begin(); it != font.end(); ++it)
    {
        out << *it;
    }
    out.close();
}
