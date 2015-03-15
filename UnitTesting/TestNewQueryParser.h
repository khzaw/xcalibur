#ifndef TestNewQueryParser_h
#define TestNewQueryParser_h

#include <cppunit/extensions/HelperMacros.h>

class NewQueryParserTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(NewQueryParserTest);
	CPPUNIT_TEST(testModifiesSubquery);

public: 
	void setUp();
	void tearDown();

	void testModifiesSubquery();

};
#endif