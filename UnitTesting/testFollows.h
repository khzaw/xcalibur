#ifndef testFollows_h
#define testFollows_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class FollowsTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( FollowsTest ); // Note 3 
	CPPUNIT_TEST(testInsert);
	CPPUNIT_TEST( testGetFollowers);
	CPPUNIT_TEST( testGetFollowees );
	CPPUNIT_TEST( testGetFollowersStar );
	CPPUNIT_TEST( testGetFolloweesStar );
	CPPUNIT_TEST( testGetAllFollower );
	CPPUNIT_TEST( testGetAllFollowee);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	// method to test assigning of duplicate follows and isFollowsTrue
	void testInsert();

	// method to test getFollowers and getFollowees
	void testGetFollowers();
	void testGetFollowees();

	// method to test getFollowersStar and getFolloweesStar
	void testGetFollowersStar();
	void testGetFolloweesStar();


	// method to test getAllFollower / getAllFollowee
	void testGetAllFollower();
	void testGetAllFollowee();

};
#endif
    