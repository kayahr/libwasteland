/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_BIT_READER_TEST_H
#define LIBWASTELAND_BIT_READER_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace wasteland
{

class bit_reader_test: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(bit_reader_test);
    CPPUNIT_TEST(test_read_bit);
    CPPUNIT_TEST(test_read_bits);
    CPPUNIT_TEST(test_read_byte);
    CPPUNIT_TEST_SUITE_END();

protected:
    void test_read_bit();
    void test_read_bits();
    void test_read_byte();
};

}

#endif
