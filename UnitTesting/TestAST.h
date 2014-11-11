#pragma once
#ifndef testAST_h
#define testAST_h
#include <cppunit/extensions/HelperMacros.h>

class TestAST : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(TestAST);
	CPPUNIT_TEST(testMatchPattern);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();
	void testMatchPattern();
};
#endif
