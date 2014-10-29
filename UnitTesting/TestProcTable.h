#ifndef TestProcTable_h
#define TestProcTable_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class ProcTableTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( ProcTableTest ); // Note 3 
	CPPUNIT_TEST(testInsert);
	CPPUNIT_TEST( testInsertAndRetrieveProceduresUsingIndex );
	CPPUNIT_TEST( testInsertAndRetrieveProceduresUsingProcName );
	CPPUNIT_TEST( testRetrieveProcTableSize );
	CPPUNIT_TEST( testIfContainsProcedure );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	// method to test assigning of duplicate procedures
	void testInsert();

	// method to test the assigning and retrieval of procedures
	void testInsertAndRetrieveProceduresUsingIndex ();
	void testInsertAndRetrieveProceduresUsingProcName ();

	// method to test the retrieval of proc table size
	void testRetrieveProcTableSize();

	// method to check if the proc table contains the specified procedure
	void testIfContainsProcedure();

};
#endif
    