#ifndef TestFollowsSubquery_h
#define TestFollowsSubquery_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class FollowsSubqueryTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( FollowsSubqueryTest ); // Note 3 
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