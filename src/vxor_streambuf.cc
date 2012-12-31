/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <cstring>
#include "vxor_streambuf.h"

using std::istream;
using std::streambuf;
using std::streamsize;

namespace wasteland
{

vxor_streambuf::vxor_streambuf(streambuf *buffer, const int width) :
   buffer(buffer),
   size(width / 2)
{
    previous_line = new char[size];
    current_line = new char[size];
    reset();
}

vxor_streambuf::~vxor_streambuf()
{
    sync();
    delete[] previous_line;
    delete[] current_line;
}

void vxor_streambuf::reset()
{
    memset(previous_line, 0, size);
    setg(0, 0, 0);
    setp(current_line, current_line + size);
}

streambuf::int_type vxor_streambuf::underflow()
{
    // Read line from original buffer
    streamsize read = buffer->sgetn(current_line, size);
    if (!read) return traits_type::eof();

    // Do vertical XOR decoding
    for (int i = 0; i < size; i += 1)
    {
        current_line[i] ^= previous_line[i];
        previous_line[i] = current_line[i];
    }

    // Set read area pointers
    setg(current_line, current_line, current_line + read);

    return traits_type::to_int_type(*gptr());
}

streambuf::int_type vxor_streambuf::overflow(streambuf::int_type value)
{
    int write = pptr() - pbase();
    if (write)
    {
        // Do vertical XOR encoding
        for (int i = 0; i < size; i += 1)
        {
            char tmp = current_line[i];
            current_line[i] ^= previous_line[i];
            previous_line[i] = tmp;
        }

        // Write line to original buffer
        streamsize written = buffer->sputn(current_line, write);
        if (written != write) return traits_type::eof();
    }

    // Set write area and put first value into it (If it is not EOF)
    setp(current_line, current_line + size);
    if (!traits_type::eq_int_type(value, traits_type::eof())) sputc(value);

    return traits_type::not_eof(value);
};

int vxor_streambuf::sync()
{
    streambuf::int_type result = this->overflow(traits_type::eof());
    buffer->pubsync();
    return traits_type::eq_int_type(result, traits_type::eof()) ? -1 : 0;
}

}
