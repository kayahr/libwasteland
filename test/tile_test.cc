/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>
#include <cppunit/TestAssert.h>
#include "tile_test.h"
#include "../src/tile.h"

using std::string;
using std::ifstream;
using std::ostringstream;
using std::istringstream;

namespace wasteland
{

CPPUNIT_TEST_SUITE_REGISTRATION(tile_test);

void tile_test::test_constructor()
{
    tile img;
    CPPUNIT_ASSERT_EQUAL(16, (int) img.get_width());
    CPPUNIT_ASSERT_EQUAL(16, (int) img.get_height());
    for (int y = 0; y < 16; y += 1)
    {
        for (int x = 0; x < 16; x += 1)
        {
            CPPUNIT_ASSERT_EQUAL(0, (int) img.get_color(x, y));
        }
    }
}

void tile_test::test_copy_constructor()
{
    tile a;
    a.set_color(0, 0, 7);
    tile b(a);
    a.set_color(0, 0, 14);
    CPPUNIT_ASSERT_EQUAL(14, (int) a.get_color(0, 0));
    CPPUNIT_ASSERT_EQUAL(7, (int) b.get_color(0, 0));
}

void tile_test::test_assignment_operator()
{
    tile a;
    a.set_color(0, 0, 7);
    tile b;
    b.set_color(0, 0, 14);
    b.set_color(1, 0, 11);
    b = a;
    a.set_color(0, 0, 1);
    a.set_color(0, 0, 2);
    CPPUNIT_ASSERT_EQUAL(7, (int) b.get_color(0, 0));
    CPPUNIT_ASSERT_EQUAL(0, (int) b.get_color(1, 0));
}

void tile_test::test_get_width()
{
    tile img;
    CPPUNIT_ASSERT_EQUAL(16, (int) img.get_width());
}

void tile_test::test_get_height()
{
    tile img;
    CPPUNIT_ASSERT_EQUAL(16, (int) img.get_height());
}

void tile_test::test_get_set_color()
{
    tile img;
    img.set_color(0, 0, 0);
    img.set_color(0, 1, 5);
    img.set_color(-1, 0, 7);
    img.set_color(288, 0, 7);
    img.set_color(0, -1, 7);
    img.set_color(0, 128, 7);
    CPPUNIT_ASSERT_EQUAL(0, (int) img.get_color(0, 0));
    CPPUNIT_ASSERT_EQUAL(5, (int) img.get_color(0, 1));

    img.set_color(0, 0, 255);
    img.set_color(0, 1, 255);
    CPPUNIT_ASSERT_EQUAL(15, (int) img.get_color(0, 0));
    CPPUNIT_ASSERT_EQUAL(15, (int) img.get_color(0, 1));
}

void tile_test::test_equals()
{
    tile a, b;

    CPPUNIT_ASSERT(a == b);

    a.set_color(0, 0, 1);
    CPPUNIT_ASSERT(a != b);

    b.set_color(0, 0, 1);
    CPPUNIT_ASSERT(a == b);

    a.set_color(15, 15, 8);
    CPPUNIT_ASSERT(a != b);
}

void tile_test::test_read()
{
    tile img;
    ifstream in("data/allhtds1");
    tile_reader reader(in);

    CPPUNIT_ASSERT_EQUAL(2, reader.count_tiles());
    reader >> img;

    CPPUNIT_ASSERT_EQUAL(0, (int) img.get_color(0, 0));
    CPPUNIT_ASSERT_EQUAL(1, (int) img.get_color(1, 0));
    CPPUNIT_ASSERT_EQUAL(2, (int) img.get_color(0, 1));
    CPPUNIT_ASSERT_EQUAL(3, (int) img.get_color(1, 1));

    CPPUNIT_ASSERT_EQUAL(4, (int) img.get_color(15, 0));
    CPPUNIT_ASSERT_EQUAL(5, (int) img.get_color(14, 0));
    CPPUNIT_ASSERT_EQUAL(6, (int) img.get_color(15, 1));
    CPPUNIT_ASSERT_EQUAL(7, (int) img.get_color(14, 1));

    CPPUNIT_ASSERT_EQUAL(8, (int) img.get_color(15, 15));
    CPPUNIT_ASSERT_EQUAL(9, (int) img.get_color(14, 15));
    CPPUNIT_ASSERT_EQUAL(10, (int) img.get_color(15, 14));
    CPPUNIT_ASSERT_EQUAL(11, (int) img.get_color(14, 14));

    CPPUNIT_ASSERT_EQUAL(12, (int) img.get_color(0, 15));
    CPPUNIT_ASSERT_EQUAL(13, (int) img.get_color(1, 15));
    CPPUNIT_ASSERT_EQUAL(14, (int) img.get_color(0, 14));
    CPPUNIT_ASSERT_EQUAL(15, (int) img.get_color(1, 14));

    reader >> img;

    CPPUNIT_ASSERT_EQUAL(3, reader.count_tiles());

    reader >> img;
    reader >> img;
    reader >> img;

    CPPUNIT_ASSERT_EQUAL(false, (bool) reader);

    in.close();
}

void tile_test::test_write()
{
    tile img;

    img.set_color(0, 0, 0);
    img.set_color(1, 0, 1);
    img.set_color(0, 1, 2);
    img.set_color(1, 1, 3);

    img.set_color(15, 0, 4);
    img.set_color(14, 0, 5);
    img.set_color(15, 1, 6);
    img.set_color(14, 1, 7);

    img.set_color(15, 15, 8);
    img.set_color(14, 15, 9);
    img.set_color(15, 14, 10);
    img.set_color(14, 14, 11);

    img.set_color(0, 15, 12);
    img.set_color(1, 15, 13);
    img.set_color(0, 14, 14);
    img.set_color(1, 14, 15);

    ostringstream out;
    tile_writer writer(out, 1);
    writer << img;
    writer.flush();
    string data = out.str();

    ifstream in1("data/allhtds1");
    istringstream in2(data);
    tile_reader reader1(in1);
    tile_reader reader2(in2);

    tile a, b;
    CPPUNIT_ASSERT_EQUAL(1, reader2.get_disk());
    reader1 >> a;
    reader2 >> b;

    CPPUNIT_ASSERT(a == b);
}

}
