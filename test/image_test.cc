/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <stdexcept>
#include <cppunit/TestAssert.h>
#include "image_test.h"
#include "../src/image.h"

namespace wasteland
{

CPPUNIT_TEST_SUITE_REGISTRATION(image_test);

void image_test::test_constructor()
{
    image img(2, 1);
    CPPUNIT_ASSERT_EQUAL(2, img.get_width());
    CPPUNIT_ASSERT_EQUAL(1, img.get_height());
    CPPUNIT_ASSERT_EQUAL(0, (int) img.get_color(0, 0));
    CPPUNIT_ASSERT_EQUAL(0, (int) img.get_color(1, 0));
    CPPUNIT_ASSERT_THROW(image img2(0, 1), std::invalid_argument);
    CPPUNIT_ASSERT_THROW(image img2(1, 0), std::invalid_argument);
}

void image_test::test_copy_constructor()
{
    image a(2, 1);
    a.set_color(0, 0, 7);
    image b(a);
    a.set_color(0, 0, 14);
    CPPUNIT_ASSERT_EQUAL(14, (int) a.get_color(0, 0));
    CPPUNIT_ASSERT_EQUAL(2, b.get_width());
    CPPUNIT_ASSERT_EQUAL(1, b.get_height());
    CPPUNIT_ASSERT_EQUAL(7, (int) b.get_color(0, 0));
}

void image_test::test_assignment_operator()
{
    image a(2, 1);
    a.set_color(0, 0, 7);
    image b(4, 2);
    b.set_color(0, 0, 14);
    b.set_color(1, 0, 11);
    b = a;
    a.set_color(0, 0, 1);
    a.set_color(0, 0, 2);
    CPPUNIT_ASSERT_EQUAL(2, b.get_width());
    CPPUNIT_ASSERT_EQUAL(1, b.get_height());
    CPPUNIT_ASSERT_EQUAL(7, (int) b.get_color(0, 0));
    CPPUNIT_ASSERT_EQUAL(0, (int) b.get_color(1, 0));

    image c(1, 1);
    c.set_color(0, 0, 7);
    image d(2, 2);
    d.set_color(0, 0, 14);
    d = c;
    CPPUNIT_ASSERT_EQUAL(1, d.get_width());
    CPPUNIT_ASSERT_EQUAL(1, d.get_height());
    CPPUNIT_ASSERT_EQUAL(7, (int) d.get_color(0, 0));
}

void image_test::test_get_width()
{
    image img(12, 34);
    CPPUNIT_ASSERT_EQUAL(12, img.get_width());
}

void image_test::test_get_height()
{
    image img(23, 45);
    CPPUNIT_ASSERT_EQUAL(45, img.get_height());
}

void image_test::test_get_set_color()
{
    image img(1, 2);
    img.set_color(0, 0, 0);
    img.set_color(0, 1, 5);
    img.set_color(-1, 0, 7);
    img.set_color(1, 0, 7);
    img.set_color(0, -1, 7);
    img.set_color(0, 2, 7);
    CPPUNIT_ASSERT_EQUAL(0, (int) img.get_color(0, 0));
    CPPUNIT_ASSERT_EQUAL(5, (int) img.get_color(0, 1));

    img.set_color(0, 0, 255);
    img.set_color(0, 1, 255);
    CPPUNIT_ASSERT_EQUAL(15, (int) img.get_color(0, 0));
    CPPUNIT_ASSERT_EQUAL(15, (int) img.get_color(0, 1));
}

}
