#ifndef TestVarTable_h
#define TestVarTable_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class VarTableTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( VarTableTest ); // Note 3 
	CPPUNIT_TEST(testInsert);
	CPPUNIT_TEST( testInsertAndRetrieveVarUsingIndex );
	CPPUNIT_TEST( testInsertAndRetrieveVarUsingVarName );
	CPPUNIT_TEST( testRetrieveVarTableSize );
	CPPUNIT_TEST( testIfContainsVar);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	// method to test assigning of duplicate variables
	void testInsert();

	// method to test the assigning and retrieval of variables
	void testInsertAndRetrieveVarUsingIndex ();
	void testInsertAndRetrieveVarUsingVarName ();

	// method to test the retrieval of var table size
	void testRetrieveVarTableSize();

	// method to test the checking of var table to see if it contains the specified variable
	void testIfContainsVar();

};
#endif
    