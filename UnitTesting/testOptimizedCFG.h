#ifndef testOptimizedCFG_h
#define testOptimizedCFG_h
#include <cppunit/extensions/HelperMacros.h>
#include "..\SPA\PKB\PKBController.h"

class OptimizedCFGTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(OptimizedCFGTest);
	//CPPUNIT_TEST(testNoLoops);
	//CPPUNIT_TEST(testIfElseLoop);
	//CPPUNIT_TEST(testWhileLoop);
	//CPPUNIT_TEST(testIfIfLoop);
	//CPPUNIT_TEST(testIfWhileLoop);
	//CPPUNIT_TEST(testWhileIfLoop);
	//CPPUNIT_TEST(testWhileWhileLoop);
	
  CPPUNIT_TEST(testSourceProgram);
	CPPUNIT_TEST_SUITE_END();

public:
  PKBController* pk;
	map<string, string> synonymTable;
	void setUp();
	void tearDown();
	void testSourceProgram();

};
#endif