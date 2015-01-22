#include <cppunit/config/SourcePrefix.h>
#include "testQueryEvaluator.h"
#include "QueryProcessor\QueryEvaluator.h"

#include <utility>
#include <vector>
#include <iostream>
#include <string>

#include <QueryProcessor\QueryTree.h>
#include <QueryProcessor\QTNode.h>
#include <PKB\Modifies.h>
#include <PKB\Follows.h>

void 
QueryEvaluatorTest::setUp()
{

}

void 
QueryEvaluatorTest::tearDown()
{
}

CPPUNIT_TEST_SUITE_REGISTRATION( QueryEvaluatorTest );

void QueryEvaluatorTest::testMerge() {
	// TEST 1: {a, b} and {a, c}
	const char *arr1[] = {"a", "b"};
	vector<string> a(arr1, end(arr1));
	const char *arr2[] = {"a", "c"};
	vector<string> b(arr2, end(arr2));
	static const int arr3[] = {1,2,3,4,5};
	vector<int> a2(arr3, arr3 + sizeof(arr3) / sizeof(arr3[0]));
	static const int arr4[] = {5,4,3,2,1};
	vector<int> a3(arr4, arr4 + sizeof(arr4) / sizeof(arr4[0]));
	static const int arr5[] = {1,1,4,4,5};
	vector<int> b2(arr5, arr5 + sizeof(arr5) / sizeof(arr5[0]));
	static const int arr6[] = {11,22,33,44,55};
	vector<int> b3(arr6, arr6 + sizeof(arr6) / sizeof(arr6[0]));
	vector<vector<int>> valA, valB;
	valA.push_back(a2);
	valA.push_back(a3);
	valB.push_back(b2);
	valB.push_back(b3);
	QueryEvaluator* qe = new QueryEvaluator();
	pair<vector<string>, vector<vector<int>>> set = qe->mergeSolutions(make_pair(a,valA), make_pair(b, valB));
	const char *ans[] = {"a", "b", "c"};
	vector<string> expSyn(ans, end(ans));
	static const int ans2[] = {1,1,4,4,5};
	vector<int> expSol1(ans2, ans2 + sizeof(ans2) / sizeof(ans2[0]));
	static const int ans3[] = {5,5,2,2,1};
	vector<int> expSol2(ans3, ans3 + sizeof(ans3) / sizeof(ans3[0]));
	static const int ans4[] = {11,22,33,44,55};
	vector<int> expSol3(ans4, ans4 + sizeof(ans4) / sizeof(ans4[0]));
	CPPUNIT_ASSERT(set.first.size() == 3);
	CPPUNIT_ASSERT(set.second.size() == 3);
	CPPUNIT_ASSERT(set.first == expSyn);
	CPPUNIT_ASSERT(set.second[0] == expSol1);
	CPPUNIT_ASSERT(set.second[1] == expSol2);
	CPPUNIT_ASSERT(set.second[2] == expSol3);

	// TEST 2: {a, b} and {a, b}
	const char *arr10[] = {"a", "b"};
	vector<string> a0(arr10, end(arr10));
	const char *arr20[] = {"a", "b"};
	vector<string> b0(arr20, end(arr20));
	static const int arr30[] = {1,2,3,4,5};
	vector<int> a20(arr30, arr30 + sizeof(arr30) / sizeof(arr30[0]));
	static const int arr40[] = {5,4,3,2,1};
	vector<int> a30(arr40, arr40 + sizeof(arr40) / sizeof(arr40[0]));
	static const int arr50[] = {1,1,2,2,4};
	vector<int> b20(arr50, arr50 + sizeof(arr50) / sizeof(arr50[0]));
	static const int arr60[] = {5,0,3,0,2};
	vector<int> b30(arr60, arr60 + sizeof(arr60) / sizeof(arr60[0]));
	vector<vector<int>> valC, valD;
	valC.push_back(a20);
	valC.push_back(a30);
	valD.push_back(b20);
	valD.push_back(b30);
	qe = new QueryEvaluator();
	set = qe->mergeSolutions(make_pair(a0,valC), make_pair(b0, valD));
	const char *ans0[] = {"a", "b"};
	vector<string> expSyn0(ans0, end(ans0));
	static const int ans20[] = {1,4};
	vector<int> expSol10(ans20, ans20 + sizeof(ans20) / sizeof(ans20[0]));
	static const int ans30[] = {5,2};
	vector<int> expSol20(ans30, ans30 + sizeof(ans30) / sizeof(ans30[0]));
	CPPUNIT_ASSERT(set.first.size() == 2);
	CPPUNIT_ASSERT(set.second.size() == 2);
	CPPUNIT_ASSERT(set.first == expSyn0);
	CPPUNIT_ASSERT(set.second[0] == expSol10);
	CPPUNIT_ASSERT(set.second[1] == expSol20);

	// TEST 2: {a, b} and {a, b}, no similar values
	const char *arr101[] = {"a", "b"};
	vector<string> a01(arr101, end(arr101));
	const char *arr201[] = {"a", "b"};
	vector<string> b01(arr201, end(arr201));
	static const int arr301[] = {1,2,3,4,5};
	vector<int> a201(arr301, arr301 + sizeof(arr301) / sizeof(arr301[0]));
	static const int arr401[] = {5,4,3,2,1};
	vector<int> a301(arr401, arr401 + sizeof(arr401) / sizeof(arr401[0]));
	static const int arr501[] = {1,1,2,2,4};
	vector<int> b201(arr501, arr501 + sizeof(arr501) / sizeof(arr501[0]));
	static const int arr601[] = {1,2,3,0,5};
	vector<int> b301(arr601, arr601 + sizeof(arr601) / sizeof(arr601[0]));
	vector<vector<int>> valC1, valD1;
	valC1.push_back(a201);
	valC1.push_back(a301);
	valD1.push_back(b201);
	valD1.push_back(b301);
	qe = new QueryEvaluator();
	set = qe->mergeSolutions(make_pair(a01,valC1), make_pair(b01, valD1));
	const char *ans01[] = {"a", "b"};
	vector<string> expSyn01(ans01, end(ans01));
	CPPUNIT_ASSERT(set.first.size() == 2);
	CPPUNIT_ASSERT(set.second.size() == 2);
	CPPUNIT_ASSERT(set.first == expSyn01);
	CPPUNIT_ASSERT(set.second[0].empty());
	CPPUNIT_ASSERT(set.second[1].empty());

	// TEST 4: {a, b} and {c, d}
	const char *arr100[] = {"a", "b"};
	vector<string> a00(arr100, end(arr100));
	const char *arr200[] = {"c", "d"};
	vector<string> b00(arr200, end(arr200));
	static const int arr300[] = {1,2,3};
	vector<int> a200(arr300, arr300 + sizeof(arr300) / sizeof(arr300[0]));
	static const int arr400[] = {5,4,3};
	vector<int> a300(arr400, arr400 + sizeof(arr400) / sizeof(arr400[0]));
	static const int arr500[] = {1,1,4};
	vector<int> b200(arr500, arr500 + sizeof(arr500) / sizeof(arr500[0]));
	static const int arr600[] = {5,0,2};
	vector<int> b300(arr600, arr600 + sizeof(arr600) / sizeof(arr600[0]));
	vector<vector<int>> valC0, valD0;
	valC0.push_back(a200);
	valC0.push_back(a300);
	valD0.push_back(b200);
	valD0.push_back(b300);
	qe = new QueryEvaluator();
	set = qe->mergeSolutions(make_pair(a00,valC0), make_pair(b00, valD0));
	const char *ans00[] = {"a", "b", "c", "d"};
	vector<string> expSyn00(ans00, end(ans00));
	static const int ans200[] = {1,1,1,2,2,2,3,3,3};
	vector<int> expSol100(ans200, ans200 + sizeof(ans200) / sizeof(ans200[0]));
	static const int ans300[] = {5,5,5,4,4,4,3,3,3};
	vector<int> expSol200(ans300, ans300 + sizeof(ans300) / sizeof(ans300[0]));
	static const int ans400[] = {1,1,4,1,1,4,1,1,4};
	vector<int> expSol300(ans400, ans400 + sizeof(ans400) / sizeof(ans400[0]));
	static const int ans500[] = {5,0,2,5,0,2,5,0,2};
	vector<int> expSol400(ans500, ans500 + sizeof(ans500) / sizeof(ans500[0]));
	CPPUNIT_ASSERT(set.first.size() == 4);
	CPPUNIT_ASSERT(set.second.size() == 4);
	CPPUNIT_ASSERT(set.first == expSyn00);
	CPPUNIT_ASSERT(set.second[0] == expSol100);
	CPPUNIT_ASSERT(set.second[1] == expSol200);
	CPPUNIT_ASSERT(set.second[2] == expSol300);
	CPPUNIT_ASSERT(set.second[3] == expSol400);
}

void QueryEvaluatorTest::testBasicSelect() {
	PKBController pk;
	TNode stmt1("ASSIGN_NODE","a = x", 1,0);
	TNode stmt2("ASSIGN_NODE","b = y", 2,0);
	TNode stmt3("WHILE_NODE","c", 3,0);
	TNode stmt4("ASSIGN_NODE","d = t", 4,0);
	TNode stmt5("ASSIGN_NODE","e = v", 5,0);
	TNode stmt6("WHILE_NODE","f", 6,0);
	TNode stmt7("WHILE_NODE","g", 7,0);
	TNode stmt8("ASSIGN_NODE","h=u", 8,0);
	TNode stmt9("WHILE_NODE","i", 9,0);
	TNode stmt10("WHILE_NODE","j", 10,0);
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
	pk.followsTable.insertFollows(3, 4);
	pk.followsTable.insertFollows(4, 5);
	pk.followsTable.insertFollows(5, 6);
	pk.followsTable.insertFollows(6, 7);
	pk.followsTable.insertFollows(7, 8);
	pk.followsTable.insertFollows(8, 9);
	pk.followsTable.insertFollows(9, 10);

	pk.procTable.insertProc("Proc1");

	pk.varTable.insertVar("x");
	pk.varTable.insertVar("y");
	pk.varTable.insertVar("z");
	pk.varTable.insertVar("a");
	pk.varTable.insertVar("b");
	pk.varTable.insertVar("c");

	QueryEvaluator* qe = new QueryEvaluator(&pk);

	map<string, string> table1;
	table1["s"]="stmt";

	//vector<int> actualResult1 = qe->solveForSelect("s", &table1, &st, &pt, &vt); // stmt s1; Select s1 such that Follows(s1, 2) | Expected <1>
	//CPPUNIT_ASSERT_EQUAL((size_t)10, actualResult1.size());
}

void QueryEvaluatorTest::testCheckSynonymInSuchThat(){
	QTNode* modifies = new QTNode("Modifies");
	QTNode* synonym1 = new QTNode("synonym1");
	QTNode* synonym2 = new QTNode("synonym2");
	synonym1->setParent(modifies);
	modifies->addChild(synonym1);
	synonym2->setParent(modifies);
	modifies->addChild(synonym2);
	QueryTree* suchThatStub = new QueryTree(modifies);
	QueryEvaluator* qe = new QueryEvaluator();
	CPPUNIT_ASSERT_EQUAL(true, qe->checkSynonymInSuchThat("synonym1", suchThatStub));
	CPPUNIT_ASSERT_EQUAL(true, qe->checkSynonymInSuchThat("synonym2", suchThatStub));
	CPPUNIT_ASSERT_EQUAL(false, qe->checkSynonymInSuchThat("synonym3", suchThatStub));
}

void QueryEvaluatorTest::testSolveForSuchThatFollows(){
	PKBController pk;
	TNode stmt1("ASSIGN_NODE","a = x", 1,0);
	TNode stmt2("ASSIGN_NODE","b = y", 2,0);
	TNode stmt3("WHILE_NODE","c", 3,0);
	TNode stmt4("ASSIGN_NODE","d = t", 4,0);
	TNode stmt5("ASSIGN_NODE","e = v", 5,0);
	TNode stmt6("WHILE_NODE","f", 6,0);
	TNode stmt7("WHILE_NODE","g", 7,0);
	TNode stmt8("ASSIGN_NODE","h=u", 8,0);
	TNode stmt9("WHILE_NODE","i", 9,0);
	TNode stmt10("WHILE_NODE","j", 10,0);
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
	pk.followsTable.insertFollows(3, 4);
	pk.followsTable.insertFollows(4, 5);
	pk.followsTable.insertFollows(5, 6);
	pk.followsTable.insertFollows(6, 7);
	pk.followsTable.insertFollows(7, 8);
	pk.followsTable.insertFollows(8, 9);
	pk.followsTable.insertFollows(9, 10);

	pk.procTable.insertProc("Proc1");

	pk.varTable.insertVar("x");
	pk.varTable.insertVar("y");
	pk.varTable.insertVar("z");
	pk.varTable.insertVar("a");
	pk.varTable.insertVar("b");
	pk.varTable.insertVar("c");

	QueryEvaluator* qe = new QueryEvaluator(&pk);

	map<string, string> table1;
	table1["s1"]="stmt";
	table1["s2"]="stmt";
	table1["a2"]="assign";
	table1["a3"]="assign";
	table1["w3"]="while";
	table1["w4"]="while";
	table1["v4"]="variable";
	table1["v5"]="variable";
	table1["proc1"]="procedure";

	QTNode* follows0 = new QTNode("Follows");
	QTNode* first0 = new QTNode("s1");
	QTNode* second0 = new QTNode("s1");
	first0->setParent(follows0);
	follows0->addChild(first0);
	second0->setParent(follows0);
	follows0->addChild(second0);
	QueryTree* query0 = new QueryTree();
	query0->getRootNode()->getChild(1)->addChild(follows0);

	vector<int> actualResult0 = qe->solve("s1",&table1, query0); // stmt s1; Select s1 such that Follows(s1, s1) | Expected <> (none)

	CPPUNIT_ASSERT(actualResult0.empty());
	
	QTNode* follows1 = new QTNode("Follows");
	QTNode* first1 = new QTNode("s1");
	QTNode* second1 = new QTNode(2);
	first1->setParent(follows1);
	follows1->addChild(first1);
	second1->setParent(follows1);
	follows1->addChild(second1);
	QueryTree* query1 = new QueryTree();
	query1->getRootNode()->getChild(1)->addChild(follows1);

	vector<int> actualResult1 = qe->solve("s1", &table1, query1); // stmt s1; Select s1 such that Follows(s1, 2) | Expected <1>
	
	CPPUNIT_ASSERT_EQUAL((size_t)1, actualResult1.size());
	CPPUNIT_ASSERT_EQUAL(1, actualResult1.at(0));
	
	QTNode* follows2 = new QTNode("Follows");
	QTNode* first2 = new QTNode("a2");
	QTNode* second2 = new QTNode(3);
	first2->setParent(follows2);
	follows2->addChild(first2);
	second2->setParent(follows2);
	follows2->addChild(second2);
	QueryTree* query2 = new QueryTree();
	query2->getRootNode()->getChild(1)->addChild(follows2);

	vector<int> actualResult2 = qe->solve("a2", &table1, query2); // assign a2; Select a2 such that Follows(a2, 3) | Expected <2>

	CPPUNIT_ASSERT_EQUAL((size_t)1, actualResult2.size());
	CPPUNIT_ASSERT_EQUAL(2, actualResult2.at(0));
	
	QTNode* follows3 = new QTNode("Follows");
	QTNode* first3 = new QTNode("a2");
	QTNode* second3 = new QTNode(4);
	first3->setParent(follows3);
	follows3->addChild(first3);
	second3->setParent(follows3);
	follows3->addChild(second3);
	QueryTree* query3 = new QueryTree();
	query3->getRootNode()->getChild(1)->addChild(follows3);

	vector<int> actualResult3 = qe->solve("a2", &table1, query3); // assign a2; Select a2 such that Follows(a2, 4) | Expected <> (none)

	CPPUNIT_ASSERT(actualResult3.empty());
	
	QTNode* follows4 = new QTNode("Follows");
	QTNode* first4 = new QTNode("w3");
	QTNode* second4 = new QTNode(3);
	first4->setParent(follows4);
	follows4->addChild(first4);
	second4->setParent(follows4);
	follows4->addChild(second4);
	QueryTree* query4 = new QueryTree();
	query4->getRootNode()->getChild(1)->addChild(follows4);

	vector<int> actualResult4 = qe->solve("w3", &table1, query4); // while w3; Select w3 such that Follows(w3, 3) | Expected <> (none)

	CPPUNIT_ASSERT(actualResult4.empty());

	QTNode* follows5 = new QTNode("Follows");
	QTNode* first5 = new QTNode("w3");
	QTNode* second5 = new QTNode(4);
	first5->setParent(follows5);
	follows5->addChild(first5);
	second5->setParent(follows5);
	follows5->addChild(second5);
	QueryTree* query5 = new QueryTree();
	query5->getRootNode()->getChild(1)->addChild(follows5);

	vector<int> actualResult5 = qe->solve("w3", &table1, query5); // while w3; Select w3 such that Follows(w3, 4) | Expected <3>

	CPPUNIT_ASSERT_EQUAL((size_t)1, actualResult5.size());
	CPPUNIT_ASSERT_EQUAL(3, actualResult5.at(0));

	QTNode* follows6 = new QTNode("Follows");
	QTNode* first6 = new QTNode("v4");
	QTNode* second6 = new QTNode(4);
	first6->setParent(follows6);
	follows6->addChild(first6);
	second6->setParent(follows6);
	follows6->addChild(second6);
	QueryTree* query6 = new QueryTree();
	query6->getRootNode()->getChild(1)->addChild(follows6);

	vector<int> actualResult6 = qe->solve("v4", &table1, query6); // variable v4; Select v4 such that Follows(v4, 4) | Expected <> (none)

	CPPUNIT_ASSERT(actualResult6.empty());

	QTNode* follows7 = new QTNode("Follows");
	QTNode* first7 = new QTNode("lol");
	QTNode* second7 = new QTNode(3);
	first7->setParent(follows7);
	follows7->addChild(first7);
	second7->setParent(follows7);
	follows7->addChild(second7);
	QueryTree* query7 = new QueryTree();
	query7->getRootNode()->getChild(1)->addChild(follows7);

	vector<int> actualResult7 = qe->solve("lol", &table1, query7); // undefined lol; Select lol such that Follows(lol, 3) | Expected <> (none)

	CPPUNIT_ASSERT(actualResult7.empty());

	QTNode* follows8 = new QTNode("Follows");
	QTNode* first8 = new QTNode("s1");
	QTNode* second8 = new QTNode("s2");
	first8->setParent(follows8);
	follows8->addChild(first8);
	second8->setParent(follows8);
	follows8->addChild(second8);
	QueryTree* query8 = new QueryTree();
	query8->getRootNode()->getChild(1)->addChild(follows8);

	vector<int> actualResult8 = qe->solve("s1", &table1, query8); // stmt s1, s2; Select s1 such that Follows(s1, s2) | Expected <1, 2 ,3 , 4, 5, 6, 7, 8, 9>

	CPPUNIT_ASSERT_EQUAL((size_t)9, actualResult8.size());
	CPPUNIT_ASSERT_EQUAL(1, actualResult8.at(0));
	CPPUNIT_ASSERT_EQUAL(2, actualResult8.at(1));
	CPPUNIT_ASSERT_EQUAL(3, actualResult8.at(2));
	CPPUNIT_ASSERT_EQUAL(4, actualResult8.at(3));
	CPPUNIT_ASSERT_EQUAL(5, actualResult8.at(4));
	CPPUNIT_ASSERT_EQUAL(6, actualResult8.at(5));
	CPPUNIT_ASSERT_EQUAL(7, actualResult8.at(6));
	CPPUNIT_ASSERT_EQUAL(8, actualResult8.at(7));
	CPPUNIT_ASSERT_EQUAL(9, actualResult8.at(8));

	QTNode* follows9 = new QTNode("Follows");
	QTNode* first9 = new QTNode("a2");
	QTNode* second9 = new QTNode("s2");
	first9->setParent(follows9);
	follows9->addChild(first9);
	second9->setParent(follows9);
	follows9->addChild(second9);
	QueryTree* query9 = new QueryTree();
	query9->getRootNode()->getChild(1)->addChild(follows9);

	vector<int> actualResult9 = qe->solve("a2", &table1, query9); // assign a2; stmt s2; Select a2 such that Follows(a2, s2) | Expected <1, 2, 4, 5, 8>

	CPPUNIT_ASSERT_EQUAL((size_t)5, actualResult9.size());
	CPPUNIT_ASSERT_EQUAL(1, actualResult9.at(0));
	CPPUNIT_ASSERT_EQUAL(2, actualResult9.at(1));
	CPPUNIT_ASSERT_EQUAL(4, actualResult9.at(2));
	CPPUNIT_ASSERT_EQUAL(5, actualResult9.at(3));
	CPPUNIT_ASSERT_EQUAL(8, actualResult9.at(4));

	QTNode* follows10 = new QTNode("Follows");
	QTNode* first10 = new QTNode("a1");
	QTNode* second10 = new QTNode("s2");
	first10->setParent(follows10);
	follows10->addChild(first10);
	second10->setParent(follows10);
	follows10->addChild(second10);
	QueryTree* query10 = new QueryTree();
	query10->getRootNode()->getChild(1)->addChild(follows10);

	vector<int> actualResult10 = qe->solve("a1", &table1, query10); // stmt s2; Select a1 such that Follows(a1, s2) | Expected <> (none because a1 is not in synonym table)

	CPPUNIT_ASSERT(actualResult10.empty());
	
	QTNode* follows11 = new QTNode("Follows");
	QTNode* first11 = new QTNode("w3");
	QTNode* second11 = new QTNode("s2");
	first11->setParent(follows11);
	follows11->addChild(first11);
	second11->setParent(follows11);
	follows11->addChild(second11);
	QueryTree* query11 = new QueryTree();
	query11->getRootNode()->getChild(1)->addChild(follows11);

	vector<int> actualResult11 = qe->solve("w3", &table1, query11); // while w3; stmt s2; Select w3 such that Follows(w3, s2) | Expected <3, 6, 7, 9>

	CPPUNIT_ASSERT_EQUAL((size_t)4, actualResult11.size());
	CPPUNIT_ASSERT_EQUAL(3, actualResult11.at(0));
	CPPUNIT_ASSERT_EQUAL(6, actualResult11.at(1));
	CPPUNIT_ASSERT_EQUAL(7, actualResult11.at(2));
	CPPUNIT_ASSERT_EQUAL(9, actualResult11.at(3));

	QTNode* follows12 = new QTNode("Follows");
	QTNode* first12 = new QTNode("s1");
	QTNode* second12 = new QTNode("a1");
	first12->setParent(follows12);
	follows12->addChild(first12);
	second12->setParent(follows12);
	follows12->addChild(second12);
	QueryTree* query12 = new QueryTree();
	query12->getRootNode()->getChild(1)->addChild(follows12);

	vector<int> actualResult12 = qe->solve("s1", &table1, query12); // stmt s1; Select s1 such that Follows(s1, a1) | Expected <> (none because a1  is not in synonym table)

	CPPUNIT_ASSERT(actualResult12.empty());

	QTNode* follows13 = new QTNode("Follows");
	QTNode* first13 = new QTNode("s1");
	QTNode* second13 = new QTNode("a2");
	first13->setParent(follows13);
	follows13->addChild(first13);
	second13->setParent(follows13);
	follows13->addChild(second13);
	QueryTree* query13 = new QueryTree();
	query13->getRootNode()->getChild(1)->addChild(follows13);

	vector<int> actualResult13 = qe->solve("s1", &table1, query13); // stmt s1; assign a2; Select s1 such that Follows(s1, a2) | Expected <1, 3, 4, 7>

	CPPUNIT_ASSERT_EQUAL((size_t)4, actualResult13.size());
	CPPUNIT_ASSERT_EQUAL(1, actualResult13.at(0));
	CPPUNIT_ASSERT_EQUAL(3, actualResult13.at(1));
	CPPUNIT_ASSERT_EQUAL(4, actualResult13.at(2));
	CPPUNIT_ASSERT_EQUAL(7, actualResult13.at(3));

	QTNode* follows14 = new QTNode("Follows");
	QTNode* first14 = new QTNode("s1");
	QTNode* second14 = new QTNode("w3");
	first14->setParent(follows14);
	follows14->addChild(first14);
	second14->setParent(follows14);
	follows14->addChild(second14);
	QueryTree* query14 = new QueryTree();
	query14->getRootNode()->getChild(1)->addChild(follows14);

	vector<int> actualResult14 = qe->solve("s1", &table1, query14); // stmt s1; while w3; Select s1 such that Follows(s1, w3) | Expected <2, 5, 6, 8, 9>

	CPPUNIT_ASSERT_EQUAL((size_t)5, actualResult14.size());
	CPPUNIT_ASSERT_EQUAL(2, actualResult14.at(0));
	CPPUNIT_ASSERT_EQUAL(5, actualResult14.at(1));
	CPPUNIT_ASSERT_EQUAL(6, actualResult14.at(2));
	CPPUNIT_ASSERT_EQUAL(8, actualResult14.at(3));
	CPPUNIT_ASSERT_EQUAL(9, actualResult14.at(4));

	QTNode* follows15 = new QTNode("Follows");
	QTNode* first15 = new QTNode("a2");
	QTNode* second15 = new QTNode("a3");
	first15->setParent(follows15);
	follows15->addChild(first15);
	second15->setParent(follows15);
	follows15->addChild(second15);
	QueryTree* query15 = new QueryTree();
	query15->getRootNode()->getChild(1)->addChild(follows15);

	vector<int> actualResult15 = qe->solve("a2", &table1, query15); // assign a2; assign a3; Select a2 such that Follows(a2, a3) | Expected <1, 4>

	CPPUNIT_ASSERT_EQUAL((size_t)2, actualResult15.size());
	CPPUNIT_ASSERT_EQUAL(1, actualResult15.at(0));
	CPPUNIT_ASSERT_EQUAL(4, actualResult15.at(1));

	QTNode* follows16 = new QTNode("Follows");
	QTNode* first16 = new QTNode("a2");
	QTNode* second16 = new QTNode("w3");
	first16->setParent(follows16);
	follows16->addChild(first16);
	second16->setParent(follows16);
	follows16->addChild(second16);
	QueryTree* query16 = new QueryTree();
	query16->getRootNode()->getChild(1)->addChild(follows16);

	vector<int> actualResult16 = qe->solve("a2", &table1, query16); // assign a2; while w3; Select a2 such that Follows(a2, w3) | Expected <2, 5, 8>

	CPPUNIT_ASSERT_EQUAL((size_t)3, actualResult16.size());
	CPPUNIT_ASSERT_EQUAL(2, actualResult16.at(0));
	CPPUNIT_ASSERT_EQUAL(5, actualResult16.at(1));
	CPPUNIT_ASSERT_EQUAL(8, actualResult16.at(2));

	QTNode* follows17 = new QTNode("Follows");
	QTNode* first17 = new QTNode("w3");
	QTNode* second17 = new QTNode("a2");
	first17->setParent(follows17);
	follows17->addChild(first17);
	second17->setParent(follows17);
	follows17->addChild(second17);
	QueryTree* query17 = new QueryTree();
	query17->getRootNode()->getChild(1)->addChild(follows17);

	vector<int> actualResult17 = qe->solve("w3", &table1, query17); // while w3; assign a2; Select w3 such that Follows(w3, a2) | Expected <3, 7>

	CPPUNIT_ASSERT_EQUAL((size_t)2, actualResult17.size());
	CPPUNIT_ASSERT_EQUAL(3, actualResult17.at(0));
	CPPUNIT_ASSERT_EQUAL(7, actualResult17.at(1));

	QTNode* follows18 = new QTNode("Follows");
	QTNode* first18 = new QTNode("w3");
	QTNode* second18 = new QTNode("w4");
	first18->setParent(follows18);
	follows18->addChild(first18);
	second18->setParent(follows18);
	follows18->addChild(second18);
	QueryTree* query18 = new QueryTree();
	query18->getRootNode()->getChild(1)->addChild(follows18);

	vector<int> actualResult18 = qe->solve("w3", &table1, query18); // while w3; while w4; Select w3 such that Follows(w3, w4) | Expected <6, 9>

	CPPUNIT_ASSERT_EQUAL((size_t)2, actualResult18.size());
	CPPUNIT_ASSERT_EQUAL(6, actualResult18.at(0));
	CPPUNIT_ASSERT_EQUAL(9, actualResult18.at(1));

	QTNode* follows19 = new QTNode("Follows");
	QTNode* first19 = new QTNode(1);
	QTNode* second19 = new QTNode("s1");
	first19->setParent(follows19);
	follows19->addChild(first19);
	second19->setParent(follows19);
	follows19->addChild(second19);
	QueryTree* query19 = new QueryTree();
	query19->getRootNode()->getChild(1)->addChild(follows19);

	vector<int> actualResult19 = qe->solve("s1", &table1, query19); // stmt s1; Select s1 such that Follows(1, s1) | Expected <2>
	
	CPPUNIT_ASSERT_EQUAL((size_t)1, actualResult19.size());
	CPPUNIT_ASSERT_EQUAL(2, actualResult19.at(0));

	QTNode* follows20 = new QTNode("Follows");
	QTNode* first20 = new QTNode(3);
	QTNode* second20 = new QTNode("a2");
	first20->setParent(follows20);
	follows20->addChild(first20);
	second20->setParent(follows20);
	follows20->addChild(second20);
	QueryTree* query20 = new QueryTree();
	query20->getRootNode()->getChild(1)->addChild(follows20);

	vector<int> actualResult20 = qe->solve("a2", &table1, query20); // assign a2; Select a2 such that Follows(3, a2) | Expected <4>

	CPPUNIT_ASSERT_EQUAL((size_t)1, actualResult20.size());
	CPPUNIT_ASSERT_EQUAL(4, actualResult20.at(0));

	QTNode* follows21 = new QTNode("Follows");
	QTNode* first21 = new QTNode(2);
	QTNode* second21 = new QTNode("a2");
	first21->setParent(follows21);
	follows21->addChild(first21);
	second21->setParent(follows21);
	follows21->addChild(second21);
	QueryTree* query21 = new QueryTree();
	query21->getRootNode()->getChild(1)->addChild(follows21);

	vector<int> actualResult21 = qe->solve("a2", &table1, query21); // assign a2; Select a2 such that Follows(2, a2) | Expected <> (none)

	CPPUNIT_ASSERT(actualResult21.empty());

	QTNode* follows22 = new QTNode("Follows");
	QTNode* first22 = new QTNode(3);
	QTNode* second22 = new QTNode("w3");
	first22->setParent(follows22);
	follows22->addChild(first22);
	second22->setParent(follows22);
	follows22->addChild(second22);
	QueryTree* query22 = new QueryTree();
	query22->getRootNode()->getChild(1)->addChild(follows22);

	vector<int> actualResult22 = qe->solve("w3", &table1, query22); // while w3; Select w3 such that Follows(3, w3) | Expected <> (none)

	CPPUNIT_ASSERT(actualResult22.empty());

	QTNode* follows23 = new QTNode("Follows");
	QTNode* first23 = new QTNode(2);
	QTNode* second23 = new QTNode("w3");
	first23->setParent(follows23);
	follows23->addChild(first23);
	second23->setParent(follows23);
	follows23->addChild(second23);
	QueryTree* query23 = new QueryTree();
	query23->getRootNode()->getChild(1)->addChild(follows23);

	vector<int> actualResult23 = qe->solve("w3", &table1, query23); // while w3; Select w3 such that Follows(2, w3) | Expected <3>

	CPPUNIT_ASSERT_EQUAL((size_t)1, actualResult23.size());
	CPPUNIT_ASSERT_EQUAL(3, actualResult23.at(0));

	QTNode* follows24 = new QTNode("Follows");
	QTNode* first24 = new QTNode(4);
	QTNode* second24 = new QTNode("v4");
	first24->setParent(follows24);
	follows24->addChild(first24);
	second24->setParent(follows24);
	follows24->addChild(second24);
	QueryTree* query24 = new QueryTree();
	query24->getRootNode()->getChild(1)->addChild(follows24);

	vector<int> actualResult24 = qe->solve("v4", &table1, query24); // variable v4; Select v4 such that Follows(4, v4) | Expected <> (none)

	CPPUNIT_ASSERT(actualResult24.empty());

	QTNode* follows25 = new QTNode("Follows");
	QTNode* first25 = new QTNode(3);
	QTNode* second25 = new QTNode("lol");
	first25->setParent(follows25);
	follows25->addChild(first25);
	second25->setParent(follows25);
	follows25->addChild(second25);
	QueryTree* query25 = new QueryTree();
	query25->getRootNode()->getChild(1)->addChild(follows25);

	vector<int> actualResult25 = qe->solve("lol", &table1, query25); // undefined lol; Select lol such that Follows(3, lol) | Expected <> (none)

	CPPUNIT_ASSERT(actualResult25.empty());

	QTNode* follows26 = new QTNode("Follows");
	QTNode* first26 = new QTNode("s1");
	QTNode* second26 = new QTNode("s2");
	first26->setParent(follows26);
	follows26->addChild(first26);
	second26->setParent(follows26);
	follows26->addChild(second26);
	QueryTree* query26 = new QueryTree();
	query26->getRootNode()->getChild(1)->addChild(follows26);

	vector<int> actualResult26 = qe->solve("s2", &table1, query26); // stmt s1, s2; Select s2 such that Follows(s1, s2) | Expected <2 ,3 , 4, 5, 6, 7, 8, 9, 10>

	CPPUNIT_ASSERT_EQUAL((size_t)9, actualResult26.size());
	CPPUNIT_ASSERT_EQUAL(2, actualResult26.at(0));
	CPPUNIT_ASSERT_EQUAL(3, actualResult26.at(1));
	CPPUNIT_ASSERT_EQUAL(4, actualResult26.at(2));
	CPPUNIT_ASSERT_EQUAL(5, actualResult26.at(3));
	CPPUNIT_ASSERT_EQUAL(6, actualResult26.at(4));
	CPPUNIT_ASSERT_EQUAL(7, actualResult26.at(5));
	CPPUNIT_ASSERT_EQUAL(8, actualResult26.at(6));
	CPPUNIT_ASSERT_EQUAL(9, actualResult26.at(7));
	CPPUNIT_ASSERT_EQUAL(10, actualResult26.at(8));

	QTNode* follows27 = new QTNode("Follows");
	QTNode* first27 = new QTNode("s2");
	QTNode* second27 = new QTNode("a2");
	first27->setParent(follows27);
	follows27->addChild(first27);
	second27->setParent(follows27);
	follows27->addChild(second27);
	QueryTree* query27 = new QueryTree();
	query27->getRootNode()->getChild(1)->addChild(follows27);

	vector<int> actualResult27 = qe->solve("a2", &table1, query27); // assign a2; stmt s2; Select a2 such that Follows(s2, a2) | Expected <2, 4, 5, 8>

	CPPUNIT_ASSERT_EQUAL((size_t)4, actualResult27.size());
	CPPUNIT_ASSERT_EQUAL(2, actualResult27.at(0));
	CPPUNIT_ASSERT_EQUAL(4, actualResult27.at(1));
	CPPUNIT_ASSERT_EQUAL(5, actualResult27.at(2));
	CPPUNIT_ASSERT_EQUAL(8, actualResult27.at(3));

	QTNode* follows28 = new QTNode("Follows");
	QTNode* first28 = new QTNode("s2");
	QTNode* second28 = new QTNode("a1");
	first28->setParent(follows28);
	follows28->addChild(first28);
	second28->setParent(follows28);
	follows28->addChild(second28);
	QueryTree* query28 = new QueryTree();
	query28->getRootNode()->getChild(1)->addChild(follows28);

	vector<int> actualResult28 = qe->solve("a1", &table1, query28); // stmt s2; Select a1 such that Follows(s2, a1) | Expected <> (none because a1 is not in synonym table)

	CPPUNIT_ASSERT(actualResult28.empty());

	QTNode* follows29 = new QTNode("Follows");
	QTNode* first29 = new QTNode("s2");
	QTNode* second29 = new QTNode("w3");
	first29->setParent(follows29);
	follows29->addChild(first29);
	second29->setParent(follows29);
	follows29->addChild(second29);
	QueryTree* query29 = new QueryTree();
	query29->getRootNode()->getChild(1)->addChild(follows29);

	vector<int> actualResult29 = qe->solve("w3", &table1, query29); // while w3; stmt s2; Select w3 such that Follows(s2, w3) | Expected <3, 6, 7, 9, 10>

	CPPUNIT_ASSERT_EQUAL((size_t)5, actualResult29.size());
	CPPUNIT_ASSERT_EQUAL(3, actualResult29.at(0));
	CPPUNIT_ASSERT_EQUAL(6, actualResult29.at(1));
	CPPUNIT_ASSERT_EQUAL(7, actualResult29.at(2));
	CPPUNIT_ASSERT_EQUAL(9, actualResult29.at(3));
	CPPUNIT_ASSERT_EQUAL(10, actualResult29.at(4));

	QTNode* follows30 = new QTNode("Follows");
	QTNode* first30 = new QTNode("a1");
	QTNode* second30 = new QTNode("s1");
	first30->setParent(follows30);
	follows30->addChild(first30);
	second30->setParent(follows30);
	follows30->addChild(second30);
	QueryTree* query30 = new QueryTree();
	query30->getRootNode()->getChild(1)->addChild(follows30);

	vector<int> actualResult30 = qe->solve("s1", &table1, query30); // stmt s1; Select s1 such that Follows(a1, s1) | Expected <> (none because a1  is not in synonym table)

	CPPUNIT_ASSERT(actualResult30.empty());

	QTNode* follows31 = new QTNode("Follows");
	QTNode* first31 = new QTNode("a2");
	QTNode* second31 = new QTNode("s1");
	first31->setParent(follows31);
	follows31->addChild(first31);
	second31->setParent(follows31);
	follows31->addChild(second31);
	QueryTree* query31 = new QueryTree();
	query31->getRootNode()->getChild(1)->addChild(follows31);

	vector<int> actualResult31 = qe->solve("s1", &table1, query31); // stmt s1; assign a2; Select s1 such that Follows(a2, s1) | Expected <2, 3, 5, 6, 9>

	CPPUNIT_ASSERT_EQUAL((size_t)5, actualResult31.size());
	CPPUNIT_ASSERT_EQUAL(2, actualResult31.at(0));
	CPPUNIT_ASSERT_EQUAL(3, actualResult31.at(1));
	CPPUNIT_ASSERT_EQUAL(5, actualResult31.at(2));
	CPPUNIT_ASSERT_EQUAL(6, actualResult31.at(3));
	CPPUNIT_ASSERT_EQUAL(9, actualResult31.at(4));

	QTNode* follows32 = new QTNode("Follows");
	QTNode* first32 = new QTNode("w3");
	QTNode* second32 = new QTNode("s1");
	first32->setParent(follows32);
	follows32->addChild(first32);
	second32->setParent(follows32);
	follows32->addChild(second32);
	QueryTree* query32 = new QueryTree();
	query32->getRootNode()->getChild(1)->addChild(follows32);

	vector<int> expectedResult32;
	expectedResult32.push_back(4);
	expectedResult32.push_back(7);
	expectedResult32.push_back(8);
	expectedResult32.push_back(10);

	vector<int> actualResult32 = qe->solve("s1", &table1, query32); // stmt s1; while w3; Select s1 such that Follows(w3, s1) | Expected <4, 7, 8, 10>

	CPPUNIT_ASSERT_EQUAL((size_t)4, actualResult32.size());
	CPPUNIT_ASSERT_EQUAL(4, actualResult32.at(0));
	CPPUNIT_ASSERT_EQUAL(7, actualResult32.at(1));
	CPPUNIT_ASSERT_EQUAL(8, actualResult32.at(2));
	CPPUNIT_ASSERT_EQUAL(10, actualResult32.at(3));

	QTNode* follows33 = new QTNode("Follows");
	QTNode* first33 = new QTNode("a2");
	QTNode* second33 = new QTNode("a3");
	first33->setParent(follows33);
	follows33->addChild(first33);
	second33->setParent(follows33);
	follows33->addChild(second33);
	QueryTree* query33 = new QueryTree();
	query33->getRootNode()->getChild(1)->addChild(follows33);

	vector<int> actualResult33 = qe->solve("a3", &table1, query33); // assign a2; assign a3; Select a3 such that Follows(a2, a3) | Expected <2, 5>

	CPPUNIT_ASSERT_EQUAL((size_t)2, actualResult33.size());
	CPPUNIT_ASSERT_EQUAL(2, actualResult33.at(0));
	CPPUNIT_ASSERT_EQUAL(5, actualResult33.at(1));

	QTNode* follows34 = new QTNode("Follows");
	QTNode* first34 = new QTNode("w3");
	QTNode* second34 = new QTNode("a2");
	first34->setParent(follows34);
	follows34->addChild(first34);
	second34->setParent(follows34);
	follows34->addChild(second34);
	QueryTree* query34 = new QueryTree();
	query34->getRootNode()->getChild(1)->addChild(follows34);

	vector<int> actualResult34 = qe->solve("a2", &table1, query34); // assign a2; while w3; Select a2 such that Follows(w3, a2) | Expected <4, 8>

	CPPUNIT_ASSERT_EQUAL((size_t)2, actualResult34.size());
	CPPUNIT_ASSERT_EQUAL(4, actualResult34.at(0));
	CPPUNIT_ASSERT_EQUAL(8, actualResult34.at(1));

	QTNode* follows35 = new QTNode("Follows");
	QTNode* first35 = new QTNode("a2");
	QTNode* second35 = new QTNode("w3");
	first35->setParent(follows35);
	follows35->addChild(first35);
	second35->setParent(follows35);
	follows35->addChild(second35);
	QueryTree* query35 = new QueryTree();
	query35->getRootNode()->getChild(1)->addChild(follows35);

	vector<int> actualResult35 = qe->solve("w3", &table1, query35); // while w3; assign a2; Select w3 such that Follows(a2, w3) | Expected <3, 6, 9>

	CPPUNIT_ASSERT_EQUAL((size_t)3, actualResult35.size());
	CPPUNIT_ASSERT_EQUAL(3, actualResult35.at(0));
	CPPUNIT_ASSERT_EQUAL(6, actualResult35.at(1));
	CPPUNIT_ASSERT_EQUAL(9, actualResult35.at(2));

	QTNode* follows36 = new QTNode("Follows");
	QTNode* first36 = new QTNode("w3");
	QTNode* second36 = new QTNode("w4");
	first36->setParent(follows36);
	follows36->addChild(first36);
	second36->setParent(follows36);
	follows36->addChild(second36);
	QueryTree* query36 = new QueryTree();
	query36->getRootNode()->getChild(1)->addChild(follows36);

	vector<int> actualResult36 = qe->solve("w4", &table1, query36); // while w3; while w4; Select w4 such that Follows(w3, w4) | Expected <7, 10>

	CPPUNIT_ASSERT_EQUAL((size_t)2, actualResult36.size());
	CPPUNIT_ASSERT_EQUAL(7, actualResult36.at(0));
	CPPUNIT_ASSERT_EQUAL(10, actualResult36.at(1));

	QTNode* follows37 = new QTNode("Follows");
	QTNode* first37 = new QTNode("s1");
	QTNode* second37 = new QTNode(1);
	first37->setParent(follows37);
	follows37->addChild(first37);
	second37->setParent(follows37);
	follows37->addChild(second37);
	QueryTree* query37 = new QueryTree();
	query37->getRootNode()->getChild(1)->addChild(follows37);

	vector<int> actualResult37 = qe->solve("s1", &table1, query37); // stmt s1; Select s1 such that Follows(s1, 1) | Expected <> (none)
	
	CPPUNIT_ASSERT(actualResult37.empty());

	QTNode* follows38 = new QTNode("Follows");
	QTNode* first38 = new QTNode("s1");
	QTNode* second38 = new QTNode(10);
	first38->setParent(follows38);
	follows38->addChild(first38);
	second38->setParent(follows38);
	follows38->addChild(second38);
	QueryTree* query38 = new QueryTree();
	query38->getRootNode()->getChild(1)->addChild(follows38);

	vector<int> actualResult38 = qe->solve("s1", &table1, query38); // stmt s1; Select s1 such that Follows(s1, 10) | Expected <9>
	
	CPPUNIT_ASSERT_EQUAL((size_t)1, actualResult38.size());
	CPPUNIT_ASSERT_EQUAL(9, actualResult38.at(0));

	QTNode* follows39 = new QTNode("Follows");
	QTNode* first39 = new QTNode("s1");
	QTNode* second39 = new QTNode(11);
	first39->setParent(follows39);
	follows39->addChild(first39);
	second39->setParent(follows39);
	follows39->addChild(second39);
	QueryTree* query39 = new QueryTree();
	query39->getRootNode()->getChild(1)->addChild(follows39);

	vector<int> actualResult39 = qe->solve("s1", &table1, query39); // stmt s1; Select s1 such that Follows(s1, 11) | Expected <> (none)
	
	CPPUNIT_ASSERT(actualResult39.empty());

	QTNode* follows40 = new QTNode("Follows");
	QTNode* first40 = new QTNode(0);
	QTNode* second40 = new QTNode("s1");
	first40->setParent(follows40);
	follows40->addChild(first40);
	second40->setParent(follows40);
	follows40->addChild(second40);
	QueryTree* query40 = new QueryTree();
	query40->getRootNode()->getChild(1)->addChild(follows40);

	vector<int> actualResult40 = qe->solve("s1", &table1, query40); // stmt s1; Select s1 such that Follows(0, s1) | Expected <> (none)
	
	CPPUNIT_ASSERT(actualResult40.empty());

	QTNode* follows41 = new QTNode("Follows");
	QTNode* first41 = new QTNode(9);
	QTNode* second41 = new QTNode("s1");
	first41->setParent(follows41);
	follows41->addChild(first41);
	second41->setParent(follows41);
	follows41->addChild(second41);
	QueryTree* query41 = new QueryTree();
	query41->getRootNode()->getChild(1)->addChild(follows41);

	vector<int> actualResult41 = qe->solve("s1", &table1, query41); // stmt s1; Select s1 such that Follows(9, s1) | Expected <10>
	
	CPPUNIT_ASSERT_EQUAL((size_t)1, actualResult41.size());
	CPPUNIT_ASSERT_EQUAL(10, actualResult41.at(0));

	QTNode* follows42 = new QTNode("Follows");
	QTNode* first42 = new QTNode(10);
	QTNode* second42 = new QTNode("s1");
	first42->setParent(follows42);
	follows42->addChild(first42);
	second42->setParent(follows42);
	follows42->addChild(second42);
	QueryTree* query42 = new QueryTree();
	query42->getRootNode()->getChild(1)->addChild(follows42);

	vector<int> actualResult42 = qe->solve("s1", &table1, query42); // stmt s1; Select s1 such that Follows(10, s1) | Expected <> (none)
	
	CPPUNIT_ASSERT(actualResult42.empty());

	QTNode* follows43 = new QTNode("Follows");
	QTNode* first43 = new QTNode(1);
	QTNode* second43 = new QTNode(2);
	first43->setParent(follows43);
	follows43->addChild(first43);
	second43->setParent(follows43);
	follows43->addChild(second43);
	QueryTree* query43 = new QueryTree();
	query43->getRootNode()->getChild(1)->addChild(follows43);

	vector<int> actualResult43 = qe->solve("s1", &table1, query43); // stmt s1; Select s1 such that Follows(1, 2) | Expected <1, 2, 3, 4, 5, 6, 7, 8, 9, 10>
	
	CPPUNIT_ASSERT_EQUAL((size_t)10, actualResult43.size());
	CPPUNIT_ASSERT_EQUAL(1, actualResult43.at(0));
	CPPUNIT_ASSERT_EQUAL(2, actualResult43.at(1));
	CPPUNIT_ASSERT_EQUAL(3, actualResult43.at(2));
	CPPUNIT_ASSERT_EQUAL(4, actualResult43.at(3));
	CPPUNIT_ASSERT_EQUAL(5, actualResult43.at(4));
	CPPUNIT_ASSERT_EQUAL(6, actualResult43.at(5));
	CPPUNIT_ASSERT_EQUAL(7, actualResult43.at(6));
	CPPUNIT_ASSERT_EQUAL(8, actualResult43.at(7));
	CPPUNIT_ASSERT_EQUAL(9, actualResult43.at(8));
	CPPUNIT_ASSERT_EQUAL(10, actualResult43.at(9));

	QTNode* follows44 = new QTNode("Follows");
	QTNode* first44 = new QTNode(1);
	QTNode* second44 = new QTNode(3);
	first44->setParent(follows44);
	follows44->addChild(first44);
	second44->setParent(follows44);
	follows44->addChild(second44);
	QueryTree* query44 = new QueryTree();
	query44->getRootNode()->getChild(1)->addChild(follows44);

	vector<int> actualResult44 = qe->solve("s1", &table1, query44); // stmt s1; Select s1 such that Follows(1, 3) | Expected <> (none)
	
	CPPUNIT_ASSERT(actualResult44.empty());

	QTNode* follows45 = new QTNode("Follows");
	QTNode* first45 = new QTNode(1);
	QTNode* second45 = new QTNode(2);
	first45->setParent(follows45);
	follows45->addChild(first45);
	second45->setParent(follows45);
	follows45->addChild(second45);
	QueryTree* query45 = new QueryTree();
	query45->getRootNode()->getChild(1)->addChild(follows45);

	vector<int> actualResult45 = qe->solve("a2", &table1, query45); // assign a2; Select a2 such that Follows(1, 2) | Expected <1, 2, 4, 5, 8>

	CPPUNIT_ASSERT_EQUAL((size_t)5, actualResult45.size());
	CPPUNIT_ASSERT_EQUAL(1, actualResult45.at(0));
	CPPUNIT_ASSERT_EQUAL(2, actualResult45.at(1));
	CPPUNIT_ASSERT_EQUAL(4, actualResult45.at(2));
	CPPUNIT_ASSERT_EQUAL(5, actualResult45.at(3));
	CPPUNIT_ASSERT_EQUAL(8, actualResult45.at(4));

	QTNode* follows46 = new QTNode("Follows");
	QTNode* first46 = new QTNode(1);
	QTNode* second46 = new QTNode(2);
	first46->setParent(follows46);
	follows46->addChild(first46);
	second46->setParent(follows46);
	follows46->addChild(second46);
	QueryTree* query46 = new QueryTree();
	query46->getRootNode()->getChild(1)->addChild(follows46);

	vector<int> actualResult46 = qe->solve("w3", &table1, query46); // while w3; Select w3 such that Follows(1, 2) | Expected <3, 6, 7, 9, 10>
	
	CPPUNIT_ASSERT_EQUAL((size_t)5, actualResult46.size());
	CPPUNIT_ASSERT_EQUAL(3, actualResult46.at(0));
	CPPUNIT_ASSERT_EQUAL(6, actualResult46.at(1));
	CPPUNIT_ASSERT_EQUAL(7, actualResult46.at(2));
	CPPUNIT_ASSERT_EQUAL(9, actualResult46.at(3));
	CPPUNIT_ASSERT_EQUAL(10, actualResult46.at(4));

	QTNode* follows47 = new QTNode("Follows");
	QTNode* first47 = new QTNode(1);
	QTNode* second47 = new QTNode(2);
	first47->setParent(follows47);
	follows47->addChild(first47);
	second47->setParent(follows47);
	follows47->addChild(second47);
	QueryTree* query47 = new QueryTree();
	query47->getRootNode()->getChild(1)->addChild(follows47);

	vector<int> actualResult47 = qe->solve("v4", &table1, query47); // variable v4; Select v4 such that Follows(1, 2) | Expected <1, 2, 3, 4, 5, 6>
	
	CPPUNIT_ASSERT_EQUAL((size_t)6, actualResult47.size());
	CPPUNIT_ASSERT_EQUAL(0, actualResult47.at(0));
	CPPUNIT_ASSERT_EQUAL(1, actualResult47.at(1));
	CPPUNIT_ASSERT_EQUAL(2, actualResult47.at(2));
	CPPUNIT_ASSERT_EQUAL(3, actualResult47.at(3));
	CPPUNIT_ASSERT_EQUAL(4, actualResult47.at(4));
	CPPUNIT_ASSERT_EQUAL(5, actualResult47.at(5));

	QTNode* follows49 = new QTNode("Follows");
	QTNode* first49 = new QTNode(1);
	QTNode* second49 = new QTNode("s2");
	first49->setParent(follows49);
	follows49->addChild(first49);
	second49->setParent(follows49);
	follows49->addChild(second49);
	QueryTree* query49 = new QueryTree();
	query49->getRootNode()->getChild(1)->addChild(follows49);

	vector<int> actualResult49 = qe->solve("s1", &table1, query49); // stmt s1, s2; Select s1 such that Follows(1, s2) | Expected <1, 2, 3, 4, 5, 6, 7, 8, 9, 10>
	
	CPPUNIT_ASSERT_EQUAL((size_t)10, actualResult49.size());
	CPPUNIT_ASSERT_EQUAL(1, actualResult49.at(0));
	CPPUNIT_ASSERT_EQUAL(2, actualResult49.at(1));
	CPPUNIT_ASSERT_EQUAL(3, actualResult49.at(2));
	CPPUNIT_ASSERT_EQUAL(4, actualResult49.at(3));
	CPPUNIT_ASSERT_EQUAL(5, actualResult49.at(4));
	CPPUNIT_ASSERT_EQUAL(6, actualResult49.at(5));
	CPPUNIT_ASSERT_EQUAL(7, actualResult49.at(6));
	CPPUNIT_ASSERT_EQUAL(8, actualResult49.at(7));
	CPPUNIT_ASSERT_EQUAL(9, actualResult49.at(8));
	CPPUNIT_ASSERT_EQUAL(10, actualResult49.at(9));

	QTNode* follows50 = new QTNode("Follows");
	QTNode* first50 = new QTNode(10);
	QTNode* second50 = new QTNode("s2");
	first50->setParent(follows50);
	follows50->addChild(first50);
	second50->setParent(follows50);
	follows50->addChild(second50);
	QueryTree* query50 = new QueryTree();
	query50->getRootNode()->getChild(1)->addChild(follows50);

	vector<int> actualResult50 = qe->solve("s1", &table1, query50); // stmt s1, s2; Select s1 such that Follows(10, s2) | Expected <> (none)
	
	CPPUNIT_ASSERT(actualResult50.empty());

	QTNode* follows51 = new QTNode("Follows");
	QTNode* first51 = new QTNode(1);
	QTNode* second51 = new QTNode("a3");
	first51->setParent(follows51);
	follows51->addChild(first51);
	second51->setParent(follows51);
	follows51->addChild(second51);
	QueryTree* query51 = new QueryTree();
	query51->getRootNode()->getChild(1)->addChild(follows51);

	vector<int> actualResult51 = qe->solve("a2", &table1, query51); // assign a2, a3; Select a2 such that Follows(1, a3) | Expected <1, 2, 4, 5, 8>
	
	CPPUNIT_ASSERT_EQUAL((size_t)5, actualResult51.size());
	CPPUNIT_ASSERT_EQUAL(1, actualResult51.at(0));
	CPPUNIT_ASSERT_EQUAL(2, actualResult51.at(1));
	CPPUNIT_ASSERT_EQUAL(4, actualResult51.at(2));
	CPPUNIT_ASSERT_EQUAL(5, actualResult51.at(3));
	CPPUNIT_ASSERT_EQUAL(8, actualResult51.at(4));

	QTNode* follows52 = new QTNode("Follows");
	QTNode* first52 = new QTNode(2);
	QTNode* second52 = new QTNode("a3");
	first52->setParent(follows52);
	follows52->addChild(first52);
	second52->setParent(follows52);
	follows52->addChild(second52);
	QueryTree* query52 = new QueryTree();
	query52->getRootNode()->getChild(1)->addChild(follows52);

	vector<int> actualResult52 = qe->solve("a2", &table1, query52); // assign a2, a3; Select a2 such that Follows(2, a3) | Expected <> (none)
	
	CPPUNIT_ASSERT(actualResult52.empty());

	QTNode* follows53 = new QTNode("Follows");
	QTNode* first53 = new QTNode(2);
	QTNode* second53 = new QTNode("w4");
	first53->setParent(follows53);
	follows53->addChild(first53);
	second53->setParent(follows53);
	follows53->addChild(second53);
	QueryTree* query53 = new QueryTree();
	query53->getRootNode()->getChild(1)->addChild(follows53);

	vector<int> actualResult53 = qe->solve("w3", &table1, query53); // while w3, w4; Select w3 such that Follows(2, w4) | Expected <3, 6, 7, 9, 10>
	
	CPPUNIT_ASSERT_EQUAL((size_t)5, actualResult53.size());
	CPPUNIT_ASSERT_EQUAL(3, actualResult53.at(0));
	CPPUNIT_ASSERT_EQUAL(6, actualResult53.at(1));
	CPPUNIT_ASSERT_EQUAL(7, actualResult53.at(2));
	CPPUNIT_ASSERT_EQUAL(9, actualResult53.at(3));
	CPPUNIT_ASSERT_EQUAL(10, actualResult53.at(4));

	QTNode* follows54 = new QTNode("Follows");
	QTNode* first54 = new QTNode(1);
	QTNode* second54 = new QTNode("w4");
	first54->setParent(follows54);
	follows54->addChild(first54);
	second54->setParent(follows54);
	follows54->addChild(second54);
	QueryTree* query54 = new QueryTree();
	query54->getRootNode()->getChild(1)->addChild(follows54);

	vector<int> actualResult54 = qe->solve("w3", &table1, query54); // while w3, w4; Select w3 such that Follows(1, w4) | Expected <> (none)
	
	CPPUNIT_ASSERT(actualResult54.empty());

	QTNode* follows55 = new QTNode("Follows");
	QTNode* first55 = new QTNode("s2");
	QTNode* second55 = new QTNode(2);
	first55->setParent(follows55);
	follows55->addChild(first55);
	second55->setParent(follows55);
	follows55->addChild(second55);
	QueryTree* query55 = new QueryTree();
	query55->getRootNode()->getChild(1)->addChild(follows55);

	vector<int> actualResult55 = qe->solve("s1", &table1, query55); // stmt s1, s2; Select s1 such that Follows(s2, 2) | Expected <1, 2, 3, 4, 5, 6, 7, 8, 9, 10>
	
    CPPUNIT_ASSERT_EQUAL((size_t)10, actualResult55.size());
    CPPUNIT_ASSERT_EQUAL(1, actualResult55.at(0));
    CPPUNIT_ASSERT_EQUAL(2, actualResult55.at(1));
    CPPUNIT_ASSERT_EQUAL(3, actualResult55.at(2));
    CPPUNIT_ASSERT_EQUAL(4, actualResult55.at(3));
    CPPUNIT_ASSERT_EQUAL(5, actualResult55.at(4));
    CPPUNIT_ASSERT_EQUAL(6, actualResult55.at(5));
    CPPUNIT_ASSERT_EQUAL(7, actualResult55.at(6));
    CPPUNIT_ASSERT_EQUAL(8, actualResult55.at(7));
    CPPUNIT_ASSERT_EQUAL(9, actualResult55.at(8));
    CPPUNIT_ASSERT_EQUAL(10, actualResult55.at(9));

	QTNode* follows56 = new QTNode("Follows");
	QTNode* first56 = new QTNode("s2");
	QTNode* second56 = new QTNode(1);
	first56->setParent(follows56);
	follows56->addChild(first56);
	second56->setParent(follows56);
	follows56->addChild(second56);
	QueryTree* query56 = new QueryTree();
	query56->getRootNode()->getChild(1)->addChild(follows56);

	vector<int> actualResult56 = qe->solve("s1", &table1, query56); // stmt s1, s2; Select s1 such that Follows(s2, 1) | Expected <> (none)
	
	CPPUNIT_ASSERT(actualResult56.empty());

	QTNode* follows57 = new QTNode("Follows");
	QTNode* first57 = new QTNode("a3");
	QTNode* second57 = new QTNode(3);
	first57->setParent(follows57);
	follows57->addChild(first57);
	second57->setParent(follows57);
	follows57->addChild(second57);
	QueryTree* query57 = new QueryTree();
	query57->getRootNode()->getChild(1)->addChild(follows57);

	vector<int> actualResult57 = qe->solve("a2", &table1, query57); // assign a2, a3; Select a2 such that Follows(a3, 3) | Expected <1, 2, 4, 5, 8>
	
    CPPUNIT_ASSERT_EQUAL((size_t)5, actualResult57.size());
    CPPUNIT_ASSERT_EQUAL(1, actualResult57.at(0));
    CPPUNIT_ASSERT_EQUAL(2, actualResult57.at(1));
    CPPUNIT_ASSERT_EQUAL(4, actualResult57.at(2));
    CPPUNIT_ASSERT_EQUAL(5, actualResult57.at(3));
    CPPUNIT_ASSERT_EQUAL(8, actualResult57.at(4));

	QTNode* follows58 = new QTNode("Follows");
	QTNode* first58 = new QTNode("a3");
	QTNode* second58 = new QTNode(4);
	first58->setParent(follows58);
	follows58->addChild(first58);
	second58->setParent(follows58);
	follows58->addChild(second58);
	QueryTree* query58 = new QueryTree();
	query58->getRootNode()->getChild(1)->addChild(follows58);

	vector<int> actualResult58 = qe->solve("a2", &table1, query58); // assign a2, a3; Select a2 such that Follows(a3, 4) | Expected <> (none)
	
	CPPUNIT_ASSERT(actualResult58.empty());

	QTNode* follows59 = new QTNode("Follows");
	QTNode* first59 = new QTNode("w4");
	QTNode* second59 = new QTNode(4);
	first59->setParent(follows59);
	follows59->addChild(first59);
	second59->setParent(follows59);
	follows59->addChild(second59);
	QueryTree* query59 = new QueryTree();
	query59->getRootNode()->getChild(1)->addChild(follows59);

	vector<int> actualResult59 = qe->solve("w3", &table1, query59); // while w3, w4; Select w3 such that Follows(w4, 4) | Expected <3, 6, 7, 9, 10>
	
    CPPUNIT_ASSERT_EQUAL((size_t)5, actualResult59.size());
    CPPUNIT_ASSERT_EQUAL(3, actualResult59.at(0));
    CPPUNIT_ASSERT_EQUAL(6, actualResult59.at(1));
    CPPUNIT_ASSERT_EQUAL(7, actualResult59.at(2));
    CPPUNIT_ASSERT_EQUAL(9, actualResult59.at(3));
    CPPUNIT_ASSERT_EQUAL(10, actualResult59.at(4));

	QTNode* follows60 = new QTNode("Follows");
	QTNode* first60 = new QTNode("w4");
	QTNode* second60 = new QTNode(3);
	first60->setParent(follows60);
	follows60->addChild(first60);
	second60->setParent(follows60);
	follows60->addChild(second60);
	QueryTree* query60 = new QueryTree();
	query60->getRootNode()->getChild(1)->addChild(follows60);

	vector<int> actualResult60 = qe->solve("w3", &table1, query60); // while w3, w4; Select w3 such that Follows(w4, 3) | Expected <> (none)
	
	CPPUNIT_ASSERT(actualResult60.empty());

	QTNode* follows61 = new QTNode("Follows");
	QTNode* first61 = new QTNode("s1");
	QTNode* second61 = new QTNode("s2");
	first61->setParent(follows61);
	follows61->addChild(first61);
	second61->setParent(follows61);
	follows61->addChild(second61);
	QueryTree* query61 = new QueryTree();
	query61->getRootNode()->getChild(1)->addChild(follows61);

	vector<int> actualResult61 = qe->solve("a2", &table1, query61); // stmt s1, s2; assign a2; Select a2 such that Follows(s1, s2) | Expected <1, 2, 4, 5, 8>
	
    CPPUNIT_ASSERT_EQUAL((size_t)5, actualResult61.size());
    CPPUNIT_ASSERT_EQUAL(1, actualResult61.at(0));
    CPPUNIT_ASSERT_EQUAL(2, actualResult61.at(1));
    CPPUNIT_ASSERT_EQUAL(4, actualResult61.at(2));
    CPPUNIT_ASSERT_EQUAL(5, actualResult61.at(3));
    CPPUNIT_ASSERT_EQUAL(8, actualResult61.at(4));

	QTNode* follows62 = new QTNode("Follows");
	QTNode* first62 = new QTNode("s1");
	QTNode* second62 = new QTNode("a3");
	first62->setParent(follows62);
	follows62->addChild(first62);
	second62->setParent(follows62);
	follows62->addChild(second62);
	QueryTree* query62 = new QueryTree();
	query62->getRootNode()->getChild(1)->addChild(follows62);

	vector<int> actualResult62 = qe->solve("a2", &table1, query62); // stmt s1; assign a2, a3; Select a2 such that Follows(s1, a3) | Expected <1, 2, 4, 5, 8>
	
    CPPUNIT_ASSERT_EQUAL((size_t)5, actualResult62.size());
    CPPUNIT_ASSERT_EQUAL(1, actualResult62.at(0));
    CPPUNIT_ASSERT_EQUAL(2, actualResult62.at(1));
    CPPUNIT_ASSERT_EQUAL(4, actualResult62.at(2));
    CPPUNIT_ASSERT_EQUAL(5, actualResult62.at(3));
    CPPUNIT_ASSERT_EQUAL(8, actualResult62.at(4));

	QTNode* follows63 = new QTNode("Follows");
	QTNode* first63 = new QTNode("s1");
	QTNode* second63 = new QTNode("w3");
	first63->setParent(follows63);
	follows63->addChild(first63);
	second63->setParent(follows63);
	follows63->addChild(second63);
	QueryTree* query63 = new QueryTree();
	query63->getRootNode()->getChild(1)->addChild(follows63);

	vector<int> actualResult63 = qe->solve("a2", &table1, query63); // stmt s1; assign a2; while w3; Select a2 such that Follows(s1, w3) | Expected <1, 2, 4, 5, 8>
	
    CPPUNIT_ASSERT_EQUAL((size_t)5, actualResult63.size());
    CPPUNIT_ASSERT_EQUAL(1, actualResult63.at(0));
    CPPUNIT_ASSERT_EQUAL(2, actualResult63.at(1));
    CPPUNIT_ASSERT_EQUAL(4, actualResult63.at(2));
    CPPUNIT_ASSERT_EQUAL(5, actualResult63.at(3));
    CPPUNIT_ASSERT_EQUAL(8, actualResult63.at(4));

	QTNode* follows64 = new QTNode("Follows");
	QTNode* first64 = new QTNode("a2");
	QTNode* second64 = new QTNode("s1");
	first64->setParent(follows64);
	follows64->addChild(first64);
	second64->setParent(follows64);
	follows64->addChild(second64);
	QueryTree* query64 = new QueryTree();
	query64->getRootNode()->getChild(1)->addChild(follows64);

	vector<int> actualResult64 = qe->solve("w3", &table1, query64); // stmt s1; assign a2; while w3; Select w3 such that Follows(a2, s1) | Expected <3, 6, 7, 9, 10>
	
    CPPUNIT_ASSERT_EQUAL((size_t)5, actualResult64.size());
    CPPUNIT_ASSERT_EQUAL(3, actualResult64.at(0));
    CPPUNIT_ASSERT_EQUAL(6, actualResult64.at(1));
    CPPUNIT_ASSERT_EQUAL(7, actualResult64.at(2));
    CPPUNIT_ASSERT_EQUAL(9, actualResult64.at(3));
    CPPUNIT_ASSERT_EQUAL(10, actualResult64.at(4));

	QTNode* follows65 = new QTNode("Follows");
	QTNode* first65 = new QTNode("a2");
	QTNode* second65 = new QTNode("a3");
	first65->setParent(follows65);
	follows65->addChild(first65);
	second65->setParent(follows65);
	follows65->addChild(second65);
	QueryTree* query65 = new QueryTree();
	query65->getRootNode()->getChild(1)->addChild(follows65);

	vector<int> actualResult65 = qe->solve("w3", &table1, query65); // assign a2, a3; while w3; Select w3 such that Follows(a2, a3) | Expected <3, 6, 7, 9, 10>
	
    CPPUNIT_ASSERT_EQUAL((size_t)5, actualResult65.size());
    CPPUNIT_ASSERT_EQUAL(3, actualResult65.at(0));
    CPPUNIT_ASSERT_EQUAL(6, actualResult65.at(1));
    CPPUNIT_ASSERT_EQUAL(7, actualResult65.at(2));
    CPPUNIT_ASSERT_EQUAL(9, actualResult65.at(3));
    CPPUNIT_ASSERT_EQUAL(10, actualResult65.at(4));

	QTNode* follows66 = new QTNode("Follows");
	QTNode* first66 = new QTNode("a2");
	QTNode* second66 = new QTNode("w4");
	first66->setParent(follows66);
	follows66->addChild(first66);
	second66->setParent(follows66);
	follows66->addChild(second66);
	QueryTree* query66 = new QueryTree();
	query66->getRootNode()->getChild(1)->addChild(follows66);

	vector<int> actualResult66 = qe->solve("w3", &table1, query66); // assign a2; while w3, w4; Select w3 such that Follows(a2, w4) | Expected <3, 6, 7, 9, 10>
	
    CPPUNIT_ASSERT_EQUAL((size_t)5, actualResult66.size());
    CPPUNIT_ASSERT_EQUAL(3, actualResult66.at(0));
    CPPUNIT_ASSERT_EQUAL(6, actualResult66.at(1));
    CPPUNIT_ASSERT_EQUAL(7, actualResult66.at(2));
    CPPUNIT_ASSERT_EQUAL(9, actualResult66.at(3));
    CPPUNIT_ASSERT_EQUAL(10, actualResult66.at(4));

	QTNode* follows67 = new QTNode("Follows");
	QTNode* first67 = new QTNode("w4");
	QTNode* second67 = new QTNode("s1");
	first67->setParent(follows67);
	follows67->addChild(first67);
	second67->setParent(follows67);
	follows67->addChild(second67);
	QueryTree* query67 = new QueryTree();
	query67->getRootNode()->getChild(1)->addChild(follows67);

	vector<int> actualResult67 = qe->solve("w3", &table1, query67); // stmt s1; while w3, w4; Select w3 such that Follows(w4, s1) | Expected <3, 6, 7, 9, 10>
	
    CPPUNIT_ASSERT_EQUAL((size_t)5, actualResult67.size());
    CPPUNIT_ASSERT_EQUAL(3, actualResult67.at(0));
    CPPUNIT_ASSERT_EQUAL(6, actualResult67.at(1));
    CPPUNIT_ASSERT_EQUAL(7, actualResult67.at(2));
    CPPUNIT_ASSERT_EQUAL(9, actualResult67.at(3));
    CPPUNIT_ASSERT_EQUAL(10, actualResult67.at(4));

	QTNode* follows68 = new QTNode("Follows");
	QTNode* first68 = new QTNode("w4");
	QTNode* second68 = new QTNode("a2");
	first68->setParent(follows68);
	follows68->addChild(first68);
	second68->setParent(follows68);
	follows68->addChild(second68);
	QueryTree* query68 = new QueryTree();
	query68->getRootNode()->getChild(1)->addChild(follows68);

	vector<int> actualResult68 = qe->solve("w3", &table1, query68); // assign a2; while w3, w4; Select w3 such that Follows(w4, a2) | Expected <3, 6, 7, 9, 10>
	
    CPPUNIT_ASSERT_EQUAL((size_t)5, actualResult68.size());
    CPPUNIT_ASSERT_EQUAL(3, actualResult68.at(0));
    CPPUNIT_ASSERT_EQUAL(6, actualResult68.at(1));
    CPPUNIT_ASSERT_EQUAL(7, actualResult68.at(2));
    CPPUNIT_ASSERT_EQUAL(9, actualResult68.at(3));
    CPPUNIT_ASSERT_EQUAL(10, actualResult68.at(4));

	QTNode* follows69 = new QTNode("Follows");
	QTNode* first69 = new QTNode("w3");
	QTNode* second69 = new QTNode("w4");
	first69->setParent(follows69);
	follows69->addChild(first69);
	second69->setParent(follows69);
	follows69->addChild(second69);
	QueryTree* query69 = new QueryTree();
	query69->getRootNode()->getChild(1)->addChild(follows69);

	vector<int> actualResult69 = qe->solve("a2", &table1, query69); // assign a2; while w3, w4; Select a2 such that Follows(w3, w4) | Expected <1, 2, 4, 5, 8>
	
    CPPUNIT_ASSERT_EQUAL((size_t)5, actualResult69.size());
    CPPUNIT_ASSERT_EQUAL(1, actualResult69.at(0));
    CPPUNIT_ASSERT_EQUAL(2, actualResult69.at(1));
    CPPUNIT_ASSERT_EQUAL(4, actualResult69.at(2));
    CPPUNIT_ASSERT_EQUAL(5, actualResult69.at(3));
    CPPUNIT_ASSERT_EQUAL(8, actualResult69.at(4));
}

void QueryEvaluatorTest::testSolveForSuchThatModifies(){
	/** SIMPLE source code
	procedure p1{
	a = x;
	b = y;
	 while c{
	 d = y;
	 e =v;
	 while f{
	  while g{
	   h=u;
		while i{
		 a=b;
		 }}}}
	}
	**/
	PKBController pk;
	TNode stmt1("ASSIGN_NODE","a = x", 1,0);
	TNode stmt2("ASSIGN_NODE","b = y", 2,0);
	TNode stmt3("WHILE_NODE","c", 3,0);
	TNode stmt4("ASSIGN_NODE","d = t", 4,0);
	TNode stmt5("ASSIGN_NODE","e = v", 5,0);
	TNode stmt6("WHILE_NODE","f", 6,0);
	TNode stmt7("WHILE_NODE","g", 7,0);
	TNode stmt8("ASSIGN_NODE","h = u", 8,0);
	TNode stmt9("WHILE_NODE","i", 9,0);
	TNode stmt10("ASSIGN_NODE","a = b", 10,0);

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

	//modifies for procedures
	pk.modifiesTable.insertModifiesProc(0,0); //var: a
	pk.modifiesTable.insertModifiesProc(0,1); //var: b
	pk.modifiesTable.insertModifiesProc(0,5); //var: d
	pk.modifiesTable.insertModifiesProc(0,7); //var: e
	pk.modifiesTable.insertModifiesProc(0,11); //var: h

	//modifies for while statements
	pk.modifiesTable.insertModifiesStmt(3,0); //var: a
    pk.modifiesTable.insertModifiesStmt(3,5); //var: d
	pk.modifiesTable.insertModifiesStmt(3,7); //var: e
	pk.modifiesTable.insertModifiesStmt(3,11); //var: h
	pk.modifiesTable.insertModifiesStmt(6,0); //var: a
	pk.modifiesTable.insertModifiesStmt(6,11); //var: h
	pk.modifiesTable.insertModifiesStmt(7,0); //var: a
	pk.modifiesTable.insertModifiesStmt(7,11); //var: h
	pk.modifiesTable.insertModifiesStmt(9,0); //var: h
	
	//modifies for assign statements

    pk.modifiesTable.insertModifiesStmt(1,0); // var:a
    pk.modifiesTable.insertModifiesStmt(2,1);  // var:b
    pk.modifiesTable.insertModifiesStmt(4,5); // var:d
    pk.modifiesTable.insertModifiesStmt(5,7); // var:e
    pk.modifiesTable.insertModifiesStmt(8,11); // var:h
	pk.modifiesTable.insertModifiesStmt(10,0);

	pk.procTable.insertProc("p1");

	pk.varTable.insertVar("a"); // index 0
	pk.varTable.insertVar("b"); // index 1
	pk.varTable.insertVar("x"); // index 2
	pk.varTable.insertVar("y"); // index 3
	pk.varTable.insertVar("c"); // index 4
	pk.varTable.insertVar("d"); // index 5
	pk.varTable.insertVar("t"); // index 6
	pk.varTable.insertVar("e"); // index 7
	pk.varTable.insertVar("v"); // index 8
	pk.varTable.insertVar("f"); // index 9
	pk.varTable.insertVar("g"); // index 10
	pk.varTable.insertVar("h"); // index 11
	pk.varTable.insertVar("u"); // index 12
	pk.varTable.insertVar("i"); // index 13
	pk.varTable.insertVar("j"); // index 14

	QueryEvaluator* qe = new QueryEvaluator(&pk);

	// synonym table, add more if needed
	map<string, string> table1;
	table1["s1"]="stmt";
	table1["s2"]="stmt";
	table1["a1"]="assign";
	table1["a2"]="assign";
	table1["w1"]="while";
	table1["w2"]="while";
	table1["v1"]="variable";
	table1["v2"]="variable";
	table1["p1"]="procedure";

	/** 
   Test No: 1
   Test Type: stmt | <syn1> == <syn2> |  <syn3> specified
   Query:stmt s1; Select s1 such that Modifies(s1, "x")
   Expected Result: <>
   **/

	QTNode* modifies1 = new QTNode("Modifies");
	QTNode* first1 = new QTNode("s1");
	QTNode* second1 = new QTNode("x");
	first1->setParent(modifies1);
	modifies1->addChild(first1);
	second1->setParent(modifies1);
	modifies1->addChild(second1);
	QueryTree* query1 = new QueryTree();
	query1->getRootNode()->getChild(1)->addChild(modifies1);

	vector<int> actualResult1 = qe->solve("s1", &table1, query1); 
	
	CPPUNIT_ASSERT(actualResult1.empty());
	
	// /** 
 //  Test No: 2
 //  Test Type: proc | <syn1> == <syn2> |  <syn3> specified
 //  Query:procedure p1; Select p1 such that Modifies(p1, "x")
 //  Expected Result: <>
 //  **/
	//QTNode* modifies2 = new QTNode("Modifies");
	//QTNode* first2 = new QTNode("p1");
	//QTNode* second2 = new QTNode("x");
	//first2->setParent(modifies2);
	//modifies2->addChild(first2);
	//second2->setParent(modifies2);
	//modifies2->addChild(second2);
	//QueryTree* query2 = new QueryTree();
	//query2->getRootNode()->getChild(1)->addChild(modifies2);

	//// store procedure name in vector
	//vector<int> actualResult2 = qe->solve("p1", &table1, query2); 
	//
	//CPPUNIT_ASSERT(actualResult2.empty());

	 /** 
   Test No: 3
   Test Type: assign | <syn1> == <syn2> |  <syn3> specified
   Query:assign a1; Select a1 such that Modifies(a1, "a")
   Expected Result: <1,10>
   **/
	QTNode* modifies3 = new QTNode("Modifies");
	QTNode* first3 = new QTNode("a1");
	QTNode* second3 = new QTNode("a");
	first3->setParent(modifies3);
	modifies3->addChild(first3);
	second3->setParent(modifies3);
	modifies3->addChild(second3);
	QueryTree* query3 = new QueryTree();
	query3->getRootNode()->getChild(1)->addChild(modifies3);

	vector<int> actualResult3 = qe->solve("a1", &table1, query3); 
	
	CPPUNIT_ASSERT_EQUAL(1, actualResult3[0]);
	CPPUNIT_ASSERT_EQUAL(10, actualResult3[1]);

	/**
	 Test No: 4
   Test Type: while | <syn1> == <syn2> or <syn1> == <syn3>|  <syn3> specified
   Query:while w1; Select w1 such that Modifies(w1, "g")
   Expected Result: <>
   **/
	QTNode* modifies4 = new QTNode("Modifies");
	QTNode* first4 = new QTNode("w1");
	QTNode* second4 = new QTNode("g");
	first4->setParent(modifies4);
	modifies4->addChild(first4);
	second4->setParent(modifies4);
	modifies4->addChild(second4);
	QueryTree* query4 = new QueryTree();
	query4->getRootNode()->getChild(1)->addChild(modifies4);

	vector<int> actualResult4 = qe->solve("w1", &table1, query4); 
	
	CPPUNIT_ASSERT(actualResult4.empty());

	/**
	 Test No: 5
   Test Type: while | <syn1> == <syn3> |  <syn2> specified
   Query:variable v1; Select v1 such that Modifies(6, v1)
   Expected Result: <0,11>
   **/
	QTNode* modifies5 = new QTNode("Modifies");
	QTNode* first5 = new QTNode(6);
	QTNode* second5 = new QTNode("v1");
	first5->setParent(modifies5);
	modifies5->addChild(first5);
	second5->setParent(modifies5);
	modifies5->addChild(second5);
	QueryTree* query5 = new QueryTree();
	query5->getRootNode()->getChild(1)->addChild(modifies5);

	vector<int> actualResult5 = qe->solve("v1", &table1, query5); 

	CPPUNIT_ASSERT(actualResult5[0] == 0);
	CPPUNIT_ASSERT(actualResult5[1] == 11);

	/**
	 Test No: 6
   Test Type: assign | <syn1> == <syn3> |  <syn2> specified
   Query:assign a1; Select a1 such that Modifies(7, a1)
   Expected Result: < > // error -1
   **/
	QTNode* modifies6 = new QTNode("Modifies");
	QTNode* first6 = new QTNode("7");
	QTNode* second6 = new QTNode("a1");
	first6->setParent(modifies6);
	modifies6->addChild(first6);
	second6->setParent(modifies6);
	modifies6->addChild(second6);
	QueryTree* query6 = new QueryTree();
	query6->getRootNode()->getChild(1)->addChild(modifies6);

	vector<int> actualResult6 = qe->solve("a1", &table1, query6); 
	
	CPPUNIT_ASSERT(actualResult6.empty());
	
	///**
	// Test No: 7
 //  Test Type: procedure | <syn1> == <syn2> or <syn1> == <syn3> |  none specified
 //  Query:procedure p1, variable v1; Select p1 such that Modifies(p1, v1)
 //  Expected Result: <0> --- 
 //  **/
	//QTNode* modifies7 = new QTNode("Modifies");
	//QTNode* first7 = new QTNode("p1");
	//QTNode* second7 = new QTNode("v1");
	//first7->setParent(modifies7);
	//modifies7->addChild(first7);
	//second7->setParent(modifies7);
	//modifies7->addChild(second7);
	//QueryTree* query7 = new QueryTree();
	//query7->getRootNode()->getChild(1)->addChild(modifies7);

	//vector<int> actualResult7 = qe->solve("p1", &table1, query7); 

	//CPPUNIT_ASSERT(actualResult7[0] == 0 );

    /**
   Test No: 8
   Test Type: stmt | <syn1> == <syn2> or <syn1> == <syn3> |  none specified
   Query:statement s1, variable v1; Select s1 such that Modifies(s1, v1)
   Expected Result: <1,2,3,4,5,6,7,8,9,10> // 
   **/
	QTNode* modifies8 = new QTNode("Modifies");
	QTNode* first8 = new QTNode("s1");
	QTNode* second8 = new QTNode("v1");
	first8->setParent(modifies8);
	modifies8->addChild(first8);
	second8->setParent(modifies8);
	modifies8->addChild(second8);
	QueryTree* query8 = new QueryTree();
	query8->getRootNode()->getChild(1)->addChild(modifies8);

	vector<int> actualResult8_1 = qe->solve("s1", &table1, query8); 
	set<int> temp(actualResult8_1.begin(), actualResult8_1.end());
	vector<int> actualResult8(temp.begin(), temp.end());
	CPPUNIT_ASSERT_EQUAL(1,actualResult8[0]);
	CPPUNIT_ASSERT_EQUAL(2,actualResult8[1]);
	CPPUNIT_ASSERT_EQUAL(3,actualResult8[2]);
	CPPUNIT_ASSERT_EQUAL(4,actualResult8[3]);
	CPPUNIT_ASSERT_EQUAL(5,actualResult8[4]);
	CPPUNIT_ASSERT_EQUAL(6,actualResult8[5]);
	CPPUNIT_ASSERT_EQUAL(7,actualResult8[6]);
	CPPUNIT_ASSERT_EQUAL(8,actualResult8[7]);
	CPPUNIT_ASSERT_EQUAL(9,actualResult8[8]);
	CPPUNIT_ASSERT_EQUAL(10,actualResult8[9]);

	/**
   Test No: 9
   Test Type: while |<syn1> == <syn2> or <syn1> == <syn3> |  none specified
   Query:while w1, variable v1; Select w1 such that Modifies(w1,v1)
   Expected Result: < > 
   **/
	QTNode* modifies9 = new QTNode("Modifies");
	QTNode* first9 = new QTNode("w1");
	QTNode* second9 = new QTNode("v1");
	first9->setParent(modifies9);
	modifies9->addChild(first9);
	second9->setParent(modifies9);
	modifies9->addChild(second9);
	QueryTree* query9 = new QueryTree();
	query9->getRootNode()->getChild(1)->addChild(modifies9);

	vector<int> actualResult9 = qe->solve("w1", &table1, query9); 
	
	CPPUNIT_ASSERT_EQUAL(3,actualResult9[0]);
	CPPUNIT_ASSERT_EQUAL(6,actualResult9[1]);
	CPPUNIT_ASSERT_EQUAL(7,actualResult9[2]);
	CPPUNIT_ASSERT_EQUAL(9,actualResult9[3]);

   /**
   Test No: 10
   Test Type: while |<syn1> == <syn2> or <syn1> == <syn3> |  none specified
   Query:statement s1, variable v1, assignment a1; Select s1 such that Modifies(s1,a1)
   Expected Result: < > // error -1
   **/
	QTNode* modifies10 = new QTNode("Modifies");
	QTNode* first10 = new QTNode("s1");
	QTNode* second10 = new QTNode("a1");
	first10->setParent(modifies10);
	modifies10->addChild(first10);
	second10->setParent(modifies10);
	modifies10->addChild(second10);
	QueryTree* query10 = new QueryTree();
	query10->getRootNode()->getChild(1)->addChild(modifies10);

	vector<int> actualResult10 = qe->solve("s1", &table1, query10); 

	CPPUNIT_ASSERT(actualResult10.empty());

	 /**
   Test No: 11
   Test Type: statement |<syn1> != <syn2> and <syn1> != <syn3>| <syn2> specified && <syn3> specified
   Query:statement s1; Select s1 such that Modifies(3, "c")
   Expected Result: < >
   **/
	QTNode* modifies11 = new QTNode("Modifies");
	QTNode* first11 = new QTNode("3");
	QTNode* second11 = new QTNode("c");
	first11->setParent(modifies11);
	modifies11->addChild(first11);
	second11->setParent(modifies11);
	modifies11->addChild(second11);
	QueryTree* query11 = new QueryTree();
	query11->getRootNode()->getChild(1)->addChild(modifies11);

	vector<int> actualResult11 = qe->solve("s1", &table1, query11); 
	
	CPPUNIT_ASSERT(actualResult11.empty());

	/**
   Test No: 12
   Test Type: assign |<syn1> != <syn2> and <syn1> != <syn3>| <syn2> specified && <syn3> specified
   Query:assign a1; Select a1 such that Modifies(5,"e")
   Expected Result: <1,2,4,5,8,10> // all assignment statements
   **/
	QTNode* modifies12 = new QTNode("Modifies");
	QTNode* first12 = new QTNode(5);
	QTNode* second12 = new QTNode("e");
	first12->setParent(modifies12);
	modifies12->addChild(first12);
	second12->setParent(modifies12);
	modifies12->addChild(second12);
	QueryTree* query12 = new QueryTree();
	query12->getRootNode()->getChild(1)->addChild(modifies12);

	vector<int> actualResult12 = qe->solve("a1", &table1, query12); 

	CPPUNIT_ASSERT_EQUAL(1, actualResult12[0]);
	CPPUNIT_ASSERT_EQUAL(2, actualResult12[1]);
	CPPUNIT_ASSERT_EQUAL(4, actualResult12[2]);
	CPPUNIT_ASSERT_EQUAL(5, actualResult12[3]);
	CPPUNIT_ASSERT_EQUAL(8, actualResult12[4]);
	CPPUNIT_ASSERT_EQUAL(10, actualResult12[5]);

	/**
   Test No: 13
   Test Type: while |<syn1> != <syn2> and <syn1> != <syn3>| <syn2> specified && <syn3> specified
   Query: while w1; Select w1 such that Modifies(8,h)
   Expected Result: <3,6,7,9> // all while stmts
   **/
	QTNode* modifies13 = new QTNode("Modifies");
	QTNode* first13 = new QTNode(8);
	QTNode* second13 = new QTNode("h");
	first13->setParent(modifies13);
	modifies13->addChild(first13);
	second13->setParent(modifies13);
	modifies13->addChild(second13);
	QueryTree* query13 = new QueryTree();
	query13->getRootNode()->getChild(1)->addChild(modifies13);

	vector<int> actualResult13 = qe->solve("w1", &table1, query13); 
	
	CPPUNIT_ASSERT_EQUAL(3, actualResult13[0]);
	CPPUNIT_ASSERT_EQUAL(6, actualResult13[1]);
	CPPUNIT_ASSERT_EQUAL(7, actualResult13[2]);
	CPPUNIT_ASSERT_EQUAL(9, actualResult13[3]);

	/**
   Test No: 14
   Test Type: variable |<syn1> != <syn2> and <syn1> != <syn3>| <syn2> specified && <syn3> specified
   Query: variable v1; Select v1 such that Modifies(2,b)
   Expected Result: <0-14>
   **/
	QTNode* modifies14 = new QTNode("Modifies");
	QTNode* first14 = new QTNode(2);
	QTNode* second14 = new QTNode("b");
	first14->setParent(modifies14);
	modifies14->addChild(first14);
	second14->setParent(modifies14);
	modifies14->addChild(second14);
	QueryTree* query14 = new QueryTree();
	query14->getRootNode()->getChild(1)->addChild(modifies14);

	vector<int> actualResult14 = qe->solve("v1", &table1, query14); 

	CPPUNIT_ASSERT(actualResult14[0]== 0);
	CPPUNIT_ASSERT(actualResult14[1]== 1);
	CPPUNIT_ASSERT(actualResult14[2]== 2);
	CPPUNIT_ASSERT(actualResult14[3]== 3);
	CPPUNIT_ASSERT(actualResult14[7]== 7);
	CPPUNIT_ASSERT(actualResult14[10]== 10);
	CPPUNIT_ASSERT(actualResult14[12]== 12);
	CPPUNIT_ASSERT(actualResult14[13]== 13);
	
	///**
 //  Test No: 15
 //  Test Type: procedure |<syn1> != <syn2> and <syn1> != <syn3>| <syn2> specified && <syn3> specified
 //  Query: procedure p1; Select p1 such that Modifies(1, "a")
 //  Expected Result: <0>
 //  **/
	//QTNode* modifies15 = new QTNode("Modifies");
	//QTNode* first15 = new QTNode("1");
	//QTNode* second15 = new QTNode("a");
	//first15->setParent(modifies15);
	//modifies15->addChild(first15);
	//second15->setParent(modifies15);
	//modifies15->addChild(second15);
	//QueryTree* query15 = new QueryTree();
	//query15->getRootNode()->getChild(1)->addChild(modifies15);

	//vector<int> actualResult15 = qe->solve("p1", &table1, query15); 
	//
	//CPPUNIT_ASSERT(actualResult14[0]== 0);
	//
	///**
 //  Test No: 16
 //  Test Type: procedure |<syn1> != <syn2> and <syn1> != <syn3>| <syn2> specified && <syn3> specified
 //  Query: procedure p1; Select p1 such that Modifies("p1", "h")
 //  Expected Result: <0>
 //  **/
	//QTNode* modifies16 = new QTNode("Modifies");
	//QTNode* first16 = new QTNode("p1");
	//QTNode* second16 = new QTNode("h");
	//first16->setParent(modifies16);
	//modifies16->addChild(first16);
	//second16->setParent(modifies16);
	//modifies16->addChild(second16);
	//QueryTree* query16 = new QueryTree();
	//query16->getRootNode()->getChild(1)->addChild(modifies16);

	//vector<int> actualResult16 = qe->solve("p1", &table1, query16); 
	//
	//CPPUNIT_ASSERT(actualResult16[0] == 0);

	///**
 //  Test No: 17
 //  Test Type: stmt |<syn1> != <syn2> and <syn1> != <syn3>| <syn2> specified && <syn3> specified
 //  Query: statement s1; Select s1 such that Modifies("p1", "h")
 //  Expected Result: <1,2,3,4,5,6,7,8,9,10>
 //  **/
	//QTNode* modifies17 = new QTNode("Modifies");
	//QTNode* first17 = new QTNode("p1");
	//QTNode* second17 = new QTNode("h");
	//first17->setParent(modifies17);
	//modifies17->addChild(first17);
	//second17->setParent(modifies17);
	//modifies17->addChild(second17);
	//QueryTree* query17 = new QueryTree();
	//query17->getRootNode()->getChild(1)->addChild(modifies17);

	//vector<int> actualResult17 = qe->solve("s1", &table1, query17); 
	//
	//CPPUNIT_ASSERT_EQUAL(1,actualResult17[0]);
	//CPPUNIT_ASSERT_EQUAL(5,actualResult17[4]);
	//CPPUNIT_ASSERT_EQUAL(8,actualResult17[7]);
	//CPPUNIT_ASSERT_EQUAL(9,actualResult17[8]);
	//CPPUNIT_ASSERT_EQUAL(10,actualResult17[9]);

   /**
   Test No: 18
   Test Type: stmt |<syn1> != <syn2> and <syn1> != <syn3>| <syn3> specified
   Query: stmt s1,stmt s2; Select s1 such that Modifies(s2, "e")
   Expected Result: <1,2,3,4,5,6,7,8,9,10>
   **/
	QTNode* modifies18 = new QTNode("Modifies");
	QTNode* first18 = new QTNode("s2");
	QTNode* second18 = new QTNode("e");
	first18->setParent(modifies18);
	modifies18->addChild(first18);
	second18->setParent(modifies18);
	modifies18->addChild(second18);
	QueryTree* query18 = new QueryTree();
	query18->getRootNode()->getChild(1)->addChild(modifies18);

	vector<int> actualResult18 = qe->solve("s1", &table1, query18); 
	
	CPPUNIT_ASSERT_EQUAL(1,actualResult18[0]);
	CPPUNIT_ASSERT_EQUAL(5,actualResult18[4]);
	CPPUNIT_ASSERT_EQUAL(8,actualResult18[7]);
	CPPUNIT_ASSERT_EQUAL(9,actualResult18[8]);
	CPPUNIT_ASSERT_EQUAL(10,actualResult18[9]);

	///**
 //  Test No: 19
 //  Test Type: procedure |<syn1> != <syn2> and <syn1> != <syn3>| <syn3> specified
 //  Query: stmt s1,procedure p1; Select p1 such that Modifies(s1, "h")
 //  Expected Result: <0> // p1
 //  **/
	//QTNode* modifies19 = new QTNode("Modifies");
	//QTNode* first19 = new QTNode("s1");
	//QTNode* second19 = new QTNode("h");
	//first19->setParent(modifies19);
	//modifies19->addChild(first19);
	//second19->setParent(modifies19);
	//modifies19->addChild(second19);
	//QueryTree* query19 = new QueryTree();
	//query19->getRootNode()->getChild(1)->addChild(modifies19);

	//vector<int> actualResult19 = qe->solve("p1", &table1, query19); 
	//
	//CPPUNIT_ASSERT(actualResult19[0] == 0);


   /**
   Test No: 20
   Test Type: assignment |<syn1> != <syn2> and <syn1> != <syn3>| <syn3> specified
   Query: assignment a1,stmt s1; Select a1 such that Modifies(s1, "a")
   Expected Result: <1,2,4,5,8,10>
   **/
	QTNode* modifies20 = new QTNode("Modifies");
	QTNode* first20 = new QTNode("s1");
	QTNode* second20 = new QTNode("a");
	first20->setParent(modifies20);
	modifies20->addChild(first20);
	second20->setParent(modifies20);
	modifies20->addChild(second20);
	QueryTree* query20 = new QueryTree();
	query20->getRootNode()->getChild(1)->addChild(modifies20);

	vector<int> actualResult20 = qe->solve("a1", &table1, query20); 
	
	CPPUNIT_ASSERT_EQUAL(1,actualResult20[0]);
	CPPUNIT_ASSERT_EQUAL(2,actualResult20[1]);
	CPPUNIT_ASSERT_EQUAL(4,actualResult20[2]);
	CPPUNIT_ASSERT_EQUAL(5,actualResult20[3]);
	CPPUNIT_ASSERT_EQUAL(10,actualResult20[5]);

	/**
   Test No: 21
   Test Type: stmt |<syn1> != <syn2> and <syn1> != <syn3>| <syn3> specified
   Query: stmt s1,assign a1; Select s1 such that Modifies(a1, "b")
   Expected Result: <1,2,3,4,5,6,7,8,9,10>
   **/
	QTNode* modifies21 = new QTNode("Modifies");
	QTNode* first21 = new QTNode("a1");
	QTNode* second21 = new QTNode("b");
	first21->setParent(modifies21);
	modifies21->addChild(first21);
	second21->setParent(modifies21);
	modifies21->addChild(second21);
	QueryTree* query21 = new QueryTree();
	query21->getRootNode()->getChild(1)->addChild(modifies21);

	vector<int> actualResult21 = qe->solve("s1", &table1, query21); 
	
	CPPUNIT_ASSERT_EQUAL(1,actualResult21[0]);
	CPPUNIT_ASSERT_EQUAL(5,actualResult21[4]);
	CPPUNIT_ASSERT_EQUAL(8,actualResult21[7]);
	CPPUNIT_ASSERT_EQUAL(9,actualResult21[8]);
	CPPUNIT_ASSERT_EQUAL(10,actualResult21[9]);

   /**
   Test No: 22
   Test Type: assign |<syn1> != <syn2> and <syn1> != <syn3>|<syn3> specified
   Query: assign a1, while w1; Select a1 such that Modifies(w1, "f")
   Expected Result: <>
   **/
	QTNode* modifies22 = new QTNode("Modifies");
	QTNode* first22 = new QTNode("w1");
	QTNode* second22 = new QTNode("f");
	first22->setParent(modifies22);
	modifies22->addChild(first22);
	second22->setParent(modifies22);
	modifies22->addChild(second22);
	QueryTree* query22 = new QueryTree();
	query22->getRootNode()->getChild(1)->addChild(modifies22);

	vector<int> actualResult22 = qe->solve("a1", &table1, query22); 

	CPPUNIT_ASSERT(actualResult22.empty());

	/**
   Test No: 23
   Test Type: variable |<syn1> != <syn2> and <syn1> != <syn3>| <syn3> specified
   Query: variable v1, while w1; Select v1 such that Modifies(w1, "c")
   Expected Result: <>
   **/
	QTNode* modifies23 = new QTNode("Modifies");
	QTNode* first23 = new QTNode("w1");
	QTNode* second23 = new QTNode("c");
	first23->setParent(modifies23);
	modifies23->addChild(first23);
	second23->setParent(modifies23);
	modifies23->addChild(second23);
	QueryTree* query23 = new QueryTree();
	query23->getRootNode()->getChild(1)->addChild(modifies23);

	vector<int> actualResult23 = qe->solve("v1", &table1, query23); 
		
	CPPUNIT_ASSERT(actualResult23.empty());

	///**
 //  Test No: 24
 //  Test Type: while |<syn1> != <syn2> and <syn1> != <syn3>| <syn3> specified
 //  Query: while w1, procedure p1; Select w1 such that Modifies(p1, "d")
 //  Expected Result: <3,6,7,9>
 //  **/
	//QTNode* modifies24 = new QTNode("Modifies");
	//QTNode* first24 = new QTNode("p1");
	//QTNode* second24 = new QTNode("d");
	//first24->setParent(modifies24);
	//modifies24->addChild(first24);
	//second24->setParent(modifies24);
	//modifies24->addChild(second24);
	//QueryTree* query24 = new QueryTree();
	//query24->getRootNode()->getChild(1)->addChild(modifies24);

	//vector<int> actualResult24 = qe->solve("w1", &table1, query24); 
	//
	//CPPUNIT_ASSERT_EQUAL(3,actualResult24[0]);
	//CPPUNIT_ASSERT_EQUAL(6,actualResult24[1]);
	//CPPUNIT_ASSERT_EQUAL(7,actualResult24[2]);
	//CPPUNIT_ASSERT_EQUAL(9,actualResult24[3]);

   /**
   Test No: 25
   Test Type: stmt |<syn1> != <syn2> and <syn1> != <syn3>| <syn2> specified
   Query: stmt s1, variable v1; Select s1 such that Modifies(3, v1)
   Expected Result: <1,2,3,4,5,6,7,8,9,10>
   **/
	QTNode* modifies25 = new QTNode("Modifies");
	QTNode* first25 = new QTNode(3);
	QTNode* second25 = new QTNode("v1");
	first25->setParent(modifies25);
	modifies25->addChild(first25);
	second25->setParent(modifies25);
	modifies25->addChild(second25);
	QueryTree* query25 = new QueryTree();
	query25->getRootNode()->getChild(1)->addChild(modifies25);

	vector<int> actualResult25 = qe->solve("s1", &table1, query25); 
	
	CPPUNIT_ASSERT_EQUAL(1,actualResult25[0]);
	CPPUNIT_ASSERT_EQUAL(5,actualResult25[4]);
	CPPUNIT_ASSERT_EQUAL(8,actualResult25[7]);
	CPPUNIT_ASSERT_EQUAL(9,actualResult25[8]);
	CPPUNIT_ASSERT_EQUAL(10,actualResult25[9]);

	/**
   Test No: 26
   Test Type: assign |<syn1> != <syn2> and <syn1> != <syn3>| <syn2> specified
   Query: assign a1, variable v1; Select a1 such that Modifies(3, v1)
   Expected Result: <1,2,4,5,8,10>
   **/
	QTNode* modifies26 = new QTNode("Modifies");
	QTNode* first26 = new QTNode(3);
	QTNode* second26 = new QTNode("v1");
	first26->setParent(modifies26);
	modifies26->addChild(first26);
	second26->setParent(modifies26);
	modifies26->addChild(second26);
	QueryTree* query26 = new QueryTree();
	query26->getRootNode()->getChild(1)->addChild(modifies26);

	vector<int> actualResult26 = qe->solve("a1", &table1, query26); 
	
    CPPUNIT_ASSERT_EQUAL(1,actualResult26[0]);
	CPPUNIT_ASSERT_EQUAL(2,actualResult26[1]);
	CPPUNIT_ASSERT_EQUAL(4,actualResult26[2]);
	CPPUNIT_ASSERT_EQUAL(5,actualResult26[3]);
	CPPUNIT_ASSERT_EQUAL(10,actualResult26[5]);

	/**
   Test No: 27
   Test Type: while |<syn1> != <syn2> and <syn1> != <syn3>| <syn2> specified
   Query: while w1, variable v1; Select w1 such that Modifies(4,v1)
   Expected Result: <3,6,7,9>
   **/
	QTNode* modifies27 = new QTNode("Modifies");
	QTNode* first27 = new QTNode(4);
	QTNode* second27 = new QTNode("v1");
	first27->setParent(modifies27);
	modifies27->addChild(first27);
	second27->setParent(modifies27);
	modifies27->addChild(second27);
	QueryTree* query27 = new QueryTree();
	query27->getRootNode()->getChild(1)->addChild(modifies27);

	vector<int> actualResult27 = qe->solve("w1", &table1, query27); 
	
    CPPUNIT_ASSERT_EQUAL(3,actualResult27[0]);
	CPPUNIT_ASSERT_EQUAL(6,actualResult27[1]);
	CPPUNIT_ASSERT_EQUAL(7,actualResult27[2]);
	CPPUNIT_ASSERT_EQUAL(9,actualResult27[3]);

	///**
 //  Test No: 28
 //  Test Type: while |<syn1> != <syn2> and <syn1> != <syn3>| <syn2> specified
 //  Query: while w1, variable v1; Select w1 such that Modifies("p1",v1)
 //  Expected Result: <3,6,7,9>
 //  **/
	//QTNode* modifies28 = new QTNode("Modifies");
	//QTNode* first28 = new QTNode("p1");
	//QTNode* second28 = new QTNode("v1");
	//first28->setParent(modifies28);
	//modifies28->addChild(first28);
	//second28->setParent(modifies28);
	//modifies28->addChild(second28);
	//QueryTree* query28 = new QueryTree();
	//query28->getRootNode()->getChild(1)->addChild(modifies28);

	//vector<int> actualResult28 = qe->solve("w1", &table1, query28); 
	//
 //   CPPUNIT_ASSERT_EQUAL(3,actualResult28[0]);
	//CPPUNIT_ASSERT_EQUAL(6,actualResult28[1]);
	//CPPUNIT_ASSERT_EQUAL(7,actualResult28[2]);
	//CPPUNIT_ASSERT_EQUAL(9,actualResult28[3]);

	/**
   Test No: 29
   Test Type: variable |<syn1> != <syn2> and <syn1> != <syn3>| <syn2> specified
   Query: variable v1,variable v2; Select v1 such that Modifies(4,v2)
   Expected Result: <0-14>
   **/
	QTNode* modifies29 = new QTNode("Modifies");
	QTNode* first29 = new QTNode(4);
	QTNode* second29 = new QTNode("v2");
	first29->setParent(modifies29);
	modifies29->addChild(first29);
	second29->setParent(modifies29);
	modifies29->addChild(second29);
	QueryTree* query29 = new QueryTree();
	query29->getRootNode()->getChild(1)->addChild(modifies29);

	vector<int> actualResult29 = qe->solve("v1", &table1, query29); 
	
	CPPUNIT_ASSERT(actualResult29[0]== 0);
	CPPUNIT_ASSERT(actualResult29[1]== 1);
	CPPUNIT_ASSERT(actualResult29[2]== 2);
	CPPUNIT_ASSERT(actualResult29[3]== 3);
	CPPUNIT_ASSERT(actualResult29[7]== 7);
	CPPUNIT_ASSERT(actualResult29[10]== 10);
	CPPUNIT_ASSERT(actualResult29[12]== 12);
	CPPUNIT_ASSERT(actualResult29[13]== 13);

	///**
 //  Test No: 30
 //  Test Type: procedure |<syn1> != <syn2> and <syn1> != <syn3>| <syn2> specified
 //  Query: variable v1,procedure p1; Select p1 such that Modifies(2,v1)
 //  Expected Result: <0>
 //  **/
	//QTNode* modifies30 = new QTNode("Modifies");
	//QTNode* first30 = new QTNode(4);
	//QTNode* second30 = new QTNode("v2");
	//first30->setParent(modifies30);
	//modifies30->addChild(first30);
	//second30->setParent(modifies30);
	//modifies30->addChild(second30);
	//QueryTree* query30 = new QueryTree();
	//query30->getRootNode()->getChild(1)->addChild(modifies30);

	//vector<int> actualResult30 = qe->solve("p1", &table1, query30); 
	//
 //   CPPUNIT_ASSERT(actualResult30[0]== 0);
	//
	///**
 //  Test No: 31
 //  Test Type: procedure |<syn1> != <syn2> and <syn1> != <syn3>| none specified
 //  Query: variable v1,procedure p1, assign a1; Select p1 such that Modifies(a1,v1)
 //  Expected Result: <0>
 //  **/
	//QTNode* modifies31 = new QTNode("Modifies");
	//QTNode* first31 = new QTNode("a1");
	//QTNode* second31 = new QTNode("v1");
	//first31->setParent(modifies31);
	//modifies31->addChild(first31);
	//second31->setParent(modifies31);
	//modifies31->addChild(second31);
	//QueryTree* query31 = new QueryTree();
	//query31->getRootNode()->getChild(1)->addChild(modifies31);

	//vector<int> actualResult31 = qe->solve("p1", &table1, query31); 
	//
 //   CPPUNIT_ASSERT(actualResult31[0]== 0);

	///**
 //  Test No: 32
 //  Test Type: procedure |<syn1> != <syn2> and <syn1> != <syn3>| none specified
 //  Query: variable v1,procedure p1, while w1; Select p1 such that Modifies(w1,v1)
 //  Expected Result: <p1>
 //  **/
	//QTNode* modifies32 = new QTNode("Modifies");
	//QTNode* first32 = new QTNode("w1");
	//QTNode* second32 = new QTNode("v1");
	//first32->setParent(modifies32);
	//modifies32->addChild(first32);
	//second32->setParent(modifies32);
	//modifies32->addChild(second32);
	//QueryTree* query32 = new QueryTree();
	//query32->getRootNode()->getChild(1)->addChild(modifies32);

	//vector<int> actualResult32 = qe->solve("p1", &table1, query32); 
	//
 //   CPPUNIT_ASSERT(actualResult32[0]== 0);
	//
	/**
   Test No: 33
   Test Type: stmt |<syn1> != <syn2> and <syn1> != <syn3>|  none specified
   Query: stmt s1,stmt s2,variable v1; Select s1 such that Modifies(s2, v1)
   Expected Result: <1,2,3,4,5,6,7,8,9,10>
   **/
	QTNode* modifies33 = new QTNode("Modifies");
	QTNode* first33 = new QTNode("s2");
	QTNode* second33 = new QTNode("v1");
	first33->setParent(modifies33);
	modifies33->addChild(first33);
	second33->setParent(modifies33);
	modifies33->addChild(second33);
	QueryTree* query33 = new QueryTree();
	query33->getRootNode()->getChild(1)->addChild(modifies33);

	vector<int> actualResult33 = qe->solve("s1", &table1, query33); 
	
	CPPUNIT_ASSERT_EQUAL(1,actualResult33[0]);
	CPPUNIT_ASSERT_EQUAL(5,actualResult33[4]);
	CPPUNIT_ASSERT_EQUAL(8,actualResult33[7]);
	CPPUNIT_ASSERT_EQUAL(9,actualResult33[8]);
	CPPUNIT_ASSERT_EQUAL(10,actualResult33[9]);

	/**
   Test No: 34
   Test Type: assign |<syn1> != <syn2> and <syn1> != <syn3>|  none specified
   Query: stmt s1,assign a1,variable v1; Select a1 such that Modifies(s1, v1)
   Expected Result: <1,2,4,5,8,10>
   **/
	QTNode* modifies34 = new QTNode("Modifies");
	QTNode* first34 = new QTNode("s1");
	QTNode* second34 = new QTNode("v1");
	first34->setParent(modifies34);
	modifies34->addChild(first34);
	second34->setParent(modifies34);
	modifies34->addChild(second34);
	QueryTree* query34 = new QueryTree();
	query34->getRootNode()->getChild(1)->addChild(modifies34);

	vector<int> actualResult34 = qe->solve("a1", &table1, query34); 
	
	CPPUNIT_ASSERT_EQUAL(1,actualResult34[0]);
	CPPUNIT_ASSERT_EQUAL(2,actualResult34[1]);
	CPPUNIT_ASSERT_EQUAL(4,actualResult34[2]);
	CPPUNIT_ASSERT_EQUAL(5,actualResult34[3]);
	CPPUNIT_ASSERT_EQUAL(10,actualResult34[5]);

	/**
   Test No: 35
   Test Type: assign |<syn1> != <syn2> and <syn1> != <syn3>|  none specified
   Query: while w1 ,assign a1,variable v1; Select a1 such that Modifies(w1, v1)
   Expected Result: <1,2,4,5,8,10>
   **/
	QTNode* modifies35 = new QTNode("Modifies");
	QTNode* first35 = new QTNode("w1");
	QTNode* second35 = new QTNode("v1");
	first35->setParent(modifies35);
	modifies35->addChild(first35);
	second35->setParent(modifies35);
	modifies35->addChild(second35);
	QueryTree* query35 = new QueryTree();
	query35->getRootNode()->getChild(1)->addChild(modifies35);

	vector<int> actualResult35 = qe->solve("a1", &table1, query35); 
	
	CPPUNIT_ASSERT_EQUAL(1,actualResult35[0]);
	CPPUNIT_ASSERT_EQUAL(2,actualResult35[1]);
	CPPUNIT_ASSERT_EQUAL(4,actualResult35[2]);
	CPPUNIT_ASSERT_EQUAL(5,actualResult35[3]);
	CPPUNIT_ASSERT_EQUAL(10,actualResult35[5]);

	/**
   Test No: 36
   Test Type: stmt |<syn1> != <syn2> and <syn1> != <syn3>|  none specified
   Query: stmt s1 ,assign a1,variable v1; Select s1 such that Modifies(a1, v1)
   Expected Result: <1,2,3,4,5,6,7,8,9,10>
   **/
	QTNode* modifies36 = new QTNode("Modifies");
	QTNode* first36 = new QTNode("a1");
	QTNode* second36 = new QTNode("v1");
	first36->setParent(modifies36);
	modifies36->addChild(first36);
	second36->setParent(modifies36);
	modifies36->addChild(second36);
	QueryTree* query36 = new QueryTree();
	query36->getRootNode()->getChild(1)->addChild(modifies36);

	vector<int> actualResult36 = qe->solve("s1", &table1, query36); 
	CPPUNIT_ASSERT_EQUAL(1,actualResult36[0]);
	CPPUNIT_ASSERT_EQUAL(5,actualResult36[4]);
	CPPUNIT_ASSERT_EQUAL(8,actualResult36[7]);
	CPPUNIT_ASSERT_EQUAL(9,actualResult36[8]);
	CPPUNIT_ASSERT_EQUAL(10,actualResult36[9]);

	/**
   Test No: 37
   Test Type: variable|<syn1> != <syn2> and <syn1> != <syn3>|  none specified
   Query: variable v1 ,assign a1,variable v2; Select v1 such that Modifies(a1, v2)
   Expected Result: <0-14>
   **/
	QTNode* modifies37 = new QTNode("Modifies");
	QTNode* first37 = new QTNode("a1");
	QTNode* second37 = new QTNode("v2");
	first37->setParent(modifies37);
	modifies37->addChild(first37);
	second37->setParent(modifies37);
	modifies37->addChild(second37);
	QueryTree* query37 = new QueryTree();
	query37->getRootNode()->getChild(1)->addChild(modifies37);

	vector<int> actualResult37 = qe->solve("v1", &table1, query37); 
	CPPUNIT_ASSERT(actualResult37[0]== 0);
	CPPUNIT_ASSERT(actualResult37[1]== 1);
	CPPUNIT_ASSERT(actualResult37[2]== 2);
	CPPUNIT_ASSERT(actualResult37[3]== 3);
	CPPUNIT_ASSERT(actualResult37[7]== 7);
	CPPUNIT_ASSERT(actualResult37[10]== 10);
	CPPUNIT_ASSERT(actualResult37[12]== 12);
	CPPUNIT_ASSERT(actualResult29[13]== 13);

	///**
 //  Test No: 38
 //  Test Type: while |<syn1> != <syn2> and <syn1> != <syn3>|  none specified
 //  Query: procedure p1, variable v1, while w1; Select w1 such that Modifies(p1, v1)
 //  Expected Result: <3,6,7,9>
 //  **/
	//QTNode* modifies38 = new QTNode("Modifies");
	//QTNode* first38 = new QTNode("p1");
	//QTNode* second38 = new QTNode("v1");
	//first38->setParent(modifies38);
	//modifies38->addChild(first38);
	//second38->setParent(modifies38);
	//modifies38->addChild(second38);
	//QueryTree* query38 = new QueryTree();
	//query38->getRootNode()->getChild(1)->addChild(modifies38);

	//vector<int> actualResult38 = qe->solve("w1", &table1, query38); 
	//
	//CPPUNIT_ASSERT_EQUAL(3,actualResult38[0]);
	//CPPUNIT_ASSERT_EQUAL(6,actualResult38[1]);
	//CPPUNIT_ASSERT_EQUAL(7,actualResult38[2]);
	//CPPUNIT_ASSERT_EQUAL(9,actualResult38[3]);
}

void QueryEvaluatorTest::testSolveForSuchThatUses(){
	/** SIMPLE source code
	procedure p1{
	a = x;
	b = y;
	 while c{
	 d = y;
	 e =v;
	 while f{
	  while g{
	   h=u;
		while i{
		 a=b;
		 }}}}
	}
	**/

	PKBController pk;
	TNode stmt1("ASSIGN_NODE","a = x", 1,0);
	TNode stmt2("ASSIGN_NODE","b = y", 2,0);
	TNode stmt3("WHILE_NODE","c", 3,0);
	TNode stmt4("ASSIGN_NODE","d = t", 4,0);
	TNode stmt5("ASSIGN_NODE","e = v", 5,0);
	TNode stmt6("WHILE_NODE","f", 6,0);
	TNode stmt7("WHILE_NODE","g", 7,0);
	TNode stmt8("ASSIGN_NODE","h = u", 8,0);
	TNode stmt9("WHILE_NODE","i", 9,0);
	TNode stmt10("ASSIGN_NODE","a = b", 10,0);

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

	pk.usesTable.insertUsesProc(0,2); //var: x
	pk.usesTable.insertUsesProc(0,3); //var: y
	pk.usesTable.insertUsesProc(0,4); //var: c
	pk.usesTable.insertUsesProc(0,6); //var: t
	pk.usesTable.insertUsesProc(0,8); //var: v 
	pk.usesTable.insertUsesProc(0,9); //var: f
	pk.usesTable.insertUsesProc(0,10); //var:g 
	pk.usesTable.insertUsesProc(0,12); //var: u
    pk.usesTable.insertUsesProc(0,13); //var: i

	//uses for while statements
	pk.usesTable.insertUsesStmt(3,1); //var: a
    pk.usesTable.insertUsesStmt(3,4); //var: d
	pk.usesTable.insertUsesStmt(3,9); //var: e
	pk.usesTable.insertUsesStmt(3,6); //var: h
	pk.usesTable.insertUsesStmt(3,8); //var: a
	pk.usesTable.insertUsesStmt(3,12); //var: h
	pk.usesTable.insertUsesStmt(3,10); //var: a
	pk.usesTable.insertUsesStmt(3,13); //var: h
    pk.usesTable.insertUsesStmt(6,9); //var: h
	pk.usesTable.insertUsesStmt(6,12); //var: h
	pk.usesTable.insertUsesStmt(6,1); //var: h
	pk.usesTable.insertUsesStmt(6,10); //var: h
	pk.usesTable.insertUsesStmt(6,13); //var: h
	pk.usesTable.insertUsesStmt(7,12); //var: h
	pk.usesTable.insertUsesStmt(7,1); //var: h
	pk.usesTable.insertUsesStmt(7,10); //var: h
	pk.usesTable.insertUsesStmt(7,13); //var: h
	pk.usesTable.insertUsesStmt(9,1); //var: h
	pk.usesTable.insertUsesStmt(9,13); //var: h
	
	//uses for assign statements
    pk.usesTable.insertUsesStmt(1,2); // var:a
    pk.usesTable.insertUsesStmt(2,3);  // var:b
    pk.usesTable.insertUsesStmt(4,6); // var:d
    pk.usesTable.insertUsesStmt(5,8); // var:e
    pk.usesTable.insertUsesStmt(8,12); // var:h
	pk.usesTable.insertUsesStmt(10,1);

	pk.procTable.insertProc("p1");

	pk.varTable.insertVar("a"); // index 0
	pk.varTable.insertVar("b"); // index 1
	pk.varTable.insertVar("x"); // index 2
	pk.varTable.insertVar("y"); // index 3
	pk.varTable.insertVar("c"); // index 4
	pk.varTable.insertVar("d"); // index 5
	pk.varTable.insertVar("t"); // index 6
	pk.varTable.insertVar("e"); // index 7
	pk.varTable.insertVar("v"); // index 8
	pk.varTable.insertVar("f"); // index 9
	pk.varTable.insertVar("g"); // index 10
	pk.varTable.insertVar("h"); // index 11
	pk.varTable.insertVar("u"); // index 12
	pk.varTable.insertVar("i"); // index 13
	pk.varTable.insertVar("j"); // index 14

	QueryEvaluator* qe = new QueryEvaluator(&pk);

	// synonym table, add more if needed
	map<string, string> table1;
	table1["s1"]="stmt";
	table1["s2"]="stmt";
	table1["a1"]="assign";
	table1["a2"]="assign";
	table1["w1"]="while";
	table1["w2"]="while";
	table1["v1"]="variable";
	table1["v2"]="variable";
	table1["p1"]="procedure";

	/** 
   Test No: 1
   Test Type: stmt | <syn1> == <syn2> |  <syn3> specified
   Query:stmt s1; Select s1 such that Uses(s1, "x")
   Expected Result: <1>
   **/

	QTNode* uses1 = new QTNode("Uses");
	QTNode* first1 = new QTNode("s1");
	QTNode* second1 = new QTNode("x");
	first1->setParent(uses1);
	uses1->addChild(first1);
	second1->setParent(uses1);
	uses1->addChild(second1);
	QueryTree* query1 = new QueryTree();
	query1->getRootNode()->getChild(1)->addChild(uses1);

	vector<int> actualResult1 = qe->solve("s1", &table1, query1); 
	
	CPPUNIT_ASSERT(actualResult1[0]==1);

	/** 
   Test No: 2
   Test Type: proc | <syn1> == <syn2> |  <syn3> specified
   Query:procedure p1; Select p1 such that Uses(p1, "x")
   Expected Result: <p1>
   **/
   /*
	QTNode* uses2 = new QTNode("Uses");
	QTNode* first2 = new QTNode("p1");
	QTNode* second2 = new QTNode("x");
	first2->setParent(uses2);
	uses2->addChild(first2);
	second2->setParent(uses2);
	uses2->addChild(second2);
	QueryTree* query2 = new QueryTree();
	query2->getRootNode()->getChild(1)->addChild(uses2);

	// store procedure name in vector
	vector<int> actualResult2 = qe->solve("p1", &table1, query2); 

	CPPUNIT_ASSERT(actualResult2[0] == 0 );
	*/

	/** 
   Test No: 3
   Test Type: assign | <syn1> == <syn2> |  <syn3> specified
   Query:assign a1; Select a1 such that Uses(a1, "b")
   Expected Result: <10>
   **/
	QTNode* uses3 = new QTNode("Uses");
	QTNode* first3 = new QTNode("a1");
	QTNode* second3 = new QTNode("b");
	first3->setParent(uses3);
	uses3->addChild(first3);
	second3->setParent(uses3);
	uses3->addChild(second3);
	QueryTree* query3 = new QueryTree();
	query3->getRootNode()->getChild(1)->addChild(uses3);

	vector<int> actualResult3 = qe->solve("a1", &table1, query3); 
	
	CPPUNIT_ASSERT_EQUAL(10, actualResult3[0]);

	/**
	 Test No: 4
   Test Type: while | <syn1> == <syn2> or <syn1> == <syn3>|  <syn3> specified
   Query:while w1; Select w1 such that Uses(w1, "g")
   Expected Result: <3,6,7>
   **/
	QTNode* uses4 = new QTNode("Uses");
	QTNode* first4 = new QTNode("w1");
	QTNode* second4 = new QTNode("g");
	first4->setParent(uses4);
	uses4->addChild(first4);
	second4->setParent(uses4);
	uses4->addChild(second4);
	QueryTree* query4 = new QueryTree();
	query4->getRootNode()->getChild(1)->addChild(uses4);

	vector<int> actualResult4 = qe->solve("w1", &table1, query4); 
	
	CPPUNIT_ASSERT_EQUAL(3,actualResult4[0]);
	CPPUNIT_ASSERT_EQUAL(6,actualResult4[1]);
	CPPUNIT_ASSERT_EQUAL(7,actualResult4[2]);

	/**
	 Test No: 5
   Test Type: while | <syn1> == <syn3> |  <syn2> specified
   Query:variable v1; Select v1 such that Uses(6, v1)
   Expected Result: <b,f,g,u,i>
   **/
	QTNode* uses5 = new QTNode("Uses");
	QTNode* first5 = new QTNode(6);
	QTNode* second5 = new QTNode("v1");
	first5->setParent(uses5);
	uses5->addChild(first5);
	second5->setParent(uses5);
	uses5->addChild(second5);
	QueryTree* query5 = new QueryTree();
	query5->getRootNode()->getChild(1)->addChild(uses5);

	vector<int> actualResult5ns = qe->solve("v1", &table1, query5); 

	set<int> temp;
	temp.insert(actualResult5ns.begin(), actualResult5ns.end());
	
	vector<int> actualResult5(temp.begin(), temp.end());

	CPPUNIT_ASSERT(actualResult5[0] == 1);
	CPPUNIT_ASSERT(actualResult5[1] == 9);
	CPPUNIT_ASSERT(actualResult5[2] == 10);
	CPPUNIT_ASSERT(actualResult5[3] == 12);
	CPPUNIT_ASSERT(actualResult5[4] == 13);

	
	/**
	 Test No: 6
   Test Type: assign | <syn1> == <syn3> |  <syn2> specified
   Query:assign a1; Select a1 such that Uses(7, a1)
   Expected Result: < > // error -1
   **/
	QTNode* uses6 = new QTNode("Uses");
	QTNode* first6 = new QTNode("7");
	QTNode* second6 = new QTNode("a1");
	first6->setParent(uses6);
	uses6->addChild(first6);
	second6->setParent(uses6);
	uses6->addChild(second6);
	QueryTree* query6 = new QueryTree();
	query6->getRootNode()->getChild(1)->addChild(uses6);

	vector<int> actualResult6 = qe->solve("a1", &table1, query6); 
	
	CPPUNIT_ASSERT(actualResult6.empty());
	
	/**
	 Test No: 7
   Test Type: procedure | <syn1> == <syn2> or <syn1> == <syn3> |  none specified
   Query:procedure p1, variable v1; Select p1 such that Uses(p1, v1)
   Expected Result: <p1> --- 
   **/
   /*
	QTNode* uses7 = new QTNode("Uses");
	QTNode* first7 = new QTNode("p1");
	QTNode* second7 = new QTNode("v1");
	first7->setParent(uses7);
	uses7->addChild(first7);
	second7->setParent(uses7);
	uses7->addChild(second7);
	QueryTree* query7 = new QueryTree();
	query7->getRootNode()->getChild(1)->addChild(uses7);

	vector<int> actualResult7 = qe->solve("p1", &table1, query7); 
	
	CPPUNIT_ASSERT(actualResult7[0] == 0 );
	*/
	/**
   Test No: 8
   Test Type: stmt | <syn1> == <syn2> or <syn1> == <syn3> |  none specified
   Query:statement s1, variable v1; Select s1 such that Uses(s1, v1)
   Expected Result: <1,2,3,4,5,6,7,8,9,10> // 
   **/
	QTNode* uses8 = new QTNode("Uses");
	QTNode* first8 = new QTNode("s1");
	QTNode* second8 = new QTNode("v1");
	first8->setParent(uses8);
	uses8->addChild(first8);
	second8->setParent(uses8);
	uses8->addChild(second8);
	QueryTree* query8 = new QueryTree();
	query8->getRootNode()->getChild(1)->addChild(uses8);

	vector<int> actualResult8_1 = qe->solve("s1", &table1, query8); 
	set<int> temp8_1(actualResult8_1.begin(), actualResult8_1.end());
	vector<int> actualResult8(temp8_1.begin(), temp8_1.end());

	CPPUNIT_ASSERT_EQUAL(1,actualResult8[0]);
	CPPUNIT_ASSERT_EQUAL(2,actualResult8[1]);
	CPPUNIT_ASSERT_EQUAL(3,actualResult8[2]);
	CPPUNIT_ASSERT_EQUAL(4,actualResult8[3]);
	CPPUNIT_ASSERT_EQUAL(5,actualResult8[4]);
	CPPUNIT_ASSERT_EQUAL(6,actualResult8[5]);
	CPPUNIT_ASSERT_EQUAL(7,actualResult8[6]);
	CPPUNIT_ASSERT_EQUAL(8,actualResult8[7]);
	CPPUNIT_ASSERT_EQUAL(9,actualResult8[8]);
	CPPUNIT_ASSERT_EQUAL(10,actualResult8[9]);
	
	/**
   Test No: 9
   Test Type: while |<syn1> == <syn2> or <syn1> == <syn3> |  none specified
   Query:while w1, variable v1; Select w1 such that Uses(w1,v1)
   Expected Result: <3,6,7,9> 
   **/
	QTNode* uses9 = new QTNode("Uses");
	QTNode* first9 = new QTNode("w1");
	QTNode* second9 = new QTNode("v1");
	first9->setParent(uses9);
	uses9->addChild(first9);
	second9->setParent(uses9);
	uses9->addChild(second9);
	QueryTree* query9 = new QueryTree();
	query9->getRootNode()->getChild(1)->addChild(uses9);

	vector<int> actualResult9 = qe->solve("w1", &table1, query9); 
	
	CPPUNIT_ASSERT_EQUAL(3,actualResult9[0]);
	CPPUNIT_ASSERT_EQUAL(6,actualResult9[1]);
	CPPUNIT_ASSERT_EQUAL(7,actualResult9[2]);
	CPPUNIT_ASSERT_EQUAL(9,actualResult9[3]);

	
   /**
   Test No: 10
   Test Type: while |<syn1> == <syn2> or <syn1> == <syn3> |  none specified
   Query:statement s1, variable v1, assignment a1; Select s1 such that Uses(s1,a1)
   Expected Result: < > // error -1
   **/
	QTNode* uses10 = new QTNode("Uses");
	QTNode* first10 = new QTNode("s1");
	QTNode* second10 = new QTNode("a1");
	first10->setParent(uses10);
	uses10->addChild(first10);
	second10->setParent(uses10);
	uses10->addChild(second10);
	QueryTree* query10 = new QueryTree();
	query10->getRootNode()->getChild(1)->addChild(uses10);

	vector<int> actualResult10 = qe->solve("s1", &table1, query10); 
	
	CPPUNIT_ASSERT(actualResult10.empty());

	
	 /**
   Test No: 11
   Test Type: statement |<syn1> != <syn2> and <syn1> != <syn3>| <syn2> specified && <syn3> specified
   Query:statement s1; Select s1 such that Uses(3, "c")
   Expected Result: <1,2,3,4,5,6,7,8,9,10>
   **/
	QTNode* uses11 = new QTNode("Uses");
	QTNode* first11 = new QTNode(3);
	QTNode* second11 = new QTNode("c");
	first11->setParent(uses11);
	uses11->addChild(first11);
	second11->setParent(uses11);
	uses11->addChild(second11);
	QueryTree* query11 = new QueryTree();
	query11->getRootNode()->getChild(1)->addChild(uses11);

	vector<int> actualResult11_1 = qe->solve("s1", &table1, query11); 
	set<int> temp11_1(actualResult11_1.begin(), actualResult11_1.end());
	vector<int> actualResult11(temp11_1.begin(), temp11_1.end());
	
	CPPUNIT_ASSERT_EQUAL(1,actualResult11[0]);
	CPPUNIT_ASSERT_EQUAL(2,actualResult11[1]);
	CPPUNIT_ASSERT_EQUAL(3,actualResult11[2]);
	CPPUNIT_ASSERT_EQUAL(4,actualResult11[3]);
	CPPUNIT_ASSERT_EQUAL(5,actualResult11[4]);
	CPPUNIT_ASSERT_EQUAL(6,actualResult11[5]);
	CPPUNIT_ASSERT_EQUAL(7,actualResult11[6]);
	CPPUNIT_ASSERT_EQUAL(8,actualResult11[7]);
	CPPUNIT_ASSERT_EQUAL(9,actualResult11[8]);
	CPPUNIT_ASSERT_EQUAL(10,actualResult11[9]);

	
	/**
   Test No: 12
   Test Type: assign |<syn1> != <syn2> and <syn1> != <syn3>| <syn2> specified && <syn3> specified
   Query:assign a1; Select a1 such that Uses(5,"v")
   Expected Result: <1,2,4,5,8,10> // all assignment statements
   **/
	QTNode* uses12 = new QTNode("Uses");
	QTNode* first12 = new QTNode(5);
	QTNode* second12 = new QTNode("v");
	first12->setParent(uses12);
	uses12->addChild(first12);
	second12->setParent(uses12);
	uses12->addChild(second12);
	QueryTree* query12 = new QueryTree();
	query12->getRootNode()->getChild(1)->addChild(uses12);

	vector<int> actualResult12 = qe->solve("a1", &table1, query12); 
	
	CPPUNIT_ASSERT_EQUAL(1, actualResult12[0]);
	CPPUNIT_ASSERT_EQUAL(2, actualResult12[1]);
	CPPUNIT_ASSERT_EQUAL(4, actualResult12[2]);
	CPPUNIT_ASSERT_EQUAL(5, actualResult12[3]);
	CPPUNIT_ASSERT_EQUAL(8, actualResult12[4]);
	CPPUNIT_ASSERT_EQUAL(10, actualResult12[5]);

	/**
   Test No: 13
   Test Type: while |<syn1> != <syn2> and <syn1> != <syn3>| <syn2> specified && <syn3> specified
   Query: while w1; Select w1 such that Uses(8,u)
   Expected Result: <3,6,7,9> // all while stmts
   **/
	QTNode* uses13 = new QTNode("Uses");
	QTNode* first13 = new QTNode(8);
	QTNode* second13 = new QTNode("u");
	first13->setParent(uses13);
	uses13->addChild(first13);
	second13->setParent(uses13);
	uses13->addChild(second13);
	QueryTree* query13 = new QueryTree();
	query13->getRootNode()->getChild(1)->addChild(uses13);

	vector<int> actualResult13 = qe->solve("w1", &table1, query13); 
	
	CPPUNIT_ASSERT_EQUAL(3, actualResult13[0]);
	CPPUNIT_ASSERT_EQUAL(6, actualResult13[1]);
	CPPUNIT_ASSERT_EQUAL(7, actualResult13[2]);
	CPPUNIT_ASSERT_EQUAL(9, actualResult13[3]);

		/**
   Test No: 14
   Test Type: variable |<syn1> != <syn2> and <syn1> != <syn3>| <syn2> specified && <syn3> specified
   Query: variable v1; Select v1 such that Uses(2,y)
   Expected Result: <a,b,x,y,c,d,t,e,v,f,g,h,u,i>
   **/
	QTNode* uses14 = new QTNode("Uses");
	QTNode* first14 = new QTNode("s1");
	QTNode* second14 = new QTNode("\"y\"");
	first14->setParent(uses14);
	uses14->addChild(first14);
	second14->setParent(uses14);
	uses14->addChild(second14);
	QueryTree* query14 = new QueryTree();
	query14->getRootNode()->getChild(1)->addChild(uses14);

	vector<int> actualResult14 = qe->solve("v1", &table1, query14); 

	CPPUNIT_ASSERT(actualResult14[0]== 0);
	CPPUNIT_ASSERT(actualResult14[1]== 1);
	CPPUNIT_ASSERT(actualResult14[2]== 2);
	CPPUNIT_ASSERT(actualResult14[3]== 3);
	CPPUNIT_ASSERT(actualResult14[7]== 7);
	CPPUNIT_ASSERT(actualResult14[10]== 10);
	CPPUNIT_ASSERT(actualResult14[12]== 12);
	CPPUNIT_ASSERT(actualResult14[13]== 13);

		/**
   Test No: 14
   Test Type: variable |<syn1> != <syn2> and <syn1> != <syn3>| <syn2> specified && <syn3> specified
   Query: variable v1; Select v1 such that Uses(2,y)
   Expected Result: <a,b,x,y,c,d,t,e,v,f,g,h,u,i>
   **/
	QTNode* uses14_5 = new QTNode("Uses");
	QTNode* first14_5 = new QTNode(2);
	QTNode* second14_5 = new QTNode("y");
	first14_5->setParent(uses14_5);
	uses14_5->addChild(first14_5);
	second14_5->setParent(uses14_5);
	uses14_5->addChild(second14_5);
	QueryTree* query14_5 = new QueryTree();
	query14_5->getRootNode()->getChild(1)->addChild(uses14_5);

	vector<int> actualResult14_5 = qe->solve("v1", &table1, query14_5); 
	
	CPPUNIT_ASSERT(actualResult14_5[0]== 0);
	CPPUNIT_ASSERT(actualResult14_5[1]== 1);
	CPPUNIT_ASSERT(actualResult14_5[2]== 2);
	CPPUNIT_ASSERT(actualResult14_5[3]== 3);
	CPPUNIT_ASSERT(actualResult14_5[7]== 7);
	CPPUNIT_ASSERT(actualResult14_5[10]== 10);
	CPPUNIT_ASSERT(actualResult14_5[12]== 12);
	CPPUNIT_ASSERT(actualResult14_5[13]== 13);

	/**
   Test No: 15
   Test Type: procedure |<syn1> != <syn2> and <syn1> != <syn3>| <syn2> specified && <syn3> specified
   Query: procedure p1; Select p1 such that Uses(1, "x")
   Expected Result: <p1>
   **/
   /*
	QTNode* uses15 = new QTNode("Uses");
	QTNode* first15 = new QTNode("1");
	QTNode* second15 = new QTNode("a");
	first15->setParent(uses15);
	uses15->addChild(first15);
	second15->setParent(uses15);
	uses15->addChild(second15);
	QueryTree* query15 = new QueryTree();
	query15->getRootNode()->getChild(1)->addChild(uses15);

	vector<int> actualResult15 = qe->solve("p1", &table1, query15); 
	
	CPPUNIT_ASSERT(actualResult14[0]== 0);
	*/
	/**
   Test No: 16
   Test Type: procedure |<syn1> != <syn2> and <syn1> != <syn3>| <syn2> specified && <syn3> specified
   Query: procedure p1; Select p1 such that Uses("p1", "h")
   Expected Result: <>
   **/
   /*
	QTNode* uses16 = new QTNode("Uses");
	QTNode* first16 = new QTNode("p1");
	QTNode* second16 = new QTNode("h");
	first16->setParent(uses16);
	uses16->addChild(first16);
	second16->setParent(uses16);
	uses16->addChild(second16);
	QueryTree* query16 = new QueryTree();
	query16->getRootNode()->getChild(1)->addChild(uses16);

	vector<int> actualResult16 = qe->solve("p1", &table1, query16); 
	
	CPPUNIT_ASSERT(actualResult16.empty());
	*/
	/**
   Test No: 17
   Test Type: stmt |<syn1> != <syn2> and <syn1> != <syn3>| <syn2> specified && <syn3> specified
   Query: statement s1; Select s1 such that Uses("p1", "t")
   Expected Result: <1,2,3,4,5,6,7,8,9,10>
   **/
   /*
	QTNode* uses17 = new QTNode("Uses");
	QTNode* first17 = new QTNode("p1");
	QTNode* second17 = new QTNode("t");
	first17->setParent(uses17);
	uses17->addChild(first17);
	second17->setParent(uses17);
	uses17->addChild(second17);
	QueryTree* query17 = new QueryTree();
	query17->getRootNode()->getChild(1)->addChild(uses17);

	vector<int> actualResult17 = qe->solve("s1", &table1, query17); 
	
	CPPUNIT_ASSERT_EQUAL(1,actualResult17[0]);
	CPPUNIT_ASSERT_EQUAL(5,actualResult17[4]);
	CPPUNIT_ASSERT_EQUAL(8,actualResult17[7]);
	CPPUNIT_ASSERT_EQUAL(9,actualResult17[8]);
	CPPUNIT_ASSERT_EQUAL(10,actualResult17[9]);
	*/
	/**
   Test No: 18
   Test Type: stmt |<syn1> != <syn2> and <syn1> != <syn3>| <syn3> specified
   Query: stmt s1,stmt s2; Select s1 such that Uses(s2, "v")
   Expected Result: <1,2,3,4,5,6,7,8,9,10>
   **/
	QTNode* uses18 = new QTNode("Uses");
	QTNode* first18 = new QTNode("s2");
	QTNode* second18 = new QTNode("v");
	first18->setParent(uses18);
	uses18->addChild(first18);
	second18->setParent(uses18);
	uses18->addChild(second18);
	QueryTree* query18 = new QueryTree();
	query18->getRootNode()->getChild(1)->addChild(uses18);

	vector<int> actualResult18 = qe->solve("s1", &table1, query18); 
	
	CPPUNIT_ASSERT_EQUAL(1,actualResult18[0]);
	CPPUNIT_ASSERT_EQUAL(5,actualResult18[4]);
	CPPUNIT_ASSERT_EQUAL(8,actualResult18[7]);
	CPPUNIT_ASSERT_EQUAL(9,actualResult18[8]);
	CPPUNIT_ASSERT_EQUAL(10,actualResult18[9]);

	/**
   Test No: 19
   Test Type: procedure |<syn1> != <syn2> and <syn1> != <syn3>| <syn3> specified
   Query: stmt s1,procedure p1; Select p1 such that Uses(s1, "f")
   Expected Result: <p1>
   **/
   /*
	QTNode* uses19 = new QTNode("Uses");
	QTNode* first19 = new QTNode("s1");
	QTNode* second19 = new QTNode("f");
	first19->setParent(uses19);
	uses19->addChild(first19);
	second19->setParent(uses19);
	uses19->addChild(second19);
	QueryTree* query19 = new QueryTree();
	query19->getRootNode()->getChild(1)->addChild(uses19);

	vector<int> actualResult19 = qe->solve("p1", &table1, query19); 
	
	CPPUNIT_ASSERT(actualResult19[0] == 0);
	*/
   /**
   Test No: 20
   Test Type: assignment |<syn1> != <syn2> and <syn1> != <syn3>| <syn3> specified
   Query: assignment a1,stmt s1; Select a1 such that Uses(s1, "c")
   Expected Result: <1,2,4,5,8,10>
   **/
	QTNode* uses20 = new QTNode("Uses");
	QTNode* first20 = new QTNode("s1");
	QTNode* second20 = new QTNode("c");
	first20->setParent(uses20);
	uses20->addChild(first20);
	second20->setParent(uses20);
	uses20->addChild(second20);
	QueryTree* query20 = new QueryTree();
	query20->getRootNode()->getChild(1)->addChild(uses20);

	vector<int> actualResult20 = qe->solve("a1", &table1, query20); 
	
	CPPUNIT_ASSERT_EQUAL(1,actualResult20[0]);
	CPPUNIT_ASSERT_EQUAL(2,actualResult20[1]);
	CPPUNIT_ASSERT_EQUAL(4,actualResult20[2]);
	CPPUNIT_ASSERT_EQUAL(5,actualResult20[3]);
	CPPUNIT_ASSERT_EQUAL(10,actualResult20[5]);

	/**
   Test No: 21
   Test Type: stmt |<syn1> != <syn2> and <syn1> != <syn3>| <syn3> specified
   Query: stmt s1,assign a1; Select s1 such that Uses(a1, "b")
   Expected Result: <1,2,3,4,5,6,7,8,9,10>
   **/
	QTNode* uses21 = new QTNode("Uses");
	QTNode* first21 = new QTNode("a1");
	QTNode* second21 = new QTNode("b");
	first21->setParent(uses21);
	uses21->addChild(first21);
	second21->setParent(uses21);
	uses21->addChild(second21);
	QueryTree* query21 = new QueryTree();
	query21->getRootNode()->getChild(1)->addChild(uses21);

	vector<int> actualResult21 = qe->solve("s1", &table1, query21); 
	
	CPPUNIT_ASSERT_EQUAL(1,actualResult21[0]);
	CPPUNIT_ASSERT_EQUAL(5,actualResult21[4]);
	CPPUNIT_ASSERT_EQUAL(8,actualResult21[7]);
	CPPUNIT_ASSERT_EQUAL(9,actualResult21[8]);
	CPPUNIT_ASSERT_EQUAL(10,actualResult21[9]);

   /**
   Test No: 22
   Test Type: assign |<syn1> != <syn2> and <syn1> != <syn3>|<syn3> specified
   Query: assign a1, while w1; Select a1 such that Uses(w1, "f")
   Expected Result: <1,2,4,5,8,10>
   **/
	QTNode* uses22 = new QTNode("Uses");
	QTNode* first22 = new QTNode("w1");
	QTNode* second22 = new QTNode("f");
	first22->setParent(uses22);
	uses22->addChild(first22);
	second22->setParent(uses22);
	uses22->addChild(second22);
	QueryTree* query22 = new QueryTree();
	query22->getRootNode()->getChild(1)->addChild(uses22);

	vector<int> actualResult22 = qe->solve("a1", &table1, query22); 
	
	CPPUNIT_ASSERT_EQUAL(1,actualResult22[0]);
	CPPUNIT_ASSERT_EQUAL(2,actualResult22[1]);
	CPPUNIT_ASSERT_EQUAL(4,actualResult22[2]);
	CPPUNIT_ASSERT_EQUAL(5,actualResult22[3]);
	CPPUNIT_ASSERT_EQUAL(10,actualResult22[5]);

	/**
   Test No: 23
   Test Type: variable |<syn1> != <syn2> and <syn1> != <syn3>| <syn3> specified
   Query: variable v1, while w1; Select v1 such that Uses(w1, "c")
   Expected Result: <a,b,x,y,c,d,t,e,v,f,g,h,u,i>
   **/
	QTNode* uses23 = new QTNode("Uses");
	QTNode* first23 = new QTNode("w1");
	QTNode* second23 = new QTNode("c");
	first23->setParent(uses23);
	uses23->addChild(first23);
	second23->setParent(uses23);
	uses23->addChild(second23);
	QueryTree* query23 = new QueryTree();
	query23->getRootNode()->getChild(1)->addChild(uses23);

	vector<int> actualResult23 = qe->solve("v1", &table1, query23); 
		
	CPPUNIT_ASSERT(actualResult23[0]== 0);
	CPPUNIT_ASSERT(actualResult23[1]== 1);
	CPPUNIT_ASSERT(actualResult23[2]== 2);
	CPPUNIT_ASSERT(actualResult23[3]== 3);
	CPPUNIT_ASSERT(actualResult23[7]== 7);
	CPPUNIT_ASSERT(actualResult23[10]== 10);
	CPPUNIT_ASSERT(actualResult23[12]== 12);
	CPPUNIT_ASSERT(actualResult23[13]== 13);

	/**
   Test No: 24
   Test Type: while |<syn1> != <syn2> and <syn1> != <syn3>| <syn3> specified
   Query: while w1, procedure p1; Select w1 such that Uses(p1, "d")
   Expected Result: <>
   **/
   /*
	QTNode* uses24 = new QTNode("Uses");
	QTNode* first24 = new QTNode("p1");
	QTNode* second24 = new QTNode("d");
	first24->setParent(uses24);
	uses24->addChild(first24);
	second24->setParent(uses24);
	uses24->addChild(second24);
	QueryTree* query24 = new QueryTree();
	query24->getRootNode()->getChild(1)->addChild(uses24);

	vector<int> actualResult24 = qe->solve("w1", &table1, query24); 
	
	CPPUNIT_ASSERT(actualResult24.empty());
	*/

   /**
   Test No: 25
   Test Type: stmt |<syn1> != <syn2> and <syn1> != <syn3>| <syn2> specified
   Query: stmt s1, variable v1; Select s1 such that Uses(3, v1)
   Expected Result: <1,2,3,4,5,6,7,8,9,10>
   **/
	QTNode* uses25 = new QTNode("Uses");
	QTNode* first25 = new QTNode(3);
	QTNode* second25 = new QTNode("v1");
	first25->setParent(uses25);
	uses25->addChild(first25);
	second25->setParent(uses25);
	uses25->addChild(second25);
	QueryTree* query25 = new QueryTree();
	query25->getRootNode()->getChild(1)->addChild(uses25);

	vector<int> actualResult25 = qe->solve("s1", &table1, query25); 
	
	CPPUNIT_ASSERT_EQUAL(1,actualResult25[0]);
	CPPUNIT_ASSERT_EQUAL(5,actualResult25[4]);
	CPPUNIT_ASSERT_EQUAL(8,actualResult25[7]);
	CPPUNIT_ASSERT_EQUAL(9,actualResult25[8]);
	CPPUNIT_ASSERT_EQUAL(10,actualResult25[9]);


	/**
   Test No: 26
   Test Type: assign |<syn1> != <syn2> and <syn1> != <syn3>| <syn2> specified
   Query: assign a1, variable v1; Select a1 such that Uses(3, v1)
   Expected Result: <1,2,4,5,8,10>
   **/
	QTNode* uses26 = new QTNode("Uses");
	QTNode* first26 = new QTNode(3);
	QTNode* second26 = new QTNode("v1");
	first26->setParent(uses26);
	uses26->addChild(first26);
	second26->setParent(uses26);
	uses26->addChild(second26);
	QueryTree* query26 = new QueryTree();
	query26->getRootNode()->getChild(1)->addChild(uses26);

	vector<int> actualResult26 = qe->solve("a1", &table1, query26); 
	
    CPPUNIT_ASSERT_EQUAL(1,actualResult26[0]);
	CPPUNIT_ASSERT_EQUAL(2,actualResult26[1]);
	CPPUNIT_ASSERT_EQUAL(4,actualResult26[2]);
	CPPUNIT_ASSERT_EQUAL(5,actualResult26[3]);
	CPPUNIT_ASSERT_EQUAL(10,actualResult26[5]);

	/**
   Test No: 27
   Test Type: while |<syn1> != <syn2> and <syn1> != <syn3>| <syn2> specified
   Query: while w1, variable v1; Select w1 such that Uses(4,v1)
   Expected Result: <3,6,7,9>
   **/
	QTNode* uses27 = new QTNode("Uses");
	QTNode* first27 = new QTNode(4);
	QTNode* second27 = new QTNode("v1");
	first27->setParent(uses27);
	uses27->addChild(first27);
	second27->setParent(uses27);
	uses27->addChild(second27);
	QueryTree* query27 = new QueryTree();
	query27->getRootNode()->getChild(1)->addChild(uses27);

	vector<int> actualResult27 = qe->solve("w1", &table1, query27); 
	
    CPPUNIT_ASSERT_EQUAL(3,actualResult27[0]);
	CPPUNIT_ASSERT_EQUAL(6,actualResult27[1]);
	CPPUNIT_ASSERT_EQUAL(7,actualResult27[2]);
	CPPUNIT_ASSERT_EQUAL(9,actualResult27[3]);


	/**
   Test No: 28
   Test Type: while |<syn1> != <syn2> and <syn1> != <syn3>| <syn2> specified
   Query: while w1, variable v1; Select w1 such that Uses("p1",v1)
   Expected Result: <3,6,7,9>
   **/
   /*
	QTNode* uses28 = new QTNode("Uses");
	QTNode* first28 = new QTNode("p1");
	QTNode* second28 = new QTNode("v1");
	first28->setParent(uses28);
	uses28->addChild(first28);
	second28->setParent(uses28);
	uses28->addChild(second28);
	QueryTree* query28 = new QueryTree();
	query28->getRootNode()->getChild(1)->addChild(uses28);

	vector<int> actualResult28 = qe->solve("w1", &table1, query28); 
	
    CPPUNIT_ASSERT_EQUAL(3,actualResult28[0]);
	CPPUNIT_ASSERT_EQUAL(6,actualResult28[1]);
	CPPUNIT_ASSERT_EQUAL(7,actualResult28[2]);
	CPPUNIT_ASSERT_EQUAL(9,actualResult28[3]);
	*/
	/**
   Test No: 29
   Test Type: variable |<syn1> != <syn2> and <syn1> != <syn3>| <syn2> specified
   Query: variable v1,variable v2; Select v1 such that Uses(4,v2)
   Expected Result: <a,b,x,y,c,d,t,e,v,f,g,h,u,i>
   **/
	QTNode* uses29 = new QTNode("Uses");
	QTNode* first29 = new QTNode(4);
	QTNode* second29 = new QTNode("v2");
	first29->setParent(uses29);
	uses29->addChild(first29);
	second29->setParent(uses29);
	uses29->addChild(second29);
	QueryTree* query29 = new QueryTree();
	query29->getRootNode()->getChild(1)->addChild(uses29);

	vector<int> actualResult29 = qe->solve("v1", &table1, query29); 
	
	CPPUNIT_ASSERT(actualResult29[0]== 0);
	CPPUNIT_ASSERT(actualResult29[1]== 1);
	CPPUNIT_ASSERT(actualResult29[2]== 2);
	CPPUNIT_ASSERT(actualResult29[3]== 3);
	CPPUNIT_ASSERT(actualResult29[7]== 7);
	CPPUNIT_ASSERT(actualResult29[10]== 10);
	CPPUNIT_ASSERT(actualResult29[12]== 12);
	CPPUNIT_ASSERT(actualResult29[13]== 13);

	/**
   Test No: 30
   Test Type: procedure |<syn1> != <syn2> and <syn1> != <syn3>| <syn2> specified
   Query: variable v1,procedure p1; Select p1 such that Uses(2,v1)
   Expected Result: <p1>
   **/
   /*
	QTNode* uses30 = new QTNode("Uses");
	QTNode* first30 = new QTNode(4);
	QTNode* second30 = new QTNode("v1");
	first30->setParent(uses30);
	uses30->addChild(first30);
	second30->setParent(uses30);
	uses30->addChild(second30);
	QueryTree* query30 = new QueryTree();
	query30->getRootNode()->getChild(1)->addChild(uses30);

	vector<int> actualResult30 = qe->solve("p1", &table1, query30); 
	
    CPPUNIT_ASSERT(actualResult30[0]== 0);
	*/
	/**
   Test No: 31
   Test Type: procedure |<syn1> != <syn2> and <syn1> != <syn3>| none specified
   Query: variable v1,procedure p1, assign a1; Select p1 such that Uses(a1,v1)
   Expected Result: <p1>
   **/
   /*
	QTNode* uses31 = new QTNode("Uses");
	QTNode* first31 = new QTNode("a1");
	QTNode* second31 = new QTNode("v1");
	first31->setParent(uses31);
	uses31->addChild(first31);
	second31->setParent(uses31);
	uses31->addChild(second31);
	QueryTree* query31 = new QueryTree();
	query31->getRootNode()->getChild(1)->addChild(uses31);

	vector<int> actualResult31 = qe->solve("p1", &table1, query31); 
	
    CPPUNIT_ASSERT(actualResult31[0]== 0);
    */
	/**
   Test No: 32
   Test Type: procedure |<syn1> != <syn2> and <syn1> != <syn3>| none specified
   Query: variable v1,procedure p1, while w1; Select p1 such that Uses(w1,v1)
   Expected Result: <p1>
   **/
   /*
	QTNode* uses32 = new QTNode("Uses");
	QTNode* first32 = new QTNode("w1");
	QTNode* second32 = new QTNode("v1");
	first32->setParent(uses32);
	uses32->addChild(first32);
	second32->setParent(uses32);
	uses32->addChild(second32);
	QueryTree* query32 = new QueryTree();
	query32->getRootNode()->getChild(1)->addChild(uses32);

	vector<int> actualResult32 = qe->solve("p1", &table1, query32); 
	
    CPPUNIT_ASSERT(actualResult32[0]== 0);
	*/
 	/**
   Test No: 33
   Test Type: stmt |<syn1> != <syn2> and <syn1> != <syn3>|  none specified
   Query: stmt s1,stmt s2,variable v1; Select s1 such that Uses(s2, v1)
   Expected Result: <1,2,3,4,5,6,7,8,9,10>
   **/
	QTNode* uses33 = new QTNode("Uses");
	QTNode* first33 = new QTNode("s2");
	QTNode* second33 = new QTNode("v1");
	first33->setParent(uses33);
	uses33->addChild(first33);
	second33->setParent(uses33);
	uses33->addChild(second33);
	QueryTree* query33 = new QueryTree();
	query33->getRootNode()->getChild(1)->addChild(uses33);

	vector<int> actualResult33 = qe->solve("s1", &table1, query33); 
	
	CPPUNIT_ASSERT_EQUAL(1,actualResult33[0]);
	CPPUNIT_ASSERT_EQUAL(5,actualResult33[4]);
	CPPUNIT_ASSERT_EQUAL(8,actualResult33[7]);
	CPPUNIT_ASSERT_EQUAL(9,actualResult33[8]);
	CPPUNIT_ASSERT_EQUAL(10,actualResult33[9]);

	/**
   Test No: 34
   Test Type: assign |<syn1> != <syn2> and <syn1> != <syn3>|  none specified
   Query: stmt s1,assign a1,variable v1; Select a1 such that Uses(s1, v1)
   Expected Result: <1,2,4,5,8,10>
   **/
	QTNode* uses34 = new QTNode("Uses");
	QTNode* first34 = new QTNode("s1");
	QTNode* second34 = new QTNode("v1");
	first34->setParent(uses34);
	uses34->addChild(first34);
	second34->setParent(uses34);
	uses34->addChild(second34);
	QueryTree* query34 = new QueryTree();
	query34->getRootNode()->getChild(1)->addChild(uses34);

	vector<int> actualResult34 = qe->solve("a1", &table1, query34); 
	
	CPPUNIT_ASSERT_EQUAL(1,actualResult34[0]);
	CPPUNIT_ASSERT_EQUAL(2,actualResult34[1]);
	CPPUNIT_ASSERT_EQUAL(4,actualResult34[2]);
	CPPUNIT_ASSERT_EQUAL(5,actualResult34[3]);
	CPPUNIT_ASSERT_EQUAL(10,actualResult34[5]);

	/**
   Test No: 35
   Test Type: assign |<syn1> != <syn2> and <syn1> != <syn3>|  none specified
   Query: while w1 ,assign a1,variable v1; Select a1 such that Uses(w1, v1)
   Expected Result: <1,2,4,5,8,10>
   **/
	QTNode* uses35 = new QTNode("Uses");
	QTNode* first35 = new QTNode("w1");
	QTNode* second35 = new QTNode("v1");
	first35->setParent(uses35);
	uses35->addChild(first35);
	second35->setParent(uses35);
	uses35->addChild(second35);
	QueryTree* query35 = new QueryTree();
	query35->getRootNode()->getChild(1)->addChild(uses35);

	vector<int> actualResult35 = qe->solve("a1", &table1, query35); 
	
	CPPUNIT_ASSERT_EQUAL(1,actualResult35[0]);
	CPPUNIT_ASSERT_EQUAL(2,actualResult35[1]);
	CPPUNIT_ASSERT_EQUAL(4,actualResult35[2]);
	CPPUNIT_ASSERT_EQUAL(5,actualResult35[3]);
	CPPUNIT_ASSERT_EQUAL(10,actualResult35[5]);

	/**
   Test No: 36
   Test Type: stmt |<syn1> != <syn2> and <syn1> != <syn3>|  none specified
   Query: stmt s1 ,assign a1,variable v1; Select s1 such that Uses(a1, v1)
   Expected Result: <1,2,3,4,5,6,7,8,9,10>
   **/
	QTNode* uses36 = new QTNode("Uses");
	QTNode* first36 = new QTNode("a1");
	QTNode* second36 = new QTNode("v1");
	first36->setParent(uses36);
	uses36->addChild(first36);
	second36->setParent(uses36);
	uses36->addChild(second36);
	QueryTree* query36 = new QueryTree();
	query36->getRootNode()->getChild(1)->addChild(uses36);

	vector<int> actualResult36 = qe->solve("s1", &table1, query36); 
	CPPUNIT_ASSERT_EQUAL(1,actualResult36[0]);
	CPPUNIT_ASSERT_EQUAL(5,actualResult36[4]);
	CPPUNIT_ASSERT_EQUAL(8,actualResult36[7]);
	CPPUNIT_ASSERT_EQUAL(9,actualResult36[8]);
	CPPUNIT_ASSERT_EQUAL(10,actualResult36[9]);

	/**
   Test No: 37
   Test Type: variable|<syn1> != <syn2> and <syn1> != <syn3>|  none specified
   Query: variable v1 ,assign a1,variable v2; Select v1 such that Uses(a1, v2)
   Expected Result: <a,b,x,y,c,d,t,e,v,f,g,h,u,i>
   **/
	QTNode* uses37 = new QTNode("Uses");
	QTNode* first37 = new QTNode("a1");
	QTNode* second37 = new QTNode("v2");
	first37->setParent(uses37);
	uses37->addChild(first37);
	second37->setParent(uses37);
	uses37->addChild(second37);
	QueryTree* query37 = new QueryTree();
	query37->getRootNode()->getChild(1)->addChild(uses37);

	vector<int> actualResult37 = qe->solve("v1", &table1, query37); 
	CPPUNIT_ASSERT(actualResult37[0]== 0);
	CPPUNIT_ASSERT(actualResult37[1]== 1);
	CPPUNIT_ASSERT(actualResult37[2]== 2);
	CPPUNIT_ASSERT(actualResult37[3]== 3);
	CPPUNIT_ASSERT(actualResult37[7]== 7);
	CPPUNIT_ASSERT(actualResult37[10]== 10);
	CPPUNIT_ASSERT(actualResult37[12]== 12);
	CPPUNIT_ASSERT(actualResult29[13]== 13);

	/**
   Test No: 38
   Test Type: while |<syn1> != <syn2> and <syn1> != <syn3>|  none specified
   Query: procedure p1, variable v1, while w1; Select w1 such that Uses(p1, v1)
   Expected Result: <3,6,7,9>
   **/
   /*
	QTNode* uses38 = new QTNode("Uses");
	QTNode* first38 = new QTNode("p1");
	QTNode* second38 = new QTNode("v1");
	first38->setParent(uses38);
	uses38->addChild(first38);
	second38->setParent(uses38);
	uses38->addChild(second38);
	QueryTree* query38 = new QueryTree();
	query38>getRootNode()->getChild(1)->addChild(uses38);

	vector<int> actualResult38 = qe->solve("w1", &table1, query38); 
	
	CPPUNIT_ASSERT_EQUAL(3,actualResult38[0]);
	CPPUNIT_ASSERT_EQUAL(6,actualResult38[1]);
	CPPUNIT_ASSERT_EQUAL(7,actualResult38[2]);
	CPPUNIT_ASSERT_EQUAL(9,actualResult38[3]);
	*/
}


void QueryEvaluatorTest::testSolveForSuchThatParent(){
	/** SIMPLE source code
	procedure Proc1{
	a = x;
	b = y;
	 while c{
	 z = a;
	 b =y;
	 while x{
	  while y{
	   z=a;
	   while b{
		while c;
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
	TNode stmt7("WHILE_NODE","y", 7,0);
	TNode stmt8("ASSIGN_NODE","z=a", 8,0);
	TNode stmt9("WHILE_NODE","b", 9,0);
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

	QueryEvaluator* qe = new QueryEvaluator(&pk);

	map<string, string> table1;
	table1["s1"]="stmt";
	table1["s2"]="stmt";
	table1["a2"]="assign";
	table1["a3"]="assign";
	table1["w3"]="while";
	table1["w4"]="while";
	table1["v4"]="variable";
	table1["v5"]="variable";
	table1["proc5"]="procedure";

	CPPUNIT_ASSERT_EQUAL(true, "stmt"==table1.at("s1")); // test 1 for synonym table
	
	QTNode* parent1 = new QTNode("Parent");
	QTNode* first1 = new QTNode("s1");
	QTNode* second1 = new QTNode(2);
	first1->setParent(parent1);
	parent1->addChild(first1);
	second1->setParent(parent1);
	parent1->addChild(second1);
	QueryTree* query1 = new QueryTree();
	query1->getRootNode()->getChild(1)->addChild(parent1);

	vector<int> actualResult1 = qe->solve("s1", &table1, query1); // stmt s1; Select s1 such that Parent(s1, 2) | Expected <1>
	
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResult1.size());

	QTNode* parent2 = new QTNode("Parent");
	QTNode* first2 = new QTNode("w3");
	QTNode* second2 = new QTNode(4);
	first2->setParent(parent2);
	parent2->addChild(first2);
	second2->setParent(parent2);
	parent2->addChild(second2);
	QueryTree* query2 = new QueryTree();
	query2->getRootNode()->getChild(1)->addChild(parent2);

	vector<int> actualResult2 = qe->solve("w3", &table1, query2); // while w3; Select w3 such that Parent(w3, 4) | Expected <3>

	CPPUNIT_ASSERT_EQUAL((size_t)1, actualResult2.size());
	CPPUNIT_ASSERT_EQUAL(3,actualResult2.at(0));

	QTNode* parent3 = new QTNode("Parent");
	QTNode* first3 = new QTNode("a2");
	QTNode* second3 = new QTNode(4);
	first3->setParent(parent3);
	parent3->addChild(first3);
	second3->setParent(parent3);
	parent3->addChild(second3);
	QueryTree* query3 = new QueryTree();
	query3->getRootNode()->getChild(1)->addChild(parent3);

	vector<int> actualResult3 = qe->solve("a2", &table1, query3); // assign a2; Select a2 such that Parent(a2, 4) | Expected <> (none)

	CPPUNIT_ASSERT(actualResult3.empty());

	QTNode* parent4 = new QTNode("Parent");
	QTNode* first4 = new QTNode("w3");
	QTNode* second4 = new QTNode(3);
	first4->setParent(parent4);
	parent4->addChild(first4);
	second4->setParent(parent4);
	parent4->addChild(second4);
	QueryTree* query4 = new QueryTree();
	query4->getRootNode()->getChild(1)->addChild(parent4);

	vector<int> actualResult4 = qe->solve("w3", &table1, query4); // while w3; Select w3 such that Parent(w3, 3) | Expected <> (none)

	CPPUNIT_ASSERT(actualResult4.empty());

	QTNode* parent5 = new QTNode("Parent");
	QTNode* first5 = new QTNode("w3");
	QTNode* second5 = new QTNode(7);
	first5->setParent(parent5);
	parent5->addChild(first5);
	second5->setParent(parent5);
	parent5->addChild(second5);
	QueryTree* query5 = new QueryTree();
	query5->getRootNode()->getChild(1)->addChild(parent5);

	vector<int> actualResult5 = qe->solve("w3", &table1, query5); // while w3; Select w3 such that Parent(w3, 7) | Expected <3>

	CPPUNIT_ASSERT_EQUAL((size_t)1, actualResult5.size());
	CPPUNIT_ASSERT_EQUAL(6, actualResult5.at(0));

	QTNode* parent6 = new QTNode("Parent");
	QTNode* first6 = new QTNode("v4");
	QTNode* second6 = new QTNode(4);
	first6->setParent(parent6);
	parent6->addChild(first6);
	second6->setParent(parent6);
	parent6->addChild(second6);
	QueryTree* query6 = new QueryTree();
	query6->getRootNode()->getChild(1)->addChild(parent6);

	vector<int> actualResult6 = qe->solve("v4", &table1, query6); // variable v4; Select v4 such that Parent(v4, 4) | Expected <> (none)

	CPPUNIT_ASSERT(actualResult6.empty());

	QTNode* parent7 = new QTNode("Parent");
	QTNode* first7 = new QTNode("lol");
	QTNode* second7 = new QTNode(3);
	first7->setParent(parent7);
	parent7->addChild(first7);
	second7->setParent(parent7);
	parent7->addChild(second7);
	QueryTree* query7 = new QueryTree();
	query7->getRootNode()->getChild(1)->addChild(parent7);

	vector<int> actualResult7 = qe->solve("lol", &table1, query7); // undefined lol; Select lol such that Parent(lol, 3) | Expected <> (none)

	CPPUNIT_ASSERT(actualResult7.empty());

	QTNode* parent8 = new QTNode("Parent");
	QTNode* first8 = new QTNode("s1");
	QTNode* second8 = new QTNode("s2");
	first8->setParent(parent8);
	parent8->addChild(first8);
	second8->setParent(parent8);
	parent8->addChild(second8);
	QueryTree* query8 = new QueryTree();
	query8->getRootNode()->getChild(1)->addChild(parent8);

	vector<int> actualResult8_1 = qe->solve("s1", &table1, query8); // stmt s1, s2; Select s1 such that Parent(s1, s2) | Expected <3,6,7,9>
	set<int> temp8(actualResult8_1.begin(), actualResult8_1.end());
	vector<int> actualResult8(temp8.begin(), temp8.end());

	CPPUNIT_ASSERT_EQUAL((size_t)4, actualResult8.size());
	CPPUNIT_ASSERT_EQUAL(3, actualResult8.at(0));
	CPPUNIT_ASSERT_EQUAL(6, actualResult8.at(1));
	CPPUNIT_ASSERT_EQUAL(7, actualResult8.at(2));
	CPPUNIT_ASSERT_EQUAL(9, actualResult8.at(3));
	

	QTNode* parent9 = new QTNode("Parent");
	QTNode* first9 = new QTNode("w3");
	QTNode* second9 = new QTNode("s2");
	first9->setParent(parent9);
	parent9->addChild(first9);
	second9->setParent(parent9);
	parent9->addChild(second9);
	QueryTree* query9 = new QueryTree();
	query9->getRootNode()->getChild(1)->addChild(parent9);

	vector<int> actualResult9_1 = qe->solve("w3", &table1, query9); // while w3; stmt s2; Select w3 such that Parent(w3, s2) | Expected <3,6,7,9>
	set<int> temp9(actualResult9_1.begin(), actualResult9_1.end());
	vector<int> actualResult9(temp9.begin(), temp9.end());

	CPPUNIT_ASSERT_EQUAL((size_t)4, actualResult9.size());
	CPPUNIT_ASSERT_EQUAL(3, actualResult9.at(0));
	CPPUNIT_ASSERT_EQUAL(6, actualResult9.at(1));
	CPPUNIT_ASSERT_EQUAL(7, actualResult9.at(2));
	CPPUNIT_ASSERT_EQUAL(9, actualResult9.at(3));

	QTNode* parent10 = new QTNode("Parent");
	QTNode* first10 = new QTNode("a1");
	QTNode* second10 = new QTNode("s2");
	first10->setParent(parent10);
	parent10->addChild(first10);
	second10->setParent(parent10);
	parent10->addChild(second10);
	QueryTree* query10 = new QueryTree();
	query10->getRootNode()->getChild(1)->addChild(parent10);

	vector<int> actualResult10 = qe->solve("a1", &table1, query10); // stmt s2; Select a1 such that Parent(a1, s2) | Expected <> (none because a1 is not in synonym table)

	CPPUNIT_ASSERT(actualResult10.empty());

	QTNode* parent11 = new QTNode("Parent");
	QTNode* first11 = new QTNode("w3");
	QTNode* second11 = new QTNode("s2");
	first11->setParent(parent11);
	parent11->addChild(first11);
	second11->setParent(parent11);
	parent11->addChild(second11);
	QueryTree* query11 = new QueryTree();
	query11->getRootNode()->getChild(1)->addChild(parent11);

	vector<int> actualResult11_1 = qe->solve("w3", &table1, query11); // while w3; stmt s2; Select w3 such that Parent(w3, s2) | Expected <3, 6, 7, 9>
	set<int> temp11(actualResult11_1.begin(), actualResult11_1.end());
	vector<int> actualResult11(temp11.begin(), temp11.end());

	CPPUNIT_ASSERT_EQUAL((size_t)4, actualResult11.size());
	CPPUNIT_ASSERT_EQUAL(3, actualResult11.at(0));
	CPPUNIT_ASSERT_EQUAL(6, actualResult11.at(1));
	CPPUNIT_ASSERT_EQUAL(7, actualResult11.at(2));
	CPPUNIT_ASSERT_EQUAL(9, actualResult11.at(3));

	QTNode* parent12 = new QTNode("Parent");
	QTNode* first12 = new QTNode("s1");
	QTNode* second12 = new QTNode("a1");
	first12->setParent(parent12);
	parent12->addChild(first12);
	second12->setParent(parent12);
	parent12->addChild(second12);
	QueryTree* query12 = new QueryTree();
	query12->getRootNode()->getChild(1)->addChild(parent12);

	vector<int> actualResult12 = qe->solve("s1", &table1, query12); // stmt s1; Select s1 such that Parent(s1, a1) | Expected <> (none because a1  is not in synonym table)

	CPPUNIT_ASSERT(actualResult12.empty());

	QTNode* parent13 = new QTNode("Parent");
	QTNode* first13 = new QTNode("s1");
	QTNode* second13 = new QTNode("a2");
	first13->setParent(parent13);
	parent13->addChild(first13);
	second13->setParent(parent13);
	parent13->addChild(second13);
	QueryTree* query13 = new QueryTree();
	query13->getRootNode()->getChild(1)->addChild(parent13);

	vector<int> actualResult13 = qe->solve("s1", &table1, query13); // stmt s1; assign a2; Select s1 such that Parent(s1, a2) | Expected <3, 3, 6>

	CPPUNIT_ASSERT_EQUAL((size_t)3, actualResult13.size());
	CPPUNIT_ASSERT_EQUAL(3, actualResult13.at(0));
	CPPUNIT_ASSERT_EQUAL(3, actualResult13.at(1));
	CPPUNIT_ASSERT_EQUAL(7, actualResult13.at(2));

	QTNode* parent14 = new QTNode("Parent");
	QTNode* first14 = new QTNode("s1");
	QTNode* second14 = new QTNode("w3");
	first14->setParent(parent14);
	parent14->addChild(first14);
	second14->setParent(parent14);
	parent14->addChild(second14);
	QueryTree* query14 = new QueryTree();
	query14->getRootNode()->getChild(1)->addChild(parent14);

	vector<int> actualResult14 = qe->solve("s1", &table1, query14); // stmt s1; while w3; Select s1 such that Parent(s1, w3) | Expected <3,6,7,9>

	CPPUNIT_ASSERT_EQUAL((size_t)4, actualResult14.size());
	CPPUNIT_ASSERT_EQUAL(3, actualResult14.at(0));
	CPPUNIT_ASSERT_EQUAL(6, actualResult14.at(1));
	CPPUNIT_ASSERT_EQUAL(7, actualResult14.at(2));
	CPPUNIT_ASSERT_EQUAL(9, actualResult14.at(3));


	QTNode* parent15 = new QTNode("Parent");
	QTNode* first15 = new QTNode("a2");
	QTNode* second15 = new QTNode("a3");
	first15->setParent(parent15);
	parent15->addChild(first15);
	second15->setParent(parent15);
	parent15->addChild(second15);
	QueryTree* query15 = new QueryTree();
	query15->getRootNode()->getChild(1)->addChild(parent15);

	vector<int> actualResult15 = qe->solve("a2", &table1, query15); // assign a2; assign a3; Select a2 such that Parent(a2, a3) | Expected <>

	CPPUNIT_ASSERT(actualResult15.empty());

	QTNode* parent16 = new QTNode("Parent");
	QTNode* first16 = new QTNode("a2");
	QTNode* second16 = new QTNode("w3");
	first16->setParent(parent16);
	parent16->addChild(first16);
	second16->setParent(parent16);
	parent16->addChild(second16);
	QueryTree* query16 = new QueryTree();
	query16->getRootNode()->getChild(1)->addChild(parent16);

	vector<int> actualResult16 = qe->solve("a2", &table1, query16); // assign a2; while w3; Select a2 such that Parent(a2, w3) | Expected <>

	CPPUNIT_ASSERT(actualResult16.empty());

	QTNode* parent17 = new QTNode("Parent");
	QTNode* first17 = new QTNode("w3");
	QTNode* second17 = new QTNode("a2");
	first17->setParent(parent17);
	parent17->addChild(first17);
	second17->setParent(parent17);
	parent17->addChild(second17);
	QueryTree* query17 = new QueryTree();
	query17->getRootNode()->getChild(1)->addChild(parent17);

	vector<int> actualResult17 = qe->solve("w3", &table1, query17); // while w3; assign a2; Select w3 such that Parent(w3, a2) | Expected <3, 3, 7>

	CPPUNIT_ASSERT_EQUAL((size_t)3, actualResult17.size());
	CPPUNIT_ASSERT_EQUAL(3, actualResult17.at(0));
	CPPUNIT_ASSERT_EQUAL(3, actualResult17.at(1));
	CPPUNIT_ASSERT_EQUAL(7, actualResult17.at(2));

	QTNode* parent18 = new QTNode("Parent");
	QTNode* first18 = new QTNode("w3");
	QTNode* second18 = new QTNode("w4");
	first18->setParent(parent18);
	parent18->addChild(first18);
	second18->setParent(parent18);
	parent18->addChild(second18);
	QueryTree* query18 = new QueryTree();
	query18->getRootNode()->getChild(1)->addChild(parent18);

	vector<int> actualResult18 = qe->solve("w3", &table1, query18); // while w3; while w4; Select w3 such that Parent(w3, w4) | Expected <3, 6, 7, 9>

	CPPUNIT_ASSERT_EQUAL((size_t)4, actualResult18.size());
	CPPUNIT_ASSERT_EQUAL(3, actualResult18.at(0));
	CPPUNIT_ASSERT_EQUAL(6, actualResult18.at(1));
	CPPUNIT_ASSERT_EQUAL(7, actualResult18.at(2));
	CPPUNIT_ASSERT_EQUAL(9, actualResult18.at(3));

	QTNode* parent19 = new QTNode("Parent");
	QTNode* first19 = new QTNode(1);
	QTNode* second19 = new QTNode("s1");
	first19->setParent(parent19);
	parent19->addChild(first19);
	second19->setParent(parent19);
	parent19->addChild(second19);
	QueryTree* query19 = new QueryTree();
	query19->getRootNode()->getChild(1)->addChild(parent19);

	vector<int> actualResult19 = qe->solve("s1", &table1, query19); // stmt s1; Select s1 such that Parent(1, s1) | Expected <>
	
	CPPUNIT_ASSERT_EQUAL((size_t)0, actualResult19.size());

	QTNode* parent20 = new QTNode("Parent");
	QTNode* first20 = new QTNode(3);
	QTNode* second20 = new QTNode("a2");
	first20->setParent(parent20);
	parent20->addChild(first20);
	second20->setParent(parent20);
	parent20->addChild(second20);
	QueryTree* query20 = new QueryTree();
	query20->getRootNode()->getChild(1)->addChild(parent20);

	vector<int> actualResult20_1 = qe->solve("a2", &table1, query20); // assign a2; Select a2 such that Parent(3, a2) | Expected <4,5>
	set<int> temp20(actualResult20_1.begin(), actualResult20_1.end());
	vector<int> actualResult20(temp20.begin(), temp20.end());

	CPPUNIT_ASSERT_EQUAL((size_t)2, actualResult20.size());
	CPPUNIT_ASSERT_EQUAL(4, actualResult20.at(0));
	CPPUNIT_ASSERT_EQUAL(5, actualResult20.at(1));

	QTNode* parent21 = new QTNode("Parent");
	QTNode* first21 = new QTNode(2);
	QTNode* second21 = new QTNode("a2");
	first21->setParent(parent21);
	parent21->addChild(first21);
	second21->setParent(parent21);
	parent21->addChild(second21);
	QueryTree* query21 = new QueryTree();
	query21->getRootNode()->getChild(1)->addChild(parent21);

	vector<int> actualResult21 = qe->solve("a2", &table1, query21); // assign a2; Select a2 such that Parent(2, a2) | Expected <> (none)

	CPPUNIT_ASSERT(actualResult21.empty());

	QTNode* parent22 = new QTNode("Parent");
	QTNode* first22 = new QTNode(3);
	QTNode* second22 = new QTNode("w3");
	first22->setParent(parent22);
	parent22->addChild(first22);
	second22->setParent(parent22);
	parent22->addChild(second22);
	QueryTree* query22 = new QueryTree();
	query22->getRootNode()->getChild(1)->addChild(parent22);

	vector<int> actualResult22 = qe->solve("w3", &table1, query22); // while w3; Select w3 such that Parent(3, w3) | Expected <> (none)

	CPPUNIT_ASSERT_EQUAL((size_t)1, actualResult22.size());
	CPPUNIT_ASSERT_EQUAL(6, actualResult22[0]);

	QTNode* parent23 = new QTNode("Parent");
	QTNode* first23 = new QTNode(2);
	QTNode* second23 = new QTNode("w3");
	first23->setParent(parent23);
	parent23->addChild(first23);
	second23->setParent(parent23);
	parent23->addChild(second23);
	QueryTree* query23 = new QueryTree();
	query23->getRootNode()->getChild(1)->addChild(parent23);

	vector<int> actualResult23 = qe->solve("w3", &table1, query23); // while w3; Select w3 such that Parent(2, w3) | Expected <>

	CPPUNIT_ASSERT(actualResult23.empty());

	QTNode* parent24 = new QTNode("Parent");
	QTNode* first24 = new QTNode(4);
	QTNode* second24 = new QTNode("v4");
	first24->setParent(parent24);
	parent24->addChild(first24);
	second24->setParent(parent24);
	parent24->addChild(second24);
	QueryTree* query24 = new QueryTree();
	query24->getRootNode()->getChild(1)->addChild(parent24);

	vector<int> actualResult24 = qe->solve("v4", &table1, query24); // variable v4; Select v4 such that Parent(4, v4) | Expected <> (none)

	CPPUNIT_ASSERT(actualResult24.empty());

	QTNode* parent25 = new QTNode("Parent");
	QTNode* first25 = new QTNode(3);
	QTNode* second25 = new QTNode("lol");
	first25->setParent(parent25);
	parent25->addChild(first25);
	second25->setParent(parent25);
	parent25->addChild(second25);
	QueryTree* query25 = new QueryTree();
	query25->getRootNode()->getChild(1)->addChild(parent25);

	vector<int> actualResult25 = qe->solve("lol", &table1, query25); // undefined lol; Select lol such that Parent(3, lol) | Expected <> (none)

	CPPUNIT_ASSERT(actualResult25.empty());

	QTNode* parent26 = new QTNode("Parent");
	QTNode* first26 = new QTNode("s1");
	QTNode* second26 = new QTNode("s2");
	first26->setParent(parent26);
	parent26->addChild(first26);
	second26->setParent(parent26);
	parent26->addChild(second26);
	QueryTree* query26 = new QueryTree();
	query26->getRootNode()->getChild(1)->addChild(parent26);

	vector<int> actualResult26 = qe->solve("s2", &table1, query26); // stmt s1, s2; Select s2 such that Parent(s1, s2) | Expected <4,5,6,7,8,9,10>

	CPPUNIT_ASSERT_EQUAL((size_t)7, actualResult26.size());
	CPPUNIT_ASSERT_EQUAL(4, actualResult26.at(0));
	CPPUNIT_ASSERT_EQUAL(5, actualResult26.at(1));
	CPPUNIT_ASSERT_EQUAL(6, actualResult26.at(2));
	CPPUNIT_ASSERT_EQUAL(7, actualResult26.at(3));
	CPPUNIT_ASSERT_EQUAL(8, actualResult26.at(4));
	CPPUNIT_ASSERT_EQUAL(9, actualResult26.at(5));
	CPPUNIT_ASSERT_EQUAL(10, actualResult26.at(6));
	

	QTNode* parent27 = new QTNode("Parent");
	QTNode* first27 = new QTNode("s2");
	QTNode* second27 = new QTNode("a2");
	first27->setParent(parent27);
	parent27->addChild(first27);
	second27->setParent(parent27);
	parent27->addChild(second27);
	QueryTree* query27 = new QueryTree();
	query27->getRootNode()->getChild(1)->addChild(parent27);

	vector<int> actualResult27 = qe->solve("a2", &table1, query27); // assign a2; stmt s2; Select a2 such that Parent(s2, a2) | Expected <4, 5, 8>

	CPPUNIT_ASSERT_EQUAL((size_t)3, actualResult27.size());
	CPPUNIT_ASSERT_EQUAL(4, actualResult27.at(0));
	CPPUNIT_ASSERT_EQUAL(5, actualResult27.at(1));
	CPPUNIT_ASSERT_EQUAL(8, actualResult27.at(2));

	QTNode* parent28 = new QTNode("Parent");
	QTNode* first28 = new QTNode("s2");
	QTNode* second28 = new QTNode("a1");
	first28->setParent(parent28);
	parent28->addChild(first28);
	second28->setParent(parent28);
	parent28->addChild(second28);
	QueryTree* query28 = new QueryTree();
	query28->getRootNode()->getChild(1)->addChild(parent28);

	vector<int> actualResult28 = qe->solve("a1", &table1, query28); // stmt s2; Select a1 such that Parent(s2, a1) | Expected <> (none because a1 is not in synonym table)

	CPPUNIT_ASSERT(actualResult28.empty());

	QTNode* parent29 = new QTNode("Parent");
	QTNode* first29 = new QTNode("s2");
	QTNode* second29 = new QTNode("w3");
	first29->setParent(parent29);
	parent29->addChild(first29);
	second29->setParent(parent29);
	parent29->addChild(second29);
	QueryTree* query29 = new QueryTree();
	query29->getRootNode()->getChild(1)->addChild(parent29);

	vector<int> actualResult29 = qe->solve("w3", &table1, query29); // while w3; stmt s2; Select w3 such that Parent(s2, w3) | Expected <6, 7, 9,10>

	CPPUNIT_ASSERT_EQUAL((size_t)4, actualResult29.size());
	CPPUNIT_ASSERT_EQUAL(6, actualResult29.at(0));
	CPPUNIT_ASSERT_EQUAL(7, actualResult29.at(1));
	CPPUNIT_ASSERT_EQUAL(9, actualResult29.at(2));
	CPPUNIT_ASSERT_EQUAL(10, actualResult29.at(3));


	QTNode* parent30 = new QTNode("Parent");
	QTNode* first30 = new QTNode("a1");
	QTNode* second30 = new QTNode("s1");
	first30->setParent(parent30);
	parent30->addChild(first30);
	second30->setParent(parent30);
	parent30->addChild(second30);
	QueryTree* query30 = new QueryTree();
	query30->getRootNode()->getChild(1)->addChild(parent30);

	vector<int> actualResult30 = qe->solve("s1", &table1, query30); // stmt s1; Select s1 such that Parent(a1, s1) | Expected <> (none because a1  is not in synonym table)

	CPPUNIT_ASSERT(actualResult30.empty());

	QTNode* parent31 = new QTNode("Parent");
	QTNode* first31 = new QTNode("a2");
	QTNode* second31 = new QTNode("s1");
	first31->setParent(parent31);
	parent31->addChild(first31);
	second31->setParent(parent31);
	parent31->addChild(second31);
	QueryTree* query31 = new QueryTree();
	query31->getRootNode()->getChild(1)->addChild(parent31);

	vector<int> actualResult31 = qe->solve("s1", &table1, query31); // stmt s1; assign a2; Select s1 such that Parent(a2, s1) | Expected <>

	CPPUNIT_ASSERT(actualResult30.empty());

	QTNode* parent32 = new QTNode("Parent");
	QTNode* first32 = new QTNode("w3");
	QTNode* second32 = new QTNode("s1");
	first32->setParent(parent32);
	parent32->addChild(first32);
	second32->setParent(parent32);
	parent32->addChild(second32);
	QueryTree* query32 = new QueryTree();
	query32->getRootNode()->getChild(1)->addChild(parent32);

	vector<int> expectedResult32;
	expectedResult32.push_back(4);
	expectedResult32.push_back(7);
	expectedResult32.push_back(8);
	expectedResult32.push_back(10);

	vector<int> actualResult32 = qe->solve("s1", &table1, query32); // stmt s1; while w3; Select s1 such that Parent(w3, s1) | Expected <4,5,6,7, 8,9, 10>

	CPPUNIT_ASSERT_EQUAL((size_t)7, actualResult32.size());
	CPPUNIT_ASSERT_EQUAL(4, actualResult32.at(0));
	CPPUNIT_ASSERT_EQUAL(5, actualResult32.at(1));
	CPPUNIT_ASSERT_EQUAL(6, actualResult32.at(2));
	CPPUNIT_ASSERT_EQUAL(7, actualResult32.at(3));
	CPPUNIT_ASSERT_EQUAL(8, actualResult32.at(4));
	CPPUNIT_ASSERT_EQUAL(9, actualResult32.at(5));
	CPPUNIT_ASSERT_EQUAL(10, actualResult32.at(6));

	QTNode* parent33 = new QTNode("Parent");
	QTNode* first33 = new QTNode("a2");
	QTNode* second33 = new QTNode("a3");
	first33->setParent(parent33);
	parent33->addChild(first33);
	second33->setParent(parent33);
	parent33->addChild(second33);
	QueryTree* query33 = new QueryTree();
	query33->getRootNode()->getChild(1)->addChild(parent33);

	vector<int> actualResult33 = qe->solve("a3", &table1, query33); // assign a2; assign a3; Select a3 such that Parent(a2, a3) | Expected <>

	CPPUNIT_ASSERT(actualResult33.empty());

	QTNode* parent34 = new QTNode("Parent");
	QTNode* first34 = new QTNode("w3");
	QTNode* second34 = new QTNode("a2");
	first34->setParent(parent34);
	parent34->addChild(first34);
	second34->setParent(parent34);
	parent34->addChild(second34);
	QueryTree* query34 = new QueryTree();
	query34->getRootNode()->getChild(1)->addChild(parent34);

	vector<int> actualResult34 = qe->solve("a2", &table1, query34); // assign a2; while w3; Select a2 such that Parent(w3, a2) | Expected <4,5,8>

	CPPUNIT_ASSERT_EQUAL((size_t)3, actualResult34.size());
	CPPUNIT_ASSERT_EQUAL(4, actualResult34.at(0));
	CPPUNIT_ASSERT_EQUAL(5, actualResult34.at(1));
	CPPUNIT_ASSERT_EQUAL(8, actualResult34.at(2));

	QTNode* parent35 = new QTNode("Parent");
	QTNode* first35 = new QTNode("a2");
	QTNode* second35 = new QTNode("w3");
	first35->setParent(parent35);
	parent35->addChild(first35);
	second35->setParent(parent35);
	parent35->addChild(second35);
	QueryTree* query35 = new QueryTree();
	query35->getRootNode()->getChild(1)->addChild(parent35);

	vector<int> actualResult35 = qe->solve("w3", &table1, query35); // while w3; assign a2; Select w3 such that Parent(a2, w3) | Expected <>

	CPPUNIT_ASSERT(actualResult35.empty());

	
	QTNode* parent36 = new QTNode("Parent");
	QTNode* first36 = new QTNode(3);
	QTNode* second36 = new QTNode(4);
	first36->setParent(parent36);
	parent36->addChild(first36);
	second36->setParent(parent36);
	parent36->addChild(second36);
	QueryTree* query36 = new QueryTree();
	query36->getRootNode()->getChild(1)->addChild(parent36);

	vector<int> actualResult36 = qe->solve("s1", &table1, query36); // stmt s1; Select s1 such that Parent(3, 4) | Expected <1, 2, 3, 4, 5, 6, 7, 8, 9, 10>
	
	CPPUNIT_ASSERT_EQUAL((size_t)10, actualResult36.size());
	CPPUNIT_ASSERT_EQUAL(1, actualResult36.at(0));
	CPPUNIT_ASSERT_EQUAL(2, actualResult36.at(1));
	CPPUNIT_ASSERT_EQUAL(3, actualResult36.at(2));
	CPPUNIT_ASSERT_EQUAL(4, actualResult36.at(3));
	CPPUNIT_ASSERT_EQUAL(5, actualResult36.at(4));
	CPPUNIT_ASSERT_EQUAL(6, actualResult36.at(5));
	CPPUNIT_ASSERT_EQUAL(7, actualResult36.at(6));
	CPPUNIT_ASSERT_EQUAL(8, actualResult36.at(7));
	CPPUNIT_ASSERT_EQUAL(9, actualResult36.at(8));
	CPPUNIT_ASSERT_EQUAL(10, actualResult36.at(9));

	QTNode* parent37 = new QTNode("Parent");
	QTNode* first37 = new QTNode(1);
	QTNode* second37 = new QTNode(3);
	first37->setParent(parent37);
	parent37->addChild(first37);
	second37->setParent(parent37);
	parent37->addChild(second37);
	QueryTree* query37 = new QueryTree();
	query37->getRootNode()->getChild(1)->addChild(parent37);

	vector<int> actualResult37 = qe->solve("s1", &table1, query37); // stmt s1; Select s1 such that Parent(1, 3) | Expected <> (none)
	
	CPPUNIT_ASSERT(actualResult37.empty());

	QTNode* parent38 = new QTNode("Parent");
	QTNode* first38 = new QTNode(9);
	QTNode* second38 = new QTNode(10);
	first38->setParent(parent38);
	parent38->addChild(first38);
	second38->setParent(parent38);
	parent38->addChild(second38);
	QueryTree* query38 = new QueryTree();
	query38->getRootNode()->getChild(1)->addChild(parent38);

	vector<int> actualResult38 = qe->solve("a2", &table1, query38); // assign a2; Select a2 such that Parent(9, 10) | Expected <1, 2, 4, 5, 8>

	CPPUNIT_ASSERT_EQUAL((size_t)5, actualResult38.size());
	CPPUNIT_ASSERT_EQUAL(1, actualResult38.at(0));
	CPPUNIT_ASSERT_EQUAL(2, actualResult38.at(1));
	CPPUNIT_ASSERT_EQUAL(4, actualResult38.at(2));
	CPPUNIT_ASSERT_EQUAL(5, actualResult38.at(3));
	CPPUNIT_ASSERT_EQUAL(8, actualResult38.at(4));

	QTNode* parent39 = new QTNode("Parent");
	QTNode* first39 = new QTNode(6);
	QTNode* second39 = new QTNode(7);
	first39->setParent(parent39);
	parent39->addChild(first39);
	second39->setParent(parent39);
	parent39->addChild(second39);
	QueryTree* query39 = new QueryTree();
	query39->getRootNode()->getChild(1)->addChild(parent39);

	vector<int> actualResult39 = qe->solve("w3", &table1, query39); // while w3; Select w3 such that Parent(6, 7) | Expected <3, 6, 7, 9, 10>
	
	CPPUNIT_ASSERT_EQUAL((size_t)5, actualResult39.size());
	CPPUNIT_ASSERT_EQUAL(3, actualResult39.at(0));
	CPPUNIT_ASSERT_EQUAL(6, actualResult39.at(1));
	CPPUNIT_ASSERT_EQUAL(7, actualResult39.at(2));
	CPPUNIT_ASSERT_EQUAL(9, actualResult39.at(3));
	CPPUNIT_ASSERT_EQUAL(10, actualResult39.at(4));

	QTNode* parent40 = new QTNode("Parent");
	QTNode* first40 = new QTNode(3);
	QTNode* second40 = new QTNode(6);
	first40->setParent(parent40);
	parent40->addChild(first40);
	second40->setParent(parent40);
	parent40->addChild(second40);
	QueryTree* query40 = new QueryTree();
	query40->getRootNode()->getChild(1)->addChild(parent40);

	vector<int> actualResult40 = qe->solve("v4", &table1, query40); // variable v4; Select v4 such that Parent(3, 6) | Expected <1, 2, 3, 4, 5, 6>
	
	CPPUNIT_ASSERT_EQUAL((size_t)6, actualResult40.size());
	CPPUNIT_ASSERT_EQUAL(0, actualResult40.at(0));
	CPPUNIT_ASSERT_EQUAL(1, actualResult40.at(1));
	CPPUNIT_ASSERT_EQUAL(2, actualResult40.at(2));
	CPPUNIT_ASSERT_EQUAL(3, actualResult40.at(3));
	CPPUNIT_ASSERT_EQUAL(4, actualResult40.at(4));
	CPPUNIT_ASSERT_EQUAL(5, actualResult40.at(5));
	/*
	QTNode* parent41 = new QTNode("Parent");
	QTNode* first41 = new QTNode(7);
	QTNode* second41 = new QTNode(9);
	first41->setParent(parent41);
	parent41->addChild(first41);
	second41->setParent(parent41);
	parent41->addChild(second41);
	QueryTree* query41 = new QueryTree();
	query41->getRootNode()->getChild(1)->addChild(parent41);

	vector<int> actualResult41 = qe->solve("proc5", &table1, query41); // procedure proc5; Select proc5 such that Parent(7, 9) | Expected <1>
	
	CPPUNIT_ASSERT_EQUAL((size_t)1, actualResult41.size());
	CPPUNIT_ASSERT_EQUAL(0, actualResult41.at(0));
	*/
	QTNode* parent42 = new QTNode("Parent");
	QTNode* first42 = new QTNode(3);
	QTNode* second42 = new QTNode("s2");
	first42->setParent(parent42);
	parent42->addChild(first42);
	second42->setParent(parent42);
	parent42->addChild(second42);
	QueryTree* query42 = new QueryTree();
	query42->getRootNode()->getChild(1)->addChild(parent42);

	vector<int> actualResult42 = qe->solve("s1", &table1, query42); // stmt s1, s2; Select s1 such that Parent(3, s2) | Expected <1, 2, 3, 4, 5, 6, 7, 8, 9, 10>
	
	CPPUNIT_ASSERT_EQUAL((size_t)10, actualResult42.size());
	CPPUNIT_ASSERT_EQUAL(1, actualResult42.at(0));
	CPPUNIT_ASSERT_EQUAL(2, actualResult42.at(1));
	CPPUNIT_ASSERT_EQUAL(3, actualResult42.at(2));
	CPPUNIT_ASSERT_EQUAL(4, actualResult42.at(3));
	CPPUNIT_ASSERT_EQUAL(5, actualResult42.at(4));
	CPPUNIT_ASSERT_EQUAL(6, actualResult42.at(5));
	CPPUNIT_ASSERT_EQUAL(7, actualResult42.at(6));
	CPPUNIT_ASSERT_EQUAL(8, actualResult42.at(7));
	CPPUNIT_ASSERT_EQUAL(9, actualResult42.at(8));
	CPPUNIT_ASSERT_EQUAL(10, actualResult42.at(9));

	QTNode* parent43 = new QTNode("Parent");
	QTNode* first43 = new QTNode(10);
	QTNode* second43 = new QTNode("s2");
	first43->setParent(parent43);
	parent43->addChild(first43);
	second43->setParent(parent43);
	parent43->addChild(second43);
	QueryTree* query43 = new QueryTree();
	query43->getRootNode()->getChild(1)->addChild(parent43);

	vector<int> actualResult43 = qe->solve("s1", &table1, query43); // stmt s1, s2; Select s1 such that Parent(10, s2) | Expected <> (none)
	
	CPPUNIT_ASSERT(actualResult43.empty());

	QTNode* parent44 = new QTNode("Parent");
	QTNode* first44 = new QTNode(3);
	QTNode* second44 = new QTNode("a3");
	first44->setParent(parent44);
	parent44->addChild(first44);
	second44->setParent(parent44);
	parent44->addChild(second44);
	QueryTree* query44 = new QueryTree();
	query44->getRootNode()->getChild(1)->addChild(parent44);

	vector<int> actualResult44 = qe->solve("a2", &table1, query44); // assign a2, a3; Select a2 such that Parent(3, a3) | Expected <1, 2, 4, 5, 8>
	
	CPPUNIT_ASSERT_EQUAL((size_t)5, actualResult44.size());
	CPPUNIT_ASSERT_EQUAL(1, actualResult44.at(0));
	CPPUNIT_ASSERT_EQUAL(2, actualResult44.at(1));
	CPPUNIT_ASSERT_EQUAL(4, actualResult44.at(2));
	CPPUNIT_ASSERT_EQUAL(5, actualResult44.at(3));
	CPPUNIT_ASSERT_EQUAL(8, actualResult44.at(4));

	QTNode* parent45 = new QTNode("Parent");
	QTNode* first45 = new QTNode("a2");
	QTNode* second45 = new QTNode("a3");
	first45->setParent(parent45);
	parent45->addChild(first45);
	second45->setParent(parent45);
	parent45->addChild(second45);
	QueryTree* query45 = new QueryTree();
	query45->getRootNode()->getChild(1)->addChild(parent45);

	vector<int> actualResult45 = qe->solve("s1", &table1, query45); // stmt s1; assign a2, a3; Select s1 such that Parent(a2, a3) | Expected <> (none)
	
	CPPUNIT_ASSERT(actualResult45.empty());

	QTNode* parent46 = new QTNode("Parent");
	QTNode* first46 = new QTNode("w3");
	QTNode* second46 = new QTNode("w4");
	first46->setParent(parent46);
	parent46->addChild(first46);
	second46->setParent(parent46);
	parent46->addChild(second46);
	QueryTree* query46 = new QueryTree();
	query46->getRootNode()->getChild(1)->addChild(parent46);

	vector<int> actualResult46 = qe->solve("s1", &table1, query46); // stmt s1; while w3, w4; Select s1 such that Parent(w3, w4) | Expected <1,2,3,4,5,6,7,8,9,10>
	
	CPPUNIT_ASSERT_EQUAL((size_t)10, actualResult46.size());
	CPPUNIT_ASSERT_EQUAL(1, actualResult46.at(0));
	CPPUNIT_ASSERT_EQUAL(2, actualResult46.at(1));
	CPPUNIT_ASSERT_EQUAL(3, actualResult46.at(2));
	CPPUNIT_ASSERT_EQUAL(4, actualResult46.at(3));
	CPPUNIT_ASSERT_EQUAL(5, actualResult46.at(4));
	CPPUNIT_ASSERT_EQUAL(6, actualResult46.at(5));
	CPPUNIT_ASSERT_EQUAL(7, actualResult46.at(6));
	CPPUNIT_ASSERT_EQUAL(8, actualResult46.at(7));
	CPPUNIT_ASSERT_EQUAL(9, actualResult46.at(8));
	CPPUNIT_ASSERT_EQUAL(10, actualResult46.at(9));

	QTNode* parent47 = new QTNode("Parent*");
	QTNode* first47 = new QTNode(3);
	QTNode* second47 = new QTNode("s1");
	first47->setParent(parent47);
	parent47->addChild(first47);
	second47->setParent(parent47);
	parent47->addChild(second47);
	QueryTree* query47 = new QueryTree();
	query47->getRootNode()->getChild(1)->addChild(parent47);

	vector<int> actualResult47 = qe->solve("s1", &table1, query47); // stmt s1; Select s1 such that ParentStar(3, s1) | Expected <4,5,6,7,8,9,10> 
	
	CPPUNIT_ASSERT_EQUAL((size_t)7, actualResult47.size());
	CPPUNIT_ASSERT_EQUAL(4,actualResult47[0]);
	CPPUNIT_ASSERT_EQUAL(5,actualResult47[1]);
	CPPUNIT_ASSERT_EQUAL(6,actualResult47[2]);
	CPPUNIT_ASSERT_EQUAL(7,actualResult47[3]);
	CPPUNIT_ASSERT_EQUAL(8,actualResult47[4]);
	CPPUNIT_ASSERT_EQUAL(9,actualResult47[5]);
	CPPUNIT_ASSERT_EQUAL(10,actualResult47[6]);

	QTNode* parent48 = new QTNode("Parent*");
	QTNode* first48 = new QTNode("s1");
	QTNode* second48 = new QTNode(9);
	first48->setParent(parent48);
	parent48->addChild(first48);
	second48->setParent(parent48);
	parent48->addChild(second48);
	QueryTree* query48 = new QueryTree();
	query48->getRootNode()->getChild(1)->addChild(parent48);

	vector<int> actualResult48 = qe->solve("s1", &table1, query48); // stmt s1; Select s1 such that ParentStar(s1, 9) | Expected <3,6,7>
	
	CPPUNIT_ASSERT_EQUAL(7,actualResult48[0]);
	CPPUNIT_ASSERT_EQUAL(6,actualResult48[1]);
	CPPUNIT_ASSERT_EQUAL(3,actualResult48[2]);

	QTNode* parent49 = new QTNode("Parent*");
	QTNode* first49 = new QTNode(3);
	QTNode* second49 = new QTNode(9);
	first49->setParent(parent49);
	parent49->addChild(first49);
	second49->setParent(parent49);
	parent49->addChild(second49);
	QueryTree* query49 = new QueryTree();
	query49->getRootNode()->getChild(1)->addChild(parent49);

	vector<int> actualResult49 = qe->solve("w3", &table1, query49); // while w1; Select w1 such that ParentStar(3, 9) | Expected <3,6,7,9,10>
	
	CPPUNIT_ASSERT_EQUAL(3,actualResult49[0]);
	CPPUNIT_ASSERT_EQUAL(6,actualResult49[1]);
	CPPUNIT_ASSERT_EQUAL(7,actualResult49[2]);
	CPPUNIT_ASSERT_EQUAL(9,actualResult49[3]);
	CPPUNIT_ASSERT_EQUAL(10,actualResult49[4]);

	QTNode* parent50 = new QTNode("Parent*");
	QTNode* first50 = new QTNode(6);
	QTNode* second50 = new QTNode(8);
	first50->setParent(parent50);
	parent50->addChild(first50);
	second50->setParent(parent50);
	parent50->addChild(second50);
	QueryTree* query50 = new QueryTree();
	query50->getRootNode()->getChild(1)->addChild(parent50);

	vector<int> actualResult50 = qe->solve("a2", &table1, query50); // assign a2; Select a2 such that ParentStar(6, 8) | Expected <1,2,4,5,8>

	CPPUNIT_ASSERT_EQUAL(1,actualResult50[0]);
	CPPUNIT_ASSERT_EQUAL(2,actualResult50[1]);
	CPPUNIT_ASSERT_EQUAL(4,actualResult50[2]);
	CPPUNIT_ASSERT_EQUAL(5,actualResult50[3]);
	CPPUNIT_ASSERT_EQUAL(8,actualResult50[4]);
	/*
	QTNode* parent51 = new QTNode("Parent*");
	QTNode* first51 = new QTNode(3);
	QTNode* second51 = new QTNode(9);
	first51->setParent(parent51);
	parent51->addChild(first51);
	second51->setParent(parent51);
	parent51->addChild(second51);
	QueryTree* query51 = new QueryTree();
	query51->getRootNode()->getChild(1)->addChild(parent51);

	vector<int> actualResult51 = qe->solve("proc5", &table1, query51); // procedure proc5; Select proc5 such that ParentStar(3, 9) | Expected <Proc1>
	
	CPPUNIT_ASSERT(actualResult51[0]==0);
	*/
}
