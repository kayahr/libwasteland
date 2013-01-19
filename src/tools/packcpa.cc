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
#include "packcpa.h"

using namespace std;
using namespace wasteland;

namespace tools
{

packcpa::packcpa() : program()
{
    set_arg_range(2, 2);
    set_syntax("[OPTION]... INPUTDIR CPAFILE");
    set_description("Packs PNG images to a CPA animation file.");
};

void packcpa::exec(int argc, char *argv[])
{
    char *source = argv[0];
    char *dest = argv[1];

    end_anim anim;

    ostringstream filename;
    filename << source << DIR_SEPARATOR << 0 << ".png";
    png_to_image(filename.str().c_str(), anim.get_base_frame());

    ostringstream delay_filename;
    delay_filename << source << DIR_SEPARATOR << "delays.txt";
    fstream delay_file(delay_filename.str().c_str(), ios_base::in);

    int index = 1;
    int delay;
    end_anim_frame prev_frame = anim.get_base_frame();
    while (delay_file >> delay)
    {
        ostringstream filename;
        filename << source << DIR_SEPARATOR << index << ".png";
        end_anim_frame next_frame;
        png_to_image(filename.str().c_str(), next_frame);
        end_anim_update update(delay);
        update.set_blocks(prev_frame, next_frame);
        anim.add_update(update);
        prev_frame = next_frame;
        index += 1;
    }
    delay_file.close();

    ofstream file(dest);
    if (!file) throw io_error(string("Unable to open ") + dest);
    file << anim;
    file.close();
}

}

int main(int argc, char *argv[])
{  
    return tools::packcpa().run(argc, argv);
}
