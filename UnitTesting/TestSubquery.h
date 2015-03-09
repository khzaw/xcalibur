#ifndef TestSubquery_h
#define TestSubquery_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include <map>
#include "PKB\PKBController.h"

class SubqueryTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( SubqueryTest ); // Note 3 
	CPPUNIT_TEST(testSubqueries);
	/*
	CPPUNIT_TEST(testParent);
	CPPUNIT_TEST(testFollowsT);
	CPPUNIT_TEST(testParentT);
	CPPUNIT_TEST(testModifies);
	CPPUNIT_TEST(testUses);
	CPPUNIT_TEST(testModifiesProc);
	CPPUNIT_TEST(testUsesProc);
	CPPUNIT_TEST(testCalls);
	CPPUNIT_TEST(testCallsT);
	CPPUNIT_TEST(testPattern);
	CPPUNIT_TEST(testWith);
	*/
	CPPUNIT_TEST_SUITE_END();

public:
	PKBController* pk;
	map<string, string> synonymTable;
	void setUp();
	void tearDown();

	void testSubqueries();
	void testFollows();
	void testParent();
	void testFollowsT();
	void testParentT();
	void testModifies();
	void testModifiesTuple();
	void testUses();
	void testModifiesProc();
	void testUsesProc();
	void testCalls();
	void testCallsTuple();
	void testCallsT();
	void testPattern();
	void testWith();
	void testWithTuple();
};
#endif