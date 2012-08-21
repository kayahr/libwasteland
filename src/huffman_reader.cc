/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include "huffman_reader.h"
#include "huffman_node.h"
#include <iostream>

using std::istream;

namespace wasteland
{

huffman_reader::huffman_reader(istream &stream) : root(NULL)
{
    reader = new bit_reader(stream);
}

huffman_reader::~huffman_reader()
{
    delete reader;
    if (root) delete root;
}

huffman_node * huffman_reader::get_root()
{
    if (!root) root = new huffman_node(*reader);
    return root;
}

int huffman_reader::read_byte()
{
    huffman_node *node = get_root();
    if (!node) return -1;
    while (node->get_left() != NULL)
    {
        int bit = reader->read_bit();
        if (bit < 0) return -1;
        node = bit ? node->get_right() : node->get_left();
    }
    return node->get_payload();
}

int huffman_reader::read_word()
{
    int low = read_byte();
    if (low == -1) return -1;
    int high = read_byte();
    if (high == -1) return -1;
    return high << 8 | low;
}

void huffman_reader::read(uint8_t *data, const int size)
{
    for (int i = 0; i != size; i += 1)
    {
        data[i] = read_byte();
    }
}

void huffman_reader::reset()
{
    reader->reset();
    if (root) delete root;
    root = NULL;
}

}
