#include <cppunit/config/SourcePrefix.h>
#include "testContains.h"
#include "PKB\Contains.h"

#include <iostream>
#include <string>

void 
	ContainsTest::setUp()
{
}

void 
	ContainsTest::tearDown()
{
}	

CPPUNIT_TEST_SUITE_REGISTRATION( ContainsTest );

void ContainsTest::testInsert(){
	Contains contains;
	contains.insertProcStmtLst(1,1);
	CPPUNIT_ASSERT(contains.isContainsProcStmtLst(1,1));
	contains.insertStmtLstStmt(1,3);
	CPPUNIT_ASSERT(contains.isContainsStmtLstStmt(1,3));
	contains.insertStmtStmtLst(3,4);
	CPPUNIT_ASSERT(contains.isContainsStmtStmtLst(3,4));
	contains.insertStmtVar(3,1);
	CPPUNIT_ASSERT(contains.isContainsStmtVar(3,1));
	contains.insertStmtConst(3,1);
	CPPUNIT_ASSERT(contains.isContainsStmtConst(3,4));

}

//tests for procedures as containers
void ContainsTest::testGetStmtLstContainedStarInProc(){
	 Contains contains;
	contains.insertProcStmtLst(1,1);
	contains.insertStmtLstStmt(1,3);
	contains.insertStmtStmtLst(3,4);
	set<int> results = contains.getStmtLstContainedStarInProc(1);
	int size = results.size();
	CPPUNIT_ASSERT_EQUAL(2, size);
	std::set<int>::iterator it= results.begin();
	CPPUNIT_ASSERT_EQUAL(1,*it);
	it++;
	CPPUNIT_ASSERT_EQUAL(4,*it); 

}

void ContainsTest::testGetProcContainingStarStmtLst(){
	 Contains contains;
	contains.insertProcStmtLst(1,1);
	contains.insertStmtLstStmt(1,3);
	contains.insertStmtStmtLst(3,4);
	set<int> results = contains.getProcContainingStarStmtLst(4);
	int size = results.size();
	CPPUNIT_ASSERT_EQUAL(1, size);
	std::set<int>::iterator it= results.begin();
	CPPUNIT_ASSERT_EQUAL(1,*it); 
}

void ContainsTest::testGetStmtContainedStarInProc(){
	 Contains contains;
	contains.insertProcStmtLst(1,1);
	contains.insertStmtLstStmt(1,3);
	contains.insertStmtStmtLst(3,4);
	set<int> results = contains.getStmtContainedStarInProc(1);
	int size = results.size();
	CPPUNIT_ASSERT_EQUAL(1, size);
	std::set<int>::iterator it= results.begin();
	CPPUNIT_ASSERT_EQUAL(3,*it); 
}

void ContainsTest::testGetProcContainingStarStmt(){
	 Contains contains;
	contains.insertProcStmtLst(1,1);
	contains.insertStmtLstStmt(1,3);
	contains.insertStmtStmtLst(3,4);
	set<int> results = contains.getProcContainingStarStmt(3);
	int size = results.size();
	CPPUNIT_ASSERT_EQUAL(1, size);
	std::set<int>::iterator it= results.begin();
	CPPUNIT_ASSERT_EQUAL(1,*it); 
}


void ContainsTest::testGetVarContainedStarInProc(){
	 Contains contains;
	contains.insertProcStmtLst(1,1);
	contains.insertStmtLstStmt(1,3);
	contains.insertStmtStmtLst(3,4);
	contains.insertStmtVar(3,1);
	contains.insertStmtConst(3,1);
	set<int> results = contains.getVarContainedStarInProc(1);
	int size = results.size();
	CPPUNIT_ASSERT_EQUAL(1, size);
	std::set<int>::iterator it= results.begin();
	CPPUNIT_ASSERT_EQUAL(1,*it); 
}

void ContainsTest::testGetProcsContainingStarVar(){
	 Contains contains;
	contains.insertProcStmtLst(1,1);
	contains.insertStmtLstStmt(1,3);
	contains.insertStmtStmtLst(3,4);
	contains.insertStmtVar(3,1);
	contains.insertStmtConst(3,1);
	set<int> results = contains.getProcsContainingStarVar(1);
	int size = results.size();
	CPPUNIT_ASSERT_EQUAL(1, size);
	std::set<int>::iterator it= results.begin();
	CPPUNIT_ASSERT_EQUAL(1,*it); 

}

void ContainsTest::testGetConstContainedStarInProc(){
	 Contains contains;
	contains.insertProcStmtLst(1,1);
	contains.insertStmtLstStmt(1,3);
	contains.insertStmtStmtLst(3,4);
	contains.insertStmtVar(3,1);
	contains.insertStmtConst(3,1);
	set<int> results = contains.getConstContainedStarInProc(1);
	int size = results.size();
	CPPUNIT_ASSERT_EQUAL(1, size);
	std::set<int>::iterator it= results.begin();
	CPPUNIT_ASSERT_EQUAL(1,*it); 
}

void ContainsTest::testGetProcContainingStarConst(){
	 Contains contains;
	contains.insertProcStmtLst(1,1);
	contains.insertStmtLstStmt(1,3);
	contains.insertStmtStmtLst(3,4);
	contains.insertStmtVar(3,1);
	contains.insertStmtConst(3,1);
	set<int> results = contains.getProcContainingStarConst(1);
	int size = results.size();
	CPPUNIT_ASSERT_EQUAL(1, size);
	std::set<int>::iterator it= results.begin();
	CPPUNIT_ASSERT_EQUAL(1,*it); 
}

//tests for statementsLists as containers
void ContainsTest::testGetStmtContainedStarInStmtLst(){
	 Contains contains;
	contains.insertProcStmtLst(1,1);
	contains.insertStmtLstStmt(1,3);
	contains.insertStmtStmtLst(3,4);
	contains.insertStmtLstStmt(4,4);
	contains.insertStmtVar(3,1);
	contains.insertStmtConst(3,1);
	set<int> results = contains.getStmtContainedStarInStmtLst(1);
	int size = results.size();
	CPPUNIT_ASSERT_EQUAL(2, size);
	std::set<int>::iterator it= results.begin();
	CPPUNIT_ASSERT_EQUAL(1,*it);
	it++;
	CPPUNIT_ASSERT_EQUAL(4,*it); 
}

void ContainsTest::testGetStmtLstContainingStarStmt(){
	 Contains contains;
	contains.insertProcStmtLst(1,1);
	contains.insertStmtLstStmt(1,3);
	contains.insertStmtStmtLst(3,4);
	contains.insertStmtLstStmt(4,4);
	contains.insertStmtVar(3,1);
	contains.insertStmtConst(3,1);
	set<int> results = contains.getStmtLstContainingStarStmt(3);
	int size = results.size();
	CPPUNIT_ASSERT_EQUAL(1, size);
	std::set<int>::iterator it= results.begin();
	CPPUNIT_ASSERT_EQUAL(1,*it);
	it++; 
}

void ContainsTest::testGetVarContainedStarInStmtLst(){
	 Contains contains;
	contains.insertProcStmtLst(1,1);
	contains.insertStmtLstStmt(1,3);
	contains.insertStmtStmtLst(3,4);
	contains.insertStmtLstStmt(4,4);
	contains.insertStmtVar(3,1);
	contains.insertStmtConst(3,1);
	set<int> results = contains.getVarContainedStarInStmtLst(1);
	int size = results.size();
	CPPUNIT_ASSERT_EQUAL(1, size);
	std::set<int>::iterator it= results.begin();
	CPPUNIT_ASSERT_EQUAL(1,*it);
	it++; 
}


void ContainsTest::testGetStmtLstContainingStarVar(){
	 Contains contains;
	contains.insertProcStmtLst(1,1);
	contains.insertStmtLstStmt(1,3);
	contains.insertStmtStmtLst(3,4);
	contains.insertStmtLstStmt(4,4);
	contains.insertStmtVar(3,1);
	contains.insertStmtConst(3,1);
	set<int> results = contains.getStmtLstContainingStarVar(1);
	int size = results.size();
	CPPUNIT_ASSERT_EQUAL(1, size);
	std::set<int>::iterator it= results.begin();
	CPPUNIT_ASSERT_EQUAL(1,*it);
	it++; 
}


void ContainsTest::testGetConstContainedStarInStmtLst(){
	 Contains contains;
	contains.insertProcStmtLst(1,1);
	contains.insertStmtLstStmt(1,3);
	contains.insertStmtStmtLst(3,4);
	contains.insertStmtLstStmt(4,4);
	contains.insertStmtVar(3,1);
	contains.insertStmtConst(3,1);
	set<int> results = contains.getConstContainedStarInStmtLst(1);
	int size = results.size();
	CPPUNIT_ASSERT_EQUAL(1, size);
	std::set<int>::iterator it= results.begin();
	CPPUNIT_ASSERT_EQUAL(1,*it);
	it++; 
}



void ContainsTest::testGetStmtLstContainingStarConst(){
	Contains contains;
	contains.insertProcStmtLst(1,1);
	contains.insertStmtLstStmt(1,3);
	contains.insertStmtStmtLst(3,4);
	contains.insertStmtLstStmt(4,4);
	contains.insertStmtVar(3,1);
	contains.insertStmtConst(3,1);
	set<int> results = contains.getStmtLstContainingStarConst(1);
	int size = results.size();
	CPPUNIT_ASSERT_EQUAL(1, size);
	std::set<int>::iterator it= results.begin();
	CPPUNIT_ASSERT_EQUAL(1,*it);
	it++; 
}	


//statements as containers
void ContainsTest::testGetVarContainedStarInStmt(){
	Contains contains;
	contains.insertProcStmtLst(1,1);
	contains.insertStmtLstStmt(1,3);
	contains.insertStmtStmtLst(3,4);
	contains.insertStmtLstStmt(4,4);
	contains.insertStmtVar(4,1);
	contains.insertStmtConst(4,1);
	set<int> results = contains.getVarContainedStarInStmt(3);
	int size = results.size();
	CPPUNIT_ASSERT_EQUAL(1, size);
	std::set<int>::iterator it= results.begin();
	CPPUNIT_ASSERT_EQUAL(1,*it);
	it++; 

}
void ContainsTest::testGetStmtContainingStarVar(){
	Contains contains;
	contains.insertProcStmtLst(1,1);
	contains.insertStmtLstStmt(1,3);
	contains.insertStmtStmtLst(3,4);
	contains.insertStmtLstStmt(4,4);
	contains.insertStmtVar(4,1);
	contains.insertStmtConst(4,1);
	set<int> results = contains.getStmtContainingStarVar(1);
	int size = results.size();
	CPPUNIT_ASSERT_EQUAL(2, size);
	std::set<int>::iterator it= results.begin();
	CPPUNIT_ASSERT_EQUAL(3,*it);
	it++;
	CPPUNIT_ASSERT_EQUAL(4,*it);
}

void ContainsTest::testGetConstContainedStarInStmt(){
	Contains contains;
	contains.insertProcStmtLst(1,1);
	contains.insertStmtLstStmt(1,3);
	contains.insertStmtStmtLst(3,4);
	contains.insertStmtLstStmt(4,4);
	contains.insertStmtVar(4,1);
	contains.insertStmtConst(4,1);
	set<int> results = contains.getConstContainedStarInStmt(3);
	int size = results.size();
	CPPUNIT_ASSERT_EQUAL(1, size);
	std::set<int>::iterator it= results.begin();
	CPPUNIT_ASSERT_EQUAL(1,*it);
	it++; 
}

void ContainsTest::testGetStmtContainingStarConst(){
	Contains contains;
	contains.insertProcStmtLst(1,1);
	contains.insertStmtLstStmt(1,3);
	contains.insertStmtStmtLst(3,4);
	contains.insertStmtLstStmt(4,4);
	contains.insertStmtVar(4,1);
	contains.insertStmtConst(4,1);
	set<int> results = contains.getStmtContainingStarConst(1);
	int size = results.size();
	CPPUNIT_ASSERT_EQUAL(2, size);
	std::set<int>::iterator it= results.begin();
	CPPUNIT_ASSERT_EQUAL(3,*it);
	it++;
	CPPUNIT_ASSERT_EQUAL(4,*it);
}

void ContainsTest::testGetStmtLstContainedStarInStmt(){
	Contains contains;
	contains.insertProcStmtLst(1,1);
	contains.insertStmtLstStmt(1,3);
	contains.insertStmtStmtLst(3,4);
	contains.insertStmtLstStmt(4,4);
	contains.insertStmtVar(4,1);
	contains.insertStmtConst(4,1);
	set<int> results = contains.getStmtLstContainedStarInStmt(3);
	int size = results.size();
	CPPUNIT_ASSERT_EQUAL(1, size);
	std::set<int>::iterator it= results.begin();
	CPPUNIT_ASSERT_EQUAL(1,*it);
	it++; 
}

void ContainsTest::testGetStmtContainingStarStmtLst(){
	Contains contains;
	contains.insertProcStmtLst(1,1);
	contains.insertStmtLstStmt(1,3);
	contains.insertStmtStmtLst(3,4);
	contains.insertStmtLstStmt(4,4);
	contains.insertStmtVar(4,1);
	contains.insertStmtConst(4,1);
	set<int> results = contains.getStmtContainingStarStmtLst(1);
	int size = results.size();
	CPPUNIT_ASSERT_EQUAL(0, size);
}

//boolean functions
void ContainsTest::testIsContainsStarProcStmtLst(){
	Contains contains;
	contains.insertProcStmtLst(1,1);
	contains.insertStmtLstStmt(1,3);
	contains.insertStmtStmtLst(3,4);
	contains.insertStmtLstStmt(4,4);
	contains.insertStmtVar(4,1);
	contains.insertStmtConst(4,1);
	bool result = contains.isContainsStarProcStmtLst(1,4);
	CPPUNIT_ASSERT(result==true);
}

void ContainsTest::testIsContainsStarProcStmt(){
	Contains contains;
	contains.insertProcStmtLst(1,1);
	contains.insertStmtLstStmt(1,3);
	contains.insertStmtStmtLst(3,4);
	contains.insertStmtLstStmt(4,4);
	contains.insertStmtVar(4,1);
	contains.insertStmtConst(4,1);
	bool result = contains.isContainsStarProcStmt(1,4);
	CPPUNIT_ASSERT(result==true);
}

void ContainsTest::testIsContainsStarProcVar(){
	Contains contains;
	contains.insertProcStmtLst(1,1);
	contains.insertStmtLstStmt(1,3);
	contains.insertStmtStmtLst(3,4);
	contains.insertStmtLstStmt(4,4);
	contains.insertStmtVar(4,1);
	contains.insertStmtConst(4,1);
	bool result = contains.isContainsStarProcVar(1,1);
	CPPUNIT_ASSERT(result==true);
	result = contains.isContainsStarProcVar(1,2);
	CPPUNIT_ASSERT(result==false);
}

void ContainsTest::testIsContainsStarStmtLstStmt(){
	Contains contains;
	contains.insertProcStmtLst(1,1);
	contains.insertStmtLstStmt(1,3);
	contains.insertStmtStmtLst(3,4);
	contains.insertStmtLstStmt(4,4);
	contains.insertStmtVar(4,1);
	contains.insertStmtConst(4,1);
	bool result = contains.isContainsStarStmtLstStmt(1,4);
	CPPUNIT_ASSERT(result==true);
	result = contains.isContainsStarStmtLstStmt(1,3);
	CPPUNIT_ASSERT(result==true);
	result = contains.isContainsStarStmtLstStmt(4,4);
	CPPUNIT_ASSERT(result==true);

}

void ContainsTest::testIsContainsStarStmtLstVar(){
	Contains contains;
	contains.insertProcStmtLst(1,1);
	contains.insertStmtLstStmt(1,3);
	contains.insertStmtStmtLst(3,4);
	contains.insertStmtLstStmt(4,4);
	contains.insertStmtVar(4,1);
	contains.insertStmtConst(4,1);
	bool result = contains.isContainsStarStmtLstVar(1,1);
	CPPUNIT_ASSERT(result==true);
	result = contains.isContainsStarStmtLstVar(4,1);
	CPPUNIT_ASSERT(result==true);
}

void ContainsTest::testIsContainsStarStmtLstConst(){
	Contains contains;
	contains.insertProcStmtLst(1,1);
	contains.insertStmtLstStmt(1,3);
	contains.insertStmtStmtLst(3,4);
	contains.insertStmtLstStmt(4,4);
	contains.insertStmtVar(4,1);
	contains.insertStmtConst(4,1);
	bool result = contains.isContainsStarStmtLstConst(1,1);
	CPPUNIT_ASSERT(result==true);
	result = contains.isContainsStarStmtLstConst(4,1);
	CPPUNIT_ASSERT(result==true);
}

void ContainsTest::testIsContainsStarStmtLstStmtLst(){
	Contains contains;
	contains.insertProcStmtLst(1,1);
	contains.insertStmtLstStmt(1,3);
	contains.insertStmtStmtLst(3,4);
	contains.insertStmtLstStmt(4,4);
	contains.insertStmtVar(4,1);
	contains.insertStmtConst(4,1);
	bool result = contains.isContainsStarStmtLstStmtLst(1,4);
	CPPUNIT_ASSERT(result==true);
	result = contains.isContainsStarStmtLstStmtLst(4,1);
	CPPUNIT_ASSERT(result==false);
}

void ContainsTest::testIsContainsStarStmtVar(){
	Contains contains;
	contains.insertProcStmtLst(1,1);
	contains.insertStmtLstStmt(1,3);
	contains.insertStmtStmtLst(3,4);
	contains.insertStmtLstStmt(4,4);
	contains.insertStmtVar(4,1);
	contains.insertStmtConst(4,1);
	bool result = contains.isContainsStarStmtVar(3,1);
	CPPUNIT_ASSERT(result==true);
	result = contains.isContainsStarStmtVar(4,1);
	CPPUNIT_ASSERT(result==true);
}

void ContainsTest::testIsContainsStarStmtConst(){
	Contains contains;
	contains.insertProcStmtLst(1,1);
	contains.insertStmtLstStmt(1,3);
	contains.insertStmtStmtLst(3,4);
	contains.insertStmtLstStmt(4,4);
	contains.insertStmtVar(4,1);
	contains.insertStmtConst(4,1);
	bool result = contains.isContainsStarStmtConst(3,1);
	CPPUNIT_ASSERT(result==true);
	result = contains.isContainsStarStmtConst(4,1);
	CPPUNIT_ASSERT(result==true);
}

void ContainsTest::testIsContainsStarStmtStmtLst(){
	Contains contains;
	contains.insertProcStmtLst(1,1);
	contains.insertStmtLstStmt(1,3);
	contains.insertStmtStmtLst(3,4);
	contains.insertStmtLstStmt(4,4);
	contains.insertStmtVar(4,1);
	contains.insertStmtConst(4,1);
	bool result = contains.isContainsStarStmtStmtLst(3,4);
	CPPUNIT_ASSERT(result==true);
	result = contains.isContainsStarStmtStmtLst(3,1);
	CPPUNIT_ASSERT(result==false);
}


