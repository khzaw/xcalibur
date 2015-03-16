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

void 
SubqueryTest::setUp()
{
}

void 
SubqueryTest::tearDown()
{
}	

CPPUNIT_TEST_SUITE_REGISTRATION( SubqueryTest );
// method to test insertion of Follows

void SubqueryTest::testSubqueries() {
	/** SIMPLE source code
	procedure First{
		x = 2;					// 1
		z = 3;					// 2
		call Second;}			// 3
	procedure Second{
		x = 0;					// 4
		i = 5;					// 5
		while i {				// 6
			x = x + 2 * y		// 7
			if m then {			// 8
				m = n;}			// 9
			else {
				n = Second;}	// 10
			call Third;			// 11
			i = i - 1;}			// 12
		if x then {				// 13
			x = x + 1;			// 14
			while m {			// 15
				m = m - 1;}}	// 16
		else {
			z = 1;}				// 17
		z = z + x + i;			// 18
		y = z + 2;				// 19
		x = x * y + z;}			// 20
	procedure Third{
		z = 5;					// 21
		v = z;}					// 22
	**/
	pk = new PKBController();
	synonymTable = map<string, string>();
	TNode stmt1("ASSIGN_NODE", "x = 2", 1, 0);
	TNode stmt2("ASSIGN_NODE", "z = 3", 2, 0);
	TNode stmt3("CALL_NODE", "Second", 3, 0);
	TNode stmt4("ASSIGN_NODE", "x = 0", 4, 1);
	TNode stmt5("ASSIGN_NODE", "i = 5", 5, 1);
	TNode stmt6("WHILE_NODE", "i", 6, 1);
	TNode stmt7("ASSIGN_NODE", "x = x + 2 * y", 7, 1);
	TNode stmt8("IF_NODE", "m", 8, 1);
	TNode stmt9("ASSIGN_NODE", "m = n", 9, 1);
	TNode stmt10("ASSIGN_NODE", "n = Second", 10, 1);
	TNode stmt11("CALL_NODE", "Third", 11, 1);
	TNode stmt12("ASSIGN_NODE", "i = i - 1", 12, 1);
	TNode stmt13("IF_NODE", "x", 13, 1);
	TNode stmt14("ASSIGN_NODE", "x = x + 1", 14, 1);
	TNode stmt15("WHILE_NODE", "m", 15, 1);
	TNode stmt16("ASSIGN_NODE", "m = m - 1", 16, 1);
	TNode stmt17("ASSIGN_NODE", "z = 1", 17, 1);
	TNode stmt18("ASSIGN_NODE", "z = z + x + i", 18, 1);
	TNode stmt19("ASSIGN_NODE", "y = z + 2", 19, 1);
	TNode stmt20("ASSIGN_NODE", "x = x * y + z", 20, 1);
	TNode stmt21("ASSIGN_NODE", "z = 5", 21, 2);
	TNode stmt22("ASSIGN_NODE", "v = z", 22, 2);
	
	TNode rootNode1("PROC_NODE", "First", -1, 0);
	TNode stmtListNode1("STMTLST_NODE", "", 0, 0); 
	stmtListNode1.addParent(&rootNode1); 
	rootNode1.addChild(&stmtListNode1);
	stmt1.addParent(&stmtListNode1); stmtListNode1.addChild(&stmt1); stmt1.addRightSibling(&stmt2);
	stmt2.addParent(&stmtListNode1); stmtListNode1.addChild(&stmt2); stmt2.addRightSibling(&stmt3);
	stmt3.addParent(&stmtListNode1); stmtListNode1.addChild(&stmt2);

	TNode rootNode2("PROC_NODE", "Second", -1, 1);
	TNode stmtListNode2("STMTLST_NODE", "", 0, 1); 
	stmtListNode2.addParent(&rootNode2); 
	rootNode2.addChild(&stmtListNode2);
	// base
	stmt4.addParent(&stmtListNode2); stmtListNode2.addChild(&stmt4); stmt4.addRightSibling(&stmt5);
	stmt5.addParent(&stmtListNode2); stmtListNode2.addChild(&stmt5); stmt5.addRightSibling(&stmt6);
	stmt6.addParent(&stmtListNode2); stmtListNode2.addChild(&stmt6); stmt6.addRightSibling(&stmt13);
	stmt13.addParent(&stmtListNode2); stmtListNode2.addChild(&stmt13); stmt13.addRightSibling(&stmt18);
	stmt18.addParent(&stmtListNode2); stmtListNode2.addChild(&stmt18); stmt18.addRightSibling(&stmt19);
	stmt19.addParent(&stmtListNode2); stmtListNode2.addChild(&stmt19); stmt19.addRightSibling(&stmt20);
	stmt20.addParent(&stmtListNode2); stmtListNode2.addChild(&stmt20);
	// statement 6 nesting
	TNode stmtListNode2_1("STMTLST_NODE", "", 0, 1); 
	stmtListNode2_1.addParent(&stmt6); stmt6.addChild(&stmtListNode2_1);
	stmt7.addParent(&stmtListNode2_1); stmtListNode2_1.addChild(&stmt7); stmt7.addRightSibling(&stmt8);
	stmt8.addParent(&stmtListNode2_1); stmtListNode2_1.addChild(&stmt8); stmt8.addRightSibling(&stmt11);
	stmt11.addParent(&stmtListNode2_1); stmtListNode2_1.addChild(&stmt11); stmt11.addRightSibling(&stmt12);
	stmt12.addParent(&stmtListNode2_1); stmtListNode2_1.addChild(&stmt12);
		// statement 8 nesting
		TNode stmtListNode2_1_1("STMTLST_NODE", "", 0, 1); TNode thennode211("THEN_NODE", "then", 0, 1);
		TNode stmtListNode2_1_2("STMTLST_NODE", "", 0, 1); TNode elsenode212("ELSE_NODE", "else", 0, 1);
		thennode211.addParent(&stmt8); stmt8.addChild(&thennode211); thennode211.addRightSibling(&elsenode212);
		elsenode212.addParent(&stmt8); stmt8.addChild(&elsenode212);
		stmtListNode2_1_1.addParent(&thennode211); thennode211.addChild(&stmtListNode2_1_1);
		stmtListNode2_1_2.addParent(&elsenode212); elsenode212.addChild(&stmtListNode2_1_2);
		stmt9.addParent(&stmtListNode2_1_1); stmtListNode2_1_1.addChild(&stmt9);
		stmt10.addParent(&stmtListNode2_1_2); stmtListNode2_1_2.addChild(&stmt10);
	// statement 13 nesting
	TNode stmtListNode2_2("STMTLST_NODE", "", 0, 1); TNode thennode222("THEN_NODE", "then", 0, 1);
	TNode stmtListNode2_3("STMTLST_NODE", "", 0, 1); TNode elsenode223("ELSE_NODE", "else", 0, 1);
	thennode222.addParent(&stmt13); stmt13.addChild(&thennode222); thennode222.addRightSibling(&elsenode223);
	elsenode223.addParent(&stmt13); stmt13.addChild(&elsenode223);
	stmtListNode2_2.addParent(&thennode222); thennode222.addChild(&stmtListNode2_2);
	stmtListNode2_3.addParent(&elsenode223); elsenode223.addChild(&stmtListNode2_3);
	stmt14.addParent(&stmtListNode2_2); stmtListNode2_2.addChild(&stmt14); stmt14.addRightSibling(&stmt15);
	stmt15.addParent(&stmtListNode2_2); stmtListNode2_2.addChild(&stmt15);
		// statement 15 nesting
		TNode stmtListNode2_2_1("STMTLST_NODE", "", 0, 1); 
		stmtListNode2_2_1.addParent(&stmt15); stmt15.addChild(&stmtListNode2_2_1);
		stmt16.addParent(&stmtListNode2_2_1); stmtListNode2_2_1.addChild(&stmt16);
	stmtListNode2_3.addParent(&stmt13); stmt13.addChild(&stmtListNode2_3);
	stmt17.addParent(&stmtListNode2_3); stmtListNode2_3.addChild(&stmt17);

	TNode rootNode3("PROC_NODE", "Third", -1, 2);
	TNode stmtListNode3("STMTLST_NODE", "", 0, 2); 
	stmtListNode3.addParent(&rootNode3); 
	rootNode3.addChild(&stmtListNode3);
	stmt21.addParent(&stmtListNode3); stmtListNode3.addChild(&stmt21); stmt21.addRightSibling(&stmt22);
	stmt22.addParent(&stmtListNode3); stmtListNode3.addChild(&stmt22);

	pk->ast.insertRoot(&rootNode1);
	pk->ast.insertRoot(&rootNode2);
	pk->ast.insertRoot(&rootNode3);
	pk->procTable.insertASTRootNode(0, &rootNode1);
	pk->procTable.insertASTRootNode(1, &rootNode2);
	pk->procTable.insertASTRootNode(2, &rootNode3);
	/*
	pk->statementTable.insertStatement(&stmt1);
	pk->statementTable.insertStatement(&stmt2);
	pk->statementTable.insertStatement(&stmt3);
	pk->statementTable.insertStatement(&stmt4);
	pk->statementTable.insertStatement(&stmt5);
	pk->statementTable.insertStatement(&stmt6);
	pk->statementTable.insertStatement(&stmt7);
	pk->statementTable.insertStatement(&stmt8);
	pk->statementTable.insertStatement(&stmt9);
	pk->statementTable.insertStatement(&stmt10);
	pk->statementTable.insertStatement(&stmt11);
	pk->statementTable.insertStatement(&stmt12);
	pk->statementTable.insertStatement(&stmt13);
	pk->statementTable.insertStatement(&stmt14);
	pk->statementTable.insertStatement(&stmt15);
	pk->statementTable.insertStatement(&stmt16);
	pk->statementTable.insertStatement(&stmt17);
	pk->statementTable.insertStatement(&stmt18);
	pk->statementTable.insertStatement(&stmt19);
	pk->statementTable.insertStatement(&stmt20);
	pk->statementTable.insertStatement(&stmt21);
	pk->statementTable.insertStatement(&stmt22);
	*/
	pk->procTable.insertProc("First");  // 0
	pk->procTable.insertProc("Second"); // 1
	pk->procTable.insertProc("Third");  // 2

	pk->varTable.insertVar("x");        // 0
	pk->varTable.insertVar("z");        // 1
	pk->varTable.insertVar("i");		   // 2
	pk->varTable.insertVar("y");        // 3
	pk->varTable.insertVar("m");        // 4
	pk->varTable.insertVar("n");        // 5
	pk->varTable.insertVar("Second");   // 6
	pk->varTable.insertVar("v");        // 7

	pk->constantTable.insertConst(2);
	pk->constantTable.insertConst(3);
	pk->constantTable.insertConst(0);
	pk->constantTable.insertConst(5);
	pk->constantTable.insertConst(1);

	pk->followsTable.insertFollows(1, 2);
	pk->followsTable.insertFollows(2, 3);
	pk->followsTable.insertFollows(4, 5);
	pk->followsTable.insertFollows(5, 6);
	pk->followsTable.insertFollows(6, 13);
	pk->followsTable.insertFollows(13, 18);
	pk->followsTable.insertFollows(18, 19);
	pk->followsTable.insertFollows(19, 20);
	pk->followsTable.insertFollows(21, 22);
	pk->followsTable.insertFollows(7, 8);
	pk->followsTable.insertFollows(8, 11);
	pk->followsTable.insertFollows(11, 12);
	pk->followsTable.insertFollows(14, 15);

	pk->parentTable.insertParent(6, 7);
	pk->parentTable.insertParent(6, 8);
	pk->parentTable.insertParent(6, 11);
	pk->parentTable.insertParent(6, 12);
	pk->parentTable.insertParent(8, 9);
	pk->parentTable.insertParent(8, 10);
	pk->parentTable.insertParent(13, 14);
	pk->parentTable.insertParent(13, 15);
	pk->parentTable.insertParent(13, 17);
	pk->parentTable.insertParent(15, 16);

	pk->callsTable.insertCalls(0, 1);
	pk->callsTable.insertCalls(1, 2);

	pk->modifiesTable.insertModifiesProc(0, 0);
	pk->modifiesTable.insertModifiesProc(0, 1);
	pk->modifiesTable.insertModifiesProc(0, 2);
	pk->modifiesTable.insertModifiesProc(0, 3);
	pk->modifiesTable.insertModifiesProc(0, 4);
	pk->modifiesTable.insertModifiesProc(0, 5);
	pk->modifiesTable.insertModifiesProc(0, 7);
	pk->modifiesTable.insertModifiesProc(1, 0);
	pk->modifiesTable.insertModifiesProc(1, 1);
	pk->modifiesTable.insertModifiesProc(1, 2);
	pk->modifiesTable.insertModifiesProc(1, 3);
	pk->modifiesTable.insertModifiesProc(1, 4);
	pk->modifiesTable.insertModifiesProc(1, 5);
	pk->modifiesTable.insertModifiesProc(1, 7);
	pk->modifiesTable.insertModifiesProc(2, 1);
	pk->modifiesTable.insertModifiesProc(2, 7);
	
	pk->modifiesTable.insertModifiesStmt(1, 0);
	pk->modifiesTable.insertModifiesStmt(2, 1);
	pk->modifiesTable.insertModifiesStmt(3, 0);
	pk->modifiesTable.insertModifiesStmt(3, 2);
	pk->modifiesTable.insertModifiesStmt(3, 4);
	pk->modifiesTable.insertModifiesStmt(3, 5);
	pk->modifiesTable.insertModifiesStmt(3, 1);
	pk->modifiesTable.insertModifiesStmt(3, 3);
	pk->modifiesTable.insertModifiesStmt(3, 7);
	pk->modifiesTable.insertModifiesStmt(4, 0);
	pk->modifiesTable.insertModifiesStmt(5, 2);
	pk->modifiesTable.insertModifiesStmt(6, 0);
	pk->modifiesTable.insertModifiesStmt(6, 4);
	pk->modifiesTable.insertModifiesStmt(6, 5);
	pk->modifiesTable.insertModifiesStmt(6, 1);
	pk->modifiesTable.insertModifiesStmt(6, 7);
	pk->modifiesTable.insertModifiesStmt(6, 2);
	pk->modifiesTable.insertModifiesStmt(7, 0);
	pk->modifiesTable.insertModifiesStmt(8, 4);
	pk->modifiesTable.insertModifiesStmt(8, 5);
	pk->modifiesTable.insertModifiesStmt(9, 4);
	pk->modifiesTable.insertModifiesStmt(10, 5);
	pk->modifiesTable.insertModifiesStmt(11, 1);
	pk->modifiesTable.insertModifiesStmt(11, 7);
	pk->modifiesTable.insertModifiesStmt(12, 2);
	pk->modifiesTable.insertModifiesStmt(13, 0);
	pk->modifiesTable.insertModifiesStmt(13, 4);
	pk->modifiesTable.insertModifiesStmt(13, 1);
	pk->modifiesTable.insertModifiesStmt(14, 0);
	pk->modifiesTable.insertModifiesStmt(15, 4);
	pk->modifiesTable.insertModifiesStmt(16, 4);
	pk->modifiesTable.insertModifiesStmt(17, 1);
	pk->modifiesTable.insertModifiesStmt(18, 1);
	pk->modifiesTable.insertModifiesStmt(19, 3);
	pk->modifiesTable.insertModifiesStmt(20, 0);
	pk->modifiesTable.insertModifiesStmt(21, 1);
	pk->modifiesTable.insertModifiesStmt(22, 7);

	pk->usesTable.insertUsesProc(0, 0);
	pk->usesTable.insertUsesProc(0, 1);
	pk->usesTable.insertUsesProc(0, 2);
	pk->usesTable.insertUsesProc(0, 3);
	pk->usesTable.insertUsesProc(0, 4);
	pk->usesTable.insertUsesProc(0, 5);
	pk->usesTable.insertUsesProc(0, 6);
	pk->usesTable.insertUsesProc(1, 0);
	pk->usesTable.insertUsesProc(1, 1);
	pk->usesTable.insertUsesProc(1, 2);
	pk->usesTable.insertUsesProc(1, 3);
	pk->usesTable.insertUsesProc(1, 4);
	pk->usesTable.insertUsesProc(1, 5);
	pk->usesTable.insertUsesProc(1, 6);
	pk->usesTable.insertUsesProc(2, 1);
	
	pk->usesTable.insertUsesStmt(3, 0);
	pk->usesTable.insertUsesStmt(3, 1);
	pk->usesTable.insertUsesStmt(3, 2);
	pk->usesTable.insertUsesStmt(3, 3);
	pk->usesTable.insertUsesStmt(3, 4);
	pk->usesTable.insertUsesStmt(3, 5);
	pk->usesTable.insertUsesStmt(3, 6);
	pk->usesTable.insertUsesStmt(6, 2);
	pk->usesTable.insertUsesStmt(6, 0);
	pk->usesTable.insertUsesStmt(6, 3);
	pk->usesTable.insertUsesStmt(6, 4);
	pk->usesTable.insertUsesStmt(6, 5);
	pk->usesTable.insertUsesStmt(6, 6);
	pk->usesTable.insertUsesStmt(6, 1);
	pk->usesTable.insertUsesStmt(7, 0);
	pk->usesTable.insertUsesStmt(7, 3);
	pk->usesTable.insertUsesStmt(8, 4);
	pk->usesTable.insertUsesStmt(8, 5);
	pk->usesTable.insertUsesStmt(8, 6);
	pk->usesTable.insertUsesStmt(9, 5);
	pk->usesTable.insertUsesStmt(10, 6);
	pk->usesTable.insertUsesStmt(11, 1);
	pk->usesTable.insertUsesStmt(12, 2);
	pk->usesTable.insertUsesStmt(13, 0);
	pk->usesTable.insertUsesStmt(13, 4);
	pk->usesTable.insertUsesStmt(14, 0);
	pk->usesTable.insertUsesStmt(15, 4);
	pk->usesTable.insertUsesStmt(16, 4);
	pk->usesTable.insertUsesStmt(18, 1);
	pk->usesTable.insertUsesStmt(18, 0);
	pk->usesTable.insertUsesStmt(18, 2);
	pk->usesTable.insertUsesStmt(19, 1);
	pk->usesTable.insertUsesStmt(20, 0);
	pk->usesTable.insertUsesStmt(20, 1);
	pk->usesTable.insertUsesStmt(20, 3);
	pk->usesTable.insertUsesStmt(22, 1);

	pk->statementTable.insertStatement(&stmt1);
	pk->statementTable.insertStatement(&stmt2);
	pk->statementTable.insertStatement(&stmt3);
	pk->statementTable.insertStatement(&stmt4);
	pk->statementTable.insertStatement(&stmt5);
	pk->statementTable.insertStatement(&stmt6);
	pk->statementTable.insertStatement(&stmt7);
	pk->statementTable.insertStatement(&stmt8);
	pk->statementTable.insertStatement(&stmt9);
	pk->statementTable.insertStatement(&stmt10);
	pk->statementTable.insertStatement(&stmt11);
	pk->statementTable.insertStatement(&stmt12);
	pk->statementTable.insertStatement(&stmt13);
	pk->statementTable.insertStatement(&stmt14);
	pk->statementTable.insertStatement(&stmt15);
	pk->statementTable.insertStatement(&stmt16);
	pk->statementTable.insertStatement(&stmt17);
	pk->statementTable.insertStatement(&stmt18);
	pk->statementTable.insertStatement(&stmt19);
	pk->statementTable.insertStatement(&stmt20);
	pk->statementTable.insertStatement(&stmt21);
	pk->statementTable.insertStatement(&stmt22);

	pk->constructCalls();
	pk->constructFollows();
	pk->constructModifies();
	pk->constructParent();
	pk->constructNext();
	pk->constructUses();

	synonymTable["s1"]="stmt";
	synonymTable["s2"]="stmt";
	synonymTable["a1"]="assign";
	synonymTable["a2"]="assign";
	synonymTable["w1"]="while";
	synonymTable["w2"]="while";
	synonymTable["i1"]="if";
	synonymTable["i2"]="if";
	synonymTable["v1"]="variable";
	synonymTable["v2"]="variable";
	synonymTable["proc1"]="procedure";
	synonymTable["proc2"]="procedure";
	synonymTable["c1"]="call";
	synonymTable["c2"]="call";
	synonymTable["l1"]="prog_line";
	synonymTable["l2"]="prog_line";
	synonymTable["const1"]="constant";
	synonymTable["const2"]="constant";

	//testNext();
	testFollows();
	testParent();
	testFollowsT();
	testParentT();
	testFollowsTuple();
	testParentTuple();
	testFollowsTTuple();
	testParentTTuple();
	testModifies();
	testModifiesTuple();
	testUses();
	testUsesTuple();
	testModifiesProc();
	testModifiesProcTuple();
	testUsesProc();
	testUsesProcTuple();
	testCalls();
	testCallsTuple();
	testCallsT();
	testCallsTTuple();
	testPattern();
	testWith();
	testWithTuple();
}

void SubqueryTest::testFollows(){
	// Test 1: Follows(s1, s2)
	FollowsSubquery followsSubquery1 = FollowsSubquery(&synonymTable, pk);
	followsSubquery1.setSynonyms("s1", "s2");
	ResultTuple* actualResultsFollowsSubquery1 = followsSubquery1.solve();
	int expectedResultsFollowsSubquery1[13][2] = {
		{1, 2}, {2, 3}, {4, 5}, {5, 6}, {6, 13}, {7, 8}, {8, 11}, {11, 12}, {13, 18}, {14, 15}, {18, 19}, {19, 20}, {21, 22}
	};
	CPPUNIT_ASSERT_EQUAL((size_t)13, actualResultsFollowsSubquery1->getAllResults().size());
	for (size_t i = 0; i < 13; i++){
		for (size_t j = 0; j < 2; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsFollowsSubquery1[i][j], actualResultsFollowsSubquery1->getResultAt(i, j));
		}
	}

	// Test 2: Follows(s1, 2)
	FollowsSubquery followsSubquery2 = FollowsSubquery(&synonymTable, pk);
	followsSubquery2.setSynonyms("s1", 2);
	ResultTuple* actualResultsFollowsSubquery2 = followsSubquery2.solve();
	int expectedResultsFollowsSubquery2[1][1] = {
		{1}
	};
	CPPUNIT_ASSERT_EQUAL((size_t)1, actualResultsFollowsSubquery2->getAllResults().size());
	for (size_t i = 0; i < 1; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsFollowsSubquery2[i][j], actualResultsFollowsSubquery2->getResultAt(i, j));
		}
	}

	// Test 3: Follows(s1, _)
	FollowsSubquery followsSubquery3 = FollowsSubquery(&synonymTable, pk);
	followsSubquery3.setSynonyms("s1", "_");
	ResultTuple* actualResultsFollowsSubquery3 = followsSubquery3.solve();
	int expectedResultsFollowsSubquery3[13][1] = {
		{1}, {2}, {4}, {5}, {6}, {7}, {8}, {11}, {13}, {14}, {18}, {19}, {21}
	};
	CPPUNIT_ASSERT_EQUAL((size_t)13, actualResultsFollowsSubquery3->getAllResults().size());
	for (size_t i = 0; i < 13; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsFollowsSubquery3[i][j], actualResultsFollowsSubquery3->getResultAt(i, j));
		}
	}

	// Test 4: Follows(a1, _)
	FollowsSubquery followsSubquery4 = FollowsSubquery(&synonymTable, pk);
	followsSubquery4.setSynonyms("a1", "_");
	ResultTuple* actualResultsFollowsSubquery4 = followsSubquery4.solve();
	int expectedResultsFollowsSubquery4[9][1] = {
		{1}, {2}, {4}, {5}, {7}, {14}, {18}, {19}, {21}
	};
	CPPUNIT_ASSERT_EQUAL((size_t)9, actualResultsFollowsSubquery4->getAllResults().size());
	for (size_t i = 0; i < 9; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsFollowsSubquery4[i][j], actualResultsFollowsSubquery4->getResultAt(i, j));
		}
	}

	// Test 5: Follows(2,s1)
	FollowsSubquery followsSubquery5 = FollowsSubquery(&synonymTable, pk);
	followsSubquery5.setSynonyms(2, "s1");
	ResultTuple* actualResultsFollowsSubquery5 = followsSubquery5.solve();
	int expectedResultsFollowsSubquery5[1][1] = {
		{3}
	};
	CPPUNIT_ASSERT_EQUAL((size_t)1, actualResultsFollowsSubquery5->getAllResults().size());
	for (size_t i = 0; i < 1; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsFollowsSubquery5[i][j], actualResultsFollowsSubquery5->getResultAt(i, j));
		}
	}

	// Test 6: Follows(1,"a1")
	FollowsSubquery followsSubquery6 = FollowsSubquery(&synonymTable, pk);
	followsSubquery6.setSynonyms(1, "a1");
	ResultTuple* actualResultsFollowsSubquery6 = followsSubquery6.solve();
	int expectedResultsFollowsSubquery6[1][1] = {
		{2}
	};
	CPPUNIT_ASSERT_EQUAL((size_t)1, actualResultsFollowsSubquery6->getAllResults().size());
	for (size_t i = 0; i < 1; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsFollowsSubquery6[i][j], actualResultsFollowsSubquery6->getResultAt(i, j));
		}
	}
	
	// Test 7: Follows(_,s1)
	FollowsSubquery followsSubquery7 = FollowsSubquery(&synonymTable, pk);
	followsSubquery7.setSynonyms("_", "s1");
	ResultTuple* actualResultsFollowsSubquery7 = followsSubquery7.solve();
	int expectedResultsFollowsSubquery7[13][1] = {
		{2}, {3}, {5}, {6}, {8}, {11}, {12}, {13}, {15}, {18}, {19}, {20}, {22}
	};
	CPPUNIT_ASSERT_EQUAL((size_t)13, actualResultsFollowsSubquery7->getAllResults().size());
	for (size_t i = 0; i < 13; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsFollowsSubquery7[i][j], actualResultsFollowsSubquery7->getResultAt(i, j));
		}
	}

	//Test 8 : Follows(_,a1)
	FollowsSubquery followsSubquery8 = FollowsSubquery(&synonymTable, pk);
	followsSubquery8.setSynonyms("_", "a1");
	ResultTuple* actualResultsFollowsSubquery8 = followsSubquery8.solve();
	int expectedResultsFollowsSubquery8[7][1] = {
		{2}, {5}, {12}, {18}, {19}, {20}, {22}
	};
	CPPUNIT_ASSERT_EQUAL((size_t)7, actualResultsFollowsSubquery8->getAllResults().size());
	for (size_t i = 0; i < 7; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsFollowsSubquery8[i][j], actualResultsFollowsSubquery8->getResultAt(i, j));
		}
	}

	// Test 0: Follows(s1, s2)
	FollowsSubquery followssubquery0 = FollowsSubquery(&synonymTable, pk);
	followssubquery0.setSynonyms("s1", "s2");
	ResultTuple* actualResultfollowssubquery0 = followssubquery0.solve();
	int expectedResultfollowssubquery0[13][2] = {
		{1, 2}, {2, 3}, {4, 5}, {5, 6}, {6, 13}, {7, 8}, {8, 11}, {11, 12}, {13, 18}, {14, 15}, {18, 19}, {19, 20}, {21, 22} 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery0)/sizeof(expectedResultfollowssubquery0[0])), actualResultfollowssubquery0->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery0)/sizeof(expectedResultfollowssubquery0[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery0[i])/sizeof(expectedResultfollowssubquery0[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery0[i][j], actualResultfollowssubquery0->getResultAt(i, j));
		}
	}

	// Test 1: Follows(s1, a2)
	FollowsSubquery followssubquery1 = FollowsSubquery(&synonymTable, pk);
	followssubquery1.setSynonyms("s1", "a2");
	ResultTuple* actualResultfollowssubquery1 = followssubquery1.solve();
	int expectedResultfollowssubquery1[7][2] = {
		{1, 2}, {4, 5}, {11, 12}, {13, 18}, {18, 19}, {19, 20}, {21, 22}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery1)/sizeof(expectedResultfollowssubquery1[0])), actualResultfollowssubquery1->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery1)/sizeof(expectedResultfollowssubquery1[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery1[i])/sizeof(expectedResultfollowssubquery1[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery1[i][j], actualResultfollowssubquery1->getResultAt(i, j));
		}
	}

	// Test 2: Follows(s1, w2)
	FollowsSubquery followssubquery2 = FollowsSubquery(&synonymTable, pk);
	followssubquery2.setSynonyms("s1", "w2");
	ResultTuple* actualResultfollowssubquery2 = followssubquery2.solve();
	int expectedResultfollowssubquery2[2][2] = {
		{5, 6}, {14, 15}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery2)/sizeof(expectedResultfollowssubquery2[0])), actualResultfollowssubquery2->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery2)/sizeof(expectedResultfollowssubquery2[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery2[i])/sizeof(expectedResultfollowssubquery2[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery2[i][j], actualResultfollowssubquery2->getResultAt(i, j));
		}
	}

	// Test 3: Follows(s1, i2)
	FollowsSubquery followssubquery3 = FollowsSubquery(&synonymTable, pk);
	followssubquery3.setSynonyms("s1", "i2");
	ResultTuple* actualResultfollowssubquery3 = followssubquery3.solve();
	int expectedResultfollowssubquery3[2][2] = {
		{6, 13}, {7, 8} 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery3)/sizeof(expectedResultfollowssubquery3[0])), actualResultfollowssubquery3->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery3)/sizeof(expectedResultfollowssubquery3[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery3[i])/sizeof(expectedResultfollowssubquery3[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery3[i][j], actualResultfollowssubquery3->getResultAt(i, j));
		}
	}

	// Test 6: Follows(s1, c2)
	FollowsSubquery followssubquery6 = FollowsSubquery(&synonymTable, pk);
	followssubquery6.setSynonyms("s1", "c2");
	ResultTuple* actualResultfollowssubquery6 = followssubquery6.solve();
	int expectedResultfollowssubquery6[2][2] = {
		{2, 3}, {8, 11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery6)/sizeof(expectedResultfollowssubquery6[0])), actualResultfollowssubquery6->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery6)/sizeof(expectedResultfollowssubquery6[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery6[i])/sizeof(expectedResultfollowssubquery6[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery6[i][j], actualResultfollowssubquery6->getResultAt(i, j));
		}
	}

	// Test 7: Follows(s1, l2)
	FollowsSubquery followssubquery7 = FollowsSubquery(&synonymTable, pk);
	followssubquery7.setSynonyms("s1", "l2");
	ResultTuple* actualResultfollowssubquery7 = followssubquery7.solve();
	int expectedResultfollowssubquery7[13][2] = {
		{1, 2}, {2, 3}, {4, 5}, {5, 6}, {6, 13}, {7, 8}, {8, 11}, {11, 12}, {13, 18}, {14, 15}, {18, 19}, {19, 20}, {21, 22} 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery7)/sizeof(expectedResultfollowssubquery7[0])), actualResultfollowssubquery7->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery7)/sizeof(expectedResultfollowssubquery7[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery7[i])/sizeof(expectedResultfollowssubquery7[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery7[i][j], actualResultfollowssubquery7->getResultAt(i, j));
		}
	}

	// Test 9: Follows(s1, _)
	FollowsSubquery followssubquery9 = FollowsSubquery(&synonymTable, pk);
	followssubquery9.setSynonyms("s1", "_");
	ResultTuple* actualResultfollowssubquery9 = followssubquery9.solve();
	int expectedResultfollowssubquery9[13][1] = {
		{1}, {2}, {4}, {5}, {6}, {7}, {8}, {11}, {13}, {14}, {18}, {19}, {21}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery9)/sizeof(expectedResultfollowssubquery9[0])), actualResultfollowssubquery9->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery9)/sizeof(expectedResultfollowssubquery9[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery9[i])/sizeof(expectedResultfollowssubquery9[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery9[i][j], actualResultfollowssubquery9->getResultAt(i, j));
		}
	}

	// Test 10: Follows(s1, 2)
	FollowsSubquery followssubquery10 = FollowsSubquery(&synonymTable, pk);
	followssubquery10.setSynonyms("s1", 2);
	ResultTuple* actualResultfollowssubquery10 = followssubquery10.solve();
	int expectedResultfollowssubquery10[1][1] = {
		{1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery10)/sizeof(expectedResultfollowssubquery10[0])), actualResultfollowssubquery10->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery10)/sizeof(expectedResultfollowssubquery10[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery10[i])/sizeof(expectedResultfollowssubquery10[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery10[i][j], actualResultfollowssubquery10->getResultAt(i, j));
		}
	}

	// Test 11: Follows(s1, 6)
	FollowsSubquery followssubquery11 = FollowsSubquery(&synonymTable, pk);
	followssubquery11.setSynonyms("s1", 6);
	ResultTuple* actualResultfollowssubquery11 = followssubquery11.solve();
	int expectedResultfollowssubquery11[1][1] = {
		{5}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery11)/sizeof(expectedResultfollowssubquery11[0])), actualResultfollowssubquery11->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery11)/sizeof(expectedResultfollowssubquery11[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery11[i])/sizeof(expectedResultfollowssubquery11[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery11[i][j], actualResultfollowssubquery11->getResultAt(i, j));
		}
	}

	// Test 12: Follows(a1, s2)
	FollowsSubquery followssubquery12 = FollowsSubquery(&synonymTable, pk);
	followssubquery12.setSynonyms("a1", "s2");
	ResultTuple* actualResultfollowssubquery12 = followssubquery12.solve();
	int expectedResultfollowssubquery12[9][2] = {
		{1, 2}, {2, 3}, {4, 5}, {5, 6}, {7, 8}, {14, 15}, {18, 19}, {19, 20}, {21, 22}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery12)/sizeof(expectedResultfollowssubquery12[0])), actualResultfollowssubquery12->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery12)/sizeof(expectedResultfollowssubquery12[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery12[i])/sizeof(expectedResultfollowssubquery12[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery12[i][j], actualResultfollowssubquery12->getResultAt(i, j));
		}
	}

	// Test 13: Follows(a1, a2)
	FollowsSubquery followssubquery13 = FollowsSubquery(&synonymTable, pk);
	followssubquery13.setSynonyms("a1", "a2");
	ResultTuple* actualResultfollowssubquery13 = followssubquery13.solve();
	int expectedResultfollowssubquery13[5][2] = {
		{1, 2}, {4, 5}, {18, 19}, {19, 20}, {21, 22}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery13)/sizeof(expectedResultfollowssubquery13[0])), actualResultfollowssubquery13->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery13)/sizeof(expectedResultfollowssubquery13[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery13[i])/sizeof(expectedResultfollowssubquery13[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery13[i][j], actualResultfollowssubquery13->getResultAt(i, j));
		}
	}

	// Test 14: Follows(a1, w2)
	FollowsSubquery followssubquery14 = FollowsSubquery(&synonymTable, pk);
	followssubquery14.setSynonyms("a1", "w2");
	ResultTuple* actualResultfollowssubquery14 = followssubquery14.solve();
	int expectedResultfollowssubquery14[2][2] = {
		{5, 6}, {14, 15}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery14)/sizeof(expectedResultfollowssubquery14[0])), actualResultfollowssubquery14->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery14)/sizeof(expectedResultfollowssubquery14[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery14[i])/sizeof(expectedResultfollowssubquery14[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery14[i][j], actualResultfollowssubquery14->getResultAt(i, j));
		}
	}

	// Test 15: Follows(a1, i2)
	FollowsSubquery followssubquery15 = FollowsSubquery(&synonymTable, pk);
	followssubquery15.setSynonyms("a1", "i2");
	ResultTuple* actualResultfollowssubquery15 = followssubquery15.solve();
	int expectedResultfollowssubquery15[1][2] = {
		{7, 8}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery15)/sizeof(expectedResultfollowssubquery15[0])), actualResultfollowssubquery15->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery15)/sizeof(expectedResultfollowssubquery15[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery15[i])/sizeof(expectedResultfollowssubquery15[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery15[i][j], actualResultfollowssubquery15->getResultAt(i, j));
		}
	}

	// Test 18: Follows(a1, c2)
	FollowsSubquery followssubquery18 = FollowsSubquery(&synonymTable, pk);
	followssubquery18.setSynonyms("a1", "c2");
	ResultTuple* actualResultfollowssubquery18 = followssubquery18.solve();
	int expectedResultfollowssubquery18[1][2] = {
		{2, 3}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery18)/sizeof(expectedResultfollowssubquery18[0])), actualResultfollowssubquery18->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery18)/sizeof(expectedResultfollowssubquery18[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery18[i])/sizeof(expectedResultfollowssubquery18[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery18[i][j], actualResultfollowssubquery18->getResultAt(i, j));
		}
	}

	// Test 19: Follows(a1, l2)
	FollowsSubquery followssubquery19 = FollowsSubquery(&synonymTable, pk);
	followssubquery19.setSynonyms("a1", "l2");
	ResultTuple* actualResultfollowssubquery19 = followssubquery19.solve();
	int expectedResultfollowssubquery19[9][2] = {
		{1, 2}, {2, 3}, {4, 5}, {5, 6}, {7, 8}, {14, 15}, {18, 19}, {19, 20}, {21, 22}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery19)/sizeof(expectedResultfollowssubquery19[0])), actualResultfollowssubquery19->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery19)/sizeof(expectedResultfollowssubquery19[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery19[i])/sizeof(expectedResultfollowssubquery19[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery19[i][j], actualResultfollowssubquery19->getResultAt(i, j));
		}
	}

	// Test 21: Follows(a1, _)
	FollowsSubquery followssubquery21 = FollowsSubquery(&synonymTable, pk);
	followssubquery21.setSynonyms("a1", "_");
	ResultTuple* actualResultfollowssubquery21 = followssubquery21.solve();
	int expectedResultfollowssubquery21[9][1] = {
		{1}, {2}, {4}, {5}, {7}, {14}, {18}, {19}, {21}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery21)/sizeof(expectedResultfollowssubquery21[0])), actualResultfollowssubquery21->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery21)/sizeof(expectedResultfollowssubquery21[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery21[i])/sizeof(expectedResultfollowssubquery21[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery21[i][j], actualResultfollowssubquery21->getResultAt(i, j));
		}
	}

	// Test 22: Follows(a1, 2)
	FollowsSubquery followssubquery22 = FollowsSubquery(&synonymTable, pk);
	followssubquery22.setSynonyms("a1", 2);
	ResultTuple* actualResultfollowssubquery22 = followssubquery22.solve();
	int expectedResultfollowssubquery22[1][1] = {
		{1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery22)/sizeof(expectedResultfollowssubquery22[0])), actualResultfollowssubquery22->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery22)/sizeof(expectedResultfollowssubquery22[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery22[i])/sizeof(expectedResultfollowssubquery22[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery22[i][j], actualResultfollowssubquery22->getResultAt(i, j));
		}
	}

	// Test 23: Follows(a1, 6)
	FollowsSubquery followssubquery23 = FollowsSubquery(&synonymTable, pk);
	followssubquery23.setSynonyms("a1", 6);
	ResultTuple* actualResultfollowssubquery23 = followssubquery23.solve();
	int expectedResultfollowssubquery23[1][1] = {
		{5}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery23)/sizeof(expectedResultfollowssubquery23[0])), actualResultfollowssubquery23->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery23)/sizeof(expectedResultfollowssubquery23[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery23[i])/sizeof(expectedResultfollowssubquery23[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery23[i][j], actualResultfollowssubquery23->getResultAt(i, j));
		}
	}

	// Test 24: Follows(w1, s2)
	FollowsSubquery followssubquery24 = FollowsSubquery(&synonymTable, pk);
	followssubquery24.setSynonyms("w1", "s2");
	ResultTuple* actualResultfollowssubquery24 = followssubquery24.solve();
	int expectedResultfollowssubquery24[1][2] = {
		{6, 13}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery24)/sizeof(expectedResultfollowssubquery24[0])), actualResultfollowssubquery24->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery24)/sizeof(expectedResultfollowssubquery24[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery24[i])/sizeof(expectedResultfollowssubquery24[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery24[i][j], actualResultfollowssubquery24->getResultAt(i, j));
		}
	}

	// Test 25: Follows(w1, a2)
	FollowsSubquery followssubquery25 = FollowsSubquery(&synonymTable, pk);
	followssubquery25.setSynonyms("w1", "a2");
	ResultTuple* actualResultfollowssubquery25 = followssubquery25.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery25->getAllResults().size());

	// Test 26: Follows(w1, w2)
	FollowsSubquery followssubquery26 = FollowsSubquery(&synonymTable, pk);
	followssubquery26.setSynonyms("w1", "w2");
	ResultTuple* actualResultfollowssubquery26 = followssubquery26.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery26->getAllResults().size());

	// Test 27: Follows(w1, i2)
	FollowsSubquery followssubquery27 = FollowsSubquery(&synonymTable, pk);
	followssubquery27.setSynonyms("w1", "i2");
	ResultTuple* actualResultfollowssubquery27 = followssubquery27.solve();
	int expectedResultfollowssubquery27[1][2] = {
		{6, 13}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery27)/sizeof(expectedResultfollowssubquery27[0])), actualResultfollowssubquery27->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery27)/sizeof(expectedResultfollowssubquery27[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery27[i])/sizeof(expectedResultfollowssubquery27[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery27[i][j], actualResultfollowssubquery27->getResultAt(i, j));
		}
	}

	// Test 30: Follows(w1, c2)
	FollowsSubquery followssubquery30 = FollowsSubquery(&synonymTable, pk);
	followssubquery30.setSynonyms("w1", "c2");
	ResultTuple* actualResultfollowssubquery30 = followssubquery30.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery30->getAllResults().size());

	// Test 31: Follows(w1, l2)
	FollowsSubquery followssubquery31 = FollowsSubquery(&synonymTable, pk);
	followssubquery31.setSynonyms("w1", "l2");
	ResultTuple* actualResultfollowssubquery31 = followssubquery31.solve();
	int expectedResultfollowssubquery31[1][2] = {
		{6, 13}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery31)/sizeof(expectedResultfollowssubquery31[0])), actualResultfollowssubquery31->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery31)/sizeof(expectedResultfollowssubquery31[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery31[i])/sizeof(expectedResultfollowssubquery31[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery31[i][j], actualResultfollowssubquery31->getResultAt(i, j));
		}
	}

	// Test 33: Follows(w1, _)
	FollowsSubquery followssubquery33 = FollowsSubquery(&synonymTable, pk);
	followssubquery33.setSynonyms("w1", "_");
	ResultTuple* actualResultfollowssubquery33 = followssubquery33.solve();
	int expectedResultfollowssubquery33[1][1] = {
		{6}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery33)/sizeof(expectedResultfollowssubquery33[0])), actualResultfollowssubquery33->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery33)/sizeof(expectedResultfollowssubquery33[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery33[i])/sizeof(expectedResultfollowssubquery33[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery33[i][j], actualResultfollowssubquery33->getResultAt(i, j));
		}
	}

	// Test 34: Follows(w1, 2)
	FollowsSubquery followssubquery34 = FollowsSubquery(&synonymTable, pk);
	followssubquery34.setSynonyms("w1", 2);
	ResultTuple* actualResultfollowssubquery34 = followssubquery34.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery34->getAllResults().size());

	// Test 35: Follows(w1, 13)
	FollowsSubquery followssubquery35 = FollowsSubquery(&synonymTable, pk);
	followssubquery35.setSynonyms("w1", 13);
	ResultTuple* actualResultfollowssubquery35 = followssubquery35.solve();
	int expectedResultfollowssubquery35[1][1] = {
		{6}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery35)/sizeof(expectedResultfollowssubquery35[0])), actualResultfollowssubquery35->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery35)/sizeof(expectedResultfollowssubquery35[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery35[i])/sizeof(expectedResultfollowssubquery35[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery35[i][j], actualResultfollowssubquery35->getResultAt(i, j));
		}
	}

	// Test 36: Follows(i1, s2)
	FollowsSubquery followssubquery36 = FollowsSubquery(&synonymTable, pk);
	followssubquery36.setSynonyms("i1", "s2");
	ResultTuple* actualResultfollowssubquery36 = followssubquery36.solve();
	int expectedResultfollowssubquery36[2][2] = {
		{8, 11}, {13, 18}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery36)/sizeof(expectedResultfollowssubquery36[0])), actualResultfollowssubquery36->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery36)/sizeof(expectedResultfollowssubquery36[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery36[i])/sizeof(expectedResultfollowssubquery36[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery36[i][j], actualResultfollowssubquery36->getResultAt(i, j));
		}
	}

	// Test 37: Follows(i1, a2)
	FollowsSubquery followssubquery37 = FollowsSubquery(&synonymTable, pk);
	followssubquery37.setSynonyms("i1", "a2");
	ResultTuple* actualResultfollowssubquery37 = followssubquery37.solve();
	int expectedResultfollowssubquery37[1][2] = {
		{13, 18}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery37)/sizeof(expectedResultfollowssubquery37[0])), actualResultfollowssubquery37->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery37)/sizeof(expectedResultfollowssubquery37[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery37[i])/sizeof(expectedResultfollowssubquery37[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery37[i][j], actualResultfollowssubquery37->getResultAt(i, j));
		}
	}

	// Test 38: Follows(i1, w2)
	FollowsSubquery followssubquery38 = FollowsSubquery(&synonymTable, pk);
	followssubquery38.setSynonyms("i1", "w2");
	ResultTuple* actualResultfollowssubquery38 = followssubquery38.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery38->getAllResults().size());

	// Test 39: Follows(i1, i2)
	FollowsSubquery followssubquery39 = FollowsSubquery(&synonymTable, pk);
	followssubquery39.setSynonyms("i1", "i2");
	ResultTuple* actualResultfollowssubquery39 = followssubquery39.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery39->getAllResults().size());

	// Test 42: Follows(i1, c2)
	FollowsSubquery followssubquery42 = FollowsSubquery(&synonymTable, pk);
	followssubquery42.setSynonyms("i1", "c2");
	ResultTuple* actualResultfollowssubquery42 = followssubquery42.solve();
	int expectedResultfollowssubquery42[1][2] = {
		{8, 11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery42)/sizeof(expectedResultfollowssubquery42[0])), actualResultfollowssubquery42->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery42)/sizeof(expectedResultfollowssubquery42[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery42[i])/sizeof(expectedResultfollowssubquery42[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery42[i][j], actualResultfollowssubquery42->getResultAt(i, j));
		}
	}

	// Test 43: Follows(i1, l2)
	FollowsSubquery followssubquery43 = FollowsSubquery(&synonymTable, pk);
	followssubquery43.setSynonyms("i1", "l2");
	ResultTuple* actualResultfollowssubquery43 = followssubquery43.solve();
	int expectedResultfollowssubquery43[2][2] = {
		{8, 11}, {13, 18}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery43)/sizeof(expectedResultfollowssubquery43[0])), actualResultfollowssubquery43->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery43)/sizeof(expectedResultfollowssubquery43[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery43[i])/sizeof(expectedResultfollowssubquery43[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery43[i][j], actualResultfollowssubquery43->getResultAt(i, j));
		}
	}

	// Test 45: Follows(i1, _)
	FollowsSubquery followssubquery45 = FollowsSubquery(&synonymTable, pk);
	followssubquery45.setSynonyms("i1", "_");
	ResultTuple* actualResultfollowssubquery45 = followssubquery45.solve();
	int expectedResultfollowssubquery45[2][1] = {
		{8}, {13}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery45)/sizeof(expectedResultfollowssubquery45[0])), actualResultfollowssubquery45->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery45)/sizeof(expectedResultfollowssubquery45[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery45[i])/sizeof(expectedResultfollowssubquery45[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery45[i][j], actualResultfollowssubquery45->getResultAt(i, j));
		}
	}

	// Test 46: Follows(i1, 2)
	FollowsSubquery followssubquery46 = FollowsSubquery(&synonymTable, pk);
	followssubquery46.setSynonyms("i1", 2);
	ResultTuple* actualResultfollowssubquery46 = followssubquery46.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery46->getAllResults().size());

	// Test 47: Follows(i1, 18)
	FollowsSubquery followssubquery47 = FollowsSubquery(&synonymTable, pk);
	followssubquery47.setSynonyms("i1", 18);
	ResultTuple* actualResultfollowssubquery47 = followssubquery47.solve();
	int expectedResultfollowssubquery47[1][1] = {
		{13}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery47)/sizeof(expectedResultfollowssubquery47[0])), actualResultfollowssubquery47->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery47)/sizeof(expectedResultfollowssubquery47[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery47[i])/sizeof(expectedResultfollowssubquery47[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery47[i][j], actualResultfollowssubquery47->getResultAt(i, j));
		}
	}

	// Test 72: Follows(c1, s2)
	FollowsSubquery followssubquery72 = FollowsSubquery(&synonymTable, pk);
	followssubquery72.setSynonyms("c1", "s2");
	ResultTuple* actualResultfollowssubquery72 = followssubquery72.solve();
	int expectedResultfollowssubquery72[1][2] = {
		{11, 12}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery72)/sizeof(expectedResultfollowssubquery72[0])), actualResultfollowssubquery72->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery72)/sizeof(expectedResultfollowssubquery72[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery72[i])/sizeof(expectedResultfollowssubquery72[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery72[i][j], actualResultfollowssubquery72->getResultAt(i, j));
		}
	}

	// Test 73: Follows(c1, a2)
	FollowsSubquery followssubquery73 = FollowsSubquery(&synonymTable, pk);
	followssubquery73.setSynonyms("c1", "a2");
	ResultTuple* actualResultfollowssubquery73 = followssubquery73.solve();
	int expectedResultfollowssubquery73[1][2] = {
		{11, 12}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery73)/sizeof(expectedResultfollowssubquery73[0])), actualResultfollowssubquery73->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery73)/sizeof(expectedResultfollowssubquery73[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery73[i])/sizeof(expectedResultfollowssubquery73[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery73[i][j], actualResultfollowssubquery73->getResultAt(i, j));
		}
	}

	// Test 74: Follows(c1, w2)
	FollowsSubquery followssubquery74 = FollowsSubquery(&synonymTable, pk);
	followssubquery74.setSynonyms("c1", "w2");
	ResultTuple* actualResultfollowssubquery74 = followssubquery74.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery74->getAllResults().size());

	// Test 75: Follows(c1, i2)
	FollowsSubquery followssubquery75 = FollowsSubquery(&synonymTable, pk);
	followssubquery75.setSynonyms("c1", "i2");
	ResultTuple* actualResultfollowssubquery75 = followssubquery75.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery75->getAllResults().size());

	// Test 78: Follows(c1, c2)
	FollowsSubquery followssubquery78 = FollowsSubquery(&synonymTable, pk);
	followssubquery78.setSynonyms("c1", "c2");
	ResultTuple* actualResultfollowssubquery78 = followssubquery78.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery78->getAllResults().size());

	// Test 79: Follows(c1, l2)
	FollowsSubquery followssubquery79 = FollowsSubquery(&synonymTable, pk);
	followssubquery79.setSynonyms("c1", "l2");
	ResultTuple* actualResultfollowssubquery79 = followssubquery79.solve();
	int expectedResultfollowssubquery79[1][2] = {
		{11, 12}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery79)/sizeof(expectedResultfollowssubquery79[0])), actualResultfollowssubquery79->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery79)/sizeof(expectedResultfollowssubquery79[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery79[i])/sizeof(expectedResultfollowssubquery79[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery79[i][j], actualResultfollowssubquery79->getResultAt(i, j));
		}
	}

	// Test 81: Follows(c1, _)
	FollowsSubquery followssubquery81 = FollowsSubquery(&synonymTable, pk);
	followssubquery81.setSynonyms("c1", "_");
	ResultTuple* actualResultfollowssubquery81 = followssubquery81.solve();
	int expectedResultfollowssubquery81[1][1] = {
		{11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery81)/sizeof(expectedResultfollowssubquery81[0])), actualResultfollowssubquery81->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery81)/sizeof(expectedResultfollowssubquery81[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery81[i])/sizeof(expectedResultfollowssubquery81[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery81[i][j], actualResultfollowssubquery81->getResultAt(i, j));
		}
	}

	// Test 82: Follows(c1, 2)
	FollowsSubquery followssubquery82 = FollowsSubquery(&synonymTable, pk);
	followssubquery82.setSynonyms("c1", 2);
	ResultTuple* actualResultfollowssubquery82 = followssubquery82.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery82->getAllResults().size());

	// Test 83: Follows(c1, 12)
	FollowsSubquery followssubquery83 = FollowsSubquery(&synonymTable, pk);
	followssubquery83.setSynonyms("c1", 12);
	ResultTuple* actualResultfollowssubquery83 = followssubquery83.solve();
	int expectedResultfollowssubquery83[1][1] = {
		{11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery83)/sizeof(expectedResultfollowssubquery83[0])), actualResultfollowssubquery83->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery83)/sizeof(expectedResultfollowssubquery83[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery83[i])/sizeof(expectedResultfollowssubquery83[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery83[i][j], actualResultfollowssubquery83->getResultAt(i, j));
		}
	}

	// Test 84: Follows(l1, s2)
	FollowsSubquery followssubquery84 = FollowsSubquery(&synonymTable, pk);
	followssubquery84.setSynonyms("l1", "s2");
	ResultTuple* actualResultfollowssubquery84 = followssubquery84.solve();
	int expectedResultfollowssubquery84[13][2] = {
		{1, 2}, {2, 3}, {4, 5}, {5, 6}, {6, 13}, {7, 8}, {8, 11}, {11, 12}, {13, 18}, {14, 15}, {18, 19}, {19, 20}, {21, 22} 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery84)/sizeof(expectedResultfollowssubquery84[0])), actualResultfollowssubquery84->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery84)/sizeof(expectedResultfollowssubquery84[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery84[i])/sizeof(expectedResultfollowssubquery84[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery84[i][j], actualResultfollowssubquery84->getResultAt(i, j));
		}
	}

	// Test 85: Follows(l1, a2)
	FollowsSubquery followssubquery85 = FollowsSubquery(&synonymTable, pk);
	followssubquery85.setSynonyms("l1", "a2");
	ResultTuple* actualResultfollowssubquery85 = followssubquery85.solve();
	int expectedResultfollowssubquery85[7][2] = {
		{1, 2}, {4, 5}, {11, 12}, {13, 18}, {18, 19}, {19, 20}, {21, 22}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery85)/sizeof(expectedResultfollowssubquery85[0])), actualResultfollowssubquery85->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery85)/sizeof(expectedResultfollowssubquery85[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery85[i])/sizeof(expectedResultfollowssubquery85[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery85[i][j], actualResultfollowssubquery85->getResultAt(i, j));
		}
	}

	// Test 86: Follows(l1, w2)
	FollowsSubquery followssubquery86 = FollowsSubquery(&synonymTable, pk);
	followssubquery86.setSynonyms("l1", "w2");
	ResultTuple* actualResultfollowssubquery86 = followssubquery86.solve();
	int expectedResultfollowssubquery86[2][2] = {
		{5, 6}, {14, 15}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery86)/sizeof(expectedResultfollowssubquery86[0])), actualResultfollowssubquery86->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery86)/sizeof(expectedResultfollowssubquery86[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery86[i])/sizeof(expectedResultfollowssubquery86[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery86[i][j], actualResultfollowssubquery86->getResultAt(i, j));
		}
	}

	// Test 87: Follows(l1, i2)
	FollowsSubquery followssubquery87 = FollowsSubquery(&synonymTable, pk);
	followssubquery87.setSynonyms("l1", "i2");
	ResultTuple* actualResultfollowssubquery87 = followssubquery87.solve();
	int expectedResultfollowssubquery87[2][2] = {
		{6, 13}, {7, 8} 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery87)/sizeof(expectedResultfollowssubquery87[0])), actualResultfollowssubquery87->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery87)/sizeof(expectedResultfollowssubquery87[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery87[i])/sizeof(expectedResultfollowssubquery87[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery87[i][j], actualResultfollowssubquery87->getResultAt(i, j));
		}
	}

	// Test 90: Follows(l1, c2)
	FollowsSubquery followssubquery90 = FollowsSubquery(&synonymTable, pk);
	followssubquery90.setSynonyms("l1", "c2");
	ResultTuple* actualResultfollowssubquery90 = followssubquery90.solve();
	int expectedResultfollowssubquery90[2][2] = {
		{2, 3}, {8, 11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery90)/sizeof(expectedResultfollowssubquery90[0])), actualResultfollowssubquery90->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery90)/sizeof(expectedResultfollowssubquery90[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery90[i])/sizeof(expectedResultfollowssubquery90[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery90[i][j], actualResultfollowssubquery90->getResultAt(i, j));
		}
	}

	// Test 91: Follows(l1, l2)
	FollowsSubquery followssubquery91 = FollowsSubquery(&synonymTable, pk);
	followssubquery91.setSynonyms("l1", "l2");
	ResultTuple* actualResultfollowssubquery91 = followssubquery91.solve();
	int expectedResultfollowssubquery91[13][2] = {
		{1, 2}, {2, 3}, {4, 5}, {5, 6}, {6, 13}, {7, 8}, {8, 11}, {11, 12}, {13, 18}, {14, 15}, {18, 19}, {19, 20}, {21, 22} 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery91)/sizeof(expectedResultfollowssubquery91[0])), actualResultfollowssubquery91->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery91)/sizeof(expectedResultfollowssubquery91[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery91[i])/sizeof(expectedResultfollowssubquery91[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery91[i][j], actualResultfollowssubquery91->getResultAt(i, j));
		}
	}

	// Test 93: Follows(l1, _)
	FollowsSubquery followssubquery93 = FollowsSubquery(&synonymTable, pk);
	followssubquery93.setSynonyms("l1", "_");
	ResultTuple* actualResultfollowssubquery93 = followssubquery93.solve();
	int expectedResultfollowssubquery93[13][1] = {
		{1}, {2}, {4}, {5}, {6}, {7}, {8}, {11}, {13}, {14}, {18}, {19}, {21} 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery93)/sizeof(expectedResultfollowssubquery93[0])), actualResultfollowssubquery93->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery93)/sizeof(expectedResultfollowssubquery93[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery93[i])/sizeof(expectedResultfollowssubquery93[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery93[i][j], actualResultfollowssubquery93->getResultAt(i, j));
		}
	}

	// Test 94: Follows(l1, 2)
	FollowsSubquery followssubquery94 = FollowsSubquery(&synonymTable, pk);
	followssubquery94.setSynonyms("l1", 2);
	ResultTuple* actualResultfollowssubquery94 = followssubquery94.solve();
	int expectedResultfollowssubquery94[1][1] = {
		{1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery94)/sizeof(expectedResultfollowssubquery94[0])), actualResultfollowssubquery94->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery94)/sizeof(expectedResultfollowssubquery94[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery94[i])/sizeof(expectedResultfollowssubquery94[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery94[i][j], actualResultfollowssubquery94->getResultAt(i, j));
		}
	}

	// Test 95: Follows(l1, 6)
	FollowsSubquery followssubquery95 = FollowsSubquery(&synonymTable, pk);
	followssubquery95.setSynonyms("l1", 6);
	ResultTuple* actualResultfollowssubquery95 = followssubquery95.solve();
	int expectedResultfollowssubquery95[1][1] = {
		{5}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery95)/sizeof(expectedResultfollowssubquery95[0])), actualResultfollowssubquery95->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery95)/sizeof(expectedResultfollowssubquery95[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery95[i])/sizeof(expectedResultfollowssubquery95[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery95[i][j], actualResultfollowssubquery95->getResultAt(i, j));
		}
	}

	// Test 108: Follows(_, s2)
	FollowsSubquery followssubquery108 = FollowsSubquery(&synonymTable, pk);
	followssubquery108.setSynonyms("_", "s2");
	ResultTuple* actualResultfollowssubquery108 = followssubquery108.solve();
	int expectedResultfollowssubquery108[13][1] = {
		{2}, {3}, {5}, {6}, {8}, {11}, {12}, {13}, {15}, {18}, {19}, {20}, {22} 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery108)/sizeof(expectedResultfollowssubquery108[0])), actualResultfollowssubquery108->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery108)/sizeof(expectedResultfollowssubquery108[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery108[i])/sizeof(expectedResultfollowssubquery108[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery108[i][j], actualResultfollowssubquery108->getResultAt(i, j));
		}
	}

	// Test 109: Follows(_, a2)
	FollowsSubquery followssubquery109 = FollowsSubquery(&synonymTable, pk);
	followssubquery109.setSynonyms("_", "a2");
	ResultTuple* actualResultfollowssubquery109 = followssubquery109.solve();
	int expectedResultfollowssubquery109[7][1] = {
		{2}, {5}, {12}, {18}, {19}, {20}, {22}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery109)/sizeof(expectedResultfollowssubquery109[0])), actualResultfollowssubquery109->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery109)/sizeof(expectedResultfollowssubquery109[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery109[i])/sizeof(expectedResultfollowssubquery109[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery109[i][j], actualResultfollowssubquery109->getResultAt(i, j));
		}
	}

	// Test 110: Follows(_, w2)
	FollowsSubquery followssubquery110 = FollowsSubquery(&synonymTable, pk);
	followssubquery110.setSynonyms("_", "w2");
	ResultTuple* actualResultfollowssubquery110 = followssubquery110.solve();
	int expectedResultfollowssubquery110[2][1] = {
		{6}, {15}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery110)/sizeof(expectedResultfollowssubquery110[0])), actualResultfollowssubquery110->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery110)/sizeof(expectedResultfollowssubquery110[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery110[i])/sizeof(expectedResultfollowssubquery110[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery110[i][j], actualResultfollowssubquery110->getResultAt(i, j));
		}
	}

	// Test 111: Follows(_, i2)
	FollowsSubquery followssubquery111 = FollowsSubquery(&synonymTable, pk);
	followssubquery111.setSynonyms("_", "i2");
	ResultTuple* actualResultfollowssubquery111 = followssubquery111.solve();
	int expectedResultfollowssubquery111[2][1] = {
		{8}, {13}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery111)/sizeof(expectedResultfollowssubquery111[0])), actualResultfollowssubquery111->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery111)/sizeof(expectedResultfollowssubquery111[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery111[i])/sizeof(expectedResultfollowssubquery111[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery111[i][j], actualResultfollowssubquery111->getResultAt(i, j));
		}
	}

	// Test 114: Follows(_, c2)
	FollowsSubquery followssubquery114 = FollowsSubquery(&synonymTable, pk);
	followssubquery114.setSynonyms("_", "c2");
	ResultTuple* actualResultfollowssubquery114 = followssubquery114.solve();
	int expectedResultfollowssubquery114[2][1] = {
		{3}, {11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery114)/sizeof(expectedResultfollowssubquery114[0])), actualResultfollowssubquery114->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery114)/sizeof(expectedResultfollowssubquery114[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery114[i])/sizeof(expectedResultfollowssubquery114[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery114[i][j], actualResultfollowssubquery114->getResultAt(i, j));
		}
	}

	// Test 115: Follows(_, l2)
	FollowsSubquery followssubquery115 = FollowsSubquery(&synonymTable, pk);
	followssubquery115.setSynonyms("_", "l2");
	ResultTuple* actualResultfollowssubquery115 = followssubquery115.solve();
	int expectedResultfollowssubquery115[13][1] = {
		{2}, {3}, {5}, {6}, {8}, {11}, {12}, {13}, {15}, {18}, {19}, {20}, {22} 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery115)/sizeof(expectedResultfollowssubquery115[0])), actualResultfollowssubquery115->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery115)/sizeof(expectedResultfollowssubquery115[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery115[i])/sizeof(expectedResultfollowssubquery115[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery115[i][j], actualResultfollowssubquery115->getResultAt(i, j));
		}
	}

	// Test 117: Follows(_, _)
	FollowsSubquery followssubquery117 = FollowsSubquery(&synonymTable, pk);
	followssubquery117.setSynonyms("_", "_");
	ResultTuple* actualResultfollowssubquery117 = followssubquery117.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery117->getAllResults().size());
	CPPUNIT_ASSERT(actualResultfollowssubquery117->isBool());
	CPPUNIT_ASSERT(!actualResultfollowssubquery117->isEmpty());

	// Test 118: Follows(_, 2)
	FollowsSubquery followssubquery118 = FollowsSubquery(&synonymTable, pk);
	followssubquery118.setSynonyms("_", 2);
	ResultTuple* actualResultfollowssubquery118 = followssubquery118.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery118->getAllResults().size());
	CPPUNIT_ASSERT(actualResultfollowssubquery118->isBool());
	CPPUNIT_ASSERT(!actualResultfollowssubquery118->isEmpty());

	// Test 119: Follows(_, 7)
	FollowsSubquery followssubquery119 = FollowsSubquery(&synonymTable, pk);
	followssubquery119.setSynonyms("_", 7);
	ResultTuple* actualResultfollowssubquery119 = followssubquery119.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery119->getAllResults().size());
	CPPUNIT_ASSERT(actualResultfollowssubquery119->isBool());
	CPPUNIT_ASSERT(actualResultfollowssubquery119->isEmpty());

	// Test 120: Follows(1, s2)
	FollowsSubquery followssubquery120 = FollowsSubquery(&synonymTable, pk);
	followssubquery120.setSynonyms(1, "s2");
	ResultTuple* actualResultfollowssubquery120 = followssubquery120.solve();
	int expectedResultfollowssubquery120[1][1] = {
		{2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery120)/sizeof(expectedResultfollowssubquery120[0])), actualResultfollowssubquery120->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery120)/sizeof(expectedResultfollowssubquery120[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery120[i])/sizeof(expectedResultfollowssubquery120[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery120[i][j], actualResultfollowssubquery120->getResultAt(i, j));
		}
	}

	// Test 121: Follows(1, a2)
	FollowsSubquery followssubquery121 = FollowsSubquery(&synonymTable, pk);
	followssubquery121.setSynonyms(1, "a2");
	ResultTuple* actualResultfollowssubquery121 = followssubquery121.solve();
	int expectedResultfollowssubquery121[1][1] = {
		{2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery121)/sizeof(expectedResultfollowssubquery121[0])), actualResultfollowssubquery121->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery121)/sizeof(expectedResultfollowssubquery121[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery121[i])/sizeof(expectedResultfollowssubquery121[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery121[i][j], actualResultfollowssubquery121->getResultAt(i, j));
		}
	}

	// Test 122: Follows(1, w2)
	FollowsSubquery followssubquery122 = FollowsSubquery(&synonymTable, pk);
	followssubquery122.setSynonyms(1, "w2");
	ResultTuple* actualResultfollowssubquery122 = followssubquery122.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery122->getAllResults().size());

	// Test 123: Follows(1, i2)
	FollowsSubquery followssubquery123 = FollowsSubquery(&synonymTable, pk);
	followssubquery123.setSynonyms(1, "i2");
	ResultTuple* actualResultfollowssubquery123 = followssubquery123.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery123->getAllResults().size());

	// Test 126: Follows(1, c2)
	FollowsSubquery followssubquery126 = FollowsSubquery(&synonymTable, pk);
	followssubquery126.setSynonyms(1, "c2");
	ResultTuple* actualResultfollowssubquery126 = followssubquery126.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery126->getAllResults().size());

	// Test 127: Follows(1, l2)
	FollowsSubquery followssubquery127 = FollowsSubquery(&synonymTable, pk);
	followssubquery127.setSynonyms(1, "l2");
	ResultTuple* actualResultfollowssubquery127 = followssubquery127.solve();
	int expectedResultfollowssubquery127[1][1] = {
		{2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery127)/sizeof(expectedResultfollowssubquery127[0])), actualResultfollowssubquery127->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery127)/sizeof(expectedResultfollowssubquery127[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery127[i])/sizeof(expectedResultfollowssubquery127[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery127[i][j], actualResultfollowssubquery127->getResultAt(i, j));
		}
	}

	// Test 129: Follows(1, _)
	FollowsSubquery followssubquery129 = FollowsSubquery(&synonymTable, pk);
	followssubquery129.setSynonyms(1, "_");
	ResultTuple* actualResultfollowssubquery129 = followssubquery129.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery129->getAllResults().size());
	CPPUNIT_ASSERT(actualResultfollowssubquery129->isBool());
	CPPUNIT_ASSERT(!actualResultfollowssubquery129->isEmpty());

	// Test 130: Follows(1, 2)
	FollowsSubquery followssubquery130 = FollowsSubquery(&synonymTable, pk);
	followssubquery130.setSynonyms(1, 2);
	ResultTuple* actualResultfollowssubquery130 = followssubquery130.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery130->getAllResults().size());
	CPPUNIT_ASSERT(actualResultfollowssubquery130->isBool());
	CPPUNIT_ASSERT(!actualResultfollowssubquery130->isEmpty());

	// Test 131: Follows(1, 6)
	FollowsSubquery followssubquery131 = FollowsSubquery(&synonymTable, pk);
	followssubquery131.setSynonyms(1, 6);
	ResultTuple* actualResultfollowssubquery131 = followssubquery131.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery131->getAllResults().size());
	CPPUNIT_ASSERT(actualResultfollowssubquery131->isBool());
	CPPUNIT_ASSERT(actualResultfollowssubquery131->isEmpty());

	// Test 132: Follows(5, s2)
	FollowsSubquery followssubquery132 = FollowsSubquery(&synonymTable, pk);
	followssubquery132.setSynonyms(5, "s2");
	ResultTuple* actualResultfollowssubquery132 = followssubquery132.solve();
	int expectedResultfollowssubquery132[1][1] = {
		{6}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery132)/sizeof(expectedResultfollowssubquery132[0])), actualResultfollowssubquery132->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery132)/sizeof(expectedResultfollowssubquery132[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery132[i])/sizeof(expectedResultfollowssubquery132[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery132[i][j], actualResultfollowssubquery132->getResultAt(i, j));
		}
	}

	// Test 133: Follows(5, a2)
	FollowsSubquery followssubquery133 = FollowsSubquery(&synonymTable, pk);
	followssubquery133.setSynonyms(5, "a2");
	ResultTuple* actualResultfollowssubquery133 = followssubquery133.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery133->getAllResults().size());

	// Test 134: Follows(5, w2)
	FollowsSubquery followssubquery134 = FollowsSubquery(&synonymTable, pk);
	followssubquery134.setSynonyms(5, "w2");
	ResultTuple* actualResultfollowssubquery134 = followssubquery134.solve();
	int expectedResultfollowssubquery134[1][1] = {
		{6}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery134)/sizeof(expectedResultfollowssubquery134[0])), actualResultfollowssubquery134->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery134)/sizeof(expectedResultfollowssubquery134[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery134[i])/sizeof(expectedResultfollowssubquery134[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery134[i][j], actualResultfollowssubquery134->getResultAt(i, j));
		}
	}

	// Test 135: Follows(7, i2)
	FollowsSubquery followssubquery135 = FollowsSubquery(&synonymTable, pk);
	followssubquery135.setSynonyms(7, "i2");
	ResultTuple* actualResultfollowssubquery135 = followssubquery135.solve();
	int expectedResultfollowssubquery135[1][1] = {
		{8}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery135)/sizeof(expectedResultfollowssubquery135[0])), actualResultfollowssubquery135->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery135)/sizeof(expectedResultfollowssubquery135[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery135[i])/sizeof(expectedResultfollowssubquery135[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery135[i][j], actualResultfollowssubquery135->getResultAt(i, j));
		}
	}

	// Test 138: Follows(8, c2)
	FollowsSubquery followssubquery138 = FollowsSubquery(&synonymTable, pk);
	followssubquery138.setSynonyms(8, "c2");
	ResultTuple* actualResultfollowssubquery138 = followssubquery138.solve();
	int expectedResultfollowssubquery138[1][1] = {
		{11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery138)/sizeof(expectedResultfollowssubquery138[0])), actualResultfollowssubquery138->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery138)/sizeof(expectedResultfollowssubquery138[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery138[i])/sizeof(expectedResultfollowssubquery138[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery138[i][j], actualResultfollowssubquery138->getResultAt(i, j));
		}
	}

	// Test 139: Follows(5, l2)
	FollowsSubquery followssubquery139 = FollowsSubquery(&synonymTable, pk);
	followssubquery139.setSynonyms(5, "l2");
	ResultTuple* actualResultfollowssubquery139 = followssubquery139.solve();
	int expectedResultfollowssubquery139[1][1] = {
		{6}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery139)/sizeof(expectedResultfollowssubquery139[0])), actualResultfollowssubquery139->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery139)/sizeof(expectedResultfollowssubquery139[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery139[i])/sizeof(expectedResultfollowssubquery139[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery139[i][j], actualResultfollowssubquery139->getResultAt(i, j));
		}
	}

	// Test 141: Follows(5, _)
	FollowsSubquery followssubquery141 = FollowsSubquery(&synonymTable, pk);
	followssubquery141.setSynonyms(5, "_");
	ResultTuple* actualResultfollowssubquery141 = followssubquery141.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery141->getAllResults().size());
	CPPUNIT_ASSERT(actualResultfollowssubquery141->isBool());
	CPPUNIT_ASSERT(!actualResultfollowssubquery141->isEmpty());

	// Test 142: Follows(5, 2)
	FollowsSubquery followssubquery142 = FollowsSubquery(&synonymTable, pk);
	followssubquery142.setSynonyms(5, 2);
	ResultTuple* actualResultfollowssubquery142 = followssubquery142.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery142->getAllResults().size());
	CPPUNIT_ASSERT(actualResultfollowssubquery142->isBool());
	CPPUNIT_ASSERT(actualResultfollowssubquery142->isEmpty());

	// Test 143: Follows(5, 6)
	FollowsSubquery followssubquery143 = FollowsSubquery(&synonymTable, pk);
	followssubquery143.setSynonyms(5, 6);
	ResultTuple* actualResultfollowssubquery143 = followssubquery143.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery143->getAllResults().size());
	CPPUNIT_ASSERT(actualResultfollowssubquery143->isBool());
	CPPUNIT_ASSERT(!actualResultfollowssubquery143->isEmpty());
}

void SubqueryTest::testFollowsTuple(){
	// testTuple:
	//  s1  |  a1  |  w1  |  i2  |  c2  |  l1  |  const1  |  v1  |  proc1  |
	//  1   |  1   |  6   |  8   |  3   |  1   |  0       |  0   |  0      |
	//  1   |  2   |  6   |  8   |  3   |  1   |  0       |  0   |  0      |
	//  1   |  1   |  15  |  8   |  3   |  1   |  0       |  0   |  0      |
	//  1   |  2   |  6   |  13  |  3   |  1   |  0       |  0   |  0      |
	//  1   |  1   |  6   |  8   |  11  |  1   |  0       |  0   |  0      |
	//  8   |  2   |  6   |  8   |  3   |  7   |  0       |  0   |  0      |
	//  1   |  1   |  6   |  8   |  3   |  1   |  3       |  0   |  0      |
	//  3   |  2   |  6   |  8   |  3   |  1   |  0       |  2   |  0      |
	//  1   |  2   |  6   |  8   |  3   |  1   |  0       |  2   |  1      |
	ResultTuple testTuple = ResultTuple();
	int index = testTuple.addSynonym("s1");
	testTuple.addSynonymToMap("s1", index);
	index = testTuple.addSynonym("a1");
	testTuple.addSynonymToMap("a1", index);
	index = testTuple.addSynonym("w1");
	testTuple.addSynonymToMap("w1", index);
	index = testTuple.addSynonym("i2");
	testTuple.addSynonymToMap("i2", index);
	index = testTuple.addSynonym("c2");
	testTuple.addSynonymToMap("c2", index);
	index = testTuple.addSynonym("l1");
	testTuple.addSynonymToMap("l1", index);
	index = testTuple.addSynonym("const1");
	testTuple.addSynonymToMap("const1", index);
	index = testTuple.addSynonym("v1");
	testTuple.addSynonymToMap("v1", index);
	index = testTuple.addSynonym("proc1");
	testTuple.addSynonymToMap("proc1", index);
	int data[9][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	for (int i = 0; i < 9; i++){
		vector<int> tempVector = vector<int>();
		testTuple.addResultRow(tempVector);
		for (int j = 0; j < 9; j++){
			testTuple.addResult(i, data[i][j]);
		}
	}

	// Test 0: Follows(s1, s2)
	FollowsSubquery followssubquery0 = FollowsSubquery(&synonymTable, pk);
	followssubquery0.setSynonyms("s1", "s2");
	ResultTuple* actualResultfollowssubquery0 = followssubquery0.solve(&testTuple);
	int expectedResultfollowssubquery0[8][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  3},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  2},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  11},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery0)/sizeof(expectedResultfollowssubquery0[0])), actualResultfollowssubquery0->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery0)/sizeof(expectedResultfollowssubquery0[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery0[i])/sizeof(expectedResultfollowssubquery0[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery0[i][j], actualResultfollowssubquery0->getResultAt(i, j));
		}
	}

	// Test 1: Follows(s1, a2)
	FollowsSubquery followssubquery1 = FollowsSubquery(&synonymTable, pk);
	followssubquery1.setSynonyms("s1", "a2");
	ResultTuple* actualResultfollowssubquery1 = followssubquery1.solve(&testTuple);
	int expectedResultfollowssubquery1[6][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery1)/sizeof(expectedResultfollowssubquery1[0])), actualResultfollowssubquery1->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery1)/sizeof(expectedResultfollowssubquery1[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery1[i])/sizeof(expectedResultfollowssubquery1[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery1[i][j], actualResultfollowssubquery1->getResultAt(i, j));
		}
	}

	// Test 2: Follows(s1, w2)
	FollowsSubquery followssubquery2 = FollowsSubquery(&synonymTable, pk);
	followssubquery2.setSynonyms("s1", "w2");
	ResultTuple* actualResultfollowssubquery2 = followssubquery2.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery2->getAllResults().size());

	// Test 3: Follows(s1, i2)
	FollowsSubquery followssubquery3 = FollowsSubquery(&synonymTable, pk);
	followssubquery3.setSynonyms("s1", "i2");
	ResultTuple* actualResultfollowssubquery3 = followssubquery3.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery3->getAllResults().size());

	// Test 6: Follows(s1, c2)
	FollowsSubquery followssubquery6 = FollowsSubquery(&synonymTable, pk);
	followssubquery6.setSynonyms("s1", "c2");
	ResultTuple* actualResultfollowssubquery6 = followssubquery6.solve(&testTuple);
	int expectedResultfollowssubquery6[1][9] = {
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery6)/sizeof(expectedResultfollowssubquery6[0])), actualResultfollowssubquery6->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery6)/sizeof(expectedResultfollowssubquery6[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery6[i])/sizeof(expectedResultfollowssubquery6[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery6[i][j], actualResultfollowssubquery6->getResultAt(i, j));
		}
	}

	// Test 7: Follows(s1, l2)
	FollowsSubquery followssubquery7 = FollowsSubquery(&synonymTable, pk);
	followssubquery7.setSynonyms("s1", "l2");
	ResultTuple* actualResultfollowssubquery7 = followssubquery7.solve(&testTuple);
	int expectedResultfollowssubquery7[8][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  3},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  2},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  11},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery7)/sizeof(expectedResultfollowssubquery7[0])), actualResultfollowssubquery7->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery7)/sizeof(expectedResultfollowssubquery7[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery7[i])/sizeof(expectedResultfollowssubquery7[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery7[i][j], actualResultfollowssubquery7->getResultAt(i, j));
		}
	}

	// Test 9: Follows(s1, _)
	FollowsSubquery followssubquery9 = FollowsSubquery(&synonymTable, pk);
	followssubquery9.setSynonyms("s1", "_");
	ResultTuple* actualResultfollowssubquery9 = followssubquery9.solve(&testTuple);
	int expectedResultfollowssubquery9[8][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery9)/sizeof(expectedResultfollowssubquery9[0])), actualResultfollowssubquery9->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery9)/sizeof(expectedResultfollowssubquery9[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery9[i])/sizeof(expectedResultfollowssubquery9[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery9[i][j], actualResultfollowssubquery9->getResultAt(i, j));
		}
	}

	// Test 10: Follows(s1, 2)
	FollowsSubquery followssubquery10 = FollowsSubquery(&synonymTable, pk);
	followssubquery10.setSynonyms("s1", 2);
	ResultTuple* actualResultfollowssubquery10 = followssubquery10.solve(&testTuple);
	int expectedResultfollowssubquery10[6][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery10)/sizeof(expectedResultfollowssubquery10[0])), actualResultfollowssubquery10->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery10)/sizeof(expectedResultfollowssubquery10[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery10[i])/sizeof(expectedResultfollowssubquery10[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery10[i][j], actualResultfollowssubquery10->getResultAt(i, j));
		}
	}

	// Test 11: Follows(s1, 6)
	FollowsSubquery followssubquery11 = FollowsSubquery(&synonymTable, pk);
	followssubquery11.setSynonyms("s1", 6);
	ResultTuple* actualResultfollowssubquery11 = followssubquery11.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery11->getAllResults().size());

	// Test 12: Follows(a1, s2)
	FollowsSubquery followssubquery12 = FollowsSubquery(&synonymTable, pk);
	followssubquery12.setSynonyms("a1", "s2");
	ResultTuple* actualResultfollowssubquery12 = followssubquery12.solve(&testTuple);
	int expectedResultfollowssubquery12[9][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  3},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  3},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  2},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  3},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  2},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  3},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  3}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery12)/sizeof(expectedResultfollowssubquery12[0])), actualResultfollowssubquery12->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery12)/sizeof(expectedResultfollowssubquery12[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery12[i])/sizeof(expectedResultfollowssubquery12[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery12[i][j], actualResultfollowssubquery12->getResultAt(i, j));
		}
	}

	// Test 13: Follows(a1, a2)
	FollowsSubquery followssubquery13 = FollowsSubquery(&synonymTable, pk);
	followssubquery13.setSynonyms("a1", "a2");
	ResultTuple* actualResultfollowssubquery13 = followssubquery13.solve(&testTuple);
	int expectedResultfollowssubquery13[4][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  2},
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery13)/sizeof(expectedResultfollowssubquery13[0])), actualResultfollowssubquery13->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery13)/sizeof(expectedResultfollowssubquery13[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery13[i])/sizeof(expectedResultfollowssubquery13[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery13[i][j], actualResultfollowssubquery13->getResultAt(i, j));
		}
	}

	// Test 14: Follows(a1, w2)
	FollowsSubquery followssubquery14 = FollowsSubquery(&synonymTable, pk);
	followssubquery14.setSynonyms("a1", "w2");
	ResultTuple* actualResultfollowssubquery14 = followssubquery14.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery14->getAllResults().size());

	// Test 15: Follows(a1, i2)
	FollowsSubquery followssubquery15 = FollowsSubquery(&synonymTable, pk);
	followssubquery15.setSynonyms("a1", "i2");
	ResultTuple* actualResultfollowssubquery15 = followssubquery15.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery15->getAllResults().size());

	// Test 18: Follows(a1, c2)
	FollowsSubquery followssubquery18 = FollowsSubquery(&synonymTable, pk);
	followssubquery18.setSynonyms("a1", "c2");
	ResultTuple* actualResultfollowssubquery18 = followssubquery18.solve(&testTuple);
	int expectedResultfollowssubquery18[5][9] = {
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery18)/sizeof(expectedResultfollowssubquery18[0])), actualResultfollowssubquery18->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery18)/sizeof(expectedResultfollowssubquery18[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery18[i])/sizeof(expectedResultfollowssubquery18[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery18[i][j], actualResultfollowssubquery18->getResultAt(i, j));
		}
	}

	// Test 19: Follows(a1, l2)
	FollowsSubquery followssubquery19 = FollowsSubquery(&synonymTable, pk);
	followssubquery19.setSynonyms("a1", "l2");
	ResultTuple* actualResultfollowssubquery19 = followssubquery19.solve(&testTuple);
	int expectedResultfollowssubquery19[9][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  3},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  3},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  2},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  3},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  2},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  3},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  3}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery19)/sizeof(expectedResultfollowssubquery19[0])), actualResultfollowssubquery19->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery19)/sizeof(expectedResultfollowssubquery19[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery19[i])/sizeof(expectedResultfollowssubquery19[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery19[i][j], actualResultfollowssubquery19->getResultAt(i, j));
		}
	}

	// Test 21: Follows(a1, _)
	FollowsSubquery followssubquery21 = FollowsSubquery(&synonymTable, pk);
	followssubquery21.setSynonyms("a1", "_");
	ResultTuple* actualResultfollowssubquery21 = followssubquery21.solve(&testTuple);
	int expectedResultfollowssubquery21[9][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery21)/sizeof(expectedResultfollowssubquery21[0])), actualResultfollowssubquery21->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery21)/sizeof(expectedResultfollowssubquery21[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery21[i])/sizeof(expectedResultfollowssubquery21[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery21[i][j], actualResultfollowssubquery21->getResultAt(i, j));
		}
	}

	// Test 22: Follows(a1, 2)
	FollowsSubquery followssubquery22 = FollowsSubquery(&synonymTable, pk);
	followssubquery22.setSynonyms("a1", 2);
	ResultTuple* actualResultfollowssubquery22 = followssubquery22.solve(&testTuple);
	int expectedResultfollowssubquery22[4][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery22)/sizeof(expectedResultfollowssubquery22[0])), actualResultfollowssubquery22->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery22)/sizeof(expectedResultfollowssubquery22[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery22[i])/sizeof(expectedResultfollowssubquery22[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery22[i][j], actualResultfollowssubquery22->getResultAt(i, j));
		}
	}

	// Test 23: Follows(a1, 6)
	FollowsSubquery followssubquery23 = FollowsSubquery(&synonymTable, pk);
	followssubquery23.setSynonyms("a1", 6);
	ResultTuple* actualResultfollowssubquery23 = followssubquery23.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery23->getAllResults().size());

	// Test 24: Follows(w1, s2)
	FollowsSubquery followssubquery24 = FollowsSubquery(&synonymTable, pk);
	followssubquery24.setSynonyms("w1", "s2");
	ResultTuple* actualResultfollowssubquery24 = followssubquery24.solve(&testTuple);
	int expectedResultfollowssubquery24[8][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  , 13},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  , 13},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  , 13},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  , 13},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  , 13},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  , 13},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  , 13},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  , 13}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery24)/sizeof(expectedResultfollowssubquery24[0])), actualResultfollowssubquery24->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery24)/sizeof(expectedResultfollowssubquery24[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery24[i])/sizeof(expectedResultfollowssubquery24[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery24[i][j], actualResultfollowssubquery24->getResultAt(i, j));
		}
	}

	// Test 25: Follows(w1, a2)
	FollowsSubquery followssubquery25 = FollowsSubquery(&synonymTable, pk);
	followssubquery25.setSynonyms("w1", "a2");
	ResultTuple* actualResultfollowssubquery25 = followssubquery25.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery25->getAllResults().size());

	// Test 26: Follows(w1, w2)
	FollowsSubquery followssubquery26 = FollowsSubquery(&synonymTable, pk);
	followssubquery26.setSynonyms("w1", "w2");
	ResultTuple* actualResultfollowssubquery26 = followssubquery26.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery26->getAllResults().size());

	// Test 27: Follows(w1, i2)
	FollowsSubquery followssubquery27 = FollowsSubquery(&synonymTable, pk);
	followssubquery27.setSynonyms("w1", "i2");
	ResultTuple* actualResultfollowssubquery27 = followssubquery27.solve(&testTuple);
	int expectedResultfollowssubquery27[1][9] = {
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0 }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery27)/sizeof(expectedResultfollowssubquery27[0])), actualResultfollowssubquery27->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery27)/sizeof(expectedResultfollowssubquery27[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery27[i])/sizeof(expectedResultfollowssubquery27[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery27[i][j], actualResultfollowssubquery27->getResultAt(i, j));
		}
	}

	// Test 30: Follows(w1, c2)
	FollowsSubquery followssubquery30 = FollowsSubquery(&synonymTable, pk);
	followssubquery30.setSynonyms("w1", "c2");
	ResultTuple* actualResultfollowssubquery30 = followssubquery30.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery30->getAllResults().size());

	// Test 31: Follows(w1, l2)
	FollowsSubquery followssubquery31 = FollowsSubquery(&synonymTable, pk);
	followssubquery31.setSynonyms("w1", "l2");
	ResultTuple* actualResultfollowssubquery31 = followssubquery31.solve(&testTuple);
	int expectedResultfollowssubquery31[8][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  , 13},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  , 13},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  , 13},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  , 13},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  , 13},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  , 13},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  , 13},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  , 13}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery31)/sizeof(expectedResultfollowssubquery31[0])), actualResultfollowssubquery31->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery31)/sizeof(expectedResultfollowssubquery31[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery31[i])/sizeof(expectedResultfollowssubquery31[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery31[i][j], actualResultfollowssubquery31->getResultAt(i, j));
		}
	}

	// Test 33: Follows(w1, _)
	FollowsSubquery followssubquery33 = FollowsSubquery(&synonymTable, pk);
	followssubquery33.setSynonyms("w1", "_");
	ResultTuple* actualResultfollowssubquery33 = followssubquery33.solve(&testTuple);
	int expectedResultfollowssubquery33[8][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery33)/sizeof(expectedResultfollowssubquery33[0])), actualResultfollowssubquery33->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery33)/sizeof(expectedResultfollowssubquery33[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery33[i])/sizeof(expectedResultfollowssubquery33[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery33[i][j], actualResultfollowssubquery33->getResultAt(i, j));
		}
	}

	// Test 34: Follows(w1, 2)
	FollowsSubquery followssubquery34 = FollowsSubquery(&synonymTable, pk);
	followssubquery34.setSynonyms("w1", 2);
	ResultTuple* actualResultfollowssubquery34 = followssubquery34.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery34->getAllResults().size());

	// Test 35: Follows(w1, 13)
	FollowsSubquery followssubquery35 = FollowsSubquery(&synonymTable, pk);
	followssubquery35.setSynonyms("w1", 13);
	ResultTuple* actualResultfollowssubquery35 = followssubquery35.solve(&testTuple);
	int expectedResultfollowssubquery35[8][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery35)/sizeof(expectedResultfollowssubquery35[0])), actualResultfollowssubquery35->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery35)/sizeof(expectedResultfollowssubquery35[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery35[i])/sizeof(expectedResultfollowssubquery35[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery35[i][j], actualResultfollowssubquery35->getResultAt(i, j));
		}
	}

	// Test 39: Follows(i1, i2)
	FollowsSubquery followssubquery39 = FollowsSubquery(&synonymTable, pk);
	followssubquery39.setSynonyms("i1", "i2");
	ResultTuple* actualResultfollowssubquery39 = followssubquery39.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery39->getAllResults().size());

	// Test 42: Follows(i1, c2)
	FollowsSubquery followssubquery42 = FollowsSubquery(&synonymTable, pk);
	followssubquery42.setSynonyms("i1", "c2");
	ResultTuple* actualResultfollowssubquery42 = followssubquery42.solve(&testTuple);
	int expectedResultfollowssubquery42[1][9] = {
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery42)/sizeof(expectedResultfollowssubquery42[0])), actualResultfollowssubquery42->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery42)/sizeof(expectedResultfollowssubquery42[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery42[i])/sizeof(expectedResultfollowssubquery42[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery42[i][j], actualResultfollowssubquery42->getResultAt(i, j));
		}
	}

	// Test 75: Follows(c1, i2)
	FollowsSubquery followssubquery75 = FollowsSubquery(&synonymTable, pk);
	followssubquery75.setSynonyms("c1", "i2");
	ResultTuple* actualResultfollowssubquery75 = followssubquery75.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery75->getAllResults().size());

	// Test 78: Follows(c1, c2)
	FollowsSubquery followssubquery78 = FollowsSubquery(&synonymTable, pk);
	followssubquery78.setSynonyms("c1", "c2");
	ResultTuple* actualResultfollowssubquery78 = followssubquery78.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery78->getAllResults().size());

	// Test 84: Follows(l1, s2)
	FollowsSubquery followssubquery84 = FollowsSubquery(&synonymTable, pk);
	followssubquery84.setSynonyms("l1", "s2");
	ResultTuple* actualResultfollowssubquery84 = followssubquery84.solve(&testTuple);
	int expectedResultfollowssubquery84[9][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  2},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  8},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  2},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  2},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery84)/sizeof(expectedResultfollowssubquery84[0])), actualResultfollowssubquery84->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery84)/sizeof(expectedResultfollowssubquery84[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery84[i])/sizeof(expectedResultfollowssubquery84[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery84[i][j], actualResultfollowssubquery84->getResultAt(i, j));
		}
	}

	// Test 85: Follows(l1, a2)
	FollowsSubquery followssubquery85 = FollowsSubquery(&synonymTable, pk);
	followssubquery85.setSynonyms("l1", "a2");
	ResultTuple* actualResultfollowssubquery85 = followssubquery85.solve(&testTuple);
	int expectedResultfollowssubquery85[8][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  2},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  2},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery85)/sizeof(expectedResultfollowssubquery85[0])), actualResultfollowssubquery85->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery85)/sizeof(expectedResultfollowssubquery85[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery85[i])/sizeof(expectedResultfollowssubquery85[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery85[i][j], actualResultfollowssubquery85->getResultAt(i, j));
		}
	}

	// Test 86: Follows(l1, w2)
	FollowsSubquery followssubquery86 = FollowsSubquery(&synonymTable, pk);
	followssubquery86.setSynonyms("l1", "w2");
	ResultTuple* actualResultfollowssubquery86 = followssubquery86.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery86->getAllResults().size());

	// Test 87: Follows(l1, i2)
	FollowsSubquery followssubquery87 = FollowsSubquery(&synonymTable, pk);
	followssubquery87.setSynonyms("l1", "i2");
	ResultTuple* actualResultfollowssubquery87 = followssubquery87.solve(&testTuple);
	int expectedResultfollowssubquery87[1][9] = {
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery87)/sizeof(expectedResultfollowssubquery87[0])), actualResultfollowssubquery87->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery87)/sizeof(expectedResultfollowssubquery87[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery87[i])/sizeof(expectedResultfollowssubquery87[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery87[i][j], actualResultfollowssubquery87->getResultAt(i, j));
		}
	}

	// Test 90: Follows(l1, c2)
	FollowsSubquery followssubquery90 = FollowsSubquery(&synonymTable, pk);
	followssubquery90.setSynonyms("l1", "c2");
	ResultTuple* actualResultfollowssubquery90 = followssubquery90.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery90->getAllResults().size());

	// Test 91: Follows(l1, l2)
	FollowsSubquery followssubquery91 = FollowsSubquery(&synonymTable, pk);
	followssubquery91.setSynonyms("l1", "l2");
	ResultTuple* actualResultfollowssubquery91 = followssubquery91.solve(&testTuple);
	int expectedResultfollowssubquery91[9][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  2},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  8},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  2},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  2},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  2} 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery91)/sizeof(expectedResultfollowssubquery91[0])), actualResultfollowssubquery91->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery91)/sizeof(expectedResultfollowssubquery91[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery91[i])/sizeof(expectedResultfollowssubquery91[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery91[i][j], actualResultfollowssubquery91->getResultAt(i, j));
		}
	}

	// Test 93: Follows(l1, _)
	FollowsSubquery followssubquery93 = FollowsSubquery(&synonymTable, pk);
	followssubquery93.setSynonyms("l1", "_");
	ResultTuple* actualResultfollowssubquery93 = followssubquery93.solve(&testTuple);
	int expectedResultfollowssubquery93[9][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  } 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery93)/sizeof(expectedResultfollowssubquery93[0])), actualResultfollowssubquery93->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery93)/sizeof(expectedResultfollowssubquery93[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery93[i])/sizeof(expectedResultfollowssubquery93[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery93[i][j], actualResultfollowssubquery93->getResultAt(i, j));
		}
	}

	// Test 94: Follows(l1, 2)
	FollowsSubquery followssubquery94 = FollowsSubquery(&synonymTable, pk);
	followssubquery94.setSynonyms("l1", 2);
	ResultTuple* actualResultfollowssubquery94 = followssubquery94.solve(&testTuple);
	int expectedResultfollowssubquery94[8][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  } 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery94)/sizeof(expectedResultfollowssubquery94[0])), actualResultfollowssubquery94->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery94)/sizeof(expectedResultfollowssubquery94[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery94[i])/sizeof(expectedResultfollowssubquery94[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery94[i][j], actualResultfollowssubquery94->getResultAt(i, j));
		}
	}

	// Test 95: Follows(l1, 6)
	FollowsSubquery followssubquery95 = FollowsSubquery(&synonymTable, pk);
	followssubquery95.setSynonyms("l1", 6);
	ResultTuple* actualResultfollowssubquery95 = followssubquery95.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery95->getAllResults().size());

	// Test 111: Follows(_, i2)
	FollowsSubquery followssubquery111 = FollowsSubquery(&synonymTable, pk);
	followssubquery111.setSynonyms("_", "i2");
	ResultTuple* actualResultfollowssubquery111 = followssubquery111.solve(&testTuple);
	int expectedResultfollowssubquery111[9][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery111)/sizeof(expectedResultfollowssubquery111[0])), actualResultfollowssubquery111->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery111)/sizeof(expectedResultfollowssubquery111[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery111[i])/sizeof(expectedResultfollowssubquery111[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery111[i][j], actualResultfollowssubquery111->getResultAt(i, j));
		}
	}

	// Test 114: Follows(_, c2)
	FollowsSubquery followssubquery114 = FollowsSubquery(&synonymTable, pk);
	followssubquery114.setSynonyms("_", "c2");
	ResultTuple* actualResultfollowssubquery114 = followssubquery114.solve(&testTuple);
	int expectedResultfollowssubquery114[9][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery114)/sizeof(expectedResultfollowssubquery114[0])), actualResultfollowssubquery114->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery114)/sizeof(expectedResultfollowssubquery114[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery114[i])/sizeof(expectedResultfollowssubquery114[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery114[i][j], actualResultfollowssubquery114->getResultAt(i, j));
		}
	}

	// Test 123: Follows(1, i2)
	FollowsSubquery followssubquery123 = FollowsSubquery(&synonymTable, pk);
	followssubquery123.setSynonyms(1, "i2");
	ResultTuple* actualResultfollowssubquery123 = followssubquery123.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery123->getAllResults().size());

	// Test 126: Follows(1, c2)
	FollowsSubquery followssubquery126 = FollowsSubquery(&synonymTable, pk);
	followssubquery126.setSynonyms(1, "c2");
	ResultTuple* actualResultfollowssubquery126 = followssubquery126.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowssubquery126->getAllResults().size());

	// Test 135: Follows(7, i2)
	FollowsSubquery followssubquery135 = FollowsSubquery(&synonymTable, pk);
	followssubquery135.setSynonyms(7, "i2");
	ResultTuple* actualResultfollowssubquery135 = followssubquery135.solve(&testTuple);
	int expectedResultfollowssubquery135[8][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery135)/sizeof(expectedResultfollowssubquery135[0])), actualResultfollowssubquery135->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery135)/sizeof(expectedResultfollowssubquery135[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery135[i])/sizeof(expectedResultfollowssubquery135[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery135[i][j], actualResultfollowssubquery135->getResultAt(i, j));
		}
	}

	// Test 138: Follows(8, c2)
	FollowsSubquery followssubquery138 = FollowsSubquery(&synonymTable, pk);
	followssubquery138.setSynonyms(8, "c2");
	ResultTuple* actualResultfollowssubquery138 = followssubquery138.solve(&testTuple);
	int expectedResultfollowssubquery138[1][9] = {
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowssubquery138)/sizeof(expectedResultfollowssubquery138[0])), actualResultfollowssubquery138->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowssubquery138)/sizeof(expectedResultfollowssubquery138[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowssubquery138[i])/sizeof(expectedResultfollowssubquery138[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowssubquery138[i][j], actualResultfollowssubquery138->getResultAt(i, j));
		}
	}
}

void SubqueryTest::testFollowsT(){
	// Test 0: FollowsStar(s1, s2)
	FollowsStarSubquery followsStarsubquery0 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery0.setSynonyms("s1", "s2");
	ResultTuple* actualResultfollowsStarsubquery0 = followsStarsubquery0.solve();
	int expectedResultfollowsStarsubquery0[32][2] = {
		{1, 2}, {1, 3}, 
		{2, 3}, 
		{4, 5}, {4, 6}, {4, 13}, {4, 18}, {4, 19}, {4, 20},
		{5, 6}, {5, 13}, {5, 18}, {5, 19}, {5, 20},
		{6, 13}, {6, 18}, {6, 19}, {6, 20},
		{7, 8}, {7, 11}, {7, 12},
		{8, 11}, {8, 12},
		{11, 12}, 
		{13, 18}, {13, 19}, {13, 20},
		{14, 15}, 
		{18, 19}, {18, 20},
		{19, 20}, 
		{21, 22}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery0)/sizeof(expectedResultfollowsStarsubquery0[0])), actualResultfollowsStarsubquery0->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery0)/sizeof(expectedResultfollowsStarsubquery0[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery0[i])/sizeof(expectedResultfollowsStarsubquery0[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery0[i][j], actualResultfollowsStarsubquery0->getResultAt(i, j));
		}
	}

	// Test 1: FollowsStar(s1, a2)
	FollowsStarSubquery followsStarsubquery1 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery1.setSynonyms("s1", "a2");
	ResultTuple* actualResultfollowsStarsubquery1 = followsStarsubquery1.solve();
	int expectedResultfollowsStarsubquery1[21][2] = {
		{1, 2},
		{4, 5}, {4, 18}, {4, 19}, {4, 20},
		{5, 18}, {5, 19}, {5, 20},
		{6, 18}, {6, 19}, {6, 20},
		{7, 12},
		{8, 12},
		{11, 12}, 
		{13, 18}, {13, 19}, {13, 20},
		{18, 19}, {18, 20},
		{19, 20}, 
		{21, 22}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery1)/sizeof(expectedResultfollowsStarsubquery1[0])), actualResultfollowsStarsubquery1->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery1)/sizeof(expectedResultfollowsStarsubquery1[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery1[i])/sizeof(expectedResultfollowsStarsubquery1[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery1[i][j], actualResultfollowsStarsubquery1->getResultAt(i, j));
		}
	}

	// Test 2: FollowsStar(s1, w2)
	FollowsStarSubquery followsStarsubquery2 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery2.setSynonyms("s1", "w2");
	ResultTuple* actualResultfollowsStarsubquery2 = followsStarsubquery2.solve();
	int expectedResultfollowsStarsubquery2[3][2] = {
		{4, 6},
		{5, 6},
		{14, 15}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery2)/sizeof(expectedResultfollowsStarsubquery2[0])), actualResultfollowsStarsubquery2->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery2)/sizeof(expectedResultfollowsStarsubquery2[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery2[i])/sizeof(expectedResultfollowsStarsubquery2[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery2[i][j], actualResultfollowsStarsubquery2->getResultAt(i, j));
		}
	}

	// Test 3: FollowsStar(s1, i2)
	FollowsStarSubquery followsStarsubquery3 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery3.setSynonyms("s1", "i2");
	ResultTuple* actualResultfollowsStarsubquery3 = followsStarsubquery3.solve();
	int expectedResultfollowsStarsubquery3[4][2] = {
		{4, 13}, {5, 13}, {6, 13}, {7, 8}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery3)/sizeof(expectedResultfollowsStarsubquery3[0])), actualResultfollowsStarsubquery3->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery3)/sizeof(expectedResultfollowsStarsubquery3[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery3[i])/sizeof(expectedResultfollowsStarsubquery3[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery3[i][j], actualResultfollowsStarsubquery3->getResultAt(i, j));
		}
	}

	// Test 6: FollowsStar(s1, c2)
	FollowsStarSubquery followsStarsubquery6 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery6.setSynonyms("s1", "c2");
	ResultTuple* actualResultfollowsStarsubquery6 = followsStarsubquery6.solve();
	int expectedResultfollowsStarsubquery6[4][2] = {
		{1, 3}, 
		{2, 3}, 
		{7, 11},
		{8, 11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery6)/sizeof(expectedResultfollowsStarsubquery6[0])), actualResultfollowsStarsubquery6->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery6)/sizeof(expectedResultfollowsStarsubquery6[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery6[i])/sizeof(expectedResultfollowsStarsubquery6[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery6[i][j], actualResultfollowsStarsubquery6->getResultAt(i, j));
		}
	}

	// Test 7: FollowsStar(s1, l2)
	FollowsStarSubquery followsStarsubquery7 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery7.setSynonyms("s1", "l2");
	ResultTuple* actualResultfollowsStarsubquery7 = followsStarsubquery7.solve();
	int expectedResultfollowsStarsubquery7[32][2] = {
		{1, 2}, {1, 3}, 
		{2, 3}, 
		{4, 5}, {4, 6}, {4, 13}, {4, 18}, {4, 19}, {4, 20},
		{5, 6}, {5, 13}, {5, 18}, {5, 19}, {5, 20},
		{6, 13}, {6, 18}, {6, 19}, {6, 20},
		{7, 8}, {7, 11}, {7, 12},
		{8, 11}, {8, 12},
		{11, 12}, 
		{13, 18}, {13, 19}, {13, 20},
		{14, 15}, 
		{18, 19}, {18, 20},
		{19, 20}, 
		{21, 22} 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery7)/sizeof(expectedResultfollowsStarsubquery7[0])), actualResultfollowsStarsubquery7->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery7)/sizeof(expectedResultfollowsStarsubquery7[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery7[i])/sizeof(expectedResultfollowsStarsubquery7[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery7[i][j], actualResultfollowsStarsubquery7->getResultAt(i, j));
		}
	}

	// Test 9: FollowsStar(s1, _)
	FollowsStarSubquery followsStarsubquery9 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery9.setSynonyms("s1", "_");
	ResultTuple* actualResultfollowsStarsubquery9 = followsStarsubquery9.solve();
	int expectedResultfollowsStarsubquery9[13][1] = {
		{1}, {2}, {4}, {5}, {6}, {7}, {8}, {11}, {13}, {14}, {18}, {19}, {21}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery9)/sizeof(expectedResultfollowsStarsubquery9[0])), actualResultfollowsStarsubquery9->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery9)/sizeof(expectedResultfollowsStarsubquery9[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery9[i])/sizeof(expectedResultfollowsStarsubquery9[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery9[i][j], actualResultfollowsStarsubquery9->getResultAt(i, j));
		}
	}

	// Test 10: FollowsStar(s1, 2)
	FollowsStarSubquery followsStarsubquery10 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery10.setSynonyms("s1", 2);
	ResultTuple* actualResultfollowsStarsubquery10 = followsStarsubquery10.solve();
	int expectedResultfollowsStarsubquery10[1][1] = {
		{1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery10)/sizeof(expectedResultfollowsStarsubquery10[0])), actualResultfollowsStarsubquery10->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery10)/sizeof(expectedResultfollowsStarsubquery10[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery10[i])/sizeof(expectedResultfollowsStarsubquery10[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery10[i][j], actualResultfollowsStarsubquery10->getResultAt(i, j));
		}
	}

	// Test 11: FollowsStar(s1, 6)
	FollowsStarSubquery followsStarsubquery11 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery11.setSynonyms("s1", 6);
	ResultTuple* actualResultfollowsStarsubquery11 = followsStarsubquery11.solve();
	int expectedResultfollowsStarsubquery11[2][1] = {
		{4}, {5}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery11)/sizeof(expectedResultfollowsStarsubquery11[0])), actualResultfollowsStarsubquery11->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery11)/sizeof(expectedResultfollowsStarsubquery11[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery11[i])/sizeof(expectedResultfollowsStarsubquery11[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery11[i][j], actualResultfollowsStarsubquery11->getResultAt(i, j));
		}
	}

	// Test 12: FollowsStar(a1, s2)
	FollowsStarSubquery followsStarsubquery12 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery12.setSynonyms("a1", "s2");
	ResultTuple* actualResultfollowsStarsubquery12 = followsStarsubquery12.solve();
	int expectedResultfollowsStarsubquery12[22][2] = {
		{1, 2}, {1, 3}, 
		{2, 3}, 
		{4, 5}, {4, 6}, {4, 13}, {4, 18}, {4, 19}, {4, 20},
		{5, 6}, {5, 13}, {5, 18}, {5, 19}, {5, 20},
		{7, 8}, {7, 11}, {7, 12},
		{14, 15}, 
		{18, 19}, {18, 20},
		{19, 20}, 
		{21, 22} 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery12)/sizeof(expectedResultfollowsStarsubquery12[0])), actualResultfollowsStarsubquery12->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery12)/sizeof(expectedResultfollowsStarsubquery12[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery12[i])/sizeof(expectedResultfollowsStarsubquery12[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery12[i][j], actualResultfollowsStarsubquery12->getResultAt(i, j));
		}
	}

	// Test 13: FollowsStar(a1, a2)
	FollowsStarSubquery followsStarsubquery13 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery13.setSynonyms("a1", "a2");
	ResultTuple* actualResultfollowsStarsubquery13 = followsStarsubquery13.solve();
	int expectedResultfollowsStarsubquery13[13][2] = {
		{1, 2},
		{4, 5}, {4, 18}, {4, 19}, {4, 20},
		{5, 18}, {5, 19}, {5, 20},
		{7, 12}, 
		{18, 19}, {18, 20},
		{19, 20}, 
		{21, 22} 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery13)/sizeof(expectedResultfollowsStarsubquery13[0])), actualResultfollowsStarsubquery13->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery13)/sizeof(expectedResultfollowsStarsubquery13[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery13[i])/sizeof(expectedResultfollowsStarsubquery13[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery13[i][j], actualResultfollowsStarsubquery13->getResultAt(i, j));
		}
	}

	// Test 14: FollowsStar(a1, w2)
	FollowsStarSubquery followsStarsubquery14 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery14.setSynonyms("a1", "w2");
	ResultTuple* actualResultfollowsStarsubquery14 = followsStarsubquery14.solve();
	int expectedResultfollowsStarsubquery14[3][2] = {
		{4, 6},
		{5, 6},
		{14, 15}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery14)/sizeof(expectedResultfollowsStarsubquery14[0])), actualResultfollowsStarsubquery14->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery14)/sizeof(expectedResultfollowsStarsubquery14[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery14[i])/sizeof(expectedResultfollowsStarsubquery14[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery14[i][j], actualResultfollowsStarsubquery14->getResultAt(i, j));
		}
	}

	// Test 15: FollowsStar(a1, i2)
	FollowsStarSubquery followsStarsubquery15 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery15.setSynonyms("a1", "i2");
	ResultTuple* actualResultfollowsStarsubquery15 = followsStarsubquery15.solve();
	int expectedResultfollowsStarsubquery15[3][2] = {
		{4, 13}, 
		{5, 13},
		{7, 8}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery15)/sizeof(expectedResultfollowsStarsubquery15[0])), actualResultfollowsStarsubquery15->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery15)/sizeof(expectedResultfollowsStarsubquery15[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery15[i])/sizeof(expectedResultfollowsStarsubquery15[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery15[i][j], actualResultfollowsStarsubquery15->getResultAt(i, j));
		}
	}

	// Test 18: FollowsStar(a1, c2)
	FollowsStarSubquery followsStarsubquery18 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery18.setSynonyms("a1", "c2");
	ResultTuple* actualResultfollowsStarsubquery18 = followsStarsubquery18.solve();
	int expectedResultfollowsStarsubquery18[3][2] = {
		{1, 3}, 
		{2, 3}, 
		{7, 11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery18)/sizeof(expectedResultfollowsStarsubquery18[0])), actualResultfollowsStarsubquery18->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery18)/sizeof(expectedResultfollowsStarsubquery18[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery18[i])/sizeof(expectedResultfollowsStarsubquery18[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery18[i][j], actualResultfollowsStarsubquery18->getResultAt(i, j));
		}
	}

	// Test 19: FollowsStar(a1, l2)
	FollowsStarSubquery followsStarsubquery19 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery19.setSynonyms("a1", "l2");
	ResultTuple* actualResultfollowsStarsubquery19 = followsStarsubquery19.solve();
	int expectedResultfollowsStarsubquery19[22][2] = {
		{1, 2}, {1, 3}, 
		{2, 3}, 
		{4, 5}, {4, 6}, {4, 13}, {4, 18}, {4, 19}, {4, 20},
		{5, 6}, {5, 13}, {5, 18}, {5, 19}, {5, 20},
		{7, 8}, {7, 11}, {7, 12},
		{14, 15}, 
		{18, 19}, {18, 20},
		{19, 20}, 
		{21, 22}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery19)/sizeof(expectedResultfollowsStarsubquery19[0])), actualResultfollowsStarsubquery19->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery19)/sizeof(expectedResultfollowsStarsubquery19[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery19[i])/sizeof(expectedResultfollowsStarsubquery19[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery19[i][j], actualResultfollowsStarsubquery19->getResultAt(i, j));
		}
	}

	// Test 21: FollowsStar(a1, _)
	FollowsStarSubquery followsStarsubquery21 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery21.setSynonyms("a1", "_");
	ResultTuple* actualResultfollowsStarsubquery21 = followsStarsubquery21.solve();
	int expectedResultfollowsStarsubquery21[9][1] = {
		{1}, {2}, {4}, {5}, {7}, {14}, {18}, {19}, {21}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery21)/sizeof(expectedResultfollowsStarsubquery21[0])), actualResultfollowsStarsubquery21->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery21)/sizeof(expectedResultfollowsStarsubquery21[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery21[i])/sizeof(expectedResultfollowsStarsubquery21[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery21[i][j], actualResultfollowsStarsubquery21->getResultAt(i, j));
		}
	}

	// Test 22: FollowsStar(a1, 2)
	FollowsStarSubquery followsStarsubquery22 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery22.setSynonyms("a1", 2);
	ResultTuple* actualResultfollowsStarsubquery22 = followsStarsubquery22.solve();
	int expectedResultfollowsStarsubquery22[1][1] = {
		{1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery22)/sizeof(expectedResultfollowsStarsubquery22[0])), actualResultfollowsStarsubquery22->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery22)/sizeof(expectedResultfollowsStarsubquery22[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery22[i])/sizeof(expectedResultfollowsStarsubquery22[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery22[i][j], actualResultfollowsStarsubquery22->getResultAt(i, j));
		}
	}

	// Test 23: FollowsStar(a1, 6)
	FollowsStarSubquery followsStarsubquery23 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery23.setSynonyms("a1", 6);
	ResultTuple* actualResultfollowsStarsubquery23 = followsStarsubquery23.solve();
	int expectedResultfollowsStarsubquery23[2][1] = {
		{4}, {5}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery23)/sizeof(expectedResultfollowsStarsubquery23[0])), actualResultfollowsStarsubquery23->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery23)/sizeof(expectedResultfollowsStarsubquery23[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery23[i])/sizeof(expectedResultfollowsStarsubquery23[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery23[i][j], actualResultfollowsStarsubquery23->getResultAt(i, j));
		}
	}

	// Test 24: FollowsStar(w1, s2)
	FollowsStarSubquery followsStarsubquery24 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery24.setSynonyms("w1", "s2");
	ResultTuple* actualResultfollowsStarsubquery24 = followsStarsubquery24.solve();
	int expectedResultfollowsStarsubquery24[4][2] = {
		{6, 13}, {6, 18}, {6, 19}, {6, 20}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery24)/sizeof(expectedResultfollowsStarsubquery24[0])), actualResultfollowsStarsubquery24->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery24)/sizeof(expectedResultfollowsStarsubquery24[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery24[i])/sizeof(expectedResultfollowsStarsubquery24[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery24[i][j], actualResultfollowsStarsubquery24->getResultAt(i, j));
		}
	}

	// Test 25: FollowsStar(w1, a2)
	FollowsStarSubquery followsStarsubquery25 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery25.setSynonyms("w1", "a2");
	ResultTuple* actualResultfollowsStarsubquery25 = followsStarsubquery25.solve();
	int expectedResultfollowsStarsubquery25[3][2] = {
		{6, 18}, {6, 19}, {6, 20}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery25)/sizeof(expectedResultfollowsStarsubquery25[0])), actualResultfollowsStarsubquery25->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery25)/sizeof(expectedResultfollowsStarsubquery25[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery25[i])/sizeof(expectedResultfollowsStarsubquery25[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery25[i][j], actualResultfollowsStarsubquery25->getResultAt(i, j));
		}
	}

	// Test 26: FollowsStar(w1, w2)
	FollowsStarSubquery followsStarsubquery26 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery26.setSynonyms("w1", "w2");
	ResultTuple* actualResultfollowsStarsubquery26 = followsStarsubquery26.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery26->getAllResults().size());

	// Test 27: FollowsStar(w1, i2)
	FollowsStarSubquery followsStarsubquery27 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery27.setSynonyms("w1", "i2");
	ResultTuple* actualResultfollowsStarsubquery27 = followsStarsubquery27.solve();
	int expectedResultfollowsStarsubquery27[1][2] = {
		{6, 13}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery27)/sizeof(expectedResultfollowsStarsubquery27[0])), actualResultfollowsStarsubquery27->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery27)/sizeof(expectedResultfollowsStarsubquery27[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery27[i])/sizeof(expectedResultfollowsStarsubquery27[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery27[i][j], actualResultfollowsStarsubquery27->getResultAt(i, j));
		}
	}

	// Test 30: FollowsStar(w1, c2)
	FollowsStarSubquery followsStarsubquery30 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery30.setSynonyms("w1", "c2");
	ResultTuple* actualResultfollowsStarsubquery30 = followsStarsubquery30.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery30->getAllResults().size());

	// Test 31: FollowsStar(w1, l2)
	FollowsStarSubquery followsStarsubquery31 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery31.setSynonyms("w1", "l2");
	ResultTuple* actualResultfollowsStarsubquery31 = followsStarsubquery31.solve();
	int expectedResultfollowsStarsubquery31[4][2] = {
		{6, 13}, {6, 18}, {6, 19}, {6, 20}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery31)/sizeof(expectedResultfollowsStarsubquery31[0])), actualResultfollowsStarsubquery31->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery31)/sizeof(expectedResultfollowsStarsubquery31[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery31[i])/sizeof(expectedResultfollowsStarsubquery31[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery31[i][j], actualResultfollowsStarsubquery31->getResultAt(i, j));
		}
	}

	// Test 33: FollowsStar(w1, _)
	FollowsStarSubquery followsStarsubquery33 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery33.setSynonyms("w1", "_");
	ResultTuple* actualResultfollowsStarsubquery33 = followsStarsubquery33.solve();
	int expectedResultfollowsStarsubquery33[1][1] = {
		{6}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery33)/sizeof(expectedResultfollowsStarsubquery33[0])), actualResultfollowsStarsubquery33->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery33)/sizeof(expectedResultfollowsStarsubquery33[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery33[i])/sizeof(expectedResultfollowsStarsubquery33[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery33[i][j], actualResultfollowsStarsubquery33->getResultAt(i, j));
		}
	}

	// Test 34: FollowsStar(w1, 2)
	FollowsStarSubquery followsStarsubquery34 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery34.setSynonyms("w1", 2);
	ResultTuple* actualResultfollowsStarsubquery34 = followsStarsubquery34.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery34->getAllResults().size());

	// Test 35: FollowsStar(w1, 13)
	FollowsStarSubquery followsStarsubquery35 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery35.setSynonyms("w1", 13);
	ResultTuple* actualResultfollowsStarsubquery35 = followsStarsubquery35.solve();
	int expectedResultfollowsStarsubquery35[1][1] = {
		{6}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery35)/sizeof(expectedResultfollowsStarsubquery35[0])), actualResultfollowsStarsubquery35->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery35)/sizeof(expectedResultfollowsStarsubquery35[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery35[i])/sizeof(expectedResultfollowsStarsubquery35[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery35[i][j], actualResultfollowsStarsubquery35->getResultAt(i, j));
		}
	}

	// Test 36: FollowsStar(i1, s2)
	FollowsStarSubquery followsStarsubquery36 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery36.setSynonyms("i1", "s2");
	ResultTuple* actualResultfollowsStarsubquery36 = followsStarsubquery36.solve();
	int expectedResultfollowsStarsubquery36[5][2] = {
		{8, 11}, {8, 12},
		{13, 18}, {13, 19}, {13, 20}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery36)/sizeof(expectedResultfollowsStarsubquery36[0])), actualResultfollowsStarsubquery36->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery36)/sizeof(expectedResultfollowsStarsubquery36[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery36[i])/sizeof(expectedResultfollowsStarsubquery36[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery36[i][j], actualResultfollowsStarsubquery36->getResultAt(i, j));
		}
	}

	// Test 37: FollowsStar(i1, a2)
	FollowsStarSubquery followsStarsubquery37 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery37.setSynonyms("i1", "a2");
	ResultTuple* actualResultfollowsStarsubquery37 = followsStarsubquery37.solve();
	int expectedResultfollowsStarsubquery37[4][2] = {
		{8, 12},
		{13, 18}, {13, 19}, {13, 20}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery37)/sizeof(expectedResultfollowsStarsubquery37[0])), actualResultfollowsStarsubquery37->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery37)/sizeof(expectedResultfollowsStarsubquery37[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery37[i])/sizeof(expectedResultfollowsStarsubquery37[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery37[i][j], actualResultfollowsStarsubquery37->getResultAt(i, j));
		}
	}

	// Test 38: FollowsStar(i1, w2)
	FollowsStarSubquery followsStarsubquery38 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery38.setSynonyms("i1", "w2");
	ResultTuple* actualResultfollowsStarsubquery38 = followsStarsubquery38.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery38->getAllResults().size());

	// Test 39: FollowsStar(i1, i2)
	FollowsStarSubquery followsStarsubquery39 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery39.setSynonyms("i1", "i2");
	ResultTuple* actualResultfollowsStarsubquery39 = followsStarsubquery39.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery39->getAllResults().size());

	// Test 42: FollowsStar(i1, c2)
	FollowsStarSubquery followsStarsubquery42 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery42.setSynonyms("i1", "c2");
	ResultTuple* actualResultfollowsStarsubquery42 = followsStarsubquery42.solve();
	int expectedResultfollowsStarsubquery42[1][2] = {
		{8, 11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery42)/sizeof(expectedResultfollowsStarsubquery42[0])), actualResultfollowsStarsubquery42->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery42)/sizeof(expectedResultfollowsStarsubquery42[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery42[i])/sizeof(expectedResultfollowsStarsubquery42[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery42[i][j], actualResultfollowsStarsubquery42->getResultAt(i, j));
		}
	}

	// Test 43: FollowsStar(i1, l2)
	FollowsStarSubquery followsStarsubquery43 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery43.setSynonyms("i1", "l2");
	ResultTuple* actualResultfollowsStarsubquery43 = followsStarsubquery43.solve();
	int expectedResultfollowsStarsubquery43[5][2] = {
		{8, 11}, {8, 12},
		{13, 18}, {13, 19}, {13, 20}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery43)/sizeof(expectedResultfollowsStarsubquery43[0])), actualResultfollowsStarsubquery43->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery43)/sizeof(expectedResultfollowsStarsubquery43[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery43[i])/sizeof(expectedResultfollowsStarsubquery43[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery43[i][j], actualResultfollowsStarsubquery43->getResultAt(i, j));
		}
	}

	// Test 45: FollowsStar(i1, _)
	FollowsStarSubquery followsStarsubquery45 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery45.setSynonyms("i1", "_");
	ResultTuple* actualResultfollowsStarsubquery45 = followsStarsubquery45.solve();
	int expectedResultfollowsStarsubquery45[2][1] = {
		{8}, {13}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery45)/sizeof(expectedResultfollowsStarsubquery45[0])), actualResultfollowsStarsubquery45->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery45)/sizeof(expectedResultfollowsStarsubquery45[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery45[i])/sizeof(expectedResultfollowsStarsubquery45[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery45[i][j], actualResultfollowsStarsubquery45->getResultAt(i, j));
		}
	}

	// Test 46: FollowsStar(i1, 2)
	FollowsStarSubquery followsStarsubquery46 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery46.setSynonyms("i1", 2);
	ResultTuple* actualResultfollowsStarsubquery46 = followsStarsubquery46.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery46->getAllResults().size());

	// Test 47: FollowsStar(i1, 18)
	FollowsStarSubquery followsStarsubquery47 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery47.setSynonyms("i1", 18);
	ResultTuple* actualResultfollowsStarsubquery47 = followsStarsubquery47.solve();
	int expectedResultfollowsStarsubquery47[1][1] = {
		{13}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery47)/sizeof(expectedResultfollowsStarsubquery47[0])), actualResultfollowsStarsubquery47->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery47)/sizeof(expectedResultfollowsStarsubquery47[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery47[i])/sizeof(expectedResultfollowsStarsubquery47[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery47[i][j], actualResultfollowsStarsubquery47->getResultAt(i, j));
		}
	}

	// Test 72: FollowsStar(c1, s2)
	FollowsStarSubquery followsStarsubquery72 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery72.setSynonyms("c1", "s2");
	ResultTuple* actualResultfollowsStarsubquery72 = followsStarsubquery72.solve();
	int expectedResultfollowsStarsubquery72[1][2] = {
		{11, 12}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery72)/sizeof(expectedResultfollowsStarsubquery72[0])), actualResultfollowsStarsubquery72->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery72)/sizeof(expectedResultfollowsStarsubquery72[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery72[i])/sizeof(expectedResultfollowsStarsubquery72[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery72[i][j], actualResultfollowsStarsubquery72->getResultAt(i, j));
		}
	}

	// Test 73: FollowsStar(c1, a2)
	FollowsStarSubquery followsStarsubquery73 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery73.setSynonyms("c1", "a2");
	ResultTuple* actualResultfollowsStarsubquery73 = followsStarsubquery73.solve();
	int expectedResultfollowsStarsubquery73[1][2] = {
		{11, 12}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery73)/sizeof(expectedResultfollowsStarsubquery73[0])), actualResultfollowsStarsubquery73->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery73)/sizeof(expectedResultfollowsStarsubquery73[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery73[i])/sizeof(expectedResultfollowsStarsubquery73[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery73[i][j], actualResultfollowsStarsubquery73->getResultAt(i, j));
		}
	}

	// Test 74: FollowsStar(c1, w2)
	FollowsStarSubquery followsStarsubquery74 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery74.setSynonyms("c1", "w2");
	ResultTuple* actualResultfollowsStarsubquery74 = followsStarsubquery74.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery74->getAllResults().size());

	// Test 75: FollowsStar(c1, i2)
	FollowsStarSubquery followsStarsubquery75 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery75.setSynonyms("c1", "i2");
	ResultTuple* actualResultfollowsStarsubquery75 = followsStarsubquery75.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery75->getAllResults().size());

	// Test 78: FollowsStar(c1, c2)
	FollowsStarSubquery followsStarsubquery78 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery78.setSynonyms("c1", "c2");
	ResultTuple* actualResultfollowsStarsubquery78 = followsStarsubquery78.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery78->getAllResults().size());

	// Test 79: FollowsStar(c1, l2)
	FollowsStarSubquery followsStarsubquery79 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery79.setSynonyms("c1", "l2");
	ResultTuple* actualResultfollowsStarsubquery79 = followsStarsubquery79.solve();
	int expectedResultfollowsStarsubquery79[1][2] = {
		{11, 12}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery79)/sizeof(expectedResultfollowsStarsubquery79[0])), actualResultfollowsStarsubquery79->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery79)/sizeof(expectedResultfollowsStarsubquery79[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery79[i])/sizeof(expectedResultfollowsStarsubquery79[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery79[i][j], actualResultfollowsStarsubquery79->getResultAt(i, j));
		}
	}

	// Test 81: FollowsStar(c1, _)
	FollowsStarSubquery followsStarsubquery81 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery81.setSynonyms("c1", "_");
	ResultTuple* actualResultfollowsStarsubquery81 = followsStarsubquery81.solve();
	int expectedResultfollowsStarsubquery81[1][1] = {
		{11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery81)/sizeof(expectedResultfollowsStarsubquery81[0])), actualResultfollowsStarsubquery81->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery81)/sizeof(expectedResultfollowsStarsubquery81[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery81[i])/sizeof(expectedResultfollowsStarsubquery81[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery81[i][j], actualResultfollowsStarsubquery81->getResultAt(i, j));
		}
	}

	// Test 82: FollowsStar(c1, 2)
	FollowsStarSubquery followsStarsubquery82 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery82.setSynonyms("c1", 2);
	ResultTuple* actualResultfollowsStarsubquery82 = followsStarsubquery82.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery82->getAllResults().size());

	// Test 83: FollowsStar(c1, 12)
	FollowsStarSubquery followsStarsubquery83 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery83.setSynonyms("c1", 12);
	ResultTuple* actualResultfollowsStarsubquery83 = followsStarsubquery83.solve();
	int expectedResultfollowsStarsubquery83[1][1] = {
		{11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery83)/sizeof(expectedResultfollowsStarsubquery83[0])), actualResultfollowsStarsubquery83->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery83)/sizeof(expectedResultfollowsStarsubquery83[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery83[i])/sizeof(expectedResultfollowsStarsubquery83[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery83[i][j], actualResultfollowsStarsubquery83->getResultAt(i, j));
		}
	}

	// Test 84: FollowsStar(l1, s2)
	FollowsStarSubquery followsStarsubquery84 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery84.setSynonyms("l1", "s2");
	ResultTuple* actualResultfollowsStarsubquery84 = followsStarsubquery84.solve();
	int expectedResultfollowsStarsubquery84[32][2] = {
		{1, 2}, {1, 3}, 
		{2, 3}, 
		{4, 5}, {4, 6}, {4, 13}, {4, 18}, {4, 19}, {4, 20},
		{5, 6}, {5, 13}, {5, 18}, {5, 19}, {5, 20},
		{6, 13}, {6, 18}, {6, 19}, {6, 20},
		{7, 8}, {7, 11}, {7, 12},
		{8, 11}, {8, 12},
		{11, 12}, 
		{13, 18}, {13, 19}, {13, 20},
		{14, 15}, 
		{18, 19}, {18, 20},
		{19, 20}, 
		{21, 22} 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery84)/sizeof(expectedResultfollowsStarsubquery84[0])), actualResultfollowsStarsubquery84->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery84)/sizeof(expectedResultfollowsStarsubquery84[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery84[i])/sizeof(expectedResultfollowsStarsubquery84[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery84[i][j], actualResultfollowsStarsubquery84->getResultAt(i, j));
		}
	}

	// Test 85: FollowsStar(l1, a2)
	FollowsStarSubquery followsStarsubquery85 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery85.setSynonyms("l1", "a2");
	ResultTuple* actualResultfollowsStarsubquery85 = followsStarsubquery85.solve();
	int expectedResultfollowsStarsubquery85[21][2] = {
		{1, 2},
		{4, 5}, {4, 18}, {4, 19}, {4, 20},
		{5, 18}, {5, 19}, {5, 20},
		{6, 18}, {6, 19}, {6, 20},
		{7, 12},
		{8, 12},
		{11, 12}, 
		{13, 18}, {13, 19}, {13, 20},
		{18, 19}, {18, 20},
		{19, 20}, 
		{21, 22} 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery85)/sizeof(expectedResultfollowsStarsubquery85[0])), actualResultfollowsStarsubquery85->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery85)/sizeof(expectedResultfollowsStarsubquery85[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery85[i])/sizeof(expectedResultfollowsStarsubquery85[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery85[i][j], actualResultfollowsStarsubquery85->getResultAt(i, j));
		}
	}

	// Test 86: FollowsStar(l1, w2)
	FollowsStarSubquery followsStarsubquery86 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery86.setSynonyms("l1", "w2");
	ResultTuple* actualResultfollowsStarsubquery86 = followsStarsubquery86.solve();
	int expectedResultfollowsStarsubquery86[3][2] = {
		{4, 6},
		{5, 6},
		{14, 15}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery86)/sizeof(expectedResultfollowsStarsubquery86[0])), actualResultfollowsStarsubquery86->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery86)/sizeof(expectedResultfollowsStarsubquery86[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery86[i])/sizeof(expectedResultfollowsStarsubquery86[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery86[i][j], actualResultfollowsStarsubquery86->getResultAt(i, j));
		}
	}

	// Test 87: FollowsStar(l1, i2)
	FollowsStarSubquery followsStarsubquery87 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery87.setSynonyms("l1", "i2");
	ResultTuple* actualResultfollowsStarsubquery87 = followsStarsubquery87.solve();
	int expectedResultfollowsStarsubquery87[4][2] = {
		{4, 13}, {5, 13},
		{6, 13},
		{7, 8}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery87)/sizeof(expectedResultfollowsStarsubquery87[0])), actualResultfollowsStarsubquery87->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery87)/sizeof(expectedResultfollowsStarsubquery87[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery87[i])/sizeof(expectedResultfollowsStarsubquery87[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery87[i][j], actualResultfollowsStarsubquery87->getResultAt(i, j));
		}
	}

	// Test 90: FollowsStar(l1, c2)
	FollowsStarSubquery followsStarsubquery90 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery90.setSynonyms("l1", "c2");
	ResultTuple* actualResultfollowsStarsubquery90 = followsStarsubquery90.solve();
	int expectedResultfollowsStarsubquery90[4][2] = {
		{1, 3}, 
		{2, 3}, 
		{7, 11},
		{8, 11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery90)/sizeof(expectedResultfollowsStarsubquery90[0])), actualResultfollowsStarsubquery90->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery90)/sizeof(expectedResultfollowsStarsubquery90[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery90[i])/sizeof(expectedResultfollowsStarsubquery90[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery90[i][j], actualResultfollowsStarsubquery90->getResultAt(i, j));
		}
	}

	// Test 91: FollowsStar(l1, l2)
	FollowsStarSubquery followsStarsubquery91 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery91.setSynonyms("l1", "l2");
	ResultTuple* actualResultfollowsStarsubquery91 = followsStarsubquery91.solve();
	int expectedResultfollowsStarsubquery91[32][2] = {
		{1, 2}, {1, 3}, 
		{2, 3}, 
		{4, 5}, {4, 6}, {4, 13}, {4, 18}, {4, 19}, {4, 20},
		{5, 6}, {5, 13}, {5, 18}, {5, 19}, {5, 20},
		{6, 13}, {6, 18}, {6, 19}, {6, 20},
		{7, 8}, {7, 11}, {7, 12},
		{8, 11}, {8, 12},
		{11, 12}, 
		{13, 18}, {13, 19}, {13, 20},
		{14, 15}, 
		{18, 19}, {18, 20},
		{19, 20}, 
		{21, 22} 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery91)/sizeof(expectedResultfollowsStarsubquery91[0])), actualResultfollowsStarsubquery91->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery91)/sizeof(expectedResultfollowsStarsubquery91[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery91[i])/sizeof(expectedResultfollowsStarsubquery91[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery91[i][j], actualResultfollowsStarsubquery91->getResultAt(i, j));
		}
	}

	// Test 93: FollowsStar(l1, _)
	FollowsStarSubquery followsStarsubquery93 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery93.setSynonyms("l1", "_");
	ResultTuple* actualResultfollowsStarsubquery93 = followsStarsubquery93.solve();
	int expectedResultfollowsStarsubquery93[13][1] = {
		{1}, {2}, {4}, {5}, {6}, {7}, {8}, {11}, {13}, {14}, {18}, {19}, {21} 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery93)/sizeof(expectedResultfollowsStarsubquery93[0])), actualResultfollowsStarsubquery93->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery93)/sizeof(expectedResultfollowsStarsubquery93[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery93[i])/sizeof(expectedResultfollowsStarsubquery93[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery93[i][j], actualResultfollowsStarsubquery93->getResultAt(i, j));
		}
	}

	// Test 94: FollowsStar(l1, 2)
	FollowsStarSubquery followsStarsubquery94 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery94.setSynonyms("l1", 2);
	ResultTuple* actualResultfollowsStarsubquery94 = followsStarsubquery94.solve();
	int expectedResultfollowsStarsubquery94[1][1] = {
		{1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery94)/sizeof(expectedResultfollowsStarsubquery94[0])), actualResultfollowsStarsubquery94->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery94)/sizeof(expectedResultfollowsStarsubquery94[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery94[i])/sizeof(expectedResultfollowsStarsubquery94[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery94[i][j], actualResultfollowsStarsubquery94->getResultAt(i, j));
		}
	}

	// Test 95: FollowsStar(l1, 6)
	FollowsStarSubquery followsStarsubquery95 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery95.setSynonyms("l1", 6);
	ResultTuple* actualResultfollowsStarsubquery95 = followsStarsubquery95.solve();
	int expectedResultfollowsStarsubquery95[2][1] = {
		{4}, {5}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery95)/sizeof(expectedResultfollowsStarsubquery95[0])), actualResultfollowsStarsubquery95->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery95)/sizeof(expectedResultfollowsStarsubquery95[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery95[i])/sizeof(expectedResultfollowsStarsubquery95[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery95[i][j], actualResultfollowsStarsubquery95->getResultAt(i, j));
		}
	}

	// Test 108: FollowsStar(_, s2)
	FollowsStarSubquery followsStarsubquery108 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery108.setSynonyms("_", "s2");
	ResultTuple* actualResultfollowsStarsubquery108 = followsStarsubquery108.solve();
	int expectedResultfollowsStarsubquery108[13][1] = {
		{2}, {3}, {5}, {6}, {8}, {11}, {12}, {13}, {15}, {18}, {19}, {20}, {22} 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery108)/sizeof(expectedResultfollowsStarsubquery108[0])), actualResultfollowsStarsubquery108->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery108)/sizeof(expectedResultfollowsStarsubquery108[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery108[i])/sizeof(expectedResultfollowsStarsubquery108[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery108[i][j], actualResultfollowsStarsubquery108->getResultAt(i, j));
		}
	}

	// Test 109: FollowsStar(_, a2)
	FollowsStarSubquery followsStarsubquery109 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery109.setSynonyms("_", "a2");
	ResultTuple* actualResultfollowsStarsubquery109 = followsStarsubquery109.solve();
	int expectedResultfollowsStarsubquery109[7][1] = {
		{2}, {5}, {12}, {18}, {19}, {20}, {22}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery109)/sizeof(expectedResultfollowsStarsubquery109[0])), actualResultfollowsStarsubquery109->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery109)/sizeof(expectedResultfollowsStarsubquery109[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery109[i])/sizeof(expectedResultfollowsStarsubquery109[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery109[i][j], actualResultfollowsStarsubquery109->getResultAt(i, j));
		}
	}

	// Test 110: FollowsStar(_, w2)
	FollowsStarSubquery followsStarsubquery110 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery110.setSynonyms("_", "w2");
	ResultTuple* actualResultfollowsStarsubquery110 = followsStarsubquery110.solve();
	int expectedResultfollowsStarsubquery110[2][1] = {
		{6}, {15}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery110)/sizeof(expectedResultfollowsStarsubquery110[0])), actualResultfollowsStarsubquery110->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery110)/sizeof(expectedResultfollowsStarsubquery110[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery110[i])/sizeof(expectedResultfollowsStarsubquery110[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery110[i][j], actualResultfollowsStarsubquery110->getResultAt(i, j));
		}
	}

	// Test 111: FollowsStar(_, i2)
	FollowsStarSubquery followsStarsubquery111 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery111.setSynonyms("_", "i2");
	ResultTuple* actualResultfollowsStarsubquery111 = followsStarsubquery111.solve();
	int expectedResultfollowsStarsubquery111[2][1] = {
		{8}, {13}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery111)/sizeof(expectedResultfollowsStarsubquery111[0])), actualResultfollowsStarsubquery111->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery111)/sizeof(expectedResultfollowsStarsubquery111[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery111[i])/sizeof(expectedResultfollowsStarsubquery111[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery111[i][j], actualResultfollowsStarsubquery111->getResultAt(i, j));
		}
	}

	// Test 114: FollowsStar(_, c2)
	FollowsStarSubquery followsStarsubquery114 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery114.setSynonyms("_", "c2");
	ResultTuple* actualResultfollowsStarsubquery114 = followsStarsubquery114.solve();
	int expectedResultfollowsStarsubquery114[2][1] = {
		{3}, {11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery114)/sizeof(expectedResultfollowsStarsubquery114[0])), actualResultfollowsStarsubquery114->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery114)/sizeof(expectedResultfollowsStarsubquery114[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery114[i])/sizeof(expectedResultfollowsStarsubquery114[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery114[i][j], actualResultfollowsStarsubquery114->getResultAt(i, j));
		}
	}

	// Test 115: FollowsStar(_, l2)
	FollowsStarSubquery followsStarsubquery115 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery115.setSynonyms("_", "l2");
	ResultTuple* actualResultfollowsStarsubquery115 = followsStarsubquery115.solve();
	int expectedResultfollowsStarsubquery115[13][1] = {
		{2}, {3}, {5}, {6}, {8}, {11}, {12}, {13}, {15}, {18}, {19}, {20}, {22} 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery115)/sizeof(expectedResultfollowsStarsubquery115[0])), actualResultfollowsStarsubquery115->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery115)/sizeof(expectedResultfollowsStarsubquery115[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery115[i])/sizeof(expectedResultfollowsStarsubquery115[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery115[i][j], actualResultfollowsStarsubquery115->getResultAt(i, j));
		}
	}

	// Test 117: FollowsStar(_, _)
	FollowsStarSubquery followsStarsubquery117 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery117.setSynonyms("_", "_");
	ResultTuple* actualResultfollowsStarsubquery117 = followsStarsubquery117.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery117->getAllResults().size());
	CPPUNIT_ASSERT(actualResultfollowsStarsubquery117->isBool());
	CPPUNIT_ASSERT(!actualResultfollowsStarsubquery117->isEmpty());

	// Test 118: FollowsStar(_, 2)
	FollowsStarSubquery followsStarsubquery118 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery118.setSynonyms("_", 2);
	ResultTuple* actualResultfollowsStarsubquery118 = followsStarsubquery118.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery118->getAllResults().size());
	CPPUNIT_ASSERT(actualResultfollowsStarsubquery118->isBool());
	CPPUNIT_ASSERT(!actualResultfollowsStarsubquery118->isEmpty());

	// Test 119: FollowsStar(_, 7)
	FollowsStarSubquery followsStarsubquery119 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery119.setSynonyms("_", 7);
	ResultTuple* actualResultfollowsStarsubquery119 = followsStarsubquery119.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery119->getAllResults().size());
	CPPUNIT_ASSERT(actualResultfollowsStarsubquery119->isBool());
	CPPUNIT_ASSERT(actualResultfollowsStarsubquery119->isEmpty());

	// Test 120: FollowsStar(1, s2)
	FollowsStarSubquery followsStarsubquery120 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery120.setSynonyms(1, "s2");
	ResultTuple* actualResultfollowsStarsubquery120 = followsStarsubquery120.solve();
	int expectedResultfollowsStarsubquery120[2][1] = {
		{2}, {3}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery120)/sizeof(expectedResultfollowsStarsubquery120[0])), actualResultfollowsStarsubquery120->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery120)/sizeof(expectedResultfollowsStarsubquery120[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery120[i])/sizeof(expectedResultfollowsStarsubquery120[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery120[i][j], actualResultfollowsStarsubquery120->getResultAt(i, j));
		}
	}

	// Test 121: FollowsStar(1, a2)
	FollowsStarSubquery followsStarsubquery121 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery121.setSynonyms(1, "a2");
	ResultTuple* actualResultfollowsStarsubquery121 = followsStarsubquery121.solve();
	int expectedResultfollowsStarsubquery121[1][1] = {
		{2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery121)/sizeof(expectedResultfollowsStarsubquery121[0])), actualResultfollowsStarsubquery121->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery121)/sizeof(expectedResultfollowsStarsubquery121[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery121[i])/sizeof(expectedResultfollowsStarsubquery121[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery121[i][j], actualResultfollowsStarsubquery121->getResultAt(i, j));
		}
	}

	// Test 122: FollowsStar(1, w2)
	FollowsStarSubquery followsStarsubquery122 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery122.setSynonyms(1, "w2");
	ResultTuple* actualResultfollowsStarsubquery122 = followsStarsubquery122.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery122->getAllResults().size());

	// Test 123: FollowsStar(1, i2)
	FollowsStarSubquery followsStarsubquery123 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery123.setSynonyms(1, "i2");
	ResultTuple* actualResultfollowsStarsubquery123 = followsStarsubquery123.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery123->getAllResults().size());

	// Test 126: FollowsStar(1, c2)
	FollowsStarSubquery followsStarsubquery126 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery126.setSynonyms(1, "c2");
	ResultTuple* actualResultfollowsStarsubquery126 = followsStarsubquery126.solve();
	int expectedResultfollowsStarsubquery126[1][1] = {
		{3}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery126)/sizeof(expectedResultfollowsStarsubquery126[0])), actualResultfollowsStarsubquery126->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery126)/sizeof(expectedResultfollowsStarsubquery126[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery126[i])/sizeof(expectedResultfollowsStarsubquery126[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery126[i][j], actualResultfollowsStarsubquery126->getResultAt(i, j));
		}
	}

	// Test 127: FollowsStar(1, l2)
	FollowsStarSubquery followsStarsubquery127 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery127.setSynonyms(1, "l2");
	ResultTuple* actualResultfollowsStarsubquery127 = followsStarsubquery127.solve();
	int expectedResultfollowsStarsubquery127[2][1] = {
		{2}, {3}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery127)/sizeof(expectedResultfollowsStarsubquery127[0])), actualResultfollowsStarsubquery127->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery127)/sizeof(expectedResultfollowsStarsubquery127[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery127[i])/sizeof(expectedResultfollowsStarsubquery127[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery127[i][j], actualResultfollowsStarsubquery127->getResultAt(i, j));
		}
	}

	// Test 129: FollowsStar(1, _)
	FollowsStarSubquery followsStarsubquery129 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery129.setSynonyms(1, "_");
	ResultTuple* actualResultfollowsStarsubquery129 = followsStarsubquery129.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery129->getAllResults().size());
	CPPUNIT_ASSERT(actualResultfollowsStarsubquery129->isBool());
	CPPUNIT_ASSERT(!actualResultfollowsStarsubquery129->isEmpty());

	// Test 130: FollowsStar(1, 2)
	FollowsStarSubquery followsStarsubquery130 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery130.setSynonyms(1, 2);
	ResultTuple* actualResultfollowsStarsubquery130 = followsStarsubquery130.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery130->getAllResults().size());
	CPPUNIT_ASSERT(actualResultfollowsStarsubquery130->isBool());
	CPPUNIT_ASSERT(!actualResultfollowsStarsubquery130->isEmpty());

	// Test 131: FollowsStar(1, 6)
	FollowsStarSubquery followsStarsubquery131 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery131.setSynonyms(1, 6);
	ResultTuple* actualResultfollowsStarsubquery131 = followsStarsubquery131.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery131->getAllResults().size());
	CPPUNIT_ASSERT(actualResultfollowsStarsubquery131->isBool());
	CPPUNIT_ASSERT(actualResultfollowsStarsubquery131->isEmpty());

	// Test 132: FollowsStar(5, s2)
	FollowsStarSubquery followsStarsubquery132 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery132.setSynonyms(5, "s2");
	ResultTuple* actualResultfollowsStarsubquery132 = followsStarsubquery132.solve();
	int expectedResultfollowsStarsubquery132[5][1] = {
		{6}, {13}, {18}, {19}, {20}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery132)/sizeof(expectedResultfollowsStarsubquery132[0])), actualResultfollowsStarsubquery132->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery132)/sizeof(expectedResultfollowsStarsubquery132[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery132[i])/sizeof(expectedResultfollowsStarsubquery132[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery132[i][j], actualResultfollowsStarsubquery132->getResultAt(i, j));
		}
	}

	// Test 133: FollowsStar(5, a2)
	FollowsStarSubquery followsStarsubquery133 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery133.setSynonyms(5, "a2");
	ResultTuple* actualResultfollowsStarsubquery133 = followsStarsubquery133.solve();
	int expectedResultfollowsStarsubquery133[3][1] = {
		{18}, {19}, {20}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery133)/sizeof(expectedResultfollowsStarsubquery133[0])), actualResultfollowsStarsubquery133->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery133)/sizeof(expectedResultfollowsStarsubquery133[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery133[i])/sizeof(expectedResultfollowsStarsubquery133[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery133[i][j], actualResultfollowsStarsubquery133->getResultAt(i, j));
		}
	}

	// Test 134: FollowsStar(5, w2)
	FollowsStarSubquery followsStarsubquery134 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery134.setSynonyms(5, "w2");
	ResultTuple* actualResultfollowsStarsubquery134 = followsStarsubquery134.solve();
	int expectedResultfollowsStarsubquery134[1][1] = {
		{6}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery134)/sizeof(expectedResultfollowsStarsubquery134[0])), actualResultfollowsStarsubquery134->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery134)/sizeof(expectedResultfollowsStarsubquery134[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery134[i])/sizeof(expectedResultfollowsStarsubquery134[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery134[i][j], actualResultfollowsStarsubquery134->getResultAt(i, j));
		}
	}

	// Test 135: FollowsStar(5, i2)
	FollowsStarSubquery followsStarsubquery135 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery135.setSynonyms(5, "i2");
	ResultTuple* actualResultfollowsStarsubquery135 = followsStarsubquery135.solve();
	int expectedResultfollowsStarsubquery135[1][1] = {
		{13}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery135)/sizeof(expectedResultfollowsStarsubquery135[0])), actualResultfollowsStarsubquery135->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery135)/sizeof(expectedResultfollowsStarsubquery135[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery135[i])/sizeof(expectedResultfollowsStarsubquery135[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery135[i][j], actualResultfollowsStarsubquery135->getResultAt(i, j));
		}
	}

	// Test 138: FollowsStar(8, c2)
	FollowsStarSubquery followsStarsubquery138 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery138.setSynonyms(8, "c2");
	ResultTuple* actualResultfollowsStarsubquery138 = followsStarsubquery138.solve();
	int expectedResultfollowsStarsubquery138[1][1] = {
		{11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery138)/sizeof(expectedResultfollowsStarsubquery138[0])), actualResultfollowsStarsubquery138->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery138)/sizeof(expectedResultfollowsStarsubquery138[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery138[i])/sizeof(expectedResultfollowsStarsubquery138[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery138[i][j], actualResultfollowsStarsubquery138->getResultAt(i, j));
		}
	}

	// Test 139: FollowsStar(5, l2)
	FollowsStarSubquery followsStarsubquery139 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery139.setSynonyms(5, "l2");
	ResultTuple* actualResultfollowsStarsubquery139 = followsStarsubquery139.solve();
	int expectedResultfollowsStarsubquery139[5][1] = {
		{6}, {13}, {18}, {19}, {20}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery139)/sizeof(expectedResultfollowsStarsubquery139[0])), actualResultfollowsStarsubquery139->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery139)/sizeof(expectedResultfollowsStarsubquery139[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery139[i])/sizeof(expectedResultfollowsStarsubquery139[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery139[i][j], actualResultfollowsStarsubquery139->getResultAt(i, j));
		}
	}

	// Test 141: FollowsStar(5, _)
	FollowsStarSubquery followsStarsubquery141 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery141.setSynonyms(5, "_");
	ResultTuple* actualResultfollowsStarsubquery141 = followsStarsubquery141.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery141->getAllResults().size());
	CPPUNIT_ASSERT(actualResultfollowsStarsubquery141->isBool());
	CPPUNIT_ASSERT(!actualResultfollowsStarsubquery141->isEmpty());

	// Test 142: FollowsStar(5, 2)
	FollowsStarSubquery followsStarsubquery142 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery142.setSynonyms(5, 2);
	ResultTuple* actualResultfollowsStarsubquery142 = followsStarsubquery142.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery142->getAllResults().size());
	CPPUNIT_ASSERT(actualResultfollowsStarsubquery142->isBool());
	CPPUNIT_ASSERT(actualResultfollowsStarsubquery142->isEmpty());

	// Test 143: FollowsStar(5, 6)
	FollowsStarSubquery followsStarsubquery143 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery143.setSynonyms(5, 6);
	ResultTuple* actualResultfollowsStarsubquery143 = followsStarsubquery143.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery143->getAllResults().size());
	CPPUNIT_ASSERT(actualResultfollowsStarsubquery143->isBool());
	CPPUNIT_ASSERT(!actualResultfollowsStarsubquery143->isEmpty());
}

void SubqueryTest::testFollowsTTuple(){
	// testTuple:
	//  s1  |  a1  |  w1  |  i2  |  c2  |  l1  |  const1  |  v1  |  proc1  |
	//  1   |  1   |  6   |  8   |  3   |  1   |  0       |  0   |  0      |
	//  1   |  2   |  6   |  8   |  3   |  1   |  0       |  0   |  0      |
	//  1   |  1   |  15  |  8   |  3   |  1   |  0       |  0   |  0      |
	//  1   |  2   |  6   |  13  |  3   |  1   |  0       |  0   |  0      |
	//  1   |  1   |  6   |  8   |  11  |  1   |  0       |  0   |  0      |
	//  8   |  2   |  6   |  8   |  3   |  7   |  0       |  0   |  0      |
	//  1   |  1   |  6   |  8   |  3   |  1   |  3       |  0   |  0      |
	//  3   |  2   |  6   |  8   |  3   |  1   |  0       |  2   |  0      |
	//  1   |  2   |  6   |  8   |  3   |  1   |  0       |  2   |  1      |
	ResultTuple testTuple = ResultTuple();
	int index = testTuple.addSynonym("s1");
	testTuple.addSynonymToMap("s1", index);
	index = testTuple.addSynonym("a1");
	testTuple.addSynonymToMap("a1", index);
	index = testTuple.addSynonym("w1");
	testTuple.addSynonymToMap("w1", index);
	index = testTuple.addSynonym("i2");
	testTuple.addSynonymToMap("i2", index);
	index = testTuple.addSynonym("c2");
	testTuple.addSynonymToMap("c2", index);
	index = testTuple.addSynonym("l1");
	testTuple.addSynonymToMap("l1", index);
	index = testTuple.addSynonym("const1");
	testTuple.addSynonymToMap("const1", index);
	index = testTuple.addSynonym("v1");
	testTuple.addSynonymToMap("v1", index);
	index = testTuple.addSynonym("proc1");
	testTuple.addSynonymToMap("proc1", index);
	int data[9][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	for (int i = 0; i < 9; i++){
		vector<int> tempVector = vector<int>();
		testTuple.addResultRow(tempVector);
		for (int j = 0; j < 9; j++){
			testTuple.addResult(i, data[i][j]);
		}
	}

	// Test 0: FollowsStar(s1, s2)
	FollowsStarSubquery followsStarsubquery0 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery0.setSynonyms("s1", "s2");
	ResultTuple* actualResultfollowsStarsubquery0 = followsStarsubquery0.solve(&testTuple);
	int expectedResultfollowsStarsubquery0[15][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  3  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  3  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  3  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  2  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  3  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  2  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  3  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  11  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  12  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  2  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  3  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  2  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  3  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery0)/sizeof(expectedResultfollowsStarsubquery0[0])), actualResultfollowsStarsubquery0->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery0)/sizeof(expectedResultfollowsStarsubquery0[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery0[i])/sizeof(expectedResultfollowsStarsubquery0[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery0[i][j], actualResultfollowsStarsubquery0->getResultAt(i, j));
		}
	}

	// Test 1: FollowsStar(s1, a2)
	FollowsStarSubquery followsStarsubquery1 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery1.setSynonyms("s1", "a2");
	ResultTuple* actualResultfollowsStarsubquery1 = followsStarsubquery1.solve(&testTuple);
	int expectedResultfollowsStarsubquery1[7][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  2  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  2  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  12  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  2  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  2  },
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery1)/sizeof(expectedResultfollowsStarsubquery1[0])), actualResultfollowsStarsubquery1->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery1)/sizeof(expectedResultfollowsStarsubquery1[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery1[i])/sizeof(expectedResultfollowsStarsubquery1[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery1[i][j], actualResultfollowsStarsubquery1->getResultAt(i, j));
		}
	}

	// Test 2: FollowsStar(s1, w2)
	FollowsStarSubquery followsStarsubquery2 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery2.setSynonyms("s1", "w2");
	ResultTuple* actualResultfollowsStarsubquery2 = followsStarsubquery2.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery2->getAllResults().size());

	// Test 3: FollowsStar(s1, i2)
	FollowsStarSubquery followsStarsubquery3 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery3.setSynonyms("s1", "i2");
	ResultTuple* actualResultfollowsStarsubquery3 = followsStarsubquery3.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery3->getAllResults().size());

	// Test 6: FollowsStar(s1, c2)
	FollowsStarSubquery followsStarsubquery6 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery6.setSynonyms("s1", "c2");
	ResultTuple* actualResultfollowsStarsubquery6 = followsStarsubquery6.solve(&testTuple);
	int expectedResultfollowsStarsubquery6[6][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery6)/sizeof(expectedResultfollowsStarsubquery6[0])), actualResultfollowsStarsubquery6->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery6)/sizeof(expectedResultfollowsStarsubquery6[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery6[i])/sizeof(expectedResultfollowsStarsubquery6[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery6[i][j], actualResultfollowsStarsubquery6->getResultAt(i, j));
		}
	}

	// Test 7: FollowsStar(s1, l2)
	FollowsStarSubquery followsStarsubquery7 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery7.setSynonyms("s1", "l2");
	ResultTuple* actualResultfollowsStarsubquery7 = followsStarsubquery7.solve(&testTuple);
	int expectedResultfollowsStarsubquery7[15][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  3  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  3  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  3  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  2  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  3  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  2  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  3  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  11  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  12  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  2  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  3  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  2  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  3  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery7)/sizeof(expectedResultfollowsStarsubquery7[0])), actualResultfollowsStarsubquery7->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery7)/sizeof(expectedResultfollowsStarsubquery7[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery7[i])/sizeof(expectedResultfollowsStarsubquery7[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery7[i][j], actualResultfollowsStarsubquery7->getResultAt(i, j));
		}
	}

	// Test 9: FollowsStar(s1, _)
	FollowsStarSubquery followsStarsubquery9 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery9.setSynonyms("s1", "_");
	ResultTuple* actualResultfollowsStarsubquery9 = followsStarsubquery9.solve(&testTuple);
	int expectedResultfollowsStarsubquery9[8][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery9)/sizeof(expectedResultfollowsStarsubquery9[0])), actualResultfollowsStarsubquery9->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery9)/sizeof(expectedResultfollowsStarsubquery9[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery9[i])/sizeof(expectedResultfollowsStarsubquery9[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery9[i][j], actualResultfollowsStarsubquery9->getResultAt(i, j));
		}
	}

	// Test 10: FollowsStar(s1, 2)
	FollowsStarSubquery followsStarsubquery10 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery10.setSynonyms("s1", 2);
	ResultTuple* actualResultfollowsStarsubquery10 = followsStarsubquery10.solve(&testTuple);
	int expectedResultfollowsStarsubquery10[6][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery10)/sizeof(expectedResultfollowsStarsubquery10[0])), actualResultfollowsStarsubquery10->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery10)/sizeof(expectedResultfollowsStarsubquery10[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery10[i])/sizeof(expectedResultfollowsStarsubquery10[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery10[i][j], actualResultfollowsStarsubquery10->getResultAt(i, j));
		}
	}

	// Test 11: FollowsStar(s1, 6)
	FollowsStarSubquery followsStarsubquery11 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery11.setSynonyms("s1", 6);
	ResultTuple* actualResultfollowsStarsubquery11 = followsStarsubquery11.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery11->getAllResults().size());

	// Test 12: FollowsStar(a1, s2)
	FollowsStarSubquery followsStarsubquery12 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery12.setSynonyms("a1", "s2");
	ResultTuple* actualResultfollowsStarsubquery12 = followsStarsubquery12.solve(&testTuple);
	int expectedResultfollowsStarsubquery12[13][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  3},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  3},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  3},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  3},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  3},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  3},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  3},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  3},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  3}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery12)/sizeof(expectedResultfollowsStarsubquery12[0])), actualResultfollowsStarsubquery12->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery12)/sizeof(expectedResultfollowsStarsubquery12[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery12[i])/sizeof(expectedResultfollowsStarsubquery12[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery12[i][j], actualResultfollowsStarsubquery12->getResultAt(i, j));
		}
	}

	// Test 13: FollowsStar(a1, a2)
	FollowsStarSubquery followsStarsubquery13 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery13.setSynonyms("a1", "a2");
	ResultTuple* actualResultfollowsStarsubquery13 = followsStarsubquery13.solve(&testTuple);
	int expectedResultfollowsStarsubquery13[4][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  2},
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery13)/sizeof(expectedResultfollowsStarsubquery13[0])), actualResultfollowsStarsubquery13->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery13)/sizeof(expectedResultfollowsStarsubquery13[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery13[i])/sizeof(expectedResultfollowsStarsubquery13[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery13[i][j], actualResultfollowsStarsubquery13->getResultAt(i, j));
		}
	}

	// Test 14: FollowsStar(a1, w2)
	FollowsStarSubquery followsStarsubquery14 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery14.setSynonyms("a1", "w2");
	ResultTuple* actualResultfollowsStarsubquery14 = followsStarsubquery14.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery14->getAllResults().size());

	// Test 15: FollowsStar(a1, i2)
	FollowsStarSubquery followsStarsubquery15 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery15.setSynonyms("a1", "i2");
	ResultTuple* actualResultfollowsStarsubquery15 = followsStarsubquery15.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery15->getAllResults().size());

	// Test 18: FollowsStar(a1, c2)
	FollowsStarSubquery followsStarsubquery18 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery18.setSynonyms("a1", "c2");
	ResultTuple* actualResultfollowsStarsubquery18 = followsStarsubquery18.solve(&testTuple);
	int expectedResultfollowsStarsubquery18[8][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery18)/sizeof(expectedResultfollowsStarsubquery18[0])), actualResultfollowsStarsubquery18->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery18)/sizeof(expectedResultfollowsStarsubquery18[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery18[i])/sizeof(expectedResultfollowsStarsubquery18[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery18[i][j], actualResultfollowsStarsubquery18->getResultAt(i, j));
		}
	}

	// Test 19: FollowsStar(a1, l2)
	FollowsStarSubquery followsStarsubquery19 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery19.setSynonyms("a1", "l2");
	ResultTuple* actualResultfollowsStarsubquery19 = followsStarsubquery19.solve(&testTuple);
	int expectedResultfollowsStarsubquery19[13][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  3},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  3},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  3},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  3},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  3},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  3},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  3},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  3},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  3}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery19)/sizeof(expectedResultfollowsStarsubquery19[0])), actualResultfollowsStarsubquery19->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery19)/sizeof(expectedResultfollowsStarsubquery19[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery19[i])/sizeof(expectedResultfollowsStarsubquery19[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery19[i][j], actualResultfollowsStarsubquery19->getResultAt(i, j));
		}
	}

	// Test 21: FollowsStar(a1, _)
	FollowsStarSubquery followsStarsubquery21 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery21.setSynonyms("a1", "_");
	ResultTuple* actualResultfollowsStarsubquery21 = followsStarsubquery21.solve(&testTuple);
	int expectedResultfollowsStarsubquery21[9][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery21)/sizeof(expectedResultfollowsStarsubquery21[0])), actualResultfollowsStarsubquery21->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery21)/sizeof(expectedResultfollowsStarsubquery21[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery21[i])/sizeof(expectedResultfollowsStarsubquery21[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery21[i][j], actualResultfollowsStarsubquery21->getResultAt(i, j));
		}
	}

	// Test 22: FollowsStar(a1, 2)
	FollowsStarSubquery followsStarsubquery22 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery22.setSynonyms("a1", 2);
	ResultTuple* actualResultfollowsStarsubquery22 = followsStarsubquery22.solve(&testTuple);
	int expectedResultfollowsStarsubquery22[4][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery22)/sizeof(expectedResultfollowsStarsubquery22[0])), actualResultfollowsStarsubquery22->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery22)/sizeof(expectedResultfollowsStarsubquery22[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery22[i])/sizeof(expectedResultfollowsStarsubquery22[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery22[i][j], actualResultfollowsStarsubquery22->getResultAt(i, j));
		}
	}

	// Test 23: FollowsStar(a1, 6)
	FollowsStarSubquery followsStarsubquery23 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery23.setSynonyms("a1", 6);
	ResultTuple* actualResultfollowsStarsubquery23 = followsStarsubquery23.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery23->getAllResults().size());

	// Test 24: FollowsStar(w1, s2)
	FollowsStarSubquery followsStarsubquery24 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery24.setSynonyms("w1", "s2");
	ResultTuple* actualResultfollowsStarsubquery24 = followsStarsubquery24.solve(&testTuple);
	int expectedResultfollowsStarsubquery24[32][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  , 13},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  , 18},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  , 19},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  , 20},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  , 13},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  , 18},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  , 19},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  , 20},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  , 13},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  , 18},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  , 19},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  , 20},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  , 13},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  , 18},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  , 19},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  , 20},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  , 13},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  , 18},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  , 19},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  , 20},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  , 13},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  , 18},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  , 19},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  , 20},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  , 13},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  , 18},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  , 19},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  , 20},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  , 13},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  , 18},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  , 19},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  , 20}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery24)/sizeof(expectedResultfollowsStarsubquery24[0])), actualResultfollowsStarsubquery24->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery24)/sizeof(expectedResultfollowsStarsubquery24[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery24[i])/sizeof(expectedResultfollowsStarsubquery24[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery24[i][j], actualResultfollowsStarsubquery24->getResultAt(i, j));
		}
	}

	// Test 25: FollowsStar(w1, a2)
	FollowsStarSubquery followsStarsubquery25 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery25.setSynonyms("w1", "a2");
	ResultTuple* actualResultfollowsStarsubquery25 = followsStarsubquery25.solve(&testTuple);
	int expectedResultfollowsStarsubquery25[24][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  , 18},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  , 19},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  , 20},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  , 18},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  , 19},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  , 20},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  , 18},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  , 19},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  , 20},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  , 18},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  , 19},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  , 20},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  , 18},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  , 19},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  , 20},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  , 18},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  , 19},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  , 20},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  , 18},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  , 19},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  , 20},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  , 18},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  , 19},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  , 20}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery25)/sizeof(expectedResultfollowsStarsubquery25[0])), actualResultfollowsStarsubquery25->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery25)/sizeof(expectedResultfollowsStarsubquery25[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery25[i])/sizeof(expectedResultfollowsStarsubquery25[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery25[i][j], actualResultfollowsStarsubquery25->getResultAt(i, j));
		}
	}

	// Test 26: FollowsStar(w1, w2)
	FollowsStarSubquery followsStarsubquery26 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery26.setSynonyms("w1", "w2");
	ResultTuple* actualResultfollowsStarsubquery26 = followsStarsubquery26.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery26->getAllResults().size());

	// Test 27: FollowsStar(w1, i2)
	FollowsStarSubquery followsStarsubquery27 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery27.setSynonyms("w1", "i2");
	ResultTuple* actualResultfollowsStarsubquery27 = followsStarsubquery27.solve(&testTuple);
	int expectedResultfollowsStarsubquery27[1][9] = {
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery27)/sizeof(expectedResultfollowsStarsubquery27[0])), actualResultfollowsStarsubquery27->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery27)/sizeof(expectedResultfollowsStarsubquery27[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery27[i])/sizeof(expectedResultfollowsStarsubquery27[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery27[i][j], actualResultfollowsStarsubquery27->getResultAt(i, j));
		}
	}

	// Test 30: FollowsStar(w1, c2)
	FollowsStarSubquery followsStarsubquery30 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery30.setSynonyms("w1", "c2");
	ResultTuple* actualResultfollowsStarsubquery30 = followsStarsubquery30.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery30->getAllResults().size());

	// Test 31: FollowsStar(w1, l2)
	FollowsStarSubquery followsStarsubquery31 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery31.setSynonyms("w1", "l2");
	ResultTuple* actualResultfollowsStarsubquery31 = followsStarsubquery31.solve(&testTuple);
	int expectedResultfollowsStarsubquery31[32][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  , 13},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  , 18},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  , 19},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  , 20},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  , 13},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  , 18},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  , 19},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  , 20},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  , 13},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  , 18},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  , 19},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  , 20},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  , 13},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  , 18},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  , 19},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  , 20},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  , 13},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  , 18},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  , 19},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  , 20},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  , 13},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  , 18},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  , 19},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  , 20},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  , 13},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  , 18},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  , 19},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  , 20},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  , 13},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  , 18},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  , 19},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  , 20}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery31)/sizeof(expectedResultfollowsStarsubquery31[0])), actualResultfollowsStarsubquery31->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery31)/sizeof(expectedResultfollowsStarsubquery31[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery31[i])/sizeof(expectedResultfollowsStarsubquery31[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery31[i][j], actualResultfollowsStarsubquery31->getResultAt(i, j));
		}
	}

	// Test 33: FollowsStar(w1, _)
	FollowsStarSubquery followsStarsubquery33 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery33.setSynonyms("w1", "_");
	ResultTuple* actualResultfollowsStarsubquery33 = followsStarsubquery33.solve(&testTuple);
	int expectedResultfollowsStarsubquery33[8][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery33)/sizeof(expectedResultfollowsStarsubquery33[0])), actualResultfollowsStarsubquery33->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery33)/sizeof(expectedResultfollowsStarsubquery33[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery33[i])/sizeof(expectedResultfollowsStarsubquery33[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery33[i][j], actualResultfollowsStarsubquery33->getResultAt(i, j));
		}
	}

	// Test 34: FollowsStar(w1, 2)
	FollowsStarSubquery followsStarsubquery34 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery34.setSynonyms("w1", 2);
	ResultTuple* actualResultfollowsStarsubquery34 = followsStarsubquery34.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery34->getAllResults().size());

	// Test 35: FollowsStar(w1, 13)
	FollowsStarSubquery followsStarsubquery35 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery35.setSynonyms("w1", 13);
	ResultTuple* actualResultfollowsStarsubquery35 = followsStarsubquery35.solve(&testTuple);
	int expectedResultfollowsStarsubquery35[8][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery35)/sizeof(expectedResultfollowsStarsubquery35[0])), actualResultfollowsStarsubquery35->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery35)/sizeof(expectedResultfollowsStarsubquery35[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery35[i])/sizeof(expectedResultfollowsStarsubquery35[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery35[i][j], actualResultfollowsStarsubquery35->getResultAt(i, j));
		}
	}

	// Test 39: FollowsStar(i1, i2)
	FollowsStarSubquery followsStarsubquery39 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery39.setSynonyms("i1", "i2");
	ResultTuple* actualResultfollowsStarsubquery39 = followsStarsubquery39.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery39->getAllResults().size());

	// Test 42: FollowsStar(i1, c2)
	FollowsStarSubquery followsStarsubquery42 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery42.setSynonyms("i1", "c2");
	ResultTuple* actualResultfollowsStarsubquery42 = followsStarsubquery42.solve(&testTuple);
	int expectedResultfollowsStarsubquery42[1][9] = {
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery42)/sizeof(expectedResultfollowsStarsubquery42[0])), actualResultfollowsStarsubquery42->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery42)/sizeof(expectedResultfollowsStarsubquery42[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery42[i])/sizeof(expectedResultfollowsStarsubquery42[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery42[i][j], actualResultfollowsStarsubquery42->getResultAt(i, j));
		}
	}

	// Test 75: FollowsStar(c1, i2)
	FollowsStarSubquery followsStarsubquery75 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery75.setSynonyms("c1", "i2");
	ResultTuple* actualResultfollowsStarsubquery75 = followsStarsubquery75.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery75->getAllResults().size());

	// Test 78: FollowsStar(c1, c2)
	FollowsStarSubquery followsStarsubquery78 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery78.setSynonyms("c1", "c2");
	ResultTuple* actualResultfollowsStarsubquery78 = followsStarsubquery78.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery78->getAllResults().size());

	// Test 84: FollowsStar(l1, s2)
	FollowsStarSubquery followsStarsubquery84 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery84.setSynonyms("l1", "s2");
	ResultTuple* actualResultfollowsStarsubquery84 = followsStarsubquery84.solve(&testTuple);
	int expectedResultfollowsStarsubquery84[19][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  3},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  3},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  3},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  3},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  3},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  8},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  11},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  12},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  3},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  2},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  3},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  2},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  3}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery84)/sizeof(expectedResultfollowsStarsubquery84[0])), actualResultfollowsStarsubquery84->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery84)/sizeof(expectedResultfollowsStarsubquery84[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery84[i])/sizeof(expectedResultfollowsStarsubquery84[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery84[i][j], actualResultfollowsStarsubquery84->getResultAt(i, j));
		}
	}

	// Test 85: FollowsStar(l1, a2)
	FollowsStarSubquery followsStarsubquery85 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery85.setSynonyms("l1", "a2");
	ResultTuple* actualResultfollowsStarsubquery85 = followsStarsubquery85.solve(&testTuple);
	int expectedResultfollowsStarsubquery85[9][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  2},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  12},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  2},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  2},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery85)/sizeof(expectedResultfollowsStarsubquery85[0])), actualResultfollowsStarsubquery85->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery85)/sizeof(expectedResultfollowsStarsubquery85[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery85[i])/sizeof(expectedResultfollowsStarsubquery85[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery85[i][j], actualResultfollowsStarsubquery85->getResultAt(i, j));
		}
	}

	// Test 86: FollowsStar(l1, w2)
	FollowsStarSubquery followsStarsubquery86 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery86.setSynonyms("l1", "w2");
	ResultTuple* actualResultfollowsStarsubquery86 = followsStarsubquery86.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery86->getAllResults().size());

	// Test 87: FollowsStar(l1, i2)
	FollowsStarSubquery followsStarsubquery87 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery87.setSynonyms("l1", "i2");
	ResultTuple* actualResultfollowsStarsubquery87 = followsStarsubquery87.solve(&testTuple);
	int expectedResultfollowsStarsubquery87[1][9] = {
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery87)/sizeof(expectedResultfollowsStarsubquery87[0])), actualResultfollowsStarsubquery87->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery87)/sizeof(expectedResultfollowsStarsubquery87[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery87[i])/sizeof(expectedResultfollowsStarsubquery87[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery87[i][j], actualResultfollowsStarsubquery87->getResultAt(i, j));
		}
	}

	// Test 90: FollowsStar(l1, c2)
	FollowsStarSubquery followsStarsubquery90 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery90.setSynonyms("l1", "c2");
	ResultTuple* actualResultfollowsStarsubquery90 = followsStarsubquery90.solve(&testTuple);
	int expectedResultfollowsStarsubquery90[7][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery90)/sizeof(expectedResultfollowsStarsubquery90[0])), actualResultfollowsStarsubquery90->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery90)/sizeof(expectedResultfollowsStarsubquery90[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery90[i])/sizeof(expectedResultfollowsStarsubquery90[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery90[i][j], actualResultfollowsStarsubquery90->getResultAt(i, j));
		}
	}

	// Test 91: FollowsStar(l1, l2)
	FollowsStarSubquery followsStarsubquery91 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery91.setSynonyms("l1", "l2");
	ResultTuple* actualResultfollowsStarsubquery91 = followsStarsubquery91.solve(&testTuple);
	int expectedResultfollowsStarsubquery91[19][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  3},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  3},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  3},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  3},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  3},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  8},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  11},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  12},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  3},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  2},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  3},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  2},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  3}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery91)/sizeof(expectedResultfollowsStarsubquery91[0])), actualResultfollowsStarsubquery91->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery91)/sizeof(expectedResultfollowsStarsubquery91[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery91[i])/sizeof(expectedResultfollowsStarsubquery91[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery91[i][j], actualResultfollowsStarsubquery91->getResultAt(i, j));
		}
	}

	// Test 93: FollowsStar(l1, _)
	FollowsStarSubquery followsStarsubquery93 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery93.setSynonyms("l1", "_");
	ResultTuple* actualResultfollowsStarsubquery93 = followsStarsubquery93.solve(&testTuple);
	int expectedResultfollowsStarsubquery93[9][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  } 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery93)/sizeof(expectedResultfollowsStarsubquery93[0])), actualResultfollowsStarsubquery93->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery93)/sizeof(expectedResultfollowsStarsubquery93[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery93[i])/sizeof(expectedResultfollowsStarsubquery93[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery93[i][j], actualResultfollowsStarsubquery93->getResultAt(i, j));
		}
	}

	// Test 94: FollowsStar(l1, 2)
	FollowsStarSubquery followsStarsubquery94 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery94.setSynonyms("l1", 2);
	ResultTuple* actualResultfollowsStarsubquery94 = followsStarsubquery94.solve(&testTuple);
	int expectedResultfollowsStarsubquery94[8][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  } 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery94)/sizeof(expectedResultfollowsStarsubquery94[0])), actualResultfollowsStarsubquery94->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery94)/sizeof(expectedResultfollowsStarsubquery94[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery94[i])/sizeof(expectedResultfollowsStarsubquery94[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery94[i][j], actualResultfollowsStarsubquery94->getResultAt(i, j));
		}
	}

	// Test 95: FollowsStar(l1, 6)
	FollowsStarSubquery followsStarsubquery95 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery95.setSynonyms("l1", 6);
	ResultTuple* actualResultfollowsStarsubquery95 = followsStarsubquery95.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery95->getAllResults().size());

	// Test 111: FollowsStar(_, i2)
	FollowsStarSubquery followsStarsubquery111 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery111.setSynonyms("_", "i2");
	ResultTuple* actualResultfollowsStarsubquery111 = followsStarsubquery111.solve(&testTuple);
	int expectedResultfollowsStarsubquery111[9][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery111)/sizeof(expectedResultfollowsStarsubquery111[0])), actualResultfollowsStarsubquery111->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery111)/sizeof(expectedResultfollowsStarsubquery111[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery111[i])/sizeof(expectedResultfollowsStarsubquery111[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery111[i][j], actualResultfollowsStarsubquery111->getResultAt(i, j));
		}
	}

	// Test 114: FollowsStar(_, c2)
	FollowsStarSubquery followsStarsubquery114 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery114.setSynonyms("_", "c2");
	ResultTuple* actualResultfollowsStarsubquery114 = followsStarsubquery114.solve(&testTuple);
	int expectedResultfollowsStarsubquery114[9][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery114)/sizeof(expectedResultfollowsStarsubquery114[0])), actualResultfollowsStarsubquery114->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery114)/sizeof(expectedResultfollowsStarsubquery114[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery114[i])/sizeof(expectedResultfollowsStarsubquery114[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery114[i][j], actualResultfollowsStarsubquery114->getResultAt(i, j));
		}
	}

	// Test 123: FollowsStar(1, i2)
	FollowsStarSubquery followsStarsubquery123 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery123.setSynonyms(1, "i2");
	ResultTuple* actualResultfollowsStarsubquery123 = followsStarsubquery123.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultfollowsStarsubquery123->getAllResults().size());

	// Test 126: FollowsStar(1, c2)
	FollowsStarSubquery followsStarsubquery126 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery126.setSynonyms(1, "c2");
	ResultTuple* actualResultfollowsStarsubquery126 = followsStarsubquery126.solve(&testTuple);
	int expectedResultfollowsStarsubquery126[8][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery126)/sizeof(expectedResultfollowsStarsubquery126[0])), actualResultfollowsStarsubquery126->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery126)/sizeof(expectedResultfollowsStarsubquery126[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery126[i])/sizeof(expectedResultfollowsStarsubquery126[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery126[i][j], actualResultfollowsStarsubquery126->getResultAt(i, j));
		}
	}

	// Test 135: FollowsStar(7, i2)
	FollowsStarSubquery followsStarsubquery135 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery135.setSynonyms(7, "i2");
	ResultTuple* actualResultfollowsStarsubquery135 = followsStarsubquery135.solve(&testTuple);
	int expectedResultfollowsStarsubquery135[8][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery135)/sizeof(expectedResultfollowsStarsubquery135[0])), actualResultfollowsStarsubquery135->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery135)/sizeof(expectedResultfollowsStarsubquery135[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery135[i])/sizeof(expectedResultfollowsStarsubquery135[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery135[i][j], actualResultfollowsStarsubquery135->getResultAt(i, j));
		}
	}

	// Test 138: FollowsStar(8, c2)
	FollowsStarSubquery followsStarsubquery138 = FollowsStarSubquery(&synonymTable, pk);
	followsStarsubquery138.setSynonyms(8, "c2");
	ResultTuple* actualResultfollowsStarsubquery138 = followsStarsubquery138.solve(&testTuple);
	int expectedResultfollowsStarsubquery138[1][9] = {
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultfollowsStarsubquery138)/sizeof(expectedResultfollowsStarsubquery138[0])), actualResultfollowsStarsubquery138->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultfollowsStarsubquery138)/sizeof(expectedResultfollowsStarsubquery138[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultfollowsStarsubquery138[i])/sizeof(expectedResultfollowsStarsubquery138[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultfollowsStarsubquery138[i][j], actualResultfollowsStarsubquery138->getResultAt(i, j));
		}
	}
}

void SubqueryTest::testParent(){
	// Test 1: Parent(s1, s2)
	ParentSubquery parentSubquery1 = ParentSubquery(&synonymTable, pk);
	parentSubquery1.setSynonyms("s1", "s2");
	ResultTuple* actualResultsParentSubquery1 = parentSubquery1.solve();
	int expectedResultsParentSubquery1[10][2] = {
		{6, 7}, {6, 8}, {6, 11}, {6, 12}, {8, 9}, {8,10},  {13, 14}, {13, 15}, {13, 17}, {15, 16}
	};
	CPPUNIT_ASSERT_EQUAL((size_t)10, actualResultsParentSubquery1->getAllResults().size());
	for (size_t i = 0; i < 10; i++){
		for (size_t j = 0; j < 2; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsParentSubquery1[i][j], actualResultsParentSubquery1->getResultAt(i, j));
		}
	}

	// Test 2: Parent(s1, 8)
	ParentSubquery parentSubquery2 = ParentSubquery(&synonymTable, pk);
	parentSubquery2.setSynonyms("s1", 8);
	ResultTuple* actualResultsParentSubquery2 = parentSubquery2.solve();
	int expectedResultsParentSubquery2[1][1] = {
		{6}
	};
	CPPUNIT_ASSERT_EQUAL((size_t)1, actualResultsParentSubquery2->getAllResults().size());
	for (size_t i = 0; i < 1; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsParentSubquery2[i][j], actualResultsParentSubquery2->getResultAt(i, j));
		}
	}

	// Test 3: Parent(s1, _)
	ParentSubquery parentSubquery3 = ParentSubquery(&synonymTable, pk);
	parentSubquery3.setSynonyms("s1", "_");
	ResultTuple* actualResultsParentSubquery3 = parentSubquery3.solve();
	int expectedResultsParentSubquery3[4][1] = {
		{6}, {8}, {13}, {15}
	};
	CPPUNIT_ASSERT_EQUAL((size_t)4, actualResultsParentSubquery3->getAllResults().size());
	for (size_t i = 0; i < 4; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsParentSubquery3[i][j], actualResultsParentSubquery3->getResultAt(i, j));
		}
	}

	// Test 4: Parent(w1, _)
	ParentSubquery parentSubquery4 = ParentSubquery(&synonymTable, pk);
	parentSubquery4.setSynonyms("w1", "_");
	ResultTuple* actualResultsParentSubquery4 = parentSubquery4.solve();
	int expectedResultsParentSubquery4[2][1] = {
		{6}, {15}
	};
	CPPUNIT_ASSERT_EQUAL((size_t)2, actualResultsParentSubquery4->getAllResults().size());
	for (size_t i = 0; i < 2; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsParentSubquery4[i][j], actualResultsParentSubquery4->getResultAt(i, j));
		}
	}

	// Test 5: Parent(6,s1)
	ParentSubquery parentSubquery5 = ParentSubquery(&synonymTable, pk);
	parentSubquery5.setSynonyms(6, "s1");
	ResultTuple* actualResultsParentSubquery5 = parentSubquery5.solve();
	int expectedResultsParentSubquery5[4][1] = {
		{7}, {8}, {11}, {12}
	};
	CPPUNIT_ASSERT_EQUAL((size_t)4, actualResultsParentSubquery5->getAllResults().size());
	for (size_t i = 0; i < 4; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsParentSubquery5[i][j], actualResultsParentSubquery5->getResultAt(i, j));
		}
	}

	// Test 0: Parent(s1, s2)
	ParentSubquery parentsubquery0 = ParentSubquery(&synonymTable, pk);
	parentsubquery0.setSynonyms("s1", "s2");
	ResultTuple* actualResultparentsubquery0 = parentsubquery0.solve();
	int expectedResultparentsubquery0[10][2] = {
		{6,7} , {6,8}, {6,11}, {6,12}, {8,9}, {8,10}, {13,14}, {13,15}, {13,17} , {15,16} 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery0)/sizeof(expectedResultparentsubquery0[0])), actualResultparentsubquery0->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery0)/sizeof(expectedResultparentsubquery0[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery0[i])/sizeof(expectedResultparentsubquery0[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery0[i][j], actualResultparentsubquery0->getResultAt(i, j));
		}
	}

	// Test 1: Parent(s1, a2)
	ParentSubquery parentsubquery1 = ParentSubquery(&synonymTable, pk);
	parentsubquery1.setSynonyms("s1", "a2");
	ResultTuple* actualResultparentsubquery1 = parentsubquery1.solve();
	int expectedResultparentsubquery1[7][2] = {
		{6,7}, {6,12}, {8, 9}, {8, 10}, {13, 14}, {13, 17}, {15,16}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery1)/sizeof(expectedResultparentsubquery1[0])), actualResultparentsubquery1->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery1)/sizeof(expectedResultparentsubquery1[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery1[i])/sizeof(expectedResultparentsubquery1[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery1[i][j], actualResultparentsubquery1->getResultAt(i, j));
		}
	}

	// Test 2: parent(s1, w2)
	ParentSubquery parentsubquery2 = ParentSubquery(&synonymTable, pk);
	parentsubquery2.setSynonyms("s1", "w2");
	ResultTuple* actualResultparentsubquery2 = parentsubquery2.solve();
	int expectedResultparentsubquery2[1][2] = {
		{13, 15}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery2)/sizeof(expectedResultparentsubquery2[0])), actualResultparentsubquery2->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery2)/sizeof(expectedResultparentsubquery2[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery2[i])/sizeof(expectedResultparentsubquery2[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery2[i][j], actualResultparentsubquery2->getResultAt(i, j));
		}
	}

	// Test 3: Follows(s1, i2)
	ParentSubquery parentsubquery3 = ParentSubquery(&synonymTable, pk);
	parentsubquery3.setSynonyms("s1", "i2");
	ResultTuple* actualResultparentsubquery3 = parentsubquery3.solve();
	int expectedResultparentsubquery3[1][2] = {
		{6, 8}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery3)/sizeof(expectedResultparentsubquery3[0])), actualResultparentsubquery3->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery3)/sizeof(expectedResultparentsubquery3[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery3[i])/sizeof(expectedResultparentsubquery3[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery3[i][j], actualResultparentsubquery3->getResultAt(i, j));
		}
	}

	// Test 6: parent(s1, c2)
	ParentSubquery parentsubquery6 = ParentSubquery(&synonymTable, pk);
	parentsubquery6.setSynonyms("s1", "c2");
	ResultTuple* actualResultparentsubquery6 = parentsubquery6.solve();
	int expectedResultparentsubquery6[1][2] = {
		{6,11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery6)/sizeof(expectedResultparentsubquery6[0])), actualResultparentsubquery6->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery6)/sizeof(expectedResultparentsubquery6[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery6[i])/sizeof(expectedResultparentsubquery6[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery6[i][j], actualResultparentsubquery6->getResultAt(i, j));
		}
	}

	// Test 7: Parent(s1, l2)
	ParentSubquery parentsubquery7 = ParentSubquery(&synonymTable, pk);
	parentsubquery7.setSynonyms("s1", "l2");
	ResultTuple* actualResultparentsubquery7 = parentsubquery7.solve();
	int expectedResultparentsubquery7[10][2] = {
		{6,7} , {6,8}, {6,11}, {6,12}, {8,9}, {8,10}, {13,14}, {13,15}, {13,17} , {15,16}  
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery7)/sizeof(expectedResultparentsubquery7[0])), actualResultparentsubquery7->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery7)/sizeof(expectedResultparentsubquery7[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery7[i])/sizeof(expectedResultparentsubquery7[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery7[i][j], actualResultparentsubquery7->getResultAt(i, j));
		}
	}

	// Test 9: Parent(s1, _)
	ParentSubquery parentsubquery9 = ParentSubquery(&synonymTable, pk);
	parentsubquery9.setSynonyms("s1", "_");
	ResultTuple* actualResultparentsubquery9 = parentsubquery9.solve();
	int expectedResultparentsubquery9[4][1] = {
		{6}, {8}, {13}, {15}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery9)/sizeof(expectedResultparentsubquery9[0])), actualResultparentsubquery9->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery9)/sizeof(expectedResultparentsubquery9[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery9[i])/sizeof(expectedResultparentsubquery9[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery9[i][j], actualResultparentsubquery9->getResultAt(i, j));
		}
	}

	// Test 10: Parent(s1, 8)
	ParentSubquery parentsubquery10 = ParentSubquery(&synonymTable, pk);
	parentsubquery10.setSynonyms("s1", 8);
	ResultTuple* actualResultparentsubquery10 = parentsubquery10.solve();
	int expectedResultparentsubquery10[1][1] = {
		{6}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery10)/sizeof(expectedResultparentsubquery10[0])), actualResultparentsubquery10->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery10)/sizeof(expectedResultparentsubquery10[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery10[i])/sizeof(expectedResultparentsubquery10[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery10[i][j], actualResultparentsubquery10->getResultAt(i, j));
		}
	}

	// Test 11: Parent(s1, 15)
	ParentSubquery parentsubquery11 = ParentSubquery(&synonymTable, pk);
	parentsubquery11.setSynonyms("s1", 15);
	ResultTuple* actualResultparentsubquery11 = parentsubquery11.solve();
	int expectedResultparentsubquery11[1][1] = {
		{13}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery11)/sizeof(expectedResultparentsubquery11[0])), actualResultparentsubquery11->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery11)/sizeof(expectedResultparentsubquery11[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery11[i])/sizeof(expectedResultparentsubquery11[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery11[i][j], actualResultparentsubquery11->getResultAt(i, j));
		}
	}


	// Test 24: Parent(w1, s2)
	ParentSubquery parentsubquery24 = ParentSubquery(&synonymTable, pk);
	parentsubquery24.setSynonyms("w1", "s2");
	ResultTuple* actualResultparentsubquery24 = parentsubquery24.solve();
	int expectedResultparentsubquery24[5][2] = {
		{6,7} , {6,8}, {6,11}, {6,12}, {15,16}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery24)/sizeof(expectedResultparentsubquery24[0])), actualResultparentsubquery24->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery24)/sizeof(expectedResultparentsubquery24[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery24[i])/sizeof(expectedResultparentsubquery24[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery24[i][j], actualResultparentsubquery24->getResultAt(i, j));
		}
	}

	// Test 25: Parent(w1, a2)
	ParentSubquery parentsubquery25 = ParentSubquery(&synonymTable, pk);
	parentsubquery25.setSynonyms("w1", "a2");
	ResultTuple* actualResultparentsubquery25 = parentsubquery25.solve();
	int expectedResultparentsubquery25[3][2] = {
		{6,7} ,{6,12}, {15,16}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery25)/sizeof(expectedResultparentsubquery25[0])), actualResultparentsubquery25->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery25)/sizeof(expectedResultparentsubquery25[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery25[i])/sizeof(expectedResultparentsubquery25[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery25[i][j], actualResultparentsubquery25->getResultAt(i, j));
		}
	}

	// Test 26: Parent(w1, w2)
	ParentSubquery parentsubquery26 = ParentSubquery(&synonymTable, pk);
	parentsubquery26.setSynonyms("w1", "w2");
	ResultTuple* actualResultparentsubquery26 = parentsubquery26.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentsubquery26->getAllResults().size());

	// Test 27: Parent(w1, i2)
	ParentSubquery parentsubquery27 = ParentSubquery(&synonymTable, pk);
	parentsubquery27.setSynonyms("w1", "i2");
	ResultTuple* actualResultparentsubquery27 = parentsubquery27.solve();
	int expectedResultparentsubquery27[1][2] = {
		{6, 8}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery27)/sizeof(expectedResultparentsubquery27[0])), actualResultparentsubquery27->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery27)/sizeof(expectedResultparentsubquery27[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery27[i])/sizeof(expectedResultparentsubquery27[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery27[i][j], actualResultparentsubquery27->getResultAt(i, j));
		}
	}

	// Test 30: Parent(w1, c2)
	ParentSubquery parentsubquery30 = ParentSubquery(&synonymTable, pk);
	parentsubquery30.setSynonyms("w1", "c2");
	ResultTuple* actualResultparentsubquery30 = parentsubquery30.solve();
	int expectedResultparentsubquery30[1][2] = {
		{6,11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery30)/sizeof(expectedResultparentsubquery30[0])), actualResultparentsubquery30->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery30)/sizeof(expectedResultparentsubquery30[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery30[i])/sizeof(expectedResultparentsubquery30[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery30[i][j], actualResultparentsubquery30->getResultAt(i, j));
		}
	}

	// Test 31: Parent(w1, l2)
	ParentSubquery parentsubquery31 = ParentSubquery(&synonymTable, pk);
	parentsubquery31.setSynonyms("w1", "l2");
	ResultTuple* actualResultparentsubquery31 = parentsubquery31.solve();
	int expectedResultparentsubquery31[5][2] = {
		{6, 7}, {6,8}, {6,11}, {6,12}, {15,16}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery31)/sizeof(expectedResultparentsubquery31[0])), actualResultparentsubquery31->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery31)/sizeof(expectedResultparentsubquery31[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery31[i])/sizeof(expectedResultparentsubquery31[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery31[i][j], actualResultparentsubquery31->getResultAt(i, j));
		}
	}

	// Test 33: Parent(w1, _)
	ParentSubquery parentsubquery33 = ParentSubquery(&synonymTable, pk);
	parentsubquery33.setSynonyms("w1", "_");
	ResultTuple* actualResultparentsubquery33 = parentsubquery33.solve();
	int expectedResultparentsubquery33[2][1] = {
		{6}, {15}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery33)/sizeof(expectedResultparentsubquery33[0])), actualResultparentsubquery33->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery33)/sizeof(expectedResultparentsubquery33[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery33[i])/sizeof(expectedResultparentsubquery33[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery33[i][j], actualResultparentsubquery33->getResultAt(i, j));
		}
	}

	// Test 34: Parent(w1, 2)
	ParentSubquery parentsubquery34 = ParentSubquery(&synonymTable, pk);
	parentsubquery34.setSynonyms("w1", 2);
	ResultTuple* actualResultparentsubquery34 = parentsubquery34.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentsubquery34->getAllResults().size());

	// Test 35: Parent(w1, 11)
	ParentSubquery parentsubquery35 = ParentSubquery(&synonymTable, pk);
	parentsubquery35.setSynonyms("w1", 11);
	ResultTuple* actualResultparentsubquery35 = parentsubquery35.solve();
	int expectedResultparentsubquery35[1][1] = {
		{6}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery35)/sizeof(expectedResultparentsubquery35[0])), actualResultparentsubquery35->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery35)/sizeof(expectedResultparentsubquery35[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery35[i])/sizeof(expectedResultparentsubquery35[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery35[i][j], actualResultparentsubquery35->getResultAt(i, j));
		}
	}

	// Test 36: Parent(i1, s2)
	ParentSubquery parentsubquery36 = ParentSubquery(&synonymTable, pk);
	parentsubquery36.setSynonyms("i1", "s2");
	ResultTuple* actualResultparentsubquery36 = parentsubquery36.solve();
	int expectedResultparentsubquery36[5][2] = {
		{8,9} , {8,10}, {13,14}, {13,15}, {13,17}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery36)/sizeof(expectedResultparentsubquery36[0])), actualResultparentsubquery36->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery36)/sizeof(expectedResultparentsubquery36[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery36[i])/sizeof(expectedResultparentsubquery36[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery36[i][j], actualResultparentsubquery36->getResultAt(i, j));
		}
	}

	// Test 37: Parent(i1, a2)
	ParentSubquery parentsubquery37 = ParentSubquery(&synonymTable, pk);
	parentsubquery37.setSynonyms("i1", "a2");
	ResultTuple* actualResultparentsubquery37 = parentsubquery37.solve();
	int expectedResultparentsubquery37[4][2] = {
		{8,9} , {8,10}, {13,14}, {13,17}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery37)/sizeof(expectedResultparentsubquery37[0])), actualResultparentsubquery37->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery37)/sizeof(expectedResultparentsubquery37[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery37[i])/sizeof(expectedResultparentsubquery37[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery37[i][j], actualResultparentsubquery37->getResultAt(i, j));
		}
	}

	// Test 38: Parent(i1, w2)
	ParentSubquery parentsubquery38 = ParentSubquery(&synonymTable, pk);
	parentsubquery38.setSynonyms("i1", "w2");
	ResultTuple* actualResultparentsubquery38 = parentsubquery38.solve();
	int expectedResultparentsubquery38[1][2] = {
		{13,15}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery38)/sizeof(expectedResultparentsubquery38[0])), actualResultparentsubquery38->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery38)/sizeof(expectedResultparentsubquery38[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery38[i])/sizeof(expectedResultparentsubquery38[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery38[i][j], actualResultparentsubquery38->getResultAt(i, j));
		}
	}

	// Test 39: Parent(i1, i2)
	ParentSubquery parentsubquery39 = ParentSubquery(&synonymTable, pk);
	parentsubquery39.setSynonyms("i1", "i2");
	ResultTuple* actualResultparentsubquery39 = parentsubquery39.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentsubquery39->getAllResults().size());

	// Test 42: Parent(i1, c2)
	ParentSubquery parentsubquery42 = ParentSubquery(&synonymTable, pk);
	parentsubquery42.setSynonyms("i1", "c2");
	ResultTuple* actualResultparentsubquery42 = parentsubquery42.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentsubquery42->getAllResults().size());

	// Test 43: Parent(i1, l2)
	ParentSubquery parentsubquery43 = ParentSubquery(&synonymTable, pk);
	parentsubquery43.setSynonyms("i1", "l2");
	ResultTuple* actualResultparentsubquery43 = parentsubquery43.solve();
	int expectedResultparentsubquery43[5][2] = {
		{8, 9}, {8,10}, {13,14}, {13,15}, {13,17}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery43)/sizeof(expectedResultparentsubquery43[0])), actualResultparentsubquery43->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery43)/sizeof(expectedResultparentsubquery43[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery43[i])/sizeof(expectedResultparentsubquery43[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery43[i][j], actualResultparentsubquery43->getResultAt(i, j));
		}
	}


	// Test 45: Parent(i1, _)
	ParentSubquery parentsubquery45 = ParentSubquery(&synonymTable, pk);
	parentsubquery45.setSynonyms("i1", "_");
	ResultTuple* actualResultparentsubquery45 = parentsubquery45.solve();
	int expectedResultparentsubquery45[2][1] = {
		{8}, {13}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery45)/sizeof(expectedResultparentsubquery45[0])), actualResultparentsubquery45->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery45)/sizeof(expectedResultparentsubquery45[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery45[i])/sizeof(expectedResultparentsubquery45[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery45[i][j], actualResultparentsubquery45->getResultAt(i, j));
		}
	}

	// Test 46: Parent(i1, 2)
	ParentSubquery parentsubquery46 = ParentSubquery(&synonymTable, pk);
	parentsubquery46.setSynonyms("i1", 2);
	ResultTuple* actualResultparentsubquery46 = parentsubquery46.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentsubquery46->getAllResults().size());

	// Test 47: Parent(i1, 14)
	ParentSubquery parentsubquery47 = ParentSubquery(&synonymTable, pk);
	parentsubquery47.setSynonyms("i1", 14);
	ResultTuple* actualResultparentsubquery47 = parentsubquery47.solve();
	int expectedResultparentsubquery47[1][1] = {
		{13}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery47)/sizeof(expectedResultparentsubquery47[0])), actualResultparentsubquery47->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery47)/sizeof(expectedResultparentsubquery47[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery47[i])/sizeof(expectedResultparentsubquery47[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery47[i][j], actualResultparentsubquery47->getResultAt(i, j));
		}
	}


	// Test 84: Parent(l1, s2)
	ParentSubquery parentsubquery84 = ParentSubquery(&synonymTable, pk);
	parentsubquery84.setSynonyms("l1", "s2");
	ResultTuple* actualResultparentsubquery84 = parentsubquery84.solve();
	int expectedResultparentsubquery84[10][2] = {
		{6,7}, {6,8}, {6,11}, {6,12}, {8,9}, {8,10}, {13,14}, {13,15}, {13,17}, {15,16}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery84)/sizeof(expectedResultparentsubquery84[0])), actualResultparentsubquery84->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery84)/sizeof(expectedResultparentsubquery84[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery84[i])/sizeof(expectedResultparentsubquery84[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery84[i][j], actualResultparentsubquery84->getResultAt(i, j));
		}
	}

	// Test 85: Parent(l1, a2)
	ParentSubquery parentsubquery85 = ParentSubquery(&synonymTable, pk);
	parentsubquery85.setSynonyms("l1", "a2");
	ResultTuple* actualResultparentsubquery85 = parentsubquery85.solve();
	int expectedResultparentsubquery85[7][2] = {
		{6,7}, {6,12}, {8,9}, {8,10}, {13,14}, {13,17}, {15,16}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery85)/sizeof(expectedResultparentsubquery85[0])), actualResultparentsubquery85->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery85)/sizeof(expectedResultparentsubquery85[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery85[i])/sizeof(expectedResultparentsubquery85[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery85[i][j], actualResultparentsubquery85->getResultAt(i, j));
		}
	}
 
	// Test 86: Parent(l1, w2)
	ParentSubquery parentsubquery86 = ParentSubquery(&synonymTable, pk);
	parentsubquery86.setSynonyms("l1", "w2");
	ResultTuple* actualResultparentsubquery86 = parentsubquery86.solve();
	int expectedResultparentsubquery86[1][2] = {
		{13, 15}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery86)/sizeof(expectedResultparentsubquery86[0])), actualResultparentsubquery86->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery86)/sizeof(expectedResultparentsubquery86[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery86[i])/sizeof(expectedResultparentsubquery86[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery86[i][j], actualResultparentsubquery86->getResultAt(i, j));
		}
	}

	// Test 87: Parent(l1, i2)
	ParentSubquery parentsubquery87 = ParentSubquery(&synonymTable, pk);
	parentsubquery87.setSynonyms("l1", "i2");
	ResultTuple* actualResultparentsubquery87 = parentsubquery87.solve();
	int expectedResultparentsubquery87[1][2] = {
		{6, 8} 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery87)/sizeof(expectedResultparentsubquery87[0])), actualResultparentsubquery87->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery87)/sizeof(expectedResultparentsubquery87[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery87[i])/sizeof(expectedResultparentsubquery87[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery87[i][j], actualResultparentsubquery87->getResultAt(i, j));
		}
	}

	// Test 90: Parent(l1, c2)
	ParentSubquery parentsubquery90 = ParentSubquery(&synonymTable, pk);
	parentsubquery90.setSynonyms("l1", "c2");
	ResultTuple* actualResultparentsubquery90 = parentsubquery90.solve();
	int expectedResultparentsubquery90[1][2] = {
		{6, 11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery90)/sizeof(expectedResultparentsubquery90[0])), actualResultparentsubquery90->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery90)/sizeof(expectedResultparentsubquery90[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery90[i])/sizeof(expectedResultparentsubquery90[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery90[i][j], actualResultparentsubquery90->getResultAt(i, j));
		}
	}

	// Test 91: Parent(l1, l2)
	ParentSubquery parentsubquery91 = ParentSubquery(&synonymTable, pk);
	parentsubquery91.setSynonyms("l1", "l2");
	ResultTuple* actualResultparentsubquery91 = parentsubquery91.solve();
	int expectedResultparentsubquery91[10][2] = {
	{6,7}, {6,8}, {6,11}, {6,12}, {8,9}, {8,10}, {13,14}, {13,15}, {13,17}, {15,16}	
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery91)/sizeof(expectedResultparentsubquery91[0])), actualResultparentsubquery91->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery91)/sizeof(expectedResultparentsubquery91[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery91[i])/sizeof(expectedResultparentsubquery91[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery91[i][j], actualResultparentsubquery91->getResultAt(i, j));
		}
	}

	// Test 93: Parent(l1, _)
	ParentSubquery parentsubquery93 = ParentSubquery(&synonymTable, pk);
	parentsubquery93.setSynonyms("l1", "_");
	ResultTuple* actualResultparentsubquery93 = parentsubquery93.solve();
	int expectedResultparentsubquery93[4][1] = {
		{6}, {8}, {13}, {15}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery93)/sizeof(expectedResultparentsubquery93[0])), actualResultparentsubquery93->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery93)/sizeof(expectedResultparentsubquery93[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery93[i])/sizeof(expectedResultparentsubquery93[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery93[i][j], actualResultparentsubquery93->getResultAt(i, j));
		}
	}

	// Test 94: Parent(l1, 7)
	ParentSubquery parentsubquery94 = ParentSubquery(&synonymTable, pk);
	parentsubquery94.setSynonyms("l1", 7);
	ResultTuple* actualResultparentsubquery94 = parentsubquery94.solve();
	int expectedResultparentsubquery94[1][1] = {
		{6}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery94)/sizeof(expectedResultparentsubquery94[0])), actualResultparentsubquery94->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery94)/sizeof(expectedResultparentsubquery94[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery94[i])/sizeof(expectedResultparentsubquery94[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery94[i][j], actualResultparentsubquery94->getResultAt(i, j));
		}
	}

	// Test 95: Parent(l1, 11)
	ParentSubquery parentsubquery95 = ParentSubquery(&synonymTable, pk);
	parentsubquery95.setSynonyms("l1", 11);
	ResultTuple* actualResultparentsubquery95 = parentsubquery95.solve();
	int expectedResultparentsubquery95[1][1] = {
		{6}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery95)/sizeof(expectedResultparentsubquery95[0])), actualResultparentsubquery95->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery95)/sizeof(expectedResultparentsubquery95[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery95[i])/sizeof(expectedResultparentsubquery95[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery95[i][j], actualResultparentsubquery95->getResultAt(i, j));
		}
	}

	// Test 108: Parent(_, s2)
	ParentSubquery parentsubquery108 = ParentSubquery(&synonymTable, pk);
	parentsubquery108.setSynonyms("_", "s2");
	ResultTuple* actualResultparentsubquery108 = parentsubquery108.solve();
	int expectedResultparentsubquery108[10][1] = {
		{7}, {8}, {9}, {10}, {11}, {12}, {14}, {15}, {16}, {17}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery108)/sizeof(expectedResultparentsubquery108[0])), actualResultparentsubquery108->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery108)/sizeof(expectedResultparentsubquery108[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery108[i])/sizeof(expectedResultparentsubquery108[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery108[i][j], actualResultparentsubquery108->getResultAt(i, j));
		}
	}

	// Test 109: Parent(_, a2)
	ParentSubquery parentsubquery109 = ParentSubquery(&synonymTable, pk);
	parentsubquery109.setSynonyms("_", "a2");
	ResultTuple* actualResultparentsubquery109 = parentsubquery109.solve();
	int expectedResultparentsubquery109[7][1] = {
		{7}, {9}, {10}, {12}, {14}, {16}, {17}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery109)/sizeof(expectedResultparentsubquery109[0])), actualResultparentsubquery109->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery109)/sizeof(expectedResultparentsubquery109[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery109[i])/sizeof(expectedResultparentsubquery109[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery109[i][j], actualResultparentsubquery109->getResultAt(i, j));
		}
	}

	// Test 110: Parent(_, w2)
	ParentSubquery parentsubquery110 = ParentSubquery(&synonymTable, pk);
	parentsubquery110.setSynonyms("_", "w2");
	ResultTuple* actualResultparentsubquery110 = parentsubquery110.solve();
	int expectedResultparentsubquery110[1][1] = {
		{15}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery110)/sizeof(expectedResultparentsubquery110[0])), actualResultparentsubquery110->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery110)/sizeof(expectedResultparentsubquery110[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery110[i])/sizeof(expectedResultparentsubquery110[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery110[i][j], actualResultparentsubquery110->getResultAt(i, j));
		}
	}

	// Test 111: Parent(_, i2)
	ParentSubquery parentsubquery111 = ParentSubquery(&synonymTable, pk);
	parentsubquery111.setSynonyms("_", "i2");
	ResultTuple* actualResultparentsubquery111 = parentsubquery111.solve();
	int expectedResultparentsubquery111[1][1] = {
		{8}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery111)/sizeof(expectedResultparentsubquery111[0])), actualResultparentsubquery111->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery111)/sizeof(expectedResultparentsubquery111[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery111[i])/sizeof(expectedResultparentsubquery111[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery111[i][j], actualResultparentsubquery111->getResultAt(i, j));
		}
	}

	// Test 114: Parent(_, c2)
	ParentSubquery parentsubquery114 = ParentSubquery(&synonymTable, pk);
	parentsubquery114.setSynonyms("_", "c2");
	ResultTuple* actualResultparentsubquery114 = parentsubquery114.solve();
	int expectedResultparentsubquery114[1][1] = {
		{11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery114)/sizeof(expectedResultparentsubquery114[0])), actualResultparentsubquery114->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery114)/sizeof(expectedResultparentsubquery114[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery114[i])/sizeof(expectedResultparentsubquery114[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery114[i][j], actualResultparentsubquery114->getResultAt(i, j));
		}
	}

	// Test 115: Parent(_, l2)
	ParentSubquery parentsubquery115 = ParentSubquery(&synonymTable, pk);
	parentsubquery115.setSynonyms("_", "l2");
	ResultTuple* actualResultparentsubquery115 = parentsubquery115.solve();
	int expectedResultparentsubquery115[10][1] = {
		{7}, {8}, {9}, {10}, {11}, {12}, {14}, {15}, {16}, {17}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery115)/sizeof(expectedResultparentsubquery115[0])), actualResultparentsubquery115->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery115)/sizeof(expectedResultparentsubquery115[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery115[i])/sizeof(expectedResultparentsubquery115[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery115[i][j], actualResultparentsubquery115->getResultAt(i, j));
		}
	}

	// Test 117: Parent(_, _)
	ParentSubquery parentsubquery117 = ParentSubquery(&synonymTable, pk);
	parentsubquery117.setSynonyms("_", "_");
	ResultTuple* actualResultparentsubquery117 = parentsubquery117.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentsubquery117->getAllResults().size());
	CPPUNIT_ASSERT(actualResultparentsubquery117->isBool());
	CPPUNIT_ASSERT(!actualResultparentsubquery117->isEmpty());

	// Test 118: Parent(_, 2)
	ParentSubquery parentsubquery118 = ParentSubquery(&synonymTable, pk);
	parentsubquery118.setSynonyms("_", 2);
	ResultTuple* actualResultparentsubquery118 = parentsubquery118.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentsubquery118->getAllResults().size());
	CPPUNIT_ASSERT(actualResultparentsubquery118->isBool());
	CPPUNIT_ASSERT(actualResultparentsubquery118->isEmpty());

	// Test 119: Parent(_, 7)
	ParentSubquery parentsubquery119 = ParentSubquery(&synonymTable, pk);
	parentsubquery119.setSynonyms("_", 7);
	ResultTuple* actualResultparentsubquery119 = parentsubquery119.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentsubquery119->getAllResults().size());
	CPPUNIT_ASSERT(actualResultparentsubquery119->isBool());
	CPPUNIT_ASSERT(!actualResultparentsubquery119->isEmpty());

	// Test 120: Parent(15, s2)
	ParentSubquery parentsubquery120 = ParentSubquery(&synonymTable, pk);
	parentsubquery120.setSynonyms(15, "s2");
	ResultTuple* actualResultparentsubquery120 = parentsubquery120.solve();
	int expectedResultparentsubquery120[1][1] = {
		{16}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery120)/sizeof(expectedResultparentsubquery120[0])), actualResultparentsubquery120->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery120)/sizeof(expectedResultparentsubquery120[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery120[i])/sizeof(expectedResultparentsubquery120[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery120[i][j], actualResultparentsubquery120->getResultAt(i, j));
		}
	}

	// Test 121: Parent(15, a2)
	ParentSubquery parentsubquery121 = ParentSubquery(&synonymTable, pk);
	parentsubquery121.setSynonyms(15, "a2");
	ResultTuple* actualResultparentsubquery121 = parentsubquery121.solve();
	int expectedResultparentsubquery121[1][1] = {
		{16}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery121)/sizeof(expectedResultparentsubquery121[0])), actualResultparentsubquery121->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery121)/sizeof(expectedResultparentsubquery121[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery121[i])/sizeof(expectedResultparentsubquery121[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery121[i][j], actualResultparentsubquery121->getResultAt(i, j));
		}
	}

	// Test 122: Parent(1, w2)
	ParentSubquery parentsubquery122 = ParentSubquery(&synonymTable, pk);
	parentsubquery122.setSynonyms(1, "w2");
	ResultTuple* actualResultparentsubquery122 = parentsubquery122.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentsubquery122->getAllResults().size());

	// Test 123: Parent(1, i2)
	ParentSubquery parentsubquery123 = ParentSubquery(&synonymTable, pk);
	parentsubquery123.setSynonyms(1, "i2");
	ResultTuple* actualResultparentsubquery123 = parentsubquery123.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentsubquery123->getAllResults().size());

	// Test 126: Parent(1, c2)
	ParentSubquery parentsubquery126 = ParentSubquery(&synonymTable, pk);
	parentsubquery126.setSynonyms(1, "c2");
	ResultTuple* actualResultparentsubquery126 = parentsubquery126.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentsubquery126->getAllResults().size());

	// Test 127: Parent(15, l2)
	ParentSubquery parentsubquery127 = ParentSubquery(&synonymTable, pk);
	parentsubquery127.setSynonyms(15, "l2");
	ResultTuple* actualResultparentsubquery127 = parentsubquery127.solve();
	int expectedResultparentsubquery127[1][1] = {
		{16}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery127)/sizeof(expectedResultparentsubquery127[0])), actualResultparentsubquery127->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery127)/sizeof(expectedResultparentsubquery127[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery127[i])/sizeof(expectedResultparentsubquery127[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery127[i][j], actualResultparentsubquery127->getResultAt(i, j));
		}
	}

	// Test 129: Parent(1, _)
	ParentSubquery parentsubquery129 = ParentSubquery(&synonymTable, pk);
	parentsubquery129.setSynonyms(1, "_");
	ResultTuple* actualResultparentsubquery129 = parentsubquery129.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentsubquery129->getAllResults().size());
	CPPUNIT_ASSERT(actualResultparentsubquery129->isBool());
	CPPUNIT_ASSERT(actualResultparentsubquery129->isEmpty());

	// Test 130: Parent(1, 2)
	ParentSubquery parentsubquery130 = ParentSubquery(&synonymTable, pk);
	parentsubquery130.setSynonyms(1, 2);
	ResultTuple* actualResultparentsubquery130 = parentsubquery130.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentsubquery130->getAllResults().size());
	CPPUNIT_ASSERT(actualResultparentsubquery130->isBool());
	CPPUNIT_ASSERT(actualResultparentsubquery130->isEmpty());

	// Test 131: Parent(1, 6)
	ParentSubquery parentsubquery131 = ParentSubquery(&synonymTable, pk);
	parentsubquery131.setSynonyms(1, 6);
	ResultTuple* actualResultparentsubquery131 = parentsubquery131.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentsubquery131->getAllResults().size());
	CPPUNIT_ASSERT(actualResultparentsubquery131->isBool());
	CPPUNIT_ASSERT(actualResultparentsubquery131->isEmpty());

	// Test 132: Parent(8, s2)
	ParentSubquery parentsubquery132 = ParentSubquery(&synonymTable, pk);
	parentsubquery132.setSynonyms(8, "s2");
	ResultTuple* actualResultparentsubquery132 = parentsubquery132.solve();
	int expectedResultparentsubquery132[2][1] = {
		{9}, {10}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery132)/sizeof(expectedResultparentsubquery132[0])), actualResultparentsubquery132->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery132)/sizeof(expectedResultparentsubquery132[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery132[i])/sizeof(expectedResultparentsubquery132[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery132[i][j], actualResultparentsubquery132->getResultAt(i, j));
		}
	}

	// Test 133: Parent(5, a2)
	ParentSubquery parentsubquery133 = ParentSubquery(&synonymTable, pk);
	parentsubquery133.setSynonyms(5, "a2");
	ResultTuple* actualResultparentsubquery133 = parentsubquery133.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentsubquery133->getAllResults().size());

	// Test 134: Parent(13, w2)
	ParentSubquery parentsubquery134 = ParentSubquery(&synonymTable, pk);
	parentsubquery134.setSynonyms(13, "w2");
	ResultTuple* actualResultparentsubquery134 = parentsubquery134.solve();
	int expectedResultparentsubquery134[1][1] = {
		{15}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery134)/sizeof(expectedResultparentsubquery134[0])), actualResultparentsubquery134->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery134)/sizeof(expectedResultparentsubquery134[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery134[i])/sizeof(expectedResultparentsubquery134[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery134[i][j], actualResultparentsubquery134->getResultAt(i, j));
		}
	}

	// Test 135: Parent(6, i2)
	ParentSubquery parentsubquery135 = ParentSubquery(&synonymTable, pk);
	parentsubquery135.setSynonyms(6, "i2");
	ResultTuple* actualResultparentsubquery135 = parentsubquery135.solve();
	int expectedResultparentsubquery135[1][1] = {
		{8}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery135)/sizeof(expectedResultparentsubquery135[0])), actualResultparentsubquery135->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery135)/sizeof(expectedResultparentsubquery135[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery135[i])/sizeof(expectedResultparentsubquery135[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery135[i][j], actualResultparentsubquery135->getResultAt(i, j));
		}
	}

	// Test 138: Parent(6, c2)
	ParentSubquery parentsubquery138 = ParentSubquery(&synonymTable, pk);
	parentsubquery138.setSynonyms(6, "c2");
	ResultTuple* actualResultparentsubquery138 = parentsubquery138.solve();
	int expectedResultparentsubquery138[1][1] = {
		{11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery138)/sizeof(expectedResultparentsubquery138[0])), actualResultparentsubquery138->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery138)/sizeof(expectedResultparentsubquery138[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery138[i])/sizeof(expectedResultparentsubquery138[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery138[i][j], actualResultparentsubquery138->getResultAt(i, j));
		}
	}

	// Test 139: Parent(15, l2)
	ParentSubquery parentsubquery139 = ParentSubquery(&synonymTable, pk);
	parentsubquery139.setSynonyms(15, "l2");
	ResultTuple* actualResultparentsubquery139 = parentsubquery139.solve();
	int expectedResultparentsubquery139[1][1] = {
		{16}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentsubquery139)/sizeof(expectedResultparentsubquery139[0])), actualResultparentsubquery139->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentsubquery139)/sizeof(expectedResultparentsubquery139[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentsubquery139[i])/sizeof(expectedResultparentsubquery139[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentsubquery139[i][j], actualResultparentsubquery139->getResultAt(i, j));
		}
	}

	// Test 141: Parent(5, _)
	ParentSubquery parentsubquery141 = ParentSubquery(&synonymTable, pk);
	parentsubquery141.setSynonyms(5, "_");
	ResultTuple* actualResultparentsubquery141 = parentsubquery141.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentsubquery141->getAllResults().size());
	CPPUNIT_ASSERT(actualResultparentsubquery141->isBool());
	CPPUNIT_ASSERT(actualResultparentsubquery141->isEmpty());

	// Test 142: Parent(5, 2)
	ParentSubquery parentsubquery142 = ParentSubquery(&synonymTable, pk);
	parentsubquery142.setSynonyms(5, 2);
	ResultTuple* actualResultparentsubquery142 = parentsubquery142.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentsubquery142->getAllResults().size());
	CPPUNIT_ASSERT(actualResultparentsubquery142->isBool());
	CPPUNIT_ASSERT(actualResultparentsubquery142->isEmpty());

	// Test 143: Parent(5, 6)
	ParentSubquery parentsubquery143 = ParentSubquery(&synonymTable, pk);
	parentsubquery143.setSynonyms(5, 6);
	ResultTuple* actualResultparentsubquery143 = parentsubquery143.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentsubquery143->getAllResults().size());
	CPPUNIT_ASSERT(actualResultparentsubquery143->isBool());
	CPPUNIT_ASSERT(actualResultparentsubquery143->isEmpty());
}

void SubqueryTest::testParentTuple(){
	// testTuple:
	//  s1  |  a1  |  w1  |  i2  |  c2  |  l1  |  const1  |  v1  |  proc1  |
	//  2   |  1   |  6   |  8   |  3   |  1   |  0       |  0   |  0      |
	//  6   |  2   |  6   |  8   |  3   |  1   |  0       |  0   |  0      |
	//  6   |  1   |  15  |  8   |  3   |  1   |  0       |  0   |  0      |
	//  8   |  2   |  6   |  13  |  3   |  1   |  0       |  0   |  0      |
	//  8   |  1   |  6   |  8   |  11  |  1   |  0       |  0   |  0      |
	//  13  |  2   |  6   |  8   |  3   |  7   |  0       |  0   |  0      |
	//  12  |  1   |  6   |  8   |  3   |  1   |  3       |  0   |  0      |
	//  15  |  2   |  6   |  8   |  3   |  1   |  0       |  2   |  0      |
	//  15  |  2   |  6   |  8   |  3   |  1   |  0       |  2   |  1      |
	ResultTuple testTuple = ResultTuple();
	int index = testTuple.addSynonym("s1");
	testTuple.addSynonymToMap("s1", index);
	index = testTuple.addSynonym("a1");
	testTuple.addSynonymToMap("a1", index);
	index = testTuple.addSynonym("w1");
	testTuple.addSynonymToMap("w1", index);
	index = testTuple.addSynonym("i2");
	testTuple.addSynonymToMap("i2", index);
	index = testTuple.addSynonym("c2");
	testTuple.addSynonymToMap("c2", index);
	index = testTuple.addSynonym("l1");
	testTuple.addSynonymToMap("l1", index);
	index = testTuple.addSynonym("const1");
	testTuple.addSynonymToMap("const1", index);
	index = testTuple.addSynonym("v1");
	testTuple.addSynonymToMap("v1", index);
	index = testTuple.addSynonym("proc1");
	testTuple.addSynonymToMap("proc1", index);
	int data[9][9] = {
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{12   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	for (int i = 0; i < 9; i++){
		vector<int> tempVector = vector<int>();
		testTuple.addResultRow(tempVector);
		for (int j = 0; j < 9; j++){
			testTuple.addResult(i, data[i][j]);
		}
	}

	// Test 0: Parent(s1, s2)
	ParentSubquery Parentsubquery0 = ParentSubquery(&synonymTable, pk);
	Parentsubquery0.setSynonyms("s1", "s2");
	ResultTuple* actualResultParentsubquery0 = Parentsubquery0.solve(&testTuple);
	int expectedResultParentsubquery0[17][10] = {

		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0,   7  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0,   8  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0,	  11 },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0,	  12 },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0,   7  },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0,   8  },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0,   11 },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0,   12 },
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0,   9  },
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0,   10 },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0 ,  9  },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0 ,  10  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   , 0,   14  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   , 0,   15  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   , 0,   17  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1,  16  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2,  16  }
	};	
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultParentsubquery0)/sizeof(expectedResultParentsubquery0[0])), actualResultParentsubquery0->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultParentsubquery0)/sizeof(expectedResultParentsubquery0[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultParentsubquery0[i])/sizeof(expectedResultParentsubquery0[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultParentsubquery0[i][j], actualResultParentsubquery0->getResultAt(i, j));
		}
	}

	// Test 1: Parent(s1, a2)
	ParentSubquery Parentsubquery1 = ParentSubquery(&synonymTable, pk);
	Parentsubquery1.setSynonyms("s1", "a2");
	ResultTuple* actualResultParentsubquery1 = Parentsubquery1.solve(&testTuple);
	int expectedResultParentsubquery1[12][10] = {
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0,   7  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0,	  12 },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0,   7  },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0,   12 },
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0,   9  },
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0,   10 },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0 ,  9  },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0 ,  10  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   , 0,   14  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   , 0,   17  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1,  16  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2,  16  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultParentsubquery1)/sizeof(expectedResultParentsubquery1[0])), actualResultParentsubquery1->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultParentsubquery1)/sizeof(expectedResultParentsubquery1[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultParentsubquery1[i])/sizeof(expectedResultParentsubquery1[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultParentsubquery1[i][j], actualResultParentsubquery1->getResultAt(i, j));
		}
	}

	// Test 2: Parent(s1, w2)
	ParentSubquery Parentsubquery2 = ParentSubquery(&synonymTable, pk);
	Parentsubquery2.setSynonyms("s1", "w2");
	ResultTuple* actualResultParentsubquery2 = Parentsubquery2.solve(&testTuple);
	int expectedResultParentsubquery2[1][10] = {
		
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   , 0,   15  },

	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultParentsubquery2)/sizeof(expectedResultParentsubquery2[0])), actualResultParentsubquery2->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultParentsubquery2)/sizeof(expectedResultParentsubquery2[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultParentsubquery2[i])/sizeof(expectedResultParentsubquery2[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultParentsubquery2[i][j], actualResultParentsubquery2->getResultAt(i, j));
		}
	}

	// Test 3: Parent(s1, i2)
	ParentSubquery Parentsubquery3 = ParentSubquery(&synonymTable, pk);
	Parentsubquery3.setSynonyms("s1", "i2");
	ResultTuple* actualResultParentsubquery3 = Parentsubquery3.solve(&testTuple);
	int expectedResultParentsubquery3[2][9] = {
		
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0 },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0 }
		
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultParentsubquery3)/sizeof(expectedResultParentsubquery3[0])), actualResultParentsubquery3->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultParentsubquery3)/sizeof(expectedResultParentsubquery3[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultParentsubquery3[i])/sizeof(expectedResultParentsubquery3[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultParentsubquery3[i][j], actualResultParentsubquery3->getResultAt(i, j));
		}
	}

	// Test 6: Parent(s1, c2)
	ParentSubquery Parentsubquery6 = ParentSubquery(&synonymTable, pk);
	Parentsubquery6.setSynonyms("s1", "c2");
	ResultTuple* actualResultParentsubquery6 = Parentsubquery6.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentsubquery6->getAllResults().size());

	// Test 7: Parent(s1, l2)
	ParentSubquery Parentsubquery7 = ParentSubquery(&synonymTable, pk);
	Parentsubquery7.setSynonyms("s1", "l2");
	ResultTuple* actualResultParentsubquery7 = Parentsubquery7.solve(&testTuple);
	int expectedResultParentsubquery7[17][10] = {
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0,   7  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0,   8  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0,	  11 },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0,	  12 },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0,   7  },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0,   8  },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0,   11 },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0,   12 },
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0,   9  },
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0,   10 },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0 ,  9  },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0 ,  10  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   , 0,   14  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   , 0,   15  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   , 0,   17  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1,  16  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2,  16  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultParentsubquery7)/sizeof(expectedResultParentsubquery7[0])), actualResultParentsubquery7->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultParentsubquery7)/sizeof(expectedResultParentsubquery7[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultParentsubquery7[i])/sizeof(expectedResultParentsubquery7[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultParentsubquery7[i][j], actualResultParentsubquery7->getResultAt(i, j));
		}
	}

	// Test 9: Parent(s1, _)
	ParentSubquery Parentsubquery9 = ParentSubquery(&synonymTable, pk);
	Parentsubquery9.setSynonyms("s1", "_");
	ResultTuple* actualResultParentsubquery9 = Parentsubquery9.solve(&testTuple);
	int expectedResultParentsubquery9[7][9] = {
		
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0 },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1 },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2 }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultParentsubquery9)/sizeof(expectedResultParentsubquery9[0])), actualResultParentsubquery9->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultParentsubquery9)/sizeof(expectedResultParentsubquery9[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultParentsubquery9[i])/sizeof(expectedResultParentsubquery9[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultParentsubquery9[i][j], actualResultParentsubquery9->getResultAt(i, j));
		}
	}

	// Test 10: Parent(s1, 2)
	ParentSubquery Parentsubquery10 = ParentSubquery(&synonymTable, pk);
	Parentsubquery10.setSynonyms("s1", 2);
	ResultTuple* actualResultParentsubquery10 = Parentsubquery10.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentsubquery10->getAllResults().size());

	// Test 11: Parent(s1, 6)
	ParentSubquery Parentsubquery11 = ParentSubquery(&synonymTable, pk);
	Parentsubquery11.setSynonyms("s1", 6);
	ResultTuple* actualResultParentsubquery11 = Parentsubquery11.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentsubquery11->getAllResults().size());


	// Test 24: Parent(w1, s2)
	ParentSubquery Parentsubquery24 = ParentSubquery(&synonymTable, pk);
	Parentsubquery24.setSynonyms("w1", "s2");
	ResultTuple* actualResultParentsubquery24 = Parentsubquery24.solve(&testTuple);
	int expectedResultParentsubquery24[33][10] = {
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0   ,  7},
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0   ,  8},
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0   ,  11},
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0   ,  12},
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0   ,  7},
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0   ,  8},
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0   ,  11},
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0   ,  12},
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0   ,  16},
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0   ,  7},
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0   ,  8},
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0   ,  11},
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0   ,  12},
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0   ,  7},
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0   ,  8},
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0   ,  11},
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0   ,  12},
		{13  ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0   ,  7},
		{13  ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0   ,  8},
		{13  ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0   ,  11},
		{13  ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0   ,  12},
		{12  ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0   ,  7},
		{12  ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0   ,  8},
		{12  ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0   ,  11},
		{12  ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0   ,  12},
		{15  ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1   ,  7},
		{15  ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1   ,  8},
		{15  ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1   ,  11},
		{15  ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1   ,  12},
		{15  ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2   ,  7},
		{15  ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2   ,  8},
		{15  ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2   ,  11},
		{15  ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2   ,  12}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultParentsubquery24)/sizeof(expectedResultParentsubquery24[0])), actualResultParentsubquery24->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultParentsubquery24)/sizeof(expectedResultParentsubquery24[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultParentsubquery24[i])/sizeof(expectedResultParentsubquery24[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultParentsubquery24[i][j], actualResultParentsubquery24->getResultAt(i, j));
		}
	}

	// Test 25: Parent(w1, a2)
	ParentSubquery Parentsubquery25 = ParentSubquery(&synonymTable, pk);
	Parentsubquery25.setSynonyms("w1", "a2");
	ResultTuple* actualResultParentsubquery25 = Parentsubquery25.solve(&testTuple);
	int expectedResultParentsubquery25[17][10] = {
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0   ,  7},
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0   ,  12},
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0   ,  7},
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0   ,  12},
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0   ,  16},
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0   ,  7},
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0   ,  12},
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0   ,  7},
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0   ,  12},
		{13  ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0   ,  7},
		{13  ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0   ,  12},
		{12  ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0   ,  7},
		{12  ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0   ,  12},
		{15  ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1   ,  7},
		{15  ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1   ,  12},
		{15  ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2   ,  7},
		{15  ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2   ,  12}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultParentsubquery25)/sizeof(expectedResultParentsubquery25[0])), actualResultParentsubquery25->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultParentsubquery25)/sizeof(expectedResultParentsubquery25[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultParentsubquery25[i])/sizeof(expectedResultParentsubquery25[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultParentsubquery25[i][j], actualResultParentsubquery25->getResultAt(i, j));
		}
	}


	// Test 26: Parent(w1, w2)
	ParentSubquery Parentsubquery26 = ParentSubquery(&synonymTable, pk);
	Parentsubquery26.setSynonyms("w1", "w2");
	ResultTuple* actualResultParentsubquery26 = Parentsubquery26.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentsubquery26->getAllResults().size());

	// Test 27: Parent(w1, i2)
	ParentSubquery Parentsubquery27 = ParentSubquery(&synonymTable, pk);
	Parentsubquery27.setSynonyms("w1", "i2");
	ResultTuple* actualResultParentsubquery27 = Parentsubquery27.solve(&testTuple);
	int expectedResultParentsubquery27[7][9] = {
		
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{12   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
		
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultParentsubquery27)/sizeof(expectedResultParentsubquery27[0])), actualResultParentsubquery27->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultParentsubquery27)/sizeof(expectedResultParentsubquery27[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultParentsubquery27[i])/sizeof(expectedResultParentsubquery27[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultParentsubquery27[i][j], actualResultParentsubquery27->getResultAt(i, j));
		}
	}

	// Test 30: Parent(w1, c2)
	ParentSubquery Parentsubquery30 = ParentSubquery(&synonymTable, pk);
	Parentsubquery30.setSynonyms("w1", "c2");
	ResultTuple* actualResultParentsubquery30 = Parentsubquery30.solve(&testTuple);
	int expectedResultParentsubquery30[1][9] = {

		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
	};

	// Test 31: Parent(w1, l2)
	ParentSubquery Parentsubquery31 = ParentSubquery(&synonymTable, pk);
	Parentsubquery31.setSynonyms("w1", "l2");
	ResultTuple* actualResultParentsubquery31 = Parentsubquery31.solve(&testTuple);
	int expectedResultParentsubquery31[33][10] = {
	    {2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0   ,  7},
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0   ,  8},
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0   ,  11},
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0   ,  12},
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0   ,  7},
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0   ,  8},
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0   ,  11},
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0   ,  12},
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0   ,  16},
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0   ,  7},
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0   ,  8},
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0   ,  11},
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0   ,  12},
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0   ,  7},
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0   ,  8},
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0   ,  11},
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0   ,  12},
		{13  ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0   ,  7},
		{13  ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0   ,  8},
		{13  ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0   ,  11},
		{13  ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0   ,  12},
		{12  ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0   ,  7},
		{12  ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0   ,  8},
		{12  ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0   ,  11},
		{12  ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0   ,  12},
		{15  ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1   ,  7},
		{15  ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1   ,  8},
		{15  ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1   ,  11},
		{15  ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1   ,  12},
		{15  ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2   ,  7},
		{15  ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2   ,  8},
		{15  ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2   ,  11},
		{15  ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2   ,  12}
	};

	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultParentsubquery31)/sizeof(expectedResultParentsubquery31[0])), actualResultParentsubquery31->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultParentsubquery31)/sizeof(expectedResultParentsubquery31[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultParentsubquery31[i])/sizeof(expectedResultParentsubquery31[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultParentsubquery31[i][j], actualResultParentsubquery31->getResultAt(i, j));
		}
	}

	// Test 33: Parent(w1, _)
	ParentSubquery Parentsubquery33 = ParentSubquery(&synonymTable, pk);
	Parentsubquery33.setSynonyms("w1", "_");
	ResultTuple* actualResultParentsubquery33 = Parentsubquery33.solve(&testTuple);
	int expectedResultParentsubquery33[9][9] = {
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{12   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};

	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultParentsubquery33)/sizeof(expectedResultParentsubquery33[0])), actualResultParentsubquery33->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultParentsubquery33)/sizeof(expectedResultParentsubquery33[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultParentsubquery33[i])/sizeof(expectedResultParentsubquery33[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultParentsubquery33[i][j], actualResultParentsubquery33->getResultAt(i, j));
		}
	}

	// Test 34: Parent(w1, 2)
	ParentSubquery Parentsubquery34 = ParentSubquery(&synonymTable, pk);
	Parentsubquery34.setSynonyms("w1", 2);
	ResultTuple* actualResultParentsubquery34 = Parentsubquery34.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentsubquery34->getAllResults().size());

	// Test 35: Parent(w1, 12)
	ParentSubquery Parentsubquery35 = ParentSubquery(&synonymTable, pk);
	Parentsubquery35.setSynonyms("w1", 12);
	ResultTuple* actualResultParentsubquery35 = Parentsubquery35.solve(&testTuple);
	int expectedResultParentsubquery35[8][9] = {
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{12   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultParentsubquery35)/sizeof(expectedResultParentsubquery35[0])), actualResultParentsubquery35->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultParentsubquery35)/sizeof(expectedResultParentsubquery35[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultParentsubquery35[i])/sizeof(expectedResultParentsubquery35[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultParentsubquery35[i][j], actualResultParentsubquery35->getResultAt(i, j));
		}
	}


	// Test 39: Parent(i1, i2)
	ParentSubquery Parentsubquery39 = ParentSubquery(&synonymTable, pk);
	Parentsubquery39.setSynonyms("i1", "i2");
	ResultTuple* actualResultParentsubquery39 = Parentsubquery39.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentsubquery39->getAllResults().size());

	// Test 42: Parent(i1, c2)
	ParentSubquery Parentsubquery42 = ParentSubquery(&synonymTable, pk);
	Parentsubquery42.setSynonyms("i1", "c2");
	ResultTuple* actualResultParentsubquery42 = Parentsubquery42.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentsubquery42->getAllResults().size());

	// Test 75: Parent(c1, i2)
	ParentSubquery Parentsubquery75 = ParentSubquery(&synonymTable, pk);
	Parentsubquery75.setSynonyms("c1", "i2");
	ResultTuple* actualResultParentsubquery75 = Parentsubquery75.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentsubquery75->getAllResults().size());

	// Test 78: Parent(c1, c2)
	ParentSubquery Parentsubquery78 = ParentSubquery(&synonymTable, pk);
	Parentsubquery78.setSynonyms("c1", "c2");
	ResultTuple* actualResultParentsubquery78 = Parentsubquery78.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentsubquery78->getAllResults().size());

	// Test 84: Parent(l1, s2)
	ParentSubquery Parentsubquery84 = ParentSubquery(&synonymTable, pk);
	Parentsubquery84.setSynonyms("l1", "s2");
	ResultTuple* actualResultParentsubquery84 = Parentsubquery84.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentsubquery84->getAllResults().size());


	// Test 85: Parent(l1, a2)
	ParentSubquery Parentsubquery85 = ParentSubquery(&synonymTable, pk);
	Parentsubquery85.setSynonyms("l1", "a2");
	ResultTuple* actualResultParentsubquery85 = Parentsubquery85.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentsubquery85->getAllResults().size());

	// Test 86: Parent(l1, w2)
	ParentSubquery Parentsubquery86 = ParentSubquery(&synonymTable, pk);
	Parentsubquery86.setSynonyms("l1", "w2");
	ResultTuple* actualResultParentsubquery86 = Parentsubquery86.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentsubquery86->getAllResults().size());

	// Test 87: Parent(l1, i2)
	ParentSubquery Parentsubquery87 = ParentSubquery(&synonymTable, pk);
	Parentsubquery87.setSynonyms("l1", "i2");
	ResultTuple* actualResultParentsubquery87 = Parentsubquery87.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentsubquery87->getAllResults().size());

	// Test 90: Parent(l1, c2)
	ParentSubquery Parentsubquery90 = ParentSubquery(&synonymTable, pk);
	Parentsubquery90.setSynonyms("l1", "c2");
	ResultTuple* actualResultParentsubquery90 = Parentsubquery90.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentsubquery90->getAllResults().size());

	// Test 91: Parent(l1, l2)
	ParentSubquery Parentsubquery91 = ParentSubquery(&synonymTable, pk);
	Parentsubquery91.setSynonyms("l1", "l2");
	ResultTuple* actualResultParentsubquery91 = Parentsubquery91.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentsubquery91->getAllResults().size());

	// Test 93: Parent(l1, _)
	ParentSubquery Parentsubquery93 = ParentSubquery(&synonymTable, pk);
	Parentsubquery93.setSynonyms("l1", "_");
	ResultTuple* actualResultParentsubquery93 = Parentsubquery93.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentsubquery93->getAllResults().size());

	// Test 94: Parent(l1, 2)
	ParentSubquery Parentsubquery94 = ParentSubquery(&synonymTable, pk);
	Parentsubquery94.setSynonyms("l1", 2);
	ResultTuple* actualResultParentsubquery94 = Parentsubquery94.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentsubquery94->getAllResults().size());

	// Test 95: Parent(l1, 6)
	ParentSubquery Parentsubquery95 = ParentSubquery(&synonymTable, pk);
	Parentsubquery95.setSynonyms("l1", 6);
	ResultTuple* actualResultParentsubquery95 = Parentsubquery95.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentsubquery95->getAllResults().size());

	// Test 111: Parent(_, i2)
	ParentSubquery Parentsubquery111 = ParentSubquery(&synonymTable, pk);
	Parentsubquery111.setSynonyms("_", "i2");
	ResultTuple* actualResultParentsubquery111 = Parentsubquery111.solve(&testTuple);
	int expectedResultParentsubquery111[8][9] = {
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{12   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultParentsubquery111)/sizeof(expectedResultParentsubquery111[0])), actualResultParentsubquery111->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultParentsubquery111)/sizeof(expectedResultParentsubquery111[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultParentsubquery111[i])/sizeof(expectedResultParentsubquery111[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultParentsubquery111[i][j], actualResultParentsubquery111->getResultAt(i, j));
		}
	}

	// Test 114: Parent(_, c2)
	ParentSubquery Parentsubquery114 = ParentSubquery(&synonymTable, pk);
	Parentsubquery114.setSynonyms("_", "c2");
	ResultTuple* actualResultParentsubquery114 = Parentsubquery114.solve(&testTuple);
	int expectedResultParentsubquery114[1][9] = {
	
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },

	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultParentsubquery114)/sizeof(expectedResultParentsubquery114[0])), actualResultParentsubquery114->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultParentsubquery114)/sizeof(expectedResultParentsubquery114[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultParentsubquery114[i])/sizeof(expectedResultParentsubquery114[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultParentsubquery114[i][j], actualResultParentsubquery114->getResultAt(i, j));
		}
	}

	// Test 123: Parent(1, i2)
	ParentSubquery Parentsubquery123 = ParentSubquery(&synonymTable, pk);
	Parentsubquery123.setSynonyms(1, "i2");
	ResultTuple* actualResultParentsubquery123 = Parentsubquery123.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentsubquery123->getAllResults().size());

	// Test 126: Parent(1, c2)
	ParentSubquery Parentsubquery126 = ParentSubquery(&synonymTable, pk);
	Parentsubquery126.setSynonyms(1, "c2");
	ResultTuple* actualResultParentsubquery126 = Parentsubquery126.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentsubquery126->getAllResults().size());

	// Test 135: Parent(7, i2)
	ParentSubquery Parentsubquery135 = ParentSubquery(&synonymTable, pk);
	Parentsubquery135.setSynonyms(7, "i2");
	ResultTuple* actualResultParentsubquery135 = Parentsubquery135.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentsubquery135->getAllResults().size());

	// Test 138: Parent(6, c2)
	ParentSubquery Parentsubquery138 = ParentSubquery(&synonymTable, pk);
	Parentsubquery138.setSynonyms(6, "c2");
	ResultTuple* actualResultParentsubquery138 = Parentsubquery138.solve(&testTuple);
	int expectedResultParentsubquery138[1][9] = {
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultParentsubquery138)/sizeof(expectedResultParentsubquery138[0])), actualResultParentsubquery138->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultParentsubquery138)/sizeof(expectedResultParentsubquery138[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultParentsubquery138[i])/sizeof(expectedResultParentsubquery138[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultParentsubquery138[i][j], actualResultParentsubquery138->getResultAt(i, j));
		}
	}
}

void SubqueryTest::testParentT(){
	// Test 0: ParentStar(s1, s2)
	ParentStarSubquery parentStarsubquery0 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery0.setSynonyms("s1", "s2");
	ResultTuple* actualResultparentStarsubquery0 = parentStarsubquery0.solve();
	int expectedResultparentStarsubquery0[13][2] = {
		{6, 7}, {6, 8}, {6, 9}, {6, 10}, {6, 11}, {6, 12},
		{8, 9}, {8, 10}, 
		{13, 14}, {13, 15}, {13, 16}, {13, 17}, 
		{15, 16}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery0)/sizeof(expectedResultparentStarsubquery0[0])), actualResultparentStarsubquery0->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery0)/sizeof(expectedResultparentStarsubquery0[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery0[i])/sizeof(expectedResultparentStarsubquery0[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery0[i][j], actualResultparentStarsubquery0->getResultAt(i, j));
		}
	}

	// Test 1: ParentStar(s1, a2)
	ParentStarSubquery parentStarsubquery1 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery1.setSynonyms("s1", "a2");
	ResultTuple* actualResultparentStarsubquery1 = parentStarsubquery1.solve();
	int expectedResultparentStarsubquery1[10][2] = {
		{6, 7}, {6, 9}, {6, 10}, {6, 12},
		{8, 9}, {8, 10}, 
		{13, 14}, {13, 16}, {13, 17}, 
		{15, 16}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery1)/sizeof(expectedResultparentStarsubquery1[0])), actualResultparentStarsubquery1->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery1)/sizeof(expectedResultparentStarsubquery1[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery1[i])/sizeof(expectedResultparentStarsubquery1[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery1[i][j], actualResultparentStarsubquery1->getResultAt(i, j));
		}
	}

	// Test 2: parentStar(s1, w2)
	ParentStarSubquery parentStarsubquery2 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery2.setSynonyms("s1", "w2");
	ResultTuple* actualResultparentStarsubquery2 = parentStarsubquery2.solve();
	int expectedResultparentStarsubquery2[1][2] = {
		{13, 15}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery2)/sizeof(expectedResultparentStarsubquery2[0])), actualResultparentStarsubquery2->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery2)/sizeof(expectedResultparentStarsubquery2[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery2[i])/sizeof(expectedResultparentStarsubquery2[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery2[i][j], actualResultparentStarsubquery2->getResultAt(i, j));
		}
	}

	// Test 3: Follows(s1, i2)
	ParentStarSubquery parentStarsubquery3 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery3.setSynonyms("s1", "i2");
	ResultTuple* actualResultparentStarsubquery3 = parentStarsubquery3.solve();
	int expectedResultparentStarsubquery3[1][2] = {
		{6, 8}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery3)/sizeof(expectedResultparentStarsubquery3[0])), actualResultparentStarsubquery3->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery3)/sizeof(expectedResultparentStarsubquery3[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery3[i])/sizeof(expectedResultparentStarsubquery3[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery3[i][j], actualResultparentStarsubquery3->getResultAt(i, j));
		}
	}

	// Test 6: parentStar(s1, c2)
	ParentStarSubquery parentStarsubquery6 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery6.setSynonyms("s1", "c2");
	ResultTuple* actualResultparentStarsubquery6 = parentStarsubquery6.solve();
	int expectedResultparentStarsubquery6[1][2] = {
		{6,11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery6)/sizeof(expectedResultparentStarsubquery6[0])), actualResultparentStarsubquery6->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery6)/sizeof(expectedResultparentStarsubquery6[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery6[i])/sizeof(expectedResultparentStarsubquery6[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery6[i][j], actualResultparentStarsubquery6->getResultAt(i, j));
		}
	}

	// Test 7: ParentStar(s1, l2)
	ParentStarSubquery parentStarsubquery7 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery7.setSynonyms("s1", "l2");
	ResultTuple* actualResultparentStarsubquery7 = parentStarsubquery7.solve();
	int expectedResultparentStarsubquery7[13][2] = {
		{6, 7}, {6, 8}, {6, 9}, {6, 10}, {6, 11}, {6, 12},
		{8, 9}, {8, 10}, 
		{13, 14}, {13, 15}, {13, 16}, {13, 17}, 
		{15, 16}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery7)/sizeof(expectedResultparentStarsubquery7[0])), actualResultparentStarsubquery7->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery7)/sizeof(expectedResultparentStarsubquery7[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery7[i])/sizeof(expectedResultparentStarsubquery7[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery7[i][j], actualResultparentStarsubquery7->getResultAt(i, j));
		}
	}

	// Test 9: ParentStar(s1, _)
	ParentStarSubquery parentStarsubquery9 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery9.setSynonyms("s1", "_");
	ResultTuple* actualResultparentStarsubquery9 = parentStarsubquery9.solve();
	int expectedResultparentStarsubquery9[4][1] = {
		{6}, {8}, {13}, {15}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery9)/sizeof(expectedResultparentStarsubquery9[0])), actualResultparentStarsubquery9->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery9)/sizeof(expectedResultparentStarsubquery9[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery9[i])/sizeof(expectedResultparentStarsubquery9[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery9[i][j], actualResultparentStarsubquery9->getResultAt(i, j));
		}
	}

	// Test 10: ParentStar(s1, 8)
	ParentStarSubquery parentStarsubquery10 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery10.setSynonyms("s1", 8);
	ResultTuple* actualResultparentStarsubquery10 = parentStarsubquery10.solve();
	int expectedResultparentStarsubquery10[1][1] = {
		{6}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery10)/sizeof(expectedResultparentStarsubquery10[0])), actualResultparentStarsubquery10->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery10)/sizeof(expectedResultparentStarsubquery10[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery10[i])/sizeof(expectedResultparentStarsubquery10[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery10[i][j], actualResultparentStarsubquery10->getResultAt(i, j));
		}
	}

	// Test 11: ParentStar(s1, 15)
	ParentStarSubquery parentStarsubquery11 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery11.setSynonyms("s1", 15);
	ResultTuple* actualResultparentStarsubquery11 = parentStarsubquery11.solve();
	int expectedResultparentStarsubquery11[1][1] = {
		{13}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery11)/sizeof(expectedResultparentStarsubquery11[0])), actualResultparentStarsubquery11->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery11)/sizeof(expectedResultparentStarsubquery11[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery11[i])/sizeof(expectedResultparentStarsubquery11[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery11[i][j], actualResultparentStarsubquery11->getResultAt(i, j));
		}
	}


	// Test 24: ParentStar(w1, s2)
	ParentStarSubquery parentStarsubquery24 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery24.setSynonyms("w1", "s2");
	ResultTuple* actualResultparentStarsubquery24 = parentStarsubquery24.solve();
	int expectedResultparentStarsubquery24[7][2] = {
		{6, 7} , {6, 8}, {6, 9}, {6, 10}, {6, 11}, {6, 12}, {15, 16}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery24)/sizeof(expectedResultparentStarsubquery24[0])), actualResultparentStarsubquery24->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery24)/sizeof(expectedResultparentStarsubquery24[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery24[i])/sizeof(expectedResultparentStarsubquery24[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery24[i][j], actualResultparentStarsubquery24->getResultAt(i, j));
		}
	}

	// Test 25: ParentStar(w1, a2)
	ParentStarSubquery parentStarsubquery25 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery25.setSynonyms("w1", "a2");
	ResultTuple* actualResultparentStarsubquery25 = parentStarsubquery25.solve();
	int expectedResultparentStarsubquery25[5][2] = {
		{6, 7}, {6, 9}, {6, 10}, {6, 12}, {15, 16}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery25)/sizeof(expectedResultparentStarsubquery25[0])), actualResultparentStarsubquery25->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery25)/sizeof(expectedResultparentStarsubquery25[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery25[i])/sizeof(expectedResultparentStarsubquery25[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery25[i][j], actualResultparentStarsubquery25->getResultAt(i, j));
		}
	}

	// Test 26: ParentStar(w1, w2)
	ParentStarSubquery parentStarsubquery26 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery26.setSynonyms("w1", "w2");
	ResultTuple* actualResultparentStarsubquery26 = parentStarsubquery26.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentStarsubquery26->getAllResults().size());

	// Test 27: ParentStar(w1, i2)
	ParentStarSubquery parentStarsubquery27 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery27.setSynonyms("w1", "i2");
	ResultTuple* actualResultparentStarsubquery27 = parentStarsubquery27.solve();
	int expectedResultparentStarsubquery27[1][2] = {
		{6, 8}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery27)/sizeof(expectedResultparentStarsubquery27[0])), actualResultparentStarsubquery27->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery27)/sizeof(expectedResultparentStarsubquery27[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery27[i])/sizeof(expectedResultparentStarsubquery27[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery27[i][j], actualResultparentStarsubquery27->getResultAt(i, j));
		}
	}

	// Test 30: ParentStar(w1, c2)
	ParentStarSubquery parentStarsubquery30 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery30.setSynonyms("w1", "c2");
	ResultTuple* actualResultparentStarsubquery30 = parentStarsubquery30.solve();
	int expectedResultparentStarsubquery30[1][2] = {
		{6, 11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery30)/sizeof(expectedResultparentStarsubquery30[0])), actualResultparentStarsubquery30->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery30)/sizeof(expectedResultparentStarsubquery30[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery30[i])/sizeof(expectedResultparentStarsubquery30[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery30[i][j], actualResultparentStarsubquery30->getResultAt(i, j));
		}
	}

	// Test 31: ParentStar(w1, l2)
	ParentStarSubquery parentStarsubquery31 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery31.setSynonyms("w1", "l2");
	ResultTuple* actualResultparentStarsubquery31 = parentStarsubquery31.solve();
	int expectedResultparentStarsubquery31[7][2] = {
		{6, 7}, {6, 8}, {6, 9}, {6, 10}, {6, 11}, {6, 12}, {15, 16}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery31)/sizeof(expectedResultparentStarsubquery31[0])), actualResultparentStarsubquery31->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery31)/sizeof(expectedResultparentStarsubquery31[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery31[i])/sizeof(expectedResultparentStarsubquery31[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery31[i][j], actualResultparentStarsubquery31->getResultAt(i, j));
		}
	}

	// Test 33: ParentStar(w1, _)
	ParentStarSubquery parentStarsubquery33 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery33.setSynonyms("w1", "_");
	ResultTuple* actualResultparentStarsubquery33 = parentStarsubquery33.solve();
	int expectedResultparentStarsubquery33[2][1] = {
		{6}, {15}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery33)/sizeof(expectedResultparentStarsubquery33[0])), actualResultparentStarsubquery33->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery33)/sizeof(expectedResultparentStarsubquery33[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery33[i])/sizeof(expectedResultparentStarsubquery33[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery33[i][j], actualResultparentStarsubquery33->getResultAt(i, j));
		}
	}

	// Test 34: ParentStar(w1, 2)
	ParentStarSubquery parentStarsubquery34 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery34.setSynonyms("w1", 2);
	ResultTuple* actualResultparentStarsubquery34 = parentStarsubquery34.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentStarsubquery34->getAllResults().size());

	// Test 35: ParentStar(w1, 11)
	ParentStarSubquery parentStarsubquery35 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery35.setSynonyms("w1", 11);
	ResultTuple* actualResultparentStarsubquery35 = parentStarsubquery35.solve();
	int expectedResultparentStarsubquery35[1][1] = {
		{6}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery35)/sizeof(expectedResultparentStarsubquery35[0])), actualResultparentStarsubquery35->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery35)/sizeof(expectedResultparentStarsubquery35[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery35[i])/sizeof(expectedResultparentStarsubquery35[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery35[i][j], actualResultparentStarsubquery35->getResultAt(i, j));
		}
	}

	// Test 36: ParentStar(i1, s2)
	ParentStarSubquery parentStarsubquery36 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery36.setSynonyms("i1", "s2");
	ResultTuple* actualResultparentStarsubquery36 = parentStarsubquery36.solve();
	int expectedResultparentStarsubquery36[6][2] = {
		{8, 9}, {8, 10}, {13, 14}, {13, 15}, {13, 16}, {13, 17}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery36)/sizeof(expectedResultparentStarsubquery36[0])), actualResultparentStarsubquery36->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery36)/sizeof(expectedResultparentStarsubquery36[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery36[i])/sizeof(expectedResultparentStarsubquery36[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery36[i][j], actualResultparentStarsubquery36->getResultAt(i, j));
		}
	}

	// Test 37: ParentStar(i1, a2)
	ParentStarSubquery parentStarsubquery37 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery37.setSynonyms("i1", "a2");
	ResultTuple* actualResultparentStarsubquery37 = parentStarsubquery37.solve();
	int expectedResultparentStarsubquery37[5][2] = {
		{8, 9}, {8, 10}, {13, 14}, {13, 16}, {13, 17}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery37)/sizeof(expectedResultparentStarsubquery37[0])), actualResultparentStarsubquery37->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery37)/sizeof(expectedResultparentStarsubquery37[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery37[i])/sizeof(expectedResultparentStarsubquery37[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery37[i][j], actualResultparentStarsubquery37->getResultAt(i, j));
		}
	}

	// Test 38: ParentStar(i1, w2)
	ParentStarSubquery parentStarsubquery38 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery38.setSynonyms("i1", "w2");
	ResultTuple* actualResultparentStarsubquery38 = parentStarsubquery38.solve();
	int expectedResultparentStarsubquery38[1][2] = {
		{13, 15}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery38)/sizeof(expectedResultparentStarsubquery38[0])), actualResultparentStarsubquery38->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery38)/sizeof(expectedResultparentStarsubquery38[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery38[i])/sizeof(expectedResultparentStarsubquery38[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery38[i][j], actualResultparentStarsubquery38->getResultAt(i, j));
		}
	}

	// Test 39: ParentStar(i1, i2)
	ParentStarSubquery parentStarsubquery39 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery39.setSynonyms("i1", "i2");
	ResultTuple* actualResultparentStarsubquery39 = parentStarsubquery39.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentStarsubquery39->getAllResults().size());

	// Test 42: ParentStar(i1, c2)
	ParentStarSubquery parentStarsubquery42 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery42.setSynonyms("i1", "c2");
	ResultTuple* actualResultparentStarsubquery42 = parentStarsubquery42.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentStarsubquery42->getAllResults().size());

	// Test 43: ParentStar(i1, l2)
	ParentStarSubquery parentStarsubquery43 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery43.setSynonyms("i1", "l2");
	ResultTuple* actualResultparentStarsubquery43 = parentStarsubquery43.solve();
	int expectedResultparentStarsubquery43[6][2] = {
		{8, 9}, {8, 10}, {13, 14}, {13, 15}, {13, 16}, {13, 17}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery43)/sizeof(expectedResultparentStarsubquery43[0])), actualResultparentStarsubquery43->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery43)/sizeof(expectedResultparentStarsubquery43[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery43[i])/sizeof(expectedResultparentStarsubquery43[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery43[i][j], actualResultparentStarsubquery43->getResultAt(i, j));
		}
	}


	// Test 45: ParentStar(i1, _)
	ParentStarSubquery parentStarsubquery45 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery45.setSynonyms("i1", "_");
	ResultTuple* actualResultparentStarsubquery45 = parentStarsubquery45.solve();
	int expectedResultparentStarsubquery45[2][1] = {
		{8}, {13}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery45)/sizeof(expectedResultparentStarsubquery45[0])), actualResultparentStarsubquery45->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery45)/sizeof(expectedResultparentStarsubquery45[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery45[i])/sizeof(expectedResultparentStarsubquery45[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery45[i][j], actualResultparentStarsubquery45->getResultAt(i, j));
		}
	}

	// Test 46: ParentStar(i1, 2)
	ParentStarSubquery parentStarsubquery46 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery46.setSynonyms("i1", 2);
	ResultTuple* actualResultparentStarsubquery46 = parentStarsubquery46.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentStarsubquery46->getAllResults().size());

	// Test 47: ParentStar(i1, 14)
	ParentStarSubquery parentStarsubquery47 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery47.setSynonyms("i1", 14);
	ResultTuple* actualResultparentStarsubquery47 = parentStarsubquery47.solve();
	int expectedResultparentStarsubquery47[1][1] = {
		{13}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery47)/sizeof(expectedResultparentStarsubquery47[0])), actualResultparentStarsubquery47->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery47)/sizeof(expectedResultparentStarsubquery47[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery47[i])/sizeof(expectedResultparentStarsubquery47[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery47[i][j], actualResultparentStarsubquery47->getResultAt(i, j));
		}
	}


	// Test 84: ParentStar(l1, s2)
	ParentStarSubquery parentStarsubquery84 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery84.setSynonyms("l1", "s2");
	ResultTuple* actualResultparentStarsubquery84 = parentStarsubquery84.solve();
	int expectedResultparentStarsubquery84[13][2] = {
		{6, 7}, {6, 8}, {6, 9}, {6, 10}, {6, 11}, {6, 12},
		{8, 9}, {8, 10}, 
		{13, 14}, {13, 15}, {13, 16}, {13, 17}, 
		{15, 16}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery84)/sizeof(expectedResultparentStarsubquery84[0])), actualResultparentStarsubquery84->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery84)/sizeof(expectedResultparentStarsubquery84[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery84[i])/sizeof(expectedResultparentStarsubquery84[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery84[i][j], actualResultparentStarsubquery84->getResultAt(i, j));
		}
	}

	// Test 85: ParentStar(l1, a2)
	ParentStarSubquery parentStarsubquery85 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery85.setSynonyms("l1", "a2");
	ResultTuple* actualResultparentStarsubquery85 = parentStarsubquery85.solve();
	int expectedResultparentStarsubquery85[10][2] = {
		{6, 7}, {6, 9}, {6, 10}, {6, 12},
		{8, 9}, {8, 10}, 
		{13, 14}, {13, 16}, {13, 17}, 
		{15, 16}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery85)/sizeof(expectedResultparentStarsubquery85[0])), actualResultparentStarsubquery85->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery85)/sizeof(expectedResultparentStarsubquery85[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery85[i])/sizeof(expectedResultparentStarsubquery85[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery85[i][j], actualResultparentStarsubquery85->getResultAt(i, j));
		}
	}
 
	// Test 86: ParentStar(l1, w2)
	ParentStarSubquery parentStarsubquery86 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery86.setSynonyms("l1", "w2");
	ResultTuple* actualResultparentStarsubquery86 = parentStarsubquery86.solve();
	int expectedResultparentStarsubquery86[1][2] = {
		{13, 15}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery86)/sizeof(expectedResultparentStarsubquery86[0])), actualResultparentStarsubquery86->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery86)/sizeof(expectedResultparentStarsubquery86[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery86[i])/sizeof(expectedResultparentStarsubquery86[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery86[i][j], actualResultparentStarsubquery86->getResultAt(i, j));
		}
	}

	// Test 87: ParentStar(l1, i2)
	ParentStarSubquery parentStarsubquery87 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery87.setSynonyms("l1", "i2");
	ResultTuple* actualResultparentStarsubquery87 = parentStarsubquery87.solve();
	int expectedResultparentStarsubquery87[1][2] = {
		{6, 8} 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery87)/sizeof(expectedResultparentStarsubquery87[0])), actualResultparentStarsubquery87->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery87)/sizeof(expectedResultparentStarsubquery87[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery87[i])/sizeof(expectedResultparentStarsubquery87[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery87[i][j], actualResultparentStarsubquery87->getResultAt(i, j));
		}
	}

	// Test 90: ParentStar(l1, c2)
	ParentStarSubquery parentStarsubquery90 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery90.setSynonyms("l1", "c2");
	ResultTuple* actualResultparentStarsubquery90 = parentStarsubquery90.solve();
	int expectedResultparentStarsubquery90[1][2] = {
		{6, 11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery90)/sizeof(expectedResultparentStarsubquery90[0])), actualResultparentStarsubquery90->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery90)/sizeof(expectedResultparentStarsubquery90[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery90[i])/sizeof(expectedResultparentStarsubquery90[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery90[i][j], actualResultparentStarsubquery90->getResultAt(i, j));
		}
	}

	// Test 91: ParentStar(l1, l2)
	ParentStarSubquery parentStarsubquery91 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery91.setSynonyms("l1", "l2");
	ResultTuple* actualResultparentStarsubquery91 = parentStarsubquery91.solve();
	int expectedResultparentStarsubquery91[13][2] = {
		{6, 7}, {6, 8}, {6, 9}, {6, 10}, {6, 11}, {6, 12},
		{8, 9}, {8, 10}, 
		{13, 14}, {13, 15}, {13, 16}, {13, 17}, 
		{15, 16}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery91)/sizeof(expectedResultparentStarsubquery91[0])), actualResultparentStarsubquery91->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery91)/sizeof(expectedResultparentStarsubquery91[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery91[i])/sizeof(expectedResultparentStarsubquery91[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery91[i][j], actualResultparentStarsubquery91->getResultAt(i, j));
		}
	}

	// Test 93: ParentStar(l1, _)
	ParentStarSubquery parentStarsubquery93 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery93.setSynonyms("l1", "_");
	ResultTuple* actualResultparentStarsubquery93 = parentStarsubquery93.solve();
	int expectedResultparentStarsubquery93[4][1] = {
		{6}, {8}, {13}, {15}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery93)/sizeof(expectedResultparentStarsubquery93[0])), actualResultparentStarsubquery93->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery93)/sizeof(expectedResultparentStarsubquery93[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery93[i])/sizeof(expectedResultparentStarsubquery93[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery93[i][j], actualResultparentStarsubquery93->getResultAt(i, j));
		}
	}

	// Test 94: ParentStar(l1, 7)
	ParentStarSubquery parentStarsubquery94 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery94.setSynonyms("l1", 7);
	ResultTuple* actualResultparentStarsubquery94 = parentStarsubquery94.solve();
	int expectedResultparentStarsubquery94[1][1] = {
		{6}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery94)/sizeof(expectedResultparentStarsubquery94[0])), actualResultparentStarsubquery94->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery94)/sizeof(expectedResultparentStarsubquery94[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery94[i])/sizeof(expectedResultparentStarsubquery94[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery94[i][j], actualResultparentStarsubquery94->getResultAt(i, j));
		}
	}

	// Test 95: ParentStar(l1, 11)
	ParentStarSubquery parentStarsubquery95 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery95.setSynonyms("l1", 11);
	ResultTuple* actualResultparentStarsubquery95 = parentStarsubquery95.solve();
	int expectedResultparentStarsubquery95[1][1] = {
		{6}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery95)/sizeof(expectedResultparentStarsubquery95[0])), actualResultparentStarsubquery95->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery95)/sizeof(expectedResultparentStarsubquery95[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery95[i])/sizeof(expectedResultparentStarsubquery95[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery95[i][j], actualResultparentStarsubquery95->getResultAt(i, j));
		}
	}

	// Test 108: ParentStar(_, s2)
	ParentStarSubquery parentStarsubquery108 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery108.setSynonyms("_", "s2");
	ResultTuple* actualResultparentStarsubquery108 = parentStarsubquery108.solve();
	int expectedResultparentStarsubquery108[10][1] = {
		{7}, {8}, {9}, {10}, {11}, {12}, {14}, {15}, {16}, {17}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery108)/sizeof(expectedResultparentStarsubquery108[0])), actualResultparentStarsubquery108->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery108)/sizeof(expectedResultparentStarsubquery108[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery108[i])/sizeof(expectedResultparentStarsubquery108[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery108[i][j], actualResultparentStarsubquery108->getResultAt(i, j));
		}
	}

	// Test 109: ParentStar(_, a2)
	ParentStarSubquery parentStarsubquery109 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery109.setSynonyms("_", "a2");
	ResultTuple* actualResultparentStarsubquery109 = parentStarsubquery109.solve();
	int expectedResultparentStarsubquery109[7][1] = {
		{7}, {9}, {10}, {12}, {14}, {16}, {17}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery109)/sizeof(expectedResultparentStarsubquery109[0])), actualResultparentStarsubquery109->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery109)/sizeof(expectedResultparentStarsubquery109[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery109[i])/sizeof(expectedResultparentStarsubquery109[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery109[i][j], actualResultparentStarsubquery109->getResultAt(i, j));
		}
	}

	// Test 110: ParentStar(_, w2)
	ParentStarSubquery parentStarsubquery110 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery110.setSynonyms("_", "w2");
	ResultTuple* actualResultparentStarsubquery110 = parentStarsubquery110.solve();
	int expectedResultparentStarsubquery110[1][1] = {
		{15}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery110)/sizeof(expectedResultparentStarsubquery110[0])), actualResultparentStarsubquery110->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery110)/sizeof(expectedResultparentStarsubquery110[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery110[i])/sizeof(expectedResultparentStarsubquery110[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery110[i][j], actualResultparentStarsubquery110->getResultAt(i, j));
		}
	}

	// Test 111: ParentStar(_, i2)
	ParentStarSubquery parentStarsubquery111 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery111.setSynonyms("_", "i2");
	ResultTuple* actualResultparentStarsubquery111 = parentStarsubquery111.solve();
	int expectedResultparentStarsubquery111[1][1] = {
		{8}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery111)/sizeof(expectedResultparentStarsubquery111[0])), actualResultparentStarsubquery111->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery111)/sizeof(expectedResultparentStarsubquery111[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery111[i])/sizeof(expectedResultparentStarsubquery111[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery111[i][j], actualResultparentStarsubquery111->getResultAt(i, j));
		}
	}

	// Test 114: ParentStar(_, c2)
	ParentStarSubquery parentStarsubquery114 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery114.setSynonyms("_", "c2");
	ResultTuple* actualResultparentStarsubquery114 = parentStarsubquery114.solve();
	int expectedResultparentStarsubquery114[1][1] = {
		{11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery114)/sizeof(expectedResultparentStarsubquery114[0])), actualResultparentStarsubquery114->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery114)/sizeof(expectedResultparentStarsubquery114[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery114[i])/sizeof(expectedResultparentStarsubquery114[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery114[i][j], actualResultparentStarsubquery114->getResultAt(i, j));
		}
	}

	// Test 115: ParentStar(_, l2)
	ParentStarSubquery parentStarsubquery115 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery115.setSynonyms("_", "l2");
	ResultTuple* actualResultparentStarsubquery115 = parentStarsubquery115.solve();
	int expectedResultparentStarsubquery115[10][1] = {
		{7}, {8}, {9}, {10}, {11}, {12}, {14}, {15}, {16}, {17}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery115)/sizeof(expectedResultparentStarsubquery115[0])), actualResultparentStarsubquery115->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery115)/sizeof(expectedResultparentStarsubquery115[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery115[i])/sizeof(expectedResultparentStarsubquery115[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery115[i][j], actualResultparentStarsubquery115->getResultAt(i, j));
		}
	}

	// Test 117: ParentStar(_, _)
	ParentStarSubquery parentStarsubquery117 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery117.setSynonyms("_", "_");
	ResultTuple* actualResultparentStarsubquery117 = parentStarsubquery117.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentStarsubquery117->getAllResults().size());
	CPPUNIT_ASSERT(actualResultparentStarsubquery117->isBool());
	CPPUNIT_ASSERT(!actualResultparentStarsubquery117->isEmpty());

	// Test 118: ParentStar(_, 2)
	ParentStarSubquery parentStarsubquery118 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery118.setSynonyms("_", 2);
	ResultTuple* actualResultparentStarsubquery118 = parentStarsubquery118.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentStarsubquery118->getAllResults().size());
	CPPUNIT_ASSERT(actualResultparentStarsubquery118->isBool());
	CPPUNIT_ASSERT(actualResultparentStarsubquery118->isEmpty());

	// Test 119: ParentStar(_, 7)
	ParentStarSubquery parentStarsubquery119 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery119.setSynonyms("_", 7);
	ResultTuple* actualResultparentStarsubquery119 = parentStarsubquery119.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentStarsubquery119->getAllResults().size());
	CPPUNIT_ASSERT(actualResultparentStarsubquery119->isBool());
	CPPUNIT_ASSERT(!actualResultparentStarsubquery119->isEmpty());

	// Test 120: ParentStar(15, s2)
	ParentStarSubquery parentStarsubquery120 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery120.setSynonyms(15, "s2");
	ResultTuple* actualResultparentStarsubquery120 = parentStarsubquery120.solve();
	int expectedResultparentStarsubquery120[1][1] = {
		{16}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery120)/sizeof(expectedResultparentStarsubquery120[0])), actualResultparentStarsubquery120->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery120)/sizeof(expectedResultparentStarsubquery120[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery120[i])/sizeof(expectedResultparentStarsubquery120[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery120[i][j], actualResultparentStarsubquery120->getResultAt(i, j));
		}
	}

	// Test 121: ParentStar(15, a2)
	ParentStarSubquery parentStarsubquery121 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery121.setSynonyms(15, "a2");
	ResultTuple* actualResultparentStarsubquery121 = parentStarsubquery121.solve();
	int expectedResultparentStarsubquery121[1][1] = {
		{16}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery121)/sizeof(expectedResultparentStarsubquery121[0])), actualResultparentStarsubquery121->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery121)/sizeof(expectedResultparentStarsubquery121[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery121[i])/sizeof(expectedResultparentStarsubquery121[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery121[i][j], actualResultparentStarsubquery121->getResultAt(i, j));
		}
	}

	// Test 122: ParentStar(1, w2)
	ParentStarSubquery parentStarsubquery122 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery122.setSynonyms(1, "w2");
	ResultTuple* actualResultparentStarsubquery122 = parentStarsubquery122.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentStarsubquery122->getAllResults().size());

	// Test 123: ParentStar(1, i2)
	ParentStarSubquery parentStarsubquery123 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery123.setSynonyms(1, "i2");
	ResultTuple* actualResultparentStarsubquery123 = parentStarsubquery123.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentStarsubquery123->getAllResults().size());

	// Test 126: ParentStar(1, c2)
	ParentStarSubquery parentStarsubquery126 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery126.setSynonyms(1, "c2");
	ResultTuple* actualResultparentStarsubquery126 = parentStarsubquery126.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentStarsubquery126->getAllResults().size());

	// Test 127: ParentStar(15, l2)
	ParentStarSubquery parentStarsubquery127 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery127.setSynonyms(15, "l2");
	ResultTuple* actualResultparentStarsubquery127 = parentStarsubquery127.solve();
	int expectedResultparentStarsubquery127[1][1] = {
		{16}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery127)/sizeof(expectedResultparentStarsubquery127[0])), actualResultparentStarsubquery127->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery127)/sizeof(expectedResultparentStarsubquery127[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery127[i])/sizeof(expectedResultparentStarsubquery127[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery127[i][j], actualResultparentStarsubquery127->getResultAt(i, j));
		}
	}

	// Test 129: ParentStar(1, _)
	ParentStarSubquery parentStarsubquery129 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery129.setSynonyms(1, "_");
	ResultTuple* actualResultparentStarsubquery129 = parentStarsubquery129.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentStarsubquery129->getAllResults().size());
	CPPUNIT_ASSERT(actualResultparentStarsubquery129->isBool());
	CPPUNIT_ASSERT(actualResultparentStarsubquery129->isEmpty());

	// Test 130: ParentStar(1, 2)
	ParentStarSubquery parentStarsubquery130 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery130.setSynonyms(1, 2);
	ResultTuple* actualResultparentStarsubquery130 = parentStarsubquery130.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentStarsubquery130->getAllResults().size());
	CPPUNIT_ASSERT(actualResultparentStarsubquery130->isBool());
	CPPUNIT_ASSERT(actualResultparentStarsubquery130->isEmpty());

	// Test 131: ParentStar(1, 6)
	ParentStarSubquery parentStarsubquery131 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery131.setSynonyms(1, 6);
	ResultTuple* actualResultparentStarsubquery131 = parentStarsubquery131.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentStarsubquery131->getAllResults().size());
	CPPUNIT_ASSERT(actualResultparentStarsubquery131->isBool());
	CPPUNIT_ASSERT(actualResultparentStarsubquery131->isEmpty());

	// Test 132: ParentStar(8, s2)
	ParentStarSubquery parentStarsubquery132 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery132.setSynonyms(8, "s2");
	ResultTuple* actualResultparentStarsubquery132 = parentStarsubquery132.solve();
	int expectedResultparentStarsubquery132[2][1] = {
		{9}, {10}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery132)/sizeof(expectedResultparentStarsubquery132[0])), actualResultparentStarsubquery132->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery132)/sizeof(expectedResultparentStarsubquery132[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery132[i])/sizeof(expectedResultparentStarsubquery132[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery132[i][j], actualResultparentStarsubquery132->getResultAt(i, j));
		}
	}

	// Test 133: ParentStar(5, a2)
	ParentStarSubquery parentStarsubquery133 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery133.setSynonyms(5, "a2");
	ResultTuple* actualResultparentStarsubquery133 = parentStarsubquery133.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentStarsubquery133->getAllResults().size());

	// Test 134: ParentStar(13, w2)
	ParentStarSubquery parentStarsubquery134 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery134.setSynonyms(13, "w2");
	ResultTuple* actualResultparentStarsubquery134 = parentStarsubquery134.solve();
	int expectedResultparentStarsubquery134[1][1] = {
		{15}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery134)/sizeof(expectedResultparentStarsubquery134[0])), actualResultparentStarsubquery134->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery134)/sizeof(expectedResultparentStarsubquery134[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery134[i])/sizeof(expectedResultparentStarsubquery134[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery134[i][j], actualResultparentStarsubquery134->getResultAt(i, j));
		}
	}

	// Test 135: ParentStar(6, i2)
	ParentStarSubquery parentStarsubquery135 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery135.setSynonyms(6, "i2");
	ResultTuple* actualResultparentStarsubquery135 = parentStarsubquery135.solve();
	int expectedResultparentStarsubquery135[1][1] = {
		{8}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery135)/sizeof(expectedResultparentStarsubquery135[0])), actualResultparentStarsubquery135->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery135)/sizeof(expectedResultparentStarsubquery135[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery135[i])/sizeof(expectedResultparentStarsubquery135[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery135[i][j], actualResultparentStarsubquery135->getResultAt(i, j));
		}
	}

	// Test 138: ParentStar(6, c2)
	ParentStarSubquery parentStarsubquery138 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery138.setSynonyms(6, "c2");
	ResultTuple* actualResultparentStarsubquery138 = parentStarsubquery138.solve();
	int expectedResultparentStarsubquery138[1][1] = {
		{11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery138)/sizeof(expectedResultparentStarsubquery138[0])), actualResultparentStarsubquery138->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery138)/sizeof(expectedResultparentStarsubquery138[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery138[i])/sizeof(expectedResultparentStarsubquery138[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery138[i][j], actualResultparentStarsubquery138->getResultAt(i, j));
		}
	}

	// Test 139: ParentStar(15, l2)
	ParentStarSubquery parentStarsubquery139 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery139.setSynonyms(15, "l2");
	ResultTuple* actualResultparentStarsubquery139 = parentStarsubquery139.solve();
	int expectedResultparentStarsubquery139[1][1] = {
		{16}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultparentStarsubquery139)/sizeof(expectedResultparentStarsubquery139[0])), actualResultparentStarsubquery139->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultparentStarsubquery139)/sizeof(expectedResultparentStarsubquery139[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultparentStarsubquery139[i])/sizeof(expectedResultparentStarsubquery139[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultparentStarsubquery139[i][j], actualResultparentStarsubquery139->getResultAt(i, j));
		}
	}

	// Test 141: ParentStar(5, _)
	ParentStarSubquery parentStarsubquery141 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery141.setSynonyms(5, "_");
	ResultTuple* actualResultparentStarsubquery141 = parentStarsubquery141.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentStarsubquery141->getAllResults().size());
	CPPUNIT_ASSERT(actualResultparentStarsubquery141->isBool());
	CPPUNIT_ASSERT(actualResultparentStarsubquery141->isEmpty());

	// Test 142: ParentStar(5, 2)
	ParentStarSubquery parentStarsubquery142 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery142.setSynonyms(5, 2);
	ResultTuple* actualResultparentStarsubquery142 = parentStarsubquery142.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentStarsubquery142->getAllResults().size());
	CPPUNIT_ASSERT(actualResultparentStarsubquery142->isBool());
	CPPUNIT_ASSERT(actualResultparentStarsubquery142->isEmpty());

	// Test 143: ParentStar(5, 6)
	ParentStarSubquery parentStarsubquery143 = ParentStarSubquery(&synonymTable, pk);
	parentStarsubquery143.setSynonyms(5, 6);
	ResultTuple* actualResultparentStarsubquery143 = parentStarsubquery143.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultparentStarsubquery143->getAllResults().size());
	CPPUNIT_ASSERT(actualResultparentStarsubquery143->isBool());
	CPPUNIT_ASSERT(actualResultparentStarsubquery143->isEmpty());
}

void SubqueryTest::testParentTTuple(){
	// testTuple:
	//  s1  |  a1  |  w1  |  i2  |  c2  |  l1  |  const1  |  v1  |  proc1  |
	//  2   |  1   |  6   |  8   |  3   |  1   |  0       |  0   |  0      |
	//  6   |  2   |  6   |  8   |  3   |  1   |  0       |  0   |  0      |
	//  6   |  1   |  15  |  8   |  3   |  1   |  0       |  0   |  0      |
	//  8   |  2   |  6   |  13  |  3   |  1   |  0       |  0   |  0      |
	//  8   |  1   |  6   |  8   |  11  |  1   |  0       |  0   |  0      |
	//  13  |  2   |  6   |  8   |  3   |  7   |  0       |  0   |  0      |
	//  12  |  1   |  6   |  8   |  3   |  1   |  3       |  0   |  0      |
	//  15  |  2   |  6   |  8   |  3   |  1   |  0       |  2   |  0      |
	//  15  |  2   |  6   |  8   |  3   |  1   |  0       |  2   |  1      |
	ResultTuple testTuple = ResultTuple();
	int index = testTuple.addSynonym("s1");
	testTuple.addSynonymToMap("s1", index);
	index = testTuple.addSynonym("a1");
	testTuple.addSynonymToMap("a1", index);
	index = testTuple.addSynonym("w1");
	testTuple.addSynonymToMap("w1", index);
	index = testTuple.addSynonym("i2");
	testTuple.addSynonymToMap("i2", index);
	index = testTuple.addSynonym("c2");
	testTuple.addSynonymToMap("c2", index);
	index = testTuple.addSynonym("l1");
	testTuple.addSynonymToMap("l1", index);
	index = testTuple.addSynonym("const1");
	testTuple.addSynonymToMap("const1", index);
	index = testTuple.addSynonym("v1");
	testTuple.addSynonymToMap("v1", index);
	index = testTuple.addSynonym("proc1");
	testTuple.addSynonymToMap("proc1", index);
	int data[9][9] = {
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{12   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	for (int i = 0; i < 9; i++){
		vector<int> tempVector = vector<int>();
		testTuple.addResultRow(tempVector);
		for (int j = 0; j < 9; j++){
			testTuple.addResult(i, data[i][j]);
		}
	}

	// Test 0: ParentStar(s1, s2)
	ParentStarSubquery ParentStarsubquery0 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery0.setSynonyms("s1", "s2");
	ResultTuple* actualResultParentStarsubquery0 = ParentStarsubquery0.solve(&testTuple);
	int expectedResultParentStarsubquery0[22][10] = {
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  7  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  8  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  9  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  10  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  11  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  12  },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  7  },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  8  },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  9  },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  10 },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  11 },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  12 },
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  9  },
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  10  },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  9  },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  10  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  14  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  15  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  16  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  17  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  16  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  16  }
	};	
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultParentStarsubquery0)/sizeof(expectedResultParentStarsubquery0[0])), actualResultParentStarsubquery0->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultParentStarsubquery0)/sizeof(expectedResultParentStarsubquery0[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultParentStarsubquery0[i])/sizeof(expectedResultParentStarsubquery0[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultParentStarsubquery0[i][j], actualResultParentStarsubquery0->getResultAt(i, j));
		}
	}

	// Test 1: ParentStar(s1, a2)
	ParentStarSubquery ParentStarsubquery1 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery1.setSynonyms("s1", "a2");
	ResultTuple* actualResultParentStarsubquery1 = ParentStarsubquery1.solve(&testTuple);
	int expectedResultParentStarsubquery1[17][10] = {
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  7  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  9  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  10  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  12  },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  7  },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  9  },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  10 },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  12 },
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  9  },
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  10  },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  9  },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  10  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  14  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  16  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  17  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  16  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  16  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultParentStarsubquery1)/sizeof(expectedResultParentStarsubquery1[0])), actualResultParentStarsubquery1->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultParentStarsubquery1)/sizeof(expectedResultParentStarsubquery1[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultParentStarsubquery1[i])/sizeof(expectedResultParentStarsubquery1[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultParentStarsubquery1[i][j], actualResultParentStarsubquery1->getResultAt(i, j));
		}
	}

	// Test 2: ParentStar(s1, w2)
	ParentStarSubquery ParentStarsubquery2 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery2.setSynonyms("s1", "w2");
	ResultTuple* actualResultParentStarsubquery2 = ParentStarsubquery2.solve(&testTuple);
	int expectedResultParentStarsubquery2[1][10] = {
		
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   , 0,   15  },

	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultParentStarsubquery2)/sizeof(expectedResultParentStarsubquery2[0])), actualResultParentStarsubquery2->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultParentStarsubquery2)/sizeof(expectedResultParentStarsubquery2[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultParentStarsubquery2[i])/sizeof(expectedResultParentStarsubquery2[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultParentStarsubquery2[i][j], actualResultParentStarsubquery2->getResultAt(i, j));
		}
	}

	// Test 3: ParentStar(s1, i2)
	ParentStarSubquery ParentStarsubquery3 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery3.setSynonyms("s1", "i2");
	ResultTuple* actualResultParentStarsubquery3 = ParentStarsubquery3.solve(&testTuple);
	int expectedResultParentStarsubquery3[2][9] = {
		
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0 },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0 }
		
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultParentStarsubquery3)/sizeof(expectedResultParentStarsubquery3[0])), actualResultParentStarsubquery3->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultParentStarsubquery3)/sizeof(expectedResultParentStarsubquery3[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultParentStarsubquery3[i])/sizeof(expectedResultParentStarsubquery3[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultParentStarsubquery3[i][j], actualResultParentStarsubquery3->getResultAt(i, j));
		}
	}

	// Test 6: ParentStar(s1, c2)
	ParentStarSubquery ParentStarsubquery6 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery6.setSynonyms("s1", "c2");
	ResultTuple* actualResultParentStarsubquery6 = ParentStarsubquery6.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentStarsubquery6->getAllResults().size());

	// Test 7: ParentStar(s1, l2)
	ParentStarSubquery ParentStarsubquery7 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery7.setSynonyms("s1", "l2");
	ResultTuple* actualResultParentStarsubquery7 = ParentStarsubquery7.solve(&testTuple);
	int expectedResultParentStarsubquery7[22][10] = {
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  7  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  8  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  9  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  10  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  11  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  12  },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  7  },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  8  },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  9  },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  10 },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  11 },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  12 },
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  9  },
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  10  },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  9  },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  10  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  14  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  15  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  16  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  17  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  16  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  16  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultParentStarsubquery7)/sizeof(expectedResultParentStarsubquery7[0])), actualResultParentStarsubquery7->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultParentStarsubquery7)/sizeof(expectedResultParentStarsubquery7[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultParentStarsubquery7[i])/sizeof(expectedResultParentStarsubquery7[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultParentStarsubquery7[i][j], actualResultParentStarsubquery7->getResultAt(i, j));
		}
	}

	// Test 9: ParentStar(s1, _)
	ParentStarSubquery ParentStarsubquery9 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery9.setSynonyms("s1", "_");
	ResultTuple* actualResultParentStarsubquery9 = ParentStarsubquery9.solve(&testTuple);
	int expectedResultParentStarsubquery9[7][9] = {
		
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0 },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1 },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2 }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultParentStarsubquery9)/sizeof(expectedResultParentStarsubquery9[0])), actualResultParentStarsubquery9->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultParentStarsubquery9)/sizeof(expectedResultParentStarsubquery9[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultParentStarsubquery9[i])/sizeof(expectedResultParentStarsubquery9[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultParentStarsubquery9[i][j], actualResultParentStarsubquery9->getResultAt(i, j));
		}
	}

	// Test 10: ParentStar(s1, 2)
	ParentStarSubquery ParentStarsubquery10 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery10.setSynonyms("s1", 2);
	ResultTuple* actualResultParentStarsubquery10 = ParentStarsubquery10.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentStarsubquery10->getAllResults().size());

	// Test 11: ParentStar(s1, 6)
	ParentStarSubquery ParentStarsubquery11 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery11.setSynonyms("s1", 6);
	ResultTuple* actualResultParentStarsubquery11 = ParentStarsubquery11.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentStarsubquery11->getAllResults().size());


	// Test 24: ParentStar(w1, s2)
	ParentStarSubquery ParentStarsubquery24 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery24.setSynonyms("w1", "s2");
	ResultTuple* actualResultParentStarsubquery24 = ParentStarsubquery24.solve(&testTuple);
	int expectedResultParentStarsubquery24[49][10] = {
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  7  },
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  8  },
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  9  },
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  10 },
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  11 },
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  12 },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  7  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  8  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  9  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  10 },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  11 },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  12 },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  , 16},
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  7  },
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  8  },
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  9  },
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  10 },
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  11 },
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  12 },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  7  },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  8  },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  9  },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  10 },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  11 },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  12 },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  7  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  8  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  9  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  10 },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  11 },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  12 },
		{12   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  7  },
		{12   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  8  },
		{12   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  9  },
		{12   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  10 },
		{12   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  11 },
		{12   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  12 },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  7  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  8  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  9  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  10 },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  11 },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  12 },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  7  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  8  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  9  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  10 },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  11 },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  12 }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultParentStarsubquery24)/sizeof(expectedResultParentStarsubquery24[0])), actualResultParentStarsubquery24->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultParentStarsubquery24)/sizeof(expectedResultParentStarsubquery24[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultParentStarsubquery24[i])/sizeof(expectedResultParentStarsubquery24[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultParentStarsubquery24[i][j], actualResultParentStarsubquery24->getResultAt(i, j));
		}
	}

	// Test 25: ParentStar(w1, a2)
	ParentStarSubquery ParentStarsubquery25 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery25.setSynonyms("w1", "a2");
	ResultTuple* actualResultParentStarsubquery25 = ParentStarsubquery25.solve(&testTuple);
	int expectedResultParentStarsubquery25[33][10] = {
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  7  },
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  9  },
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  10 },
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  12 },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  7  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  9  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  10 },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  12 },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  , 16},
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  7  },
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  9  },
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  10 },
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  12 },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  7  },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  9  },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  10 },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  12 },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  7  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  9  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  10 },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  12 },
		{12   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  7  },
		{12   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  9  },
		{12   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  10 },
		{12   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  12 },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  7  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  9  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  10 },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  12 },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  7  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  9  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  10 },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  12 }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultParentStarsubquery25)/sizeof(expectedResultParentStarsubquery25[0])), actualResultParentStarsubquery25->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultParentStarsubquery25)/sizeof(expectedResultParentStarsubquery25[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultParentStarsubquery25[i])/sizeof(expectedResultParentStarsubquery25[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultParentStarsubquery25[i][j], actualResultParentStarsubquery25->getResultAt(i, j));
		}
	}


	// Test 26: ParentStar(w1, w2)
	ParentStarSubquery ParentStarsubquery26 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery26.setSynonyms("w1", "w2");
	ResultTuple* actualResultParentStarsubquery26 = ParentStarsubquery26.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentStarsubquery26->getAllResults().size());

	// Test 27: ParentStar(w1, i2)
	ParentStarSubquery ParentStarsubquery27 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery27.setSynonyms("w1", "i2");
	ResultTuple* actualResultParentStarsubquery27 = ParentStarsubquery27.solve(&testTuple);
	int expectedResultParentStarsubquery27[7][9] = {
		
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{12   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
		
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultParentStarsubquery27)/sizeof(expectedResultParentStarsubquery27[0])), actualResultParentStarsubquery27->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultParentStarsubquery27)/sizeof(expectedResultParentStarsubquery27[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultParentStarsubquery27[i])/sizeof(expectedResultParentStarsubquery27[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultParentStarsubquery27[i][j], actualResultParentStarsubquery27->getResultAt(i, j));
		}
	}

	// Test 30: ParentStar(w1, c2)
	ParentStarSubquery ParentStarsubquery30 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery30.setSynonyms("w1", "c2");
	ResultTuple* actualResultParentStarsubquery30 = ParentStarsubquery30.solve(&testTuple);
	int expectedResultParentStarsubquery30[1][9] = {

		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
	};

	// Test 31: ParentStar(w1, l2)
	ParentStarSubquery ParentStarsubquery31 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery31.setSynonyms("w1", "l2");
	ResultTuple* actualResultParentStarsubquery31 = ParentStarsubquery31.solve(&testTuple);
	int expectedResultParentStarsubquery31[49][10] = {
	    {2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  7  },
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  8  },
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  9  },
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  10 },
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  11 },
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  12 },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  7  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  8  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  9  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  10 },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  11 },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  12 },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  , 16},
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  7  },
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  8  },
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  9  },
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  10 },
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  11 },
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  12 },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  7  },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  8  },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  9  },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  10 },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  11 },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  12 },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  7  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  8  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  9  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  10 },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  11 },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  12 },
		{12   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  7  },
		{12   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  8  },
		{12   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  9  },
		{12   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  10 },
		{12   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  11 },
		{12   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  12 },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  7  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  8  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  9  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  10 },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  11 },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  12 },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  7  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  8  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  9  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  10 },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  11 },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  ,  12 }
	};

	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultParentStarsubquery31)/sizeof(expectedResultParentStarsubquery31[0])), actualResultParentStarsubquery31->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultParentStarsubquery31)/sizeof(expectedResultParentStarsubquery31[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultParentStarsubquery31[i])/sizeof(expectedResultParentStarsubquery31[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultParentStarsubquery31[i][j], actualResultParentStarsubquery31->getResultAt(i, j));
		}
	}

	// Test 33: ParentStar(w1, _)
	ParentStarSubquery ParentStarsubquery33 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery33.setSynonyms("w1", "_");
	ResultTuple* actualResultParentStarsubquery33 = ParentStarsubquery33.solve(&testTuple);
	int expectedResultParentStarsubquery33[9][9] = {
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{12   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};

	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultParentStarsubquery33)/sizeof(expectedResultParentStarsubquery33[0])), actualResultParentStarsubquery33->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultParentStarsubquery33)/sizeof(expectedResultParentStarsubquery33[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultParentStarsubquery33[i])/sizeof(expectedResultParentStarsubquery33[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultParentStarsubquery33[i][j], actualResultParentStarsubquery33->getResultAt(i, j));
		}
	}

	// Test 34: ParentStar(w1, 2)
	ParentStarSubquery ParentStarsubquery34 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery34.setSynonyms("w1", 2);
	ResultTuple* actualResultParentStarsubquery34 = ParentStarsubquery34.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentStarsubquery34->getAllResults().size());

	// Test 35: ParentStar(w1, 12)
	ParentStarSubquery ParentStarsubquery35 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery35.setSynonyms("w1", 12);
	ResultTuple* actualResultParentStarsubquery35 = ParentStarsubquery35.solve(&testTuple);
	int expectedResultParentStarsubquery35[8][9] = {
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{12   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultParentStarsubquery35)/sizeof(expectedResultParentStarsubquery35[0])), actualResultParentStarsubquery35->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultParentStarsubquery35)/sizeof(expectedResultParentStarsubquery35[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultParentStarsubquery35[i])/sizeof(expectedResultParentStarsubquery35[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultParentStarsubquery35[i][j], actualResultParentStarsubquery35->getResultAt(i, j));
		}
	}


	// Test 39: ParentStar(i1, i2)
	ParentStarSubquery ParentStarsubquery39 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery39.setSynonyms("i1", "i2");
	ResultTuple* actualResultParentStarsubquery39 = ParentStarsubquery39.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentStarsubquery39->getAllResults().size());

	// Test 42: ParentStar(i1, c2)
	ParentStarSubquery ParentStarsubquery42 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery42.setSynonyms("i1", "c2");
	ResultTuple* actualResultParentStarsubquery42 = ParentStarsubquery42.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentStarsubquery42->getAllResults().size());

	// Test 75: ParentStar(c1, i2)
	ParentStarSubquery ParentStarsubquery75 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery75.setSynonyms("c1", "i2");
	ResultTuple* actualResultParentStarsubquery75 = ParentStarsubquery75.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentStarsubquery75->getAllResults().size());

	// Test 78: ParentStar(c1, c2)
	ParentStarSubquery ParentStarsubquery78 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery78.setSynonyms("c1", "c2");
	ResultTuple* actualResultParentStarsubquery78 = ParentStarsubquery78.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentStarsubquery78->getAllResults().size());

	// Test 84: ParentStar(l1, s2)
	ParentStarSubquery ParentStarsubquery84 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery84.setSynonyms("l1", "s2");
	ResultTuple* actualResultParentStarsubquery84 = ParentStarsubquery84.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentStarsubquery84->getAllResults().size());


	// Test 85: ParentStar(l1, a2)
	ParentStarSubquery ParentStarsubquery85 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery85.setSynonyms("l1", "a2");
	ResultTuple* actualResultParentStarsubquery85 = ParentStarsubquery85.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentStarsubquery85->getAllResults().size());

	// Test 86: ParentStar(l1, w2)
	ParentStarSubquery ParentStarsubquery86 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery86.setSynonyms("l1", "w2");
	ResultTuple* actualResultParentStarsubquery86 = ParentStarsubquery86.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentStarsubquery86->getAllResults().size());

	// Test 87: ParentStar(l1, i2)
	ParentStarSubquery ParentStarsubquery87 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery87.setSynonyms("l1", "i2");
	ResultTuple* actualResultParentStarsubquery87 = ParentStarsubquery87.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentStarsubquery87->getAllResults().size());

	// Test 90: ParentStar(l1, c2)
	ParentStarSubquery ParentStarsubquery90 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery90.setSynonyms("l1", "c2");
	ResultTuple* actualResultParentStarsubquery90 = ParentStarsubquery90.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentStarsubquery90->getAllResults().size());

	// Test 91: ParentStar(l1, l2)
	ParentStarSubquery ParentStarsubquery91 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery91.setSynonyms("l1", "l2");
	ResultTuple* actualResultParentStarsubquery91 = ParentStarsubquery91.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentStarsubquery91->getAllResults().size());

	// Test 93: ParentStar(l1, _)
	ParentStarSubquery ParentStarsubquery93 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery93.setSynonyms("l1", "_");
	ResultTuple* actualResultParentStarsubquery93 = ParentStarsubquery93.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentStarsubquery93->getAllResults().size());

	// Test 94: ParentStar(l1, 2)
	ParentStarSubquery ParentStarsubquery94 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery94.setSynonyms("l1", 2);
	ResultTuple* actualResultParentStarsubquery94 = ParentStarsubquery94.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentStarsubquery94->getAllResults().size());

	// Test 95: ParentStar(l1, 6)
	ParentStarSubquery ParentStarsubquery95 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery95.setSynonyms("l1", 6);
	ResultTuple* actualResultParentStarsubquery95 = ParentStarsubquery95.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentStarsubquery95->getAllResults().size());

	// Test 111: ParentStar(_, i2)
	ParentStarSubquery ParentStarsubquery111 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery111.setSynonyms("_", "i2");
	ResultTuple* actualResultParentStarsubquery111 = ParentStarsubquery111.solve(&testTuple);
	int expectedResultParentStarsubquery111[8][9] = {
		{2   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{6   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{6   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{13   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{12   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{15   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultParentStarsubquery111)/sizeof(expectedResultParentStarsubquery111[0])), actualResultParentStarsubquery111->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultParentStarsubquery111)/sizeof(expectedResultParentStarsubquery111[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultParentStarsubquery111[i])/sizeof(expectedResultParentStarsubquery111[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultParentStarsubquery111[i][j], actualResultParentStarsubquery111->getResultAt(i, j));
		}
	}

	// Test 114: ParentStar(_, c2)
	ParentStarSubquery ParentStarsubquery114 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery114.setSynonyms("_", "c2");
	ResultTuple* actualResultParentStarsubquery114 = ParentStarsubquery114.solve(&testTuple);
	int expectedResultParentStarsubquery114[1][9] = {
	
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },

	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultParentStarsubquery114)/sizeof(expectedResultParentStarsubquery114[0])), actualResultParentStarsubquery114->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultParentStarsubquery114)/sizeof(expectedResultParentStarsubquery114[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultParentStarsubquery114[i])/sizeof(expectedResultParentStarsubquery114[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultParentStarsubquery114[i][j], actualResultParentStarsubquery114->getResultAt(i, j));
		}
	}

	// Test 123: ParentStar(1, i2)
	ParentStarSubquery ParentStarsubquery123 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery123.setSynonyms(1, "i2");
	ResultTuple* actualResultParentStarsubquery123 = ParentStarsubquery123.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentStarsubquery123->getAllResults().size());

	// Test 126: ParentStar(1, c2)
	ParentStarSubquery ParentStarsubquery126 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery126.setSynonyms(1, "c2");
	ResultTuple* actualResultParentStarsubquery126 = ParentStarsubquery126.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentStarsubquery126->getAllResults().size());

	// Test 135: ParentStar(7, i2)
	ParentStarSubquery ParentStarsubquery135 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery135.setSynonyms(7, "i2");
	ResultTuple* actualResultParentStarsubquery135 = ParentStarsubquery135.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultParentStarsubquery135->getAllResults().size());

	// Test 138: ParentStar(6, c2)
	ParentStarSubquery ParentStarsubquery138 = ParentStarSubquery(&synonymTable, pk);
	ParentStarsubquery138.setSynonyms(6, "c2");
	ResultTuple* actualResultParentStarsubquery138 = ParentStarsubquery138.solve(&testTuple);
	int expectedResultParentStarsubquery138[1][9] = {
		{8   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultParentStarsubquery138)/sizeof(expectedResultParentStarsubquery138[0])), actualResultParentStarsubquery138->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultParentStarsubquery138)/sizeof(expectedResultParentStarsubquery138[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultParentStarsubquery138[i])/sizeof(expectedResultParentStarsubquery138[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultParentStarsubquery138[i][j], actualResultParentStarsubquery138->getResultAt(i, j));
		}
	}
}

void SubqueryTest::testModifies(){
	// Test 1: Modifies(s1, x)
	ModifiesSubquery ms1 = ModifiesSubquery(&synonymTable, pk);
	ms1.setSynonyms("s1", 0);
	ResultTuple* actualResultsModifiesSubquery1 = ms1.solve();
	int expectedResultsModifiesSubquery1[8][1] = {
		{1}, {3}, {4}, {6}, {7}, {13}, {14}, {20}
	};
	for (size_t i = 0; i < 8; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsModifiesSubquery1[i][j], actualResultsModifiesSubquery1->getResultAt(i, j));
		}
	}

	// Test 1.2: Modifies(s1, _)
	ModifiesSubquery ms1_2 = ModifiesSubquery(&synonymTable, pk);
	ms1_2.setSynonyms("s1", "_");
	ResultTuple* actualResultsModifiesSubquery1_2 = ms1_2.solve();
	int expectedResultsModifiesSubquery1_2[22][1] = {
		{1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}, {13}, {14}, {15}, {16}, {17}, {18}, {19}, {20}, {21}, {22}
	};
	for (size_t i = 0; i < 22; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsModifiesSubquery1_2[i][j], actualResultsModifiesSubquery1_2->getResultAt(i, j));
		}
	}

	// Test 1.3: Modifies(s1, v1)
	ModifiesSubquery ms1_3 = ModifiesSubquery(&synonymTable, pk);
	ms1_3.setSynonyms("s1", "v1");
	ResultTuple* actualResultsModifiesSubquery1_3 = ms1_3.solve();
	int expectedResultsModifiesSubquery1_3[37][2] = {
		{1, 0}, {2, 1}, {3, 0}, {3, 2}, {3, 4}, {3, 5}, {3, 1}, {3, 3}, {3, 7},
		{4, 0}, {5, 2}, {6, 0}, {6, 4}, {6, 5}, {6, 1}, {6, 7}, {6, 2},
		{7, 0}, {8, 4}, {8, 5}, {9, 4}, {10, 5}, {11, 1}, {11, 7}, {12, 2}, 
		{13, 0}, {13, 4}, {13, 1}, {14, 0}, {15, 4}, {16, 4}, {17, 1}, {18, 1}, 
		{19, 3}, {20, 0}, {21, 1}, {22, 7}
	};
	for (size_t i = 0; i < 37; i++){
		for (size_t j = 0; j < 2; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsModifiesSubquery1_3[i][j], actualResultsModifiesSubquery1_3->getResultAt(i, j));
		}
	}

	// Test 2: Modifies(a1, x)
	ModifiesSubquery ms2 = ModifiesSubquery(&synonymTable, pk);
	ms2.setSynonyms("a1", 0);
	ResultTuple* actualResultsModifiesSubquery2 = ms2.solve();
	int expectedResultsModifiesSubquery2[5][1] = {
		{1}, {4}, {7}, {14}, {20}
	};
	for (size_t i = 0; i < 5; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsModifiesSubquery2[i][j], actualResultsModifiesSubquery2->getResultAt(i, j));
		}
	}
	// Test 2.2: Modifies(a1, _)
	ModifiesSubquery ms2_2 = ModifiesSubquery(&synonymTable, pk);
	ms2_2.setSynonyms("a1", "_");
	ResultTuple* actualResultsModifiesSubquery2_2 = ms2_2.solve();
	int expectedResultsModifiesSubquery2_2[16][1] = {
		{1}, {2}, {4}, {5}, {7}, {9}, {10}, {12}, {14}, {16}, {17}, {18}, {19}, {20}, {21}, {22}
	};
	for (size_t i = 0; i < 16; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsModifiesSubquery2_2[i][j], actualResultsModifiesSubquery2_2->getResultAt(i, j));
		}
	}
	// Test 2.3: Modifies(a1, v1)
	ModifiesSubquery ms2_3 = ModifiesSubquery(&synonymTable, pk);
	ms2_3.setSynonyms("a1", "v1");
	ResultTuple* actualResultsModifiesSubquery2_3 = ms2_3.solve();
	int expectedResultsModifiesSubquery2_3[16][2] = {
		{1,0},{2,1},{4,0},{5,2},{7,0},{9,4},{10,5},{12,2},
		{14,0},{16,4},{17,1},{18,1},{19,3},{20,0},{21,1},{22,7}
	};
	for (size_t i = 0; i < 16; i++){
		for (size_t j = 0; j < 2; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsModifiesSubquery2_3[i][j], actualResultsModifiesSubquery2_3->getResultAt(i, j));
		}
	}

	// Test 3: Modifies(c1, x)
	ModifiesSubquery ms3 = ModifiesSubquery(&synonymTable, pk);
	ms3.setSynonyms("c1", 0);
	ResultTuple* actualResultsModifiesSubquery3 = ms3.solve();
	int expectedResultsModifiesSubquery3[1][1] = {
		{3}
	};
	for (size_t i = 0; i < 1; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsModifiesSubquery3[i][j], actualResultsModifiesSubquery3->getResultAt(i, j));
		}
	}
	// Test 3.2: Modifies(c1, _)
	ModifiesSubquery ms3_2 = ModifiesSubquery(&synonymTable, pk);
	ms3_2.setSynonyms("c1", "_");
	ResultTuple* actualResultsModifiesSubquery3_2 = ms3_2.solve();
	int expectedResultsModifiesSubquery3_2[2][1] = {
		{3}, {11}	
	};
	for (size_t i = 0; i < 2; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsModifiesSubquery3_2[i][j], actualResultsModifiesSubquery3_2->getResultAt(i, j));
		}
	}

	// Test 3.3: Modifies(c1, v1)
	ModifiesSubquery ms3_3 = ModifiesSubquery(&synonymTable, pk);
	ms3_3.setSynonyms("c1", "v1");
	ResultTuple* actualResultsModifiesSubquery3_3 = ms3_3.solve();
	int expectedResultsModifiesSubquery3_3[9][2] = {
		{3, 0}, {3, 2}, {3, 4}, {3, 5}, {3, 1}, {3, 3}, {3, 7},{11, 1}, {11, 7}
	};
	for (size_t i = 0; i < 9; i++){
		for (size_t j = 0; j < 2; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsModifiesSubquery3_3[i][j], actualResultsModifiesSubquery3_3->getResultAt(i, j));
		}
	}

	// Test 4: Modifies(i1, x)
	ModifiesSubquery ms4 = ModifiesSubquery(&synonymTable, pk);
	ms4.setSynonyms("i1", 0);
	ResultTuple* actualResultsModifiesSubquery4 = ms4.solve();
	int expectedResultsModifiesSubquery4[1][1] = {
		{13}
	};
	for (size_t i = 0; i < 1; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsModifiesSubquery4[i][j], actualResultsModifiesSubquery4->getResultAt(i, j));
		}
	}
	// Test 4.2: Modifies(i1, _)
	ModifiesSubquery ms4_2 = ModifiesSubquery(&synonymTable, pk);
	ms4_2.setSynonyms("i1", "_");
	ResultTuple* actualResultsModifiesSubquery4_2 = ms4_2.solve();
	int expectedResultsModifiesSubquery4_2[2][1] = {
		{8}, {13}	
	};
	for (size_t i = 0; i < 2; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsModifiesSubquery4_2[i][j], actualResultsModifiesSubquery4_2->getResultAt(i, j));
		}
	}
	
	// Test 4.3: Modifies(i1, v1)
	ModifiesSubquery ms4_3 = ModifiesSubquery(&synonymTable, pk);
	ms4_3.setSynonyms("i1", "v1");
	ResultTuple* actualResultsModifiesSubquery4_3 = ms4_3.solve();
	int expectedResultsModifiesSubquery4_3[5][2] = {
		{8, 4}, {8, 5}, {13, 0}, {13, 4}, {13, 1}
	};
	for (size_t i = 0; i < 5; i++){
		for (size_t j = 0; j < 2; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsModifiesSubquery4_3[i][j], actualResultsModifiesSubquery4_3->getResultAt(i, j));
		}
	}

	// Test 5: Modifies(w1, x)
	ModifiesSubquery ms5 = ModifiesSubquery(&synonymTable, pk);
	ms5.setSynonyms("w1", 0);
	ResultTuple* actualResultsModifiesSubquery5 = ms5.solve();
	int expectedResultsModifiesSubquery5[1][1] = {
		{6}
	};
	for (size_t i = 0; i < 1; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsModifiesSubquery5[i][j], actualResultsModifiesSubquery5->getResultAt(i, j));
		}
	}
	// Test 5.2: Modifies(w1, _)
	ModifiesSubquery ms5_2 = ModifiesSubquery(&synonymTable, pk);
	ms5_2.setSynonyms("w1", "_");
	ResultTuple* actualResultsModifiesSubquery5_2 = ms5_2.solve();
	int expectedResultsModifiesSubquery5_2[2][1] = {
		{6}, {15}	
	};
	for (size_t i = 0; i < 1; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsModifiesSubquery5_2[i][j], actualResultsModifiesSubquery5_2->getResultAt(i, j));
		}
	}

	// Test 5.3: Modifies(w1, v1)
	ModifiesSubquery ms5_3 = ModifiesSubquery(&synonymTable, pk);
	ms5_3.setSynonyms("w1", "v1");
	ResultTuple* actualResultsModifiesSubquery5_3 = ms5_3.solve();
	int expectedResultsModifiesSubquery5_3[7][2] = {
		{6, 0}, {6, 4}, {6, 5}, {6, 1}, {6, 7}, {6, 2},{15, 4}
	};
	for (size_t i = 0; i < 7; i++){
		for (size_t j = 0; j < 2; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsModifiesSubquery5_3[i][j], actualResultsModifiesSubquery5_3->getResultAt(i, j));
		}
	}
}

void SubqueryTest::testModifiesTuple() {
	ResultTuple* rt = new ResultTuple();
	rt->addSynonymToMap("s1", rt->addSynonym("s1"));
	int arr[] = {1, 2, 3, 4, 5};
	for (int i = 0; i < 5; i++) {
		vector<int> temp = vector<int>();
		temp.push_back(arr[i]);
		rt->addResultRow(temp);
	}
	
	// Test 1: Modifies(s1, x)
	ModifiesSubquery ms1 = ModifiesSubquery(&synonymTable, pk);
	ms1.setSynonyms("s1", 0);
	ResultTuple* actualResultsModifiesSubquery1 = ms1.solve(rt);
	int expectedResultsModifiesSubquery1[3][1] = {
		{1}, {3}, {4}
	};
	for (size_t i = 0; i < 3; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsModifiesSubquery1[i][j], actualResultsModifiesSubquery1->getResultAt(i, j));
		}
	}
	// Test 1.2: Modifies(s1, _)
	ModifiesSubquery ms1_2 = ModifiesSubquery(&synonymTable, pk);
	ms1_2.setSynonyms("s1", "_");
	ResultTuple* actualResultsModifiesSubquery1_2 = ms1_2.solve(rt);
	int expectedResultsModifiesSubquery1_2[5][1] = {
		{1}, {2}, {3}, {4}, {5}
	};
	for (size_t i = 0; i < 5; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsModifiesSubquery1_2[i][j], actualResultsModifiesSubquery1_2->getResultAt(i, j));
		}
	}

	rt = new ResultTuple();
	rt->addSynonymToMap("s1", rt->addSynonym("s1"));
	rt->addSynonymToMap("v1", rt->addSynonym("v1"));
	int arr12[17][2] = {{1, 0}, {2, 1}, {3, 0}, {3, 2}, {3, 4},{3, 5}, {3, 1}, {3, 3}, 
	{3, 7},{4, 0}, {5, 2}, {6, 0}, {6, 4}, {6, 5}, {6, 1}, {6, 7}, {6, 2}};
	for (int i = 0; i < 17; i++) {
		vector<int> temp = vector<int>();
		temp.push_back(arr12[i][0]);
		temp.push_back(arr12[i][1]);
		rt->addResultRow(temp);
	}
	// Test 1.3: Modifies(s1, v1)
	ModifiesSubquery ms1_3 = ModifiesSubquery(&synonymTable, pk);
	ms1_3.setSynonyms("s1", "v1");
	ResultTuple* actualResultsModifiesSubquery1_3 = ms1_3.solve(rt);
	int expectedResultsModifiesSubquery1_3[17][2] = {
		{1, 0}, {2, 1}, {3, 0}, {3, 2}, {3, 4}, {3, 5}, {3, 1}, {3, 3}, {3, 7},
		{4, 0}, {5, 2}, {6, 0}, {6, 4}, {6, 5}, {6, 1}, {6, 7}, {6, 2}
	};
	for (size_t i = 0; i < 17; i++){
		for (size_t j = 0; j < 2; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsModifiesSubquery1_3[i][j], actualResultsModifiesSubquery1_3->getResultAt(i, j));
		}
	}

	rt = new ResultTuple();
	rt->addSynonymToMap("s1", rt->addSynonym("s1"));
	rt->addSynonymToMap("v1", rt->addSynonym("v1"));
	int arr13[11][2] = {{1, 0}, {2, 1}, {3, 0}, {3, 2}, {3, 4},{3, 5}, {3, 1}, {3, 3}, 
	{3, 7},{4, 0}, {5, 2}};
	for (int i = 0; i < 11; i++) {
		vector<int> temp = vector<int>();
		temp.push_back(arr13[i][0]);
		temp.push_back(arr13[i][1]);
		rt->addResultRow(temp);
	}
	// Test 1.3: Modifies(s1, v2)
	ModifiesSubquery ms1_31 = ModifiesSubquery(&synonymTable, pk);
	ms1_31.setSynonyms("s1", "v2");
	ResultTuple* actualResultsModifiesSubquery1_31 = ms1_31.solve(rt);
	int expectedResultsModifiesSubquery1_31[53][3] = {
		{1, 0, 0}, {2, 1, 1}, {3, 0, 0}, {3, 0, 1}, {3, 0, 2}, {3, 0, 3}, {3, 0, 4}, {3, 0, 5}, {3, 0, 7}, {3, 2, 0}, {3, 2, 1}, 
		{3, 2, 2}, {3, 2, 3}, {3, 2, 4}, {3, 2, 5}, {3, 2, 7}, {3, 4, 0}, {3, 4, 1}, {3, 4, 2}, {3, 4, 3}, {3, 4, 4}, {3, 4, 5}, 
		{3, 4, 7}, {3, 5, 0}, {3, 5, 1}, {3, 5, 2}, {3, 5, 3}, {3, 5, 4}, {3, 5, 5}, {3, 5, 7}, {3, 1, 0}, {3, 1, 1}, {3, 1, 2}, 
		{3, 1, 3}, {3, 1, 4}, {3, 1, 5}, {3, 1, 7}, {3, 3, 0}, {3, 3, 1}, {3, 3, 2}, {3, 3, 3}, {3, 3, 4}, {3, 3, 5}, {3, 3, 7}, 
		{3, 7, 0}, {3, 7, 1}, {3, 7, 2}, {3, 7, 3}, {3, 7, 4}, {3, 7, 5}, {3, 7, 7}, {4, 0, 0}, {5, 2, 2}, 
	};
	for (size_t i = 0; i < 53; i++){
		for (size_t j = 0; j < 3; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsModifiesSubquery1_31[i][j], actualResultsModifiesSubquery1_31->getResultAt(i, j));
		}
	}
	
	rt = new ResultTuple();
	rt->addSynonymToMap("v1", rt->addSynonym("v1"));
	int arr123[3] = {0, 1, 2};
	for (int i = 0; i < 3; i++) {
		vector<int> temp = vector<int>();
		temp.push_back(arr123[i]);
		rt->addResultRow(temp);
	}
	// Test 1.3: Modifies(s1, v1)
	ModifiesSubquery ms1_3x = ModifiesSubquery(&synonymTable, pk);
	ms1_3x.setSynonyms("s1", "v1");
	ResultTuple* actualResultsModifiesSubquery1_3x = ms1_3.solve(rt);
	int expectedResultsModifiesSubquery1_3x[20][2] = {
		{0, 1}, {0, 3}, {0, 4}, {0, 6}, {0, 7},{0, 13}, {0, 14}, {0, 20},
		{1, 2}, {1, 3}, {1, 6}, {1, 11}, {1, 13}, {1, 17}, {1, 18}, {1, 21},
		{2, 3}, {2, 5}, {2, 6}, {2, 12}
	};
	for (size_t i = 0; i < 20; i++){
		for (size_t j = 0; j < 2; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsModifiesSubquery1_3x[i][j], actualResultsModifiesSubquery1_3x->getResultAt(i, j));
		}
	}

	ResultTuple* rt2 = new ResultTuple();
	rt2->addSynonymToMap("a1", rt2->addSynonym("a1"));
	int arr2[] = {1, 2, 4, 5};
	for (int i = 0; i < 4; i++) {
		vector<int> temp = vector<int>();
		temp.push_back(arr2[i]);
		rt2->addResultRow(temp);
	}
	// Test 2: Modifies(a1, x)
	ModifiesSubquery ms2 = ModifiesSubquery(&synonymTable, pk);
	ms2.setSynonyms("a1", 0);
	ResultTuple* actualResultsModifiesSubquery2 = ms2.solve(rt2);
	int expectedResultsModifiesSubquery2[2][1] = {
		{1}, {4}
	};
	for (size_t i = 0; i < 2; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsModifiesSubquery2[i][j], actualResultsModifiesSubquery2->getResultAt(i, j));
		}
	}
	// Test 2.2: Modifies(a1, _)
	ModifiesSubquery ms2_2 = ModifiesSubquery(&synonymTable, pk);
	ms2_2.setSynonyms("a1", "_");
	ResultTuple* actualResultsModifiesSubquery2_2 = ms2_2.solve(rt2);
	int expectedResultsModifiesSubquery2_2[4][1] = {
		{1}, {2}, {4}, {5}
	};
	for (size_t i = 0; i < 4; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsModifiesSubquery2_2[i][j], actualResultsModifiesSubquery2_2->getResultAt(i, j));
		}
	}

	ResultTuple* rt3 = new ResultTuple();
	rt3->addSynonymToMap("c1", rt3->addSynonym("c1"));
	int arr3[] = {3};
	for (int i = 0; i < 2; i++) {
		vector<int> temp = vector<int>();
		temp.push_back(arr3[i]);
		rt3->addResultRow(temp);
	}
	// Test 3: Modifies(c1, x)
	ModifiesSubquery ms3 = ModifiesSubquery(&synonymTable, pk);
	ms3.setSynonyms("c1", 0);
	ResultTuple* actualResultsModifiesSubquery3 = ms3.solve(rt3);
	int expectedResultsModifiesSubquery3[1][1] = {{3}};
	for (size_t i = 0; i < 1; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsModifiesSubquery3[i][j], actualResultsModifiesSubquery3->getResultAt(i, j));
		}
	}
	// Test 3.2: Modifies(c1, _)
	ModifiesSubquery ms3_2 = ModifiesSubquery(&synonymTable, pk);
	ms3_2.setSynonyms("c1", "_");
	ResultTuple* actualResultsModifiesSubquery3_2 = ms3_2.solve(rt3);
	int expectedResultsModifiesSubquery3_2[1][1] = {{3}};
	for (size_t i = 0; i < 1; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsModifiesSubquery3_2[i][j], actualResultsModifiesSubquery3_2->getResultAt(i, j));
		}
	}

	ResultTuple* rt4 = new ResultTuple();
	rt4->addSynonymToMap("i1", rt4->addSynonym("i1"));
	int arr4[] = {8};
	for (int i = 0; i < 1; i++) {
		vector<int> temp = vector<int>();
		temp.push_back(arr4[i]);
		rt4->addResultRow(temp);
	}
	// Test 4: Modifies(i1, x)
	ModifiesSubquery ms4 = ModifiesSubquery(&synonymTable, pk);
	ms4.setSynonyms("i1", 0);
	ResultTuple* actualResultsModifiesSubquery4 = ms4.solve(rt4);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultsModifiesSubquery4->getAllResults().size());
	
	// Test 4.2: Modifies(i1, _)
	ModifiesSubquery ms4_2 = ModifiesSubquery(&synonymTable, pk);
	ms4_2.setSynonyms("i1", "_");
	ResultTuple* actualResultsModifiesSubquery4_2 = ms4_2.solve(rt4);
	int expectedResultsModifiesSubquery4_2[1][1] = {
		{8}	
	};
	for (size_t i = 0; i < 1; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsModifiesSubquery4_2[i][j], actualResultsModifiesSubquery4_2->getResultAt(i, j));
		}
	}

	ResultTuple* rt5 = new ResultTuple();
	rt5->addSynonymToMap("w1", rt5->addSynonym("w1"));
	int arr5[] = {6, 15};
	for (int i = 0; i < 2; i++) {
		vector<int> temp = vector<int>();
		temp.push_back(arr5[i]);
		rt5->addResultRow(temp);
	}
	// Test 5: Modifies(w1, x)
	ModifiesSubquery ms5 = ModifiesSubquery(&synonymTable, pk);
	ms5.setSynonyms("w1", 0);
	ResultTuple* actualResultsModifiesSubquery5 = ms5.solve(rt5);
	int expectedResultsModifiesSubquery5[1][1] = {
		{6}
	};
	for (size_t i = 0; i < 1; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsModifiesSubquery5[i][j], actualResultsModifiesSubquery5->getResultAt(i, j));
		}
	}
	// Test 5.2: Modifies(w1, _)
	ModifiesSubquery ms5_2 = ModifiesSubquery(&synonymTable, pk);
	ms5_2.setSynonyms("w1", "_");
	ResultTuple* actualResultsModifiesSubquery5_2 = ms5_2.solve(rt5);
	int expectedResultsModifiesSubquery5_2[2][1] = {
		{6}, {15}	
	};
	for (size_t i = 0; i < 1; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsModifiesSubquery5_2[i][j], actualResultsModifiesSubquery5_2->getResultAt(i, j));
		}
	}
}

void SubqueryTest::testModifiesProc(){
	// Test 64: Modifies(proc1, v2)
	ModifiesProcSubquery modifiesprocsubquery64 = ModifiesProcSubquery(&synonymTable, pk);
	modifiesprocsubquery64.setSynonyms("proc1", "v2");
	ResultTuple* actualResultmodifiesprocsubquery64 = modifiesprocsubquery64.solve();
	int expectedResultmodifiesprocsubquery64[16][2] = {
		{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 7},
		{1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 7},
		{2, 1}, {2, 7}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultmodifiesprocsubquery64)/sizeof(expectedResultmodifiesprocsubquery64[0])), actualResultmodifiesprocsubquery64->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultmodifiesprocsubquery64)/sizeof(expectedResultmodifiesprocsubquery64[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultmodifiesprocsubquery64[i])/sizeof(expectedResultmodifiesprocsubquery64[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultmodifiesprocsubquery64[i][j], actualResultmodifiesprocsubquery64->getResultAt(i, j));
		}
	}

	// Test 69: Modifies(proc1, _)
	ModifiesProcSubquery modifiesprocsubquery69 = ModifiesProcSubquery(&synonymTable, pk);
	modifiesprocsubquery69.setSynonyms("proc1", "_");
	ResultTuple* actualResultmodifiesprocsubquery69 = modifiesprocsubquery69.solve();
	int expectedResultmodifiesprocsubquery69[3][1] = {
		{0}, {1}, {2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultmodifiesprocsubquery69)/sizeof(expectedResultmodifiesprocsubquery69[0])), actualResultmodifiesprocsubquery69->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultmodifiesprocsubquery69)/sizeof(expectedResultmodifiesprocsubquery69[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultmodifiesprocsubquery69[i])/sizeof(expectedResultmodifiesprocsubquery69[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultmodifiesprocsubquery69[i][j], actualResultmodifiesprocsubquery69->getResultAt(i, j));
		}
	}
	
	// Test 70: Modifies(proc1, 2)
	ModifiesProcSubquery modifiesprocsubquery70 = ModifiesProcSubquery(&synonymTable, pk);
	modifiesprocsubquery70.setSynonyms("proc1", 2);
	ResultTuple* actualResultmodifiesprocsubquery70 = modifiesprocsubquery70.solve();
	int expectedResultmodifiesprocsubquery70[2][1] = {
		{0}, {1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultmodifiesprocsubquery70)/sizeof(expectedResultmodifiesprocsubquery70[0])), actualResultmodifiesprocsubquery70->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultmodifiesprocsubquery70)/sizeof(expectedResultmodifiesprocsubquery70[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultmodifiesprocsubquery70[i])/sizeof(expectedResultmodifiesprocsubquery70[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultmodifiesprocsubquery70[i][j], actualResultmodifiesprocsubquery70->getResultAt(i, j));
		}
	}

	// Test 71: Modifies(proc1, 6)
	ModifiesProcSubquery modifiesprocsubquery71 = ModifiesProcSubquery(&synonymTable, pk);
	modifiesprocsubquery71.setSynonyms("proc1", 6);
	ResultTuple* actualResultmodifiesprocsubquery71 = modifiesprocsubquery71.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultmodifiesprocsubquery71->getAllResults().size());

	// Test 124: Modifies(1, v2)
	ModifiesProcSubquery modifiesprocsubquery124 = ModifiesProcSubquery(&synonymTable, pk);
	modifiesprocsubquery124.setSynonyms(1, "v2");
	ResultTuple* actualResultmodifiesprocsubquery124 = modifiesprocsubquery124.solve();
	int expectedResultmodifiesprocsubquery124[7][1] = {
		{0}, {1}, {2}, {3}, {4}, {5}, {7}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultmodifiesprocsubquery124)/sizeof(expectedResultmodifiesprocsubquery124[0])), actualResultmodifiesprocsubquery124->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultmodifiesprocsubquery124)/sizeof(expectedResultmodifiesprocsubquery124[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultmodifiesprocsubquery124[i])/sizeof(expectedResultmodifiesprocsubquery124[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultmodifiesprocsubquery124[i][j], actualResultmodifiesprocsubquery124->getResultAt(i, j));
		}
	}

	// Test 129: Modifies(1, _)
	ModifiesProcSubquery modifiesprocsubquery129 = ModifiesProcSubquery(&synonymTable, pk);
	modifiesprocsubquery129.setSynonyms(1, "_");
	ResultTuple* actualResultmodifiesprocsubquery129 = modifiesprocsubquery129.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultmodifiesprocsubquery129->getAllResults().size());
	CPPUNIT_ASSERT(actualResultmodifiesprocsubquery129->isBool());
	CPPUNIT_ASSERT(!actualResultmodifiesprocsubquery129->isEmpty());

	// Test 130: Modifies(1, 2)
	ModifiesProcSubquery modifiesprocsubquery130 = ModifiesProcSubquery(&synonymTable, pk);
	modifiesprocsubquery130.setSynonyms(1, 2);
	ResultTuple* actualResultmodifiesprocsubquery130 = modifiesprocsubquery130.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultmodifiesprocsubquery130->getAllResults().size());
	CPPUNIT_ASSERT(actualResultmodifiesprocsubquery130->isBool());
	CPPUNIT_ASSERT(!actualResultmodifiesprocsubquery130->isEmpty());

	// Test 131: Modifies(1, 6)
	ModifiesProcSubquery modifiesprocsubquery131 = ModifiesProcSubquery(&synonymTable, pk);
	modifiesprocsubquery131.setSynonyms(1, 6);
	ResultTuple* actualResultmodifiesprocsubquery131 = modifiesprocsubquery131.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultmodifiesprocsubquery131->getAllResults().size());
	CPPUNIT_ASSERT(actualResultmodifiesprocsubquery131->isBool());
	CPPUNIT_ASSERT(actualResultmodifiesprocsubquery131->isEmpty());

	// Test 136: Modifies(2, v2)
	ModifiesProcSubquery modifiesprocsubquery136 = ModifiesProcSubquery(&synonymTable, pk);
	modifiesprocsubquery136.setSynonyms(2, "v2");
	ResultTuple* actualResultmodifiesprocsubquery136 = modifiesprocsubquery136.solve();
	int expectedResultmodifiesprocsubquery136[2][1] = {
		{1}, {7}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultmodifiesprocsubquery136)/sizeof(expectedResultmodifiesprocsubquery136[0])), actualResultmodifiesprocsubquery136->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultmodifiesprocsubquery136)/sizeof(expectedResultmodifiesprocsubquery136[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultmodifiesprocsubquery136[i])/sizeof(expectedResultmodifiesprocsubquery136[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultmodifiesprocsubquery136[i][j], actualResultmodifiesprocsubquery136->getResultAt(i, j));
		}
	}
	
	// Test 141: Modifies(2, _)
	ModifiesProcSubquery modifiesprocsubquery141 = ModifiesProcSubquery(&synonymTable, pk);
	modifiesprocsubquery141.setSynonyms(2, "_");
	ResultTuple* actualResultmodifiesprocsubquery141 = modifiesprocsubquery141.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultmodifiesprocsubquery141->getAllResults().size());
	CPPUNIT_ASSERT(actualResultmodifiesprocsubquery141->isBool());
	CPPUNIT_ASSERT(!actualResultmodifiesprocsubquery141->isEmpty());

	// Test 142: Modifies(2, 2)
	ModifiesProcSubquery modifiesprocsubquery142 = ModifiesProcSubquery(&synonymTable, pk);
	modifiesprocsubquery142.setSynonyms(2, 2);
	ResultTuple* actualResultmodifiesprocsubquery142 = modifiesprocsubquery142.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultmodifiesprocsubquery142->getAllResults().size());
	CPPUNIT_ASSERT(actualResultmodifiesprocsubquery142->isBool());
	CPPUNIT_ASSERT(actualResultmodifiesprocsubquery142->isEmpty());

	// Test 143: Modifies(2, 1)
	ModifiesProcSubquery modifiesprocsubquery143 = ModifiesProcSubquery(&synonymTable, pk);
	modifiesprocsubquery143.setSynonyms(2, 1);
	ResultTuple* actualResultmodifiesprocsubquery143 = modifiesprocsubquery143.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultmodifiesprocsubquery143->getAllResults().size());
	CPPUNIT_ASSERT(actualResultmodifiesprocsubquery143->isBool());
	CPPUNIT_ASSERT(!actualResultmodifiesprocsubquery143->isEmpty());
}

void SubqueryTest::testModifiesProcTuple(){
}

void SubqueryTest::testUses(){
	// Test 1: Uses(s1, x)
	UsesSubquery us1 = UsesSubquery(&synonymTable, pk);
	us1.setSynonyms("s1", 0);
	ResultTuple* actualResultsUsesSubquery1 = us1.solve();
	int expectedResultsUsesSubquery1[7][1] = {
		{3}, {6}, {7}, {13}, {14}, {18}, {20}
	};
	for (size_t i = 0; i < 7; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsUsesSubquery1[i][j], actualResultsUsesSubquery1->getResultAt(i, j));
		}
	}

	// Test 1.2: Uses(s1, _)
	UsesSubquery us1_2 = UsesSubquery(&synonymTable, pk);
	us1_2.setSynonyms("s1", "_");
	ResultTuple* actualResultsUsesSubquery1_2 = us1_2.solve();
	int expectedResultsUsesSubquery1_2[16][1] = {
		{3}, {6}, {7}, {8}, {9}, {10}, {11}, {12}, 
		{13}, {14}, {15}, {16}, {18}, {19}, {20}, {22}
	};
	for (size_t i = 0; i < 16; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsUsesSubquery1_2[i][j], actualResultsUsesSubquery1_2->getResultAt(i, j));
		}
	}

	// Test 1.3: Uses(s1, v1)
	UsesSubquery us1_3 = UsesSubquery(&synonymTable, pk);
	us1_3.setSynonyms("s1", "v1");
	ResultTuple* actualResultsUsesSubquery1_3 = us1_3.solve();
	int expectedResultsUsesSubquery1_3[36][2] = {
		{3, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {6, 2}, {6, 0},
		{6, 3}, {6, 4}, {6, 5}, {6, 6}, {6, 1}, {7, 0}, {7, 3}, {8, 4}, {8, 5}, 
		{8, 6}, {9, 5}, {10, 6}, {11, 1}, {12, 2}, {13, 0}, {13, 4}, {14, 0}, {15, 4},
		{16, 4}, {18, 1}, {18, 0}, {18, 2}, {19, 1}, {20, 0}, {20, 1}, {20, 3}, {22, 1}
	};
	for (size_t i = 0; i < 36; i++){
		for (size_t j = 0; j < 2; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsUsesSubquery1_3[i][j], actualResultsUsesSubquery1_3->getResultAt(i, j));
		}
	}

	// Test 2: Uses(a1, x)
	UsesSubquery us2 = UsesSubquery(&synonymTable, pk);
	us2.setSynonyms("a1", 0);
	ResultTuple* actualResultsUsesSubquery2 = us2.solve();
	int expectedResultsUsesSubquery2[4][1] = {
		{7}, {14}, {18}, {20}
	};
	for (size_t i = 0; i < 4; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsUsesSubquery2[i][j], actualResultsUsesSubquery2->getResultAt(i, j));
		}
	}
	// Test 2.2: Uses(a1, _)
	UsesSubquery us2_2 = UsesSubquery(&synonymTable, pk);
	us2_2.setSynonyms("a1", "_");
	ResultTuple* actualResultsUsesSubquery2_2 = us2_2.solve();
	int expectedResultsUsesSubquery2_2[10][1] = {
		{7}, {9}, {10}, {12}, {14}, {16}, {18}, {19}, {20}, {22}
	};
	for (size_t i = 0; i < 10; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsUsesSubquery2_2[i][j], actualResultsUsesSubquery2_2->getResultAt(i, j));
		}
	}
	// Test 2.3: Uses(a1, v1)
	UsesSubquery us2_3 = UsesSubquery(&synonymTable, pk);
	us2_3.setSynonyms("a1", "v1");
	ResultTuple* actualResultsUsesSubquery2_3 = us2_3.solve();
	int expectedResultsUsesSubquery2_3[15][2] = {
		{7, 0}, {7, 3}, {9, 5}, {10, 6}, {12, 2}, {14, 0}, {16, 4}, {18, 1}, {18, 0}, {18, 2}, {19, 1}, {20, 0}, {20, 1}, {20, 3}, {22, 1}
	};
	for (size_t i = 0; i < 15; i++){
		for (size_t j = 0; j < 2; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsUsesSubquery2_3[i][j], actualResultsUsesSubquery2_3->getResultAt(i, j));
		}
	}

	// Test 3: Uses(c1, x)
	UsesSubquery us3 = UsesSubquery(&synonymTable, pk);
	us3.setSynonyms("c1", 0);
	ResultTuple* actualResultsUsesSubquery3 = us3.solve();
	int expectedResultsUsesSubquery3[1][1] = {
		{3}
	};
	for (size_t i = 0; i < 1; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsUsesSubquery3[i][j], actualResultsUsesSubquery3->getResultAt(i, j));
		}
	}
	// Test 3.2: Uses(c1, _)
	UsesSubquery us3_2 = UsesSubquery(&synonymTable, pk);
	us3_2.setSynonyms("c1", "_");
	ResultTuple* actualResultsUsesSubquery3_2 = us3_2.solve();
	int expectedResultsUsesSubquery3_2[2][1] = {
		{3}, {11}
	};
	for (size_t i = 0; i < 2; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsUsesSubquery3_2[i][j], actualResultsUsesSubquery3_2->getResultAt(i, j));
		}
	}

	// Test 3.3: Uses(c1, v1)
	UsesSubquery us3_3 = UsesSubquery(&synonymTable, pk);
	us3_3.setSynonyms("c1", "v1");
	ResultTuple* actualResultsUsesSubquery3_3 = us3_3.solve();
	int expectedResultsUsesSubquery3_3[8][2] = {
		{3, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {11, 1}
	};
	for (size_t i = 0; i < 8; i++){
		for (size_t j = 0; j < 2; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsUsesSubquery3_3[i][j], actualResultsUsesSubquery3_3->getResultAt(i, j));
		}
	}

	// Test 4: Uses(i1, x)
	UsesSubquery us4 = UsesSubquery(&synonymTable, pk);
	us4.setSynonyms("i1", 0);
	ResultTuple* actualResultsUsesSubquery4 = us4.solve();
	int expectedResultsUsesSubquery4[1][1] = {
		{13}
	};
	for (size_t i = 0; i < 1; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsUsesSubquery4[i][j], actualResultsUsesSubquery4->getResultAt(i, j));
		}
	}
	// Test 4.2: Uses(i1, _)
	UsesSubquery us4_2 = UsesSubquery(&synonymTable, pk);
	us4_2.setSynonyms("i1", "_");
	ResultTuple* actualResultsUsesSubquery4_2 = us4_2.solve();
	int expectedResultsUsesSubquery4_2[2][1] = {
		{8}, {13}
	};
	for (size_t i = 0; i < 1; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsUsesSubquery4_2[i][j], actualResultsUsesSubquery4_2->getResultAt(i, j));
		}
	}
	
	// Test 4.3: Uses(i1, v1)
	UsesSubquery us4_3 = UsesSubquery(&synonymTable, pk);
	us4_3.setSynonyms("i1", "v1");
	ResultTuple* actualResultsUsesSubquery4_3 = us4_3.solve();
	int expectedResultsUsesSubquery4_3[5][2] = {
		{8, 4}, {8, 5}, {8, 6}, {13, 0}, {13, 4}
	};
	for (size_t i = 0; i < 5; i++){
		for (size_t j = 0; j < 2; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsUsesSubquery4_3[i][j], actualResultsUsesSubquery4_3->getResultAt(i, j));
		}
	}

	// Test 5: Uses(w1, x)
	UsesSubquery us5 = UsesSubquery(&synonymTable, pk);
	us5.setSynonyms("w1", 0);
	ResultTuple* actualResultsUsesSubquery5 = us5.solve();
	int expectedResultsUsesSubquery5[1][1] = {
		{6}
	};
	for (size_t i = 0; i < 1; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsUsesSubquery5[i][j], actualResultsUsesSubquery5->getResultAt(i, j));
		}
	}
	// Test 5.2: Uses(w1, _)
	UsesSubquery us5_2 = UsesSubquery(&synonymTable, pk);
	us5_2.setSynonyms("w1", "_");
	ResultTuple* actualResultsUsesSubquery5_2 = us5_2.solve();
	int expectedResultsUsesSubquery5_2[2][1] = {
		{6}, {15}
	};
	for (size_t i = 0; i < 1; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsUsesSubquery5_2[i][j], actualResultsUsesSubquery5_2->getResultAt(i, j));
		}
	}

	// Test 5.3: Uses(w1, v1)
	UsesSubquery us5_3 = UsesSubquery(&synonymTable, pk);
	us5_3.setSynonyms("w1", "v1");
	ResultTuple* actualResultsUsesSubquery5_3 = us5_3.solve();
	int expectedResultsUsesSubquery5_3[8][2] = {
		{6, 2}, {6, 0}, {6, 3}, {6, 4}, {6, 5}, {6, 6}, {6, 1}, {15, 4}
	
	};
	for (size_t i = 0; i < 8; i++){
		for (size_t j = 0; j < 2; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsUsesSubquery5_3[i][j], actualResultsUsesSubquery5_3->getResultAt(i, j));
		}
	}
}

void SubqueryTest::testUsesTuple() {
	ResultTuple* rt = new ResultTuple();
	rt->addSynonymToMap("s1", rt->addSynonym("s1"));
	int arr[] = {1, 2, 3, 4, 5};
	for (int i = 0; i < 5; i++) {
		vector<int> temp = vector<int>();
		temp.push_back(arr[i]);
		rt->addResultRow(temp);
	}
	
	// Test 1: Uses(s1, x)
	UsesSubquery ms1 = UsesSubquery(&synonymTable, pk);
	ms1.setSynonyms("s1", 0);
	ResultTuple* actualResultsUsesSubquery1 = ms1.solve(rt);
	int expectedResultsUsesSubquery1[1][1] = {
		{3}
	};
	for (size_t i = 0; i < 1; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsUsesSubquery1[i][j], actualResultsUsesSubquery1->getResultAt(i, j));
		}
	}

	// Test 1.2: Uses(s1, _)
	UsesSubquery ms1_2 = UsesSubquery(&synonymTable, pk);
	ms1_2.setSynonyms("s1", "_");
	ResultTuple* actualResultsUsesSubquery1_2 = ms1_2.solve(rt);
	int expectedResultsUsesSubquery1_2[1][1] = {
		{3}
	};
	for (size_t i = 0; i < 1; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsUsesSubquery1_2[i][j], actualResultsUsesSubquery1_2->getResultAt(i, j));
		}
	}

	rt = new ResultTuple();
	rt->addSynonymToMap("s1", rt->addSynonym("s1"));
	rt->addSynonymToMap("v1", rt->addSynonym("v1"));
	int arr12[15][2] = {
	{3, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, 
	{6, 2}, {6, 0},{6, 3}, {6, 4}, {6, 5}, {6, 6}, {6, 1}, {10, 10}
	};
	for (int i = 0; i < 14; i++) {
		vector<int> temp = vector<int>();
		temp.push_back(arr12[i][0]);
		temp.push_back(arr12[i][1]);
		rt->addResultRow(temp);
	}
	// Test 1.3: Uses(s1, v1)
	UsesSubquery ms1_3 = UsesSubquery(&synonymTable, pk);
	ms1_3.setSynonyms("s1", "v1");
	ResultTuple* actualResultsUsesSubquery1_3 = ms1_3.solve(rt);
	int expectedResultsUsesSubquery1_3[14][2] = {
		{3, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, 
	{6, 2}, {6, 0},{6, 3}, {6, 4}, {6, 5}, {6, 6}, {6, 1}
	};
	for (size_t i = 0; i < 14; i++){
		for (size_t j = 0; j < 2; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsUsesSubquery1_3[i][j], actualResultsUsesSubquery1_3->getResultAt(i, j));
		}
	}

	rt = new ResultTuple();
	rt->addSynonymToMap("s1", rt->addSynonym("s1"));
	rt->addSynonymToMap("v1", rt->addSynonym("v1"));
	int arr13[7][2] = {
		{3, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}
	};
	for (int i = 0; i < 7; i++) {
		vector<int> temp = vector<int>();
		temp.push_back(arr13[i][0]);
		temp.push_back(arr13[i][1]);
		rt->addResultRow(temp);
	}
	// Test 1.3: Uses(s1, v2)
	UsesSubquery ms1_31 = UsesSubquery(&synonymTable, pk);
	ms1_31.setSynonyms("s1", "v2");
	ResultTuple* actualResultsUsesSubquery1_31 = ms1_31.solve(rt);
	int expectedResultsUsesSubquery1_31[49][3] = {
		{3, 0, 0}, {3, 0, 1}, {3, 0, 2}, {3, 0, 3}, {3, 0, 4}, {3, 0, 5}, {3, 0, 6}, 
		{3, 1, 0}, {3, 1, 1}, {3, 1, 2}, {3, 1, 3}, {3, 1, 4}, {3, 1, 5}, {3, 1, 6},
		{3, 2, 0}, {3, 2, 1}, {3, 2, 2}, {3, 2, 3}, {3, 2, 4}, {3, 2, 5}, {3, 2, 6},
		{3, 3, 0}, {3, 3, 1}, {3, 3, 2}, {3, 3, 3}, {3, 3, 4}, {3, 3, 5}, {3, 3, 6},
		{3, 4, 0}, {3, 4, 1}, {3, 4, 2}, {3, 4, 3}, {3, 4, 4}, {3, 4, 5}, {3, 4, 6}, 
		{3, 5, 0}, {3, 5, 1}, {3, 5, 2}, {3, 5, 3}, {3, 5, 4}, {3, 5, 5}, {3, 5, 6}, 
		{3, 6, 0}, {3, 6, 1}, {3, 6, 2}, {3, 6, 3}, {3, 6, 4}, {3, 6, 5}, {3, 6, 6}
	};
	for (size_t i = 0; i < 49; i++){
		for (size_t j = 0; j < 3; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsUsesSubquery1_31[i][j], actualResultsUsesSubquery1_31->getResultAt(i, j));
		}
	}

	rt = new ResultTuple();
	rt->addSynonymToMap("v1", rt->addSynonym("v1"));
	int arr123[3] = {0, 1, 2};
	for (int i = 0; i < 3; i++) {
		vector<int> temp = vector<int>();
		temp.push_back(arr123[i]);
		rt->addResultRow(temp);
	}
	// Test 1.3: Uses(s1, v1)
	UsesSubquery ms1_3x = UsesSubquery(&synonymTable, pk);
	ms1_3x.setSynonyms("s1", "v1");
	ResultTuple* actualResultsUsesSubquery1_3x = ms1_3.solve(rt);
	int expectedResultsUsesSubquery1_3x[18][2] = {
		{0, 3}, {0, 6}, {0, 7}, {0, 13}, {0, 14}, {0, 18}, {0, 20}, {1, 3}, {1, 6}, {1, 11}, {1, 18}, {1, 19},
		{1, 20}, {1, 22}, {2, 3}, {2, 6}, {2, 12}, {2, 18}  
	};
	for (size_t i = 0; i < 18; i++){
		for (size_t j = 0; j < 2; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsUsesSubquery1_3x[i][j], actualResultsUsesSubquery1_3x->getResultAt(i, j));
		}
	}

	ResultTuple* rt2 = new ResultTuple();
	rt2->addSynonymToMap("a1", rt2->addSynonym("a1"));
	int arr2[] = {1, 2, 4, 5};
	for (int i = 0; i < 4; i++) {
		vector<int> temp = vector<int>();
		temp.push_back(arr2[i]);
		rt2->addResultRow(temp);
	}
	// Test 2: Uses(a1, x)
	UsesSubquery ms2 = UsesSubquery(&synonymTable, pk);
	ms2.setSynonyms("a1", 0);
	ResultTuple* actualResultsUsesSubquery2 = ms2.solve(rt2);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultsUsesSubquery2->getAllResults().size());
	
	// Test 2.2: Uses(a1, _)
	UsesSubquery ms2_2 = UsesSubquery(&synonymTable, pk);
	ms2_2.setSynonyms("a1", "_");
	ResultTuple* actualResultsUsesSubquery2_2 = ms2_2.solve(rt2);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultsUsesSubquery2_2->getAllResults().size());

	ResultTuple* rt3 = new ResultTuple();
	rt3->addSynonymToMap("c1", rt3->addSynonym("c1"));
	int arr3[] = {3, 11};
	for (int i = 0; i < 2; i++) {
		vector<int> temp = vector<int>();
		temp.push_back(arr3[i]);
		rt3->addResultRow(temp);
	}
	// Test 3: Uses(c1, x)
	UsesSubquery ms3 = UsesSubquery(&synonymTable, pk);
	ms3.setSynonyms("c1", 0);
	ResultTuple* actualResultsUsesSubquery3 = ms3.solve(rt3);
	int expectedResultsUsesSubquery3[1][1] = {{3}};
	for (size_t i = 0; i < 1; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsUsesSubquery3[i][j], actualResultsUsesSubquery3->getResultAt(i, j));
		}
	}
	// Test 3.2: Uses(c1, _)
	UsesSubquery ms3_2 = UsesSubquery(&synonymTable, pk);
	ms3_2.setSynonyms("c1", "_");
	ResultTuple* actualResultsUsesSubquery3_2 = ms3_2.solve(rt3);
	int expectedResultsUsesSubquery3_2[2][1] = {{3}, {11}};
	for (size_t i = 0; i < 2; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsUsesSubquery3_2[i][j], actualResultsUsesSubquery3_2->getResultAt(i, j));
		}
	}

		ResultTuple* rt4 = new ResultTuple();
	rt4->addSynonymToMap("i1", rt4->addSynonym("i1"));
	int arr4[] = {8};
	for (int i = 0; i < 1; i++) {
		vector<int> temp = vector<int>();
		temp.push_back(arr4[i]);
		rt4->addResultRow(temp);
	}

	// Test 4: Uses(i1, x)
	UsesSubquery ms4 = UsesSubquery(&synonymTable, pk);
	ms4.setSynonyms("i1", 0);
	ResultTuple* actualResultsUsesSubquery4 = ms4.solve(rt4);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultsUsesSubquery4->getAllResults().size());

	// Test 4.2: Uses(i1, _)
	UsesSubquery ms4_2 = UsesSubquery(&synonymTable, pk);
	ms4_2.setSynonyms("i1", "_");
	ResultTuple* actualResultsUsesSubquery4_2 = ms4_2.solve(rt4);
	int expectedResultsUsesSubquery4_2[1][1] = {
		{8}	
	};
	for (size_t i = 0; i < 1; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsUsesSubquery4_2[i][j], actualResultsUsesSubquery4_2->getResultAt(i, j));
		}
	}

	ResultTuple* rt5 = new ResultTuple();
	rt5->addSynonymToMap("w1", rt5->addSynonym("w1"));
	int arr5[] = {6, 15};
	for (int i = 0; i < 2; i++) {
		vector<int> temp = vector<int>();
		temp.push_back(arr5[i]);
		rt5->addResultRow(temp);
	}
	// Test 5: Uses(w1, x)
	UsesSubquery ms5 = UsesSubquery(&synonymTable, pk);
	ms5.setSynonyms("w1", 0);
	ResultTuple* actualResultsUsesSubquery5 = ms5.solve(rt5);
	int expectedResultsUsesSubquery5[1][1] = {
		{6}
	};
	for (size_t i = 0; i < 1; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsUsesSubquery5[i][j], actualResultsUsesSubquery5->getResultAt(i, j));
		}
	}
	// Test 5.2: Uses(w1, _)
	UsesSubquery ms5_2 = UsesSubquery(&synonymTable, pk);
	ms5_2.setSynonyms("w1", "_");
	ResultTuple* actualResultsUsesSubquery5_2 = ms5_2.solve(rt5);
	int expectedResultsUsesSubquery5_2[2][1] = {
		{6}, {15}	
	};
	for (size_t i = 0; i < 1; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsUsesSubquery5_2[i][j], actualResultsUsesSubquery5_2->getResultAt(i, j));
		}
	}
}

void SubqueryTest::testUsesProc(){
	// Test 64: Uses(proc1, v2)
	UsesProcSubquery usesprocsubquery64 = UsesProcSubquery(&synonymTable, pk);
	usesprocsubquery64.setSynonyms("proc1", "v2");
	ResultTuple* actualResultusesprocsubquery64 = usesprocsubquery64.solve();
	int expectedResultusesprocsubquery64[15][2] = {
		{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6},
		{1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6},
		{2, 1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultusesprocsubquery64)/sizeof(expectedResultusesprocsubquery64[0])), actualResultusesprocsubquery64->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultusesprocsubquery64)/sizeof(expectedResultusesprocsubquery64[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultusesprocsubquery64[i])/sizeof(expectedResultusesprocsubquery64[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultusesprocsubquery64[i][j], actualResultusesprocsubquery64->getResultAt(i, j));
		}
	}

	// Test 69: Uses(proc1, _)
	UsesProcSubquery usesprocsubquery69 = UsesProcSubquery(&synonymTable, pk);
	usesprocsubquery69.setSynonyms("proc1", "_");
	ResultTuple* actualResultusesprocsubquery69 = usesprocsubquery69.solve();
	int expectedResultusesprocsubquery69[3][1] = {
		{0}, {1}, {2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultusesprocsubquery69)/sizeof(expectedResultusesprocsubquery69[0])), actualResultusesprocsubquery69->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultusesprocsubquery69)/sizeof(expectedResultusesprocsubquery69[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultusesprocsubquery69[i])/sizeof(expectedResultusesprocsubquery69[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultusesprocsubquery69[i][j], actualResultusesprocsubquery69->getResultAt(i, j));
		}
	}
	
	// Test 70: Uses(proc1, 2)
	UsesProcSubquery usesprocsubquery70 = UsesProcSubquery(&synonymTable, pk);
	usesprocsubquery70.setSynonyms("proc1", 2);
	ResultTuple* actualResultusesprocsubquery70 = usesprocsubquery70.solve();
	int expectedResultusesprocsubquery70[2][1] = {
		{0}, {1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultusesprocsubquery70)/sizeof(expectedResultusesprocsubquery70[0])), actualResultusesprocsubquery70->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultusesprocsubquery70)/sizeof(expectedResultusesprocsubquery70[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultusesprocsubquery70[i])/sizeof(expectedResultusesprocsubquery70[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultusesprocsubquery70[i][j], actualResultusesprocsubquery70->getResultAt(i, j));
		}
	}

	// Test 71: Uses(proc1, 6)
	UsesProcSubquery usesprocsubquery71 = UsesProcSubquery(&synonymTable, pk);
	usesprocsubquery71.setSynonyms("proc1", 6);
	ResultTuple* actualResultusesprocsubquery71 = usesprocsubquery71.solve();
	int expectedResultusesprocsubquery71[2][1] = {
		{0}, {1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultusesprocsubquery71)/sizeof(expectedResultusesprocsubquery71[0])), actualResultusesprocsubquery71->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultusesprocsubquery71)/sizeof(expectedResultusesprocsubquery71[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultusesprocsubquery71[i])/sizeof(expectedResultusesprocsubquery71[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultusesprocsubquery71[i][j], actualResultusesprocsubquery71->getResultAt(i, j));
		}
	}

	// Test 124: Uses(1, v2)
	UsesProcSubquery usesprocsubquery124 = UsesProcSubquery(&synonymTable, pk);
	usesprocsubquery124.setSynonyms(1, "v2");
	ResultTuple* actualResultusesprocsubquery124 = usesprocsubquery124.solve();
	int expectedResultusesprocsubquery124[7][1] = {
		{0}, {1}, {2}, {3}, {4}, {5}, {6}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultusesprocsubquery124)/sizeof(expectedResultusesprocsubquery124[0])), actualResultusesprocsubquery124->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultusesprocsubquery124)/sizeof(expectedResultusesprocsubquery124[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultusesprocsubquery124[i])/sizeof(expectedResultusesprocsubquery124[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultusesprocsubquery124[i][j], actualResultusesprocsubquery124->getResultAt(i, j));
		}
	}

	// Test 129: Uses(1, _)
	UsesProcSubquery usesprocsubquery129 = UsesProcSubquery(&synonymTable, pk);
	usesprocsubquery129.setSynonyms(1, "_");
	ResultTuple* actualResultusesprocsubquery129 = usesprocsubquery129.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultusesprocsubquery129->getAllResults().size());
	CPPUNIT_ASSERT(actualResultusesprocsubquery129->isBool());
	CPPUNIT_ASSERT(!actualResultusesprocsubquery129->isEmpty());

	// Test 130: Uses(1, 7)
	UsesProcSubquery usesprocsubquery130 = UsesProcSubquery(&synonymTable, pk);
	usesprocsubquery130.setSynonyms(1, 7);
	ResultTuple* actualResultusesprocsubquery130 = usesprocsubquery130.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultusesprocsubquery130->getAllResults().size());
	CPPUNIT_ASSERT(actualResultusesprocsubquery130->isBool());
	CPPUNIT_ASSERT(actualResultusesprocsubquery130->isEmpty());

	// Test 131: Uses(1, 6)
	UsesProcSubquery usesprocsubquery131 = UsesProcSubquery(&synonymTable, pk);
	usesprocsubquery131.setSynonyms(1, 6);
	ResultTuple* actualResultusesprocsubquery131 = usesprocsubquery131.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultusesprocsubquery131->getAllResults().size());
	CPPUNIT_ASSERT(actualResultusesprocsubquery131->isBool());
	CPPUNIT_ASSERT(!actualResultusesprocsubquery131->isEmpty());

	// Test 136: Uses(2, v2)
	UsesProcSubquery usesprocsubquery136 = UsesProcSubquery(&synonymTable, pk);
	usesprocsubquery136.setSynonyms(2, "v2");
	ResultTuple* actualResultusesprocsubquery136 = usesprocsubquery136.solve();
	int expectedResultusesprocsubquery136[1][1] = {
		{1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultusesprocsubquery136)/sizeof(expectedResultusesprocsubquery136[0])), actualResultusesprocsubquery136->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultusesprocsubquery136)/sizeof(expectedResultusesprocsubquery136[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultusesprocsubquery136[i])/sizeof(expectedResultusesprocsubquery136[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultusesprocsubquery136[i][j], actualResultusesprocsubquery136->getResultAt(i, j));
		}
	}
	
	// Test 141: Uses(2, _)
	UsesProcSubquery usesprocsubquery141 = UsesProcSubquery(&synonymTable, pk);
	usesprocsubquery141.setSynonyms(2, "_");
	ResultTuple* actualResultusesprocsubquery141 = usesprocsubquery141.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultusesprocsubquery141->getAllResults().size());
	CPPUNIT_ASSERT(actualResultusesprocsubquery141->isBool());
	CPPUNIT_ASSERT(!actualResultusesprocsubquery141->isEmpty());

	// Test 142: Uses(2, 2)
	UsesProcSubquery usesprocsubquery142 = UsesProcSubquery(&synonymTable, pk);
	usesprocsubquery142.setSynonyms(2, 2);
	ResultTuple* actualResultusesprocsubquery142 = usesprocsubquery142.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultusesprocsubquery142->getAllResults().size());
	CPPUNIT_ASSERT(actualResultusesprocsubquery142->isBool());
	CPPUNIT_ASSERT(actualResultusesprocsubquery142->isEmpty());

	// Test 143: Uses(2, 1)
	UsesProcSubquery usesprocsubquery143 = UsesProcSubquery(&synonymTable, pk);
	usesprocsubquery143.setSynonyms(2, 1);
	ResultTuple* actualResultusesprocsubquery143 = usesprocsubquery143.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultusesprocsubquery143->getAllResults().size());
	CPPUNIT_ASSERT(actualResultusesprocsubquery143->isBool());
	CPPUNIT_ASSERT(!actualResultusesprocsubquery143->isEmpty());
}

void SubqueryTest::testUsesProcTuple(){
}

void SubqueryTest::testCalls(){
	// Test 65: Calls(proc1, proc2)
	CallsSubquery callssubquery65 = CallsSubquery(&synonymTable, pk);
	callssubquery65.setSynonyms("proc1", "proc2");
	ResultTuple* actualResultcallssubquery65 = callssubquery65.solve();
	int expectedResultcallssubquery65[2][2] = {
		{0, 1}, {1, 2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultcallssubquery65)/sizeof(expectedResultcallssubquery65[0])), actualResultcallssubquery65->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultcallssubquery65)/sizeof(expectedResultcallssubquery65[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultcallssubquery65[i])/sizeof(expectedResultcallssubquery65[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultcallssubquery65[i][j], actualResultcallssubquery65->getResultAt(i, j));
		}
	}

	// Test 69: Calls(proc1, _)
	CallsSubquery callssubquery69 = CallsSubquery(&synonymTable, pk);
	callssubquery69.setSynonyms("proc1", "_");
	ResultTuple* actualResultcallssubquery69 = callssubquery69.solve();
	int expectedResultcallssubquery69[2][1] = {
		{0}, {1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultcallssubquery69)/sizeof(expectedResultcallssubquery69[0])), actualResultcallssubquery69->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultcallssubquery69)/sizeof(expectedResultcallssubquery69[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultcallssubquery69[i])/sizeof(expectedResultcallssubquery69[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultcallssubquery69[i][j], actualResultcallssubquery69->getResultAt(i, j));
		}
	}

	// Test 70: Calls(proc1, 2)
	CallsSubquery callssubquery70 = CallsSubquery(&synonymTable, pk);
	callssubquery70.setSynonyms("proc1", 2);
	ResultTuple* actualResultcallssubquery70 = callssubquery70.solve();
	int expectedResultcallssubquery70[1][1] = {
		{1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultcallssubquery70)/sizeof(expectedResultcallssubquery70[0])), actualResultcallssubquery70->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultcallssubquery70)/sizeof(expectedResultcallssubquery70[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultcallssubquery70[i])/sizeof(expectedResultcallssubquery70[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultcallssubquery70[i][j], actualResultcallssubquery70->getResultAt(i, j));
		}
	}

	// Test 71: Calls(proc1, 6)
	CallsSubquery callssubquery71 = CallsSubquery(&synonymTable, pk);
	callssubquery71.setSynonyms("proc1", 6);
	ResultTuple* actualResultcallssubquery71 = callssubquery71.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultcallssubquery71->getAllResults().size());

	// Test 113: Calls(_, proc2)
	CallsSubquery callssubquery113 = CallsSubquery(&synonymTable, pk);
	callssubquery113.setSynonyms("_", "proc2");
	ResultTuple* actualResultcallssubquery113 = callssubquery113.solve();
	int expectedResultcallssubquery113[2][1] = {
		{1}, {2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultcallssubquery113)/sizeof(expectedResultcallssubquery113[0])), actualResultcallssubquery113->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultcallssubquery113)/sizeof(expectedResultcallssubquery113[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultcallssubquery113[i])/sizeof(expectedResultcallssubquery113[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultcallssubquery113[i][j], actualResultcallssubquery113->getResultAt(i, j));
		}
	}

	// Test 117: Calls(_, _)
	CallsSubquery callssubquery117 = CallsSubquery(&synonymTable, pk);
	callssubquery117.setSynonyms("_", "_");
	ResultTuple* actualResultcallssubquery117 = callssubquery117.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultcallssubquery117->getAllResults().size());
	CPPUNIT_ASSERT(actualResultcallssubquery117->isBool());
	CPPUNIT_ASSERT(!actualResultcallssubquery117->isEmpty());

	// Test 118: Calls(_, 2)
	CallsSubquery callssubquery118 = CallsSubquery(&synonymTable, pk);
	callssubquery118.setSynonyms("_", 2);
	ResultTuple* actualResultcallssubquery118 = callssubquery118.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultcallssubquery118->getAllResults().size());
	CPPUNIT_ASSERT(actualResultcallssubquery118->isBool());
	CPPUNIT_ASSERT(!actualResultcallssubquery118->isEmpty());

	// Test 119: Calls(_, 6)
	CallsSubquery callssubquery119 = CallsSubquery(&synonymTable, pk);
	callssubquery119.setSynonyms("_", 6);
	ResultTuple* actualResultcallssubquery119 = callssubquery119.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultcallssubquery119->getAllResults().size());
	CPPUNIT_ASSERT(actualResultcallssubquery119->isBool());
	CPPUNIT_ASSERT(actualResultcallssubquery119->isEmpty());

	// Test 125: Calls(1, proc2)
	CallsSubquery callssubquery125 = CallsSubquery(&synonymTable, pk);
	callssubquery125.setSynonyms(1, "proc2");
	ResultTuple* actualResultcallssubquery125 = callssubquery125.solve();
	int expectedResultcallssubquery125[1][1] = {
		{2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultcallssubquery125)/sizeof(expectedResultcallssubquery125[0])), actualResultcallssubquery125->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultcallssubquery125)/sizeof(expectedResultcallssubquery125[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultcallssubquery125[i])/sizeof(expectedResultcallssubquery125[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultcallssubquery125[i][j], actualResultcallssubquery125->getResultAt(i, j));
		}
	}

	// Test 129: Calls(1, _)
	CallsSubquery callssubquery129 = CallsSubquery(&synonymTable, pk);
	callssubquery129.setSynonyms(1, "_");
	ResultTuple* actualResultcallssubquery129 = callssubquery129.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultcallssubquery129->getAllResults().size());
	CPPUNIT_ASSERT(actualResultcallssubquery129->isBool());
	CPPUNIT_ASSERT(!actualResultcallssubquery129->isEmpty());

	// Test 130: Calls(1, 2)
	CallsSubquery callssubquery130 = CallsSubquery(&synonymTable, pk);
	callssubquery130.setSynonyms(1, 2);
	ResultTuple* actualResultcallssubquery130 = callssubquery130.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultcallssubquery130->getAllResults().size());
	CPPUNIT_ASSERT(actualResultcallssubquery130->isBool());
	CPPUNIT_ASSERT(!actualResultcallssubquery130->isEmpty());

	// Test 131: Calls(1, 6)
	CallsSubquery callssubquery131 = CallsSubquery(&synonymTable, pk);
	callssubquery131.setSynonyms(1, 6);
	ResultTuple* actualResultcallssubquery131 = callssubquery131.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultcallssubquery131->getAllResults().size());
	CPPUNIT_ASSERT(actualResultcallssubquery131->isBool());
	CPPUNIT_ASSERT(actualResultcallssubquery131->isEmpty());

	// Test 137: Calls(5, proc2)
	CallsSubquery callssubquery137 = CallsSubquery(&synonymTable, pk);
	callssubquery137.setSynonyms(5, "proc2");
	ResultTuple* actualResultcallssubquery137 = callssubquery137.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultcallssubquery137->getAllResults().size());
	
	// Test 141: Calls(5, _)
	CallsSubquery callssubquery141 = CallsSubquery(&synonymTable, pk);
	callssubquery141.setSynonyms(5, "_");
	ResultTuple* actualResultcallssubquery141 = callssubquery141.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultcallssubquery141->getAllResults().size());
	CPPUNIT_ASSERT(actualResultcallssubquery141->isBool());
	CPPUNIT_ASSERT(actualResultcallssubquery141->isEmpty());

	// Test 142: Calls(5, 2)
	CallsSubquery callssubquery142 = CallsSubquery(&synonymTable, pk);
	callssubquery142.setSynonyms(5, 2);
	ResultTuple* actualResultcallssubquery142 = callssubquery142.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultcallssubquery142->getAllResults().size());
	CPPUNIT_ASSERT(actualResultcallssubquery142->isBool());
	CPPUNIT_ASSERT(actualResultcallssubquery142->isEmpty());

	// Test 143: Calls(5, 6)
	CallsSubquery callssubquery143 = CallsSubquery(&synonymTable, pk);
	callssubquery143.setSynonyms(5, 6);
	ResultTuple* actualResultcallssubquery143 = callssubquery143.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultcallssubquery143->getAllResults().size());
	CPPUNIT_ASSERT(actualResultcallssubquery143->isBool());
	CPPUNIT_ASSERT(actualResultcallssubquery143->isEmpty());

	// Test 144: Calls(0, 2)
	CallsSubquery callssubquery144 = CallsSubquery(&synonymTable, pk);
	callssubquery144.setSynonyms(0, 2);
	ResultTuple* actualResultcallssubquery144 = callssubquery144.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultcallssubquery144->getAllResults().size());
	CPPUNIT_ASSERT(actualResultcallssubquery144->isBool());
	CPPUNIT_ASSERT(actualResultcallssubquery144->isEmpty());
}

void SubqueryTest::testCallsTuple(){
	// testTuple:
	//  s1  |  a1  |  w1  |  i2  |  c2  |  l1  |  const1  |  v1  |  proc1  |
	//  1   |  1   |  6   |  8   |  3   |  1   |  0       |  0   |  0      |
	//  1   |  2   |  6   |  8   |  3   |  1   |  0       |  0   |  0      |
	//  1   |  1   |  15  |  8   |  3   |  1   |  0       |  0   |  0      |
	//  1   |  2   |  6   |  13  |  3   |  1   |  0       |  0   |  0      |
	//  1   |  1   |  6   |  8   |  11  |  1   |  0       |  0   |  0      |
	//  8   |  2   |  6   |  8   |  3   |  7   |  0       |  0   |  0      |
	//  1   |  1   |  6   |  8   |  3   |  1   |  3       |  0   |  0      |
	//  3   |  2   |  6   |  8   |  3   |  1   |  0       |  2   |  0      |
	//  1   |  2   |  6   |  8   |  3   |  1   |  0       |  2   |  1      |
	ResultTuple testTuple = ResultTuple();
	int index = testTuple.addSynonym("s1");
	testTuple.addSynonymToMap("s1", index);
	index = testTuple.addSynonym("a1");
	testTuple.addSynonymToMap("a1", index);
	index = testTuple.addSynonym("w1");
	testTuple.addSynonymToMap("w1", index);
	index = testTuple.addSynonym("i2");
	testTuple.addSynonymToMap("i2", index);
	index = testTuple.addSynonym("c2");
	testTuple.addSynonymToMap("c2", index);
	index = testTuple.addSynonym("l1");
	testTuple.addSynonymToMap("l1", index);
	index = testTuple.addSynonym("const1");
	testTuple.addSynonymToMap("const1", index);
	index = testTuple.addSynonym("v1");
	testTuple.addSynonymToMap("v1", index);
	index = testTuple.addSynonym("proc1");
	testTuple.addSynonymToMap("proc1", index);
	int data[9][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	for (int i = 0; i < 9; i++){
		vector<int> tempVector = vector<int>();
		testTuple.addResultRow(tempVector);
		for (int j = 0; j < 9; j++){
			testTuple.addResult(i, data[i][j]);
		}
	}

	// Test 65: Calls(proc1, proc2)
	CallsSubquery callssubquery65 = CallsSubquery(&synonymTable, pk);
	callssubquery65.setSynonyms("proc1", "proc2");
	ResultTuple* actualResultcallssubquery65 = callssubquery65.solve(&testTuple);
	int expectedResultcallssubquery65[8][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  1},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  1},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  1},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultcallssubquery65)/sizeof(expectedResultcallssubquery65[0])), actualResultcallssubquery65->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultcallssubquery65)/sizeof(expectedResultcallssubquery65[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultcallssubquery65[i])/sizeof(expectedResultcallssubquery65[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultcallssubquery65[i][j], actualResultcallssubquery65->getResultAt(i, j));
		}
	}

	// Test 69: Calls(proc1, _)
	CallsSubquery callssubquery69 = CallsSubquery(&synonymTable, pk);
	callssubquery69.setSynonyms("proc1", "_");
	ResultTuple* actualResultcallssubquery69 = callssubquery69.solve(&testTuple);
	int expectedResultcallssubquery69[8][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultcallssubquery69)/sizeof(expectedResultcallssubquery69[0])), actualResultcallssubquery69->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultcallssubquery69)/sizeof(expectedResultcallssubquery69[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultcallssubquery69[i])/sizeof(expectedResultcallssubquery69[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultcallssubquery69[i][j], actualResultcallssubquery69->getResultAt(i, j));
		}
	}

	// Test 70: Calls(proc1, 2)
	CallsSubquery callssubquery70 = CallsSubquery(&synonymTable, pk);
	callssubquery70.setSynonyms("proc1", 2);
	ResultTuple* actualResultcallssubquery70 = callssubquery70.solve(&testTuple);
	int expectedResultcallssubquery70[1][9] = {
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultcallssubquery70)/sizeof(expectedResultcallssubquery70[0])), actualResultcallssubquery70->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultcallssubquery70)/sizeof(expectedResultcallssubquery70[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultcallssubquery70[i])/sizeof(expectedResultcallssubquery70[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultcallssubquery70[i][j], actualResultcallssubquery70->getResultAt(i, j));
		}
	}
	
	// Test 71: Calls(proc1, 6)
	CallsSubquery callssubquery71 = CallsSubquery(&synonymTable, pk);
	callssubquery71.setSynonyms("proc1", 6);
	ResultTuple* actualResultcallssubquery71 = callssubquery71.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultcallssubquery71->getAllResults().size());

	// Test 72: Calls(0, proc1)
	CallsSubquery callssubquery72 = CallsSubquery(&synonymTable, pk);
	callssubquery72.setSynonyms(0, "proc1");
	ResultTuple* actualResultcallssubquery72 = callssubquery72.solve(&testTuple);
	int expectedResultcallssubquery72[1][9] = {
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultcallssubquery72)/sizeof(expectedResultcallssubquery72[0])), actualResultcallssubquery72->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultcallssubquery72)/sizeof(expectedResultcallssubquery72[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultcallssubquery72[i])/sizeof(expectedResultcallssubquery72[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultcallssubquery72[i][j], actualResultcallssubquery72->getResultAt(i, j));
		}
	}

	// Test 73: Calls("_", proc1)
	CallsSubquery callssubquery73 = CallsSubquery(&synonymTable, pk);
	callssubquery73.setSynonyms("_", "proc1");
	ResultTuple* actualResultcallssubquery73 = callssubquery73.solve(&testTuple);
	int expectedResultcallssubquery73[2][9] = {
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultcallssubquery73)/sizeof(expectedResultcallssubquery73[0])), actualResultcallssubquery73->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultcallssubquery73)/sizeof(expectedResultcallssubquery73[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultcallssubquery73[i])/sizeof(expectedResultcallssubquery73[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultcallssubquery73[i][j], actualResultcallssubquery73->getResultAt(i, j));
		}
	}

	ResultTuple testTuple2 = ResultTuple();
	index = testTuple2.addSynonym("proc1");
	testTuple2.addSynonymToMap("proc1", index);
	index = testTuple2.addSynonym("proc2");
	testTuple2.addSynonymToMap("proc2", index);
	int data2[5][2] = {
		{0  ,  1  },
		{0  ,  0  },
		{1  ,  0  },
		{1  ,  2  },
		{2  ,  0  }
	};
	for (int i = 0; i < 5; i++){
		vector<int> tempVector = vector<int>();
		testTuple2.addResultRow(tempVector);
		for (int j = 0; j < 2; j++){
			testTuple2.addResult(i, data2[i][j]);
		}
	}

	// Test 75: Calls(proc1, proc2)
	CallsSubquery callssubquery75 = CallsSubquery(&synonymTable, pk);
	callssubquery75.setSynonyms("proc1", "proc2");
	ResultTuple* actualResultcallssubquery75 = callssubquery75.solve(&testTuple2);
	int expectedResultcallssubquery75[2][2] = {
		{0, 1}, {1, 2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultcallssubquery75)/sizeof(expectedResultcallssubquery75[0])), actualResultcallssubquery75->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultcallssubquery75)/sizeof(expectedResultcallssubquery75[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultcallssubquery75[i])/sizeof(expectedResultcallssubquery75[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultcallssubquery75[i][j], actualResultcallssubquery75->getResultAt(i, j));
		}
	}

	PKBController* pk2 = new PKBController();

	TNode stmt1("CALL_NODE", "Two", 1, 0);
	TNode stmt2("CALL_NODE", "Three", 2, 0);
	TNode stmt3("CALL_NODE", "Three", 3, 1);
	TNode stmt4("ASSIGN_NODE", "a = 1", 4, 2);
	pk2->statementTable.insertStatement(&stmt1);
	pk2->statementTable.insertStatement(&stmt2);
	pk2->statementTable.insertStatement(&stmt3);
	pk2->statementTable.insertStatement(&stmt4);

	pk2->procTable.insertProc("One");  // 0
	pk2->procTable.insertProc("Two"); // 1
	pk2->procTable.insertProc("Three");  // 2

	pk2->callsTable.insertCalls(0, 1);
	pk2->callsTable.insertCalls(0, 2);
	pk2->callsTable.insertCalls(1, 2);

	pk2->constructCalls();

	// Test 76: Calls(proc1, proc2)
	CallsSubquery callssubquery76 = CallsSubquery(&synonymTable, pk2);
	callssubquery76.setSynonyms("proc1", "proc2");
	ResultTuple* actualResultcallssubquery76 = callssubquery76.solve(&testTuple);
	int expectedResultcallssubquery76[15][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  2},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  1},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  1},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  2},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultcallssubquery76)/sizeof(expectedResultcallssubquery76[0])), actualResultcallssubquery76->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultcallssubquery76)/sizeof(expectedResultcallssubquery76[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultcallssubquery76[i])/sizeof(expectedResultcallssubquery76[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultcallssubquery76[i][j], actualResultcallssubquery76->getResultAt(i, j));
		}
	}
}

void SubqueryTest::testCallsT(){
	// Test 65: CallsStar(proc1, proc2)
	CallsStarSubquery callsStarsubquery65 = CallsStarSubquery(&synonymTable, pk);
	callsStarsubquery65.setSynonyms("proc1", "proc2");
	ResultTuple* actualResultcallsStarsubquery65 = callsStarsubquery65.solve();
	int expectedResultcallsStarsubquery65[3][2] = {
		{0, 1}, {0, 2}, {1, 2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultcallsStarsubquery65)/sizeof(expectedResultcallsStarsubquery65[0])), actualResultcallsStarsubquery65->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultcallsStarsubquery65)/sizeof(expectedResultcallsStarsubquery65[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultcallsStarsubquery65[i])/sizeof(expectedResultcallsStarsubquery65[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultcallsStarsubquery65[i][j], actualResultcallsStarsubquery65->getResultAt(i, j));
		}
	}

	// Test 69: CallsStar(proc1, _)
	CallsStarSubquery callsStarsubquery69 = CallsStarSubquery(&synonymTable, pk);
	callsStarsubquery69.setSynonyms("proc1", "_");
	ResultTuple* actualResultcallsStarsubquery69 = callsStarsubquery69.solve();
	int expectedResultcallsStarsubquery69[2][1] = {
		{0}, {1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultcallsStarsubquery69)/sizeof(expectedResultcallsStarsubquery69[0])), actualResultcallsStarsubquery69->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultcallsStarsubquery69)/sizeof(expectedResultcallsStarsubquery69[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultcallsStarsubquery69[i])/sizeof(expectedResultcallsStarsubquery69[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultcallsStarsubquery69[i][j], actualResultcallsStarsubquery69->getResultAt(i, j));
		}
	}

	// Test 70: CallsStar(proc1, 2)
	CallsStarSubquery callsStarsubquery70 = CallsStarSubquery(&synonymTable, pk);
	callsStarsubquery70.setSynonyms("proc1", 2);
	ResultTuple* actualResultcallsStarsubquery70 = callsStarsubquery70.solve();
	int expectedResultcallsStarsubquery70[2][1] = {
		{0}, {1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultcallsStarsubquery70)/sizeof(expectedResultcallsStarsubquery70[0])), actualResultcallsStarsubquery70->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultcallsStarsubquery70)/sizeof(expectedResultcallsStarsubquery70[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultcallsStarsubquery70[i])/sizeof(expectedResultcallsStarsubquery70[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultcallsStarsubquery70[i][j], actualResultcallsStarsubquery70->getResultAt(i, j));
		}
	}

	// Test 71: CallsStar(proc1, 6)
	CallsStarSubquery callsStarsubquery71 = CallsStarSubquery(&synonymTable, pk);
	callsStarsubquery71.setSynonyms("proc1", 6);
	ResultTuple* actualResultcallsStarsubquery71 = callsStarsubquery71.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultcallsStarsubquery71->getAllResults().size());

	// Test 113: CallsStar(_, proc2)
	CallsStarSubquery callsStarsubquery113 = CallsStarSubquery(&synonymTable, pk);
	callsStarsubquery113.setSynonyms("_", "proc2");
	ResultTuple* actualResultcallsStarsubquery113 = callsStarsubquery113.solve();
	int expectedResultcallsStarsubquery113[2][1] = {
		{1}, {2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultcallsStarsubquery113)/sizeof(expectedResultcallsStarsubquery113[0])), actualResultcallsStarsubquery113->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultcallsStarsubquery113)/sizeof(expectedResultcallsStarsubquery113[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultcallsStarsubquery113[i])/sizeof(expectedResultcallsStarsubquery113[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultcallsStarsubquery113[i][j], actualResultcallsStarsubquery113->getResultAt(i, j));
		}
	}

	// Test 117: CallsStar(_, _)
	CallsStarSubquery callsStarsubquery117 = CallsStarSubquery(&synonymTable, pk);
	callsStarsubquery117.setSynonyms("_", "_");
	ResultTuple* actualResultcallsStarsubquery117 = callsStarsubquery117.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultcallsStarsubquery117->getAllResults().size());
	CPPUNIT_ASSERT(actualResultcallsStarsubquery117->isBool());
	CPPUNIT_ASSERT(!actualResultcallsStarsubquery117->isEmpty());

	// Test 118: CallsStar(_, 2)
	CallsStarSubquery callsStarsubquery118 = CallsStarSubquery(&synonymTable, pk);
	callsStarsubquery118.setSynonyms("_", 2);
	ResultTuple* actualResultcallsStarsubquery118 = callsStarsubquery118.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultcallsStarsubquery118->getAllResults().size());
	CPPUNIT_ASSERT(actualResultcallsStarsubquery118->isBool());
	CPPUNIT_ASSERT(!actualResultcallsStarsubquery118->isEmpty());

	// Test 119: CallsStar(_, 6)
	CallsStarSubquery callsStarsubquery119 = CallsStarSubquery(&synonymTable, pk);
	callsStarsubquery119.setSynonyms("_", 6);
	ResultTuple* actualResultcallsStarsubquery119 = callsStarsubquery119.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultcallsStarsubquery119->getAllResults().size());
	CPPUNIT_ASSERT(actualResultcallsStarsubquery119->isBool());
	CPPUNIT_ASSERT(actualResultcallsStarsubquery119->isEmpty());

	// Test 125: CallsStar(1, proc2)
	CallsStarSubquery callsStarsubquery125 = CallsStarSubquery(&synonymTable, pk);
	callsStarsubquery125.setSynonyms(1, "proc2");
	ResultTuple* actualResultcallsStarsubquery125 = callsStarsubquery125.solve();
	int expectedResultcallsStarsubquery125[1][1] = {
		{2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultcallsStarsubquery125)/sizeof(expectedResultcallsStarsubquery125[0])), actualResultcallsStarsubquery125->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultcallsStarsubquery125)/sizeof(expectedResultcallsStarsubquery125[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultcallsStarsubquery125[i])/sizeof(expectedResultcallsStarsubquery125[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultcallsStarsubquery125[i][j], actualResultcallsStarsubquery125->getResultAt(i, j));
		}
	}

	// Test 129: CallsStar(1, _)
	CallsStarSubquery callsStarsubquery129 = CallsStarSubquery(&synonymTable, pk);
	callsStarsubquery129.setSynonyms(1, "_");
	ResultTuple* actualResultcallsStarsubquery129 = callsStarsubquery129.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultcallsStarsubquery129->getAllResults().size());
	CPPUNIT_ASSERT(actualResultcallsStarsubquery129->isBool());
	CPPUNIT_ASSERT(!actualResultcallsStarsubquery129->isEmpty());

	// Test 130: CallsStar(1, 2)
	CallsStarSubquery callsStarsubquery130 = CallsStarSubquery(&synonymTable, pk);
	callsStarsubquery130.setSynonyms(1, 2);
	ResultTuple* actualResultcallsStarsubquery130 = callsStarsubquery130.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultcallsStarsubquery130->getAllResults().size());
	CPPUNIT_ASSERT(actualResultcallsStarsubquery130->isBool());
	CPPUNIT_ASSERT(!actualResultcallsStarsubquery130->isEmpty());

	// Test 131: CallsStar(1, 6)
	CallsStarSubquery callsStarsubquery131 = CallsStarSubquery(&synonymTable, pk);
	callsStarsubquery131.setSynonyms(1, 6);
	ResultTuple* actualResultcallsStarsubquery131 = callsStarsubquery131.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultcallsStarsubquery131->getAllResults().size());
	CPPUNIT_ASSERT(actualResultcallsStarsubquery131->isBool());
	CPPUNIT_ASSERT(actualResultcallsStarsubquery131->isEmpty());

	// Test 137: CallsStar(5, proc2)
	CallsStarSubquery callsStarsubquery137 = CallsStarSubquery(&synonymTable, pk);
	callsStarsubquery137.setSynonyms(5, "proc2");
	ResultTuple* actualResultcallsStarsubquery137 = callsStarsubquery137.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultcallsStarsubquery137->getAllResults().size());
	
	// Test 141: CallsStar(5, _)
	CallsStarSubquery callsStarsubquery141 = CallsStarSubquery(&synonymTable, pk);
	callsStarsubquery141.setSynonyms(5, "_");
	ResultTuple* actualResultcallsStarsubquery141 = callsStarsubquery141.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultcallsStarsubquery141->getAllResults().size());
	CPPUNIT_ASSERT(actualResultcallsStarsubquery141->isBool());
	CPPUNIT_ASSERT(actualResultcallsStarsubquery141->isEmpty());

	// Test 142: CallsStar(5, 2)
	CallsStarSubquery callsStarsubquery142 = CallsStarSubquery(&synonymTable, pk);
	callsStarsubquery142.setSynonyms(5, 2);
	ResultTuple* actualResultcallsStarsubquery142 = callsStarsubquery142.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultcallsStarsubquery142->getAllResults().size());
	CPPUNIT_ASSERT(actualResultcallsStarsubquery142->isBool());
	CPPUNIT_ASSERT(actualResultcallsStarsubquery142->isEmpty());

	// Test 143: CallsStar(5, 6)
	CallsStarSubquery callsStarsubquery143 = CallsStarSubquery(&synonymTable, pk);
	callsStarsubquery143.setSynonyms(5, 6);
	ResultTuple* actualResultcallsStarsubquery143 = callsStarsubquery143.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultcallsStarsubquery143->getAllResults().size());
	CPPUNIT_ASSERT(actualResultcallsStarsubquery143->isBool());
	CPPUNIT_ASSERT(actualResultcallsStarsubquery143->isEmpty());

	// Test 144: CallsStar(0, 2)
	CallsStarSubquery callsStarsubquery144 = CallsStarSubquery(&synonymTable, pk);
	callsStarsubquery144.setSynonyms(0, 2);
	ResultTuple* actualResultcallsStarsubquery144 = callsStarsubquery144.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultcallsStarsubquery144->getAllResults().size());
	CPPUNIT_ASSERT(actualResultcallsStarsubquery144->isBool());
	CPPUNIT_ASSERT(!actualResultcallsStarsubquery144->isEmpty());
}

void SubqueryTest::testCallsTTuple(){
	// testTuple:
	//  s1  |  a1  |  w1  |  i2  |  c2  |  l1  |  const1  |  v1  |  proc1  |
	//  1   |  1   |  6   |  8   |  3   |  1   |  0       |  0   |  0      |
	//  1   |  2   |  6   |  8   |  3   |  1   |  0       |  0   |  0      |
	//  1   |  1   |  15  |  8   |  3   |  1   |  0       |  0   |  0      |
	//  1   |  2   |  6   |  13  |  3   |  1   |  0       |  0   |  0      |
	//  1   |  1   |  6   |  8   |  11  |  1   |  0       |  0   |  0      |
	//  8   |  2   |  6   |  8   |  3   |  7   |  0       |  0   |  0      |
	//  1   |  1   |  6   |  8   |  3   |  1   |  3       |  0   |  0      |
	//  3   |  2   |  6   |  8   |  3   |  1   |  0       |  2   |  0      |
	//  1   |  2   |  6   |  8   |  3   |  1   |  0       |  2   |  1      |
	ResultTuple testTuple = ResultTuple();
	int index = testTuple.addSynonym("s1");
	testTuple.addSynonymToMap("s1", index);
	index = testTuple.addSynonym("a1");
	testTuple.addSynonymToMap("a1", index);
	index = testTuple.addSynonym("w1");
	testTuple.addSynonymToMap("w1", index);
	index = testTuple.addSynonym("i2");
	testTuple.addSynonymToMap("i2", index);
	index = testTuple.addSynonym("c2");
	testTuple.addSynonymToMap("c2", index);
	index = testTuple.addSynonym("l1");
	testTuple.addSynonymToMap("l1", index);
	index = testTuple.addSynonym("const1");
	testTuple.addSynonymToMap("const1", index);
	index = testTuple.addSynonym("v1");
	testTuple.addSynonymToMap("v1", index);
	index = testTuple.addSynonym("proc1");
	testTuple.addSynonymToMap("proc1", index);
	int data[9][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	for (int i = 0; i < 9; i++){
		vector<int> tempVector = vector<int>();
		testTuple.addResultRow(tempVector);
		for (int j = 0; j < 9; j++){
			testTuple.addResult(i, data[i][j]);
		}
	}

	// Test 65: CallsStar(proc1, proc2)
	CallsStarSubquery callsStarsubquery65 = CallsStarSubquery(&synonymTable, pk);
	callsStarsubquery65.setSynonyms("proc1", "proc2");
	ResultTuple* actualResultcallsStarsubquery65 = callsStarsubquery65.solve(&testTuple);
	int expectedResultcallsStarsubquery65[15][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  2},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  1},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  1},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  2},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultcallsStarsubquery65)/sizeof(expectedResultcallsStarsubquery65[0])), actualResultcallsStarsubquery65->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultcallsStarsubquery65)/sizeof(expectedResultcallsStarsubquery65[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultcallsStarsubquery65[i])/sizeof(expectedResultcallsStarsubquery65[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultcallsStarsubquery65[i][j], actualResultcallsStarsubquery65->getResultAt(i, j));
		}
	}

	// Test 69: CallsStar(proc1, _)
	CallsStarSubquery callsStarsubquery69 = CallsStarSubquery(&synonymTable, pk);
	callsStarsubquery69.setSynonyms("proc1", "_");
	ResultTuple* actualResultcallsStarsubquery69 = callsStarsubquery69.solve(&testTuple);
	int expectedResultcallsStarsubquery69[8][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultcallsStarsubquery69)/sizeof(expectedResultcallsStarsubquery69[0])), actualResultcallsStarsubquery69->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultcallsStarsubquery69)/sizeof(expectedResultcallsStarsubquery69[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultcallsStarsubquery69[i])/sizeof(expectedResultcallsStarsubquery69[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultcallsStarsubquery69[i][j], actualResultcallsStarsubquery69->getResultAt(i, j));
		}
	}

	// Test 70: CallsStar(proc1, 2)
	CallsStarSubquery callsStarsubquery70 = CallsStarSubquery(&synonymTable, pk);
	callsStarsubquery70.setSynonyms("proc1", 2);
	ResultTuple* actualResultcallsStarsubquery70 = callsStarsubquery70.solve(&testTuple);
	int expectedResultcallsStarsubquery70[8][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultcallsStarsubquery70)/sizeof(expectedResultcallsStarsubquery70[0])), actualResultcallsStarsubquery70->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultcallsStarsubquery70)/sizeof(expectedResultcallsStarsubquery70[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultcallsStarsubquery70[i])/sizeof(expectedResultcallsStarsubquery70[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultcallsStarsubquery70[i][j], actualResultcallsStarsubquery70->getResultAt(i, j));
		}
	}
	
	// Test 71: CallsStar(proc1, 6)
	CallsStarSubquery callsStarsubquery71 = CallsStarSubquery(&synonymTable, pk);
	callsStarsubquery71.setSynonyms("proc1", 6);
	ResultTuple* actualResultcallsStarsubquery71 = callsStarsubquery71.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultcallsStarsubquery71->getAllResults().size());

	// Test 72: CallsStar(0, proc1)
	CallsStarSubquery callsStarsubquery72 = CallsStarSubquery(&synonymTable, pk);
	callsStarsubquery72.setSynonyms(0, "proc1");
	ResultTuple* actualResultcallsStarsubquery72 = callsStarsubquery72.solve(&testTuple);
	int expectedResultcallsStarsubquery72[2][9] = {
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultcallsStarsubquery72)/sizeof(expectedResultcallsStarsubquery72[0])), actualResultcallsStarsubquery72->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultcallsStarsubquery72)/sizeof(expectedResultcallsStarsubquery72[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultcallsStarsubquery72[i])/sizeof(expectedResultcallsStarsubquery72[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultcallsStarsubquery72[i][j], actualResultcallsStarsubquery72->getResultAt(i, j));
		}
	}

	// Test 73: CallsStar("_", proc1)
	CallsStarSubquery callsStarsubquery73 = CallsStarSubquery(&synonymTable, pk);
	callsStarsubquery73.setSynonyms("_", "proc1");
	ResultTuple* actualResultcallsStarsubquery73 = callsStarsubquery73.solve(&testTuple);
	int expectedResultcallsStarsubquery73[2][9] = {
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  2  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultcallsStarsubquery73)/sizeof(expectedResultcallsStarsubquery73[0])), actualResultcallsStarsubquery73->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultcallsStarsubquery73)/sizeof(expectedResultcallsStarsubquery73[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultcallsStarsubquery73[i])/sizeof(expectedResultcallsStarsubquery73[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultcallsStarsubquery73[i][j], actualResultcallsStarsubquery73->getResultAt(i, j));
		}
	}

	ResultTuple testTuple2 = ResultTuple();
	index = testTuple2.addSynonym("proc1");
	testTuple2.addSynonymToMap("proc1", index);
	index = testTuple2.addSynonym("proc2");
	testTuple2.addSynonymToMap("proc2", index);
	int data2[5][2] = {
		{0  ,  1  },
		{0  ,  0  },
		{1  ,  0  },
		{1  ,  2  },
		{2  ,  0  }
	};
	for (int i = 0; i < 5; i++){
		vector<int> tempVector = vector<int>();
		testTuple2.addResultRow(tempVector);
		for (int j = 0; j < 2; j++){
			testTuple2.addResult(i, data2[i][j]);
		}
	}

	// Test 75: CallsStar(proc1, proc2)
	CallsStarSubquery callsStarsubquery75 = CallsStarSubquery(&synonymTable, pk);
	callsStarsubquery75.setSynonyms("proc1", "proc2");
	ResultTuple* actualResultcallsStarsubquery75 = callsStarsubquery75.solve(&testTuple2);
	int expectedResultcallsStarsubquery75[2][2] = {
		{0, 1}, {1, 2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultcallsStarsubquery75)/sizeof(expectedResultcallsStarsubquery75[0])), actualResultcallsStarsubquery75->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultcallsStarsubquery75)/sizeof(expectedResultcallsStarsubquery75[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultcallsStarsubquery75[i])/sizeof(expectedResultcallsStarsubquery75[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultcallsStarsubquery75[i][j], actualResultcallsStarsubquery75->getResultAt(i, j));
		}
	}

	PKBController* pk2 = new PKBController();

	TNode stmt1("CALL_NODE", "Two", 1, 0);
	TNode stmt2("CALL_NODE", "Three", 2, 0);
	TNode stmt3("CALL_NODE", "Three", 3, 1);
	TNode stmt4("ASSIGN_NODE", "a = 1", 4, 2);
	pk2->statementTable.insertStatement(&stmt1);
	pk2->statementTable.insertStatement(&stmt2);
	pk2->statementTable.insertStatement(&stmt3);
	pk2->statementTable.insertStatement(&stmt4);

	pk2->procTable.insertProc("One");  // 0
	pk2->procTable.insertProc("Two"); // 1
	pk2->procTable.insertProc("Three");  // 2

	pk2->callsTable.insertCalls(0, 1);
	pk2->callsTable.insertCalls(0, 2);
	pk2->callsTable.insertCalls(1, 2);

	pk2->constructCalls();

	// Test 76: CallsStar(proc1, proc2)
	CallsStarSubquery callsStarsubquery76 = CallsStarSubquery(&synonymTable, pk2);
	callsStarsubquery76.setSynonyms("proc1", "proc2");
	ResultTuple* actualResultcallsStarsubquery76 = callsStarsubquery76.solve(&testTuple);
	int expectedResultcallsStarsubquery76[15][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  2},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  1},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  1},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  2},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultcallsStarsubquery76)/sizeof(expectedResultcallsStarsubquery76[0])), actualResultcallsStarsubquery76->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultcallsStarsubquery76)/sizeof(expectedResultcallsStarsubquery76[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultcallsStarsubquery76[i])/sizeof(expectedResultcallsStarsubquery76[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultcallsStarsubquery76[i][j], actualResultcallsStarsubquery76->getResultAt(i, j));
		}
	}
}

void SubqueryTest::testPattern(){
}

void SubqueryTest::testWith(){
	// Test 0: with s1.stmt# = s2.stmt#
	WithSubquery withsubquery0 = WithSubquery(&synonymTable, pk);
	withsubquery0.setSynonyms("s1", "s2");
	ResultTuple* actualResultwithsubquery0 = withsubquery0.solve();
	int expectedResultwithsubquery0[22][2] = {
		{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10}, {11, 11}, {12, 12}, {13, 13}, {14, 14}, {15, 15}, {16, 16}, {17, 17}, {18, 18}, {19, 19}, {20, 20}, {21, 21}, {22, 22}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery0)/sizeof(expectedResultwithsubquery0[0])), actualResultwithsubquery0->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery0)/sizeof(expectedResultwithsubquery0[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery0[i])/sizeof(expectedResultwithsubquery0[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery0[i][j], actualResultwithsubquery0->getResultAt(i, j));
		}
	}

	// Test 1: with s1.stmt# = a2.stmt#
	WithSubquery withsubquery1 = WithSubquery(&synonymTable, pk);
	withsubquery1.setSynonyms("s1", "a2");
	ResultTuple* actualResultwithsubquery1 = withsubquery1.solve();
	int expectedResultwithsubquery1[16][2] = {
		{1, 1}, {2, 2}, {4, 4}, {5, 5}, {7, 7}, {9, 9}, {10, 10}, {12, 12}, {14, 14}, {16, 16}, {17, 17}, {18, 18}, {19, 19}, {20, 20}, {21, 21}, {22, 22}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery1)/sizeof(expectedResultwithsubquery1[0])), actualResultwithsubquery1->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery1)/sizeof(expectedResultwithsubquery1[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery1[i])/sizeof(expectedResultwithsubquery1[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery1[i][j], actualResultwithsubquery1->getResultAt(i, j));
		}
	}

	// Test 2: with s1.stmt# = w2.stmt#
	WithSubquery withsubquery2 = WithSubquery(&synonymTable, pk);
	withsubquery2.setSynonyms("s1", "w2");
	ResultTuple* actualResultwithsubquery2 = withsubquery2.solve();
	int expectedResultwithsubquery2[2][2] = {
		{6, 6}, {15, 15}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery2)/sizeof(expectedResultwithsubquery2[0])), actualResultwithsubquery2->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery2)/sizeof(expectedResultwithsubquery2[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery2[i])/sizeof(expectedResultwithsubquery2[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery2[i][j], actualResultwithsubquery2->getResultAt(i, j));
		}
	}

	// Test 3: with s1.stmt# = i2.stmt#
	WithSubquery withsubquery3 = WithSubquery(&synonymTable, pk);
	withsubquery3.setSynonyms("s1", "i2");
	ResultTuple* actualResultwithsubquery3 = withsubquery3.solve();
	int expectedResultwithsubquery3[2][2] = {
		{8, 8}, {13, 13}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery3)/sizeof(expectedResultwithsubquery3[0])), actualResultwithsubquery3->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery3)/sizeof(expectedResultwithsubquery3[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery3[i])/sizeof(expectedResultwithsubquery3[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery3[i][j], actualResultwithsubquery3->getResultAt(i, j));
		}
	}

	// Test 6: with s1.stmt# = c2.stmt#
	WithSubquery withsubquery6 = WithSubquery(&synonymTable, pk);
	withsubquery6.setSynonyms("s1", "c2");
	ResultTuple* actualResultwithsubquery6 = withsubquery6.solve();
	int expectedResultwithsubquery6[2][2] = {
		{3, 3}, {11, 11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery6)/sizeof(expectedResultwithsubquery6[0])), actualResultwithsubquery6->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery6)/sizeof(expectedResultwithsubquery6[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery6[i])/sizeof(expectedResultwithsubquery6[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery6[i][j], actualResultwithsubquery6->getResultAt(i, j));
		}
	}

	// Test 7: with s1.stmt# = l2
	WithSubquery withsubquery7 = WithSubquery(&synonymTable, pk);
	withsubquery7.setSynonyms("s1", "l2");
	ResultTuple* actualResultwithsubquery7 = withsubquery7.solve();
	int expectedResultwithsubquery7[22][2] = {
		{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10}, {11, 11}, {12, 12}, {13, 13}, {14, 14}, {15, 15}, {16, 16}, {17, 17}, {18, 18}, {19, 19}, {20, 20}, {21, 21}, {22, 22}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery7)/sizeof(expectedResultwithsubquery7[0])), actualResultwithsubquery7->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery7)/sizeof(expectedResultwithsubquery7[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery7[i])/sizeof(expectedResultwithsubquery7[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery7[i][j], actualResultwithsubquery7->getResultAt(i, j));
		}
	}

	// Test 8: with s1.stmt# = const2.value
	WithSubquery withsubquery8 = WithSubquery(&synonymTable, pk);
	withsubquery8.setSynonyms("s1", "const2");
	ResultTuple* actualResultwithsubquery8 = withsubquery8.solve();
	int expectedResultwithsubquery8[4][2] = {
		{1, 4}, {2, 0}, {3, 1}, {5, 3}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery8)/sizeof(expectedResultwithsubquery8[0])), actualResultwithsubquery8->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery8)/sizeof(expectedResultwithsubquery8[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery8[i])/sizeof(expectedResultwithsubquery8[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery8[i][j], actualResultwithsubquery8->getResultAt(i, j));
		}
	}

	// Test 10: with s1.stmt# = 2
	WithSubquery withsubquery10 = WithSubquery(&synonymTable, pk);
	withsubquery10.setSynonyms("s1", 2);
	ResultTuple* actualResultwithsubquery10 = withsubquery10.solve();
	int expectedResultwithsubquery10[1][1] = {
		{2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery10)/sizeof(expectedResultwithsubquery10[0])), actualResultwithsubquery10->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery10)/sizeof(expectedResultwithsubquery10[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery10[i])/sizeof(expectedResultwithsubquery10[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery10[i][j], actualResultwithsubquery10->getResultAt(i, j));
		}
	}

	// Test 11: with s1.stmt# = 6
	WithSubquery withsubquery11 = WithSubquery(&synonymTable, pk);
	withsubquery11.setSynonyms("s1", 6);
	ResultTuple* actualResultwithsubquery11 = withsubquery11.solve();
	int expectedResultwithsubquery11[1][1] = {
		{6}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery11)/sizeof(expectedResultwithsubquery11[0])), actualResultwithsubquery11->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery11)/sizeof(expectedResultwithsubquery11[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery11[i])/sizeof(expectedResultwithsubquery11[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery11[i][j], actualResultwithsubquery11->getResultAt(i, j));
		}
	}

	// Test 12: with a1.stmt# = s2.stmt#
	WithSubquery withsubquery12 = WithSubquery(&synonymTable, pk);
	withsubquery12.setSynonyms("a1", "s2");
	ResultTuple* actualResultwithsubquery12 = withsubquery12.solve();
	int expectedResultwithsubquery12[16][2] = {
		{1, 1}, {2, 2}, {4, 4}, {5, 5}, {7, 7}, {9, 9}, {10, 10}, {12, 12}, {14, 14}, {16, 16}, {17, 17}, {18, 18}, {19, 19}, {20, 20}, {21, 21}, {22, 22}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery12)/sizeof(expectedResultwithsubquery12[0])), actualResultwithsubquery12->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery12)/sizeof(expectedResultwithsubquery12[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery12[i])/sizeof(expectedResultwithsubquery12[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery12[i][j], actualResultwithsubquery12->getResultAt(i, j));
		}
	}

	// Test 13: with a1.stmt# = a2.stmt#
	WithSubquery withsubquery13 = WithSubquery(&synonymTable, pk);
	withsubquery13.setSynonyms("a1", "a2");
	ResultTuple* actualResultwithsubquery13 = withsubquery13.solve();
	int expectedResultwithsubquery13[16][2] = {
		{1, 1}, {2, 2}, {4, 4}, {5, 5}, {7, 7}, {9, 9}, {10, 10}, {12, 12}, {14, 14}, {16, 16}, {17, 17}, {18, 18}, {19, 19}, {20, 20}, {21, 21}, {22, 22}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery13)/sizeof(expectedResultwithsubquery13[0])), actualResultwithsubquery13->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery13)/sizeof(expectedResultwithsubquery13[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery13[i])/sizeof(expectedResultwithsubquery13[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery13[i][j], actualResultwithsubquery13->getResultAt(i, j));
		}
	}

	// Test 14: with(a1, w2)
	WithSubquery withsubquery14 = WithSubquery(&synonymTable, pk);
	withsubquery14.setSynonyms("a1", "w2");
	ResultTuple* actualResultwithsubquery14 = withsubquery14.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery14->getAllResults().size());

	// Test 15: with(a1, i2)
	WithSubquery withsubquery15 = WithSubquery(&synonymTable, pk);
	withsubquery15.setSynonyms("a1", "i2");
	ResultTuple* actualResultwithsubquery15 = withsubquery15.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery15->getAllResults().size());

	// Test 18: with(a1, c2)
	WithSubquery withsubquery18 = WithSubquery(&synonymTable, pk);
	withsubquery18.setSynonyms("a1", "c2");
	ResultTuple* actualResultwithsubquery18 = withsubquery18.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery18->getAllResults().size());

	// Test 19: with(a1, l2)
	WithSubquery withsubquery19 = WithSubquery(&synonymTable, pk);
	withsubquery19.setSynonyms("a1", "l2");
	ResultTuple* actualResultwithsubquery19 = withsubquery19.solve();
	int expectedResultwithsubquery19[16][2] = {
		{1, 1}, {2, 2}, {4, 4}, {5, 5}, {7, 7}, {9, 9}, {10, 10}, {12, 12}, {14, 14}, {16, 16}, {17, 17}, {18, 18}, {19, 19}, {20, 20}, {21, 21}, {22, 22}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery19)/sizeof(expectedResultwithsubquery19[0])), actualResultwithsubquery19->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery19)/sizeof(expectedResultwithsubquery19[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery19[i])/sizeof(expectedResultwithsubquery19[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery19[i][j], actualResultwithsubquery19->getResultAt(i, j));
		}
	}

	// Test 20: with(a1, const2)
	WithSubquery withsubquery20 = WithSubquery(&synonymTable, pk);
	withsubquery20.setSynonyms("a1", "const2");
	ResultTuple* actualResultwithsubquery20 = withsubquery20.solve();
	int expectedResultwithsubquery20[3][2] = {
		{1, 4}, {2, 0}, {5, 3}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery20)/sizeof(expectedResultwithsubquery20[0])), actualResultwithsubquery20->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery20)/sizeof(expectedResultwithsubquery20[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery20[i])/sizeof(expectedResultwithsubquery20[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery20[i][j], actualResultwithsubquery20->getResultAt(i, j));
		}
	}

	// Test 22: with(a1, 2)
	WithSubquery withsubquery22 = WithSubquery(&synonymTable, pk);
	withsubquery22.setSynonyms("a1", 2);
	ResultTuple* actualResultwithsubquery22 = withsubquery22.solve();
	int expectedResultwithsubquery22[1][1] = {
		{2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery22)/sizeof(expectedResultwithsubquery22[0])), actualResultwithsubquery22->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery22)/sizeof(expectedResultwithsubquery22[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery22[i])/sizeof(expectedResultwithsubquery22[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery22[i][j], actualResultwithsubquery22->getResultAt(i, j));
		}
	}

	// Test 23: with(a1, 6)
	WithSubquery withsubquery23 = WithSubquery(&synonymTable, pk);
	withsubquery23.setSynonyms("a1", 6);
	ResultTuple* actualResultwithsubquery23 = withsubquery23.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery23->getAllResults().size());

	// Test 24: with(w1, s2)
	WithSubquery withsubquery24 = WithSubquery(&synonymTable, pk);
	withsubquery24.setSynonyms("w1", "s2");
	ResultTuple* actualResultwithsubquery24 = withsubquery24.solve();
	int expectedResultwithsubquery24[2][2] = {
		{6, 6}, {15, 15}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery24)/sizeof(expectedResultwithsubquery24[0])), actualResultwithsubquery24->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery24)/sizeof(expectedResultwithsubquery24[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery24[i])/sizeof(expectedResultwithsubquery24[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery24[i][j], actualResultwithsubquery24->getResultAt(i, j));
		}
	}

	// Test 25: with(w1, a2)
	WithSubquery withsubquery25 = WithSubquery(&synonymTable, pk);
	withsubquery25.setSynonyms("w1", "a2");
	ResultTuple* actualResultwithsubquery25 = withsubquery25.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery25->getAllResults().size());

	// Test 26: with(w1, w2)
	WithSubquery withsubquery26 = WithSubquery(&synonymTable, pk);
	withsubquery26.setSynonyms("w1", "w2");
	ResultTuple* actualResultwithsubquery26 = withsubquery26.solve();
	int expectedResultwithsubquery26[2][2] = {
		{6, 6}, {15, 15}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery26)/sizeof(expectedResultwithsubquery26[0])), actualResultwithsubquery26->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery26)/sizeof(expectedResultwithsubquery26[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery26[i])/sizeof(expectedResultwithsubquery26[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery26[i][j], actualResultwithsubquery26->getResultAt(i, j));
		}
	}

	// Test 27: with(w1, i2)
	WithSubquery withsubquery27 = WithSubquery(&synonymTable, pk);
	withsubquery27.setSynonyms("w1", "i2");
	ResultTuple* actualResultwithsubquery27 = withsubquery27.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery27->getAllResults().size());

	// Test 30: with(w1, c2)
	WithSubquery withsubquery30 = WithSubquery(&synonymTable, pk);
	withsubquery30.setSynonyms("w1", "c2");
	ResultTuple* actualResultwithsubquery30 = withsubquery30.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery30->getAllResults().size());

	// Test 31: with(w1, l2)
	WithSubquery withsubquery31 = WithSubquery(&synonymTable, pk);
	withsubquery31.setSynonyms("w1", "l2");
	ResultTuple* actualResultwithsubquery31 = withsubquery31.solve();
	int expectedResultwithsubquery31[2][2] = {
		{6, 6}, {15, 15}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery31)/sizeof(expectedResultwithsubquery31[0])), actualResultwithsubquery31->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery31)/sizeof(expectedResultwithsubquery31[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery31[i])/sizeof(expectedResultwithsubquery31[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery31[i][j], actualResultwithsubquery31->getResultAt(i, j));
		}
	}

	// Test 32: with(w1, const2)
	WithSubquery withsubquery32 = WithSubquery(&synonymTable, pk);
	withsubquery32.setSynonyms("w1", "const2");
	ResultTuple* actualResultwithsubquery32 = withsubquery32.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery32->getAllResults().size());

	// Test 34: with(w1, 2)
	WithSubquery withsubquery34 = WithSubquery(&synonymTable, pk);
	withsubquery34.setSynonyms("w1", 2);
	ResultTuple* actualResultwithsubquery34 = withsubquery34.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery34->getAllResults().size());

	// Test 35: with(w1, 6)
	WithSubquery withsubquery35 = WithSubquery(&synonymTable, pk);
	withsubquery35.setSynonyms("w1", 6);
	ResultTuple* actualResultwithsubquery35 = withsubquery35.solve();
	int expectedResultwithsubquery35[1][1] = {
		{6}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery35)/sizeof(expectedResultwithsubquery35[0])), actualResultwithsubquery35->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery35)/sizeof(expectedResultwithsubquery35[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery35[i])/sizeof(expectedResultwithsubquery35[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery35[i][j], actualResultwithsubquery35->getResultAt(i, j));
		}
	}

	// Test 36: with(i1, s2)
	WithSubquery withsubquery36 = WithSubquery(&synonymTable, pk);
	withsubquery36.setSynonyms("i1", "s2");
	ResultTuple* actualResultwithsubquery36 = withsubquery36.solve();
	int expectedResultwithsubquery36[2][2] = {
		{8, 8}, {13, 13}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery36)/sizeof(expectedResultwithsubquery36[0])), actualResultwithsubquery36->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery36)/sizeof(expectedResultwithsubquery36[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery36[i])/sizeof(expectedResultwithsubquery36[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery36[i][j], actualResultwithsubquery36->getResultAt(i, j));
		}
	}

	// Test 37: with(i1, a2)
	WithSubquery withsubquery37 = WithSubquery(&synonymTable, pk);
	withsubquery37.setSynonyms("i1", "a2");
	ResultTuple* actualResultwithsubquery37 = withsubquery37.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery37->getAllResults().size());

	// Test 38: with(i1, w2)
	WithSubquery withsubquery38 = WithSubquery(&synonymTable, pk);
	withsubquery38.setSynonyms("i1", "w2");
	ResultTuple* actualResultwithsubquery38 = withsubquery38.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery38->getAllResults().size());

	// Test 39: with(i1, i2)
	WithSubquery withsubquery39 = WithSubquery(&synonymTable, pk);
	withsubquery39.setSynonyms("i1", "i2");
	ResultTuple* actualResultwithsubquery39 = withsubquery39.solve();
	int expectedResultwithsubquery39[2][2] = {
		{8, 8}, {13, 13}
	};

	// Test 42: with(i1, c2)
	WithSubquery withsubquery42 = WithSubquery(&synonymTable, pk);
	withsubquery42.setSynonyms("i1", "c2");
	ResultTuple* actualResultwithsubquery42 = withsubquery42.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery42->getAllResults().size());

	// Test 43: with(i1, l2)
	WithSubquery withsubquery43 = WithSubquery(&synonymTable, pk);
	withsubquery43.setSynonyms("i1", "l2");
	ResultTuple* actualResultwithsubquery43 = withsubquery43.solve();
	int expectedResultwithsubquery43[2][2] = {
		{8, 8}, {13, 13}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery43)/sizeof(expectedResultwithsubquery43[0])), actualResultwithsubquery43->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery43)/sizeof(expectedResultwithsubquery43[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery43[i])/sizeof(expectedResultwithsubquery43[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery43[i][j], actualResultwithsubquery43->getResultAt(i, j));
		}
	}

	// Test 44: with(i1, const2)
	WithSubquery withsubquery44 = WithSubquery(&synonymTable, pk);
	withsubquery44.setSynonyms("i1", "const2");
	ResultTuple* actualResultwithsubquery44 = withsubquery44.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery44->getAllResults().size());

	// Test 46: with(i1, 2)
	WithSubquery withsubquery46 = WithSubquery(&synonymTable, pk);
	withsubquery46.setSynonyms("i1", 2);
	ResultTuple* actualResultwithsubquery46 = withsubquery46.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery46->getAllResults().size());

	// Test 47: with(i1, 6)
	WithSubquery withsubquery47 = WithSubquery(&synonymTable, pk);
	withsubquery47.setSynonyms("i1", 6);
	ResultTuple* actualResultwithsubquery47 = withsubquery47.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery47->getAllResults().size());

	// Test 52: with(v1, v2)
	WithSubquery withsubquery52 = WithSubquery(&synonymTable, pk);
	withsubquery52.setSynonyms("v1", "v2");
	ResultTuple* actualResultwithsubquery52 = withsubquery52.solve();
	int expectedResultwithsubquery52[8][2] = {
		{0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery52)/sizeof(expectedResultwithsubquery52[0])), actualResultwithsubquery52->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery52)/sizeof(expectedResultwithsubquery52[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery52[i])/sizeof(expectedResultwithsubquery52[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery52[i][j], actualResultwithsubquery52->getResultAt(i, j));
		}
	}

	// Test 53: with(v1, proc2)
	WithSubquery withsubquery53 = WithSubquery(&synonymTable, pk);
	withsubquery53.setSynonyms("v1", "proc2");
	ResultTuple* actualResultwithsubquery53 = withsubquery53.solve();
	int expectedResultwithsubquery53[1][2] = {
		{6, 1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery53)/sizeof(expectedResultwithsubquery53[0])), actualResultwithsubquery53->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery53)/sizeof(expectedResultwithsubquery53[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery53[i])/sizeof(expectedResultwithsubquery53[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery53[i][j], actualResultwithsubquery53->getResultAt(i, j));
		}
	}

	// Test 64: with(proc1, v2)
	WithSubquery withsubquery64 = WithSubquery(&synonymTable, pk);
	withsubquery64.setSynonyms("proc1", "v2");
	ResultTuple* actualResultwithsubquery64 = withsubquery64.solve();
	int expectedResultwithsubquery64[1][2] = {
		{1, 6}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery64)/sizeof(expectedResultwithsubquery64[0])), actualResultwithsubquery64->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery64)/sizeof(expectedResultwithsubquery64[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery64[i])/sizeof(expectedResultwithsubquery64[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery64[i][j], actualResultwithsubquery64->getResultAt(i, j));
		}
	}

	// Test 65: with(proc1, proc2)
	WithSubquery withsubquery65 = WithSubquery(&synonymTable, pk);
	withsubquery65.setSynonyms("proc1", "proc2");
	ResultTuple* actualResultwithsubquery65 = withsubquery65.solve();
	int expectedResultwithsubquery65[3][2] = {
		{0, 0}, {1, 1}, {2, 2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery65)/sizeof(expectedResultwithsubquery65[0])), actualResultwithsubquery65->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery65)/sizeof(expectedResultwithsubquery65[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery65[i])/sizeof(expectedResultwithsubquery65[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery65[i][j], actualResultwithsubquery65->getResultAt(i, j));
		}
	}

	// Test 72: with(c1, s2)
	WithSubquery withsubquery72 = WithSubquery(&synonymTable, pk);
	withsubquery72.setSynonyms("c1", "s2");
	ResultTuple* actualResultwithsubquery72 = withsubquery72.solve();
	int expectedResultwithsubquery72[2][2] = {
		{3, 3}, {11, 11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery72)/sizeof(expectedResultwithsubquery72[0])), actualResultwithsubquery72->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery72)/sizeof(expectedResultwithsubquery72[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery72[i])/sizeof(expectedResultwithsubquery72[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery72[i][j], actualResultwithsubquery72->getResultAt(i, j));
		}
	}

	// Test 73: with(c1, a2)
	WithSubquery withsubquery73 = WithSubquery(&synonymTable, pk);
	withsubquery73.setSynonyms("c1", "a2");
	ResultTuple* actualResultwithsubquery73 = withsubquery73.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery73->getAllResults().size());

	// Test 74: with(c1, w2)
	WithSubquery withsubquery74 = WithSubquery(&synonymTable, pk);
	withsubquery74.setSynonyms("c1", "w2");
	ResultTuple* actualResultwithsubquery74 = withsubquery74.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery74->getAllResults().size());

	// Test 75: with(c1, i2)
	WithSubquery withsubquery75 = WithSubquery(&synonymTable, pk);
	withsubquery75.setSynonyms("c1", "i2");
	ResultTuple* actualResultwithsubquery75 = withsubquery75.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery75->getAllResults().size());

	// Test 78: with(c1, c2)
	WithSubquery withsubquery78 = WithSubquery(&synonymTable, pk);
	withsubquery78.setSynonyms("c1", "c2");
	ResultTuple* actualResultwithsubquery78 = withsubquery78.solve();
	int expectedResultwithsubquery78[2][2] = {
		{3, 3}, {11, 11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery78)/sizeof(expectedResultwithsubquery78[0])), actualResultwithsubquery78->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery78)/sizeof(expectedResultwithsubquery78[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery78[i])/sizeof(expectedResultwithsubquery78[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery78[i][j], actualResultwithsubquery78->getResultAt(i, j));
		}
	}

	// Test 79: with(c1, l2)
	WithSubquery withsubquery79 = WithSubquery(&synonymTable, pk);
	withsubquery79.setSynonyms("c1", "l2");
	ResultTuple* actualResultwithsubquery79 = withsubquery79.solve();
	int expectedResultwithsubquery79[2][2] = {
		{3, 3}, {11, 11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery79)/sizeof(expectedResultwithsubquery79[0])), actualResultwithsubquery79->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery79)/sizeof(expectedResultwithsubquery79[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery79[i])/sizeof(expectedResultwithsubquery79[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery79[i][j], actualResultwithsubquery79->getResultAt(i, j));
		}
	}

	// Test 80: with(c1, const2)
	WithSubquery withsubquery80 = WithSubquery(&synonymTable, pk);
	withsubquery80.setSynonyms("c1", "const2");
	ResultTuple* actualResultwithsubquery80 = withsubquery80.solve();
	int expectedResultwithsubquery80[1][2] = {
		{3, 1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery80)/sizeof(expectedResultwithsubquery80[0])), actualResultwithsubquery80->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery80)/sizeof(expectedResultwithsubquery80[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery80[i])/sizeof(expectedResultwithsubquery80[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery80[i][j], actualResultwithsubquery80->getResultAt(i, j));
		}
	}

	// Test 82: with(c1, 2)
	WithSubquery withsubquery82 = WithSubquery(&synonymTable, pk);
	withsubquery82.setSynonyms("c1", 2);
	ResultTuple* actualResultwithsubquery82 = withsubquery82.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery82->getAllResults().size());

	// Test 83: with(c1, 6)
	WithSubquery withsubquery83 = WithSubquery(&synonymTable, pk);
	withsubquery83.setSynonyms("c1", 6);
	ResultTuple* actualResultwithsubquery83 = withsubquery83.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery83->getAllResults().size());

	// Test 84: with(l1, s2)
	WithSubquery withsubquery84 = WithSubquery(&synonymTable, pk);
	withsubquery84.setSynonyms("l1", "s2");
	ResultTuple* actualResultwithsubquery84 = withsubquery84.solve();
	int expectedResultwithsubquery84[22][2] = {
		{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10}, {11, 11}, {12, 12}, {13, 13}, {14, 14}, {15, 15}, {16, 16}, {17, 17}, {18, 18}, {19, 19}, {20, 20}, {21, 21}, {22, 22}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery84)/sizeof(expectedResultwithsubquery84[0])), actualResultwithsubquery84->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery84)/sizeof(expectedResultwithsubquery84[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery84[i])/sizeof(expectedResultwithsubquery84[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery84[i][j], actualResultwithsubquery84->getResultAt(i, j));
		}
	}

	// Test 85: with(l1, a2)
	WithSubquery withsubquery85 = WithSubquery(&synonymTable, pk);
	withsubquery85.setSynonyms("l1", "a2");
	ResultTuple* actualResultwithsubquery85 = withsubquery85.solve();
	int expectedResultwithsubquery85[16][2] = {
		{1, 1}, {2, 2}, {4, 4}, {5, 5}, {7, 7}, {9, 9}, {10, 10}, {12, 12}, {14, 14}, {16, 16}, {17, 17}, {18, 18}, {19, 19}, {20, 20}, {21, 21}, {22, 22}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery85)/sizeof(expectedResultwithsubquery85[0])), actualResultwithsubquery85->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery85)/sizeof(expectedResultwithsubquery85[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery85[i])/sizeof(expectedResultwithsubquery85[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery85[i][j], actualResultwithsubquery85->getResultAt(i, j));
		}
	}

	// Test 86: with(l1, w2)
	WithSubquery withsubquery86 = WithSubquery(&synonymTable, pk);
	withsubquery86.setSynonyms("l1", "w2");
	ResultTuple* actualResultwithsubquery86 = withsubquery86.solve();
	int expectedResultwithsubquery86[2][2] = {
		{6, 6}, {15, 15}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery86)/sizeof(expectedResultwithsubquery86[0])), actualResultwithsubquery86->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery86)/sizeof(expectedResultwithsubquery86[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery86[i])/sizeof(expectedResultwithsubquery86[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery86[i][j], actualResultwithsubquery86->getResultAt(i, j));
		}
	}

	// Test 87: with(l1, i2)
	WithSubquery withsubquery87 = WithSubquery(&synonymTable, pk);
	withsubquery87.setSynonyms("l1", "i2");
	ResultTuple* actualResultwithsubquery87 = withsubquery87.solve();
	int expectedResultwithsubquery87[2][2] = {
		{8, 8}, {13, 13}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery87)/sizeof(expectedResultwithsubquery87[0])), actualResultwithsubquery87->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery87)/sizeof(expectedResultwithsubquery87[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery87[i])/sizeof(expectedResultwithsubquery87[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery87[i][j], actualResultwithsubquery87->getResultAt(i, j));
		}
	}

	// Test 90: with(l1, c2)
	WithSubquery withsubquery90 = WithSubquery(&synonymTable, pk);
	withsubquery90.setSynonyms("l1", "c2");
	ResultTuple* actualResultwithsubquery90 = withsubquery90.solve();
	int expectedResultwithsubquery90[2][2] = {
		{3, 3}, {11, 11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery90)/sizeof(expectedResultwithsubquery90[0])), actualResultwithsubquery90->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery90)/sizeof(expectedResultwithsubquery90[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery90[i])/sizeof(expectedResultwithsubquery90[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery90[i][j], actualResultwithsubquery90->getResultAt(i, j));
		}
	}

	// Test 91: with(l1, l2)
	WithSubquery withsubquery91 = WithSubquery(&synonymTable, pk);
	withsubquery91.setSynonyms("l1", "l2");
	ResultTuple* actualResultwithsubquery91 = withsubquery91.solve();
	int expectedResultwithsubquery91[22][2] = {
		{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10}, {11, 11}, {12, 12}, {13, 13}, {14, 14}, {15, 15}, {16, 16}, {17, 17}, {18, 18}, {19, 19}, {20, 20}, {21, 21}, {22, 22}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery91)/sizeof(expectedResultwithsubquery91[0])), actualResultwithsubquery91->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery91)/sizeof(expectedResultwithsubquery91[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery91[i])/sizeof(expectedResultwithsubquery91[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery91[i][j], actualResultwithsubquery91->getResultAt(i, j));
		}
	}

	// Test 92: with(l1, const2)
	WithSubquery withsubquery92 = WithSubquery(&synonymTable, pk);
	withsubquery92.setSynonyms("l1", "const2");
	ResultTuple* actualResultwithsubquery92 = withsubquery92.solve();
	int expectedResultwithsubquery92[4][2] = {
		{1, 4}, {2, 0}, {3, 1}, {5, 3}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery92)/sizeof(expectedResultwithsubquery92[0])), actualResultwithsubquery92->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery92)/sizeof(expectedResultwithsubquery92[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery92[i])/sizeof(expectedResultwithsubquery92[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery92[i][j], actualResultwithsubquery92->getResultAt(i, j));
		}
	}

	// Test 94: with(l1, 2)
	WithSubquery withsubquery94 = WithSubquery(&synonymTable, pk);
	withsubquery94.setSynonyms("l1", 2);
	ResultTuple* actualResultwithsubquery94 = withsubquery94.solve();
	int expectedResultwithsubquery94[1][1] = {
		{2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery94)/sizeof(expectedResultwithsubquery94[0])), actualResultwithsubquery94->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery94)/sizeof(expectedResultwithsubquery94[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery94[i])/sizeof(expectedResultwithsubquery94[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery94[i][j], actualResultwithsubquery94->getResultAt(i, j));
		}
	}

	// Test 95: with(l1, 6)
	WithSubquery withsubquery95 = WithSubquery(&synonymTable, pk);
	withsubquery95.setSynonyms("l1", 6);
	ResultTuple* actualResultwithsubquery95 = withsubquery95.solve();
	int expectedResultwithsubquery95[1][1] = {
		{6}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery95)/sizeof(expectedResultwithsubquery95[0])), actualResultwithsubquery95->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery95)/sizeof(expectedResultwithsubquery95[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery95[i])/sizeof(expectedResultwithsubquery95[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery95[i][j], actualResultwithsubquery95->getResultAt(i, j));
		}
	}

		// Test 96: with(const1, s2)
	WithSubquery withsubquery96 = WithSubquery(&synonymTable, pk);
	withsubquery96.setSynonyms("const1", "s2");
	ResultTuple* actualResultwithsubquery96 = withsubquery96.solve();
	int expectedResultwithsubquery96[4][2] = {
		{0, 2}, {1, 3}, {3, 5}, {4, 1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery96)/sizeof(expectedResultwithsubquery96[0])), actualResultwithsubquery96->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery96)/sizeof(expectedResultwithsubquery96[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery96[i])/sizeof(expectedResultwithsubquery96[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery96[i][j], actualResultwithsubquery96->getResultAt(i, j));
		}
	}

	// Test 97: with(const1, a2)
	WithSubquery withsubquery97 = WithSubquery(&synonymTable, pk);
	withsubquery97.setSynonyms("const1", "a2");
	ResultTuple* actualResultwithsubquery97 = withsubquery97.solve();
	int expectedResultwithsubquery97[3][2] = {
		{0, 2}, {3, 5}, {4, 1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery97)/sizeof(expectedResultwithsubquery97[0])), actualResultwithsubquery97->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery97)/sizeof(expectedResultwithsubquery97[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery97[i])/sizeof(expectedResultwithsubquery97[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery97[i][j], actualResultwithsubquery97->getResultAt(i, j));
		}
	}

	// Test 98: with(const1, w2)
	WithSubquery withsubquery98 = WithSubquery(&synonymTable, pk);
	withsubquery98.setSynonyms("const1", "w2");
	ResultTuple* actualResultwithsubquery98 = withsubquery98.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery98->getAllResults().size());

	// Test 99: with(const1, i2)
	WithSubquery withsubquery99 = WithSubquery(&synonymTable, pk);
	withsubquery99.setSynonyms("const1", "i2");
	ResultTuple* actualResultwithsubquery99 = withsubquery99.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery99->getAllResults().size());

	// Test 102: with(const1, c2)
	WithSubquery withsubquery102 = WithSubquery(&synonymTable, pk);
	withsubquery102.setSynonyms("const1", "c2");
	ResultTuple* actualResultwithsubquery102 = withsubquery102.solve();
	int expectedResultwithsubquery102[1][2] = {
		{1, 3}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery102)/sizeof(expectedResultwithsubquery102[0])), actualResultwithsubquery102->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery102)/sizeof(expectedResultwithsubquery102[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery102[i])/sizeof(expectedResultwithsubquery102[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery102[i][j], actualResultwithsubquery102->getResultAt(i, j));
		}
	}

	// Test 103: with(const1, l2)
	WithSubquery withsubquery103 = WithSubquery(&synonymTable, pk);
	withsubquery103.setSynonyms("const1", "l2");
	ResultTuple* actualResultwithsubquery103 = withsubquery103.solve();
	int expectedResultwithsubquery103[4][2] = {
		{0, 2}, {1, 3}, {3, 5}, {4, 1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery103)/sizeof(expectedResultwithsubquery103[0])), actualResultwithsubquery103->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery103)/sizeof(expectedResultwithsubquery103[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery103[i])/sizeof(expectedResultwithsubquery103[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery103[i][j], actualResultwithsubquery103->getResultAt(i, j));
		}
	}

	// Test 104: with(const1, const2)
	WithSubquery withsubquery104 = WithSubquery(&synonymTable, pk);
	withsubquery104.setSynonyms("const1", "const2");
	ResultTuple* actualResultwithsubquery104 = withsubquery104.solve();
	int expectedResultwithsubquery104[5][2] = {
		{0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery104)/sizeof(expectedResultwithsubquery104[0])), actualResultwithsubquery104->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery104)/sizeof(expectedResultwithsubquery104[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery104[i])/sizeof(expectedResultwithsubquery104[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery104[i][j], actualResultwithsubquery104->getResultAt(i, j));
		}
	}

	// Test 106: with(const1, 2)
	WithSubquery withsubquery106 = WithSubquery(&synonymTable, pk);
	withsubquery106.setSynonyms("const1", 2);
	ResultTuple* actualResultwithsubquery106 = withsubquery106.solve();
	int expectedResultwithsubquery106[1][1] = {
		{0}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery106)/sizeof(expectedResultwithsubquery106[0])), actualResultwithsubquery106->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery106)/sizeof(expectedResultwithsubquery106[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery106[i])/sizeof(expectedResultwithsubquery106[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery106[i][j], actualResultwithsubquery106->getResultAt(i, j));
		}
	}

	// Test 107: with(const1, 6)
	WithSubquery withsubquery107 = WithSubquery(&synonymTable, pk);
	withsubquery107.setSynonyms("const1", 6);
	ResultTuple* actualResultwithsubquery107 = withsubquery107.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery107->getAllResults().size());

	// Test 120: with(1, s2)
	WithSubquery withsubquery120 = WithSubquery(&synonymTable, pk);
	withsubquery120.setSynonyms(1, "s2");
	ResultTuple* actualResultwithsubquery120 = withsubquery120.solve();
	int expectedResultwithsubquery120[1][1] = {
		{1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery120)/sizeof(expectedResultwithsubquery120[0])), actualResultwithsubquery120->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery120)/sizeof(expectedResultwithsubquery120[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery120[i])/sizeof(expectedResultwithsubquery120[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery120[i][j], actualResultwithsubquery120->getResultAt(i, j));
		}
	}

	// Test 121: with(1, a2)
	WithSubquery withsubquery121 = WithSubquery(&synonymTable, pk);
	withsubquery121.setSynonyms(1, "a2");
	ResultTuple* actualResultwithsubquery121 = withsubquery121.solve();
	int expectedResultwithsubquery121[1][1] = {
		{1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery121)/sizeof(expectedResultwithsubquery121[0])), actualResultwithsubquery121->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery121)/sizeof(expectedResultwithsubquery121[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery121[i])/sizeof(expectedResultwithsubquery121[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery121[i][j], actualResultwithsubquery121->getResultAt(i, j));
		}
	}

	// Test 122: with(1, w2)
	WithSubquery withsubquery122 = WithSubquery(&synonymTable, pk);
	withsubquery122.setSynonyms(1, "w2");
	ResultTuple* actualResultwithsubquery122 = withsubquery122.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery122->getAllResults().size());

	// Test 123: with(1, i2)
	WithSubquery withsubquery123 = WithSubquery(&synonymTable, pk);
	withsubquery123.setSynonyms(1, "i2");
	ResultTuple* actualResultwithsubquery123 = withsubquery123.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery123->getAllResults().size());

	// Test 126: with(1, c2)
	WithSubquery withsubquery126 = WithSubquery(&synonymTable, pk);
	withsubquery126.setSynonyms(1, "c2");
	ResultTuple* actualResultwithsubquery126 = withsubquery126.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery126->getAllResults().size());

	// Test 127: with(1, l2)
	WithSubquery withsubquery127 = WithSubquery(&synonymTable, pk);
	withsubquery127.setSynonyms(1, "l2");
	ResultTuple* actualResultwithsubquery127 = withsubquery127.solve();
	int expectedResultwithsubquery127[1][1] = {
		{1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery127)/sizeof(expectedResultwithsubquery127[0])), actualResultwithsubquery127->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery127)/sizeof(expectedResultwithsubquery127[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery127[i])/sizeof(expectedResultwithsubquery127[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery127[i][j], actualResultwithsubquery127->getResultAt(i, j));
		}
	}

	// Test 128: with(1, const2)
	WithSubquery withsubquery128 = WithSubquery(&synonymTable, pk);
	withsubquery128.setSynonyms(1, "const2");
	ResultTuple* actualResultwithsubquery128 = withsubquery128.solve();
	int expectedResultwithsubquery128[1][1] = {
		{4}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery128)/sizeof(expectedResultwithsubquery128[0])), actualResultwithsubquery128->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery128)/sizeof(expectedResultwithsubquery128[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery128[i])/sizeof(expectedResultwithsubquery128[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery128[i][j], actualResultwithsubquery128->getResultAt(i, j));
		}
	}

	// Test 130: with(1, 2)
	WithSubquery withsubquery130 = WithSubquery(&synonymTable, pk);
	withsubquery130.setSynonyms(1, 2);
	ResultTuple* actualResultwithsubquery130 = withsubquery130.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery130->getAllResults().size());
	CPPUNIT_ASSERT(actualResultwithsubquery130->isBool());
	CPPUNIT_ASSERT(actualResultwithsubquery130->isEmpty());

	// Test 131: with(1, 6)
	WithSubquery withsubquery131 = WithSubquery(&synonymTable, pk);
	withsubquery131.setSynonyms(1, 6);
	ResultTuple* actualResultwithsubquery131 = withsubquery131.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery131->getAllResults().size());
	CPPUNIT_ASSERT(actualResultwithsubquery131->isBool());
	CPPUNIT_ASSERT(actualResultwithsubquery131->isEmpty());

	// Test 134: with(6, w2)
	WithSubquery withsubquery134 = WithSubquery(&synonymTable, pk);
	withsubquery134.setSynonyms(6, "w2");
	ResultTuple* actualResultwithsubquery134 = withsubquery134.solve();
	int expectedResultwithsubquery134[1][1] = {
		{6}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery134)/sizeof(expectedResultwithsubquery134[0])), actualResultwithsubquery134->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery134)/sizeof(expectedResultwithsubquery134[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery134[i])/sizeof(expectedResultwithsubquery134[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery134[i][j], actualResultwithsubquery134->getResultAt(i, j));
		}
	}

	// Test 135: with(8, i2)
	WithSubquery withsubquery135 = WithSubquery(&synonymTable, pk);
	withsubquery135.setSynonyms(8, "i2");
	ResultTuple* actualResultwithsubquery135 = withsubquery135.solve();
	int expectedResultwithsubquery135[1][1] = {
		{8}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery135)/sizeof(expectedResultwithsubquery135[0])), actualResultwithsubquery135->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery135)/sizeof(expectedResultwithsubquery135[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery135[i])/sizeof(expectedResultwithsubquery135[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery135[i][j], actualResultwithsubquery135->getResultAt(i, j));
		}
	}

	// Test 138: with(3, c2)
	WithSubquery withsubquery138 = WithSubquery(&synonymTable, pk);
	withsubquery138.setSynonyms(3, "c2");
	ResultTuple* actualResultwithsubquery138 = withsubquery138.solve();
	int expectedResultwithsubquery138[1][1] = {
		{3}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery138)/sizeof(expectedResultwithsubquery138[0])), actualResultwithsubquery138->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery138)/sizeof(expectedResultwithsubquery138[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery138[i])/sizeof(expectedResultwithsubquery138[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery138[i][j], actualResultwithsubquery138->getResultAt(i, j));
		}
	}

	// Test 139: with(5, l2)
	WithSubquery withsubquery139 = WithSubquery(&synonymTable, pk);
	withsubquery139.setSynonyms(5, "l2");
	ResultTuple* actualResultwithsubquery139 = withsubquery139.solve();
	int expectedResultwithsubquery139[1][1] = {
		{5}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery139)/sizeof(expectedResultwithsubquery139[0])), actualResultwithsubquery139->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery139)/sizeof(expectedResultwithsubquery139[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery139[i])/sizeof(expectedResultwithsubquery139[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery139[i][j], actualResultwithsubquery139->getResultAt(i, j));
		}
	}

	// Test 140: with(5, const2)
	WithSubquery withsubquery140 = WithSubquery(&synonymTable, pk);
	withsubquery140.setSynonyms(5, "const2");
	ResultTuple* actualResultwithsubquery140 = withsubquery140.solve();
	int expectedResultwithsubquery140[1][1] = {
		{3}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery140)/sizeof(expectedResultwithsubquery140[0])), actualResultwithsubquery140->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery140)/sizeof(expectedResultwithsubquery140[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery140[i])/sizeof(expectedResultwithsubquery140[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery140[i][j], actualResultwithsubquery140->getResultAt(i, j));
		}
	}

	// Test 143: with(5, 5)
	WithSubquery withsubquery143 = WithSubquery(&synonymTable, pk);
	withsubquery143.setSynonyms(5, 5);
	ResultTuple* actualResultwithsubquery143 = withsubquery143.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery143->getAllResults().size());
	CPPUNIT_ASSERT(actualResultwithsubquery143->isBool());
	CPPUNIT_ASSERT(!actualResultwithsubquery143->isEmpty());
}

void SubqueryTest::testWithTuple(){
	// testTuple:
	//  s1  |  a1  |  w1  |  i2  |  c2  |  l1  |  const1  |  v1  |  proc1  |
	//  1   |  1   |  6   |  8   |  3   |  1   |  0       |  0   |  0      |
	//  1   |  2   |  6   |  8   |  3   |  1   |  0       |  0   |  0      |
	//  1   |  1   |  15  |  8   |  3   |  1   |  0       |  0   |  0      |
	//  1   |  2   |  6   |  13  |  3   |  1   |  0       |  0   |  0      |
	//  1   |  1   |  6   |  8   |  11  |  1   |  0       |  0   |  0      |
	//  8   |  2   |  6   |  8   |  3   |  7   |  0       |  0   |  0      |
	//  1   |  1   |  6   |  8   |  3   |  1   |  3       |  0   |  0      |
	//  3   |  2   |  6   |  8   |  3   |  1   |  0       |  2   |  0      |
	//  1   |  2   |  6   |  8   |  3   |  1   |  0       |  2   |  1      |
	ResultTuple testTuple = ResultTuple();
	int index = testTuple.addSynonym("s1");
	testTuple.addSynonymToMap("s1", index);
	index = testTuple.addSynonym("a1");
	testTuple.addSynonymToMap("a1", index);
	index = testTuple.addSynonym("w1");
	testTuple.addSynonymToMap("w1", index);
	index = testTuple.addSynonym("i2");
	testTuple.addSynonymToMap("i2", index);
	index = testTuple.addSynonym("c2");
	testTuple.addSynonymToMap("c2", index);
	index = testTuple.addSynonym("l1");
	testTuple.addSynonymToMap("l1", index);
	index = testTuple.addSynonym("const1");
	testTuple.addSynonymToMap("const1", index);
	index = testTuple.addSynonym("v1");
	testTuple.addSynonymToMap("v1", index);
	index = testTuple.addSynonym("proc1");
	testTuple.addSynonymToMap("proc1", index);
	int data[9][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  }
	};
	for (int i = 0; i < 9; i++){
		vector<int> tempVector = vector<int>();
		testTuple.addResultRow(tempVector);
		for (int j = 0; j < 9; j++){
			testTuple.addResult(i, data[i][j]);
		}
	}
	// Test 0: with s1.stmt# = s2.stmt#
	WithSubquery withsubquery0 = WithSubquery(&synonymTable, pk);
	withsubquery0.setSynonyms("s1", "s2");
	ResultTuple* actualResultwithsubquery0 = withsubquery0.solve(&testTuple);
	int expectedResultwithsubquery0[9][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  1},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  8},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  1},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  0  ,  3},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery0)/sizeof(expectedResultwithsubquery0[0])), actualResultwithsubquery0->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery0)/sizeof(expectedResultwithsubquery0[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery0[i])/sizeof(expectedResultwithsubquery0[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery0[i][j], actualResultwithsubquery0->getResultAt(i, j));
		}
	}

	// Test 1: with s1.stmt# = a2.stmt#
	WithSubquery withsubquery1 = WithSubquery(&synonymTable, pk);
	withsubquery1.setSynonyms("s1", "a2");
	ResultTuple* actualResultwithsubquery1 = withsubquery1.solve(&testTuple);
	int expectedResultwithsubquery1[7][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  1},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery1)/sizeof(expectedResultwithsubquery1[0])), actualResultwithsubquery1->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery1)/sizeof(expectedResultwithsubquery1[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery1[i])/sizeof(expectedResultwithsubquery1[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery1[i][j], actualResultwithsubquery1->getResultAt(i, j));
		}
	}

	// Test 2: with s1.stmt# = w2.stmt#
	WithSubquery withsubquery2 = WithSubquery(&synonymTable, pk);
	withsubquery2.setSynonyms("s1", "w2");
	ResultTuple* actualResultwithsubquery2 = withsubquery2.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery2->getAllResults().size());

	// Test 3: with s1.stmt# = i2.stmt#
	WithSubquery withsubquery3 = WithSubquery(&synonymTable, pk);
	withsubquery3.setSynonyms("s1", "i2");
	ResultTuple* actualResultwithsubquery3 = withsubquery3.solve(&testTuple);
	int expectedResultwithsubquery3[1][9] = {
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery3)/sizeof(expectedResultwithsubquery3[0])), actualResultwithsubquery3->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery3)/sizeof(expectedResultwithsubquery3[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery3[i])/sizeof(expectedResultwithsubquery3[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery3[i][j], actualResultwithsubquery3->getResultAt(i, j));
		}
	}

	// Test 6: with s1.stmt# = c2.stmt#
	WithSubquery withsubquery6 = WithSubquery(&synonymTable, pk);
	withsubquery6.setSynonyms("s1", "c2");
	ResultTuple* actualResultwithsubquery6 = withsubquery6.solve(&testTuple);
	int expectedResultwithsubquery6[1][9] = {
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  0  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery6)/sizeof(expectedResultwithsubquery6[0])), actualResultwithsubquery6->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery6)/sizeof(expectedResultwithsubquery6[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery6[i])/sizeof(expectedResultwithsubquery6[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery6[i][j], actualResultwithsubquery6->getResultAt(i, j));
		}
	}

	// Test 7: with s1.stmt# = l2
	WithSubquery withsubquery7 = WithSubquery(&synonymTable, pk);
	withsubquery7.setSynonyms("s1", "l2");
	ResultTuple* actualResultwithsubquery7 = withsubquery7.solve(&testTuple);
	int expectedResultwithsubquery7[9][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  1},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  8},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  1},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  0  ,  3},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery7)/sizeof(expectedResultwithsubquery7[0])), actualResultwithsubquery7->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery7)/sizeof(expectedResultwithsubquery7[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery7[i])/sizeof(expectedResultwithsubquery7[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery7[i][j], actualResultwithsubquery7->getResultAt(i, j));
		}
	}

	// Test 8: with s1.stmt# = const2.value
	WithSubquery withsubquery8 = WithSubquery(&synonymTable, pk);
	withsubquery8.setSynonyms("s1", "const2");
	ResultTuple* actualResultwithsubquery8 = withsubquery8.solve(&testTuple);
	int expectedResultwithsubquery8[8][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  4},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  4},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  0},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  4},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  4},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  4},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  0  ,  1},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  4}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery8)/sizeof(expectedResultwithsubquery8[0])), actualResultwithsubquery8->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery8)/sizeof(expectedResultwithsubquery8[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery8[i])/sizeof(expectedResultwithsubquery8[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery8[i][j], actualResultwithsubquery8->getResultAt(i, j));
		}
	}

	// Test 10: with s1.stmt# = 2
	WithSubquery withsubquery10 = WithSubquery(&synonymTable, pk);
	withsubquery10.setSynonyms("s1", 2);
	ResultTuple* actualResultwithsubquery10 = withsubquery10.solve(&testTuple);
	int expectedResultwithsubquery10[1][9] = {
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery10)/sizeof(expectedResultwithsubquery10[0])), actualResultwithsubquery10->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery10)/sizeof(expectedResultwithsubquery10[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery10[i])/sizeof(expectedResultwithsubquery10[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery10[i][j], actualResultwithsubquery10->getResultAt(i, j));
		}
	}

	// Test 11: with s1.stmt# = 6
	WithSubquery withsubquery11 = WithSubquery(&synonymTable, pk);
	withsubquery11.setSynonyms("s1", 6);
	ResultTuple* actualResultwithsubquery11 = withsubquery11.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery11->getAllResults().size());

	// Test 12: with a1.stmt# = s2.stmt#
	WithSubquery withsubquery12 = WithSubquery(&synonymTable, pk);
	withsubquery12.setSynonyms("a1", "s2");
	ResultTuple* actualResultwithsubquery12 = withsubquery12.solve(&testTuple);
	int expectedResultwithsubquery12[9][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  1},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  1},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  0  ,  2},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery12)/sizeof(expectedResultwithsubquery12[0])), actualResultwithsubquery12->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery12)/sizeof(expectedResultwithsubquery12[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery12[i])/sizeof(expectedResultwithsubquery12[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery12[i][j], actualResultwithsubquery12->getResultAt(i, j));
		}
	}

	// Test 13: with a1.stmt# = a2.stmt#
	WithSubquery withsubquery13 = WithSubquery(&synonymTable, pk);
	withsubquery13.setSynonyms("a1", "a2");
	ResultTuple* actualResultwithsubquery13 = withsubquery13.solve(&testTuple);
	int expectedResultwithsubquery13[9][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  1},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  1},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  0  ,  2},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery13)/sizeof(expectedResultwithsubquery13[0])), actualResultwithsubquery13->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery13)/sizeof(expectedResultwithsubquery13[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery13[i])/sizeof(expectedResultwithsubquery13[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery13[i][j], actualResultwithsubquery13->getResultAt(i, j));
		}
	}

	// Test 14: with(a1, w2)
	WithSubquery withsubquery14 = WithSubquery(&synonymTable, pk);
	withsubquery14.setSynonyms("a1", "w2");
	ResultTuple* actualResultwithsubquery14 = withsubquery14.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery14->getAllResults().size());

	// Test 15: with(a1, i2)
	WithSubquery withsubquery15 = WithSubquery(&synonymTable, pk);
	withsubquery15.setSynonyms("a1", "i2");
	ResultTuple* actualResultwithsubquery15 = withsubquery15.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery15->getAllResults().size());

	// Test 18: with(a1, c2)
	WithSubquery withsubquery18 = WithSubquery(&synonymTable, pk);
	withsubquery18.setSynonyms("a1", "c2");
	ResultTuple* actualResultwithsubquery18 = withsubquery18.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery18->getAllResults().size());

	// Test 19: with(a1, l2)
	WithSubquery withsubquery19 = WithSubquery(&synonymTable, pk);
	withsubquery19.setSynonyms("a1", "l2");
	ResultTuple* actualResultwithsubquery19 = withsubquery19.solve(&testTuple);
	int expectedResultwithsubquery19[9][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  1},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  1},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  0  ,  2},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery19)/sizeof(expectedResultwithsubquery19[0])), actualResultwithsubquery19->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery19)/sizeof(expectedResultwithsubquery19[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery19[i])/sizeof(expectedResultwithsubquery19[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery19[i][j], actualResultwithsubquery19->getResultAt(i, j));
		}
	}

	// Test 20: with(a1, const2)
	WithSubquery withsubquery20 = WithSubquery(&synonymTable, pk);
	withsubquery20.setSynonyms("a1", "const2");
	ResultTuple* actualResultwithsubquery20 = withsubquery20.solve(&testTuple);
	int expectedResultwithsubquery20[9][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  4},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  0},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  4},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  0},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  4},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  0},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  4},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  0  ,  0},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  0}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery20)/sizeof(expectedResultwithsubquery20[0])), actualResultwithsubquery20->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery20)/sizeof(expectedResultwithsubquery20[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery20[i])/sizeof(expectedResultwithsubquery20[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery20[i][j], actualResultwithsubquery20->getResultAt(i, j));
		}
	}

	// Test 22: with(a1, 2)
	WithSubquery withsubquery22 = WithSubquery(&synonymTable, pk);
	withsubquery22.setSynonyms("a1", 2);
	ResultTuple* actualResultwithsubquery22 = withsubquery22.solve(&testTuple);
	int expectedResultwithsubquery22[5][9] = {
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  0},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery22)/sizeof(expectedResultwithsubquery22[0])), actualResultwithsubquery22->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery22)/sizeof(expectedResultwithsubquery22[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery22[i])/sizeof(expectedResultwithsubquery22[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery22[i][j], actualResultwithsubquery22->getResultAt(i, j));
		}
	}

	// Test 23: with(a1, 6)
	WithSubquery withsubquery23 = WithSubquery(&synonymTable, pk);
	withsubquery23.setSynonyms("a1", 6);
	ResultTuple* actualResultwithsubquery23 = withsubquery23.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery23->getAllResults().size());

	// Test 24: with(w1, s2)
	WithSubquery withsubquery24 = WithSubquery(&synonymTable, pk);
	withsubquery24.setSynonyms("w1", "s2");
	ResultTuple* actualResultwithsubquery24 = withsubquery24.solve(&testTuple);
	int expectedResultwithsubquery24[9][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  6},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  6},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  15},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  6},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  6},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  6},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  6},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  0  ,  6},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  6}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery24)/sizeof(expectedResultwithsubquery24[0])), actualResultwithsubquery24->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery24)/sizeof(expectedResultwithsubquery24[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery24[i])/sizeof(expectedResultwithsubquery24[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery24[i][j], actualResultwithsubquery24->getResultAt(i, j));
		}
	}

	// Test 25: with(w1, a2)
	WithSubquery withsubquery25 = WithSubquery(&synonymTable, pk);
	withsubquery25.setSynonyms("w1", "a2");
	ResultTuple* actualResultwithsubquery25 = withsubquery25.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery25->getAllResults().size());

	// Test 26: with(w1, w2)
	WithSubquery withsubquery26 = WithSubquery(&synonymTable, pk);
	withsubquery26.setSynonyms("w1", "w2");
	ResultTuple* actualResultwithsubquery26 = withsubquery26.solve(&testTuple);
	int expectedResultwithsubquery26[9][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  6},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  6},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  15},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  6},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  6},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  6},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  6},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  0  ,  6},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  6}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery26)/sizeof(expectedResultwithsubquery26[0])), actualResultwithsubquery26->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery26)/sizeof(expectedResultwithsubquery26[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery26[i])/sizeof(expectedResultwithsubquery26[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery26[i][j], actualResultwithsubquery26->getResultAt(i, j));
		}
	}

	// Test 27: with(w1, i2)
	WithSubquery withsubquery27 = WithSubquery(&synonymTable, pk);
	withsubquery27.setSynonyms("w1", "i2");
	ResultTuple* actualResultwithsubquery27 = withsubquery27.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery27->getAllResults().size());

	// Test 30: with(w1, c2)
	WithSubquery withsubquery30 = WithSubquery(&synonymTable, pk);
	withsubquery30.setSynonyms("w1", "c2");
	ResultTuple* actualResultwithsubquery30 = withsubquery30.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery30->getAllResults().size());

	// Test 31: with(w1, l2)
	WithSubquery withsubquery31 = WithSubquery(&synonymTable, pk);
	withsubquery31.setSynonyms("w1", "l2");
	ResultTuple* actualResultwithsubquery31 = withsubquery31.solve(&testTuple);
	int expectedResultwithsubquery31[9][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  6},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  6},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  15},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  6},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  6},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  6},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  6},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  0  ,  6},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  6}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery31)/sizeof(expectedResultwithsubquery31[0])), actualResultwithsubquery31->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery31)/sizeof(expectedResultwithsubquery31[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery31[i])/sizeof(expectedResultwithsubquery31[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery31[i][j], actualResultwithsubquery31->getResultAt(i, j));
		}
	}

	// Test 32: with(w1, const2)
	WithSubquery withsubquery32 = WithSubquery(&synonymTable, pk);
	withsubquery32.setSynonyms("w1", "const2");
	ResultTuple* actualResultwithsubquery32 = withsubquery32.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery32->getAllResults().size());

	// Test 34: with(w1, 2)
	WithSubquery withsubquery34 = WithSubquery(&synonymTable, pk);
	withsubquery34.setSynonyms("w1", 2);
	ResultTuple* actualResultwithsubquery34 = withsubquery34.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery34->getAllResults().size());

	// Test 35: with(w1, 6)
	WithSubquery withsubquery35 = WithSubquery(&synonymTable, pk);
	withsubquery35.setSynonyms("w1", 6);
	ResultTuple* actualResultwithsubquery35 = withsubquery35.solve(&testTuple);
	int expectedResultwithsubquery35[8][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  0},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery35)/sizeof(expectedResultwithsubquery35[0])), actualResultwithsubquery35->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery35)/sizeof(expectedResultwithsubquery35[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery35[i])/sizeof(expectedResultwithsubquery35[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery35[i][j], actualResultwithsubquery35->getResultAt(i, j));
		}
	}

	// Test 39: with(i1, i2)
	WithSubquery withsubquery39 = WithSubquery(&synonymTable, pk);
	withsubquery39.setSynonyms("i1", "i2");
	ResultTuple* actualResultwithsubquery39 = withsubquery39.solve(&testTuple);
	int expectedResultwithsubquery39[9][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  8},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  8},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  8},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  13},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  8},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  8},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  8},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  0  ,  8},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  8}
	};

	// Test 42: with(i1, c2)
	WithSubquery withsubquery42 = WithSubquery(&synonymTable, pk);
	withsubquery42.setSynonyms("i1", "c2");
	ResultTuple* actualResultwithsubquery42 = withsubquery42.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery42->getAllResults().size());

	// Test 52: with(v1, v2)
	WithSubquery withsubquery52 = WithSubquery(&synonymTable, pk);
	withsubquery52.setSynonyms("v1", "v2");
	ResultTuple* actualResultwithsubquery52 = withsubquery52.solve(&testTuple);
	int expectedResultwithsubquery52[9][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  0},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  0},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  0},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  0},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  0},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  0},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  0},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  0  ,  2},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery52)/sizeof(expectedResultwithsubquery52[0])), actualResultwithsubquery52->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery52)/sizeof(expectedResultwithsubquery52[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery52[i])/sizeof(expectedResultwithsubquery52[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery52[i][j], actualResultwithsubquery52->getResultAt(i, j));
		}
	}

	// Test 53: with(v1, proc2)
	WithSubquery withsubquery53 = WithSubquery(&synonymTable, pk);
	withsubquery53.setSynonyms("v1", "proc2");
	ResultTuple* actualResultwithsubquery53 = withsubquery53.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery53->getAllResults().size());

	// Test 64: with(proc1, v2)
	WithSubquery withsubquery64 = WithSubquery(&synonymTable, pk);
	withsubquery64.setSynonyms("proc1", "v2");
	ResultTuple* actualResultwithsubquery64 = withsubquery64.solve(&testTuple);
	int expectedResultwithsubquery64[1][10] = {
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  6}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery64)/sizeof(expectedResultwithsubquery64[0])), actualResultwithsubquery64->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery64)/sizeof(expectedResultwithsubquery64[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery64[i])/sizeof(expectedResultwithsubquery64[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery64[i][j], actualResultwithsubquery64->getResultAt(i, j));
		}
	}

	// Test 65: with(proc1, proc2)
	WithSubquery withsubquery65 = WithSubquery(&synonymTable, pk);
	withsubquery65.setSynonyms("proc1", "proc2");
	ResultTuple* actualResultwithsubquery65 = withsubquery65.solve(&testTuple);
	int expectedResultwithsubquery65[9][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  0},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  0},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  0},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  0},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  0},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  0},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  0},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  0  ,  0},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery65)/sizeof(expectedResultwithsubquery65[0])), actualResultwithsubquery65->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery65)/sizeof(expectedResultwithsubquery65[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery65[i])/sizeof(expectedResultwithsubquery65[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery65[i][j], actualResultwithsubquery65->getResultAt(i, j));
		}
	}

	// Test 75: with(c1, i2)
	WithSubquery withsubquery75 = WithSubquery(&synonymTable, pk);
	withsubquery75.setSynonyms("c1", "i2");
	ResultTuple* actualResultwithsubquery75 = withsubquery75.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery75->getAllResults().size());

	// Test 78: with(c1, c2)
	WithSubquery withsubquery78 = WithSubquery(&synonymTable, pk);
	withsubquery78.setSynonyms("c1", "c2");
	ResultTuple* actualResultwithsubquery78 = withsubquery78.solve(&testTuple);
	int expectedResultwithsubquery78[9][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  3},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  3},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  3},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  3},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  11},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  3},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  3},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  0  ,  3},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  3}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery78)/sizeof(expectedResultwithsubquery78[0])), actualResultwithsubquery78->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery78)/sizeof(expectedResultwithsubquery78[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery78[i])/sizeof(expectedResultwithsubquery78[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery78[i][j], actualResultwithsubquery78->getResultAt(i, j));
		}
	}

	// Test 84: with(l1, s2)
	WithSubquery withsubquery84 = WithSubquery(&synonymTable, pk);
	withsubquery84.setSynonyms("l1", "s2");
	ResultTuple* actualResultwithsubquery84 = withsubquery84.solve(&testTuple);
	int expectedResultwithsubquery84[9][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  1},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  7},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  1},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  0  ,  1},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery84)/sizeof(expectedResultwithsubquery84[0])), actualResultwithsubquery84->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery84)/sizeof(expectedResultwithsubquery84[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery84[i])/sizeof(expectedResultwithsubquery84[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery84[i][j], actualResultwithsubquery84->getResultAt(i, j));
		}
	}

	// Test 85: with(l1, a2)
	WithSubquery withsubquery85 = WithSubquery(&synonymTable, pk);
	withsubquery85.setSynonyms("l1", "a2");
	ResultTuple* actualResultwithsubquery85 = withsubquery85.solve(&testTuple);
	int expectedResultwithsubquery85[9][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  1},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  7},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  1},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  0  ,  1},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery85)/sizeof(expectedResultwithsubquery85[0])), actualResultwithsubquery85->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery85)/sizeof(expectedResultwithsubquery85[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery85[i])/sizeof(expectedResultwithsubquery85[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery85[i][j], actualResultwithsubquery85->getResultAt(i, j));
		}
	}

	// Test 86: with(l1, w2)
	WithSubquery withsubquery86 = WithSubquery(&synonymTable, pk);
	withsubquery86.setSynonyms("l1", "w2");
	ResultTuple* actualResultwithsubquery86 = withsubquery86.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery86->getAllResults().size());

	// Test 87: with(l1, i2)
	WithSubquery withsubquery87 = WithSubquery(&synonymTable, pk);
	withsubquery87.setSynonyms("l1", "i2");
	ResultTuple* actualResultwithsubquery87 = withsubquery87.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery87->getAllResults().size());

	// Test 90: with(l1, c2)
	WithSubquery withsubquery90 = WithSubquery(&synonymTable, pk);
	withsubquery90.setSynonyms("l1", "c2");
	ResultTuple* actualResultwithsubquery90 = withsubquery90.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery90->getAllResults().size());

	// Test 91: with(l1, l2)
	WithSubquery withsubquery91 = WithSubquery(&synonymTable, pk);
	withsubquery91.setSynonyms("l1", "l2");
	ResultTuple* actualResultwithsubquery91 = withsubquery91.solve(&testTuple);
	int expectedResultwithsubquery91[9][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  1},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  1},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  7},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  1},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  0  ,  1},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery91)/sizeof(expectedResultwithsubquery91[0])), actualResultwithsubquery91->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery91)/sizeof(expectedResultwithsubquery91[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery91[i])/sizeof(expectedResultwithsubquery91[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery91[i][j], actualResultwithsubquery91->getResultAt(i, j));
		}
	}

	// Test 92: with(l1, const2)
	WithSubquery withsubquery92 = WithSubquery(&synonymTable, pk);
	withsubquery92.setSynonyms("l1", "const2");
	ResultTuple* actualResultwithsubquery92 = withsubquery92.solve(&testTuple);
	int expectedResultwithsubquery92[8][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  4},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  4},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  4},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  4},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  4},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  4},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  0  ,  4},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  4}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery92)/sizeof(expectedResultwithsubquery92[0])), actualResultwithsubquery92->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery92)/sizeof(expectedResultwithsubquery92[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery92[i])/sizeof(expectedResultwithsubquery92[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery92[i][j], actualResultwithsubquery92->getResultAt(i, j));
		}
	}

	// Test 94: with(l1, 2)
	WithSubquery withsubquery94 = WithSubquery(&synonymTable, pk);
	withsubquery94.setSynonyms("l1", 2);
	ResultTuple* actualResultwithsubquery94 = withsubquery94.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery94->getAllResults().size());

	// Test 95: with(l1, 6)
	WithSubquery withsubquery95 = WithSubquery(&synonymTable, pk);
	withsubquery95.setSynonyms("l1", 6);
	ResultTuple* actualResultwithsubquery95 = withsubquery95.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery95->getAllResults().size());

	// Test 96: with(const1, s2)
	WithSubquery withsubquery96 = WithSubquery(&synonymTable, pk);
	withsubquery96.setSynonyms("const1", "s2");
	ResultTuple* actualResultwithsubquery96 = withsubquery96.solve(&testTuple);
	int expectedResultwithsubquery96[9][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  2},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  5},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  0  ,  2},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery96)/sizeof(expectedResultwithsubquery96[0])), actualResultwithsubquery96->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery96)/sizeof(expectedResultwithsubquery96[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery96[i])/sizeof(expectedResultwithsubquery96[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery96[i][j], actualResultwithsubquery96->getResultAt(i, j));
		}
	}

	// Test 97: with(const1, a2)
	WithSubquery withsubquery97 = WithSubquery(&synonymTable, pk);
	withsubquery97.setSynonyms("const1", "a2");
	ResultTuple* actualResultwithsubquery97 = withsubquery97.solve(&testTuple);
	int expectedResultwithsubquery97[9][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  2},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  5},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  0  ,  2},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery97)/sizeof(expectedResultwithsubquery97[0])), actualResultwithsubquery97->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery97)/sizeof(expectedResultwithsubquery97[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery97[i])/sizeof(expectedResultwithsubquery97[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery97[i][j], actualResultwithsubquery97->getResultAt(i, j));
		}
	}

	// Test 98: with(const1, w2)
	WithSubquery withsubquery98 = WithSubquery(&synonymTable, pk);
	withsubquery98.setSynonyms("const1", "w2");
	ResultTuple* actualResultwithsubquery98 = withsubquery98.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery98->getAllResults().size());

	// Test 99: with(const1, i2)
	WithSubquery withsubquery99 = WithSubquery(&synonymTable, pk);
	withsubquery99.setSynonyms("const1", "i2");
	ResultTuple* actualResultwithsubquery99 = withsubquery99.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery99->getAllResults().size());

	// Test 102: with(const1, c2)
	WithSubquery withsubquery102 = WithSubquery(&synonymTable, pk);
	withsubquery102.setSynonyms("const1", "c2");
	ResultTuple* actualResultwithsubquery102 = withsubquery102.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery102->getAllResults().size());

	// Test 103: with(const1, l2)
	WithSubquery withsubquery103 = WithSubquery(&synonymTable, pk);
	withsubquery103.setSynonyms("const1", "l2");
	ResultTuple* actualResultwithsubquery103 = withsubquery103.solve(&testTuple);
	int expectedResultwithsubquery103[9][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  2},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  2},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  5},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  0  ,  2},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery103)/sizeof(expectedResultwithsubquery103[0])), actualResultwithsubquery103->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery103)/sizeof(expectedResultwithsubquery103[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery103[i])/sizeof(expectedResultwithsubquery103[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery103[i][j], actualResultwithsubquery103->getResultAt(i, j));
		}
	}

	// Test 104: with(const1, const2)
	WithSubquery withsubquery104 = WithSubquery(&synonymTable, pk);
	withsubquery104.setSynonyms("const1", "const2");
	ResultTuple* actualResultwithsubquery104 = withsubquery104.solve(&testTuple);
	int expectedResultwithsubquery104[9][10] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  0},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  0},
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  ,  0},
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  ,  0},
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  ,  0},
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  ,  0},
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  ,  3},
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  0  ,  0},
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  ,  0}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery104)/sizeof(expectedResultwithsubquery104[0])), actualResultwithsubquery104->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery104)/sizeof(expectedResultwithsubquery104[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery104[i])/sizeof(expectedResultwithsubquery104[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery104[i][j], actualResultwithsubquery104->getResultAt(i, j));
		}
	}

	// Test 106: with(const1, 2)
	WithSubquery withsubquery106 = WithSubquery(&synonymTable, pk);
	withsubquery106.setSynonyms("const1", 2);
	ResultTuple* actualResultwithsubquery106 = withsubquery106.solve(&testTuple);
	int expectedResultwithsubquery106[8][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery106)/sizeof(expectedResultwithsubquery106[0])), actualResultwithsubquery106->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery106)/sizeof(expectedResultwithsubquery106[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery106[i])/sizeof(expectedResultwithsubquery106[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery106[i][j], actualResultwithsubquery106->getResultAt(i, j));
		}
	}

	// Test 107: with(const1, 6)
	WithSubquery withsubquery107 = WithSubquery(&synonymTable, pk);
	withsubquery107.setSynonyms("const1", 6);
	ResultTuple* actualResultwithsubquery107 = withsubquery107.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery107->getAllResults().size());

	// Test 123: with(1, i2)
	WithSubquery withsubquery123 = WithSubquery(&synonymTable, pk);
	withsubquery123.setSynonyms(1, "i2");
	ResultTuple* actualResultwithsubquery123 = withsubquery123.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery123->getAllResults().size());

	// Test 126: with(1, c2)
	WithSubquery withsubquery126 = WithSubquery(&synonymTable, pk);
	withsubquery126.setSynonyms(1, "c2");
	ResultTuple* actualResultwithsubquery126 = withsubquery126.solve(&testTuple);
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultwithsubquery126->getAllResults().size());

	// Test 127: with(11, c2)
	WithSubquery withsubquery127 = WithSubquery(&synonymTable, pk);
	withsubquery127.setSynonyms(11, "c2");
	ResultTuple* actualResultwithsubquery127 = withsubquery127.solve(&testTuple);
	int expectedResultwithsubquery127[1][9] = {
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery127)/sizeof(expectedResultwithsubquery127[0])), actualResultwithsubquery127->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery127)/sizeof(expectedResultwithsubquery127[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery127[i])/sizeof(expectedResultwithsubquery127[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery127[i][j], actualResultwithsubquery127->getResultAt(i, j));
		}
	}

	// Test 128: with(1, i2)
	WithSubquery withsubquery128 = WithSubquery(&synonymTable, pk);
	withsubquery128.setSynonyms(8, "i2");
	ResultTuple* actualResultwithsubquery128 = withsubquery128.solve(&testTuple);
	int expectedResultwithsubquery128[8][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery128)/sizeof(expectedResultwithsubquery128[0])), actualResultwithsubquery128->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery128)/sizeof(expectedResultwithsubquery128[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery128[i])/sizeof(expectedResultwithsubquery128[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery128[i][j], actualResultwithsubquery128->getResultAt(i, j));
		}
	}

	// Test 134: with(6, w1)
	WithSubquery withsubquery134 = WithSubquery(&synonymTable, pk);
	withsubquery134.setSynonyms(6, "w1");
	ResultTuple* actualResultwithsubquery134 = withsubquery134.solve(&testTuple);
	int expectedResultwithsubquery134[8][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery134)/sizeof(expectedResultwithsubquery134[0])), actualResultwithsubquery134->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery134)/sizeof(expectedResultwithsubquery134[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery134[i])/sizeof(expectedResultwithsubquery134[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery134[i][j], actualResultwithsubquery134->getResultAt(i, j));
		}
	}

	// Test 135: with(8, i2)
	WithSubquery withsubquery135 = WithSubquery(&synonymTable, pk);
	withsubquery135.setSynonyms(8, "i2");
	ResultTuple* actualResultwithsubquery135 = withsubquery135.solve(&testTuple);
	int expectedResultwithsubquery135[8][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  11  ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery135)/sizeof(expectedResultwithsubquery135[0])), actualResultwithsubquery135->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery135)/sizeof(expectedResultwithsubquery135[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery135[i])/sizeof(expectedResultwithsubquery135[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery135[i][j], actualResultwithsubquery135->getResultAt(i, j));
		}
	}

	// Test 138: with(3, c2)
	WithSubquery withsubquery138 = WithSubquery(&synonymTable, pk);
	withsubquery138.setSynonyms(3, "c2");
	ResultTuple* actualResultwithsubquery138 = withsubquery138.solve(&testTuple);
	int expectedResultwithsubquery138[8][9] = {
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{2   ,  1   ,  15  ,  8   ,  3   ,  1   ,  0   ,  0   ,  0  },
		{1   ,  2   ,  6   ,  13  ,  3   ,  1   ,  0   ,  0   ,  0  },
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  },
		{1   ,  1   ,  6   ,  8   ,  3   ,  1   ,  3   ,  0   ,  0  },
		{3   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  0  },
		{1   ,  2   ,  6   ,  8   ,  3   ,  1   ,  0   ,  2   ,  1  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery138)/sizeof(expectedResultwithsubquery138[0])), actualResultwithsubquery138->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery138)/sizeof(expectedResultwithsubquery138[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery138[i])/sizeof(expectedResultwithsubquery138[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery138[i][j], actualResultwithsubquery138->getResultAt(i, j));
		}
	}

	// Test 139: with(7, l1)
	WithSubquery withsubquery139 = WithSubquery(&synonymTable, pk);
	withsubquery139.setSynonyms(7, "l1");
	ResultTuple* actualResultwithsubquery139 = withsubquery139.solve(&testTuple);
	int expectedResultwithsubquery139[1][9] = {
		{8   ,  2   ,  6   ,  8   ,  3   ,  7   ,  0   ,  0   ,  0  }
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultwithsubquery139)/sizeof(expectedResultwithsubquery139[0])), actualResultwithsubquery139->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultwithsubquery139)/sizeof(expectedResultwithsubquery139[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultwithsubquery139[i])/sizeof(expectedResultwithsubquery139[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultwithsubquery139[i][j], actualResultwithsubquery139->getResultAt(i, j));
		}
	}
}

void SubqueryTest::testNext() {
	NextSubquery nextSubqueryX = NextSubquery(&synonymTable, pk);
	nextSubqueryX.setSynonyms(1 , 2);
	ResultTuple* actualResultsNextSubqueryX = nextSubqueryX.solve();
	CPPUNIT_ASSERT_EQUAL(true, actualResultsNextSubqueryX->isBool());
	CPPUNIT_ASSERT_EQUAL(false, actualResultsNextSubqueryX->isEmpty());
	
	NextSubquery nextSubqueryX1 = NextSubquery(&synonymTable, pk);
	nextSubqueryX1.setSynonyms(6 , 13);
	ResultTuple* actualResultsNextSubqueryX1 = nextSubqueryX1.solve();
	CPPUNIT_ASSERT_EQUAL(true, actualResultsNextSubqueryX1->isBool());
	CPPUNIT_ASSERT_EQUAL(false, actualResultsNextSubqueryX1->isEmpty());

	NextSubquery nextSubqueryX2 = NextSubquery(&synonymTable, pk);
	nextSubqueryX2.setSynonyms(1 , 22);
	ResultTuple* actualResultsNextSubqueryX2 = nextSubqueryX2.solve();
	CPPUNIT_ASSERT_EQUAL(true, actualResultsNextSubqueryX2->isBool());
	CPPUNIT_ASSERT_EQUAL(true, actualResultsNextSubqueryX2->isEmpty());
	
	NextSubquery nextSubqueryX3 = NextSubquery(&synonymTable, pk);
	nextSubqueryX3.setSynonyms(6 , 9);
	ResultTuple* actualResultsNextSubqueryX3 = nextSubqueryX3.solve();
	CPPUNIT_ASSERT_EQUAL(true, actualResultsNextSubqueryX3->isBool());
	CPPUNIT_ASSERT_EQUAL(true, actualResultsNextSubqueryX3->isEmpty());
	
	NextSubquery nextSubqueryX4 = NextSubquery(&synonymTable, pk);
	nextSubqueryX4.setSynonyms("_" , 9);
	ResultTuple* actualResultsNextSubqueryX4 = nextSubqueryX4.solve();
	CPPUNIT_ASSERT_EQUAL(true, actualResultsNextSubqueryX4->isBool());
	CPPUNIT_ASSERT_EQUAL(false, actualResultsNextSubqueryX4->isEmpty());

	// Test 1: Next(s1, s2)
	NextSubquery nextSubquery1 = NextSubquery(&synonymTable, pk);
	nextSubquery1.setSynonyms("s1", "s2");
	ResultTuple* actualResultsNextSubquery1 = nextSubquery1.solve();
	int expectedResultsNextSubquery1[23][2] = {
		{1, 2}, {2, 3}, {4, 5}, {5, 6}, {6, 7}, {6, 13}, 
		{7, 8}, {8, 9}, {8, 10}, {9, 11}, {10, 11}, {11, 12},
		{12, 6}, {13, 14}, {13, 17}, {14, 15}, {15, 16}, {15, 18},
		{16, 15}, {17, 18}, {18, 19}, {19, 20}, {21, 22} 
	};
	CPPUNIT_ASSERT_EQUAL((size_t)23, actualResultsNextSubquery1->getAllResults().size());
	for (size_t i = 0; i < 23; i++){
		for (size_t j = 0; j < 2; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsNextSubquery1[i][j], actualResultsNextSubquery1->getResultAt(i, j));
		}
	}

	// Test 2: Next(s1, 18)
	NextSubquery nextSubquery2 = NextSubquery(&synonymTable, pk);
	nextSubquery2.setSynonyms("s1", 18);
	ResultTuple* actualResultsNextSubquery2 = nextSubquery2.solve();
	int expectedResultsNextSubquery2[2][1] = {
		{15}, {17} 
	};
	cout << actualResultsNextSubquery2->toString();
	CPPUNIT_ASSERT_EQUAL((size_t)2, actualResultsNextSubquery2->getAllResults().size());
	for (size_t i = 0; i < 2; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsNextSubquery2[i][j], actualResultsNextSubquery2->getResultAt(i, j));
		}
	}

	// Test 3: Next(s1, _)
	NextSubquery nextSubquery3 = NextSubquery(&synonymTable, pk);
	nextSubquery3.setSynonyms("s1", "_");
	ResultTuple* actualResultsNextSubquery3 = nextSubquery3.solve();
	cout << endl << actualResultsNextSubquery3->toString() << endl;
	int expectedResultsNextSubquery3[19][1] = {
		{1}, {2}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}, {13}, {14}, {15}, {16}, {17}, {18}, {19}, {21}
	};
	CPPUNIT_ASSERT_EQUAL((size_t)19, actualResultsNextSubquery3->getAllResults().size());
	for (size_t i = 0; i < 19; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsNextSubquery3[i][j], actualResultsNextSubquery3->getResultAt(i, j));
		}
	}	
	
	// Test 4: Next(a1, _)
	NextSubquery nextSubquery4 = NextSubquery(&synonymTable, pk);
	nextSubquery4.setSynonyms("a1", "_");
	ResultTuple* actualResultsNextSubquery4 = nextSubquery4.solve();
	int expectedResultsNextSubquery4[14][1] = {
		{1}, {2}, {4}, {5}, {7}, {9}, {10}, {12}, {14}, {16}, {17}, {18}, {19}, {21}
	};
	CPPUNIT_ASSERT_EQUAL((size_t)14, actualResultsNextSubquery4->getAllResults().size());
	for (size_t i = 0; i < 14; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsNextSubquery4[i][j], actualResultsNextSubquery4->getResultAt(i, j));
		}
	}

	// Test 5: Next(2,s1)
	NextSubquery nextSubquery5 = NextSubquery(&synonymTable, pk);
	nextSubquery5.setSynonyms(2, "s1");
	ResultTuple* actualResultsNextSubquery5 = nextSubquery5.solve();
	int expectedResultsNextSubquery5[1][1] = {
		{3}
	};
	CPPUNIT_ASSERT_EQUAL((size_t)1, actualResultsNextSubquery5->getAllResults().size());
	for (size_t i = 0; i < 1; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsNextSubquery5[i][j], actualResultsNextSubquery5->getResultAt(i, j));
		}
	}

	// Test 6: Next(1,"a1")
	NextSubquery nextSubquery6 = NextSubquery(&synonymTable, pk);
	nextSubquery6.setSynonyms(1, "a1");
	ResultTuple* actualResultsNextSubquery6 = nextSubquery6.solve();
	int expectedResultsNextSubquery6[1][1] = {
		{2}
	};
	CPPUNIT_ASSERT_EQUAL((size_t)1, actualResultsNextSubquery6->getAllResults().size());
	for (size_t i = 0; i < 1; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsNextSubquery6[i][j], actualResultsNextSubquery6->getResultAt(i, j));
		}
	}
	
	// Test 7: Next(_,s1)
	NextSubquery nextSubquery7 = NextSubquery(&synonymTable, pk);
	nextSubquery7.setSynonyms("_", "s1");
	ResultTuple* actualResultsNextSubquery7 = nextSubquery7.solve();
	int expectedResultsNextSubquery7[19][1] = {
		{2}, {3}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}, {13}, {14}, {15}, {16}, {17}, {18}, {19}, {20}, {22}
	};
	CPPUNIT_ASSERT_EQUAL((size_t)19, actualResultsNextSubquery7->getAllResults().size());
	for (size_t i = 0; i < 19; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsNextSubquery7[i][j], actualResultsNextSubquery7->getResultAt(i, j));
		}
	}

		//Test 8 : Next(_,a1)
	NextSubquery nextSubquery8 = NextSubquery(&synonymTable, pk);
	nextSubquery8.setSynonyms("_", "a1");
	ResultTuple* actualResultsNextSubquery8 = nextSubquery8.solve();
	int expectedResultsNextSubquery8[13][1] = {
		{2}, {5}, {7}, {9}, {10}, {12}, {14}, {16}, {17}, {18}, {19}, {20}, {22}
	};
	CPPUNIT_ASSERT_EQUAL((size_t)13, actualResultsNextSubquery8->getAllResults().size());
	for (size_t i = 0; i < 13; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsNextSubquery8[i][j], actualResultsNextSubquery8->getResultAt(i, j));
		}
	}

	// Test 1: Next(s1, a2)
	NextSubquery nextsubquery1 = NextSubquery(&synonymTable, pk);
	nextsubquery1.setSynonyms("s1", "a2");
	ResultTuple* actualResultnextsubquery1 = nextsubquery1.solve();
	int expectedResultnextsubquery1[14][2] = {
		{1, 2}, {4, 5}, {6, 7}, {8, 9}, {8, 10}, {11, 12}, {13, 14}, {13, 17}, {15, 16}, {15, 18}, {17, 18}, {18, 19}, {19, 20}, {21, 22} 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery1)/sizeof(expectedResultnextsubquery1[0])), actualResultnextsubquery1->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery1)/sizeof(expectedResultnextsubquery1[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery1[i])/sizeof(expectedResultnextsubquery1[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery1[i][j], actualResultnextsubquery1->getResultAt(i, j));
		}
	}

	// Test 2: Next(s1, w2)
	NextSubquery nextsubquery2 = NextSubquery(&synonymTable, pk);
	nextsubquery2.setSynonyms("s1", "w2");
	ResultTuple* actualResultnextsubquery2 = nextsubquery2.solve();
	int expectedResultnextsubquery2[4][2] = {
		{5, 6}, {12, 6}, {14, 15},{16, 15}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery2)/sizeof(expectedResultnextsubquery2[0])), actualResultnextsubquery2->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery2)/sizeof(expectedResultnextsubquery2[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery2[i])/sizeof(expectedResultnextsubquery2[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery2[i][j], actualResultnextsubquery2->getResultAt(i, j));
		}
	}

	// Test 3: Next(s1, i2)
	NextSubquery nextsubquery3 = NextSubquery(&synonymTable, pk);
	nextsubquery3.setSynonyms("s1", "i2");
	ResultTuple* actualResultnextsubquery3 = nextsubquery3.solve();
	int expectedResultnextsubquery3[2][2] = {
		{6, 13}, {7, 8} 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery3)/sizeof(expectedResultnextsubquery3[0])), actualResultnextsubquery3->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery3)/sizeof(expectedResultnextsubquery3[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery3[i])/sizeof(expectedResultnextsubquery3[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery3[i][j], actualResultnextsubquery3->getResultAt(i, j));
		}
	}

	// Test 6: Next(s1, c2)
	NextSubquery nextsubquery6 = NextSubquery(&synonymTable, pk);
	nextsubquery6.setSynonyms("s1", "c2");
	ResultTuple* actualResultnextsubquery6 = nextsubquery6.solve();
	int expectedResultnextsubquery6[3][2] = {
		{2, 3}, {9, 11}, {10, 11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery6)/sizeof(expectedResultnextsubquery6[0])), actualResultnextsubquery6->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery6)/sizeof(expectedResultnextsubquery6[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery6[i])/sizeof(expectedResultnextsubquery6[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery6[i][j], actualResultnextsubquery6->getResultAt(i, j));
		}
	}

	// Test 7: Next(s1, l2)
	NextSubquery nextsubquery7 = NextSubquery(&synonymTable, pk);
	nextsubquery7.setSynonyms("s1", "l2");
	ResultTuple* actualResultnextsubquery7 = nextsubquery7.solve();
	int expectedResultnextsubquery7[23][2] = {
		{1, 2}, {2, 3}, {4, 5}, {5, 6}, {6, 7}, {6, 13}, {7, 8}, {8, 9}, {8, 10}, {9, 11}, {10, 11}, {11, 12},{12, 6}, {13, 14}, {13, 17}, {14, 15}, {15, 16}, {15, 18},{16, 15}, {17, 18}, {18, 19}, {19, 20}, {21, 22} 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery7)/sizeof(expectedResultnextsubquery7[0])), actualResultnextsubquery7->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery7)/sizeof(expectedResultnextsubquery7[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery7[i])/sizeof(expectedResultnextsubquery7[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery7[i][j], actualResultnextsubquery7->getResultAt(i, j));
		}
	}

	// Test 9: Next(s1, _)
	NextSubquery nextsubquery9 = NextSubquery(&synonymTable, pk);
	nextsubquery9.setSynonyms("s1", "_");
	ResultTuple* actualResultnextsubquery9 = nextsubquery9.solve();
	int expectedResultnextsubquery9[19][1] = {
		{1}, {2}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}, {13}, {14}, {15}, {16}, {17}, {18}, {19}, {21}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery9)/sizeof(expectedResultnextsubquery9[0])), actualResultnextsubquery9->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery9)/sizeof(expectedResultnextsubquery9[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery9[i])/sizeof(expectedResultnextsubquery9[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery9[i][j], actualResultnextsubquery9->getResultAt(i, j));
		}
	}

	// Test 10: Next(s1, 2)
	NextSubquery nextsubquery10 = NextSubquery(&synonymTable, pk);
	nextsubquery10.setSynonyms("s1", 2);
	ResultTuple* actualResultnextsubquery10 = nextsubquery10.solve();
	int expectedResultnextsubquery10[1][1] = {
		{1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery10)/sizeof(expectedResultnextsubquery10[0])), actualResultnextsubquery10->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery10)/sizeof(expectedResultnextsubquery10[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery10[i])/sizeof(expectedResultnextsubquery10[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery10[i][j], actualResultnextsubquery10->getResultAt(i, j));
		}
	}

	// Test 11: Next(s1, 6)
	NextSubquery nextsubquery11 = NextSubquery(&synonymTable, pk);
	nextsubquery11.setSynonyms("s1", 6);
	ResultTuple* actualResultnextsubquery11 = nextsubquery11.solve();
	int expectedResultnextsubquery11[2][1] = {
		{5}, {12}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery11)/sizeof(expectedResultnextsubquery11[0])), actualResultnextsubquery11->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery11)/sizeof(expectedResultnextsubquery11[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery11[i])/sizeof(expectedResultnextsubquery11[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery11[i][j], actualResultnextsubquery11->getResultAt(i, j));
		}
	}

	// Test 12: Next(a1, s2)
	NextSubquery nextsubquery12 = NextSubquery(&synonymTable, pk);
	nextsubquery12.setSynonyms("a1", "s2");
	ResultTuple* actualResultnextsubquery12 = nextsubquery12.solve();
	int expectedResultnextsubquery12[14][2] = {
		{1, 2}, {2, 3}, {4, 5}, {5, 6}, {7, 8}, {9, 11}, {10, 11}, {12, 6}, {14, 15}, {16, 15}, {17, 18}, {18, 19}, {19, 20}, {21, 22} 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery12)/sizeof(expectedResultnextsubquery12[0])), actualResultnextsubquery12->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery12)/sizeof(expectedResultnextsubquery12[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery12[i])/sizeof(expectedResultnextsubquery12[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery12[i][j], actualResultnextsubquery12->getResultAt(i, j));
		}
	}

	// Test 13: Next(a1, a2)
	NextSubquery nextsubquery13 = NextSubquery(&synonymTable, pk);
	nextsubquery13.setSynonyms("a1", "a2");
	ResultTuple* actualResultnextsubquery13 = nextsubquery13.solve();
	int expectedResultnextsubquery13[6][2] = {
		{1, 2}, {4, 5}, {17, 18}, {18, 19}, {19, 20}, {21, 22} 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery13)/sizeof(expectedResultnextsubquery13[0])), actualResultnextsubquery13->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery13)/sizeof(expectedResultnextsubquery13[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery13[i])/sizeof(expectedResultnextsubquery13[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery13[i][j], actualResultnextsubquery13->getResultAt(i, j));
		}
	}

	
	// Test 14: Next(a1, w2)
	NextSubquery nextsubquery14 = NextSubquery(&synonymTable, pk);
	nextsubquery14.setSynonyms("a1", "w2");
	ResultTuple* actualResultnextsubquery14 = nextsubquery14.solve();
	int expectedResultnextsubquery14[4][2] = {
		{5, 6}, {12, 6}, {14, 15}, {16, 15}
	
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery14)/sizeof(expectedResultnextsubquery14[0])), actualResultnextsubquery14->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery14)/sizeof(expectedResultnextsubquery14[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery14[i])/sizeof(expectedResultnextsubquery14[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery14[i][j], actualResultnextsubquery14->getResultAt(i, j));
		}
	}

	// Test 15: Next(a1, i2)
	NextSubquery nextsubquery15 = NextSubquery(&synonymTable, pk);
	nextsubquery15.setSynonyms("a1", "i2");
	ResultTuple* actualResultnextsubquery15 = nextsubquery15.solve();
	int expectedResultnextsubquery15[1][2] = {
		{7, 8}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery15)/sizeof(expectedResultnextsubquery15[0])), actualResultnextsubquery15->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery15)/sizeof(expectedResultnextsubquery15[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery15[i])/sizeof(expectedResultnextsubquery15[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery15[i][j], actualResultnextsubquery15->getResultAt(i, j));
		}
	}

	// Test 18: Next(a1, c2)
	NextSubquery nextsubquery18 = NextSubquery(&synonymTable, pk);
	nextsubquery18.setSynonyms("a1", "c2");
	ResultTuple* actualResultnextsubquery18 = nextsubquery18.solve();
	int expectedResultnextsubquery18[3][2] = {
		{2, 3}, {9, 11}, {10, 11}
	
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery18)/sizeof(expectedResultnextsubquery18[0])), actualResultnextsubquery18->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery18)/sizeof(expectedResultnextsubquery18[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery18[i])/sizeof(expectedResultnextsubquery18[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery18[i][j], actualResultnextsubquery18->getResultAt(i, j));
		}
	}

	// Test 19: Next(a1, l2)
	NextSubquery nextsubquery19 = NextSubquery(&synonymTable, pk);
	nextsubquery19.setSynonyms("a1", "l2");
	ResultTuple* actualResultnextsubquery19 = nextsubquery19.solve();
	int expectedResultnextsubquery19[14][2] = {
		{1, 2}, {2, 3}, {4, 5}, {5, 6}, {7, 8}, {9, 11}, {10, 11}, {12, 6}, {14, 15}, {16, 15}, {17, 18}, {18, 19}, {19, 20}, {21, 22} 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery19)/sizeof(expectedResultnextsubquery19[0])), actualResultnextsubquery19->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery19)/sizeof(expectedResultnextsubquery19[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery19[i])/sizeof(expectedResultnextsubquery19[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery19[i][j], actualResultnextsubquery19->getResultAt(i, j));
		}
	}

	// Test 21: Next(a1, _)
	NextSubquery nextsubquery21 = NextSubquery(&synonymTable, pk);
	nextsubquery21.setSynonyms("a1", "_");
	ResultTuple* actualResultnextsubquery21 = nextsubquery21.solve();
	int expectedResultnextsubquery21[14][1] = {
		{1}, {2}, {4}, {5}, {7}, {9}, {10}, {12}, {14}, {16}, {17}, {18}, {19}, {21}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery21)/sizeof(expectedResultnextsubquery21[0])), actualResultnextsubquery21->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery21)/sizeof(expectedResultnextsubquery21[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery21[i])/sizeof(expectedResultnextsubquery21[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery21[i][j], actualResultnextsubquery21->getResultAt(i, j));
		}
	}

	// Test 22: Next(a1, 2)
	NextSubquery nextsubquery22 = NextSubquery(&synonymTable, pk);
	nextsubquery22.setSynonyms("a1", 2);
	ResultTuple* actualResultnextsubquery22 = nextsubquery22.solve();
	int expectedResultnextsubquery22[1][1] = {
		{1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery22)/sizeof(expectedResultnextsubquery22[0])), actualResultnextsubquery22->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery22)/sizeof(expectedResultnextsubquery22[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery22[i])/sizeof(expectedResultnextsubquery22[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery22[i][j], actualResultnextsubquery22->getResultAt(i, j));
		}
	}

	// Test 23: Next(a1, 6)
	NextSubquery nextsubquery23 = NextSubquery(&synonymTable, pk);
	nextsubquery23.setSynonyms("a1", 6);
	ResultTuple* actualResultnextsubquery23 = nextsubquery23.solve();
	int expectedResultnextsubquery23[2][1] = {
		{5}, {12}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery23)/sizeof(expectedResultnextsubquery23[0])), actualResultnextsubquery23->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery23)/sizeof(expectedResultnextsubquery23[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery23[i])/sizeof(expectedResultnextsubquery23[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery23[i][j], actualResultnextsubquery23->getResultAt(i, j));
		}
	}

	// Test 24: Next(w1, s2)
	NextSubquery nextsubquery24 = NextSubquery(&synonymTable, pk);
	nextsubquery24.setSynonyms("w1", "s2");
	ResultTuple* actualResultnextsubquery24 = nextsubquery24.solve();
	int expectedResultnextsubquery24[4][2] = {
		{6, 7}, {6, 13}, {15, 16}, {15, 18}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery24)/sizeof(expectedResultnextsubquery24[0])), actualResultnextsubquery24->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery24)/sizeof(expectedResultnextsubquery24[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery24[i])/sizeof(expectedResultnextsubquery24[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery24[i][j], actualResultnextsubquery24->getResultAt(i, j));
		}
	}

	// Test 25: Next(w1, a2)
	NextSubquery nextsubquery25 = NextSubquery(&synonymTable, pk);
	nextsubquery25.setSynonyms("w1", "a2");
	ResultTuple* actualResultnextsubquery25 = nextsubquery25.solve();
	int expectedResultnextsubquery25[3][2] = {
		{6, 7}, {15, 16}, {15, 18}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery25)/sizeof(expectedResultnextsubquery25[0])), actualResultnextsubquery25->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery25)/sizeof(expectedResultnextsubquery25[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery25[i])/sizeof(expectedResultnextsubquery25[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery25[i][j], actualResultnextsubquery25->getResultAt(i, j));
		}
	}

	// Test 26: Next(w1, w2)
	NextSubquery nextsubquery26 = NextSubquery(&synonymTable, pk);
	nextsubquery26.setSynonyms("w1", "w2");
	ResultTuple* actualResultnextsubquery26 = nextsubquery26.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultnextsubquery26->getAllResults().size());

	// Test 27: Next(w1, i2)
	NextSubquery nextsubquery27 = NextSubquery(&synonymTable, pk);
	nextsubquery27.setSynonyms("w1", "i2");
	ResultTuple* actualResultnextsubquery27 = nextsubquery27.solve();
	int expectedResultnextsubquery27[1][2] = {
		{6, 13}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery27)/sizeof(expectedResultnextsubquery27[0])), actualResultnextsubquery27->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery27)/sizeof(expectedResultnextsubquery27[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery27[i])/sizeof(expectedResultnextsubquery27[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery27[i][j], actualResultnextsubquery27->getResultAt(i, j));
		}
	}

	// Test 30: Next(w1, c2)
	NextSubquery nextsubquery30 = NextSubquery(&synonymTable, pk);
	nextsubquery30.setSynonyms("w1", "c2");
	ResultTuple* actualResultnextsubquery30 = nextsubquery30.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultnextsubquery30->getAllResults().size());

	// Test 31: Next(w1, l2)
	NextSubquery nextsubquery31 = NextSubquery(&synonymTable, pk);
	nextsubquery31.setSynonyms("w1", "l2");
	ResultTuple* actualResultnextsubquery31 = nextsubquery31.solve();
	int expectedResultnextsubquery31[4][2] = {
		{6, 7}, {6, 13}, {15, 16}, {15, 18}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery31)/sizeof(expectedResultnextsubquery31[0])), actualResultnextsubquery31->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery31)/sizeof(expectedResultnextsubquery31[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery31[i])/sizeof(expectedResultnextsubquery31[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery31[i][j], actualResultnextsubquery31->getResultAt(i, j));
		}
	}

	// Test 33: Next(w1, _)
	NextSubquery nextsubquery33 = NextSubquery(&synonymTable, pk);
	nextsubquery33.setSynonyms("w1", "_");
	ResultTuple* actualResultnextsubquery33 = nextsubquery33.solve();
	int expectedResultnextsubquery33[2][1] = {
		{6}, {15}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery33)/sizeof(expectedResultnextsubquery33[0])), actualResultnextsubquery33->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery33)/sizeof(expectedResultnextsubquery33[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery33[i])/sizeof(expectedResultnextsubquery33[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery33[i][j], actualResultnextsubquery33->getResultAt(i, j));
		}
	}

	// Test 34: Next(w1, 2)
	NextSubquery nextsubquery34 = NextSubquery(&synonymTable, pk);
	nextsubquery34.setSynonyms("w1", 2);
	ResultTuple* actualResultnextsubquery34 = nextsubquery34.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultnextsubquery34->getAllResults().size());

	// Test 35: Next(w1, 13)
	NextSubquery nextsubquery35 = NextSubquery(&synonymTable, pk);
	nextsubquery35.setSynonyms("w1", 13);
	ResultTuple* actualResultnextsubquery35 = nextsubquery35.solve();
	int expectedResultnextsubquery35[1][1] = {
		{6}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery35)/sizeof(expectedResultnextsubquery35[0])), actualResultnextsubquery35->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery35)/sizeof(expectedResultnextsubquery35[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery35[i])/sizeof(expectedResultnextsubquery35[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery35[i][j], actualResultnextsubquery35->getResultAt(i, j));
		}
	}

	// Test 36: Next(i1, s2)
	NextSubquery nextsubquery36 = NextSubquery(&synonymTable, pk);
	nextsubquery36.setSynonyms("i1", "s2");
	ResultTuple* actualResultnextsubquery36 = nextsubquery36.solve();
	int expectedResultnextsubquery36[4][2] = {
		{8, 9}, {8, 10}, {13, 14}, {13, 17}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery36)/sizeof(expectedResultnextsubquery36[0])), actualResultnextsubquery36->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery36)/sizeof(expectedResultnextsubquery36[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery36[i])/sizeof(expectedResultnextsubquery36[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery36[i][j], actualResultnextsubquery36->getResultAt(i, j));
		}
	}

	// Test 37: Next(i1, a2)
	NextSubquery nextsubquery37 = NextSubquery(&synonymTable, pk);
	nextsubquery37.setSynonyms("i1", "a2");
	ResultTuple* actualResultnextsubquery37 = nextsubquery37.solve();
	int expectedResultnextsubquery37[4][2] = {
		{8, 9}, {8, 10}, {13, 14}, {13, 17}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery37)/sizeof(expectedResultnextsubquery37[0])), actualResultnextsubquery37->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery37)/sizeof(expectedResultnextsubquery37[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery37[i])/sizeof(expectedResultnextsubquery37[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery37[i][j], actualResultnextsubquery37->getResultAt(i, j));
		}
	}

	// Test 38: Next(i1, w2)
	NextSubquery nextsubquery38 = NextSubquery(&synonymTable, pk);
	nextsubquery38.setSynonyms("i1", "w2");
	ResultTuple* actualResultnextsubquery38 = nextsubquery38.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultnextsubquery38->getAllResults().size());

	// Test 39: Next(i1, i2)
	NextSubquery nextsubquery39 = NextSubquery(&synonymTable, pk);
	nextsubquery39.setSynonyms("i1", "i2");
	ResultTuple* actualResultnextsubquery39 = nextsubquery39.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultnextsubquery39->getAllResults().size());

	// Test 42: Next(i1, c2)
	NextSubquery nextsubquery42 = NextSubquery(&synonymTable, pk);
	nextsubquery42.setSynonyms("i1", "c2");
	ResultTuple* actualResultnextsubquery42 = nextsubquery42.solve();
	int expectedResultnextsubquery42[1][2] = {
		{8, 11}
	};
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultnextsubquery42->getAllResults().size());


	// Test 43: Next(i1, l2)
	NextSubquery nextsubquery43 = NextSubquery(&synonymTable, pk);
	nextsubquery43.setSynonyms("i1", "l2");
	ResultTuple* actualResultnextsubquery43 = nextsubquery43.solve();
	int expectedResultnextsubquery43[4][2] = {
		{8, 9}, {8, 10}, {13, 14}, {13, 17}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery43)/sizeof(expectedResultnextsubquery43[0])), actualResultnextsubquery43->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery43)/sizeof(expectedResultnextsubquery43[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery43[i])/sizeof(expectedResultnextsubquery43[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery43[i][j], actualResultnextsubquery43->getResultAt(i, j));
		}
	}

	// Test 45: Next(i1, _)
	NextSubquery nextsubquery45 = NextSubquery(&synonymTable, pk);
	nextsubquery45.setSynonyms("i1", "_");
	ResultTuple* actualResultnextsubquery45 = nextsubquery45.solve();
	int expectedResultnextsubquery45[2][1] = {
		{8}, {13}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery45)/sizeof(expectedResultnextsubquery45[0])), actualResultnextsubquery45->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery45)/sizeof(expectedResultnextsubquery45[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery45[i])/sizeof(expectedResultnextsubquery45[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery45[i][j], actualResultnextsubquery45->getResultAt(i, j));
		}
	}

	// Test 46: Next(i1, 2)
	NextSubquery nextsubquery46 = NextSubquery(&synonymTable, pk);
	nextsubquery46.setSynonyms("i1", 2);
	ResultTuple* actualResultnextsubquery46 = nextsubquery46.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultnextsubquery46->getAllResults().size());

	// Test 47: Next(i1, 18)
	NextSubquery nextsubquery47 = NextSubquery(&synonymTable, pk);
	nextsubquery47.setSynonyms("i1", 18);
	ResultTuple* actualResultnextsubquery47 = nextsubquery47.solve();
	CPPUNIT_ASSERT_EQUAL((size_t) 0, actualResultnextsubquery47->getAllResults().size());


	// Test 72: Next(c1, s2)
	NextSubquery nextsubquery72 = NextSubquery(&synonymTable, pk);
	nextsubquery72.setSynonyms("c1", "s2");
	ResultTuple* actualResultnextsubquery72 = nextsubquery72.solve();
	int expectedResultnextsubquery72[1][2] = {
		{11, 12}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery72)/sizeof(expectedResultnextsubquery72[0])), actualResultnextsubquery72->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery72)/sizeof(expectedResultnextsubquery72[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery72[i])/sizeof(expectedResultnextsubquery72[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery72[i][j], actualResultnextsubquery72->getResultAt(i, j));
		}
	}

	// Test 73: Next(c1, a2)
	NextSubquery nextsubquery73 = NextSubquery(&synonymTable, pk);
	nextsubquery73.setSynonyms("c1", "a2");
	ResultTuple* actualResultnextsubquery73 = nextsubquery73.solve();
	int expectedResultnextsubquery73[1][2] = {
		{11, 12}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery73)/sizeof(expectedResultnextsubquery73[0])), actualResultnextsubquery73->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery73)/sizeof(expectedResultnextsubquery73[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery73[i])/sizeof(expectedResultnextsubquery73[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery73[i][j], actualResultnextsubquery73->getResultAt(i, j));
		}
	}

	// Test 74: Next(c1, w2)
	NextSubquery nextsubquery74 = NextSubquery(&synonymTable, pk);
	nextsubquery74.setSynonyms("c1", "w2");
	ResultTuple* actualResultnextsubquery74 = nextsubquery74.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultnextsubquery74->getAllResults().size());

	// Test 75: Next(c1, i2)
	NextSubquery nextsubquery75 = NextSubquery(&synonymTable, pk);
	nextsubquery75.setSynonyms("c1", "i2");
	ResultTuple* actualResultnextsubquery75 = nextsubquery75.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultnextsubquery75->getAllResults().size());

	// Test 78: Next(c1, c2)
	NextSubquery nextsubquery78 = NextSubquery(&synonymTable, pk);
	nextsubquery78.setSynonyms("c1", "c2");
	ResultTuple* actualResultnextsubquery78 = nextsubquery78.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultnextsubquery78->getAllResults().size());

	// Test 79: Next(c1, l2)
	NextSubquery nextsubquery79 = NextSubquery(&synonymTable, pk);
	nextsubquery79.setSynonyms("c1", "l2");
	ResultTuple* actualResultnextsubquery79 = nextsubquery79.solve();
	int expectedResultnextsubquery79[1][2] = {
		{11, 12}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery79)/sizeof(expectedResultnextsubquery79[0])), actualResultnextsubquery79->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery79)/sizeof(expectedResultnextsubquery79[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery79[i])/sizeof(expectedResultnextsubquery79[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery79[i][j], actualResultnextsubquery79->getResultAt(i, j));
		}
	}

		// Test 81: Next(c1, _)
	NextSubquery nextsubquery81 = NextSubquery(&synonymTable, pk);
	nextsubquery81.setSynonyms("c1", "_");
	ResultTuple* actualResultnextsubquery81 = nextsubquery81.solve();
	int expectedResultnextsubquery81[1][1] = {
		{11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery81)/sizeof(expectedResultnextsubquery81[0])), actualResultnextsubquery81->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery81)/sizeof(expectedResultnextsubquery81[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery81[i])/sizeof(expectedResultnextsubquery81[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery81[i][j], actualResultnextsubquery81->getResultAt(i, j));
		}
	}

	// Test 82: Next(c1, 2)
	NextSubquery nextsubquery82 = NextSubquery(&synonymTable, pk);
	nextsubquery82.setSynonyms("c1", 2);
	ResultTuple* actualResultnextsubquery82 = nextsubquery82.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultnextsubquery82->getAllResults().size());

	// Test 83: Next(c1, 12)
	NextSubquery nextsubquery83 = NextSubquery(&synonymTable, pk);
	nextsubquery83.setSynonyms("c1", 12);
	ResultTuple* actualResultnextsubquery83 = nextsubquery83.solve();
	int expectedResultnextsubquery83[1][1] = {
		{11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery83)/sizeof(expectedResultnextsubquery83[0])), actualResultnextsubquery83->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery83)/sizeof(expectedResultnextsubquery83[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery83[i])/sizeof(expectedResultnextsubquery83[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery83[i][j], actualResultnextsubquery83->getResultAt(i, j));
		}
	}

	// Test 84: Next(l1, s2)
	NextSubquery nextsubquery84 = NextSubquery(&synonymTable, pk);
	nextsubquery84.setSynonyms("l1", "s2");
	ResultTuple* actualResultnextsubquery84 = nextsubquery84.solve();
	int expectedResultnextsubquery84[23][2] = {
		{1, 2}, {2, 3}, {4, 5}, {5, 6}, {6, 7}, {6, 13}, {7, 8}, {8, 9}, {8, 10}, {9, 11}, {10, 11}, {11, 12},{12, 6}, {13, 14}, {13, 17}, {14, 15}, {15, 16}, {15, 18},{16, 15}, {17, 18}, {18, 19}, {19, 20}, {21, 22} 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery84)/sizeof(expectedResultnextsubquery84[0])), actualResultnextsubquery84->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery84)/sizeof(expectedResultnextsubquery84[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery84[i])/sizeof(expectedResultnextsubquery84[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery84[i][j], actualResultnextsubquery84->getResultAt(i, j));
		}
	}

	// Test 85: Next(l1, a2)
	NextSubquery nextsubquery85 = NextSubquery(&synonymTable, pk);
	nextsubquery85.setSynonyms("l1", "a2");
	ResultTuple* actualResultnextsubquery85 = nextsubquery85.solve();
	int expectedResultnextsubquery85[14][2] = {
		{1, 2}, {4, 5}, {6, 7}, {8, 9}, {8, 10}, {11, 12}, {13, 14}, {13, 17}, {15, 16}, {15, 18}, {17, 18}, {18, 19}, {19, 20}, {21, 22} 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery85)/sizeof(expectedResultnextsubquery85[0])), actualResultnextsubquery85->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery85)/sizeof(expectedResultnextsubquery85[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery85[i])/sizeof(expectedResultnextsubquery85[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery85[i][j], actualResultnextsubquery85->getResultAt(i, j));
		}
	}

	// Test 86: Next(l1, w2)
	NextSubquery nextsubquery86 = NextSubquery(&synonymTable, pk);
	nextsubquery86.setSynonyms("l1", "w2");
	ResultTuple* actualResultnextsubquery86 = nextsubquery86.solve();
	int expectedResultnextsubquery86[4][2] = {
		{5, 6}, {12, 6}, {14, 15}, {16, 15}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery86)/sizeof(expectedResultnextsubquery86[0])), actualResultnextsubquery86->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery86)/sizeof(expectedResultnextsubquery86[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery86[i])/sizeof(expectedResultnextsubquery86[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery86[i][j], actualResultnextsubquery86->getResultAt(i, j));
		}
	}

	// Test 87: Next(l1, i2)
	NextSubquery nextsubquery87 = NextSubquery(&synonymTable, pk);
	nextsubquery87.setSynonyms("l1", "i2");
	ResultTuple* actualResultnextsubquery87 = nextsubquery87.solve();
	int expectedResultnextsubquery87[2][2] = {
		{6, 13}, {7, 8} 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery87)/sizeof(expectedResultnextsubquery87[0])), actualResultnextsubquery87->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery87)/sizeof(expectedResultnextsubquery87[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery87[i])/sizeof(expectedResultnextsubquery87[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery87[i][j], actualResultnextsubquery87->getResultAt(i, j));
		}
	}

	// Test 90: Next(l1, c2)
	NextSubquery nextsubquery90 = NextSubquery(&synonymTable, pk);
	nextsubquery90.setSynonyms("l1", "c2");
	ResultTuple* actualResultnextsubquery90 = nextsubquery90.solve();
	int expectedResultnextsubquery90[3][2] = {
		{2, 3}, {9, 11}, {10, 11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery90)/sizeof(expectedResultnextsubquery90[0])), actualResultnextsubquery90->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery90)/sizeof(expectedResultnextsubquery90[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery90[i])/sizeof(expectedResultnextsubquery90[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery90[i][j], actualResultnextsubquery90->getResultAt(i, j));
		}
	}

	// Test 91: Next(l1, l2)
	NextSubquery nextsubquery91 = NextSubquery(&synonymTable, pk);
	nextsubquery91.setSynonyms("l1", "l2");
	ResultTuple* actualResultnextsubquery91 = nextsubquery91.solve();
	int expectedResultnextsubquery91[23][2] = {
		{1, 2}, {2, 3}, {4, 5}, {5, 6}, {6, 7}, {6, 13}, {7, 8}, {8, 9}, {8, 10}, {9, 11}, {10, 11}, {11, 12},{12, 6}, {13, 14}, {13, 17}, {14, 15}, {15, 16}, {15, 18},{16, 15}, {17, 18}, {18, 19}, {19, 20}, {21, 22} 
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery91)/sizeof(expectedResultnextsubquery91[0])), actualResultnextsubquery91->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery91)/sizeof(expectedResultnextsubquery91[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery91[i])/sizeof(expectedResultnextsubquery91[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery91[i][j], actualResultnextsubquery91->getResultAt(i, j));
		}
	}

	// Test 93: Next(l1, _)
	NextSubquery nextsubquery93 = NextSubquery(&synonymTable, pk);
	nextsubquery93.setSynonyms("l1", "_");
	ResultTuple* actualResultnextsubquery93 = nextsubquery93.solve();
	int expectedResultnextsubquery93[19][1] = {
		{1}, {2}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}, {13}, {14}, {15}, {16}, {17}, {18}, {19}, {21}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery93)/sizeof(expectedResultnextsubquery93[0])), actualResultnextsubquery93->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery93)/sizeof(expectedResultnextsubquery93[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery93[i])/sizeof(expectedResultnextsubquery93[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery93[i][j], actualResultnextsubquery93->getResultAt(i, j));
		}
	}

	// Test 94: Next(l1, 2)
	NextSubquery nextsubquery94 = NextSubquery(&synonymTable, pk);
	nextsubquery94.setSynonyms("l1", 2);
	ResultTuple* actualResultnextsubquery94 = nextsubquery94.solve();
	int expectedResultnextsubquery94[1][1] = {
		{1}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery94)/sizeof(expectedResultnextsubquery94[0])), actualResultnextsubquery94->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery94)/sizeof(expectedResultnextsubquery94[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery94[i])/sizeof(expectedResultnextsubquery94[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery94[i][j], actualResultnextsubquery94->getResultAt(i, j));
		}
	}

	// Test 95: Next(l1, 6)
	NextSubquery nextsubquery95 = NextSubquery(&synonymTable, pk);
	nextsubquery95.setSynonyms("l1", 6);
	ResultTuple* actualResultnextsubquery95 = nextsubquery95.solve();
	int expectedResultnextsubquery95[2][1] = {
		{5}, {12}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery95)/sizeof(expectedResultnextsubquery95[0])), actualResultnextsubquery95->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery95)/sizeof(expectedResultnextsubquery95[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery95[i])/sizeof(expectedResultnextsubquery95[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery95[i][j], actualResultnextsubquery95->getResultAt(i, j));
		}
	}

	// Test 108: Next(_, s2)
	NextSubquery nextsubquery108 = NextSubquery(&synonymTable, pk);
	nextsubquery108.setSynonyms("_", "s2");
	ResultTuple* actualResultnextsubquery108 = nextsubquery108.solve();
	int expectedResultnextsubquery108[19][1] = {
		{2}, {3}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}, {13}, {14}, {15}, {16}, {17}, {18}, {19}, {20}, {22}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery108)/sizeof(expectedResultnextsubquery108[0])), actualResultnextsubquery108->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery108)/sizeof(expectedResultnextsubquery108[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery108[i])/sizeof(expectedResultnextsubquery108[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery108[i][j], actualResultnextsubquery108->getResultAt(i, j));
		}
	}

	// Test 109: Next(_, a2)
	NextSubquery nextsubquery109 = NextSubquery(&synonymTable, pk);
	nextsubquery109.setSynonyms("_", "a2");
	ResultTuple* actualResultnextsubquery109 = nextsubquery109.solve();
	int expectedResultnextsubquery109[13][1] = {
		{2}, {5}, {7}, {9}, {10}, {12}, {14}, {16}, {17}, {18}, {19}, {20}, {22}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery109)/sizeof(expectedResultnextsubquery109[0])), actualResultnextsubquery109->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery109)/sizeof(expectedResultnextsubquery109[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery109[i])/sizeof(expectedResultnextsubquery109[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery109[i][j], actualResultnextsubquery109->getResultAt(i, j));
		}
	}

	// Test 110: Next(_, w2)
	NextSubquery nextsubquery110 = NextSubquery(&synonymTable, pk);
	nextsubquery110.setSynonyms("_", "w2");
	ResultTuple* actualResultnextsubquery110 = nextsubquery110.solve();
	int expectedResultnextsubquery110[2][1] = {
		{6}, {15}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery110)/sizeof(expectedResultnextsubquery110[0])), actualResultnextsubquery110->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery110)/sizeof(expectedResultnextsubquery110[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery110[i])/sizeof(expectedResultnextsubquery110[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery110[i][j], actualResultnextsubquery110->getResultAt(i, j));
		}
	}

	// Test 111: Next(_, i2)
	NextSubquery nextsubquery111 = NextSubquery(&synonymTable, pk);
	nextsubquery111.setSynonyms("_", "i2");
	ResultTuple* actualResultnextsubquery111 = nextsubquery111.solve();
	int expectedResultnextsubquery111[2][1] = {
		{8}, {13}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery111)/sizeof(expectedResultnextsubquery111[0])), actualResultnextsubquery111->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery111)/sizeof(expectedResultnextsubquery111[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery111[i])/sizeof(expectedResultnextsubquery111[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery111[i][j], actualResultnextsubquery111->getResultAt(i, j));
		}
	}

	// Test 114: Next(_, c2)
	NextSubquery nextsubquery114 = NextSubquery(&synonymTable, pk);
	nextsubquery114.setSynonyms("_", "c2");
	ResultTuple* actualResultnextsubquery114 = nextsubquery114.solve();
	int expectedResultnextsubquery114[2][1] = {
		{3}, {11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery114)/sizeof(expectedResultnextsubquery114[0])), actualResultnextsubquery114->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery114)/sizeof(expectedResultnextsubquery114[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery114[i])/sizeof(expectedResultnextsubquery114[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery114[i][j], actualResultnextsubquery114->getResultAt(i, j));
		}
	}

	// Test 115: Next(_, l2)
	NextSubquery nextsubquery115 = NextSubquery(&synonymTable, pk);
	nextsubquery115.setSynonyms("_", "l2");
	ResultTuple* actualResultnextsubquery115 = nextsubquery115.solve();
	int expectedResultnextsubquery115[19][1] = {
		{2}, {3}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}, {13}, {14}, {15}, {16}, {17}, {18}, {19}, {20}, {22}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery115)/sizeof(expectedResultnextsubquery115[0])), actualResultnextsubquery115->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery115)/sizeof(expectedResultnextsubquery115[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery115[i])/sizeof(expectedResultnextsubquery115[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery115[i][j], actualResultnextsubquery115->getResultAt(i, j));
		}
	}

	// Test 117: Next(_, _)
	NextSubquery nextsubquery117 = NextSubquery(&synonymTable, pk);
	nextsubquery117.setSynonyms("_", "_");
	ResultTuple* actualResultnextsubquery117 = nextsubquery117.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultnextsubquery117->getAllResults().size());
	CPPUNIT_ASSERT(actualResultnextsubquery117->isBool());
	CPPUNIT_ASSERT(!actualResultnextsubquery117->isEmpty());

	// Test 118: Next(_, 2)
	NextSubquery nextsubquery118 = NextSubquery(&synonymTable, pk);
	nextsubquery118.setSynonyms("_", 2);
	ResultTuple* actualResultnextsubquery118 = nextsubquery118.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultnextsubquery118->getAllResults().size());
	CPPUNIT_ASSERT(actualResultnextsubquery118->isBool());
	CPPUNIT_ASSERT(!actualResultnextsubquery118->isEmpty());

	// Test 119: Next(_, 7)
	NextSubquery nextsubquery119 = NextSubquery(&synonymTable, pk);
	nextsubquery119.setSynonyms("_", 7);
	ResultTuple* actualResultnextsubquery119 = nextsubquery119.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultnextsubquery119->getAllResults().size());
	CPPUNIT_ASSERT(actualResultnextsubquery119->isBool());
	CPPUNIT_ASSERT(!actualResultnextsubquery119->isEmpty());

	


	// Test 120: Next(1, s2)
	NextSubquery nextsubquery120 = NextSubquery(&synonymTable, pk);
	nextsubquery120.setSynonyms(1, "s2");
	ResultTuple* actualResultnextsubquery120 = nextsubquery120.solve();
	int expectedResultnextsubquery120[1][1] = {
		{2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery120)/sizeof(expectedResultnextsubquery120[0])), actualResultnextsubquery120->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery120)/sizeof(expectedResultnextsubquery120[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery120[i])/sizeof(expectedResultnextsubquery120[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery120[i][j], actualResultnextsubquery120->getResultAt(i, j));
		}
	}

	// Test 121: Next(1, a2)
	NextSubquery nextsubquery121 = NextSubquery(&synonymTable, pk);
	nextsubquery121.setSynonyms(1, "a2");
	ResultTuple* actualResultnextsubquery121 = nextsubquery121.solve();
	int expectedResultnextsubquery121[1][1] = {
		{2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery121)/sizeof(expectedResultnextsubquery121[0])), actualResultnextsubquery121->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery121)/sizeof(expectedResultnextsubquery121[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery121[i])/sizeof(expectedResultnextsubquery121[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery121[i][j], actualResultnextsubquery121->getResultAt(i, j));
		}
	}

	// Test 122: Next(1, w2)
	NextSubquery nextsubquery122 = NextSubquery(&synonymTable, pk);
	nextsubquery122.setSynonyms(1, "w2");
	ResultTuple* actualResultnextsubquery122 = nextsubquery122.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultnextsubquery122->getAllResults().size());

	// Test 123: Next(1, i2)
	NextSubquery nextsubquery123 = NextSubquery(&synonymTable, pk);
	nextsubquery123.setSynonyms(1, "i2");
	ResultTuple* actualResultnextsubquery123 = nextsubquery123.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultnextsubquery123->getAllResults().size());

	// Test 126: Next(1, c2)
	NextSubquery nextsubquery126 = NextSubquery(&synonymTable, pk);
	nextsubquery126.setSynonyms(1, "c2");
	ResultTuple* actualResultnextsubquery126 = nextsubquery126.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultnextsubquery126->getAllResults().size());

	// Test 127: Next(1, l2)
	NextSubquery nextsubquery127 = NextSubquery(&synonymTable, pk);
	nextsubquery127.setSynonyms(1, "l2");
	ResultTuple* actualResultnextsubquery127 = nextsubquery127.solve();
	int expectedResultnextsubquery127[1][1] = {
		{2}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery127)/sizeof(expectedResultnextsubquery127[0])), actualResultnextsubquery127->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery127)/sizeof(expectedResultnextsubquery127[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery127[i])/sizeof(expectedResultnextsubquery127[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery127[i][j], actualResultnextsubquery127->getResultAt(i, j));
		}
	}

	// Test 129: Next(1, _)
	NextSubquery nextsubquery129 = NextSubquery(&synonymTable, pk);
	nextsubquery129.setSynonyms(1, "_");
	ResultTuple* actualResultnextsubquery129 = nextsubquery129.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultnextsubquery129->getAllResults().size());
	CPPUNIT_ASSERT(actualResultnextsubquery129->isBool());
	CPPUNIT_ASSERT(!actualResultnextsubquery129->isEmpty());

	// Test 130: Next(1, 2)
	NextSubquery nextsubquery130 = NextSubquery(&synonymTable, pk);
	nextsubquery130.setSynonyms(1, 2);
	ResultTuple* actualResultnextsubquery130 = nextsubquery130.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultnextsubquery130->getAllResults().size());
	CPPUNIT_ASSERT(actualResultnextsubquery130->isBool());
	CPPUNIT_ASSERT(!actualResultnextsubquery130->isEmpty());

	// Test 131: Next(1, 6)
	NextSubquery nextsubquery131 = NextSubquery(&synonymTable, pk);
	nextsubquery131.setSynonyms(1, 6);
	ResultTuple* actualResultnextsubquery131 = nextsubquery131.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultnextsubquery131->getAllResults().size());
	CPPUNIT_ASSERT(actualResultnextsubquery131->isBool());
	CPPUNIT_ASSERT(actualResultnextsubquery131->isEmpty());

	// Test 132: Next(5, s2)
	NextSubquery nextsubquery132 = NextSubquery(&synonymTable, pk);
	nextsubquery132.setSynonyms(5, "s2");
	ResultTuple* actualResultnextsubquery132 = nextsubquery132.solve();
	int expectedResultnextsubquery132[1][1] = {
		{6}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery132)/sizeof(expectedResultnextsubquery132[0])), actualResultnextsubquery132->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery132)/sizeof(expectedResultnextsubquery132[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery132[i])/sizeof(expectedResultnextsubquery132[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery132[i][j], actualResultnextsubquery132->getResultAt(i, j));
		}
	}

	// Test 133: Next(5, a2)
	NextSubquery nextsubquery133 = NextSubquery(&synonymTable, pk);
	nextsubquery133.setSynonyms(5, "a2");
	ResultTuple* actualResultnextsubquery133 = nextsubquery133.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultnextsubquery133->getAllResults().size());

	// Test 134: Next(5, w2)
	NextSubquery nextsubquery134 = NextSubquery(&synonymTable, pk);
	nextsubquery134.setSynonyms(5, "w2");
	ResultTuple* actualResultnextsubquery134 = nextsubquery134.solve();
	int expectedResultnextsubquery134[1][1] = {
		{6}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery134)/sizeof(expectedResultnextsubquery134[0])), actualResultnextsubquery134->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery134)/sizeof(expectedResultnextsubquery134[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery134[i])/sizeof(expectedResultnextsubquery134[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery134[i][j], actualResultnextsubquery134->getResultAt(i, j));
		}
	}

	// Test 135: Next(7, i2)
	NextSubquery nextsubquery135 = NextSubquery(&synonymTable, pk);
	nextsubquery135.setSynonyms(7, "i2");
	ResultTuple* actualResultnextsubquery135 = nextsubquery135.solve();
	int expectedResultnextsubquery135[1][1] = {
		{8}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery135)/sizeof(expectedResultnextsubquery135[0])), actualResultnextsubquery135->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery135)/sizeof(expectedResultnextsubquery135[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery135[i])/sizeof(expectedResultnextsubquery135[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery135[i][j], actualResultnextsubquery135->getResultAt(i, j));
		}
	}

	// Test 138: Next(8, c2)
	NextSubquery nextsubquery138 = NextSubquery(&synonymTable, pk);
	nextsubquery138.setSynonyms(8, "c2");
	ResultTuple* actualResultnextsubquery138 = nextsubquery138.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultnextsubquery138->getAllResults().size());


	// Test 139: Next(5, l2)
	NextSubquery nextsubquery139 = NextSubquery(&synonymTable, pk);
	nextsubquery139.setSynonyms(5, "l2");
	ResultTuple* actualResultnextsubquery139 = nextsubquery139.solve();
	int expectedResultnextsubquery139[1][1] = {
		{6}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResultnextsubquery139)/sizeof(expectedResultnextsubquery139[0])), actualResultnextsubquery139->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResultnextsubquery139)/sizeof(expectedResultnextsubquery139[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResultnextsubquery139[i])/sizeof(expectedResultnextsubquery139[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultnextsubquery139[i][j], actualResultnextsubquery139->getResultAt(i, j));
		}
	}

	// Test 141: Next(5, _)
	NextSubquery nextsubquery141 = NextSubquery(&synonymTable, pk);
	nextsubquery141.setSynonyms(5, "_");
	ResultTuple* actualResultnextsubquery141 = nextsubquery141.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultnextsubquery141->getAllResults().size());
	CPPUNIT_ASSERT(actualResultnextsubquery141->isBool());
	CPPUNIT_ASSERT(!actualResultnextsubquery141->isEmpty());

	// Test 142: Next(5, 2)
	NextSubquery nextsubquery142 = NextSubquery(&synonymTable, pk);
	nextsubquery142.setSynonyms(5, 2);
	ResultTuple* actualResultnextsubquery142 = nextsubquery142.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultnextsubquery142->getAllResults().size());
	CPPUNIT_ASSERT(actualResultnextsubquery142->isBool());
	CPPUNIT_ASSERT(actualResultnextsubquery142->isEmpty());

	// Test 143: Next(5, 6)
	NextSubquery nextsubquery143 = NextSubquery(&synonymTable, pk);
	nextsubquery143.setSynonyms(5, 6);
	ResultTuple* actualResultnextsubquery143 = nextsubquery143.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResultnextsubquery143->getAllResults().size());
	CPPUNIT_ASSERT(actualResultnextsubquery143->isBool());
	CPPUNIT_ASSERT(!actualResultnextsubquery143->isEmpty());

}

void SubqueryTest::testNextStar() {
	NextStarSubquery nextStarSubqueryX = NextStarSubquery(&synonymTable, pk);
	nextStarSubqueryX.setSynonyms(1 , 2);
	ResultTuple* actualResultsNextStarSubqueryX = nextStarSubqueryX.solve();
	CPPUNIT_ASSERT_EQUAL(true, actualResultsNextStarSubqueryX->isBool());
	CPPUNIT_ASSERT_EQUAL(false, actualResultsNextStarSubqueryX->isEmpty());
	
	NextStarSubquery nextStarSubqueryX1 = NextStarSubquery(&synonymTable, pk);
	nextStarSubqueryX1.setSynonyms(6 , 13);
	ResultTuple* actualResultsNextStarSubqueryX1 = nextStarSubqueryX1.solve();
	CPPUNIT_ASSERT_EQUAL(true, actualResultsNextStarSubqueryX1->isBool());
	CPPUNIT_ASSERT_EQUAL(false, actualResultsNextStarSubqueryX1->isEmpty());

	NextStarSubquery nextStarSubqueryX2 = NextStarSubquery(&synonymTable, pk);
	nextStarSubqueryX2.setSynonyms(1 , 22);
	ResultTuple* actualResultsNextStarSubqueryX2 = nextStarSubqueryX2.solve();
	CPPUNIT_ASSERT_EQUAL(true, actualResultsNextStarSubqueryX2->isBool());
	CPPUNIT_ASSERT_EQUAL(true, actualResultsNextStarSubqueryX2->isEmpty());
	
	NextStarSubquery nextStarSubqueryX3 = NextStarSubquery(&synonymTable, pk);
	nextStarSubqueryX3.setSynonyms(6 , 9);
	ResultTuple* actualResultsNextStarSubqueryX3 = nextStarSubqueryX3.solve();
	CPPUNIT_ASSERT_EQUAL(true, actualResultsNextStarSubqueryX3->isBool());
	CPPUNIT_ASSERT_EQUAL(false, actualResultsNextStarSubqueryX3->isEmpty());
	
	NextStarSubquery nextStarSubqueryX4 = NextStarSubquery(&synonymTable, pk);
	nextStarSubqueryX4.setSynonyms("_" , 9);
	ResultTuple* actualResultsNextStarSubqueryX4 = nextStarSubqueryX4.solve();
	CPPUNIT_ASSERT_EQUAL(true, actualResultsNextStarSubqueryX4->isBool());
	CPPUNIT_ASSERT_EQUAL(false, actualResultsNextStarSubqueryX4->isEmpty());

	/*
	// Test 2: NextStar(s1, 2)
	NextStarSubquery nextStarSubquery2 = NextStarSubquery(&synonymTable, pk);
	nextStarSubquery2.setSynonyms("s1", 18);
	ResultTuple* actualResultsNextStarSubquery2 = nextStarSubquery2.solve();
	int expectedResultsNextStarSubquery2[14][1] = {
		{4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}, {13}, {14}, {15}, {16}, {17} 
	};
	CPPUNIT_ASSERT_EQUAL((size_t)14, actualResultsNextStarSubquery2->getAllResults().size());
	for (size_t i = 0; i < 14; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsNextStarSubquery2[i][j], actualResultsNextStarSubquery2->getResultAt(i, j));
		}
	}

	NextStarSubquery nextStarSubquery2_ = NextStarSubquery(&synonymTable, pk);
	nextStarSubquery2_.setSynonyms(6, "s1");
	ResultTuple* actualResultsNextStarSubquery2_ = nextStarSubquery2_.solve();
	int expectedResultsNextStarSubquery2_[15][1] = {
		{6}, {7}, {8}, {9}, {10}, {11}, {12}, {13}, {14}, {15}, {16}, {17}, {18}, {19}, {20}
	};
	cout << actualResultsNextStarSubquery2_->toString() <<endl;
	CPPUNIT_ASSERT_EQUAL((size_t)15, actualResultsNextStarSubquery2_->getAllResults().size());
	for (size_t i = 0; i < 15; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsNextStarSubquery2_[i][j], actualResultsNextStarSubquery2_->getResultAt(i, j));
		}
	}
	*/

	// Test 1: NextStar(s1, s2)
	NextStarSubquery nextStarSubquery1 = NextStarSubquery(&synonymTable, pk);
	nextStarSubquery1.setSynonyms("s1", "s2");
	ResultTuple* actualResultsNextStarSubquery1 = nextStarSubquery1.solve();
	int expectedResultsNextStarSubquery1[23][2] = {
		{1, 2}, {2, 3}, {4, 5}, {5, 6}, {6, 7}, {6, 13}, 
		{7, 8}, {8, 9}, {8, 10}, {9, 11}, {10, 11}, {11, 12},
		{12, 6}, {13, 14}, {13, 17}, {14, 15}, {15, 16}, {15, 18},
		{16, 15}, {17, 18}, {18, 19}, {19, 20}, {21, 22} 
	};
	CPPUNIT_ASSERT_EQUAL((size_t)23, actualResultsNextStarSubquery1->getAllResults().size());
	for (size_t i = 0; i < 23; i++){
		for (size_t j = 0; j < 2; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsNextStarSubquery1[i][j], actualResultsNextStarSubquery1->getResultAt(i, j));
		}
	}

	// Test 3: NextStar(s1, _)
	NextStarSubquery nextStarSubquery3 = NextStarSubquery(&synonymTable, pk);
	nextStarSubquery3.setSynonyms("s1", "_");
	ResultTuple* actualResultsNextStarSubquery3 = nextStarSubquery3.solve();
	int expectedResultsNextStarSubquery3[20][1] = {
		{1}, {2}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}, {13}, {14}, {15}, {16}, {17}, {18}, {19}, {20}, {21}
	};
	CPPUNIT_ASSERT_EQUAL((size_t)20, actualResultsNextStarSubquery3->getAllResults().size());
	for (size_t i = 0; i < 20; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsNextStarSubquery3[i][j], actualResultsNextStarSubquery3->getResultAt(i, j));
		}
	}	
}