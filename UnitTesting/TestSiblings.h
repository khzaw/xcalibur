#ifndef testSiblings_h
#define testSiblings_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class SiblingsTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( SiblingsTest ); // Note 3 

	CPPUNIT_TEST(testInsert);
	CPPUNIT_TEST(testGetStmtLstSiblingOfStmtLst);
	CPPUNIT_TEST(testGetStmtSiblingOfStmt);
	CPPUNIT_TEST(testGetVarSiblingOfConst);
	CPPUNIT_TEST(testGetConstSiblingOfVar);
	CPPUNIT_TEST(testGetVarSiblingOfVar);
	CPPUNIT_TEST(testGetConstSiblingOfConst);
	CPPUNIT_TEST(testGetVarSiblingOfStmtLst);
	CPPUNIT_TEST(testGetStmtLstSiblingOfVar);
	CPPUNIT_TEST(testGetAllStmtLstSiblingOfStmtLst);
	CPPUNIT_TEST(testGetAllStmtSiblingOfStmt);
	CPPUNIT_TEST(testGetAllVarSiblingOfConst);
	CPPUNIT_TEST(testGetAllConstSiblingOfVar);
	CPPUNIT_TEST(testGetAllVarSiblingOfVar);
	CPPUNIT_TEST(testGetAllConstSiblingOfConst);
	CPPUNIT_TEST(testGetAllVarSiblingOfStmtLst);
	CPPUNIT_TEST(testGetAllStmtLstSiblingOfVar);

	//boolean functions
	CPPUNIT_TEST(testIsSiblingVarVar);
	CPPUNIT_TEST(testIsSiblingStmtLstStmtLst);
	CPPUNIT_TEST(testIsSiblingStmtStmt);
	CPPUNIT_TEST(testIsSiblingVarStmtLst);
	CPPUNIT_TEST(testIsSiblingVarConst);
	CPPUNIT_TEST(testIsSiblingConstConst);
	

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	// method to test insertion into siblings Table
	void testInsert();
	void testGetStmtLstSiblingOfStmtLst();
	void testGetStmtSiblingOfStmt();
	void testGetVarSiblingOfConst();
	void testGetConstSiblingOfVar();
	void testGetVarSiblingOfVar();
	void testGetConstSiblingOfConst();
	void testGetVarSiblingOfStmtLst();
	void testGetStmtLstSiblingOfVar();
	void testGetAllStmtLstSiblingOfStmtLst();
	void testGetAllStmtSiblingOfStmt();
	void testGetAllVarSiblingOfConst();
	void testGetAllConstSiblingOfVar();
	void testGetAllVarSiblingOfVar();
	void testGetAllConstSiblingOfConst();
	void testGetAllVarSiblingOfStmtLst();
	void testGetAllStmtLstSiblingOfVar();

	//boolean functions
	void testIsSiblingVarVar();
	void testIsSiblingStmtLstStmtLst();
	void testIsSiblingStmtStmt();
	void testIsSiblingVarStmtLst();
	void testIsSiblingVarConst();;
	void testIsSiblingConstConst();
	

	
};
#endif