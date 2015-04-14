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
	void testFollowsTuple();
	void testParent();
	void testParentTuple();
	void testFollowsT();
	void testFollowsTTuple();
	void testParentT();
	void testParentTTuple();
	void testModifies();
	void testModifiesTuple();
	void testUses();
	void testUsesTuple();
	void testModifiesProc();
	void testModifiesProcTuple();
	void testUsesProc();
	void testUsesProcTuple();
	void testCalls();
	void testCallsTuple();
	void testCallsT();
	void testCallsTTuple();
	void testPattern();
	void testPatternTuple();
	void testWith();
	void testWithTuple();
	void testNext();
  void testOptimizedNext();
	void testNextTuple();
	void testNextStar();
  void testOptimizedNextStar();
	void testNextStarTuple();
	void testAffects();
  void testOptimizedAffects();
	void testAffectsTuple();
	void testAffectsStar();
	void testAffectsStarTuple();
};
#endif