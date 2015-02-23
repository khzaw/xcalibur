#include <cppunit/config/SourcePrefix.h>
#include "testFollows.h"
#include "PKB\Follows.h"

#include <iostream>
#include <string>

void 
FollowsTest::setUp()
{
}

void 
FollowsTest::tearDown()
{
}	

CPPUNIT_TEST_SUITE_REGISTRATION( FollowsTest );
// method to test insertion of Follows


void 
FollowsTest::testInsert(){
	

	//inserting non duplicates follows
	Follows f;
	f.insertFollows(1,2);
	f.insertFollows(2,3);
	f.insertFollows(3,4);
	CPPUNIT_ASSERT(f.isFollowsTrue(1,2));
	CPPUNIT_ASSERT(f.isFollowsTrue(2,3));
	CPPUNIT_ASSERT(f.isFollowsTrue(3,4));
	//inserting duplicate follows
	CPPUNIT_ASSERT_EQUAL(3,f.getSize());
	f.insertFollows(2,3);
	//size of follows remains unchanged. duplicate is not inserted
	CPPUNIT_ASSERT_EQUAL(3,f.getSize());
	return;
}

// method to test getFollowers and getFollowees
void 
FollowsTest::testGetFollowers(){
	
	Follows f;
	f.insertFollows(1,2);
	f.insertFollows(2,3);
	f.insertFollows(3,4);
	vector<int> follower = f.getFollowers(1);
	CPPUNIT_ASSERT_EQUAL(2, follower[0]);
	vector<int> follower2 = f.getFollowers(3);
	CPPUNIT_ASSERT_EQUAL(4, follower2[0]);
	return;
}

void 
FollowsTest::testGetFollowees(){
	Follows f;
	f.insertFollows(1,2);
	f.insertFollows(2,3);
	f.insertFollows(3,4);
	vector<int> followee = f.getFollowees(3);
	CPPUNIT_ASSERT_EQUAL(2, followee[0]);
	vector<int> followee2 = f.getFollowees(4);
	CPPUNIT_ASSERT_EQUAL(3, followee2[0]);
	return;
}

// method to test getFollowersStar and getFolloweesStar
void 
FollowsTest::testGetFollowersStar(){
	
	Follows f;
	f.insertFollows(1,2);
	f.insertFollows(2,3);
	f.insertFollows(3,4);
	f.insertFollows(4,5);
	vector<int> followers = f.getFollowersStar(2);
	CPPUNIT_ASSERT_EQUAL(3, followers[0]);
	CPPUNIT_ASSERT_EQUAL(4, followers[1]);
	CPPUNIT_ASSERT_EQUAL(5, followers[2]);

	return;
}

void
FollowsTest::testGetFolloweesStar(){
	Follows f;
	f.insertFollows(1,2);
	f.insertFollows(2,3);
	f.insertFollows(3,4);
	f.insertFollows(4,5);
	vector<int> followees = f.getFolloweesStar(4);
    CPPUNIT_ASSERT_EQUAL(3, followees[0]);
	CPPUNIT_ASSERT_EQUAL(2, followees[1]);
	CPPUNIT_ASSERT_EQUAL(1, followees[2]);

	return;
}


// method to test getAllFollower / getAllFollowee
void 
FollowsTest::testGetAllFollower(){
	Follows f;
	f.insertFollows(1,2);
	f.insertFollows(2,3);
	f.insertFollows(3,4);
	f.insertFollows(1,3);
	vector<int> followers = f.getAllFollowerStmt();
	int size = followers.size();
	CPPUNIT_ASSERT_EQUAL(3, size);
	CPPUNIT_ASSERT_EQUAL(2,followers[0]);
	CPPUNIT_ASSERT_EQUAL(3,followers[1]);
	CPPUNIT_ASSERT_EQUAL(4,followers[2]);

	return;
}

void
FollowsTest::testGetAllFollowee(){
	Follows f;
	f.insertFollows(1,2);
	f.insertFollows(2,3);
	f.insertFollows(3,4);
	f.insertFollows(2,5);
	vector<int> followees = f.getAllFolloweeStmt();
	CPPUNIT_ASSERT(followees.size() == 3);
	CPPUNIT_ASSERT_EQUAL(1,followees[0]);
	CPPUNIT_ASSERT_EQUAL(2,followees[1]);
	CPPUNIT_ASSERT_EQUAL(3,followees[2]);

	return;
}

