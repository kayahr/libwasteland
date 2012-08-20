/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include "bit_writer_test.h"
#include "../src/bit_writer.h"

using std::stringstream;

namespace wasteland
{

CPPUNIT_TEST_SUITE_REGISTRATION(bit_writer_test);

void bit_writer_test::test_write_bit()
{
    stringstream stream;
    bit_writer writer(stream);

    writer.write_bit(0);
    writer.write_bit(1);
    writer.write_bit(1);
    writer.write_bit(1);
    writer.write_bit(0);
    writer.write_bit(1);
    writer.write_bit(1);
    writer.write_bit(1);

    writer.write_bit(0);
    writer.write_bit(1);
    writer.write_bit(1);
    writer.write_bit(0);
    writer.write_bit(1);
    writer.write_bit(1);
    writer.write_bit(0);
    writer.write_bit(0);
    writer.flush();

    CPPUNIT_ASSERT_EQUAL(std::string("wl"), stream.str());
}

void bit_writer_test::test_write_bits()
{
    stringstream stream;
    bit_writer writer(stream);

    writer.write_bits(0b0111, 4);
    writer.write_bits(0b01, 2);
    writer.write_bits(0b1101, 4);
    writer.write_bits(0b1011, 4);
    writer.flush();

    CPPUNIT_ASSERT_EQUAL(std::string("wl"), stream.str());
}

void bit_writer_test::test_write_byte()
{
    stringstream stream;
    bit_writer writer(stream);

    writer.write_byte('w');
    writer.write_byte('l');
    // No flushing here because last command must have filled 8 bits already

    CPPUNIT_ASSERT_EQUAL(std::string("wl"), stream.str());
}

}
