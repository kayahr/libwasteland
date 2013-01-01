/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_HUFFMAN_WRITER_TEST_H
#define LIBWASTELAND_HUFFMAN_WRITER_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace wasteland
{

class huffman_ostream_test: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(huffman_ostream_test);
    CPPUNIT_TEST(test_put);
    CPPUNIT_TEST(test_write);
    CPPUNIT_TEST_SUITE_END();

protected:
    void test_put();
    void test_write();
};

}

#endif
