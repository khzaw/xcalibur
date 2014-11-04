#ifndef testParent_h
#define testParent_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class ParentTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( ParentTest ); // Note 3 
	CPPUNIT_TEST(testInsert);
	CPPUNIT_TEST( testGetChild);
	CPPUNIT_TEST( testGetParent );
	CPPUNIT_TEST( testGetChildStar );
	CPPUNIT_TEST( testGetParentStar );
	CPPUNIT_TEST( testGetAllChild );
	CPPUNIT_TEST( testGetAllParent);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	// method to test assigning of duplicate follows and isFollowsTrue
	void testInsert();

	// method to test getChild and getParent
	void testGetChild();
	void testGetParent();

	// method to test getChildStar and getParentStar
	void testGetChildStar();
	void testGetParentStar();


	// method to test getAllParent / getAllChild statements
	void testGetAllChild();
	void testGetAllParent();

};
#endif
    