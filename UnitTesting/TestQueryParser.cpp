#include <cppunit/config/SourcePrefix.h>
#include "TestQueryParser.h"
#include "QueryParser.h"
#include "QueryTree.h"
#include "QTNode.h"

#include <iostream>
#include <string>

void QueryParserTest::setUp() {}
void QueryParserTest::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(QueryParserTest);

// Test synonym declarations
void QueryParserTest::testSynonym() {
	string q1;
	QueryParser* a;
	map<string, string> synonyms;
	
	q1 = "while a; select a";
	a = new QueryParser(q1);
	synonyms = a->getSynonyms();	
	CPPUNIT_ASSERT(synonyms.at("a") == "while");

	q1 = "procedure b, c, d; select b";
	a = new QueryParser(q1);
	synonyms = a->getSynonyms();
	CPPUNIT_ASSERT(synonyms.at("b") == "procedure");
	CPPUNIT_ASSERT(synonyms.at("c") == "procedure");
	CPPUNIT_ASSERT(synonyms.at("d") == "procedure");

	q1 = "stmtLst e; select e";
	a = new QueryParser(q1);
	synonyms = a->getSynonyms();
	CPPUNIT_ASSERT(synonyms.at("e") == "stmtLst");

	q1 = "assign f, g, h ; select f";
	a = new QueryParser(q1);
	synonyms = a->getSynonyms();
	CPPUNIT_ASSERT(synonyms.at("f") == "assign");
	CPPUNIT_ASSERT(synonyms.at("g") == "assign");
	CPPUNIT_ASSERT(synonyms.at("h") == "assign");

	q1 = "while a, b, c; call f, g, h ; select f";
	a = new QueryParser(q1);
	synonyms = a->getSynonyms();
	CPPUNIT_ASSERT(synonyms.at("a") == "while");
	CPPUNIT_ASSERT(synonyms.at("b") == "while");
	CPPUNIT_ASSERT(synonyms.at("c") == "while");
	CPPUNIT_ASSERT(synonyms.at("f") == "call");
	CPPUNIT_ASSERT(synonyms.at("g") == "call");
	CPPUNIT_ASSERT(synonyms.at("h") == "call");

	q1 = "if a; variable f,g; constant b, c; prog_line h; select f";
	a = new QueryParser(q1);
	synonyms = a->getSynonyms();
	CPPUNIT_ASSERT(synonyms.at("a") == "if");
	CPPUNIT_ASSERT(synonyms.at("b") == "constant");
	CPPUNIT_ASSERT(synonyms.at("c") == "constant");
	CPPUNIT_ASSERT(synonyms.at("f") == "variable");
	CPPUNIT_ASSERT(synonyms.at("g") == "variable");
	CPPUNIT_ASSERT(synonyms.at("h") == "prog_line");
}

void QueryParserTest::testSuchThat() {
	string q;
	QueryParser* qp;
	QTNode* qt;

	q = "while a; select a";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(0);
	CPPUNIT_ASSERT(qt->getNumChild() == 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "a");

	q = "constant a, d; stmt b, c; select <a, b, c, d>";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(0);
	CPPUNIT_ASSERT(qt->getNumChild() == 4);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(1)->getKey() == "b");
	CPPUNIT_ASSERT(qt->getChild(2)->getKey() == "c");
	CPPUNIT_ASSERT(qt->getChild(3)->getKey() == "d");


	q = "while a; assign b; select BOOLEAN";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(0);
	CPPUNIT_ASSERT(qt->getNumChild() == 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "BOOLEAN");
}

void QueryParserTest::testModifies() {
	string q;
	QueryParser* qp;
	QTNode* qt;
	//ent, var
	q = "while a; variable b; select a such that Modifies(a, b)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT(qt->getNumChild() == 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Modifies");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "b");

	q = "while a; variable b; select a such that Modifies(1, \"x\")";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT(qt->getNumChild() == 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Modifies");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getValue() == 1);
	cout << "Child:" << qt->getChild(0)->getChild(1)->getKey() << endl;
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "\"x\"");
	

	//stmt, var
}

void QueryParserTest::testFollows() {
	string q;
	QueryParser* qp;
	QTNode* qt;
	
	q = "while a; select a such that follows(1, 2)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Follows");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getValue() == 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getValue() == 2);

	q = "while a; select a such that FOLLOWS(a, 2)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Follows");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getValue() == 2);

	q = "while a; select a such that foLLows(1, a)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Follows");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getValue() == 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "a");

	q = "while a; select a such that Follows(a, a)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Follows");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "a");
	
	// Follows *
	q = "while a; select a such that follows*(1, 2)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Follows*");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getValue() == 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getValue() == 2);

	q = "while a; select a such that FOLLOWS*(a, 2)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Follows*");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getValue() == 2);

	q = "while a; select a such that foLLows*(1, a)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Follows*");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getValue() == 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "a");

	q = "while a; select a such that Follows*(a, a)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Follows*");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "a");
	
	// Multiple Follows/Follows*
	q = "while a; select a such that Follows(10, a) and Follows*(b, c)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Follows");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getValue() == 10);
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(1)->getKey() == "Follows*");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(0)->getKey() == "b");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(1)->getKey() == "c");

	q = "while a; select a such that Follows*(10, a) such that Follows(b, c)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Follows*");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getValue() == 10);
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(1)->getKey() == "Follows");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(0)->getKey() == "b");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(1)->getKey() == "c");

	q = "while a; select a such that Follows*(10, a) such that Follows(b, c) and Follows*(d, e)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Follows*");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getValue() == 10);
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(1)->getKey() == "Follows");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(0)->getKey() == "b");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(1)->getKey() == "c");
	CPPUNIT_ASSERT(qt->getChild(2)->getKey() == "Follows*");
	CPPUNIT_ASSERT(qt->getChild(2)->getChild(0)->getKey() == "d");
	CPPUNIT_ASSERT(qt->getChild(2)->getChild(1)->getKey() == "e");
}