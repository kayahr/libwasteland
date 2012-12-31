/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_BIT_WRITER_TEST_H
#define LIBWASTELAND_BIT_WRITER_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace wasteland
{

class bit_writer_test: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(bit_writer_test);
    CPPUNIT_TEST(test_write_bit);
    CPPUNIT_TEST(test_write_bits);
    CPPUNIT_TEST(test_write_byte);
    CPPUNIT_TEST_SUITE_END();

protected:
    void test_write_bit();
    void test_write_bits();
    void test_write_byte();
};

}

#endif
