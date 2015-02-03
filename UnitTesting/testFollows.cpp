#include <cppunit/config/SourcePrefix.h>
#include "testFollows.h"
#include "Follows.h"
#include "FollowsExtractor.h"

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
	FollowsExtractor extractor(&f);
	extractor.construct();
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
	FollowsExtractor extractor(&f);
	extractor.construct();
	f.insertFollows(1,2);
	f.insertFollows(2,3);
	f.insertFollows(3,4);
	set<int> follower = f.getFollowers(1);
	std::set<int>::iterator itr = follower.begin();
	CPPUNIT_ASSERT_EQUAL(2, *itr);
	set<int> follower2 = f.getFollowers(3);
	itr = follower2.begin();
	CPPUNIT_ASSERT_EQUAL(4, *itr);
	return;
}

void 
FollowsTest::testGetFollowees(){
	Follows f;
	FollowsExtractor extractor(&f);
	extractor.construct();
	f.insertFollows(1,2);
	f.insertFollows(2,3);
	f.insertFollows(3,4);
	set<int> followee = f.getFollowees(3);
	std::set<int>::iterator itr = followee.begin();
	CPPUNIT_ASSERT_EQUAL(2, *itr);
	set<int> followee2 = f.getFollowees(4);
	itr = followee.begin();
	CPPUNIT_ASSERT_EQUAL(3, *itr);
	return;
}

// method to test getFollowersStar and getFolloweesStar
void 
FollowsTest::testGetFollowersStar(){
	
	Follows f;
	FollowsExtractor extractor(&f);
	extractor.construct();
	f.insertFollows(1,2);
	f.insertFollows(2,3);
	f.insertFollows(3,4);
	f.insertFollows(4,5);
	set<int> followers = f.getFollowersStar(2);
	std::set<int>::iterator itr = followers.begin();
	CPPUNIT_ASSERT_EQUAL(3,*itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(4, *itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(5, *itr);

	return;
}

void
FollowsTest::testGetFolloweesStar(){
	Follows f;
	FollowsExtractor extractor(&f);
	extractor.construct();
	f.insertFollows(1,2);
	f.insertFollows(2,3);
	f.insertFollows(3,4);
	f.insertFollows(4,5);
	set<int> followees = f.getFolloweesStar(4);
	std::set<int>::iterator itr = followees.begin();
	CPPUNIT_ASSERT_EQUAL(3, *itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(2, *itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(1, *itr);

	return;
}


// method to test getAllFollower / getAllFollowee
void 
FollowsTest::testGetAllFollower(){
	Follows f;
	FollowsExtractor extractor(&f);
	extractor.construct();
	f.insertFollows(1,2);
	f.insertFollows(2,3);
	f.insertFollows(3,4);
	f.insertFollows(1,3);
	set<int> followers = f.getAllFollowerStmt();
	int size = followers.size();
	CPPUNIT_ASSERT(3, size);
	std::set<int>::iterator itr = followers.begin();
	CPPUNIT_ASSERT_EQUAL(2,*itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(3,*itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(4,*itr);

	return;
}

void
FollowsTest::testGetAllFollowee(){
	Follows f;
	FollowsExtractor extractor(&f);
	extractor.construct();
	f.insertFollows(1,2);
	f.insertFollows(2,3);
	f.insertFollows(3,4);
	f.insertFollows(2,5);
	set<int> followees = f.getAllFolloweeStmt();
	std::set<int>::iterator itr = followees.begin();
	CPPUNIT_ASSERT(followees.size() == 3);
	CPPUNIT_ASSERT_EQUAL(1,*itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(2,*itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(3,*itr);
	itr++;

	return;
}

//test evaluateIsFollowsStar

void 
FollowsTest::testEvaluateIsFollowsStar(){
	Follows f;
	FollowsExtractor extractor(&f);
	extractor.construct();
	f.insertFollows(1,2);
	f.insertFollows(2,3);
	f.insertFollows(3,4);
	bool isFollowsStarTrue = false;
	isFollowsStarTrue = f.isFollowsStarTrue(1,4);
	CPPUNIT_ASSERT_EQUAL(true,isFollowsStarTrue);
	return;
}

//test evaluateIsFollows
void
FollowsTest::testEvaluateIsFollows(){
	Follows f;
	FollowsExtractor extractor(&f);
	extractor.construct();
	f.insertFollows(1,2);
	f.insertFollows(2,3);
	f.insertFollows(3,4);
	bool isFollowsTrue = false;
	isFollowsTrue = f.isFollowsTrue(1,4);
	CPPUNIT_ASSERT_EQUAL(true,isFollowsTrue);
	return;
}

//test evaluateGetFolloweeStar
void
FollowsTest::testEvaluateGetFolloweeStar(){
	Follows f;
	FollowsExtractor extractor(&f);
	extractor.construct();
	f.insertFollows(1,2);
	f.insertFollows(2,3);
	f.insertFollows(3,4);
	set<int> followeeStar = f.evaluateGetFolloweeStar(4);
	CPPUNIT_ASSERT(followeeStar.size()==3);
	std::set<int>::iterator itr = followeeStar.begin();
	CPPUNIT_ASSERT_EQUAL(1,*itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(2,*itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(3,*itr);
	itr++;

	return;
}

//test evaluateGetFollowerStar
void
FollowsTest::testEvaluateGetFollowerStar(){
	Follows f;
	FollowsExtractor extractor(&f);
	extractor.construct();
	f.insertFollows(1,2);
	f.insertFollows(2,3);
	f.insertFollows(3,4);
	set<int> followerStar = f.evaluateGetFollowerStar(1);
	CPPUNIT_ASSERT(followerStar.size()==3);
	std::set<int>::iterator itr = followerStar.begin();
	CPPUNIT_ASSERT_EQUAL(2,*itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(3,*itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(4,*itr);
	itr++;
	return;
}

//test evaluateGetFollowees
void
FollowsTest::testEvaluateGetFollowees(){
	Follows f;
	FollowsExtractor extractor(&f);
	extractor.construct();
	f.insertFollows(1,2);
	f.insertFollows(2,3);
	f.insertFollows(3,4);
	set<int> followees = f.evaluateGetFollowees(4);
	CPPUNIT_ASSERT(followees.size()==1);
	std::set<int>::iterator itr = followees.begin();
	CPPUNIT_ASSERT_EQUAL(3,*itr);
	followees = f.evaluateGetFollowees(2);
	itr = followees.begin();
	CPPUNIT_ASSERT_EQUAL(1,*itr);
	return;
}

//test evaluateGetFollowees
void
FollowsTest::testEvaluateGetFollowers(){
	Follows f;
	FollowsExtractor extractor(&f);
	extractor.construct();
	f.insertFollows(1,2);
	f.insertFollows(2,3);
	f.insertFollows(3,4);
	set<int> followers = f.evaluateGetFollowers(1);
	CPPUNIT_ASSERT(followers.size()==1);
	std::set<int>::iterator itr = followers.begin();
	CPPUNIT_ASSERT_EQUAL(2,*itr);
	followers = f.evaluateGetFollowers(2);
	itr = followers.begin();
	CPPUNIT_ASSERT_EQUAL(3,*itr);
	return;
}