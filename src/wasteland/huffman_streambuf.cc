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
   root(NULL),
   value(0)
{
    reader = new bit_reader(*buffer);
    writer = new bit_writer(*buffer);
    reset();
}

huffman_streambuf::~huffman_streambuf()
{
    sync();
    delete reader;
    delete writer;
    if (root) delete root;
}

void huffman_streambuf::reset()
{
    reader->reset();
    if (root) delete root;
    root = NULL;

    for (std::list<huffman_node *>::const_iterator iterator = nodes.begin();
            iterator != nodes.end(); ++iterator)
    {
        delete *iterator;
    }
    values.clear();
    nodes.clear();
    node_index.clear();
    value = 0;

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

streambuf::int_type huffman_streambuf::overflow(streambuf::int_type value)
{
    int write = pptr() - pbase();
    if (write)
    {
        // Add value to the buffer
        values.push_back(this->value);

        // Create huffman node for this value or increase the usage pointer if
        // there is already a node for this value
        huffman_node* node = node_index[this->value];
        if (!node)
        {
            node = new huffman_node(this->value);
            nodes.push_back(node);
            node_index[this->value] = node;
        }
        else
        {
            node->increase_usage();
        }
    }

    // Set write area and put first value into it (If it is not EOF)
    setp(&this->value, &this->value + 1);
    if (!traits_type::eq_int_type(value, traits_type::eof())) sputc(value);

    return traits_type::not_eof(value);
};

int huffman_streambuf::sync()
{
    streambuf::int_type result = this->overflow(traits_type::eof());

    // Do nothing if there is no data to flush
    if (!values.empty())
    {
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
        for (int i = 0, max = values.size(); i != max; i += 1)
        {
            write_compressed_byte(values[i]);
        }

        // Flush the bit writer to ensure that all bytes are written
        writer->flush();

        // Reset the buffer so it can be used for the next huffman tree
        reset();
    }

    return traits_type::eq_int_type(result, traits_type::eof()) ? -1 : 0;
}


void huffman_streambuf::write_node(const huffman_node *node)
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

void huffman_streambuf::write_compressed_byte(const uint8_t byte)
{
    huffman_node *node = node_index[byte];
    for (int i = node->get_key_bits() - 1; i >= 0; i -= 1)
    {
        writer->write_bit((node->get_key() >> i) & 1);
    }
}

}
