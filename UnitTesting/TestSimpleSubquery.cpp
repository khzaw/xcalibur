#include <cppunit/config/SourcePrefix.h>
#include <iostream>
#include <string>
#include <map>
#include "TestSubquery.h"
#include "..\SPA\PKB\NextExtractor.h"
#include "QueryProcessor\Subquery.h"
#include "QueryProcessor\Subquery.cpp"
#include "QueryProcessor\FollowsSubquery.cpp"
#include "QueryProcessor\FollowsStarSubquery.cpp"
#include "QueryProcessor\ModifiesSubquery.cpp"
#include "QueryProcessor\ModifiesProcSubquery.cpp"
#include "QueryProcessor\UsesSubquery.cpp"
#include "QueryProcessor\UsesProcSubquery.cpp"
#include "QueryProcessor\ParentSubquery.cpp"
#include "QueryProcessor\ParentStarSubquery.cpp"
#include "QueryProcessor\WithSubquery.cpp"
#include "QueryProcessor\CallsSubquery.cpp"
#include "QueryProcessor\CallsStarSubquery.cpp"
#include "QueryProcessor\NextSubquery.cpp"
#include "QueryProcessor\NextStarSubquery.cpp"
#include "QueryProcessor\AffectsSubquery.cpp"

void SubqueryTest::setUp() {
}

void SubqueryTest::tearDown() {
}

CPPUNIT_TEST_SUITE_REGISTRATION( SubqueryTest );
void SubqueryTest::testSubqueries() {
	/**
	procedure test {
	a = 3;				// 1
		while i {		// 2
			b = 4;		// 3
		}
	c = 5;				// 4
	}
	**/

	pk = new PKBController();
	synonymTable = map<string, string>();

	pk->procTable->insertProc("test");		 // 0

	TNode rootNode1("PROC_NODE", "test", 0, 0);
	TNode stmtListNode1("STMTLST_NODE", "", 0, 0); 
	rootNode1.addChild(&stmtListNode1);
	stmtListNode1.addParent(&rootNode1);

	pk->ast->insertRoot(&rootNode1);
	pk->procTable->insertASTRootNode(0, &rootNode1);

	TNode stmt1("ASSIGN_NODE", "a = 3", 1, 0);
	pk->statementTable->insertStatement(&stmt1);
	TNode stmt2("WHILE_NODE", "i", 2, 0);
	pk->statementTable->insertStatement(&stmt2);
	TNode stmt3("ASSIGN_NODE", "b = 4", 3, 0);
	pk->statementTable->insertStatement(&stmt3);
	TNode stmt4("ASSIGN_NODE", "c = 5", 4, 0);
	pk->statementTable->insertStatement(&stmt4);

	stmt1.addParent(&stmtListNode1); stmtListNode1.addChild(&stmt1); 
	stmt2.addParent(&stmtListNode1); stmtListNode1.addChild(&stmt2); 
	stmt4.addParent(&stmtListNode1); stmtListNode1.addChild(&stmt4);

	TNode stmtListNode2("STMTLST_NODE", "", 2, 0);
	stmt2.addChild(&stmtListNode2); stmtListNode2.addParent(&stmt2);
	stmt3.addParent(&stmtListNode2); stmtListNode2.addChild(&stmt3);

	stmt1.addRightSibling(&stmt2);
    stmt2.addRightSibling(&stmt4);




	pk->varTable->insertVar("a");			// 0
	pk->varTable->insertVar("i");			// 1
	pk->varTable->insertVar("b");			// 2
	pk->varTable->insertVar("c");			// 3

	pk->constantTable->insertConst(3);
	pk->constantTable->insertConst(4);
	pk->constantTable->insertConst(5);

	pk->followsTable->insertFollows(1, 2);
	pk->followsTable->insertFollows(2, 4);

	pk->parentTable->insertParent(2, 3);

	pk->constructFollows();
	pk->constructParent();
	pk->constructNext();

	set<int, less<int>, allocator<int>> test = pk->nextExtractor->getNext(2);
	test = pk->nextExtractor->getNext(3);
	cout << "yay" << endl;


	synonymTable["s"] = "stmt";

	testNext();
}

void SubqueryTest::testNext() {
	cout << "Testing Next " << endl;
	cout << "Testing Next " << endl;
	cout << "Testing Next " << endl;
	cout << "Testing Next " << endl;
	cout << "Testing Next " << endl;
	cout << "Testing Next " << endl;
	cout << "Testing Next " << endl;
	cout << "Testing Next " << endl;
	cout << "Testing Next " << endl;
	cout << "Testing Next " << endl;
	cout << "Testing Next " << endl;
	NextSubquery nextSubquery = NextSubquery(&synonymTable, pk);
	nextSubquery.setSynonyms("s", 4);
	ResultTuple* actualResultsNextSubquery = nextSubquery.solve();
	int expectedResultsNextSubquery[1][1] = {
		{2}
	};
	CPPUNIT_ASSERT_EQUAL((size_t)1, actualResultsNextSubquery->getAllResults().size());
	for(size_t i = 0; i < 1; i++) {
		for(size_t j = 0; j < 1; j++) {
			CPPUNIT_ASSERT_EQUAL(expectedResultsNextSubquery[i][j], actualResultsNextSubquery->getResultAt(i, j));
		}
	}
}