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
	
	q1 = "while a; Select a";
	a = new QueryParser(q1);
	synonyms = a->getSynonyms();	
	CPPUNIT_ASSERT(synonyms.at("a") == "while");

	q1 = "assign a; while a; Select a";
	a = new QueryParser(q1);
	synonyms = a->getSynonyms();	
	CPPUNIT_ASSERT(synonyms.at("a") == "while");

	q1 = "procedure b, c, d; Select b";
	a = new QueryParser(q1);
	synonyms = a->getSynonyms();
	CPPUNIT_ASSERT(synonyms.at("b") == "procedure");
	CPPUNIT_ASSERT(synonyms.at("c") == "procedure");
	CPPUNIT_ASSERT(synonyms.at("d") == "procedure");

	q1 = "stmtLst e; Select e";
	a = new QueryParser(q1);
	synonyms = a->getSynonyms();
	CPPUNIT_ASSERT(synonyms.at("e") == "stmtLst");

	q1 = "assign f, g, h ; Select f";
	a = new QueryParser(q1);
	synonyms = a->getSynonyms();
	CPPUNIT_ASSERT(synonyms.at("f") == "assign");
	CPPUNIT_ASSERT(synonyms.at("g") == "assign");
	CPPUNIT_ASSERT(synonyms.at("h") == "assign");

	q1 = "while a, b, c; call f, g, h ; Select f";
	a = new QueryParser(q1);
	synonyms = a->getSynonyms();
	CPPUNIT_ASSERT(synonyms.at("a") == "while");
	CPPUNIT_ASSERT(synonyms.at("b") == "while");
	CPPUNIT_ASSERT(synonyms.at("c") == "while");
	CPPUNIT_ASSERT(synonyms.at("f") == "call");
	CPPUNIT_ASSERT(synonyms.at("g") == "call");
	CPPUNIT_ASSERT(synonyms.at("h") == "call");

	q1 = "if a; variable f,g; constant b, c; prog_line h; Select f";
	a = new QueryParser(q1);
	synonyms = a->getSynonyms();
	CPPUNIT_ASSERT(synonyms.at("a") == "if");
	CPPUNIT_ASSERT(synonyms.at("b") == "constant");
	CPPUNIT_ASSERT(synonyms.at("c") == "constant");
	CPPUNIT_ASSERT(synonyms.at("f") == "variable");
	CPPUNIT_ASSERT(synonyms.at("g") == "variable");
	CPPUNIT_ASSERT(synonyms.at("h") == "prog_line");

	q1 = "stmt s; Select s";
	a = new QueryParser(q1);
	synonyms = a->getSynonyms();
	CPPUNIT_ASSERT(synonyms.at("s") == "stmt");

	q1 ="Select s";
	a = new QueryParser(q1);
	synonyms = a->getSynonyms();
	CPPUNIT_ASSERT(synonyms.empty());
}

void QueryParserTest::testSuchThat() {
	string q;
	QueryParser* qp;
	QTNode* qt;

	q = "while a; Select a";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(0);
	CPPUNIT_ASSERT(qt->getNumChild() == 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "a");

	q = "constant a, d; stmt b, c; Select <a, b, c, d>";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(0);
	CPPUNIT_ASSERT(qt->getNumChild() == 4);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(1)->getKey() == "b");
	CPPUNIT_ASSERT(qt->getChild(2)->getKey() == "c");
	CPPUNIT_ASSERT(qt->getChild(3)->getKey() == "d");


	q = "while a; assign b; Select BOOLEAN";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(0);
	CPPUNIT_ASSERT(qt->getNumChild() == 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "BOOLEAN");
}

void QueryParserTest::testModifies() {
	string q;
	QueryParser* qp;
	QTNode* qt;
	//Modifies (ent, var)
	q = "while a; variable b; Select a such that Modifies(a, b)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT(qt->getNumChild() == 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Modifies");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "b");

	q = "while a; variable b; Select a such that Modifies(1, \"x\")";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT(qt->getNumChild() == 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Modifies");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getValue() == 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "\"x\"");

	q = "while a; variable b; Select a such that Modifies(a,_)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT(qt->getNumChild() == 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Modifies");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "_");

	// Multiple Modifies
	q = "while a; variable b; Select a such that Modifies(b,_) such that Modifies(a, b)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT(qt->getNumChild() == 2);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Modifies");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "b");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(1)->getKey() == "Modifies");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(0)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(1)->getKey() == "b");

	q = "while a; variable b; Select a such that Modifies(b,_) and Modifies(a, b)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT(qt->getNumChild() == 2);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Modifies");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "b");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(1)->getKey() == "Modifies");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(0)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(1)->getKey() == "b");
	
	q = "while a; variable b; Select a such that Modifies(3,a) such that Modifies(a, b) and Modifies(1, _)";
	qp = new QueryParser(q);
	//qp->printMap();
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 3);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Modifies");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getValue() == 3);
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(1)->getKey() == "Modifies");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(0)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(1)->getKey() == "b");
	CPPUNIT_ASSERT(qt->getChild(2)->getKey() == "Modifies");
	CPPUNIT_ASSERT(qt->getChild(2)->getChild(0)->getValue() == 1);
	CPPUNIT_ASSERT(qt->getChild(2)->getChild(1)->getKey() == "_");
	
	q = "while a; variable b; Select a such that Modifies(d,_) and Modifies(a, b) and Modifies(1, \"abc\")";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 3);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Modifies");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "d");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(1)->getKey() == "Modifies");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(0)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(1)->getKey() == "b");
	CPPUNIT_ASSERT(qt->getChild(2)->getKey() == "Modifies");
	CPPUNIT_ASSERT(qt->getChild(2)->getChild(0)->getValue() == 1);
	CPPUNIT_ASSERT(qt->getChild(2)->getChild(1)->getKey() == "\"abc\"");
}

void QueryParserTest::testUses() {
	string q;
	QueryParser* qp;
	QTNode* qt;
	//Uses (ent, var)
	q = "while a; variable b; Select a such that Uses(a, b)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT(qt->getNumChild() == 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Uses");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "b");

	q = "while a; variable b; Select a such that Uses(1, \"x\")";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT(qt->getNumChild() == 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Uses");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getValue() == 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "\"x\"");

	q = "while a; variable b; Select a such that Uses(a,_)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT(qt->getNumChild() == 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Uses");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "_");

	// Multiple Modifies
	q = "while a; variable b; Select a such that Uses(b,_) such that Uses(a, b)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT(qt->getNumChild() == 2);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Uses");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "b");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(1)->getKey() == "Uses");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(0)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(1)->getKey() == "b");

	q = "while a; variable b; Select a such that Uses(b,_) and Uses(a, b)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT(qt->getNumChild() == 2);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Uses");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "b");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(1)->getKey() == "Uses");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(0)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(1)->getKey() == "b");
	
	q = "while a; variable b; Select a such that Uses(3,a) such that Uses(a, b) and Uses(1, _)";
	qp = new QueryParser(q);
	//qp->printMap();
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 3);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Uses");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getValue() == 3);
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(1)->getKey() == "Uses");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(0)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(1)->getKey() == "b");
	CPPUNIT_ASSERT(qt->getChild(2)->getKey() == "Uses");
	CPPUNIT_ASSERT(qt->getChild(2)->getChild(0)->getValue() == 1);
	CPPUNIT_ASSERT(qt->getChild(2)->getChild(1)->getKey() == "_");
	
	q = "while a; variable b; Select a such that Uses(3,_) and Uses(a, b) and Uses(1, \"abc\")";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 3);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Uses");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getValue() == 3);
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(1)->getKey() == "Uses");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(0)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(1)->getKey() == "b");
	CPPUNIT_ASSERT(qt->getChild(2)->getKey() == "Uses");
	CPPUNIT_ASSERT(qt->getChild(2)->getChild(0)->getValue() == 1);
	CPPUNIT_ASSERT(qt->getChild(2)->getChild(1)->getKey() == "\"abc\"");
}

void QueryParserTest::testCalls() {
	string q;
	QueryParser* qp;
	QTNode* qt;	

	//calls (entRef, entRef)
	q = "while a; Select a such that calls(1, 2)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Calls");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getValue() == 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getValue() == 2);

	q = "while a; Select a such that calls(a, _)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Calls");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "_");

	q = "while a; Select a such that calls(_, \"yolo\")";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Calls");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "\"yolo\"");

	q = "while a; Select a such that calls(\"hobo\", a)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Calls");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "\"hobo\"");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "a");

	//calls*(entRef, entRef)
	q = "while a; Select a such that calls*(1, 2)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Calls*");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getValue() == 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getValue() == 2);

	q = "while a; Select a such that calls*(a, _)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Calls*");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "_");

	q = "while a; Select a such that calls*(_, \"yolo\")";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Calls*");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "\"yolo\"");

	q = "while a; Select a such that calls*(\"hobo\", a)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Calls*");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "\"hobo\"");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "a");

	//Multiple calls/calls*
	q = "while a; Select a such that calls*(\"hobo\", a) and calls(_, 101)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 2);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Calls*");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "\"hobo\"");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(1)->getKey() == "Calls");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(0)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(1)->getValue() == 101);

	q = "while a; Select a such that calls*(_, a) such that calls(\"hohoho\", 101)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 2);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Calls*");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(1)->getKey() == "Calls");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(0)->getKey() == "\"hohoho\"");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(1)->getValue() == 101);

	q = "while a; Select a such that calls*(_, a) and calls(1, 2) such that calls(\"hohoho\", 101)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 3);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Calls*");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(1)->getKey() == "Calls");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(0)->getValue() == 1);
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(1)->getValue() == 2);
	CPPUNIT_ASSERT(qt->getChild(2)->getKey() == "Calls");
	CPPUNIT_ASSERT(qt->getChild(2)->getChild(0)->getKey() == "\"hohoho\"");
	CPPUNIT_ASSERT(qt->getChild(2)->getChild(1)->getValue() == 101);

	q = "while a; Select a such that calls*(_, a) and calls(1, 2) and calls(\"hohoho\", 101)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 3);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Calls*");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(1)->getKey() == "Calls");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(0)->getValue() == 1);
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(1)->getValue() == 2);
	CPPUNIT_ASSERT(qt->getChild(2)->getKey() == "Calls");
	CPPUNIT_ASSERT(qt->getChild(2)->getChild(0)->getKey() == "\"hohoho\"");
	CPPUNIT_ASSERT(qt->getChild(2)->getChild(1)->getValue() == 101);
}

void QueryParserTest::testParent() {
	string q;
	QueryParser* qp;
	QTNode* qt;
	
	q = "while a; Select a such that parent(1, 2)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Parent");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getValue() == 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getValue() == 2);

	q = "while a; Select a such that parent(a, 2)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Parent");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getValue() == 2);

	q = "while a; Select a such that parent(_, a)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Parent");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "a");

	q = "while a; Select a such that parent(_, _)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Parent");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "_");
	
	// parent *
	q = "while a; Select a such that parent*(1, 2)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Parent*");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getValue() == 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getValue() == 2);

	q = "while a; Select a such that parent*(a, 2)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Parent*");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getValue() == 2);

	q = "while a; Select a such that parent*(1, _)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Parent*");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getValue() == 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "_");

	q = "while a; Select a such that parent*(_, _)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Parent*");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "_");
	
	// Multiple parent/parent*
	q = "while a; Select a such that parent(10, a) and parent*(b, c)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 2);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Parent");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getValue() == 10);
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(1)->getKey() == "Parent*");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(0)->getKey() == "b");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(1)->getKey() == "c");

	q = "while a; Select a such that parent*(10, a) such that parent(b, c)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 2);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Parent*");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getValue() == 10);
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(1)->getKey() == "Parent");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(0)->getKey() == "b");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(1)->getKey() == "c");

	q = "while a; Select a such that parent*(10, a) such that parent(_, _) and parent*(d, e)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 3);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Parent*");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getValue() == 10);
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(1)->getKey() == "Parent");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(0)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(1)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(2)->getKey() == "Parent*");
	CPPUNIT_ASSERT(qt->getChild(2)->getChild(0)->getKey() == "d");
	CPPUNIT_ASSERT(qt->getChild(2)->getChild(1)->getKey() == "e");

	q = "while a; Select a such that parent*(10, a) and parent(_, _) such that parent*(d, e)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 3);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Parent*");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getValue() == 10);
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(1)->getKey() == "Parent");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(0)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(1)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(2)->getKey() == "Parent*");
	CPPUNIT_ASSERT(qt->getChild(2)->getChild(0)->getKey() == "d");
	CPPUNIT_ASSERT(qt->getChild(2)->getChild(1)->getKey() == "e");

	q = "while a; Select a such that parent*(10, a) and parent(_, _) and parent*(d, e)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 3);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Parent*");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getValue() == 10);
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(1)->getKey() == "Parent");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(0)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(1)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(2)->getKey() == "Parent*");
	CPPUNIT_ASSERT(qt->getChild(2)->getChild(0)->getKey() == "d");
	CPPUNIT_ASSERT(qt->getChild(2)->getChild(1)->getKey() == "e");
}

void QueryParserTest::testFollows() {
	string q;
	QueryParser* qp;
	QTNode* qt;
	
	q = "while a; Select a such that follows(1, 2)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Follows");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getValue() == 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getValue() == 2);

	q = "while a; Select a such that FOLLOWS(a, 2)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Follows");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getValue() == 2);

	q = "while a; Select a such that foLLows(_, a)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Follows");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "a");

	q = "while a; Select a such that Follows(_, _)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Follows");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "_");
	
	// Follows *
	q = "while a; Select a such that follows*(1, 2)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Follows*");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getValue() == 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getValue() == 2);

	q = "while a; Select a such that FOLLOWS*(a, 2)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Follows*");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getValue() == 2);

	q = "while a; Select a such that foLLows*(1, _)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Follows*");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getValue() == 1);
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "_");

	q = "while a; Select a such that Follows*(_, _)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Follows*");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "_");
	
	// Multiple Follows/Follows*
	q = "while a; Select a such that Follows(10, a) and Follows*(b, c)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 2);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Follows");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getValue() == 10);
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(1)->getKey() == "Follows*");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(0)->getKey() == "b");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(1)->getKey() == "c");

	q = "while a; Select a such that Follows*(10, a) such that Follows(b, c)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 2);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Follows*");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getValue() == 10);
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(1)->getKey() == "Follows");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(0)->getKey() == "b");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(1)->getKey() == "c");

	q = "while a; Select a such that Follows*(10, a) such that Follows(_, _) and Follows*(d, e)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 3);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Follows*");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getValue() == 10);
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(1)->getKey() == "Follows");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(0)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(1)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(2)->getKey() == "Follows*");
	CPPUNIT_ASSERT(qt->getChild(2)->getChild(0)->getKey() == "d");
	CPPUNIT_ASSERT(qt->getChild(2)->getChild(1)->getKey() == "e");

	q = "while a; Select a such that Follows*(10, a) and Follows(_, _) such that Follows*(d, e)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 3);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Follows*");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getValue() == 10);
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(1)->getKey() == "Follows");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(0)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(1)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(2)->getKey() == "Follows*");
	CPPUNIT_ASSERT(qt->getChild(2)->getChild(0)->getKey() == "d");
	CPPUNIT_ASSERT(qt->getChild(2)->getChild(1)->getKey() == "e");

	q = "while a; Select a such that Follows*(10, a) and Follows(_, _) and Follows*(d, e)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(1);
	CPPUNIT_ASSERT_EQUAL(qt->getNumChild(), 3);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "Follows*");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getValue() == 10);
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(1)->getKey() == "Follows");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(0)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(1)->getChild(1)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(2)->getKey() == "Follows*");
	CPPUNIT_ASSERT(qt->getChild(2)->getChild(0)->getKey() == "d");
	CPPUNIT_ASSERT(qt->getChild(2)->getChild(1)->getKey() == "e");
}

void QueryParserTest::testAssignPattern() {
	string q;
	QueryParser* qp;
	QTNode* qt;
	
	q = "assign a; Select a pattern a(b, \"x+y\")";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(2);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "assign");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "b");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(2)->getKey() == "+");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(2)->getChild(0)->getKey() == "x");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(2)->getChild(1)->getKey() == "y");

	q = "assign a; Select a pattern a(\"x\", \"x+y+z\")";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(2);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "assign");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "\"x\"");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(2)->getKey() == "+");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(2)->getChild(0)->getKey() == "+");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(2)->getChild(1)->getKey() == "z");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(2)->getChild(0)->getChild(0)->getKey() == "x");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(2)->getChild(0)->getChild(1)->getKey() == "y");

	q = "assign a; Select a pattern a(_, \"w + x+ y +z\")";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(2);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "assign");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(2)->getKey() == "+");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(2)->getChild(0)->getKey() == "+");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(2)->getChild(1)->getKey() == "z");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(2)->getChild(0)->getChild(0)->getKey() == "+");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(2)->getChild(0)->getChild(1)->getKey() == "y");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(2)->getChild(0)->getChild(0)->getChild(0)->getKey() == "w");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(2)->getChild(0)->getChild(0)->getChild(1)->getKey() == "x");

	q = "assign a; Select a pattern a(b, _\"x+y\")";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(2);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "assign");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "b");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(2)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(3)->getKey() == "+");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(3)->getChild(0)->getKey() == "x");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(3)->getChild(1)->getKey() == "y");

	q = "assign a; Select a pattern a(b, \"x+y\"_)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(2);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "assign");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "b");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(2)->getKey() == "+");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(3)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(2)->getChild(0)->getKey() == "x");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(2)->getChild(1)->getKey() == "y");

	q = "assign a; Select a pattern a(b, _\"x+y\"_)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(2);
	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "assign");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "b");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(2)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(3)->getKey() == "+");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(4)->getKey() == "_");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(3)->getChild(0)->getKey() == "x");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(3)->getChild(1)->getKey() == "y");
}

void QueryParserTest::testMoreAssignPatterns() {
	string q;
	QueryParser* qp;
	QTNode* qt;
	q = "assign a; Select a pattern a(\"oSCar\", _)";
	qp = new QueryParser(q);
	qt = qp->getQueryTree()->getRootNode()->getChild(2);

	CPPUNIT_ASSERT(qt->getChild(0)->getKey() == "assign");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(0)->getKey() == "a");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(1)->getKey() == "\"oSCar\"");
	CPPUNIT_ASSERT(qt->getChild(0)->getChild(2)->getKey() == "_");
}