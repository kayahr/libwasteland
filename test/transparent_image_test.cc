/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#include <stdexcept>
#include <cppunit/TestAssert.h>
#include "transparent_image_test.h"
#include "../src/transparent_image.h"

namespace wasteland
{

CPPUNIT_TEST_SUITE_REGISTRATION(transparent_image_test);

void transparent_image_test::test_constructor()
{
    transparent_image img(2, 1);
    CPPUNIT_ASSERT_EQUAL(2, img.get_width());
    CPPUNIT_ASSERT_EQUAL(1, img.get_height());
    CPPUNIT_ASSERT_EQUAL(0, (int) img.get_color(0, 0));
    CPPUNIT_ASSERT_EQUAL(0, (int) img.get_color(1, 0));
    CPPUNIT_ASSERT_EQUAL(false, img.is_transparent(0, 0));
    CPPUNIT_ASSERT_EQUAL(false, img.is_transparent(1, 0));
    CPPUNIT_ASSERT_THROW(transparent_image img2(-1, 1), std::invalid_argument);
    CPPUNIT_ASSERT_THROW(transparent_image img2(1, 0), std::invalid_argument);
}

void transparent_image_test::test_copy_constructor()
{
    transparent_image a(2, 1);
    a.set_color(0, 0, 7);
    a.set_transparent(0, 0, true);
    transparent_image b(a);
    a.set_transparent(0, 0, false);
    a.set_color(0, 0, 14);
    CPPUNIT_ASSERT_EQUAL(14, (int) a.get_color(0, 0));
    CPPUNIT_ASSERT_EQUAL(false, a.is_transparent(0, 0));
    CPPUNIT_ASSERT_EQUAL(2, b.get_width());
    CPPUNIT_ASSERT_EQUAL(1, b.get_height());
    CPPUNIT_ASSERT_EQUAL(7, (int) b.get_color(0, 0));
    CPPUNIT_ASSERT_EQUAL(true, b.is_transparent(0, 0));
}

void transparent_image_test::test_assignment_operator()
{
    transparent_image a(2, 1);
    a.set_color(0, 0, 7);
    a.set_transparent(0, 0, true);
    transparent_image b(4, 2);
    b.set_color(0, 0, 14);
    b.set_color(1, 0, 11);
    b.set_transparent(0, 0, false);
    b.set_transparent(1, 0, true);
    b = a;
    CPPUNIT_ASSERT_EQUAL(2, b.get_width());
    CPPUNIT_ASSERT_EQUAL(1, b.get_height());
    CPPUNIT_ASSERT_EQUAL(7, (int) b.get_color(0, 0));
    CPPUNIT_ASSERT_EQUAL(0, (int) b.get_color(1, 0));
    CPPUNIT_ASSERT_EQUAL(true, b.is_transparent(0, 0));
    CPPUNIT_ASSERT_EQUAL(false, b.is_transparent(1, 0));
}

void transparent_image_test::test_get_width()
{
    transparent_image img(12, 34);
    CPPUNIT_ASSERT_EQUAL(12, img.get_width());
}

void transparent_image_test::test_get_height()
{
    transparent_image img(23, 45);
    CPPUNIT_ASSERT_EQUAL(45, img.get_height());
}

void transparent_image_test::test_get_set_color()
{
    transparent_image img(2, 2);
    img.set_color(0, 0, 0);
    img.set_color(0, 1, 5);
    img.set_color(1, 0, 10);
    img.set_color(1, 1, 15);
    img.set_color(-1, 1, 7);
    img.set_color(1, -1, 7);
    img.set_color(2, 1, 7);
    img.set_color(1, 2, 7);
    CPPUNIT_ASSERT_EQUAL(0, (int) img.get_color(0, 0));
    CPPUNIT_ASSERT_EQUAL(5, (int) img.get_color(0, 1));
    CPPUNIT_ASSERT_EQUAL(10, (int) img.get_color(1, 0));
    CPPUNIT_ASSERT_EQUAL(15, (int) img.get_color(1, 1));

    img.set_color(0, 0, 255);
    img.set_color(1, 0, 255);
    CPPUNIT_ASSERT_EQUAL(15, (int) img.get_color(0, 0));
    CPPUNIT_ASSERT_EQUAL(15, (int) img.get_color(1, 0));
}

void transparent_image_test::test_get_set_transparent()
{
    transparent_image img(1, 2);
    img.set_transparent(0, 0, true);
    img.set_transparent(0, 1, false);
    img.set_transparent(-1, 0, true);
    img.set_transparent(1, 0, true);
    img.set_transparent(0, -1, true);
    img.set_transparent(0, 2, true);
    CPPUNIT_ASSERT_EQUAL(true, img.is_transparent(0, 0));
    CPPUNIT_ASSERT_EQUAL(false, img.is_transparent(0, 1));
}

}
