#include <cppunit/config/SourcePrefix.h>
#include "TestProcTable.h"
#include "PKB\ProcTable.h"

#include <iostream>
#include <string>

void 
ProcTableTest::setUp()
{
}

void 
ProcTableTest::tearDown()
{
}

CPPUNIT_TEST_SUITE_REGISTRATION( ProcTableTest );
// method to test insertion of procedures
void 
ProcTableTest::testInsert(){
	//inserting non duplicates procedures
	ProcTable p;
	p.insertProc("procedure1");
	p.insertProc("procedure2");
	p.insertProc("procedure3");
	CPPUNIT_ASSERT(p.getProcName(0) == "procedure1");
	CPPUNIT_ASSERT(p.getProcName(1) == "procedure2");
	CPPUNIT_ASSERT(p.getProcName(2) == "procedure3");
	//inserting duplicate procedures
	//size before inserting
	CPPUNIT_ASSERT_EQUAL(3,p.getSize());
	p.insertProc("procedure2");
	//size of proctable remains unchanged. duplicate is not inserted
	CPPUNIT_ASSERT_EQUAL(3,p.getSize());
	return;
}

// method to test the assigning and retrieval of procedures
void 
ProcTableTest::testInsertAndRetrieveProceduresUsingIndex (){
	ProcTable p;
	p.insertProc("procedure1");
	p.insertProc("procedure2");
	p.insertProc("procedure3");
	CPPUNIT_ASSERT_EQUAL(0,p.getProcIndex("procedure1"));
	CPPUNIT_ASSERT_EQUAL(1,p.getProcIndex("procedure2"));
	CPPUNIT_ASSERT_EQUAL(2,p.getProcIndex("procedure3"));
	return;
}

void 
ProcTableTest::testInsertAndRetrieveProceduresUsingProcName (){
	ProcTable p;
	p.insertProc("procedure1");
	p.insertProc("procedure2");
	p.insertProc("procedure3");
	CPPUNIT_ASSERT(p.getProcName(0) == "procedure1");
	CPPUNIT_ASSERT(p.getProcName(1) == "procedure2");
	CPPUNIT_ASSERT(p.getProcName(2) == "procedure3");
	return;
}

// method to test the retrieval of proc table size
void 
ProcTableTest::testRetrieveProcTableSize(){
	ProcTable p;
	p.insertProc("procedure1");
	CPPUNIT_ASSERT_EQUAL(1,p.getSize());
	p.insertProc("procedure2");
	CPPUNIT_ASSERT_EQUAL(2,p.getSize());
	p.insertProc("procedure3");
	CPPUNIT_ASSERT_EQUAL(3,p.getSize());
	return;
}

	// method to check if the proc table contains the specified procedure
void
ProcTableTest::testIfContainsProcedure(){
	ProcTable p;
	p.insertProc("procedure1");
	CPPUNIT_ASSERT(p.containsProc("procedure1"));
	CPPUNIT_ASSERT(!(p.containsProc("procedure112")));
	p.insertProc("procedure2");
	CPPUNIT_ASSERT(p.containsProc("procedure2"));
	return;
}
