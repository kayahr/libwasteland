/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <cstring>
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
#include "end_anim.h"
#include "end_anim_frame.h"
#include <errno.h>
#include "tile.h"
#include "vxor_streambuf.h"
#include "vxor_istream.h"
#include "vxor_ostream.h"

using namespace std;
using namespace wasteland;

int main()
{
//    end_anim_frame frame;
//    vector<end_anim_update> updates;
//    add(updates);
//    frame. insert(frame.begin(), updates.begin(), updates.end());
//    cout << frame.size() << endl;
//    cout << frame.at(0).get_update() << endl;
//    cout << frame.at(0).get_offset() << endl;

	ifstream file("/home/k/.dosemu/drive_c/wland/title.pic");
	//vxor_streambuf buf(file, 288);
	vxor_istream in(file, 288);
	//istream in(&buf);

	//cout << anim.get_frames().size() << endl;

//    tile img;
//    ofstream out("/tmp/newallhtds1");
//    tile_writer writer(out);
//
//    ifstream in("/home/k/.dosemu/drive_c/wland/allhtds1");
//    //ifstream in("/tmp/newallhtds1");
//    tile_reader reader(in);
//    while(reader)
//    {
//        int tiles = reader.count_tiles();
//        int disk = reader.get_disk();
//        cout << "Tiles: " << tiles << endl;
//        for (int i = 0; i < tiles; i++)
//        {
//            cout << "Tile: " << reader.get_tile_no() << endl;
//            reader >> img;
//            writer << img;
//        }
//        writer.flush();
//    //
//    //    reader >> img;
//    //    reader >> img;
//    //    reader >> img;
//    //
	char buf2[144 * 128];
	in.read(buf2, 144*128);

	//char buf3[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

	ofstream outfile("/tmp/title.pic");
    vxor_ostream out(outfile, 288);
    out.write(buf2, 144*128);
    out.flush();
    outfile.close();

    //vxor_streambuf *outbuf = new vxor_streambuf(outfile.rdbuf(), 32);
	//ostream *out = new ostream(outbuf);
	//vxor_ostream *out = new vxor_ostream(outfile, 32);
//	for (int i = 0; i < 15; i++)
	//out << '\0';




//    out->write(buf3, 16);
    //out->flush();
    //delete outbuf;
//	out->flush();

//	ifstream infile("/tmp/title.pic");
//	vxor_istream in2(infile, 32);
//	for (int i = 0; i < 15; i++)
//	{
//	    in2.read(buf3, 16);
//	    for (int j = 0; j < 16; j++)
//	        cout << (int) buf3[j] << ", ";
//	    cout << endl;
//	}
//	infile.close();



        for (int y = 0; y < 128; y++)
        {
            for (int x = 0; x < 144; x++)
            {
                char c;

                //c = in.get();
                c = buf2[y * 144 + x];
//                if (c == -1) break;
                cout << (char) (' ' + ((c >> 4) & 0xf));
                cout << (char) (' ' + (c & 0xf));

                //cout << (char) (' ' + anim.get_color(x, y));
            }
            cout << endl;
        }
    file.close();

   // cerr << "End of app" << endl;
    return 0;
}
