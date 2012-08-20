/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include "huffman_reader_test.h"
#include "../src/huffman_reader.h"

using std::stringstream;

namespace wasteland
{

CPPUNIT_TEST_SUITE_REGISTRATION(huffman_reader_test);

void huffman_reader_test::test_read_byte()
{
    stringstream stream("\x16\xe5\xb0\xba\x2e\x65\x84\xab\x96\x55\x93\x4d\x71\x87\x80");
    huffman_reader reader(stream);

    CPPUNIT_ASSERT_EQUAL('W', (char) reader.read_byte());
    CPPUNIT_ASSERT_EQUAL('a', (char) reader.read_byte());
    CPPUNIT_ASSERT_EQUAL('s', (char) reader.read_byte());
    CPPUNIT_ASSERT_EQUAL('t', (char) reader.read_byte());
    CPPUNIT_ASSERT_EQUAL('e', (char) reader.read_byte());
    CPPUNIT_ASSERT_EQUAL('l', (char) reader.read_byte());
    CPPUNIT_ASSERT_EQUAL('a', (char) reader.read_byte());
    CPPUNIT_ASSERT_EQUAL('n', (char) reader.read_byte());
    CPPUNIT_ASSERT_EQUAL('d', (char) reader.read_byte());
}

void huffman_reader_test::test_read_word()
{
    stringstream stream("\x22\x49\xa2\xac\x2f");
    huffman_reader reader(stream);

    CPPUNIT_ASSERT_EQUAL(0x3412, reader.read_word());
    CPPUNIT_ASSERT_EQUAL(0x5634, reader.read_word());
    CPPUNIT_ASSERT_EQUAL(0x5656, reader.read_word());
}

}
