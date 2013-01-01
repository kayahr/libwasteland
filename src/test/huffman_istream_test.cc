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

void huffman_istream_test::test_read()
{
    stringstream stream("\x16\xe5\xb0\xba\x2e\x65\x84\xab\x96\x55\x93\x4d\x71\x87\x80");
    huffman_istream reader(stream);

    CPPUNIT_ASSERT_EQUAL('W', (char) reader.get());
    CPPUNIT_ASSERT_EQUAL('a', (char) reader.get());
    CPPUNIT_ASSERT_EQUAL('s', (char) reader.get());
    CPPUNIT_ASSERT_EQUAL('t', (char) reader.get());
    CPPUNIT_ASSERT_EQUAL('e', (char) reader.get());
    CPPUNIT_ASSERT_EQUAL('l', (char) reader.get());
    CPPUNIT_ASSERT_EQUAL('a', (char) reader.get());
    CPPUNIT_ASSERT_EQUAL('n', (char) reader.get());
    CPPUNIT_ASSERT_EQUAL('d', (char) reader.get());
}

//void huffman_istream_test::test_read_word()
//{
//    stringstream stream("\x22\x49\xa2\xac\x2f");
//    huffman_istream reader(stream);
//
//    CPPUNIT_ASSERT_EQUAL(0x3412, reader.read_word());
//    CPPUNIT_ASSERT_EQUAL(0x5634, reader.read_word());
//    CPPUNIT_ASSERT_EQUAL(0x5656, reader.read_word());
//}

}
