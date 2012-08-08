/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>
#include <cppunit/TestAssert.h>
#include "sprite_test.h"
#include "../src/sprite_istreams.h"
#include "../src/sprite_ostreams.h"
#include "../src/sprite.h"

using std::string;
using std::ifstream;
using std::ostringstream;
using std::istringstream;

namespace wasteland
{

CPPUNIT_TEST_SUITE_REGISTRATION(sprite_test);

void sprite_test::test_constructor()
{
    sprite pic;
    CPPUNIT_ASSERT_EQUAL(16, (int) pic.get_width());
    CPPUNIT_ASSERT_EQUAL(16, (int) pic.get_height());
    for (int y = 0; y < 16; y += 1)
    {
        for (int x = 0; x < 16; x += 1)
        {
            CPPUNIT_ASSERT_EQUAL(0, (int) pic.get_color(x, y));
            CPPUNIT_ASSERT_EQUAL(true, pic.is_opaque(x, y));
        }
    }
}

void sprite_test::test_copy_constructor()
{
    sprite a;
    a.set_color(0, 0, 7);
    sprite b(a);
    a.set_color(0, 0, 14);
    CPPUNIT_ASSERT_EQUAL(14, (int) a.get_color(0, 0));
    CPPUNIT_ASSERT_EQUAL(7, (int) b.get_color(0, 0));
}

void sprite_test::test_assignment_operator()
{
    sprite a;
    a.set_color(0, 0, 7);
    sprite b;
    b.set_color(0, 0, 14);
    b.set_color(1, 0, 11);
    b = a;
    a.set_color(0, 0, 1);
    a.set_color(0, 0, 2);
    CPPUNIT_ASSERT_EQUAL(7, (int) b.get_color(0, 0));
    CPPUNIT_ASSERT_EQUAL(0, (int) b.get_color(1, 0));
}

void sprite_test::test_get_width()
{
    sprite img;
    CPPUNIT_ASSERT_EQUAL(16, (int) img.get_width());
}

void sprite_test::test_get_height()
{
    sprite img;
    CPPUNIT_ASSERT_EQUAL(16, (int) img.get_height());
}

void sprite_test::test_get_set_color()
{
    sprite img;
    img.set_color(0, 0, 0);
    img.set_color(0, 1, 5);
    img.set_color(-1, 0, 7);
    img.set_color(16, 0, 7);
    img.set_color(0, -1, 7);
    img.set_color(0, 16, 7);
    CPPUNIT_ASSERT_EQUAL(0, (int) img.get_color(0, 0));
    CPPUNIT_ASSERT_EQUAL(5, (int) img.get_color(0, 1));

    img.set_color(0, 0, 255);
    img.set_color(0, 1, 255);
    CPPUNIT_ASSERT_EQUAL(15, (int) img.get_color(0, 0));
    CPPUNIT_ASSERT_EQUAL(15, (int) img.get_color(0, 1));
}

void sprite_test::test_get_set_transparency()
{
    sprite img;
    img.set_transparent(0, 0, false);
    img.set_transparent(1, 0, true);
    img.set_opaque(0, 1, false);
    img.set_opaque(1, 1, true);

    CPPUNIT_ASSERT_EQUAL(false, img.is_transparent(0, 0));
    CPPUNIT_ASSERT_EQUAL(true, img.is_transparent(0, 1));
    CPPUNIT_ASSERT_EQUAL(false, img.is_opaque(1, 0));
    CPPUNIT_ASSERT_EQUAL(true, img.is_opaque(1, 1));
}

void sprite_test::test_equals()
{
    sprite a, b;

    CPPUNIT_ASSERT(a == b);

    a.set_color(0, 0, 1);
    CPPUNIT_ASSERT(a != b);

    b.set_color(0, 0, 1);
    CPPUNIT_ASSERT(a == b);

    a.set_color(15, 15, 8);
    CPPUNIT_ASSERT(a != b);
}

void sprite_test::test_read()
{
    sprite pic;

    ifstream colors_in("data/ic0_9.wlf");
    ifstream masks_in("data/masks.wlf");
    sprite_istreams in(colors_in, masks_in);
    in >> pic;
    colors_in.close();
    masks_in.close();

    CPPUNIT_ASSERT_EQUAL(0, (int) pic.get_color(0, 0));
    CPPUNIT_ASSERT_EQUAL(1, (int) pic.get_color(1, 0));
    CPPUNIT_ASSERT_EQUAL(2, (int) pic.get_color(0, 1));
    CPPUNIT_ASSERT_EQUAL(3, (int) pic.get_color(1, 1));

    CPPUNIT_ASSERT_EQUAL(4, (int) pic.get_color(15, 0));
    CPPUNIT_ASSERT_EQUAL(5, (int) pic.get_color(14, 0));
    CPPUNIT_ASSERT_EQUAL(6, (int) pic.get_color(15, 1));
    CPPUNIT_ASSERT_EQUAL(7, (int) pic.get_color(14, 1));

    CPPUNIT_ASSERT_EQUAL(8, (int) pic.get_color(15, 15));
    CPPUNIT_ASSERT_EQUAL(9, (int) pic.get_color(14, 15));
    CPPUNIT_ASSERT_EQUAL(10, (int) pic.get_color(15, 14));
    CPPUNIT_ASSERT_EQUAL(11, (int) pic.get_color(14, 14));

    CPPUNIT_ASSERT_EQUAL(12, (int) pic.get_color(0, 15));
    CPPUNIT_ASSERT_EQUAL(13, (int) pic.get_color(1, 15));
    CPPUNIT_ASSERT_EQUAL(14, (int) pic.get_color(0, 14));
    CPPUNIT_ASSERT_EQUAL(15, (int) pic.get_color(1, 14));
}

void sprite_test::test_write()
{
    sprite pic;

    pic.set_color(0, 0, 0);
    pic.set_color(1, 0, 1);
    pic.set_color(0, 1, 2);
    pic.set_color(1, 1, 3);

    pic.set_color(15, 0, 4);
    pic.set_color(14, 0, 5);
    pic.set_color(15, 1, 6);
    pic.set_color(14, 1, 7);

    pic.set_color(15, 15, 8);
    pic.set_color(14, 15, 9);
    pic.set_color(15, 14, 10);
    pic.set_color(14, 14, 11);

    pic.set_color(0, 15, 12);
    pic.set_color(1, 15, 13);
    pic.set_color(0, 14, 14);
    pic.set_color(1, 14, 15);

    for (int y = 0; y != 16; y += 1)
        for (int x = 0; x != 16; x += 1)
            if ((y > 1 && y < 14) || (x > 1 && x < 14))
                pic.set_transparent(x, y);

    ostringstream colors_out;
    ostringstream masks_out;
    sprite_ostreams out(colors_out, masks_out);
    out << pic;
    string colors_data = colors_out.str();
    string masks_data = masks_out.str();

    ifstream colors_in1("data/ic0_9.wlf");
    ifstream masks_in1("data/masks.wlf");
    sprite_istreams in1(colors_in1, masks_in1);
    istringstream colors_in2(colors_data);
    istringstream masks_in2(masks_data);
    sprite_istreams in2(colors_in2, masks_in2);


    sprite a, b;
    in1 >> a;
    in2 >> b;

    CPPUNIT_ASSERT(a == b);
}

}
