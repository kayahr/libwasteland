/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <cstring>
#include "huffman_streambuf.h"

using std::istream;
using std::streambuf;
using std::streamsize;

namespace wasteland
{

huffman_streambuf::huffman_streambuf(streambuf *buffer) :
   buffer(buffer),
   root(NULL)
{
    reader = new bit_reader(*buffer);
    reset();
}

huffman_streambuf::~huffman_streambuf()
{
    sync();
    delete reader;
    if (root) delete root;
}

void huffman_streambuf::reset()
{
    reader->reset();
    if (root) delete root;
    root = NULL;
    setg(0, 0, 0);
    setp(&value, &value + 1);
}

huffman_node * huffman_streambuf::get_root()
{
    if (!root) root = new huffman_node(*reader);
    return root;
}

streambuf::int_type huffman_streambuf::underflow()
{
    huffman_node *node = get_root();
    if (!node) return traits_type::eof();
    while (node->get_left() != NULL)
    {
        int bit = reader->read_bit();
        if (bit < 0) return traits_type::eof();
        node = bit ? node->get_right() : node->get_left();
    }
    value = node->get_payload();
    setg(&value, &value, &value +1);
    return traits_type::to_int_type(*gptr());
}

/*
streambuf::int_type huffman_streambuf::overflow(streambuf::int_type value)
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
*/

int huffman_streambuf::sync()
{
    streambuf::int_type result = this->overflow(traits_type::eof());
    buffer->pubsync();
    return traits_type::eq_int_type(result, traits_type::eof()) ? -1 : 0;
}

}
