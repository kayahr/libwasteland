/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_HUFFMAN_NODE_H
#define LIBWASTELAND_HUFFMAN_NODE_H

#include <stdint.h>
#include "bit_reader.h"

namespace wasteland
{

/**
 * A single node in the huffman tree.
 */
class huffman_node
{
    friend class huffman_writer;
    friend bool compare_huffman_nodes(const huffman_node *a, const huffman_node *b);

public:
    /**
     * Constructs a new empty huffman node.
     */
    explicit huffman_node(bit_reader &reader);
    explicit huffman_node(const huffman_node &other);
    explicit huffman_node(const uint8_t payload);
    huffman_node(huffman_node *left, huffman_node *right);
    virtual ~huffman_node();

    huffman_node * get_left() const;
    huffman_node * get_right() const;
    uint8_t get_payload() const;
    int get_key() const;
    int get_key_bits() const;

private:
    huffman_node *parent;
    huffman_node *left;
    huffman_node *right;
    uint8_t payload;
    int key;
    int key_bits;
    int usage;

    int get_usage() const;
    void increase_usage();
    void set_key(const int key, const int key_bits);
};

bool compare_huffman_nodes(const huffman_node *a, const huffman_node *b);

}

#endif
