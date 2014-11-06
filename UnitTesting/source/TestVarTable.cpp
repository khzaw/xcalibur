#include <cppunit/config/SourcePrefix.h>
#include "testVarTable.h"
#include "VarTable.h"

#include <iostream>
#include <string>

void 
VarTableTest::setUp()
{
}

void 
VarTableTest::tearDown()
{
}

CPPUNIT_TEST_SUITE_REGISTRATION( VarTableTest );

// method to test insertion of procedures
void 
VarTableTest::testInsert(){
	//inserting non duplicates procedures
	VarTable p;
	p.insertVar("variable1");
	p.insertVar("variable2");
	p.insertVar("variable3");
	CPPUNIT_ASSERT(p.getVarName(0) == "variable1");
	CPPUNIT_ASSERT(p.getVarName(1) == "variable2");
	CPPUNIT_ASSERT(p.getVarName(2) == "variable3");
	//inserting duplicate procedures
	//size before inserting
	CPPUNIT_ASSERT_EQUAL(3,p.getSize());
	p.insertVar("variable2");
	//size of proctable remains unchanged. duplicate is not inserted
	CPPUNIT_ASSERT_EQUAL(3,p.getSize());
	return;
}

// method to test the assigning and retrieval of procedures
void 
VarTableTest::testInsertAndRetrieveVarUsingIndex (){
	VarTable p;
	p.insertVar("variable1");
	p.insertVar("variable2");
	p.insertVar("variable3");
	CPPUNIT_ASSERT_EQUAL(0,p.getVarIndex("variable1"));
	CPPUNIT_ASSERT_EQUAL(1,p.getVarIndex("variable2"));
	CPPUNIT_ASSERT_EQUAL(2,p.getVarIndex("variable3"));
	return;
}

void 
VarTableTest::testInsertAndRetrieveVarUsingVarName (){
	VarTable p;
	p.insertVar("procedure1");
	p.insertVar("procedure2");
	p.insertVar("procedure3");
	CPPUNIT_ASSERT(p.getVarName(0) == "procedure1");
	CPPUNIT_ASSERT(p.getVarName(1) == "procedure2");
	CPPUNIT_ASSERT(p.getVarName(2) == "procedure3");
	return;
}

// method to test the retrieval of proc table size
void 
VarTableTest::testRetrieveVarTableSize(){
	VarTable v;
	v.insertVar("variable1");
	CPPUNIT_ASSERT_EQUAL(1,v.getSize());
	v.insertVar("variable2");
	CPPUNIT_ASSERT_EQUAL(2,v.getSize());
	v.insertVar("variable3");
	CPPUNIT_ASSERT_EQUAL(3,v.getSize());
	return;
}

	// method to check if the proc table contains the specified procedure
void
VarTableTest::testIfContainsVar(){
	VarTable v;
	v.insertVar("variable1");
	CPPUNIT_ASSERT(v.containsVar("variable1"));
	CPPUNIT_ASSERT(!(v.containsVar("variable112")));
	v.insertVar("variable2");
	CPPUNIT_ASSERT(v.containsVar("variable2"));
	return;
}
