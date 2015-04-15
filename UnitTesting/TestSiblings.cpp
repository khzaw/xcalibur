#include <cppunit/config/SourcePrefix.h>
#include "testSiblings.h"
#include "PKB\Siblings.h"

#include <iostream>
#include <string>

void 
	SiblingsTest::setUp()
{
}

void 
	SiblingsTest::tearDown()
{
}	

CPPUNIT_TEST_SUITE_REGISTRATION( SiblingsTest );

void SiblingsTest::testInsert(){
	Sibling sibling;
	sibling.insertStmtStmt(1,2);
	CPPUNIT_ASSERT(sibling.isSiblingStmtStmt(1,2)==true);
	sibling.insertVarConst(1,2);
	CPPUNIT_ASSERT(sibling.isSiblingVarConst(1,2)==true);
	sibling.inserVarStmtLst(1,3);
	CPPUNIT_ASSERT(sibling.isSiblingVarStmtLst(1,3)==true);
}

void  SiblingsTest::testGetStmtLstSiblingOfStmtLst(){
	Sibling sibling;
	sibling.insertStmtStmt(1,2);
	sibling.insertVarConst(1,2);
	sibling.inserVarStmtLst(1,3);
	sibling.insertStmtStmt(1,2);
	sibling.insertStmtStmt(4,5);
	sibling.insertStmtLstStmtLst(3,4);
	sibling.inserVarStmtLst(1,4);
	sibling.insertVarConst(2,5);
	set<int> result = sibling.getStmtLstSiblingOfStmtLst(3);
	int size = result.size();
	CPPUNIT_ASSERT_EQUAL(1, size);
	std::set<int>::iterator it = result.begin();
	CPPUNIT_ASSERT_EQUAL(4, *it);
}

void  SiblingsTest::testGetStmtSiblingOfStmt(){
	Sibling sibling;
	sibling.insertStmtStmt(1,2);
	sibling.insertVarConst(1,2);
	sibling.inserVarStmtLst(1,3);
	sibling.insertStmtStmt(1,2);
	sibling.insertStmtStmt(4,5);
	sibling.insertStmtLstStmtLst(3,4);
	sibling.inserVarStmtLst(1,4);
	sibling.insertVarConst(2,5);
	sibling.insertVarConst(1,5);
	set<int> result = sibling.getStmtSiblingOfStmt(2);
	int size = result.size();
	CPPUNIT_ASSERT_EQUAL(1, size);
	std::set<int>::iterator it = result.begin();
	CPPUNIT_ASSERT_EQUAL(2, *it);
}

void  SiblingsTest::testGetVarSiblingOfConst(){
	Sibling sibling;
	sibling.insertStmtStmt(1,2);
	sibling.insertVarConst(1,2);
	sibling.inserVarStmtLst(1,3);
	sibling.insertStmtStmt(1,2);
	sibling.insertStmtStmt(4,5);
	sibling.insertStmtLstStmtLst(3,4);
	sibling.inserVarStmtLst(1,4);
	sibling.insertVarConst(2,5);
	sibling.insertVarConst(1,5);
	set<int> result = sibling.getVarSiblingOfConst(5);
	int size = result.size();
	CPPUNIT_ASSERT_EQUAL(2, size);
	std::set<int>::iterator it = result.begin();
	CPPUNIT_ASSERT_EQUAL(1, *it);
	it++;
	CPPUNIT_ASSERT_EQUAL(2, *it);
}

void  SiblingsTest::testGetConstSiblingOfVar(){
	Sibling sibling;
	sibling.insertStmtStmt(1,2);
	sibling.insertVarConst(1,2);
	sibling.inserVarStmtLst(1,3);
	sibling.insertStmtStmt(1,2);
	sibling.insertStmtStmt(4,5);
	sibling.insertStmtLstStmtLst(3,4);
	sibling.inserVarStmtLst(1,4);
	sibling.insertVarConst(2,5);
	sibling.insertVarConst(1,5);
	set<int> result = sibling.getConstSiblingOfVar(2);
	int size = result.size();
	CPPUNIT_ASSERT_EQUAL(1, size);
	std::set<int>::iterator it = result.begin();
	CPPUNIT_ASSERT_EQUAL(5, *it);
}

void  SiblingsTest::testGetVarSiblingOfVar(){
	Sibling sibling;
	sibling.insertStmtStmt(1,2);
	sibling.insertVarConst(1,2);
	sibling.inserVarStmtLst(1,3);
	sibling.insertStmtStmt(1,2);
	sibling.insertStmtStmt(4,5);
	sibling.insertStmtLstStmtLst(3,4);
	sibling.inserVarStmtLst(1,4);
	sibling.insertVarConst(2,5);
	sibling.insertVarConst(1,5);
	set<int> result = sibling.getVarSiblingOfVar(2);
	int size = result.size();
	CPPUNIT_ASSERT_EQUAL(0, size);
}


void  SiblingsTest::testGetConstSiblingOfConst(){
	Sibling sibling;
	sibling.insertStmtStmt(1,2);
	sibling.insertVarConst(1,2);
	sibling.inserVarStmtLst(1,3);
	sibling.insertStmtStmt(1,2);
	sibling.insertStmtStmt(4,5);
	sibling.insertStmtLstStmtLst(3,4);
	sibling.inserVarStmtLst(1,4);
	sibling.insertVarConst(2,5);
	sibling.insertVarConst(1,5);
	set<int> result = sibling.getConstSiblingOfConst(5);
	int size = result.size();
	CPPUNIT_ASSERT_EQUAL(0, size);
}

void  SiblingsTest::testGetVarSiblingOfStmtLst(){
	Sibling sibling;
	sibling.insertStmtStmt(1,2);
	sibling.insertVarConst(1,2);
	sibling.inserVarStmtLst(1,3);
	sibling.insertStmtStmt(1,2);
	sibling.insertStmtStmt(4,5);
	sibling.insertStmtLstStmtLst(3,4);
	sibling.inserVarStmtLst(1,4);
	sibling.insertVarConst(2,5);
	sibling.insertVarConst(1,5);
	set<int> result = sibling.getVarSiblingOfStmtLst(3);
	int size = result.size();
	CPPUNIT_ASSERT_EQUAL(1, size);
	std::set<int>::iterator it = result.begin();
	CPPUNIT_ASSERT_EQUAL(1, *it);
}

void  SiblingsTest::testGetStmtLstSiblingOfVar(){
	Sibling sibling;
	sibling.insertStmtStmt(1,2);
	sibling.insertVarConst(1,2);
	sibling.inserVarStmtLst(1,3);
	sibling.insertStmtStmt(1,2);
	sibling.insertStmtStmt(4,5);
	sibling.insertStmtLstStmtLst(3,4);
	sibling.inserVarStmtLst(1,4);
	sibling.insertVarConst(2,5);
	sibling.insertVarConst(1,5);
	set<int> result = sibling.getStmtLstSiblingOfVar(1);
	int size = result.size();
	CPPUNIT_ASSERT_EQUAL(2, size);
	std::set<int>::iterator it = result.begin();
	CPPUNIT_ASSERT_EQUAL(3, *it);
	it++;
	CPPUNIT_ASSERT_EQUAL(4, *it);
}

void  SiblingsTest::testGetAllStmtLstSiblingOfStmtLst(){
	Sibling sibling;
	sibling.insertStmtStmt(1,2);
	sibling.insertVarConst(1,2);
	sibling.inserVarStmtLst(1,3);
	sibling.insertStmtStmt(1,2);
	sibling.insertStmtStmt(4,5);
	sibling.insertStmtLstStmtLst(3,4);
	sibling.inserVarStmtLst(1,4);
	sibling.insertVarConst(2,5);
	sibling.insertVarConst(1,5);
	set<int> result = sibling.getAllStmtLstSiblingOfStmtLst();
	int size = result.size();
	CPPUNIT_ASSERT_EQUAL(2, size);
	std::set<int>::iterator it = result.begin();
	CPPUNIT_ASSERT_EQUAL(3, *it);
	it++;
	CPPUNIT_ASSERT_EQUAL(4, *it);
}	


void  SiblingsTest::testGetAllStmtSiblingOfStmt(){
	Sibling sibling;
	sibling.insertStmtStmt(1,2);
	sibling.insertVarConst(1,2);
	sibling.inserVarStmtLst(1,3);
	sibling.insertStmtStmt(4,5);
	sibling.insertStmtLstStmtLst(3,4);
	sibling.inserVarStmtLst(1,4);
	sibling.insertVarConst(2,5);
	sibling.insertVarConst(1,5);
	set<int> result = sibling.getAllStmtSiblingOfStmt();
	int size = result.size();
	CPPUNIT_ASSERT_EQUAL(4, size);
	std::set<int>::iterator it = result.begin();
	CPPUNIT_ASSERT_EQUAL(1, *it);
	it++;
	CPPUNIT_ASSERT_EQUAL(2, *it);
	it++;
	CPPUNIT_ASSERT_EQUAL(4, *it);
	it++;
	CPPUNIT_ASSERT_EQUAL(5, *it);

}


void  SiblingsTest::testGetAllVarSiblingOfConst(){
	Sibling sibling;
	sibling.insertStmtStmt(1,2);
	sibling.insertVarConst(1,2);
	sibling.inserVarStmtLst(1,3);
	sibling.insertStmtStmt(4,5);
	sibling.insertStmtLstStmtLst(3,4);
	sibling.inserVarStmtLst(1,4);
	sibling.insertVarConst(2,5);
	sibling.insertVarConst(1,5);
	set<int> result = sibling.getAllVarSiblingOfConst();
	int size = result.size();
	CPPUNIT_ASSERT_EQUAL(2, size);
	std::set<int>::iterator it = result.begin();
	CPPUNIT_ASSERT_EQUAL(1, *it);
	it++;
	CPPUNIT_ASSERT_EQUAL(2, *it);
	it++;
}

void  SiblingsTest::testGetAllConstSiblingOfVar(){
	Sibling sibling;
	sibling.insertStmtStmt(1,2);
	sibling.insertVarConst(1,2);
	sibling.inserVarStmtLst(1,3);
	sibling.insertStmtStmt(4,5);
	sibling.insertStmtLstStmtLst(3,4);
	sibling.inserVarStmtLst(1,4);
	sibling.insertVarConst(2,5);
	sibling.insertVarConst(1,5);
	set<int> result = sibling.getAllConstSiblingOfVar();
	int size = result.size();
	CPPUNIT_ASSERT_EQUAL(2, size);
	std::set<int>::iterator it = result.begin();
	CPPUNIT_ASSERT_EQUAL(2, *it);
	it++;
	CPPUNIT_ASSERT_EQUAL(5, *it);
	it++;
}


void  SiblingsTest::testGetAllVarSiblingOfVar(){
	Sibling sibling;
	sibling.insertStmtStmt(1,2);
	sibling.insertVarConst(1,2);
	sibling.inserVarStmtLst(1,3);
	sibling.insertStmtStmt(4,5);
	sibling.insertStmtLstStmtLst(3,4);
	sibling.inserVarStmtLst(1,4);
	sibling.insertVarConst(2,5);
	sibling.insertVarConst(1,5);
	set<int> result = sibling.getAllVarSiblingOfVar();
	int size = result.size();
	CPPUNIT_ASSERT_EQUAL(0, size);
}


void  SiblingsTest::testGetAllConstSiblingOfConst(){
	Sibling sibling;
	sibling.insertStmtStmt(1,2);
	sibling.insertVarConst(1,2);
	sibling.inserVarStmtLst(1,3);
	sibling.insertStmtStmt(4,5);
	sibling.insertStmtLstStmtLst(3,4);
	sibling.inserVarStmtLst(1,4);
	sibling.insertVarConst(2,5);
	sibling.insertVarConst(1,5);
	set<int> result = sibling.getAllConstSiblingOfConst();
	int size = result.size();
	CPPUNIT_ASSERT_EQUAL(0, size);
}	


void  SiblingsTest::testGetAllVarSiblingOfStmtLst(){
	Sibling sibling;
	sibling.insertStmtStmt(1,2);
	sibling.insertVarConst(1,2);
	sibling.inserVarStmtLst(1,3);
	sibling.insertStmtStmt(4,5);
	sibling.insertStmtLstStmtLst(3,4);
	sibling.inserVarStmtLst(1,4);
	sibling.insertVarConst(2,5);
	sibling.insertVarConst(1,5);
	set<int> result = sibling.getAllVarSiblingOfStmtLst();
	int size = result.size();
	CPPUNIT_ASSERT_EQUAL(1, size);
	std::set<int>::iterator it = result.begin();
	CPPUNIT_ASSERT_EQUAL(1, *it);
}


void  SiblingsTest::testGetAllStmtLstSiblingOfVar(){
	Sibling sibling;
	sibling.insertStmtStmt(1,2);
	sibling.insertVarConst(1,2);
	sibling.inserVarStmtLst(1,3);
	sibling.insertStmtStmt(4,5);
	sibling.insertStmtLstStmtLst(3,4);
	sibling.inserVarStmtLst(1,4);
	sibling.insertVarConst(2,5);
	sibling.insertVarConst(1,5);
	set<int> result = sibling.getAllStmtLstSiblingOfVar();
	int size = result.size();
	CPPUNIT_ASSERT_EQUAL(2, size);
	std::set<int>::iterator it = result.begin();
	CPPUNIT_ASSERT_EQUAL(3, *it);
	it++;
	CPPUNIT_ASSERT_EQUAL(4,*it);
}

//boolean functions

void  SiblingsTest::testIsSiblingVarVar(){
	Sibling sibling;
	sibling.insertStmtStmt(1,2);
	sibling.insertVarConst(1,2);
	sibling.inserVarStmtLst(1,3);
	sibling.insertStmtStmt(4,5);
	sibling.insertStmtLstStmtLst(3,4);
	sibling.inserVarStmtLst(1,4);
	sibling.insertVarConst(2,5);
	sibling.insertVarConst(1,5);
	bool result = sibling.isSiblingVarVar(1,2);
	CPPUNIT_ASSERT(false,result);
}

void SiblingsTest::testIsSiblingStmtLstStmtLst(){
	Sibling sibling;
	sibling.insertStmtStmt(1,2);
	sibling.insertVarConst(1,2);
	sibling.inserVarStmtLst(1,3);
	sibling.insertStmtStmt(4,5);
	sibling.insertStmtLstStmtLst(3,4);
	sibling.inserVarStmtLst(1,4);
	sibling.insertVarConst(2,5);
	sibling.insertVarConst(1,5);
	bool result = sibling.isSiblingStmtLstStmtLst(3,4);
	CPPUNIT_ASSERT(true,result);
}

void SiblingsTest::testIsSiblingStmtStmt(){
	Sibling sibling;
	sibling.insertStmtStmt(1,2);
	sibling.insertVarConst(1,2);
	sibling.inserVarStmtLst(1,3);
	sibling.insertStmtStmt(4,5);
	sibling.insertStmtLstStmtLst(3,4);
	sibling.inserVarStmtLst(1,4);
	sibling.insertVarConst(2,5);
	sibling.insertVarConst(1,5);
	bool result = sibling.isSiblingStmtStmt(1,2);
	CPPUNIT_ASSERT(true,result);
}

void SiblingsTest::testIsSiblingVarStmtLst(){
	Sibling sibling;
	sibling.insertStmtStmt(1,2);
	sibling.insertVarConst(1,2);
	sibling.inserVarStmtLst(1,3);
	sibling.insertStmtStmt(4,5);
	sibling.insertStmtLstStmtLst(3,4);
	sibling.inserVarStmtLst(1,4);
	sibling.insertVarConst(2,5);
	sibling.insertVarConst(1,5);
	bool result = sibling.isSiblingVarStmtLst(1,4);
	CPPUNIT_ASSERT(true,result);
}

void SiblingsTest::testIsSiblingVarConst(){
	Sibling sibling;
	sibling.insertStmtStmt(1,2);
	sibling.insertVarConst(1,2);
	sibling.inserVarStmtLst(1,3);
	sibling.insertStmtStmt(4,5);
	sibling.insertStmtLstStmtLst(3,4);
	sibling.inserVarStmtLst(1,4);
	sibling.insertVarConst(2,5);
	sibling.insertVarConst(1,5);
	bool result = sibling.isSiblingVarConst(2,5);
	CPPUNIT_ASSERT(true,result);
	result = sibling.isSiblingVarConst(1,3);
	CPPUNIT_ASSERT(false,result);
}

void SiblingsTest::testIsSiblingConstConst(){
	Sibling sibling;
	sibling.insertStmtStmt(1,2);
	sibling.insertVarConst(1,2);
	sibling.inserVarStmtLst(1,3);
	sibling.insertStmtStmt(4,5);
	sibling.insertStmtLstStmtLst(3,4);
	sibling.inserVarStmtLst(1,4);
	sibling.insertVarConst(2,5);
	sibling.insertVarConst(1,5);
	bool result = sibling.isSiblingConstConst(1,2);
	CPPUNIT_ASSERT(false,result);
}




