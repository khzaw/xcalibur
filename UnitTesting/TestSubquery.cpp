#include <cppunit/config/SourcePrefix.h>
#include <iostream>
#include <string>
#include <map>
#include "TestSubquery.h"
#include "QueryProcessor\Subquery.h"
#include "QueryProcessor\Subquery.cpp"
#include "QueryProcessor\FollowsSubquery.cpp"
#include "QueryProcessor\ModifiesSubquery.cpp"
#include "QueryProcessor\UsesSubquery.cpp"
#include "QueryProcessor\ParentSubquery.cpp"
#include "QueryProcessor\WithSubquery.cpp"
#include "QueryProcessor\CallsSubquery.cpp"

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

	pk->modifiesTable.insertModifiesProc(2, 1);
	pk->modifiesTable.insertModifiesProc(2, 7);
	pk->modifiesTable.insertModifiesProc(1, 0);
	pk->modifiesTable.insertModifiesProc(1, 2);
	pk->modifiesTable.insertModifiesProc(1, 4);
	pk->modifiesTable.insertModifiesProc(1, 5);
	pk->modifiesTable.insertModifiesProc(1, 1);
	pk->modifiesTable.insertModifiesProc(1, 3);
	pk->modifiesTable.insertModifiesProc(1, 7);
	pk->modifiesTable.insertModifiesProc(0, 0);
	pk->modifiesTable.insertModifiesProc(0, 1);
	pk->modifiesTable.insertModifiesProc(0, 2);
	pk->modifiesTable.insertModifiesProc(0, 3);
	pk->modifiesTable.insertModifiesProc(0, 4);
	pk->modifiesTable.insertModifiesProc(0, 5);
	pk->modifiesTable.insertModifiesProc(0, 7);

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

	pk->usesTable.insertUsesProc(2, 1);
	pk->usesTable.insertUsesProc(1, 2);
	pk->usesTable.insertUsesProc(1, 0);
	pk->usesTable.insertUsesProc(1, 3);
	pk->usesTable.insertUsesProc(1, 4);
	pk->usesTable.insertUsesProc(1, 5);
	pk->usesTable.insertUsesProc(1, 6);
	pk->usesTable.insertUsesProc(1, 1);
	pk->usesTable.insertUsesProc(1, 2);
	pk->usesTable.insertUsesProc(0, 0);
	pk->usesTable.insertUsesProc(0, 1);
	pk->usesTable.insertUsesProc(0, 2);
	pk->usesTable.insertUsesProc(0, 3);
	pk->usesTable.insertUsesProc(0, 4);
	pk->usesTable.insertUsesProc(0, 5);
	pk->usesTable.insertUsesProc(0, 6);

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

	pk->constructCalls();
	pk->constructFollows();
	pk->constructModifies();
	pk->constructParent();
//	pk->constructNext();
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

	
	testFollows();
	testParent();
	testFollowsT();
	testParentT();
	testModifies();
	testModifiesTuple();
	testUses();
	testModifiesProc();
	testUsesProc();
	testCalls();
	testCallsT();
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

}

void SubqueryTest::testFollowsT(){

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

	/*// Test 6: Follows(1,"a1")
	FollowsSubquery followsSubquery6 = FollowsSubquery(&synonymTable, pk);
	followsSubquery6.setSynonyms(2, "a1");
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
	}*/

}

void SubqueryTest::testParentT(){

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
	for (size_t i = 0; i < 1; i++){
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
	cout << endl << actualResultsModifiesSubquery1->toString() << endl;
	/*
	for (size_t i = 0; i < 3; i++){
		for (size_t j = 0; j < 1; j++){
			CPPUNIT_ASSERT_EQUAL(expectedResultsModifiesSubquery1[i][j], actualResultsModifiesSubquery1->getResultAt(i, j));
		}
	}
	*/
}

void SubqueryTest::testModifiesProc(){
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

void SubqueryTest::testUsesProc(){
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

void SubqueryTest::testCallsT(){
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
	cout << endl << actualResultwithsubquery53->toString() << endl;
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