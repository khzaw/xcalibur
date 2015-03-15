#include <cppunit/config/SourcePrefix.h>
#include "TestNewQueryParser.h"
#include "QueryProcessor\NewQueryParser.h"
#include "QueryProcessor\ModifiesSubquery.cpp"
#include "PKB\PKBController.h"

#include <iostream>
#include <string>

void NewQueryParserTest::setUp() {
}

void NewQueryParserTest::tearDown() {
}

CPPUNIT_TEST_SUITE_REGISTRATION(NewQueryParserTest);

void NewQueryParserTest::testModifiesSubquery() {
	string query;
	NewQueryParser* parser;
	PKBController* controller;
	map<string, string> synonyms;

	query = "if a; variable f,g; constant b, c; prog_line h; Select BOOLEAN";
	parser = new NewQueryParser(query, controller);
	synonyms = parser->getSynonyms();
	CPPUNIT_ASSERT(synonyms.at("a") == "if");
	CPPUNIT_ASSERT(synonyms.at("f") == "variable");
	CPPUNIT_ASSERT(synonyms.at("g") == "variable");
	CPPUNIT_ASSERT(synonyms.at("b") == "contstant");
	CPPUNIT_ASSERT(synonyms.at("c") == "prog_line");
}
