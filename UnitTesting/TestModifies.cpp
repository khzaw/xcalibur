#include <cppunit/config/SourcePrefix.h>
#include "TestModifies.h"
#include <Modifies.h>

#include <utility>
#include <vector>
#include <iostream>
#include <string>
#include <set>
#include "ModifiesExtractor.h"

void 
ModifiesTest::setUp()
{

}

void 
ModifiesTest::tearDown()
{
}

CPPUNIT_TEST_SUITE_REGISTRATION( ModifiesTest );

//test get statements that modify variables
void 
ModifiesTest::testGetModifiersStmt(){
   Modifies m;
   set<int> stmt;
   m.insertModifiesStmt(1,2);
   stmt.insert(1);
   m.insertModifiesStmt(2,2);
   stmt.insert(2);
   m.insertModifiesStmt(4,2);
   stmt.insert(4);
   m.insertModifiesStmt(3,2);
   stmt.insert(3);
   
   set<int> modifiers = m.evaluateGetModifiersStmt(2);
   std::set<int>::iterator itr1 = modifiers.begin();
   std::set<int>::iterator itr2 = stmt.begin();
   for(int i=0;i<modifiers.size();i++){
   CPPUNIT_ASSERT_EQUAL(*itr1,*itr2);
   itr1++;
   itr2++;
   }
	return;
}


//test get modified variables of statements
void 
ModifiesTest::testGetModifiedVarStmt(){
 Modifies m;
   set<int> var;
   m.insertModifiesStmt(1,2);
   var.insert(2);
   m.insertModifiesStmt(1,3);
   var.insert(3);
   m.insertModifiesStmt(1,4);
   var.insert(4);
   m.insertModifiesStmt(1,5);
   var.insert(5);
   
   set<int> modifiedVar = m.getModifiedVarStmt(1);
   std::set<int>::iterator itr1= modifiedVar.begin();
   std::set<int>::iterator itr2 = var.begin();
   CPPUNIT_ASSERT_EQUAL(var.size(), modifiedVar.size());
   for(int i=0;i<modifiedVar.size();i++){
   CPPUNIT_ASSERT_EQUAL(*itr1, *itr2);
   itr1++;
   itr2++;
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
	set<int> var;
	m.insertModifiesStmt(1,2);
	var.insert(2);
	m.insertModifiesStmt(1,3);
	var.insert(3);
	set<int> varGet = m.getModifiedVarStmt(1);
	std::set<int>::iterator itr1 = varGet.begin();
	std::set<int>::iterator itr2 = var.begin();
	for(int i=0;i<varGet.size();i++){
	CPPUNIT_ASSERT_EQUAL(*itr1,*itr2);
	itr1++;
	itr2++;
	}
	m.insertModifiesStmt(1,4);
	var.insert(4);
	varGet = m.getModifiedVarStmt();
	itr1 = varGet.begin();
	itr2 = var.begin();
	for(int i=0;i<varGet.size();i++){
	CPPUNIT_ASSERT_EQUAL(*itr1,*itr2);
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
   set<int> proc;
   m.insertModifiesProc(1,2);
   proc.insert(1);
   m.insertModifiesProc(2,2);
   proc.insert(2);
   m.insertModifiesProc(4,2);
   proc.insert(4);
   m.insertModifiesProc(3,2);
   proc.insert(3);
   
   set<int> modifiers = m.getModifiersProc(2);
   std::set<int>::iterator itr1 = modifiers.begin();
   std::set<int>::iterator itr2 = proc.begin();
   for(int i=0;i<modifiers.size();i++){
   CPPUNIT_ASSERT_EQUAL(*itr1,*itr2);
   itr1++;
   itr2++;
   }
	return;
}

//test get modified variables of procedures
void 
ModifiesTest::testGetModifiedVarProc(){
 Modifies m;
   set<int> var;
   m.insertModifiesProc(1,2);
   var.insert(2);
   m.insertModifiesProc(1,3);
   var.insert(3);
   m.insertModifiesProc(1,4);
   var.insert(4);
   m.insertModifiesProc(1,5);
   var.insert(5);
   
   set<int> modifiedVar = m.getModifiedVarProc(1);
   std::set<int>::iterator itr1 = modifiedVar.begin();
   std::set<int>::iterator itr2 = var.begin();
   for(int i=0;i<modifiedVar.size();i++){
   CPPUNIT_ASSERT_EQUAL(*itr1,*itr2);
   itr1++;
   itr2++;
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
	set<int> var;
	
	m.insertModifiesProc(1,2);
	var.insert(2);
	m.insertModifiesProc(1,3);
	var.insert(3);
	set<int> varGet = m.getModifiedVarProc(1);
	std::set<int>::iterator itr1 = varGet.begin();
	std::set<int>::iterator itr2 = var.begin();
	for(int i=0;i<varGet.size();i++){
	CPPUNIT_ASSERT_EQUAL(*itr1,*itr2);
	itr1++;
	itr2++;
	}
	m.insertModifiesProc(1,4);
	var.insert(4);
	varGet = m.getModifiedVarProc(1);
	itr1 = varGet.begin();
	itr2 = var.begin();
	for(int i=0;i<varGet.size();i++){
	CPPUNIT_ASSERT_EQUAL(*itr1,*itr2);
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

// test if modifies for statements
void ModifiesTest::testEvaluateIsModifiesStmt(){
	Modifies m;
	m.insertModifiesStmt(1,2);
	ModifiesExtractor extractor(&m);
	extractor.construct();
	CPPUNIT_ASSERT(m.evaluateIsModifiesStmt(1,2));
	return;
}

// test if modifies for procedures
void ModifiesTest::testEvaluateIsModifiesProc(){
	Modifies m;
	m.insertModifiesProc(1,2);
	ModifiesExtractor extractor(&m);
	extractor.construct();
	CPPUNIT_ASSERT(m.evaluateIsModifiesProc(1,2));
	return;
}

// test get statements that modify variables
void ModifiesTest::testEvaluateGetModifiersStmt(){
   Modifies m;
   set<int> stmt;
   m.insertModifiesStmt(1,2);
   stmt.insert(1);
   m.insertModifiesStmt(2,2);
   stmt.insert(2);
   m.insertModifiesStmt(4,2);
   stmt.insert(4);
   m.insertModifiesStmt(3,2);
   stmt.insert(3);
   ModifiesExtractor extractor(&m);
   extractor.construct();
   set<int> modifiers = m.evaluateGetModifiersStmt(2);
   std::set<int>::iterator itr1 = modifiers.begin();
   std::set<int>::iterator itr2 = stmt.begin();
   for(int i=0;i<modifiers.size();i++){
   CPPUNIT_ASSERT_EQUAL(*itr1,*itr2);
   ++itr1;
   ++itr2;
   }
	return;
}

//test get modified var for statement
void 
ModifiesTest::testGetModifiedVarStmt(){
 Modifies m;
   set<int> var;
   m.insertModifiesStmt(1,2);
   var.insert(2);
   m.insertModifiesStmt(1,3);
   var.insert(3);
   m.insertModifiesStmt(1,4);
   var.insert(4);
   m.insertModifiesStmt(1,5);
   var.insert(5);
   ModifiesExtractor extractor(&m);
   extractor.construct();
   set<int> modifiedVar = m.getModifiedVarStmt(1);
   std::set<int>::iterator itr1= modifiedVar.begin();
   std::set<int>::iterator itr2 = var.begin();
   CPPUNIT_ASSERT_EQUAL(var.size(), modifiedVar.size());
   for(int i=0;i<modifiedVar.size();i++){
   CPPUNIT_ASSERT_EQUAL(*itr1, *itr2);
   itr1++;
   itr2++;
   }
	return;
}


//test get procedures that modified var
void 
ModifiesTest::testEvaluateGetModifiersProc(){
   Modifies m;
   set<int> proc;
   m.insertModifiesProc(1,2);
   proc.insert(1);
   m.insertModifiesProc(2,2);
   proc.insert(2);
   m.insertModifiesProc(4,2);
   proc.insert(4);
   m.insertModifiesProc(3,2);
   proc.insert(3);
   
   set<int> modifiers = m.evaluateGetModifiersProc(2);
   std::set<int>::iterator itr1 = modifiers.begin();
   std::set<int>::iterator itr2 = proc.begin();
   for(int i=0;i<modifiers.size();i++){
   CPPUNIT_ASSERT_EQUAL(*itr1,*itr2);
   itr1++;
   itr2++;
   }
	return;
}

//test get modified variables of procedures
void 
ModifiesTest::testEvaluateGetModifiedVarProc(){
 Modifies m;
   set<int> var;
   m.insertModifiesProc(1,2);
   var.insert(2);
   m.insertModifiesProc(1,3);
   var.insert(3);
   m.insertModifiesProc(1,4);
   var.insert(4);
   m.insertModifiesProc(1,5);
   var.insert(5);
   
   set<int> modifiedVar = m.evaluateGetModifiedVarProc(1);
   std::set<int>::iterator itr1 = modifiedVar.begin();
   std::set<int>::iterator itr2 = var.begin();
   for(int i=0;i<modifiedVar.size();i++){
   CPPUNIT_ASSERT_EQUAL(*itr1,*itr2);
   itr1++;
   itr2++;
   }
	return;
}