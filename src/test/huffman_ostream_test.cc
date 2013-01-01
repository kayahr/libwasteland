/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include "huffman_ostream_test.h"
#include <wasteland/huffman_ostream.h>

using std::stringstream;
using std::string;

namespace wasteland
{

CPPUNIT_TEST_SUITE_REGISTRATION(huffman_ostream_test);

void huffman_ostream_test::test_put()
{
    stringstream stream;
    huffman_ostream huffman(stream);

    huffman.put('c');
    huffman.put('a');
    huffman.put('b');
    huffman.put('a');
    huffman.put('c');
    huffman.put('a');
    huffman.flush();

    CPPUNIT_ASSERT_EQUAL(string("\x2c\x4b\x1a\xc2\xcb"), stream.str());
}

void huffman_ostream_test::test_write()
{
    stringstream stream;
    huffman_ostream huffman(stream);
    uint16_t word = 0x3412;
    huffman.write((char *) &word, 2);
    word = 0x5634;
    huffman.write((char *) &word, 2);
    word = 0x5656;
    huffman.write((char *) &word, 2);
    huffman.flush();

    CPPUNIT_ASSERT_EQUAL(string("\x22\x49\xa2\xac\x2f"), stream.str());
}

}
