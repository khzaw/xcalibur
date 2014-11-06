#ifndef TestUses_h
#define TestUses_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class UsesTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( UsesTest ); // Note 3 
	CPPUNIT_TEST(testGetUsersStmt);
	CPPUNIT_TEST( testGetUsedVarStmt);
	CPPUNIT_TEST( testGetUsesStmt );
	CPPUNIT_TEST( testInsertUsesStmt);
	CPPUNIT_TEST( testIsUsesStmt);
	CPPUNIT_TEST(testGetUsersProc);
	CPPUNIT_TEST( testGetUsedVarProc);
	CPPUNIT_TEST( testGetUsesProc );
	CPPUNIT_TEST( testInsertUsesProc);
	CPPUNIT_TEST( testIsUsesProc);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();
	//statements

	//test get statements that modified var
	void testGetUsersStmt();
	//test get modified variables of statements
	void testGetUsedVarStmt();
	//test get modifies table of statement
    void testGetUsesStmt();
	//test insertion of modifies for statement
	void testInsertUsesStmt();
	//test if modifies for statement 
	void  testIsUsesStmt();
	//Procedure

	//test get statements that modified var
	void testGetUsersProc();
	//test get modified variables of statements
	void testGetUsedVarProc();
	//test get modifies table of statement
    void testGetUsesProc();
	//test insertion of modifies for statement
	void testInsertUsesProc();
	//test if modifies for statement 
	void  testIsUsesProc();

};
#endif
    