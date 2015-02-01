#include <cppunit/config/SourcePrefix.h>
#include "TestParentSubquery.h"
#include "QueryProcessor\ParentSubquery.cpp"

#include <iostream>
#include <string>

void 
ParentSubqueryTest::setUp()
{
}

void 
ParentSubqueryTest::tearDown()
{
}	

CPPUNIT_TEST_SUITE_REGISTRATION( ParentSubqueryTest );
// method to test insertion of Follows

void ParentSubqueryTest::testSolve(){
	/** SIMPLE source code
	procedure Proc1{
	a = x;			// 1
	b = y;			// 2
	 while c{		// 3
	 z = a;			// 4
	 b =y;			// 5
	 while x{		// 6
	  if y{			// 7
	   z=a;			// 8
	   if b{		// 9
		while c;	// 10
		 }}}}
	}
	**/

	PKBController pk;
	TNode stmt1("ASSIGN_NODE","a = x", 1,0);
	TNode stmt2("ASSIGN_NODE","b = y", 2,0);
	TNode stmt3("WHILE_NODE","c", 3,0);
	TNode stmt4("ASSIGN_NODE","z = a", 4,0);
	TNode stmt5("ASSIGN_NODE","b = y", 5,0);
	TNode stmt6("WHILE_NODE","x", 6,0);
	TNode stmt7("IF_NODE","y", 7,0);
	TNode stmt8("ASSIGN_NODE","z=a", 8,0);
	TNode stmt9("IF_NODE","b", 9,0);
	TNode stmt10("WHILE_NODE","c", 10,0);
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

	pk.parentTable.insertParent(3, 4);
	pk.parentTable.insertParent(3, 5);
	pk.parentTable.insertParent(3, 6);
	pk.parentTable.insertParent(6, 7);
	pk.parentTable.insertParent(7, 8);
	pk.parentTable.insertParent(7, 9);
	pk.parentTable.insertParent(9, 10);
	
	pk.procTable.insertProc("Proc1");

	pk.varTable.insertVar("x");
	pk.varTable.insertVar("y");
	pk.varTable.insertVar("z");
	pk.varTable.insertVar("a");
	pk.varTable.insertVar("b");
	pk.varTable.insertVar("c");

	map<string, string> table1;
	table1["s1"]="stmt";
	table1["s2"]="stmt";
	table1["a1"]="assign";
	table1["a2"]="assign";
	table1["w1"]="while";
	table1["w2"]="while";
	table1["i1"]="if";
	table1["i2"]="if";
	table1["v1"]="variable";
	table1["v2"]="variable";
	table1["proc5"]="procedure";

	ParentSubquery ps1 = ParentSubquery(&table1, &pk);
	ps1.setSynonyms(3, "s1");
	ResultTuple* rt1 = ps1.solve();
	int expected1[3][2] = {{3, 4}, {3, 5}, {3, 6}};
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 2; j++){
			CPPUNIT_ASSERT_EQUAL(expected1[i][j], rt1->getAllResults()[i][j]);
		}
	}

	ParentSubquery ps2 = ParentSubquery(&table1, &pk);
	ps2.setSynonyms(9, "s2");
	ResultTuple* rt2 = ps2.solve();
	int expected2[1][2] = {{9, 10}};
	for (int i = 0; i < 1; i++){
		for (int j = 0; j < 2; j++){
			CPPUNIT_ASSERT_EQUAL(expected2[i][j], rt2->getAllResults()[i][j]);
		}
	}

	ParentSubquery ps3 = ParentSubquery(&table1, &pk);
	ps3.setSynonyms(2, 3);
	ResultTuple* rt3 = ps3.solve();
	CPPUNIT_ASSERT_EQUAL((size_t)0, rt3->getAllResults().size());
}