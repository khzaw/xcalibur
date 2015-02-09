#include <cppunit/config/SourcePrefix.h>
#include "testConstant.h"
#include "SPA/PKB/ConstantTable.h"

#include <iostream>
#include <string>

void 
ConstantTest::setUp()
{
}

void 
ConstantTest::tearDown()
{
}

CPPUNIT_TEST_SUITE_REGISTRATION( ConstantTest );

// method to test insertion of procedures
void 
ConstantTest::testInsert(){
	//inserting non duplicates procedures
	ConstantTable c;
	c.insertConst(1);
	c.insertConst(2);
	c.insertConst(3);
    CPPUNIT_ASSERT_EQUAL(1, c.getConstant(0));
	CPPUNIT_ASSERT_EQUAL(2, c.getConstant(1));
	CPPUNIT_ASSERT_EQUAL(3, c.getConstant(2));
	//inserting duplicate constant
	//size before inserting
	CPPUNIT_ASSERT_EQUAL(3,c.getSize());
	c.insertConst(4);
	//size of proctable remains unchanged. duplicate is not inserted
	CPPUNIT_ASSERT_EQUAL(4,c.getSize());
	return;
}




// method to test get constant using its index
void 
ConstantTest::testGetConstant(){
	ConstantTable c;
	c.insertConst(1);
	c.insertConst(2);
	c.insertConst(3);
	CPPUNIT_ASSERT_EQUAL(1, c.getConstant(0));
	CPPUNIT_ASSERT_EQUAL(2, c.getConstant(1));
	CPPUNIT_ASSERT_EQUAL(3, c.getConstant(2));
	return;
}

void 
ConstantTest::testGetConstantIndex(){
	ConstantTable c;
	c.insertConst(1);
	c.insertConst(2);
	c.insertConst(3);
	CPPUNIT_ASSERT_EQUAL(0, c.getConstIndex(1));
	CPPUNIT_ASSERT_EQUAL(1, c.getConstIndex(2));
	CPPUNIT_ASSERT_EQUAL(2, c.getConstIndex(3));
	return;
}


// method to test the retrieval of constant table
void 
ConstantTest::testGetAllConstant(){
	ConstantTable c;
	c.insertConst(1);
	c.insertConst(2);
	c.insertConst(3);
	vector<int> constants = c.getAllConstant();
	CPPUNIT_ASSERT_EQUAL(1, constants[0]);
	CPPUNIT_ASSERT_EQUAL(2, constants[1]);
    CPPUNIT_ASSERT_EQUAL(3, constants[2]);
	return;
}

// method to test the checking of var table to see if it contains the specified constant
void
ConstantTest::testIfContainsConst(){
    ConstantTable c;
	c.insertConst(1);
	c.insertConst(2);
	c.insertConst(3);
	CPPUNIT_ASSERT(c.containsConst(1));
    CPPUNIT_ASSERT(c.containsConst(2));
    CPPUNIT_ASSERT(c.containsConst(3));
	return;
}

