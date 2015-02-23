#ifndef testCalls_h
#define testCalls_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class CallsTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( CallsTest ); // Note 3
	CPPUNIT_TEST(testInsertCalls);
	CPPUNIT_TEST(testGetCallerStar);
	CPPUNIT_TEST(testGetCalleeStar);
	CPPUNIT_TEST(testGetAllCallers);
	CPPUNIT_TEST(testGetAllCallees);
	CPPUNIT_TEST(testEvaluateGetCallees);
	CPPUNIT_TEST(testEvaluateGetCallers);
	CPPUNIT_TEST(testEvaluateGetCallersStar);
	CPPUNIT_TEST(testEvaluateGetCalleesStar);
	CPPUNIT_TEST(testIsCallsStar);
	CPPUNIT_TEST(testIsCalls);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	// method to test insertCalls
	void testInsertCalls();

	// method to test GetCallerStar and GetCalleeStar
	void testGetCallerStar();
	void testGetCalleeStar();


	// method to test GetAllCallers / GetAllCallees
	void testGetAllCallers();
	void testGetAllCallees();

	//method to test EvaluateGetCallees / EvaluateGetCallers
	void testEvaluateGetCallees();
	void testEvaluateGetCallers();

	//methods to testEvaluateGetCallerStar / EvaluateGetCalleeStar
	void testEvaluateGetCallersStar();
	void testEvaluateGetCalleesStar();

	// method to test testEvaluateIsCalls /testEvaluateIsCallsStar
	void testIsCalls();
	void testIsCallsStar();

};
#endif
    