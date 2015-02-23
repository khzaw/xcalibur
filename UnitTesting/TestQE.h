#ifndef TestQE_h
#define TestQE_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class QueryEvaluatorTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( QueryEvaluatorTest ); // Note 3 
	//CPPUNIT_TEST(testUnion);
	CPPUNIT_TEST(testBQE);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	//void testUnion();
	void testBQE();

};
#endif