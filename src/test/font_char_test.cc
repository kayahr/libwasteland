/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>
#include <cppunit/TestAssert.h>
#include "font_char_test.h"
#include <wasteland/font_char.h>

using std::string;
using std::ifstream;
using std::ostringstream;
using std::istringstream;

namespace wasteland
{

CPPUNIT_TEST_SUITE_REGISTRATION(font_char_test);

void font_char_test::test_constructor()
{
    font_char pic;
    CPPUNIT_ASSERT_EQUAL(8, (int) pic.get_width());
    CPPUNIT_ASSERT_EQUAL(8, (int) pic.get_height());
    for (int y = 0; y < 8; y += 1)
    {
        for (int x = 0; x < 8; x += 1)
        {
            CPPUNIT_ASSERT_EQUAL(0, (int) pic.get_color(x, y));
        }
    }
}

void font_char_test::test_copy_constructor()
{
    font_char a;
    a.set_color(0, 0, 7);
    font_char b(a);
    a.set_color(0, 0, 14);
    CPPUNIT_ASSERT_EQUAL(14, (int) a.get_color(0, 0));
    CPPUNIT_ASSERT_EQUAL(7, (int) b.get_color(0, 0));
}

void font_char_test::test_assignment_operator()
{
    font_char a;
    a.set_color(0, 0, 7);
    font_char b;
    b.set_color(0, 0, 14);
    b.set_color(1, 0, 11);
    b = a;
    a.set_color(0, 0, 1);
    a.set_color(0, 0, 2);
    CPPUNIT_ASSERT_EQUAL(7, (int) b.get_color(0, 0));
    CPPUNIT_ASSERT_EQUAL(0, (int) b.get_color(1, 0));
}

void font_char_test::test_get_width()
{
    font_char img;
    CPPUNIT_ASSERT_EQUAL(8, (int) img.get_width());
}

void font_char_test::test_get_height()
{
    font_char img;
    CPPUNIT_ASSERT_EQUAL(8, (int) img.get_height());
}

void font_char_test::test_get_set_color()
{
    font_char img;
    img.set_color(0, 0, 0);
    img.set_color(0, 1, 5);
    img.set_color(-1, 0, 7);
    img.set_color(8, 0, 7);
    img.set_color(0, -1, 7);
    img.set_color(0, 8, 7);
    CPPUNIT_ASSERT_EQUAL(0, (int) img.get_color(0, 0));
    CPPUNIT_ASSERT_EQUAL(5, (int) img.get_color(0, 1));

    img.set_color(0, 0, 255);
    img.set_color(0, 1, 255);
    CPPUNIT_ASSERT_EQUAL(15, (int) img.get_color(0, 0));
    CPPUNIT_ASSERT_EQUAL(15, (int) img.get_color(0, 1));
}

void font_char_test::test_equals()
{
    font_char a, b;

    CPPUNIT_ASSERT(a == b);

    a.set_color(0, 0, 1);
    CPPUNIT_ASSERT(a != b);

    b.set_color(0, 0, 1);
    CPPUNIT_ASSERT(a == b);

    a.set_color(7, 7, 8);
    CPPUNIT_ASSERT(a != b);
}

void font_char_test::test_read()
{
    font_char pic;

    ifstream in("data/colorf.fnt");
    in >> pic;
    in.close();

    CPPUNIT_ASSERT_EQUAL(0, (int) pic.get_color(0, 0));
    CPPUNIT_ASSERT_EQUAL(1, (int) pic.get_color(1, 0));
    CPPUNIT_ASSERT_EQUAL(2, (int) pic.get_color(0, 1));
    CPPUNIT_ASSERT_EQUAL(3, (int) pic.get_color(1, 1));

    CPPUNIT_ASSERT_EQUAL(4, (int) pic.get_color(7, 0));
    CPPUNIT_ASSERT_EQUAL(5, (int) pic.get_color(6, 0));
    CPPUNIT_ASSERT_EQUAL(6, (int) pic.get_color(7, 1));
    CPPUNIT_ASSERT_EQUAL(7, (int) pic.get_color(6, 1));

    CPPUNIT_ASSERT_EQUAL(8, (int) pic.get_color(7, 7));
    CPPUNIT_ASSERT_EQUAL(9, (int) pic.get_color(6, 7));
    CPPUNIT_ASSERT_EQUAL(10, (int) pic.get_color(7, 6));
    CPPUNIT_ASSERT_EQUAL(11, (int) pic.get_color(6, 6));

    CPPUNIT_ASSERT_EQUAL(12, (int) pic.get_color(0, 7));
    CPPUNIT_ASSERT_EQUAL(13, (int) pic.get_color(1, 7));
    CPPUNIT_ASSERT_EQUAL(14, (int) pic.get_color(0, 6));
    CPPUNIT_ASSERT_EQUAL(15, (int) pic.get_color(1, 6));
}

void font_char_test::test_write()
{
    font_char pic;

    pic.set_color(0, 0, 0);
    pic.set_color(1, 0, 1);
    pic.set_color(0, 1, 2);
    pic.set_color(1, 1, 3);

    pic.set_color(7, 0, 4);
    pic.set_color(6, 0, 5);
    pic.set_color(7, 1, 6);
    pic.set_color(6, 1, 7);

    pic.set_color(7, 7, 8);
    pic.set_color(6, 7, 9);
    pic.set_color(7, 6, 10);
    pic.set_color(6, 6, 11);

    pic.set_color(0, 7, 12);
    pic.set_color(1, 7, 13);
    pic.set_color(0, 6, 14);
    pic.set_color(1, 6, 15);

    ostringstream out;
    out << pic;
    string data = out.str();

    ifstream in1("data/colorf.fnt");
    istringstream in2(data);

    font_char a, b;
    in1 >> a;
    in2 >> b;

    CPPUNIT_ASSERT(a == b);
}

}
