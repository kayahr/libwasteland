/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_HUFFMAN_READER_TEST_H
#define LIBWASTELAND_HUFFMAN_READER_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace wasteland
{

class huffman_reader_test: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(huffman_reader_test);
    CPPUNIT_TEST(test_read_byte);
    CPPUNIT_TEST(test_read_word);
    CPPUNIT_TEST_SUITE_END();

protected:
    void test_read_byte();
    void test_read_word();
};

}

#endif
