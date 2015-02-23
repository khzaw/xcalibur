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
	CPPUNIT_TEST(testEvaluateIsUsesStmt);
	CPPUNIT_TEST(testEvaluateIsUsesProc);
	CPPUNIT_TEST(testEvaluateGetUsersStmt);
	CPPUNIT_TEST(testEvaluateGetUsedVarStmt);
	CPPUNIT_TEST(testEvaluateGetUsersProc);
	CPPUNIT_TEST(testEvaluateGetUsedVarProc);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();
	//statements

	//test get statements that used var
	void testGetUsersStmt();
	//test get used variables of statements
	void testGetUsedVarStmt();
	//test get uses table of statement
    void testGetUsesStmt();
	//test insertion of uses for statement
	void testInsertUsesStmt();
	//test if uses for statement 
	void  testIsUsesStmt();
	//test if uses for statement 
	void  testEvaluateIsUsesStmt();
	//test get statements that used var
	void testEvaluateGetUsersStmt();
	//test get used variables of statements
	void testEvaluateGetUsedVarStmt();

	//Procedure

	//test get procedures that used var
	void testGetUsersProc();
	//test get used variables of procedures
	void testGetUsedVarProc();
	//test get uses table of procedures
    void testGetUsesProc();
	//test insertion of uses for procedures
	void testInsertUsesProc();
	//test if uses for procedures
	void  testIsUsesProc();
	//test if uses for procedures
	void  testEvaluateIsUsesProc();
	//test get procedures that used var
	void testEvaluateGetUsersProc();
	//test get used variables of procedures
	void testEvaluateGetUsedVarProc();
};
#endif
    