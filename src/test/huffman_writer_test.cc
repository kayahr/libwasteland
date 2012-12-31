/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include "huffman_writer_test.h"
#include <wasteland/huffman_writer.h>

using std::stringstream;
using std::string;

namespace wasteland
{

CPPUNIT_TEST_SUITE_REGISTRATION(huffman_writer_test);

void huffman_writer_test::test_write_byte()
{
    stringstream stream;
    huffman_writer writer(stream);

    writer.write_byte('c');
    writer.write_byte('a');
    writer.write_byte('b');
    writer.write_byte('a');
    writer.write_byte('c');
    writer.write_byte('a');
    writer.flush();

    CPPUNIT_ASSERT_EQUAL(string("\x2c\x4b\x1a\xc2\xcb"), stream.str());
}

void huffman_writer_test::test_write_word()
{
    stringstream stream;
    huffman_writer writer(stream);

    writer.write_word(0x3412);
    writer.write_word(0x5634);
    writer.write_word(0x5656);
    writer.flush();

    CPPUNIT_ASSERT_EQUAL(string("\x22\x49\xa2\xac\x2f"), stream.str());
}

}
