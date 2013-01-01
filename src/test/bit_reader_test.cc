/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <wasteland/bit_reader.h>
#include "bit_reader_test.h"

using std::stringstream;

namespace wasteland
{

CPPUNIT_TEST_SUITE_REGISTRATION(bit_reader_test);

void bit_reader_test::test_read_bit()
{
    stringstream stream("wl");
    bit_reader reader(*(stream.rdbuf()));

    CPPUNIT_ASSERT_EQUAL(0, reader.read_bit());
    CPPUNIT_ASSERT_EQUAL(1, reader.read_bit());
    CPPUNIT_ASSERT_EQUAL(1, reader.read_bit());
    CPPUNIT_ASSERT_EQUAL(1, reader.read_bit());
    CPPUNIT_ASSERT_EQUAL(0, reader.read_bit());
    CPPUNIT_ASSERT_EQUAL(1, reader.read_bit());
    CPPUNIT_ASSERT_EQUAL(1, reader.read_bit());
    CPPUNIT_ASSERT_EQUAL(1, reader.read_bit());

    CPPUNIT_ASSERT_EQUAL(0, reader.read_bit());
    CPPUNIT_ASSERT_EQUAL(1, reader.read_bit());
    CPPUNIT_ASSERT_EQUAL(1, reader.read_bit());
    CPPUNIT_ASSERT_EQUAL(0, reader.read_bit());
    CPPUNIT_ASSERT_EQUAL(1, reader.read_bit());
    CPPUNIT_ASSERT_EQUAL(1, reader.read_bit());
    CPPUNIT_ASSERT_EQUAL(0, reader.read_bit());
    CPPUNIT_ASSERT_EQUAL(0, reader.read_bit());

    CPPUNIT_ASSERT_EQUAL(-1, reader.read_bit());
}

void bit_reader_test::test_read_bits()
{
    stringstream stream("wl");
    bit_reader reader(*(stream.rdbuf()));

    CPPUNIT_ASSERT_EQUAL(0b0111, reader.read_bits(4));
    CPPUNIT_ASSERT_EQUAL(0b01, reader.read_bits(2));
    CPPUNIT_ASSERT_EQUAL(0b1101, reader.read_bits(4));
    CPPUNIT_ASSERT_EQUAL(0b1011, reader.read_bits(4));
    CPPUNIT_ASSERT_EQUAL(-1, reader.read_bits(3));
}

void bit_reader_test::test_read_byte()
{
    stringstream stream("wl");
    bit_reader reader(*(stream.rdbuf()));

    CPPUNIT_ASSERT_EQUAL('w', (char) reader.read_byte());
    CPPUNIT_ASSERT_EQUAL('l', (char) reader.read_byte());
}

}
