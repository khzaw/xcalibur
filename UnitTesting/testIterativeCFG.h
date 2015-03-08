#ifndef testIterativeCFG_h
#define testIterativeCFG_h
#include <cppunit/extensions/HelperMacros.h>

class iterativeCFGTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(iterativeCFGTest);
	CPPUNIT_TEST(testNoLoops);
	CPPUNIT_TEST(testIfElseLoop);
	CPPUNIT_TEST(testWhileLoop);
	CPPUNIT_TEST(testIfIfLoop);
	CPPUNIT_TEST(testIfWhileLoop);
	CPPUNIT_TEST(testWhileIfLoop);
	CPPUNIT_TEST(testWhileWhileLoop);

	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();
	void testNoLoops();
	void testIfElseLoop();
	void testWhileLoop();
	void testIfIfLoop();
	void testIfWhileLoop();
	void testWhileIfLoop();
	void testWhileWhileLoop();

};
#endif