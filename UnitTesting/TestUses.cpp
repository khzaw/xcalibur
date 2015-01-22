#include <cppunit/config/SourcePrefix.h>
#include "TestUses.h"
#include "PKB\Uses.h"

#include <utility>
#include <vector>
#include <iostream>
#include <string>

void 
UsesTest::setUp()
{

}

void 
UsesTest::tearDown()
{
}

CPPUNIT_TEST_SUITE_REGISTRATION( UsesTest );

//statements

//test get statements that modified var
void 
UsesTest::testGetUsersStmt(){
   Uses m;
   vector<int> stmt;
   m.insertUsesStmt(1,2);
   stmt.push_back(1);
   m.insertUsesStmt(2,2);
   stmt.push_back(2);
   m.insertUsesStmt(4,2);
   stmt.push_back(4);
   m.insertUsesStmt(3,2);
   stmt.push_back(3);
   
   vector<int> users = m.getUsersStmt(2);
   for(int i=0;i<users.size();i++){
   CPPUNIT_ASSERT_EQUAL(stmt[i],users[i]);
   }
	return;
}

//test get modified variables of statements
void 
UsesTest::testGetUsedVarStmt(){
 Uses m;
   vector<int> var;
   m.insertUsesStmt(1,2);
   var.push_back(2);
   m.insertUsesStmt(1,3);
   var.push_back(3);
   m.insertUsesStmt(1,4);
   var.push_back(4);
   m.insertUsesStmt(1,5);
   var.push_back(5);
   
   vector<int> usedVar = m.getUsedVarStmt(1);
   for(int i=0;i<usedVar.size();i++){
   CPPUNIT_ASSERT_EQUAL(var[i],usedVar[i]);
   }
	return;
}

//test get modifies table of statement
void
UsesTest::testGetUsesStmt(){
   Uses m;
   vector<pair<int,int>> p;

   m.insertUsesStmt(1,2);
   p.push_back(make_pair(1,2));
   m.insertUsesStmt(2,3); 
    p.push_back(make_pair(2,3));
   m.insertUsesStmt(4,4);
    p.push_back(make_pair(4,4));
   m.insertUsesStmt(3,5);
    p.push_back(make_pair(3,5));

   vector<pair<int,int>> usesStmt = m.getUsesStmt();
   for(int i=0;i<usesStmt.size();i++){
	   CPPUNIT_ASSERT(p[i] == usesStmt[i]);
   }
    return;
}

//test insertion of modifies for statement
void 
UsesTest::testInsertUsesStmt(){
    Uses m;
	vector<int> var;
	
	m.insertUsesStmt(1,2);
	var.push_back(2);
	m.insertUsesStmt(1,3);
	var.push_back(3);
	vector<int> varGet = m.getUsedVarStmt(1);
	for(int i=0;i<varGet.size();i++){
	CPPUNIT_ASSERT_EQUAL(var[i],varGet[i]);
	}
	m.insertUsesStmt(1,4);
	var.push_back(4);
	for(int i=0;i<varGet.size();i++){
	CPPUNIT_ASSERT_EQUAL(var[i],varGet[i]);
	}
	//check for duplicates
	vector<pair<int,int>> usesTable = m.getUsesStmt();
	int tableSize = usesTable.size();
	CPPUNIT_ASSERT_EQUAL(3,tableSize);
	m.insertUsesStmt(1,4);
	vector<pair<int,int>> usesTable2 = m.getUsesStmt();
	int tableSize2 = usesTable2.size();
	CPPUNIT_ASSERT_EQUAL(3, tableSize2);
	return;
}

//test if modifies for statement 
void 
UsesTest::testIsUsesStmt(){
	Uses m;
	m.insertUsesStmt(1,2);
	CPPUNIT_ASSERT(m.isUsesStmt(1,2));

	return;
}

//Procedure
//test get procedures that modified var
void 
UsesTest::testGetUsersProc(){
   Uses m;
   vector<int> proc;
   m.insertUsesProc(1,2);
   proc.push_back(1);
   m.insertUsesProc(2,2);
   proc.push_back(2);
   m.insertUsesProc(4,2);
   proc.push_back(4);
   m.insertUsesProc(3,2);
   proc.push_back(3);
   
   vector<int> users = m.getUsersStmt(2);
   for(int i=0;i<users.size();i++){
   CPPUNIT_ASSERT_EQUAL(proc[i],users[i]);
   }
	return;
}

//test get modified variables of procedures
void 
UsesTest::testGetUsedVarProc(){
 Uses m;
   vector<int> var;
   m.insertUsesProc(1,2);
   var.push_back(2);
   m.insertUsesProc(1,3);
   var.push_back(3);
   m.insertUsesProc(1,4);
   var.push_back(4);
   m.insertUsesProc(1,5);
   var.push_back(5);
   
   vector<int> usedVar = m.getUsedVarProc(1);
   for(int i=0;i<usedVar.size();i++){
   CPPUNIT_ASSERT_EQUAL(var[i],usedVar[i]);
   }
	return;
}

//test get modifies table of procedures
void
UsesTest::testGetUsesProc(){
   Uses m;
   vector<pair<int,int>> p;

   m.insertUsesProc(1,2);
   p.push_back(make_pair(1,2));
   m.insertUsesProc(2,3); 
    p.push_back(make_pair(2,3));
   m.insertUsesProc(4,4);
    p.push_back(make_pair(4,4));
   m.insertUsesProc(3,5);
    p.push_back(make_pair(3,5));

   vector<pair<int,int>> usesProc = m.getUsesProc();
   for(int i=0;i<usesProc.size();i++){
	   CPPUNIT_ASSERT(p[i] == usesProc[i]);
   }
    return;
}
//test insertion of modifies for procedures
void 
UsesTest::testInsertUsesProc(){
    Uses m;
	vector<int> var;
	m.insertUsesProc(1,2);
	var.push_back(2);
	m.insertUsesProc(1,3);
	var.push_back(3);
	vector<int> varGet = m.getUsedVarProc(1);
	for(int i=0;i<varGet.size();i++){
	CPPUNIT_ASSERT_EQUAL(var[i],varGet[i]);
	}
	m.insertUsesProc(1,4);
	var.push_back(4);
	for(int i=0;i<varGet.size();i++){
	CPPUNIT_ASSERT_EQUAL(var[i],varGet[i]);
	}
	//check for duplicates
	vector<pair<int,int>> usesTable = m.getUsesProc();
	int tableSize = usesTable.size();
	CPPUNIT_ASSERT_EQUAL(3,tableSize);
	m.insertUsesProc(1,4);
	vector<pair<int,int>> usesTable2 = m.getUsesProc();
	int tableSize2 = usesTable2.size();
	CPPUNIT_ASSERT_EQUAL(3, tableSize2);
	return;
}

//test if modifies for procedures 
void 
UsesTest::testIsUsesProc(){
	Uses m;
	m.insertUsesProc(1,2);
	CPPUNIT_ASSERT(m.isUsesProc(1,2));

	return;
}
