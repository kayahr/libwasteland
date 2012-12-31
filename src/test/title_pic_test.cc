/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>
#include <cppunit/TestAssert.h>
#include "title_pic_test.h"
#include <wasteland/title_pic.h>

using std::string;
using std::ifstream;
using std::ostringstream;
using std::istringstream;

namespace wasteland
{

CPPUNIT_TEST_SUITE_REGISTRATION(title_pic_test);

void title_pic_test::test_constructor()
{
    title_pic pic;
    CPPUNIT_ASSERT_EQUAL(288, (int) pic.get_width());
    CPPUNIT_ASSERT_EQUAL(128, (int) pic.get_height());
    for (int y = 0; y < 128; y += 1)
    {
        for (int x = 0; x < 288; x += 1)
        {
            CPPUNIT_ASSERT_EQUAL(0, (int) pic.get_color(x, y));
        }
    }
}

void title_pic_test::test_copy_constructor()
{
    title_pic a;
    a.set_color(0, 0, 7);
    title_pic b(a);
    a.set_color(0, 0, 14);
    CPPUNIT_ASSERT_EQUAL(14, (int) a.get_color(0, 0));
    CPPUNIT_ASSERT_EQUAL(7, (int) b.get_color(0, 0));
}

void title_pic_test::test_assignment_operator()
{
    title_pic a;
    a.set_color(0, 0, 7);
    title_pic b;
    b.set_color(0, 0, 14);
    b.set_color(1, 0, 11);
    b = a;
    a.set_color(0, 0, 1);
    a.set_color(0, 0, 2);
    CPPUNIT_ASSERT_EQUAL(7, (int) b.get_color(0, 0));
    CPPUNIT_ASSERT_EQUAL(0, (int) b.get_color(1, 0));
}

void title_pic_test::test_get_width()
{
    title_pic img;
    CPPUNIT_ASSERT_EQUAL(288, (int) img.get_width());
}

void title_pic_test::test_get_height()
{
    title_pic img;
    CPPUNIT_ASSERT_EQUAL(128, (int) img.get_height());
}

void title_pic_test::test_get_set_color()
{
    title_pic img;
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

void title_pic_test::test_equals()
{
    title_pic a, b;

    CPPUNIT_ASSERT(a == b);

    a.set_color(0, 0, 1);
    CPPUNIT_ASSERT(a != b);

    b.set_color(0, 0, 1);
    CPPUNIT_ASSERT(a == b);

    a.set_color(287, 127, 8);
    CPPUNIT_ASSERT(a != b);
}

void title_pic_test::test_read()
{
    title_pic pic;

    ifstream in("data/title.pic");
    in >> pic;
    in.close();

    CPPUNIT_ASSERT_EQUAL(0, (int) pic.get_color(0, 0));
    CPPUNIT_ASSERT_EQUAL(1, (int) pic.get_color(1, 0));
    CPPUNIT_ASSERT_EQUAL(2, (int) pic.get_color(0, 1));
    CPPUNIT_ASSERT_EQUAL(3, (int) pic.get_color(1, 1));

    CPPUNIT_ASSERT_EQUAL(4, (int) pic.get_color(287, 0));
    CPPUNIT_ASSERT_EQUAL(5, (int) pic.get_color(286, 0));
    CPPUNIT_ASSERT_EQUAL(6, (int) pic.get_color(287, 1));
    CPPUNIT_ASSERT_EQUAL(7, (int) pic.get_color(286, 1));

    CPPUNIT_ASSERT_EQUAL(8, (int) pic.get_color(287, 127));
    CPPUNIT_ASSERT_EQUAL(9, (int) pic.get_color(286, 127));
    CPPUNIT_ASSERT_EQUAL(10, (int) pic.get_color(287, 126));
    CPPUNIT_ASSERT_EQUAL(11, (int) pic.get_color(286, 126));

    CPPUNIT_ASSERT_EQUAL(12, (int) pic.get_color(0, 127));
    CPPUNIT_ASSERT_EQUAL(13, (int) pic.get_color(1, 127));
    CPPUNIT_ASSERT_EQUAL(14, (int) pic.get_color(0, 126));
    CPPUNIT_ASSERT_EQUAL(15, (int) pic.get_color(1, 126));
}

void title_pic_test::test_write()
{
    title_pic pic;

    pic.set_color(0, 0, 0);
    pic.set_color(1, 0, 1);
    pic.set_color(0, 1, 2);
    pic.set_color(1, 1, 3);

    pic.set_color(287, 0, 4);
    pic.set_color(286, 0, 5);
    pic.set_color(287, 1, 6);
    pic.set_color(286, 1, 7);

    pic.set_color(287, 127, 8);
    pic.set_color(286, 127, 9);
    pic.set_color(287, 126, 10);
    pic.set_color(286, 126, 11);

    pic.set_color(0, 127, 12);
    pic.set_color(1, 127, 13);
    pic.set_color(0, 126, 14);
    pic.set_color(1, 126, 15);

    ostringstream out;
    out << pic;
    string data = out.str();

    ifstream in1("data/title.pic");
    istringstream in2(data);

    title_pic a, b;
    in1 >> a;
    in2 >> b;

    CPPUNIT_ASSERT(a == b);
}

}
