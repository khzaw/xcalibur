#include <cppunit/config/SourcePrefix.h>
#include "TestUses.h"
#include "PKB\Uses.h"

#include <utility>
#include <vector>
#include <iostream>
#include <string>
#include <set>
#include "PKB\UsesExtractor.h"

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
   set<int> stmt;
   m.insertUsesStmt(1,2);
   stmt.insert(1);
   m.insertUsesStmt(2,2);
   stmt.insert(2);
   m.insertUsesStmt(4,2);
   stmt.insert(4);
   m.insertUsesStmt(3,2);
   UsesExtractor extractor(&m);
	extractor.construct();
   stmt.insert(3);
   set<int> users = m.getUsersStmt(2);
   std::set<int>::iterator itr1 = users.begin();
   std::set<int>::iterator itr2 = stmt.begin();
   for(int i=0;i<users.size();i++){
   CPPUNIT_ASSERT_EQUAL(*itr1,*itr2);
   itr1++;
   itr2++;
   }
	return;
}

//test get modified variables of statements
void 
UsesTest::testGetUsedVarStmt(){
 Uses m;
   set<int> var;
   m.insertUsesStmt(1,2);
   var.insert(2);
   m.insertUsesStmt(1,3);
   var.insert(3);
   m.insertUsesStmt(1,4);
   var.insert(4);
   m.insertUsesStmt(1,5);
   var.insert(5);
   UsesExtractor extractor(&m);
	extractor.construct();
   set<int> usedVar = m.getUsedVarStmt(1);
   std::set<int>::iterator itr1 = usedVar.begin();
   std::set<int>::iterator itr2 = var.begin();
   for(int i=0;i<usedVar.size();i++){
   CPPUNIT_ASSERT_EQUAL(*itr1,*itr2);
   itr1++;
   itr2++;
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
	UsesExtractor extractor(&m);
	extractor.construct();
   vector<pair<int,int>> usesStmt = m.getUsesStmt();
   for(int i=0;i<usesStmt.size();i++){
	   CPPUNIT_ASSERT(p[i] == usesStmt[i]);
   }
    return;
}

//test insertion of uses for statement
void 
UsesTest::testInsertUsesStmt(){
    Uses m;
	set<int> var;
	
	m.insertUsesStmt(1,2);
	var.insert(2);
	m.insertUsesStmt(1,3);
	UsesExtractor extractor(&m);
	extractor.construct();
	var.insert(3);
	set<int> varGet = m.getUsedVarStmt(1);
	std::set<int>::iterator itr1 = var.begin();
	std::set<int>::iterator itr2 = varGet.begin();
	for(int i=0;i<varGet.size();i++){
	CPPUNIT_ASSERT_EQUAL(*itr1,*itr2);
	itr1++;
	itr2++;
	}
	m.insertUsesStmt(1,4);
	extractor.construct();
	var.insert(4);
	varGet = m.getUsedVarStmt(1);
	itr1 = var.begin();
	itr2 = varGet.begin();
	for(int i=0;i<varGet.size();i++){
	CPPUNIT_ASSERT_EQUAL(*itr1,*itr2);
	itr1++;
	itr2++;
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
	UsesExtractor extractor(&m);
	extractor.construct();
	CPPUNIT_ASSERT(m.isUsesStmt(1,2));

	return;
}

//Procedure
//test get procedures that modified var
void 
UsesTest::testGetUsersProc(){
   Uses m;
   set<int> proc;
   m.insertUsesProc(1,2);
   proc.insert(1);
   m.insertUsesProc(2,2);
   proc.insert(2);
   m.insertUsesProc(4,2);
   proc.insert(4);
   m.insertUsesProc(3,2);
   proc.insert(3);
   UsesExtractor extractor(&m);
	extractor.construct();
   set<int> users = m.getUsersProc(2);
   std::set<int>::iterator itr1 = users.begin();
   std::set<int>::iterator itr2 = proc.begin();
   for(int i=0;i<users.size();i++){
   CPPUNIT_ASSERT_EQUAL(*itr1,*itr2);
   itr1++;
   itr2++;
   }
	return;
}

//test get modified variables of procedures
void 
UsesTest::testGetUsedVarProc(){
   Uses m;
   set<int> var;
   m.insertUsesProc(1,2);
   var.insert(2);
   m.insertUsesProc(1,3);
   var.insert(3);
   m.insertUsesProc(1,4);
   var.insert(4);
   m.insertUsesProc(1,5);
   var.insert(5);
   UsesExtractor extractor(&m);
	extractor.construct();
   set<int> usedVar = m.getUsedVarProc(1);
   std::set<int>::iterator itr1 = usedVar.begin();
   std::set<int>::iterator itr2 = var.begin();
   for(int i=0;i<usedVar.size();i++){
   CPPUNIT_ASSERT_EQUAL(*itr1,*itr2);
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
	UsesExtractor extractor(&m);
	extractor.construct();
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
	set<int> var;
	m.insertUsesProc(1,2);
	var.insert(2);
	m.insertUsesProc(1,3);
	var.insert(3);
	UsesExtractor extractor(&m);
	extractor.construct();
	set<int> varGet = m.getUsedVarProc(1);
	std::set<int>::iterator itr1 = var.begin();
	std::set<int>::iterator itr2 = varGet.begin();
	for(int i=0;i<varGet.size();i++){
	CPPUNIT_ASSERT_EQUAL(*itr1,*itr2);
	itr1++;
	itr2++;
	}
	m.insertUsesProc(1,4);
	extractor.construct();
	var.insert(4);
	for(int i=0;i<varGet.size();i++){
	CPPUNIT_ASSERT_EQUAL(*itr1,*itr2);
	itr1++;
	itr2++;
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
	UsesExtractor extractor(&m);
	extractor.construct();
	CPPUNIT_ASSERT(m.isUsesProc(1,2));
	return;
}

//test if uses for statement 
void
UsesTest::testEvaluateIsUsesStmt(){
	Uses m;
	m.insertUsesStmt(1,2);
	UsesExtractor extractor(&m);
	extractor.construct();
	CPPUNIT_ASSERT(m.evaluateIsUsesStmt(1,2));

	return;
}

//test get statements that used var
void UsesTest::testEvaluateGetUsersStmt(){
   Uses m;
   set<int> stmt;
   m.insertUsesStmt(1,2);
   stmt.insert(1);
   m.insertUsesStmt(2,2);
   stmt.insert(2);
   m.insertUsesStmt(4,2);
   stmt.insert(4);
   m.insertUsesStmt(3,2);
   stmt.insert(3);
   UsesExtractor extractor(&m);
   extractor.construct();
   set<int> users = m.evaluateGetUsersStmt(2);
   std::set<int>::iterator itr1 = users.begin();
   std::set<int>::iterator itr2 = stmt.begin();
   for(int i=0;i<users.size();i++){
   CPPUNIT_ASSERT_EQUAL(*itr1,*itr2);
   itr1++;
   itr2++;
   }
	return;
}

//test get used variables of statements
void UsesTest::testEvaluateGetUsedVarStmt(){
	Uses m;
   set<int> var;
   m.insertUsesStmt(1,2);
   var.insert(2);
   m.insertUsesStmt(1,3);
   var.insert(3);
   m.insertUsesStmt(1,4);
   var.insert(4);
   m.insertUsesStmt(1,5);
   var.insert(5);
   UsesExtractor extractor(&m);
	extractor.construct();
   set<int> usedVar = m.evaluateGetUsedVarStmt(1);
   std::set<int>::iterator itr1 = usedVar.begin();
   std::set<int>::iterator itr2 = var.begin();
   for(int i=0;i<usedVar.size();i++){
   CPPUNIT_ASSERT_EQUAL(*itr1,*itr2);
   itr1++;
   itr2++;
   }
	return;
}

//test if uses for procedures
void  UsesTest::testEvaluateIsUsesProc(){
	Uses m;
	m.insertUsesProc(1,2);
	UsesExtractor extractor(&m);
	extractor.construct();
	CPPUNIT_ASSERT(m.evaluateIsUsesProc(1,2));
	return;
}

//test get procedures that used var
void  UsesTest::testEvaluateGetUsersProc(){
   Uses m;
   set<int> proc;
   m.insertUsesProc(1,2);
   proc.insert(1);
   m.insertUsesProc(2,2);
   proc.insert(2);
   m.insertUsesProc(4,2);
   proc.insert(4);
   m.insertUsesProc(3,2);
   proc.insert(3);
   UsesExtractor extractor(&m);
	extractor.construct();
   set<int> users = m.evaluateGetUsersProc(2);
   std::set<int>::iterator itr1 = users.begin();
   std::set<int>::iterator itr2 = proc.begin();
   for(int i=0;i<users.size();i++){
   CPPUNIT_ASSERT_EQUAL(*itr1,*itr2);
   itr1++;
   itr2++;
   }
	return;
}

//test get used variables of procedures
void  UsesTest::testEvaluateGetUsedVarProc(){
   Uses m;
   set<int> var;
   m.insertUsesProc(1,2);
   var.insert(2);
   m.insertUsesProc(1,3);
   var.insert(3);
   m.insertUsesProc(1,4);
   var.insert(4);
   m.insertUsesProc(1,5);
   var.insert(5);
   UsesExtractor extractor(&m);
   extractor.construct();
   set<int> usedVar = m.evaluateGetUsedVarProc(1);
   std::set<int>::iterator itr1 = usedVar.begin();
   std::set<int>::iterator itr2 = var.begin();
   for(int i=0;i<usedVar.size();i++){
   CPPUNIT_ASSERT_EQUAL(*itr1,*itr2);
   }
   return;
}
