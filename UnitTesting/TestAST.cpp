#include "AST.h"
#include "TestAST.h"
#include <iostream>

void TestAST::setUp() {
}

void TestAST::tearDown() {
}

void TestAST::testMatchPattern() {
	string nodePattern, queryPattern;

	nodePattern = "x y + z + a + b +";
	queryPattern = "x y +";
	CPPUNIT_ASSERT_EQUAL(true, AST::matchPattern(nodePattern, queryPattern, 2));

	queryPattern = "z a +";
	CPPUNIT_ASSERT_EQUAL(false, AST::matchPattern(nodePattern, queryPattern, 2));

	queryPattern = "a";
	CPPUNIT_ASSERT_EQUAL(true, AST::matchPattern(nodePattern, queryPattern, 1));


	nodePattern = "OsCar bravo + mother + father + 134 +";
	queryPattern = "mother father +";
	CPPUNIT_ASSERT_EQUAL(false, AST::matchPattern(nodePattern, queryPattern, 2));

	queryPattern = "bravo";
	CPPUNIT_ASSERT_EQUAL(true, AST::matchPattern(nodePattern, queryPattern, 1));

}

CPPUNIT_TEST_SUITE_REGISTRATION(TestAST);