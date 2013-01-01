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
    friend class huffman_streambuf;
    friend bool compare_huffman_nodes(const huffman_node *a, const huffman_node *b);

public:
    /**
     * Constructs a new empty huffman node from data read from the specified
     * bit reader.
     *
     * @param reader
     *            The bit reader to read the huffman node from.
     */
    explicit huffman_node(bit_reader &reader);

    /**
     * Copy-constructor.
     *
     * @param other
     *            The other huffman node to copy the data from.
     */
    explicit huffman_node(const huffman_node &other);

    /**
     * Constructs a new huffman node with the specified payload.
     *
     * @param payload
     *            The payload to be represented by this huffman node.
     */
    explicit huffman_node(const uint8_t payload);

    /**
     * Constructs a new parent huffman node with the specified child nodes.
     *
     * @param left
     *            The left child node.
     * @param right
     *            The right child node.
     */
    huffman_node(huffman_node *left, huffman_node *right);

    /**
     * Destructor.
     */
    virtual ~huffman_node();

    /**
     * Returns the left child node.
     *
     * @return The left child node. NULL if none.
     */
    huffman_node * get_left() const;

    /**
     * Returns the right child node.
     *
     * @return The right child node. NULL if none.
     */
    huffman_node * get_right() const;

    /**
     * Returns the payload.
     *
     * @return The payload.
     */
    uint8_t get_payload() const;

    /**
     * Returns the key of this node in the huffman tree.
     *
     * @return The node key in the tree.
     */
    int get_key() const;

    /**
     * Returns the number of relevant bits in the node key.
     *
     * @return The number of relevant bits in the node key.
     */
    int get_key_bits() const;

private:
    /** The left child node. */
    huffman_node *left;

    /** The right child node. */
    huffman_node *right;

    /** The payload. */
    uint8_t payload;

    /** The node key in the huffman tree. */
    int key;

    /** The relevant bits in the node key. */
    int key_bits;

    /** The usage counter for tree generation. */
    int usage;

    /**
     * Returns how often the payload of this node is used in the data.
     *
     * @return The usage counter.
     */
    int get_usage() const;

    /**
     * Increases the usage counter during tree generation.
     */
    void increase_usage();

    /**
     * Sets the key of this node in the huffman tree. Also recursively sets
     * the keys in all child nodes.
     *
     * @param key
     *            The node key to set.
     * @param key_bits
     *            The number of relevant bits in the node key.
     */
    void set_key(const int key, const int key_bits);
};

bool compare_huffman_nodes(const huffman_node *a, const huffman_node *b);

}

#endif
