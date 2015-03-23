#ifndef TestOptimizedQE_h
#define TestOptimizedQE_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include <map>
#include "QueryProcessor\QE.h"
#include "QueryProcessor\OptimizedSubquerySolver.h"

class OptimizedQETest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( OptimizedQETest ); // Note 3 
	CPPUNIT_TEST(testQE);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testQE();
	void testMakeDisjointSet();
};
#endif
    