#include <cppunit/config/SourcePrefix.h>
#include "testParent.h"
#include "Parent.h"
#include "ParentExtractor.h"

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
	ParentExtractor extractor(&f);
	extractor.construct();
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
	ParentExtractor extractor(&f);
	extractor.construct();
	set<int> children = f.getChildren(1);
	std::set<int>::iterator itr = children.begin();
	CPPUNIT_ASSERT_EQUAL(2, *itr);
	set<int> children2 = f.getChildren(3);
	itr = children2.begin();
	CPPUNIT_ASSERT_EQUAL(4, *itr);
	return;
}

void 
ParentTest::testGetParent(){
	Parent f;
	f.insertParent(1,2);
	f.insertParent(2,3);
	f.insertParent(3,4);
	ParentExtractor extractor(&f);
	extractor.construct();
	set<int> parent = f.getParents(3);
	std::set<int>::iterator itr = parent.begin();
	CPPUNIT_ASSERT_EQUAL(2, *itr);
	itr++;
	set<int> parent2 = f.getParents(4);
	itr = parent2.begin();
	CPPUNIT_ASSERT_EQUAL(3, *itr);
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
	ParentExtractor extractor(&f);
	extractor.construct();
	set<int> children = f.getChildrenStar(2);
	std::set<int>::iterator itr = children.begin();
	CPPUNIT_ASSERT_EQUAL(3, *itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(4, *itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(5, *itr);

	return;
}

void
ParentTest::testGetParentStar(){
	Parent f;
	f.insertParent(1,2);
	f.insertParent(2,3);
	f.insertParent(3,4);
	f.insertParent(4,5);
	ParentExtractor extractor(&f);
	extractor.construct();
	set<int> parent = f.getParentStar(4);
	std::set<int>::iterator itr = parent.begin();
    CPPUNIT_ASSERT_EQUAL(3,  *itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(2,  *itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(1,  *itr);

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
	ParentExtractor extractor(&f);
	extractor.construct();
	set<int> children = f.getAllChildrenStmt();\
	int size = children.size();
	std::set<int>::iterator itr = children.begin();
	CPPUNIT_ASSERT(3, size);
	CPPUNIT_ASSERT_EQUAL(2,*itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(3,*itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(4,*itr);

	return;
}

void
ParentTest::testGetAllParent(){
	Parent f;
	f.insertParent(1,2);
	f.insertParent(2,3);
	f.insertParent(3,4);
	f.insertParent(2,5);
	ParentExtractor extractor(&f);
	extractor.construct();
	set<int> parents = f.getAllParentStmt();
	std::set<int>::iterator itr = parents.begin();
	CPPUNIT_ASSERT(parents.size() == 3);
	CPPUNIT_ASSERT_EQUAL(1,*itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(2,*itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(3,*itr);

	return;
}

//test the function testEvaluateIsParentStar
void 
ParentTest::testEvaluateIsParentStar(){
	Parent f;
	f.insertParent(1,2);
	f.insertParent(2,3);
	f.insertParent(3,4);
	f.insertParent(2,5);
	ParentExtractor extractor(&f);
	extractor.construct();
	bool ans = f.evaluateIsParentStar(1,3);
	CPPUNIT_ASSERT(ans==true);
	ans = f.evaluateIsParentStar(3,5);
	CPPUNIT_ASSERT(ans==false);
	return;
}

//test the function testEvaluateIsParent
void
ParentTest::testEvaluateIsParent(){
	Parent f;
	f.insertParent(1,2);
	f.insertParent(2,3);
	f.insertParent(3,4);
	f.insertParent(2,5);
	ParentExtractor extractor(&f);
	extractor.construct();
	bool ans = f.evaluateIsParent(1,2);
	CPPUNIT_ASSERT(ans==true);
	ans = f.evaluateIsParent(3,4);
	CPPUNIT_ASSERT(ans==true);
	return;
}

//test the function testEvaluateGetParentStar
void
ParentTest::testEvaluateGetParentStar(){
	Parent f;
	f.insertParent(1,2);
	f.insertParent(2,3);
	f.insertParent(3,4);
	f.insertParent(2,5);
	ParentExtractor extractor(&f);
	extractor.construct();
	set<int> parents = f.evaluateGetParentStar(4);
	std::set<int>::iterator itr = parents.begin();
	CPPUNIT_ASSERT_EQUAL(1,*itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(2,*itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(3,*itr);
	return;
}

//test the function testEvaluateGetChildrenStar
void
ParentTest::testEvaluateGetChildrenStar(){
	Parent f;
	f.insertParent(1,2);
	f.insertParent(2,3);
	f.insertParent(3,4);
	f.insertParent(2,5);
	ParentExtractor extractor(&f);
	extractor.construct();
	set<int> children = f.evaluateGetChildrenStar(1);
	std::set<int>::iterator itr = children.begin();
	CPPUNIT_ASSERT(children.size()==4);
	CPPUNIT_ASSERT_EQUAL(2,*itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(3,*itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(4,*itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(5,*itr);

	return;
}

//test the function testEvaluateGetParent
void
ParentTest::testEvaluateGetParent(){
	Parent f;
	f.insertParent(1,2);
	f.insertParent(2,3);
	f.insertParent(3,4);
	f.insertParent(2,5);
	ParentExtractor extractor(&f);
	extractor.construct();
	set<int> parent = f.evaluateGetParent(4);
	std::set<int>::iterator itr = parent.begin();
	CPPUNIT_ASSERT_EQUAL(3,*itr);
	return;
}

//test the function testEvaluateGetChildren
void
ParentTest::testEvaluateGetChildren(){
	Parent f;
	f.insertParent(1,2);
	f.insertParent(2,3);
	f.insertParent(3,4);
	f.insertParent(2,5);
	ParentExtractor extractor(&f);
	extractor.construct();
	set<int> children = f.evaluateGetChildren(2);
	std::set<int>::iterator itr = children.begin();
	CPPUNIT_ASSERT(children.size()==2);
	CPPUNIT_ASSERT_EQUAL(3,*itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(5,*itr);
	return;
}

