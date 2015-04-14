#ifndef testContains_h
#define testContains_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class ContainsTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( ContainsTest ); // Note 3 
	CPPUNIT_TEST(testInsert);

	//tests for procedures as containers
	CPPUNIT_TEST(testGetStmtLstContainedStarInProc);
	CPPUNIT_TEST(testGetProcContainingStarStmtLst);
	CPPUNIT_TEST(testGetStmtContainedStarInProc);
	CPPUNIT_TEST(testGetProcContainingStarStmt);
	CPPUNIT_TEST(testGetVarContainedStarInProc);
	CPPUNIT_TEST(testGetProcsContainingStarVar);
	CPPUNIT_TEST(testGetConstContainedStarInProc);
	CPPUNIT_TEST(testGetProcContainingStarConst);
	
	//tests for statementsLists as containers
	CPPUNIT_TEST(testGetStmtContainedStarInStmtLst);
	CPPUNIT_TEST(testGetStmtLstContainingStarStmt);
	CPPUNIT_TEST(testGetVarContainedStarInStmtLst);
	CPPUNIT_TEST(testGetStmtLstContainingStarVar);
	CPPUNIT_TEST(testGetConstContainedStarInStmtLst);
	CPPUNIT_TEST(testGetStmtLstContainingStarConst);

	//statements as containers
	CPPUNIT_TEST(testGetVarContainedStarInStmt);
	CPPUNIT_TEST(testGetStmtContainingStarVar);
	CPPUNIT_TEST(testGetConstContainedStarInStmt);
	CPPUNIT_TEST(testGetStmtContainingStarConst);
	CPPUNIT_TEST(testGetStmtLstContainedStarInStmt);
	CPPUNIT_TEST(testGetStmtContainingStarStmtLst);

	//boolean functions
	CPPUNIT_TEST(testIsContainsStarProcStmtLst);
	CPPUNIT_TEST(testIsContainsStarProcStmt);
	CPPUNIT_TEST(testIsContainsStarProcVar);
	CPPUNIT_TEST(testIsContainsStarStmtLstStmt);
	CPPUNIT_TEST(testIsContainsStarStmtLstVar);
	CPPUNIT_TEST(testIsContainsStarStmtLstConst);
	CPPUNIT_TEST(testIsContainsStarStmtLstStmtLst);
	CPPUNIT_TEST(testIsContainsStarStmtVar) ;
	CPPUNIT_TEST(testIsContainsStarStmtConst);
	CPPUNIT_TEST(testIsContainsStarStmtStmtLst);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	// method to test insertion into contains table
	void testInsert();

	void testGetStmtLstContainedStarInProc();
	void testGetProcContainingStarStmtLst();
	void testGetStmtContainedStarInProc();
	void testGetProcContainingStarStmt();
	void testGetVarContainedStarInProc();
	void testGetProcsContainingStarVar();
	void testGetConstContainedStarInProc();
	void testGetProcContainingStarConst();

	void testGetStmtContainedStarInStmtLst();
	void testGetStmtLstContainingStarStmt();
	void testGetVarContainedStarInStmtLst();
	void testGetStmtLstContainingStarVar();
	void testGetConstContainedStarInStmtLst();
	void testGetStmtLstContainingStarConst();

	void testGetVarContainedStarInStmt();
	void testGetStmtContainingStarVar();
	void testGetConstContainedStarInStmt();
	void testGetStmtContainingStarConst();
	void testGetStmtLstContainedStarInStmt();
	void testGetStmtContainingStarStmtLst();

	void testIsContainsStarProcStmtLst();
	void testIsContainsStarProcStmt();
	void testIsContainsStarProcVar();
	void testIsContainsStarStmtLstStmt();
	void testIsContainsStarStmtLstVar();
	void testIsContainsStarStmtLstConst();
	void testIsContainsStarStmtLstStmtLst();
	void testIsContainsStarStmtVar(); 
	void testIsContainsStarStmtConst();
	void testIsContainsStarStmtStmtLst();

	
};
#endif