#include <cppunit/config/SourcePrefix.h>
#include "TestOptimizedSubquerySolver.h"
#include "QueryProcessor\Subquery.h"
#include "QueryProcessor\OptimizedSubquerySolver.cpp"
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

#include <iostream>
#include <string>

void 
OptimizedSubquerySolverTest::setUp()
{
}

void 
OptimizedSubquerySolverTest::tearDown()
{
}	

CPPUNIT_TEST_SUITE_REGISTRATION( OptimizedSubquerySolverTest );
// method to test insertion of Follows

void OptimizedSubquerySolverTest::testOSS() {
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
	oss = new OptimizedSubquerySolver();
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

	testSolveSet();
	testMultithreadSolve();
	compareTime();
}

void OptimizedSubquerySolverTest::testSolveSet() {
	FollowsStarSubquery* f = new FollowsStarSubquery(&synonymTable, pk);
	f->setSynonyms(4, "s1");
	ParentStarSubquery* p = new ParentStarSubquery(&synonymTable, pk);
	p->setSynonyms("s1", "s2");
	FollowsStarSubquery* f2 = new FollowsStarSubquery(&synonymTable, pk);
	f2->setSynonyms("s2", 12);
	vector<Subquery*> queries;
	queries.push_back(f);
	queries.push_back(p);
	queries.push_back(f2);
	ResultTuple* actualResult = oss->solveSet(queries);
	int expectedResult[3][2] = {
		{6, 7},
		{6, 8},
		{6, 11}
	};
	CPPUNIT_ASSERT_EQUAL((sizeof(expectedResult)/sizeof(expectedResult[0])), actualResult->getAllResults().size());
	for (size_t i = 0; i < (sizeof(expectedResult)/sizeof(expectedResult[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResult[i])/sizeof(expectedResult[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResult[i][j], actualResult->getResultAt(i, j));
		}
	}
}

void OptimizedSubquerySolverTest::testMultithreadSolve() {
	FollowsStarSubquery* f1 = new FollowsStarSubquery(&synonymTable, pk);
	f1->setSynonyms(4, "s1");
	ParentStarSubquery* p1 = new ParentStarSubquery(&synonymTable, pk);
	p1->setSynonyms("s1", "s2");
	FollowsStarSubquery* f2 = new FollowsStarSubquery(&synonymTable, pk);
	f2->setSynonyms("s2", 12);
	vector<Subquery*> queries1;
	queries1.push_back(f1);
	queries1.push_back(p1);
	queries1.push_back(f2);
	FollowsSubquery* f3 = new FollowsSubquery(&synonymTable, pk);
	f3->setSynonyms("a1", "w1");
	ParentSubquery* p2 = new ParentSubquery(&synonymTable, pk);
	p2->setSynonyms("w1", "i1");
	FollowsStarSubquery* f4 = new FollowsStarSubquery(&synonymTable, pk);
	f4->setSynonyms("i1", "c1");
	vector<Subquery*> queries2;
	queries2.push_back(f3);
	queries2.push_back(p2);
	queries2.push_back(f4);
	vector<vector<Subquery*> > testSets;
	testSets.push_back(queries1);
	testSets.push_back(queries2);
	vector<ResultTuple*> actualResult = oss->multithreadSolve(testSets);
	int expectedResult0[1][4] = {
		{5, 6, 8, 11}
	};
	int expectedResult1[3][2] = {
		{6, 7},
		{6, 8},
		{6, 11}
	};
	CPPUNIT_ASSERT_EQUAL((size_t)2, actualResult.size());
	for (size_t i = 0; i < (sizeof(expectedResult0)/sizeof(expectedResult0[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResult0[i])/sizeof(expectedResult0[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResult0[i][j], actualResult[0]->getResultAt(i, j));
		}
	}
	for (size_t i = 0; i < (sizeof(expectedResult1)/sizeof(expectedResult1[0])); i++){
		for (size_t j = 0; j < (sizeof(expectedResult1[i])/sizeof(expectedResult1[i][0])); j++){
			CPPUNIT_ASSERT_EQUAL(expectedResult1[i][j], actualResult[1]->getResultAt(i, j));
		}
	}
	cout << endl << "RESULT FROM MULTITHREAD SOLVE: " << endl;
	for (size_t i = 0; i < actualResult.size(); i++){
		cout << endl << actualResult[i]->toString() << endl;
	}
}

void OptimizedSubquerySolverTest::compareTime(){
	FollowsStarSubquery* f1 = new FollowsStarSubquery(&synonymTable, pk);
	f1->setSynonyms(4, "s1");
	ParentStarSubquery* p1 = new ParentStarSubquery(&synonymTable, pk);
	p1->setSynonyms("s1", "s2");
	FollowsStarSubquery* f2 = new FollowsStarSubquery(&synonymTable, pk);
	f2->setSynonyms("s2", 12);
	vector<Subquery*> queries1;
	queries1.push_back(f1);
	queries1.push_back(p1);
	queries1.push_back(f2);
	FollowsSubquery* f3 = new FollowsSubquery(&synonymTable, pk);
	f3->setSynonyms("a1", "w1");
	ParentSubquery* p2 = new ParentSubquery(&synonymTable, pk);
	p2->setSynonyms("w1", "i1");
	FollowsStarSubquery* f4 = new FollowsStarSubquery(&synonymTable, pk);
	f4->setSynonyms("i1", "c1");
	vector<Subquery*> queries2;
	queries2.push_back(f3);
	queries2.push_back(p2);
	queries2.push_back(f4);
	vector<vector<Subquery*> > testSets;
	testSets.push_back(queries1);
	testSets.push_back(queries2);
	clock_t beginM = clock();
	vector<ResultTuple*> multithreadResult = oss->multithreadSolve(testSets);
	clock_t endM = clock();
	cout << endl << "RESULT FROM MULTITHREAD SOLVE: " << endl;
	for (size_t i = 0; i < multithreadResult.size(); i++){
		cout << endl << multithreadResult[i]->toString() << endl;
	}
	cout << endl << "SOLVING TIME: " << (endM - beginM) << endl;
	clock_t beginS = clock();
	vector<ResultTuple*> singlethreadResult = oss->singlethreadSolve(testSets);
	clock_t endS = clock();
	cout << endl << "RESULT FROM SINGLETHREAD SOLVE: " << endl;
	for (size_t i = 0; i < singlethreadResult.size(); i++){
		cout << endl << singlethreadResult[i]->toString() << endl;
	}
	cout << endl << "SOLVING TIME: " << (endS - beginS) << endl;
	CPPUNIT_ASSERT(endM - beginM <= endS - beginS);
}