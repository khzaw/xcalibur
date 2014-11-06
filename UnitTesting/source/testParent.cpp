#include <cppunit/config/SourcePrefix.h>
#include "testParent.h"
#include "Parent.h"

#include <iostream>
#include <string>

void 
ParentTest::setUp()
{
}

void 
ParentTest::tearDown()
{
}	

CPPUNIT_TEST_SUITE_REGISTRATION( ParentTest );
// method to test insertion of procedures
void 

ParentTest::testInsert(){
	//inserting non duplicates procedures
	Parent f;
	f.insertParent(1,2);
	f.insertParent(2,3);
	f.insertParent(3,4);
	CPPUNIT_ASSERT(f.isParentTrue(1,2));
	CPPUNIT_ASSERT(f.isParentTrue(2,3));
	CPPUNIT_ASSERT(f.isParentTrue(3,4));
	//inserting duplicate procedures
	CPPUNIT_ASSERT_EQUAL(3,f.getSize());
	f.insertParent(2,3);
	//size of follows remains unchanged. duplicate is not inserted
	CPPUNIT_ASSERT_EQUAL(3,f.getSize());
	return;
}

// method to test getFollowers and getFollowees
void 
ParentTest::testGetChild(){
	Parent f;
	f.insertParent(1,2);
	f.insertParent(2,3);
	f.insertParent(3,4);
	vector<int> children = f.getChildren(1);
	CPPUNIT_ASSERT_EQUAL(2, children[0]);
	vector<int> children2 = f.getChildren(3);
	CPPUNIT_ASSERT_EQUAL(4, children2[0]);
	return;
}

void 
ParentTest::testGetParent(){
	Parent f;
	f.insertParent(1,2);
	f.insertParent(2,3);
	f.insertParent(3,4);
	vector<int> parent = f.getParents(3);
	CPPUNIT_ASSERT_EQUAL(2, parent [0]);
	vector<int> parent2 = f.getParents(4);
	CPPUNIT_ASSERT_EQUAL(3, parent2[0]);
	return;
}

// method to test getFollowersStar and getFolloweesStar
void 
ParentTest::testGetChildStar(){
	Parent f;
	f.insertParent(1,2);
	f.insertParent(2,3);
	f.insertParent(3,4);
	f.insertParent(4,5);
	vector<int> children = f.getChildrenStar(2);
	CPPUNIT_ASSERT_EQUAL(3, children[0]);
	CPPUNIT_ASSERT_EQUAL(4, children[1]);
	CPPUNIT_ASSERT_EQUAL(5, children[2]);

	return;
}

void
ParentTest::testGetParentStar(){
	Parent f;
	f.insertParent(1,2);
	f.insertParent(2,3);
	f.insertParent(3,4);
	f.insertParent(4,5);
	vector<int> parent = f.getParentStar(4);
    CPPUNIT_ASSERT_EQUAL(3,  parent[0]);
	CPPUNIT_ASSERT_EQUAL(2,  parent[1]);
	CPPUNIT_ASSERT_EQUAL(1,  parent[2]);

	return;
}


// method to test getAllFollower / getAllFollowee
void 
ParentTest::testGetAllChild(){
	Parent f;
	f.insertParent(1,2);
	f.insertParent(2,3);
	f.insertParent(3,4);
	f.insertParent(1,3);
	vector<int> children = f.getAllChildrenStmt();\
	int size = children.size();
	CPPUNIT_ASSERT(3, size);
	CPPUNIT_ASSERT_EQUAL(2,children[0]);
	CPPUNIT_ASSERT_EQUAL(3,children[1]);
	CPPUNIT_ASSERT_EQUAL(4,children[2]);

	return;
}

void
ParentTest::testGetAllParent(){
	Parent f;
	f.insertParent(1,2);
	f.insertParent(2,3);
	f.insertParent(3,4);
	f.insertParent(2,5);
	vector<int> parents = f.getAllParentStmt();
	CPPUNIT_ASSERT(parents.size() == 3);
	CPPUNIT_ASSERT_EQUAL(1,parents[0]);
	CPPUNIT_ASSERT_EQUAL(2,parents[1]);
	CPPUNIT_ASSERT_EQUAL(3,parents[2]);

	return;
}

