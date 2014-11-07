#ifndef TestQueryParser_h
#define TestQueryParser_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class QueryParserTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE(QueryParserTest); // Note 3 
	CPPUNIT_TEST(testSynonym);
	CPPUNIT_TEST(testSuchThat);
	CPPUNIT_TEST(testFollows);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testSynonym();
	void testSuchThat();
	void testFollows();

};
#endif
    