#include <cppunit/config/SourcePrefix.h>
#include "TestQE.h"
#include "QueryProcessor\Subquery.h"
#include "QueryProcessor\QE.cpp"
#include "QueryProcessor\FollowsSubquery.cpp"
#include "QueryProcessor\ModifiesSubquery.cpp"

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

void QueryEvaluatorTest::testQE() {
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
	pk->statementTable->insertStatement(&stmt1);
	pk->statementTable->insertStatement(&stmt2);
	pk->statementTable->insertStatement(&stmt3);
	pk->statementTable->insertStatement(&stmt4);
	pk->statementTable->insertStatement(&stmt5);
	pk->statementTable->insertStatement(&stmt6);
	pk->statementTable->insertStatement(&stmt7);
	pk->statementTable->insertStatement(&stmt8);
	pk->statementTable->insertStatement(&stmt9);
	pk->statementTable->insertStatement(&stmt10);
	pk->statementTable->insertStatement(&stmt11);
	pk->statementTable->insertStatement(&stmt12);
	pk->statementTable->insertStatement(&stmt13);
	pk->statementTable->insertStatement(&stmt14);
	pk->statementTable->insertStatement(&stmt15);
	pk->statementTable->insertStatement(&stmt16);
	pk->statementTable->insertStatement(&stmt17);
	pk->statementTable->insertStatement(&stmt18);
	pk->statementTable->insertStatement(&stmt19);
	pk->statementTable->insertStatement(&stmt20);
	pk->statementTable->insertStatement(&stmt21);
	pk->statementTable->insertStatement(&stmt22);

	pk->procTable->insertProc("First");  // 0
	pk->procTable->insertProc("Second"); // 1
	pk->procTable->insertProc("Third");  // 2

	pk->varTable->insertVar("x");        // 0
	pk->varTable->insertVar("z");        // 1
	pk->varTable->insertVar("i");		   // 2
	pk->varTable->insertVar("y");        // 3
	pk->varTable->insertVar("m");        // 4
	pk->varTable->insertVar("n");        // 5
	pk->varTable->insertVar("Second");   // 6
	pk->varTable->insertVar("v");        // 7

	pk->constantTable->insertConst(2);
	pk->constantTable->insertConst(3);
	pk->constantTable->insertConst(0);
	pk->constantTable->insertConst(5);
	pk->constantTable->insertConst(1);

	pk->followsTable->insertFollows(1, 2);
	pk->followsTable->insertFollows(2, 3);
	pk->followsTable->insertFollows(4, 5);
	pk->followsTable->insertFollows(5, 6);
	pk->followsTable->insertFollows(6, 13);
	pk->followsTable->insertFollows(13, 18);
	pk->followsTable->insertFollows(18, 19);
	pk->followsTable->insertFollows(19, 20);
	pk->followsTable->insertFollows(21, 22);
	pk->followsTable->insertFollows(7, 8);
	pk->followsTable->insertFollows(8, 11);
	pk->followsTable->insertFollows(11, 12);
	pk->followsTable->insertFollows(14, 15);

	pk->parentTable->insertParent(6, 7);
	pk->parentTable->insertParent(6, 8);
	pk->parentTable->insertParent(6, 11);
	pk->parentTable->insertParent(6, 12);
	pk->parentTable->insertParent(8, 9);
	pk->parentTable->insertParent(8, 10);
	pk->parentTable->insertParent(13, 14);
	pk->parentTable->insertParent(13, 15);
	pk->parentTable->insertParent(13, 17);
	pk->parentTable->insertParent(15, 16);

	pk->callsTable->insertCalls(0, 1);
	pk->callsTable->insertCalls(1, 2);

	pk->modifiesTable->insertModifiesProc(0, 0);
	pk->modifiesTable->insertModifiesProc(0, 1);
	pk->modifiesTable->insertModifiesProc(0, 2);
	pk->modifiesTable->insertModifiesProc(0, 3);
	pk->modifiesTable->insertModifiesProc(0, 4);
	pk->modifiesTable->insertModifiesProc(0, 5);
	pk->modifiesTable->insertModifiesProc(0, 7);
	pk->modifiesTable->insertModifiesProc(1, 0);
	pk->modifiesTable->insertModifiesProc(1, 1);
	pk->modifiesTable->insertModifiesProc(1, 2);
	pk->modifiesTable->insertModifiesProc(1, 3);
	pk->modifiesTable->insertModifiesProc(1, 4);
	pk->modifiesTable->insertModifiesProc(1, 5);
	pk->modifiesTable->insertModifiesProc(1, 7);
	pk->modifiesTable->insertModifiesProc(2, 1);
	pk->modifiesTable->insertModifiesProc(2, 7);
	
	pk->modifiesTable->insertModifiesStmt(1, 0);
	pk->modifiesTable->insertModifiesStmt(2, 1);
	pk->modifiesTable->insertModifiesStmt(3, 0);
	pk->modifiesTable->insertModifiesStmt(3, 2);
	pk->modifiesTable->insertModifiesStmt(3, 4);
	pk->modifiesTable->insertModifiesStmt(3, 5);
	pk->modifiesTable->insertModifiesStmt(3, 1);
	pk->modifiesTable->insertModifiesStmt(3, 3);
	pk->modifiesTable->insertModifiesStmt(3, 7);
	pk->modifiesTable->insertModifiesStmt(4, 0);
	pk->modifiesTable->insertModifiesStmt(5, 2);
	pk->modifiesTable->insertModifiesStmt(6, 0);
	pk->modifiesTable->insertModifiesStmt(6, 4);
	pk->modifiesTable->insertModifiesStmt(6, 5);
	pk->modifiesTable->insertModifiesStmt(6, 1);
	pk->modifiesTable->insertModifiesStmt(6, 7);
	pk->modifiesTable->insertModifiesStmt(6, 2);
	pk->modifiesTable->insertModifiesStmt(7, 0);
	pk->modifiesTable->insertModifiesStmt(8, 4);
	pk->modifiesTable->insertModifiesStmt(8, 5);
	pk->modifiesTable->insertModifiesStmt(9, 4);
	pk->modifiesTable->insertModifiesStmt(10, 5);
	pk->modifiesTable->insertModifiesStmt(11, 1);
	pk->modifiesTable->insertModifiesStmt(11, 7);
	pk->modifiesTable->insertModifiesStmt(12, 2);
	pk->modifiesTable->insertModifiesStmt(13, 0);
	pk->modifiesTable->insertModifiesStmt(13, 4);
	pk->modifiesTable->insertModifiesStmt(13, 1);
	pk->modifiesTable->insertModifiesStmt(14, 0);
	pk->modifiesTable->insertModifiesStmt(15, 4);
	pk->modifiesTable->insertModifiesStmt(16, 4);
	pk->modifiesTable->insertModifiesStmt(17, 1);
	pk->modifiesTable->insertModifiesStmt(18, 1);
	pk->modifiesTable->insertModifiesStmt(19, 3);
	pk->modifiesTable->insertModifiesStmt(20, 0);
	pk->modifiesTable->insertModifiesStmt(21, 1);
	pk->modifiesTable->insertModifiesStmt(22, 7);

	pk->usesTable->insertUsesProc(0, 0);
	pk->usesTable->insertUsesProc(0, 1);
	pk->usesTable->insertUsesProc(0, 2);
	pk->usesTable->insertUsesProc(0, 3);
	pk->usesTable->insertUsesProc(0, 4);
	pk->usesTable->insertUsesProc(0, 5);
	pk->usesTable->insertUsesProc(0, 6);
	pk->usesTable->insertUsesProc(1, 0);
	pk->usesTable->insertUsesProc(1, 1);
	pk->usesTable->insertUsesProc(1, 2);
	pk->usesTable->insertUsesProc(1, 3);
	pk->usesTable->insertUsesProc(1, 4);
	pk->usesTable->insertUsesProc(1, 5);
	pk->usesTable->insertUsesProc(1, 6);
	pk->usesTable->insertUsesProc(2, 1);
	
	pk->usesTable->insertUsesStmt(3, 0);
	pk->usesTable->insertUsesStmt(3, 1);
	pk->usesTable->insertUsesStmt(3, 2);
	pk->usesTable->insertUsesStmt(3, 3);
	pk->usesTable->insertUsesStmt(3, 4);
	pk->usesTable->insertUsesStmt(3, 5);
	pk->usesTable->insertUsesStmt(3, 6);
	pk->usesTable->insertUsesStmt(6, 2);
	pk->usesTable->insertUsesStmt(6, 0);
	pk->usesTable->insertUsesStmt(6, 3);
	pk->usesTable->insertUsesStmt(6, 4);
	pk->usesTable->insertUsesStmt(6, 5);
	pk->usesTable->insertUsesStmt(6, 6);
	pk->usesTable->insertUsesStmt(6, 1);
	pk->usesTable->insertUsesStmt(7, 0);
	pk->usesTable->insertUsesStmt(7, 3);
	pk->usesTable->insertUsesStmt(8, 4);
	pk->usesTable->insertUsesStmt(8, 5);
	pk->usesTable->insertUsesStmt(8, 6);
	pk->usesTable->insertUsesStmt(9, 5);
	pk->usesTable->insertUsesStmt(10, 6);
	pk->usesTable->insertUsesStmt(11, 1);
	pk->usesTable->insertUsesStmt(12, 2);
	pk->usesTable->insertUsesStmt(13, 0);
	pk->usesTable->insertUsesStmt(13, 4);
	pk->usesTable->insertUsesStmt(14, 0);
	pk->usesTable->insertUsesStmt(15, 4);
	pk->usesTable->insertUsesStmt(16, 4);
	pk->usesTable->insertUsesStmt(18, 1);
	pk->usesTable->insertUsesStmt(18, 0);
	pk->usesTable->insertUsesStmt(18, 2);
	pk->usesTable->insertUsesStmt(19, 1);
	pk->usesTable->insertUsesStmt(20, 0);
	pk->usesTable->insertUsesStmt(20, 1);
	pk->usesTable->insertUsesStmt(20, 3);
	pk->usesTable->insertUsesStmt(22, 1);

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

	testInsert();
	testValidate();
	testConvertString();
}

void QueryEvaluatorTest::testInsert() {
	qe = new QE(vector<string>(), pk);
	qe->addQuery(&FollowsSubquery(&synonymTable, pk));
	CPPUNIT_ASSERT_EQUAL((size_t) 1, qe->queries.size());
	qe->addQuery(&ModifiesSubquery(&synonymTable, pk));
	CPPUNIT_ASSERT_EQUAL((size_t) 2, qe->queries.size());
}

void QueryEvaluatorTest::testValidate() {
	qe = new QE(vector<string>(), pk);
	FollowsSubquery f = FollowsSubquery(&synonymTable, pk);
	f.setSynonyms("s1", 2);
	ModifiesSubquery m = ModifiesSubquery(&synonymTable, pk);
	m.setSynonyms("s2", "v1");
	FollowsSubquery f2 = FollowsSubquery(&synonymTable, pk);
	f2.setSynonyms("s1", "const1");
	ModifiesSubquery m2 = ModifiesSubquery(&synonymTable, pk);
	m2.setSynonyms("s2", "i1");

	qe->addQuery(&f);
	CPPUNIT_ASSERT_EQUAL(true, qe->validateQueries());
	qe->addQuery(&m);
	CPPUNIT_ASSERT_EQUAL(true, qe->validateQueries());
	qe->addQuery(&m2);
	CPPUNIT_ASSERT_EQUAL(false, qe->validateQueries());
	qe->addQuery(&f2);
	CPPUNIT_ASSERT_EQUAL(false, qe->validateQueries());
	qe->addQuery(&f);
	CPPUNIT_ASSERT_EQUAL(false, qe->validateQueries());
}

void QueryEvaluatorTest::testConvertString() {

	//qe = new QE(vector<string>(), pk);
	//qe->synonymTable = synonymTable;

	//ResultTuple* tup = new ResultTuple();
	//tup->addSynonymToMap("s1", tup->addSynonym("s1"));
	//tup->addSynonymToMap("a1", tup->addSynonym("a1"));
	//tup->addSynonymToMap("v1", tup->addSynonym("v1"));
	//tup->addSynonymToMap("c1", tup->addSynonym("c1"));
	//tup->addSynonymToMap("i1", tup->addSynonym("i1"));
	//tup->addSynonymToMap("w1", tup->addSynonym("w1"));
	//tup->addSynonymToMap("const1", tup->addSynonym("const1"));
	//tup->addSynonymToMap("proc1", tup->addSynonym("proc1"));
	//

	//
	//for (int i = 0; i < 3; i++) {
	//	vector<int> row = vector<int>();
	//	for (int j = 0; j < 8; j++) {
	//		row.push_back(i);
	//	}
	//	tup->addResultRow(row);
	//}

	//qe->synonyms.push_back("s1");
	//qe->synonyms.push_back("a1");
	//qe->solution = new ResultTuple();
	//list<string> actual = qe->convertSolutionToString();
	//string expected = "none";
	//CPPUNIT_ASSERT_EQUAL(expected, actual.front());
	//
	//qe->solution = tup;
	//actual = qe->convertSolutionToString();
	//string expected2[3] = {"0 0", "1 1" , "2 2"};
	//CPPUNIT_ASSERT_EQUAL(expected2[0], actual.front());
	//actual.pop_front();
	//CPPUNIT_ASSERT_EQUAL(expected2[1], actual.front());
	//actual.pop_front();
	//CPPUNIT_ASSERT_EQUAL(expected2[2], actual.front());

	//qe->synonyms.push_back("const1");
	//actual = qe-> convertSolutionToString();
	//string expected3[3] = {"0 0 2", "1 1 3", "2 2 0"};
	//CPPUNIT_ASSERT_EQUAL(expected3[0], actual.front());
	//actual.pop_front();
	//CPPUNIT_ASSERT_EQUAL(expected3[1], actual.front());
	//actual.pop_front();
	//CPPUNIT_ASSERT_EQUAL(expected3[2], actual.front());

	//qe->synonyms.push_back("proc1");
	//actual = qe-> convertSolutionToString();
	//string expected4[3] = {"0 0 2 First", "1 1 3 Second", "2 2 0 Third"};
	//CPPUNIT_ASSERT_EQUAL(expected4[0], actual.front());
	//actual.pop_front();
	//CPPUNIT_ASSERT_EQUAL(expected4[1], actual.front());
	//actual.pop_front();
	//CPPUNIT_ASSERT_EQUAL(expected4[2], actual.front());
	////string expected;
	////CPPUNIT_ASSERT_EQUAL(expected, actual.front());
	//
	//qe->solution = tup;
	//actual = qe->convertSolutionToString();
	//expected = "0 0, 1 1, 2 2";
	////CPPUNIT_ASSERT_EQUAL(expected, actual.front());

	//qe->synonyms.push_back("const1");
	//actual = qe-> convertSolutionToString();
	//expected = "0 0 2, 1 1 3, 2 2 0";
	////CPPUNIT_ASSERT_EQUAL(expected, actual.front());

	//qe->synonyms.push_back("proc1");
	//actual = qe-> convertSolutionToString();
	//expected = "0 0 2 First, 1 1 3 Second, 2 2 0 Third";
	////CPPUNIT_ASSERT_EQUAL(expected, actual.front());
	//actual = qe-> convertSolutionToString();
	//string expected5[3] = {"0 0 2 First First 0 x 2 0", "1 1 3 Second Second 1 z 3 1", "2 2 0 Third Third 2 i 0 2"};
	//CPPUNIT_ASSERT_EQUAL(expected5[0], actual.front());
	//actual.pop_front();
	//CPPUNIT_ASSERT_EQUAL(expected5[1], actual.front());
	//actual.pop_front();
	//CPPUNIT_ASSERT_EQUAL(expected5[2], actual.front());

	/*
	QE* qe2 = new QE(vector<string>(), pk);
	qe->synonyms.push_back("BOOLEAN");
	actual = qe-> convertSolutionToString();
	expected = "FALSE";
	CPPUNIT_ASSERT_EQUAL(expected, actual);

	qe->solution = tup;
	actual = qe-> convertSolutionToString();
	expected = "TRUE";
	CPPUNIT_ASSERT_EQUAL(expected, actual);
	
	tup->isBoolean = true;
	tup->isEmp = false;
	actual = qe-> convertSolutionToString();
	expected = "TRUE";
	CPPUNIT_ASSERT_EQUAL(expected, actual);

	tup->isEmp = true;
	actual = qe-> convertSolutionToString();
	expected = "FALSE";
	CPPUNIT_ASSERT_EQUAL(expected, actual);
	*/
}

/*
void QueryEvaluatorTest::testBQE(){
	FollowsSubquery q1 = FollowsSubquery(&table1, &pk);
	q1.setSynonyms(1, "s1");
	FollowsSubquery q2 = FollowsSubquery(&table1, &pk);
	q2.setSynonyms("s1", "s2");
	
	vector<string> synonyms = vector<string>();
	synonyms.push_back("s1");
	QE query = QE(synonyms, &pk);
	query.addQuery(&q1);
	query.addQuery(&q2);
	query.solve();
	CPPUNIT_ASSERT_EQUAL(2, query.solution->getResultRow(0).at(0));

	ModifiesSubquery q3 = ModifiesSubquery(&table1, &pk);
	q3.setSynonyms("s1", 0);
	FollowsSubquery q4 = FollowsSubquery(&table1, &pk);
	q4.setSynonyms("s1", 1);
	vector<string> synonyms2 = vector<string>();
	synonyms2.push_back("s1");
	QE query2 = QE(synonyms2, &pk);
	query2.addQuery(&q3);
	query2.addQuery(&q4);
	query2.solve();
	CPPUNIT_ASSERT_EQUAL((size_t) 0, query2.solution->getAllResults().size());
}
*/

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
