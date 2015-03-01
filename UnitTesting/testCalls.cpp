#include <cppunit/config/SourcePrefix.h>
#include "testCalls.h"
#include "PKB\Calls.h"
#include "PKB\CallsExtractor.h"

#include <iostream>
#include <string>

void 
CallsTest::setUp()
{
}

void 
CallsTest::tearDown()
{
}	

CPPUNIT_TEST_SUITE_REGISTRATION( CallsTest );
// method to test insertion of Calls


void 
CallsTest::testInsertCalls(){
	Calls c;
	CallsExtractor extractor(&c);
	c.insertCalls(1,2);
	c.insertCalls(2,3);
	c.insertCalls(1,3);
	c.insertCalls(1,4);
	c.insertCalls(4,5);
	extractor.construct();
	CPPUNIT_ASSERT(c.isCalls(1,2));
	CPPUNIT_ASSERT(c.isCalls(1,3));
	CPPUNIT_ASSERT(c.isCalls(1,4));
	CPPUNIT_ASSERT(c.isCalls(2,3));
	CPPUNIT_ASSERT(c.isCalls(4,5));
	CPPUNIT_ASSERT_EQUAL(5,c.getSize());
	return;
}

void
CallsTest::testGetCallerStar(){
	Calls c;
	CallsExtractor extractor(&c);
	c.insertCalls(1,2);
	c.insertCalls(2,3);
	c.insertCalls(1,3);
	c.insertCalls(1,4);
	c.insertCalls(4,5);
	extractor.construct();
	set<int> callers = c.getCallerStar(3);
	CPPUNIT_ASSERT(callers.size()==2);
	std::set<int>::iterator itr = callers.begin();
	CPPUNIT_ASSERT_EQUAL(1,*itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(2,*itr);
	return;
}

void
	CallsTest::testGetCalleeStar(){
	Calls c;
	CallsExtractor extractor(&c);
	c.insertCalls(1,2);
	c.insertCalls(2,3);
	c.insertCalls(1,3);
	c.insertCalls(1,4);
	c.insertCalls(4,5);
	extractor.construct();
	set<int> callees = c.getCalleeStar(1);
	CPPUNIT_ASSERT(callees.size()==4);
	std::set<int>::iterator itr = callees.begin();
	CPPUNIT_ASSERT_EQUAL(2,*itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(3,*itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(4,*itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(5,*itr);
	return;
}

void
CallsTest::testGetAllCallers(){
	Calls c;
	CallsExtractor extractor(&c);
	c.insertCalls(1,2);
	c.insertCalls(2,3);
	c.insertCalls(1,3);
	extractor.construct();
	set<int> callers = c.getAllCallers();
	CPPUNIT_ASSERT(callers.size()==2);
	std::set<int>::iterator itr = callers.begin();
	CPPUNIT_ASSERT_EQUAL(1,*itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(2,*itr);
	return;
}

void
CallsTest::testGetAllCallees(){
	Calls c;
	CallsExtractor extractor(&c);
	c.insertCalls(1,2);
	c.insertCalls(2,3);
	c.insertCalls(1,3);
	extractor.construct();
	set<int> callees = c.getAllCallees();
	CPPUNIT_ASSERT(callees.size()==2);
	std::set<int>::iterator itr = callees.begin();
	CPPUNIT_ASSERT_EQUAL(2,*itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(3,*itr);
	return;
}

void
CallsTest::testEvaluateGetCallees(){
	Calls c;
	CallsExtractor extractor(&c);
	c.insertCalls(1,2);
	c.insertCalls(2,3);
	c.insertCalls(1,3);
	c.insertCalls(1,4);
	c.insertCalls(4,5);
	extractor.construct();
	set<int> callees = c.evaluateGetCallees(1);
	CPPUNIT_ASSERT(callees.size()==3);
	std::set<int>::iterator itr = callees.begin();
	CPPUNIT_ASSERT_EQUAL(2,*itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(3,*itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(4,*itr);
	return;
}

void
CallsTest::testEvaluateGetCallers(){
	Calls c;
	CallsExtractor extractor(&c);
	c.insertCalls(1,2);
	c.insertCalls(2,3);
	c.insertCalls(1,3);
	c.insertCalls(1,4);
	c.insertCalls(4,5);
	extractor.construct();
	set<int> callers = c.evaluateGetCallers(3);
	CPPUNIT_ASSERT(callers.size()==2);
	std::set<int>::iterator itr = callers.begin();
	CPPUNIT_ASSERT_EQUAL(1,*itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(2,*itr);
	return;
}

void
CallsTest::testEvaluateGetCallersStar(){
	Calls c;
	CallsExtractor extractor(&c);
	c.insertCalls(1,2);
	c.insertCalls(2,3);
	c.insertCalls(1,4);
	c.insertCalls(4,5);
	extractor.construct();
	set<int> callers = c.evaluateGetCallersStar(5);
	CPPUNIT_ASSERT(callers.size()==2);
	std::set<int>::iterator itr = callers.begin();
	CPPUNIT_ASSERT_EQUAL(1,*itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(4,*itr);
	return;
}

void
CallsTest::testEvaluateGetCalleesStar(){
	Calls c;
	CallsExtractor extractor(&c);
	c.insertCalls(1,2);
	c.insertCalls(2,3);
	c.insertCalls(1,3);
	c.insertCalls(1,4);
	c.insertCalls(4,5);
	extractor.construct();
	set<int> callees = c.evaluateGetCalleesStar(1);
	CPPUNIT_ASSERT(callees.size()==3);
	std::set<int>::iterator itr = callees.begin();
	CPPUNIT_ASSERT_EQUAL(2,*itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(3,*itr);
	itr++;
	CPPUNIT_ASSERT_EQUAL(4,*itr);
	return;
}

void
CallsTest::testIsCalls(){
	Calls c;
	CallsExtractor extractor(&c);
	c.insertCalls(1,2);
	c.insertCalls(2,3);
	c.insertCalls(1,3);
	extractor.construct();
	CPPUNIT_ASSERT_EQUAL(true,c.isCalls(1,2));
	CPPUNIT_ASSERT_EQUAL(true,c.isCalls(2,3));
	CPPUNIT_ASSERT_EQUAL(true,c.isCalls(1,3));
}

void
CallsTest::testIsCallsStar(){
	Calls c;
	CallsExtractor extractor(&c);
	c.insertCalls(1,2);
	c.insertCalls(2,3);
	c.insertCalls(1,4);
	c.insertCalls(4,5);
	extractor.construct();
	CPPUNIT_ASSERT_EQUAL(true,c.isCallsStar(1,2));
	CPPUNIT_ASSERT_EQUAL(true,c.isCallsStar(1,3));
	CPPUNIT_ASSERT_EQUAL(true,c.isCallsStar(1,5));
	return;
}