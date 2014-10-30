#ifndef TestModifies_h
#define TestModifies_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class ModifiesTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( ModifiesTest ); // Note 3 
	CPPUNIT_TEST(testGetModifiersStmt);
	CPPUNIT_TEST( testGetModifiedVarStmt);
	CPPUNIT_TEST( testGetModifiesStmt );
	CPPUNIT_TEST( testInsertModifiesStmt);
	CPPUNIT_TEST( testIsModifiesStmt);
	CPPUNIT_TEST(testGetModifiersProc);
	CPPUNIT_TEST( testGetModifiedVarProc);
	CPPUNIT_TEST( testGetModifiesProc );
	CPPUNIT_TEST( testInsertModifiesProc);
	CPPUNIT_TEST( testIsModifiesProc);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	//statements
	//test get statements that modified var
	void testGetModifiersStmt();
	//test get modified variables of statements
	void testGetModifiedVarStmt();
	//test get modifies table of statement
    void testGetModifiesStmt();
	//test insertion of modifies for statement
	void testInsertModifiesStmt();
	//test if modifies for statement 
	void testIsModifiesStmt();

	//Procedure
	//test get procedures that modified var
	void testGetModifiersProc();
	//test get modified variables of procedures
	void testGetModifiedVarProc();
	//test get modifies table of procedures
    void testGetModifiesProc();
	//test insertion of modifies for procedures
	void testInsertModifiesProc();
	//test if modifies for procedures 
	void testIsModifiesProc();

};
#endif
    