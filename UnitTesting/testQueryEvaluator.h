#ifndef testQueryEvaluator_h
#define testQueryEvaluator_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class QueryEvaluatorTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE(QueryEvaluatorTest ); // Note 3 
	CPPUNIT_TEST(testCheckSynonymInSuchThat);
	CPPUNIT_TEST(testSolveForSuchThatFollows);
	CPPUNIT_TEST(testSolveForSuchThatModifies);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testCheckSynonymInSuchThat();
	void testSolveForSuchThatFollows();
	void testSolveForSuchThatModifies();
};
#endif