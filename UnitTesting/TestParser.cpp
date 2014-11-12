#include "TestParser.h"
#include "Parser.h"
#include <cppunit/config/SourcePrefix.h>

//Parser empty("../Debug/empty.txt");
Parser sample("../Debug/Sample-Source.txt");
//Parser sample("../Debug/Source2.txt");

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
	CPPUNIT_ASSERT_EQUAL(20, sample.controller.parentTable.getSize());
}

void TestParser::testTotalModifies() {
	CPPUNIT_ASSERT_EQUAL(39, sample.controller.modifiesTable.getSizeStmtModifies());
	CPPUNIT_ASSERT_EQUAL(20, sample.controller.modifiesTable.getSizeProcModifies());
}

void TestParser::testTotalUses() {
	CPPUNIT_ASSERT_EQUAL(73, sample.controller.usesTable.getSizeStmtUses());
	CPPUNIT_ASSERT_EQUAL(16, sample.controller.usesTable.getSizeProcUses());
}

CPPUNIT_TEST_SUITE_REGISTRATION(TestParser);