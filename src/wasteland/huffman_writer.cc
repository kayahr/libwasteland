/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <iostream>
#include "huffman_writer.h"
#include "huffman_node.h"
#include <iostream>

using std::ostream;
using std::cout;
using std::endl;

namespace wasteland
{

/**
 * Constructor.
 *
 * @param stream
 *            The input stream to wrap.
 */
huffman_writer::huffman_writer(ostream &stream)
{
    writer = new bit_writer(stream);
}

huffman_writer::~huffman_writer()
{
    reset();
    delete writer;
}

void huffman_writer::write_byte(const uint8_t value)
{
    // Add value to the buffer
    buffer.push_back(value);

    // Create huffman node for this value or increase the usage pointer if
    // there is already a node for this value
    huffman_node* node = node_index[value];
    if (!node)
    {
        node = new huffman_node(value);
        nodes.push_back(node);
        node_index[value] = node;
    }
    else
    {
        node->increase_usage();
    }
}

void huffman_writer::write_word(const uint16_t value)
{
    write_byte(value & 0xff);
    write_byte(value >> 8);
}

void huffman_writer::reset()
{
    for (std::list<huffman_node *>::const_iterator iterator = nodes.begin();
        iterator != nodes.end(); ++iterator)
    {
        delete *iterator;
    }
    buffer.clear();
    nodes.clear();
    node_index.clear();
}

void huffman_writer::write_node(const huffman_node *node)
{
    huffman_node *left = node->get_left();
    huffman_node *right = node->get_right();
    if (left && right)
    {
        writer->write_bit(0);
        write_node(left);
        writer->write_bit(0);
        write_node(right);
    }
    else
    {
        writer->write_bit(1);
        writer->write_byte(node->get_payload());
    }
}

/**
 * Writes a byte to the huffman encoded stream. You have to provide pointers
 * to the dataByte/dataMask storage bytes for the bit-based IO functions which
 * are used to read the huffman data and you also have to provide a huffman
 * node index (which is created by wlHuffmanBuildTree()) which is used to
 * lookup huffman nodes by payload.
 *
 * @param file
 *            The file stream
 * @param rootNode
 *            The root node of the huffman tree
 * @param dataByte
 *            Storage for last read byte
 * @param dateMask
 *            Storage for last bit mask
 * @return 1 on success, 0 on failure
 */

void huffman_writer::write_compressed_byte(const uint8_t byte)
{
    huffman_node *node = node_index[byte];
    for (int i = node->get_key_bits() - 1; i >= 0; i -= 1)
    {
        writer->write_bit((node->get_key() >> i) & 1);
    }
}

void huffman_writer::flush()
{
    cout << "1" << endl;
    // Do nothing if there is no data to flush
    if (buffer.empty()) return;

    // Convert node list into a node tree.
    while (nodes.size() > 1)
    {
        nodes.sort(compare_huffman_nodes);
        huffman_node *left = nodes.front();
        nodes.pop_front();
        huffman_node *right = nodes.front();
        nodes.pop_front();
        nodes.push_front(new huffman_node(left, right));
    }
    huffman_node *root = nodes.front();

    // Recursively write the huffman node tree
    write_node(root);

    // Write the compressed bytes from the buffer
    for (int i = 0, max = buffer.size(); i != max; i += 1)
    {
        write_compressed_byte(buffer[i]);
    }

    // Flush the bit writer to ensure that all bytes are written
    writer->flush();

    // Reset the huffman writer so it can be used for the next huffman tree
    reset();
}

}
