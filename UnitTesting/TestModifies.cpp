#include <cppunit/config/SourcePrefix.h>
#include "TestModifies.h"
#include "PKB\Modifies.h"

#include <utility>
#include <vector>
#include <iostream>
#include <string>

void 
ModifiesTest::setUp()
{

}

void 
ModifiesTest::tearDown()
{
}

CPPUNIT_TEST_SUITE_REGISTRATION( ModifiesTest );

//statements
//test get statements that modified var
void 
ModifiesTest::testGetModifiersStmt(){
   Modifies m;
   vector<int> stmt;
   m.insertModifiesStmt(1,2);
   stmt.push_back(1);
   m.insertModifiesStmt(2,2);
   stmt.push_back(2);
   m.insertModifiesStmt(4,2);
   stmt.push_back(4);
   m.insertModifiesStmt(3,2);
   stmt.push_back(3);
   
   vector<int> modifiers = m.getModifiersStmt(2);
   for(int i=0;i<modifiers.size();i++){
   CPPUNIT_ASSERT_EQUAL(stmt[i],modifiers[i]);
   }
	return;
}

//test get modified variables of statements
void 
ModifiesTest::testGetModifiedVarStmt(){
 Modifies m;
   vector<int> var;
   m.insertModifiesStmt(1,2);
   var.push_back(2);
   m.insertModifiesStmt(1,3);
   var.push_back(3);
   m.insertModifiesStmt(1,4);
   var.push_back(4);
   m.insertModifiesStmt(1,5);
   var.push_back(5);
   
   vector<int> modifiedVar = m.getModifiedVarStmt(1);
   for(int i=0;i<modifiedVar.size();i++){
   CPPUNIT_ASSERT_EQUAL(var[i],modifiedVar[i]);
   }
	return;
}

//test get modifies table of statement
void
ModifiesTest::testGetModifiesStmt(){
   Modifies m;
   vector<pair<int,int>> p;

   m.insertModifiesStmt(1,2);
   p.push_back(make_pair(1,2));
   m.insertModifiesStmt(2,3); 
    p.push_back(make_pair(2,3));
   m.insertModifiesStmt(4,4);
    p.push_back(make_pair(4,4));
   m.insertModifiesStmt(3,5);
    p.push_back(make_pair(3,5));

   vector<pair<int,int>> modifiesStmt = m.getModifiesStmt();
   for(int i=0;i<modifiesStmt.size();i++){
	   CPPUNIT_ASSERT(p[i] == modifiesStmt[i]);
   }
    return;
}

//test insertion of modifies for statement
void 
ModifiesTest::testInsertModifiesStmt(){
    Modifies m;
	vector<int> var;
	
	m.insertModifiesStmt(1,2);
	var.push_back(2);
	m.insertModifiesStmt(1,3);
	var.push_back(3);
	vector<int> varGet = m.getModifiedVarStmt(1);
	for(int i=0;i<varGet.size();i++){
	CPPUNIT_ASSERT_EQUAL(var[i],varGet[i]);
	}
	m.insertModifiesStmt(1,4);
	var.push_back(4);
	for(int i=0;i<varGet.size();i++){
	CPPUNIT_ASSERT_EQUAL(var[i],varGet[i]);
	}
	//check for duplicates
	vector<pair<int,int>> modifiesTable = m.getModifiesStmt();
	int tableSize = modifiesTable.size();
	CPPUNIT_ASSERT_EQUAL(3,tableSize);
	m.insertModifiesStmt(1,4);
	vector<pair<int,int>> modifiesTable2 = m.getModifiesStmt();
	int tableSize2 = modifiesTable2.size();
	CPPUNIT_ASSERT_EQUAL(3,tableSize2);
	return;
}

//test if modifies for statement 
void 
ModifiesTest::testIsModifiesStmt(){
	Modifies m;
	m.insertModifiesStmt(1,2);
	CPPUNIT_ASSERT(m.isModifiesStmt(1,2));

	return;
}

//Procedure
//test get procedures that modified var
void 
ModifiesTest::testGetModifiersProc(){
   Modifies m;
   vector<int> proc;
   m.insertModifiesProc(1,2);
   proc.push_back(1);
   m.insertModifiesProc(2,2);
   proc.push_back(2);
   m.insertModifiesProc(4,2);
   proc.push_back(4);
   m.insertModifiesProc(3,2);
   proc.push_back(3);
   
   vector<int> modifiers = m.getModifiersProc(2);
   for(int i=0;i<modifiers.size();i++){
   CPPUNIT_ASSERT_EQUAL(proc[i],modifiers[i]);
   }
	return;
}

//test get modified variables of procedures
void 
ModifiesTest::testGetModifiedVarProc(){
 Modifies m;
   vector<int> var;
   m.insertModifiesProc(1,2);
   var.push_back(2);
   m.insertModifiesProc(1,3);
   var.push_back(3);
   m.insertModifiesProc(1,4);
   var.push_back(4);
   m.insertModifiesProc(1,5);
   var.push_back(5);
   
   vector<int> modifiedVar = m.getModifiedVarProc(1);
   for(int i=0;i<modifiedVar.size();i++){
   CPPUNIT_ASSERT_EQUAL(var[i],modifiedVar[i]);
   }
	return;
}

//test get modifies table of procedures
void
ModifiesTest::testGetModifiesProc(){
   Modifies m;
   vector<pair<int,int>> p;

   m.insertModifiesProc(1,2);
   p.push_back(make_pair(1,2));
   m.insertModifiesProc(2,3); 
    p.push_back(make_pair(2,3));
   m.insertModifiesProc(4,4);
    p.push_back(make_pair(4,4));
   m.insertModifiesProc(3,5);
    p.push_back(make_pair(3,5));

   vector<pair<int,int>> modifiesProc = m.getModifiesProc();
   for(int i=0;i<modifiesProc.size();i++){
	   CPPUNIT_ASSERT(p[i] == modifiesProc[i]);
   }
    return;
}

//test insertion of modifies for procedures
void 
ModifiesTest::testInsertModifiesProc(){
    Modifies m;
	vector<int> var;
	
	m.insertModifiesProc(1,2);
	var.push_back(2);
	m.insertModifiesProc(1,3);
	var.push_back(3);
	vector<int> varGet = m.getModifiedVarProc(1);
	for(int i=0;i<varGet.size();i++){
	CPPUNIT_ASSERT_EQUAL(var[i],varGet[i]);
	}
	m.insertModifiesProc(1,4);
	var.push_back(4);
	for(int i=0;i<varGet.size();i++){
	CPPUNIT_ASSERT_EQUAL(var[i],varGet[i]);
	}
	//check for duplicates
	vector<pair<int,int>> modifiesTable = m.getModifiesProc();
	int tableSize = modifiesTable.size();
	CPPUNIT_ASSERT_EQUAL(3,tableSize);
	m.insertModifiesProc(1,4);
	vector<pair<int,int>> modifiesTable2 = m.getModifiesProc();
	int tableSize2 = modifiesTable2.size();
	CPPUNIT_ASSERT_EQUAL(3,tableSize2);
	return;
}

//test if modifies for procedures 
void 
ModifiesTest::testIsModifiesProc(){
	Modifies m;
	m.insertModifiesProc(1,2);
	CPPUNIT_ASSERT(m.isModifiesProc(1,2));

	return;
}
