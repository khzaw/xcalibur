#include <cppunit/config/SourcePrefix.h>
#include "TestQE.h"
#include "QueryProcessor\Subquery.h"
#include "QueryProcessor\QE.cpp"
#include "QueryProcessor\FollowsSubquery.cpp"

#include <iostream>
#include <string>

void 
QueryEvaluatorTest::setUp()
{
}

void 
QueryEvaluatorTest::tearDown()
{
}	

CPPUNIT_TEST_SUITE_REGISTRATION( QueryEvaluatorTest );
// method to test insertion of Follows

void QueryEvaluatorTest::testBQE(){
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

	FollowsSubquery q1 = FollowsSubquery(&table1, &pk);
	q1.setSynonyms(1, "s1");
	FollowsSubquery q2 = FollowsSubquery(&table1, &pk);
	q2.setSynonyms("s1", "s2");
	
	vector<string> synonyms = vector<string>();
	synonyms.push_back("s1");
	QE query = QE(synonyms);
	query.addQuery(&q1);
	query.addQuery(&q2);
	query.solve();
	CPPUNIT_ASSERT_EQUAL(2, query.solution->getResultRow(0).at(0));
}

/*
void QueryEvaluatorTest::testUnion(){
	PKBController pk;
	map<string, string> table1;
	
	// TEST 1:
	// (s1, s2), (s3, s2), (s4, s5), (s5, s1)
	// (s6, s7), (s7, s8)
	QE q1 = QE(vector<string>());
	Subquery s1 = Subquery(&table1, &pk);
	s1.setSynonyms("s1", "s2");
	Subquery s2 = Subquery(&table1, &pk);
	s2.setSynonyms("s6", "s7");
	Subquery s3 = Subquery(&table1, &pk);
	s3.setSynonyms("s4", "s5");
	Subquery s4 = Subquery(&table1, &pk);
	s4.setSynonyms("s3", "s2");
	Subquery s5 = Subquery(&table1, &pk);
	s5.setSynonyms("s7", "s8");
	Subquery s6 = Subquery(&table1, &pk);
	s6.setSynonyms("s5", "s1");
	q1.addQuery(s1); q1.addQuery(s2); q1.addQuery(s3); 
	q1.addQuery(s4); q1.addQuery(s5); q1.addQuery(s6);
	q1.unionQuerySets();
	string expectL1[4] = {"s1", "s3", "s4","s5"};
	string expectR1[4] = {"s2", "s2", "s5","s1"};
	string expectL2[2] = {"s6", "s7"};
	string expectR2[2] = {"s7", "s8"};
	for (int i = 0; i < 4; i++){
		CPPUNIT_ASSERT_EQUAL(expectL1[i], q1.queries[0][i].leftSynonym);
		CPPUNIT_ASSERT_EQUAL(expectR1[i], q1.queries[0][i].rightSynonym);
	}
	for (int i = 0; i < 2; i++){
		CPPUNIT_ASSERT_EQUAL(expectL2[i], q1.queries[1][i].leftSynonym);
		CPPUNIT_ASSERT_EQUAL(expectR2[i], q1.queries[1][i].rightSynonym);
	}

	// TEST 2:
	QE q2 = QE(vector<string>());
	Subquery s7 = Subquery(&table1, &pk);
	s7.setSynonyms("s5", "s6");
	q2.addQuery(s1); q2.addQuery(s2); q2.addQuery(s3); 
	q2.addQuery(s4); q2.addQuery(s5); q2.addQuery(s6);
	q2.addQuery(s7);
	q2.unionQuerySets();
	string expectL3[7] = {"s1", "s3", "s4","s5", "s5", "s6", "s7"};
	string expectR3[7] = {"s2", "s2", "s5","s1", "s6", "s7", "s8"};
	for (int i = 0; i < 7; i++){
		CPPUNIT_ASSERT_EQUAL(expectL3[i], q2.queries[0][i].leftSynonym);
		CPPUNIT_ASSERT_EQUAL(expectR3[i], q2.queries[0][i].rightSynonym);
	}
}
*/