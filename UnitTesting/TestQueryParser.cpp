#include <cppunit/config/SourcePrefix.h>
#include "TestQueryParser.h"
#include "QueryParser.h"

#include <iostream>
#include <string>

void QueryParserTest::setUp() {}
void QueryParserTest::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(QueryParserTest);

// Test synonym declarations
void QueryParserTest::testSynonym() {
	string q1 = "while a; select a";
	QueryParser* a = new QueryParser(q1);
	map<string, string> syn = a->getSynonyms();

	q1 = "while b, c, d; select b";
	a = new QueryParser(q1);
	map<string, string> syn = a->getSynonyms();

	q1 = "assign e; select e";
	a = new QueryParser(q1);
	map<string, string> syn = a->getSynonyms();

	q1 = "assign e, f, g ; select a";
	a = new QueryParser(q1);
	map<string, string> syn = a->getSynonyms();
}