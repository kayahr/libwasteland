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
#include "huffman_reader.h"
#include "huffman_writer.h"
#include <errno.h>

using namespace std;
using namespace wasteland;

int main()
{
    string s;

    ifstream in("/tmp/test");
    in.exceptions( std::ios::failbit );
    if (in == NULL) cout << "No stream" << endl;
//    cout << "stream open. Press enter now" << endl;
//    cin >> s;
    bit_reader reader(in);
    cout << (int) reader.read_bit() << endl;
    cout << (int) reader.read_bit() << endl;
    cout << (int) reader.read_bit() << endl;
    cout << (int) reader.read_bit() << endl;
    cout << (int) reader.read_bit() << endl;
    cout << (int) reader.read_bit() << endl;
    cout << (int) reader.read_bit() << endl;
    cout << (int) reader.read_bit() << endl;
    cout << (int) reader.read_bit() << endl;

    ofstream out("/tmp/huffman.out");
    huffman_writer writer(out);

    writer.write_byte('c');
    writer.write_byte('a');
    writer.write_byte('b');
    writer.write_byte('a');
    writer.write_byte('c');
    writer.write_byte('a');
    writer.flush();
    return 0;
}
