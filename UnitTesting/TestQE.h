#ifndef TestQE_h
#define TestQE_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include <map>
#include "PKB\PKBController.h"
#include "QueryProcessor\QE.h"

class QueryEvaluatorTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( QueryEvaluatorTest ); // Note 3 
	//CPPUNIT_TEST(testUnion);
	CPPUNIT_TEST(testQE);
	//CPPUNIT_TEST(testBQE);
	CPPUNIT_TEST_SUITE_END();

public:
	QE* qe;
	PKBController* pk;
	map<string, string> synonymTable;
	void setUp();
	void tearDown();
	
	//void testUnion();
	//void testBQE();
	void testQE();
	void testInsert();
	void testValidate();
	void testConvertString();
};
#endif