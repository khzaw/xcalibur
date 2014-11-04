#include "TestParser.h"
#include "Parser.h"
#include <cppunit/config/SourcePrefix.h>

void TestParser::setUp() {
}

void TestParser::tearDown() {
}

void TestParser::testTotalStatementNumber() {
	Parser parser("Sample-Source.txt");
	CPPUNIT_ASSERT_EQUAL(parser.getTotalStatementNumber(),  20);
}

CPPUNIT_TEST_SUITE_REGISTRATION(TestParser);