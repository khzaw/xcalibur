#ifndef TestQueryParser_h
#define TestQueryParser_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class QueryParserTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE(QueryParserTest); // Note 3 
	CPPUNIT_TEST(testSynonym);
	CPPUNIT_TEST(testSuchThat);
	CPPUNIT_TEST(testModifies);
	CPPUNIT_TEST(testUses);
	CPPUNIT_TEST(testCalls);
	CPPUNIT_TEST(testParent);
	CPPUNIT_TEST(testFollows);
	CPPUNIT_TEST(testAssignPattern);
	CPPUNIT_TEST(testMoreAssignPatterns);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testSynonym();
	void testSuchThat();
	void testModifies();
	void testUses();
	void testCalls();
	void testParent();
	void testFollows();
	void testAssignPattern();
	void testMoreAssignPatterns();

};
#endif

// Ent : syn, _, "IDENT", INT
// var : syn, _, "IDENT"
// stmt: syn, _, INT
    