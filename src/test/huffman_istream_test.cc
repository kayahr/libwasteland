/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include "huffman_istream_test.h"
#include <wasteland/huffman_istream.h>

using std::stringstream;

namespace wasteland
{

CPPUNIT_TEST_SUITE_REGISTRATION(huffman_istream_test);

void huffman_istream_test::test_get()
{
    stringstream stream("\x16\xe5\xb0\xba\x2e\x65\x84\xab\x96\x55\x93\x4d\x71\x87\x80");
    huffman_istream huffman(stream);

    CPPUNIT_ASSERT_EQUAL('W', (char) huffman.get());
    CPPUNIT_ASSERT_EQUAL('a', (char) huffman.get());
    CPPUNIT_ASSERT_EQUAL('s', (char) huffman.get());
    CPPUNIT_ASSERT_EQUAL('t', (char) huffman.get());
    CPPUNIT_ASSERT_EQUAL('e', (char) huffman.get());
    CPPUNIT_ASSERT_EQUAL('l', (char) huffman.get());
    CPPUNIT_ASSERT_EQUAL('a', (char) huffman.get());
    CPPUNIT_ASSERT_EQUAL('n', (char) huffman.get());
    CPPUNIT_ASSERT_EQUAL('d', (char) huffman.get());
}

void huffman_istream_test::test_read()
{
    stringstream stream("\x22\x49\xa2\xac\x2f");
    huffman_istream huffman(stream);
    uint16_t word;

    huffman.read((char *) &word, 2);
    CPPUNIT_ASSERT_EQUAL((uint16_t) 0x3412, word);
    huffman.read((char *) &word, 2);
    CPPUNIT_ASSERT_EQUAL((uint16_t) 0x5634, word);
    huffman.read((char *) &word, 2);
    CPPUNIT_ASSERT_EQUAL((uint16_t) 0x5656, word);
}

}
