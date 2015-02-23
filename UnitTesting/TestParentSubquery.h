#ifndef TestParentSubquery_h
#define TestParentSubquery_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class ParentSubqueryTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( ParentSubqueryTest ); // Note 3 
	CPPUNIT_TEST(testSolve);
	//CPPUNIT_TEST(testSolveWithTuple);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testSolve();
	void testSolveWithTuple();

};
#endif