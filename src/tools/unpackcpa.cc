/*
 * Copyright (C) 2013 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <fstream>
#include <sstream>
#include <wasteland/exceptions.h>
#include <wasteland/end_anim.h>
#include "gdutils.h"
#include "fileutils.h"
#include "unpackcpa.h"

using namespace std;
using namespace wasteland;

namespace tools
{

unpackcpa::unpackcpa() : program()
{
    set_arg_range(2, 2);
    set_syntax("[OPTION]... CPAFILE OUTPUTDIR");
    set_description("Unpacks CPA animation file into PNG images.");
};

void unpackcpa::exec(int argc, char *argv[])
{
    char *source = argv[0];
    char *dest = argv[1];

    mkdir(dest);

    ifstream file(source);
    if (!source) throw io_error(string("Unable to open ") + source);
    end_anim anim;
    file >> anim;
    if (!file) throw io_error("Unable to read end animation");

    end_anim_frame frame;
    ostringstream filename;
    filename << dest << DIR_SEPARATOR << 0 << ".png";
    frame = anim.get_base_frame();
    image_to_png(frame, filename.str().c_str());

    ostringstream delay_filename;
    delay_filename << dest << DIR_SEPARATOR << "delays.txt";
    fstream delay_file(delay_filename.str().c_str(), ios_base::out);

    int index = 1;
    for(vector<end_anim_update>::iterator update = anim.get_updates().begin(),
        end = anim.get_updates().end(); update != end; ++update)
    {
        update->apply(frame);
        ostringstream filename;
        filename << dest << DIR_SEPARATOR << index << ".png";
        delay_file << update->get_delay() << endl;
        image_to_png(frame, filename.str().c_str());
        index += 1;
    }

    delay_file.close();
    file.close();
}

}

int main(int argc, char *argv[])
{  
    return tools::unpackcpa().run(argc, argv);
}
