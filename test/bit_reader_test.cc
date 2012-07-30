/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include "bit_reader_test.h"
#include "../src/bit_reader.h"

using std::stringstream;

namespace wasteland
{

CPPUNIT_TEST_SUITE_REGISTRATION(bit_reader_test);

void bit_reader_test::test_read_bit()
{
	stringstream stream("wl");
	bit_reader reader(stream);

	CPPUNIT_ASSERT_EQUAL(1, reader.read_bit());
	CPPUNIT_ASSERT_EQUAL(1, reader.read_bit());
	CPPUNIT_ASSERT_EQUAL(1, reader.read_bit());
	CPPUNIT_ASSERT_EQUAL(0, reader.read_bit());
	CPPUNIT_ASSERT_EQUAL(1, reader.read_bit());
	CPPUNIT_ASSERT_EQUAL(1, reader.read_bit());
	CPPUNIT_ASSERT_EQUAL(1, reader.read_bit());
	CPPUNIT_ASSERT_EQUAL(0, reader.read_bit());

	CPPUNIT_ASSERT_EQUAL(0, reader.read_bit());
	CPPUNIT_ASSERT_EQUAL(0, reader.read_bit());
	CPPUNIT_ASSERT_EQUAL(1, reader.read_bit());
	CPPUNIT_ASSERT_EQUAL(1, reader.read_bit());
	CPPUNIT_ASSERT_EQUAL(0, reader.read_bit());
	CPPUNIT_ASSERT_EQUAL(1, reader.read_bit());
	CPPUNIT_ASSERT_EQUAL(1, reader.read_bit());
	CPPUNIT_ASSERT_EQUAL(0, reader.read_bit());

	CPPUNIT_ASSERT_EQUAL(-1, reader.read_bit());
}

void bit_reader_test::test_read_bits()
{
	stringstream stream("wl");
	bit_reader reader(stream);

	CPPUNIT_ASSERT_EQUAL(0b0111, reader.read_bits(4));
	CPPUNIT_ASSERT_EQUAL(0b11, reader.read_bits(2));
	CPPUNIT_ASSERT_EQUAL(0b0001, reader.read_bits(4));
	CPPUNIT_ASSERT_EQUAL(0b1011, reader.read_bits(4));
	CPPUNIT_ASSERT_EQUAL(-1, reader.read_bits(3));
}

}
