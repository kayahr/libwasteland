/*
 * Copyright (C) 2013 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <fstream>
#include <sstream>
#include <wasteland/exceptions.h>
#include <wasteland/font_char.h>
#include "gdutils.h"
#include "fileutils.h"
#include "unpackfont.h"

using namespace std;
using namespace wasteland;

namespace tools
{

unpackfont::unpackfont() : program()
{
    set_arg_range(2, 2);
    set_syntax("[OPTION]... FONTFILE OUTPUTDIR");
    set_description("Unpacks font into PNG images.");
};

void unpackfont::exec(int argc, char *argv[])
{
    char *source = argv[0];
    char *dest = argv[1];

    mkdir(dest);

    ifstream file(source);
    if (!source) throw io_error(string("Unable to open ") + source);
    for (int i = 0; i < 172; i += 1)
    {
        font_char c;
        file >> c;
        if (!file) throw io_error("Unable to read font");
        ostringstream filename;
        filename << dest << DIR_SEPARATOR << i << ".png";
        image_to_png(c, filename.str().c_str());
    }
    file.close();
}

}

int main(int argc, char *argv[])
{  
    return tools::unpackfont().run(argc, argv);
}
