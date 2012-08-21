/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <stdexcept>
#include <iostream>
#include "huffman_node.h"
#include "exceptions.h"

namespace wasteland
{

huffman_node::huffman_node(const huffman_node &other):
    left(other.left),
    right(other.right),
    payload(other.payload),
    usage(other.usage),
    key(other.key),
    key_bits(other.key_bits)
{
}

huffman_node::huffman_node(const uint8_t payload):
    left(NULL),
    right(NULL),
    payload(payload),
    usage(1),
    key(0),
    key_bits(0)
{
}

huffman_node::huffman_node(huffman_node *left, huffman_node *right):
    left(left),
    right(right),
    payload(0),
    usage(left->usage + right->usage)
{
    set_key(0, 0);
}

huffman_node::huffman_node(bit_reader &reader) :
    key(0),
    key_bits(0)
{
    uint8_t bit;

    // Read payload or sub nodes.
    if ((bit = reader.read_bit()) == -1) throw eos_error();
    if (bit)
    {
        left = NULL;
        right = NULL;
        if ((payload = reader.read_byte()) == -1) throw eos_error();
        usage = 0;
    }
    else
    {
        left = new huffman_node(reader);
        if (reader.read_bit() == -1)  throw eos_error();
        right = new huffman_node(reader);
        payload = 0;
        usage = 1;
    }
}

huffman_node::~huffman_node()
{
    if (right) delete right;
    if (left) delete left;
}

huffman_node * huffman_node::get_left() const
{
    return left;
}

huffman_node * huffman_node::get_right() const
{
    return right;
}

uint8_t huffman_node::get_payload() const
{
    return payload;
}

int huffman_node::get_usage() const
{
    return usage;
}

void huffman_node::increase_usage()
{
    usage += 1;
}

int huffman_node::get_key() const
{
    return key;
}

int huffman_node::get_key_bits() const
{
    return key_bits;
}

void huffman_node::set_key(const int key, const int key_bits)
{
    // Special case (only one node is present)
    if (!key_bits && !left && !right)
    {
        this->key = 0;
        this->key_bits = 1;
        return;
    }

    // Store key
    this->key = key;
    this->key_bits = key_bits;

    // Dive into sub nodes
    if (right) left->set_key(key << 1, key_bits + 1);
    if (right) right->set_key((key << 1) | 1, key_bits + 1);
}

bool compare_huffman_nodes(const huffman_node *a, const huffman_node *b)
{
    return a->get_usage() < b->get_usage();
}

}
