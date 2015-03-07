#include <cppunit/config/SourcePrefix.h>
#include <iostream>
#include <string>
#include <map>
#include "TestSubquery.h"
#include "QueryProcessor\Subquery.h"
#include "QueryProcessor\Subquery.cpp"
#include "QueryProcessor\FollowsSubquery.cpp"

void 
SubqueryTest::setUp()
{
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
}

void 
SubqueryTest::tearDown()
{
}	

CPPUNIT_TEST_SUITE_REGISTRATION( SubqueryTest );
// method to test insertion of Follows

void SubqueryTest::testFollows(){
	FollowsSubquery followsSubquery1 = FollowsSubquery(&synonymTable, &pk);
	followsSubquery1.setSynonyms("s1", "s2");
	ResultTuple* resultsFollowsSubquery1 = followsSubquery1.solve();
	cout << "Result1: \n" << resultsFollowsSubquery1->toString() << endl;
}