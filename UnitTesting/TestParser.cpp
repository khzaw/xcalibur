#include "TestParser.h"
#include "Parser.h"
#include <cppunit/config/SourcePrefix.h>

//Parser empty("../Debug/empty.txt");
Parser sample("../Debug/Sample-Source.txt");
//Parser two("../Debug/Source2.txt");

void TestParser::setUp() {
}

void TestParser::tearDown() {
}

void TestParser::testTotalStatementNumber() {
	CPPUNIT_ASSERT_EQUAL(20, sample.getTotalStatementNumber());
	//CPPUNIT_ASSERT_EQUAL(20, two.getTotalStatementNumber());
}

void TestParser::testTotalFollows() {
	CPPUNIT_ASSERT_EQUAL(12, sample.controller.followsTable.getSize());
	//CPPUNIT_ASSERT_EQUAL(12, two.controller.followsTable.getSize());
}

void TestParser::testTotalParents() {
	CPPUNIT_ASSERT_EQUAL(13, sample.controller.parentTable.getSize());
}

void TestParser::testTotalModifies() {
	CPPUNIT_ASSERT_EQUAL(35, sample.controller.modifiesTable.getSizeStmtModifies());
	CPPUNIT_ASSERT_EQUAL(13, sample.controller.modifiesTable.getSizeProcModifies());
}

CPPUNIT_TEST_SUITE_REGISTRATION(TestParser);