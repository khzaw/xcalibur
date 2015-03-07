#ifndef TestSubquery_h
#define TestSubquery_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class SubqueryTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( SubqueryTest ); // Note 3 
	CPPUNIT_TEST(testFollows);
	//CPPUNIT_TEST(testParent);
	//CPPUNIT_TEST(testFollowsT);
	//CPPUNIT_TEST(testParentT);
	//CPPUNIT_TEST(testModifies);
	//CPPUNIT_TEST(testUses);
	//CPPUNIT_TEST(testModifiesProc);
	//CPPUNIT_TEST(testUsesProc);
	//CPPUNIT_TEST(testCalls);
	//CPPUNIT_TEST(testCallsT);
	//CPPUNIT_TEST(testPattern);
	//CPPUNIT_TEST(testWith);
	CPPUNIT_TEST_SUITE_END();

protected:
	PKBController pk;
	map<string, string> synonymTable;

public:
	void setUp();
	void tearDown();

	void testFollows();

};
#endif