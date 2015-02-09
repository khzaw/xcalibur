#include <cppunit/config/SourcePrefix.h>
#include "TestFollowsSubquery.h"
#include "SPA/QueryProcessor/FollowsSubquery.cpp"

#include <iostream>
#include <string>

void 
FollowsSubqueryTest::setUp()
{
}

void 
FollowsSubqueryTest::tearDown()
{
}	

CPPUNIT_TEST_SUITE_REGISTRATION( FollowsSubqueryTest );
// method to test insertion of Follows

void FollowsSubqueryTest::testSolve(){
	/** SIMPLE source code
	procedure Proc1{
	a = x;			// 1
	b = y;			// 2
	while c{		// 3
	   z = a;			// 4
	   b = y;			// 5
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

	pk.followsTable.insertFollows(1, 2);
	pk.followsTable.insertFollows(2, 3);
	pk.followsTable.insertFollows(4, 5);
	pk.followsTable.insertFollows(5, 6);
	pk.followsTable.insertFollows(8, 9);
	
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

	FollowsSubquery ps1 = FollowsSubquery(&table1, &pk);
	ps1.setSynonyms(1, "s1");
	ResultTuple* rt1 = ps1.solve();
	int expected1[1] = {2};
	for (int i = 0; i < rt1->getAllResults().size(); i++){
		CPPUNIT_ASSERT_EQUAL(expected1[0], rt1->getAllResults()[i][0]);
	}

	FollowsSubquery ps2 = FollowsSubquery(&table1, &pk);
	ps2.setSynonyms(1, 2);
	ResultTuple* rt2 = ps2.solve();
	CPPUNIT_ASSERT(rt2->isBool());
	CPPUNIT_ASSERT(!rt2->isEmpty());

	FollowsSubquery ps3 = FollowsSubquery(&table1, &pk);
	ps3.setSynonyms(1, 3);
	ResultTuple* rt3 = ps3.solve();
	CPPUNIT_ASSERT(rt3->isBool());
	CPPUNIT_ASSERT(rt3->isEmpty());

	FollowsSubquery ps4 = FollowsSubquery(&table1, &pk);
	ps4.setSynonyms(1, "_");
	ResultTuple* rt4 = ps4.solve();
	CPPUNIT_ASSERT(rt4->isBool());
	CPPUNIT_ASSERT(!rt4->isEmpty());

	FollowsSubquery ps5 = FollowsSubquery(&table1, &pk);
	ps5.setSynonyms("s1", "s2");
	ResultTuple* rt5 = ps5.solve();
	int expected5[5][2] = {{1, 2}, {2, 3}, {4, 5}, {5, 6}, {8, 9}};
	CPPUNIT_ASSERT_EQUAL((size_t)5, rt5->getAllResults().size());
	CPPUNIT_ASSERT_EQUAL((size_t)2, rt5->getResultRow(0).size());
	for (int i = 0; i < rt5->getAllResults().size(); i++){
		for (int j = 0; j < rt5->getResultRow(i).size(); j++){
			CPPUNIT_ASSERT_EQUAL(expected5[i][j], rt5->getResultAt(i, j));
		}
	}

	FollowsSubquery ps6 = FollowsSubquery(&table1, &pk);
	ps6.setSynonyms("a1", "w2");
	ResultTuple* rt6 = ps6.solve();
	int expected6[2][2] = {{2, 3}, {5, 6}};
	CPPUNIT_ASSERT_EQUAL((size_t)2, rt6->getAllResults().size());
	CPPUNIT_ASSERT_EQUAL((size_t)2, rt6->getResultRow(0).size());
	for (int i = 0; i < rt6->getAllResults().size(); i++){
		for (int j = 0; j < rt6->getResultRow(i).size(); j++){
			CPPUNIT_ASSERT_EQUAL(expected6[i][j], rt6->getResultAt(i, j));
		}
	}
}