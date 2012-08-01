/*
 * Copyright (C) 2012 Klaus Reimer <k@ailis.de>
 * See COPYING file for copying conditions
 */

#ifndef LIBWASTELAND_IMAGE_TEST_H
#define LIBWASTELAND_IMAGE_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace wasteland
{

class image_test: public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(image_test);
    CPPUNIT_TEST(test_constructor);
    CPPUNIT_TEST(test_copy_constructor);
    CPPUNIT_TEST(test_assignment_operator);
	CPPUNIT_TEST(test_get_width);
    CPPUNIT_TEST(test_get_height);
    CPPUNIT_TEST(test_get_set_color);
	CPPUNIT_TEST_SUITE_END();

protected:
    void test_constructor();
    void test_copy_constructor();
    void test_assignment_operator();
	void test_get_width();
	void test_get_height();
	void test_get_set_color();
};

}

#endif
