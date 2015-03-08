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
#include <algorithm>

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
	pk = PKBController();
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
	pk.statementTable.insertStatement(&stmt1);
	pk.statementTable.insertStatement(&stmt2);
	pk.statementTable.insertStatement(&stmt3);
	pk.statementTable.insertStatement(&stmt4);
	pk.statementTable.insertStatement(&stmt5);
	pk.statementTable.insertStatement(&stmt6);
	pk.statementTable.insertStatement(&stmt7);
	pk.statementTable.insertStatement(&stmt8);
	pk.statementTable.insertStatement(&stmt9);
	pk.statementTable.insertStatement(&stmt10);
	pk.statementTable.insertStatement(&stmt11);
	pk.statementTable.insertStatement(&stmt12);
	pk.statementTable.insertStatement(&stmt13);
	pk.statementTable.insertStatement(&stmt14);
	pk.statementTable.insertStatement(&stmt15);
	pk.statementTable.insertStatement(&stmt16);
	pk.statementTable.insertStatement(&stmt17);
	pk.statementTable.insertStatement(&stmt18);
	pk.statementTable.insertStatement(&stmt19);
	pk.statementTable.insertStatement(&stmt20);
	pk.statementTable.insertStatement(&stmt21);
	pk.statementTable.insertStatement(&stmt22);

	pk.procTable.insertProc("First");  // 0
	pk.procTable.insertProc("Second"); // 1
	pk.procTable.insertProc("Third");  // 2

	pk.varTable.insertVar("x");        // 0
	pk.varTable.insertVar("z");        // 1
	pk.varTable.insertVar("i");		   // 2
	pk.varTable.insertVar("y");        // 3
	pk.varTable.insertVar("m");        // 4
	pk.varTable.insertVar("n");        // 5
	pk.varTable.insertVar("Second");   // 6
	pk.varTable.insertVar("v");        // 7

	pk.constantTable.insertConst(2);
	pk.constantTable.insertConst(3);
	pk.constantTable.insertConst(0);
	pk.constantTable.insertConst(5);
	pk.constantTable.insertConst(1);

	pk.followsTable.insertFollows(1, 2);
	pk.followsTable.insertFollows(2, 3);
	pk.followsTable.insertFollows(4, 5);
	pk.followsTable.insertFollows(5, 6);
	pk.followsTable.insertFollows(6, 13);
	pk.followsTable.insertFollows(13, 18);
	pk.followsTable.insertFollows(18, 19);
	pk.followsTable.insertFollows(19, 20);
	pk.followsTable.insertFollows(21, 22);
	pk.followsTable.insertFollows(7, 8);
	pk.followsTable.insertFollows(8, 11);
	pk.followsTable.insertFollows(11, 12);
	pk.followsTable.insertFollows(14, 15);

	pk.parentTable.insertParent(6, 7);
	pk.parentTable.insertParent(6, 8);
	pk.parentTable.insertParent(6, 11);
	pk.parentTable.insertParent(6, 12);
	pk.parentTable.insertParent(8, 9);
	pk.parentTable.insertParent(8, 10);
	pk.parentTable.insertParent(13, 14);
	pk.parentTable.insertParent(13, 15);
	pk.parentTable.insertParent(13, 17);
	pk.parentTable.insertParent(15, 16);

	pk.callsTable.insertCalls(0, 1);
	pk.callsTable.insertCalls(1, 2);

	pk.modifiesTable.insertModifiesProc(2, 1);
	pk.modifiesTable.insertModifiesProc(2, 7);
	pk.modifiesTable.insertModifiesProc(1, 0);
	pk.modifiesTable.insertModifiesProc(1, 2);
	pk.modifiesTable.insertModifiesProc(1, 4);
	pk.modifiesTable.insertModifiesProc(1, 5);
	pk.modifiesTable.insertModifiesProc(1, 1);
	pk.modifiesTable.insertModifiesProc(1, 3);
	pk.modifiesTable.insertModifiesProc(1, 7);
	pk.modifiesTable.insertModifiesProc(0, 0);
	pk.modifiesTable.insertModifiesProc(0, 1);
	pk.modifiesTable.insertModifiesProc(0, 2);
	pk.modifiesTable.insertModifiesProc(0, 3);
	pk.modifiesTable.insertModifiesProc(0, 4);
	pk.modifiesTable.insertModifiesProc(0, 5);
	pk.modifiesTable.insertModifiesProc(0, 7);

	pk.modifiesTable.insertModifiesStmt(1, 0);
	pk.modifiesTable.insertModifiesStmt(2, 1);
	pk.modifiesTable.insertModifiesStmt(3, 0);
	pk.modifiesTable.insertModifiesStmt(3, 2);
	pk.modifiesTable.insertModifiesStmt(3, 4);
	pk.modifiesTable.insertModifiesStmt(3, 5);
	pk.modifiesTable.insertModifiesStmt(3, 1);
	pk.modifiesTable.insertModifiesStmt(3, 3);
	pk.modifiesTable.insertModifiesStmt(3, 7);
	pk.modifiesTable.insertModifiesStmt(4, 0);
	pk.modifiesTable.insertModifiesStmt(5, 2);
	pk.modifiesTable.insertModifiesStmt(6, 0);
	pk.modifiesTable.insertModifiesStmt(6, 4);
	pk.modifiesTable.insertModifiesStmt(6, 5);
	pk.modifiesTable.insertModifiesStmt(6, 1);
	pk.modifiesTable.insertModifiesStmt(6, 7);
	pk.modifiesTable.insertModifiesStmt(6, 2);
	pk.modifiesTable.insertModifiesStmt(7, 0);
	pk.modifiesTable.insertModifiesStmt(8, 4);
	pk.modifiesTable.insertModifiesStmt(8, 5);
	pk.modifiesTable.insertModifiesStmt(9, 4);
	pk.modifiesTable.insertModifiesStmt(10, 5);
	pk.modifiesTable.insertModifiesStmt(11, 1);
	pk.modifiesTable.insertModifiesStmt(11, 7);
	pk.modifiesTable.insertModifiesStmt(12, 2);
	pk.modifiesTable.insertModifiesStmt(13, 0);
	pk.modifiesTable.insertModifiesStmt(13, 4);
	pk.modifiesTable.insertModifiesStmt(13, 1);
	pk.modifiesTable.insertModifiesStmt(14, 0);
	pk.modifiesTable.insertModifiesStmt(15, 4);
	pk.modifiesTable.insertModifiesStmt(16, 4);
	pk.modifiesTable.insertModifiesStmt(17, 1);
	pk.modifiesTable.insertModifiesStmt(18, 1);
	pk.modifiesTable.insertModifiesStmt(19, 3);
	pk.modifiesTable.insertModifiesStmt(20, 0);
	pk.modifiesTable.insertModifiesStmt(21, 1);
	pk.modifiesTable.insertModifiesStmt(22, 7);

	pk.usesTable.insertUsesProc(2, 1);
	pk.usesTable.insertUsesProc(1, 2);
	pk.usesTable.insertUsesProc(1, 0);
	pk.usesTable.insertUsesProc(1, 3);
	pk.usesTable.insertUsesProc(1, 4);
	pk.usesTable.insertUsesProc(1, 5);
	pk.usesTable.insertUsesProc(1, 6);
	pk.usesTable.insertUsesProc(1, 1);
	pk.usesTable.insertUsesProc(1, 2);
	pk.usesTable.insertUsesProc(0, 0);
	pk.usesTable.insertUsesProc(0, 1);
	pk.usesTable.insertUsesProc(0, 2);
	pk.usesTable.insertUsesProc(0, 3);
	pk.usesTable.insertUsesProc(0, 4);
	pk.usesTable.insertUsesProc(0, 5);
	pk.usesTable.insertUsesProc(0, 6);

	pk.usesTable.insertUsesStmt(3, 0);
	pk.usesTable.insertUsesStmt(3, 1);
	pk.usesTable.insertUsesStmt(3, 2);
	pk.usesTable.insertUsesStmt(3, 3);
	pk.usesTable.insertUsesStmt(3, 4);
	pk.usesTable.insertUsesStmt(3, 5);
	pk.usesTable.insertUsesStmt(3, 6);
	pk.usesTable.insertUsesStmt(6, 2);
	pk.usesTable.insertUsesStmt(6, 0);
	pk.usesTable.insertUsesStmt(6, 3);
	pk.usesTable.insertUsesStmt(6, 4);
	pk.usesTable.insertUsesStmt(6, 5);
	pk.usesTable.insertUsesStmt(6, 6);
	pk.usesTable.insertUsesStmt(6, 1);
	pk.usesTable.insertUsesStmt(7, 0);
	pk.usesTable.insertUsesStmt(7, 3);
	pk.usesTable.insertUsesStmt(8, 4);
	pk.usesTable.insertUsesStmt(8, 5);
	pk.usesTable.insertUsesStmt(8, 6);
	pk.usesTable.insertUsesStmt(9, 5);
	pk.usesTable.insertUsesStmt(10, 6);
	pk.usesTable.insertUsesStmt(11, 1);
	pk.usesTable.insertUsesStmt(12, 2);
	pk.usesTable.insertUsesStmt(13, 0);
	pk.usesTable.insertUsesStmt(13, 4);
	pk.usesTable.insertUsesStmt(14, 0);
	pk.usesTable.insertUsesStmt(15, 4);
	pk.usesTable.insertUsesStmt(16, 4);
	pk.usesTable.insertUsesStmt(18, 1);
	pk.usesTable.insertUsesStmt(18, 0);
	pk.usesTable.insertUsesStmt(18, 2);
	pk.usesTable.insertUsesStmt(19, 1);
	pk.usesTable.insertUsesStmt(20, 0);
	pk.usesTable.insertUsesStmt(20, 1);
	pk.usesTable.insertUsesStmt(20, 3);
	pk.usesTable.insertUsesStmt(22, 1);

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
}

void SubqueryTest::testFollows(){
	
	// Test 1: Follows(s1, s2)
	FollowsSubquery followsSubquery1 = FollowsSubquery(&synonymTable, &pk);
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
	FollowsSubquery followsSubquery2 = FollowsSubquery(&synonymTable, &pk);
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
	FollowsSubquery followsSubquery3 = FollowsSubquery(&synonymTable, &pk);
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
	FollowsSubquery followsSubquery4 = FollowsSubquery(&synonymTable, &pk);
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
	FollowsSubquery followsSubquery5 = FollowsSubquery(&synonymTable, &pk);
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
	FollowsSubquery followsSubquery6 = FollowsSubquery(&synonymTable, &pk);
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
	FollowsSubquery followsSubquery7 = FollowsSubquery(&synonymTable, &pk);
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
	FollowsSubquery followsSubquery8 = FollowsSubquery(&synonymTable, &pk);
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
}

void SubqueryTest::testParentT(){

}

void SubqueryTest::testModifies(){
	// Test 1: Modifies(s1, x)
	ModifiesSubquery ms1 = ModifiesSubquery(&synonymTable, &pk);
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
	ModifiesSubquery ms1_2 = ModifiesSubquery(&synonymTable, &pk);
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
	ModifiesSubquery ms1_3 = ModifiesSubquery(&synonymTable, &pk);
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
	ModifiesSubquery ms2 = ModifiesSubquery(&synonymTable, &pk);
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
	ModifiesSubquery ms2_2 = ModifiesSubquery(&synonymTable, &pk);
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
	ModifiesSubquery ms2_3 = ModifiesSubquery(&synonymTable, &pk);
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
	ModifiesSubquery ms3 = ModifiesSubquery(&synonymTable, &pk);
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
	ModifiesSubquery ms3_2 = ModifiesSubquery(&synonymTable, &pk);
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
	ModifiesSubquery ms3_3 = ModifiesSubquery(&synonymTable, &pk);
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
	ModifiesSubquery ms4 = ModifiesSubquery(&synonymTable, &pk);
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
	ModifiesSubquery ms4_2 = ModifiesSubquery(&synonymTable, &pk);
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
	ModifiesSubquery ms4_3 = ModifiesSubquery(&synonymTable, &pk);
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
	ModifiesSubquery ms5 = ModifiesSubquery(&synonymTable, &pk);
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
	ModifiesSubquery ms5_2 = ModifiesSubquery(&synonymTable, &pk);
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
	ModifiesSubquery ms5_3 = ModifiesSubquery(&synonymTable, &pk);
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
	ModifiesSubquery ms1 = ModifiesSubquery(&synonymTable, &pk);
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
	UsesSubquery us1 = UsesSubquery(&synonymTable, &pk);
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
	UsesSubquery us1_2 = UsesSubquery(&synonymTable, &pk);
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
	UsesSubquery us1_3 = UsesSubquery(&synonymTable, &pk);
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
	UsesSubquery us2 = UsesSubquery(&synonymTable, &pk);
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
	UsesSubquery us2_2 = UsesSubquery(&synonymTable, &pk);
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
	UsesSubquery us2_3 = UsesSubquery(&synonymTable, &pk);
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
	UsesSubquery us3 = UsesSubquery(&synonymTable, &pk);
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
	UsesSubquery us3_2 = UsesSubquery(&synonymTable, &pk);
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
	UsesSubquery us3_3 = UsesSubquery(&synonymTable, &pk);
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
	UsesSubquery us4 = UsesSubquery(&synonymTable, &pk);
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
	UsesSubquery us4_2 = UsesSubquery(&synonymTable, &pk);
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
	UsesSubquery us4_3 = UsesSubquery(&synonymTable, &pk);
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
	UsesSubquery us5 = UsesSubquery(&synonymTable, &pk);
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
	UsesSubquery us5_2 = UsesSubquery(&synonymTable, &pk);
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
	UsesSubquery us5_3 = UsesSubquery(&synonymTable, &pk);
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
}

void SubqueryTest::testCallsT(){
}

void SubqueryTest::testPattern(){
}

void SubqueryTest::testWith(){
}