#pragma once
#ifndef testParser_h
#define testParser_h
#include <cppunit/extensions/HelperMacros.h>

class TestParser : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(TestParser);
	CPPUNIT_TEST(testTotalLinesOfStatement);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();
	void testTotalLinesOfStatement();
};
#endif