/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <ios>
#include <iostream>
#include <fstream>
#include <sstream>
#include "bit_reader.h"
#include "pic_reader.h"
#include "title_pic.h"

using std::ios;
using std::string;
using std::cout;
using std::ifstream;
using std::endl;
using std::stringstream;
using wasteland::bit_reader;
using wasteland::pic_reader;
using wasteland::image;
using wasteland::title_pic;

int main()
{
//    string data = "abcd";
//    stringstream stream(data);
//
//    bit_reader reader(stream);
//    int bit;
//
//    cout << reader.read_bits(16) << endl;
//
//    while ((bit = reader.read_bit()) != -1)
//    {
//        cout << (int) bit;
//    }
//
//    cout << endl;
//
//    image img(32, 8);
//    img(0, 0) = 12;
//    cout << (int) img(0, 0) << endl;

    title_pic pic;

    ifstream file("/home/k/.dosemu/drive_c/wland/title.pic", ios::binary);
    pic_reader reader(file);
    reader >> pic;

    for (int y = 0; y != pic.height(); y += 1)
    {
    	for (int x = 0; x != pic.width(); x += 1)
    	{
    		cout << (char) ('a' + pic(x, y));
    	}
    	cout << endl;
    }

    char a = 0xf0;

    return 0;
}
