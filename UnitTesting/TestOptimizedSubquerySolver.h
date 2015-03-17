#ifndef TestOptimizedSubquerySolver_h
#define TestOptimizedSubquerySolver_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include <map>
#include "PKB\PKBController.h"
#include "QueryProcessor\OptimizedSubquerySolver.h"

class OptimizedSubquerySolverTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( OptimizedSubquerySolverTest ); // Note 3 
	CPPUNIT_TEST(testOSS);
	CPPUNIT_TEST_SUITE_END();

public:
	OptimizedSubquerySolver* oss;
	PKBController* pk;
	map<string, string> synonymTable;
	void setUp();
	void tearDown();

	void testOSS();
	void testSolveSet();
	void testMultithreadSolve();
	void compareTime();
};
#endif
    