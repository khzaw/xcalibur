#include <cppunit/config/SourcePrefix.h>
#include "TestOptimizedQE.h"
#include "QueryProcessor\OptimizedQE.h"
#include "QueryProcessor\Subquery.h"
#include "QueryProcessor\OptimizedQE.cpp"
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
OptimizedQETest::setUp()
{
}

void 
OptimizedQETest::tearDown()
{
}	

CPPUNIT_TEST_SUITE_REGISTRATION( OptimizedQETest );
// method to test insertion of Follows

void OptimizedQETest::testQE() {
	testMakeDisjointSet();
}

void OptimizedQETest::testMakeDisjointSet() {
	OptimizedQE qe = OptimizedQE();
	map<string, string> synonymTable = map<string, string>();
	PKBController pk = PKBController();
	NextStarSubquery* y1 = new NextStarSubquery(&synonymTable, &pk);
	y1->setSynonyms(4, "s1");
	NextStarSubquery* y2 = new NextStarSubquery(&synonymTable, &pk);
	y2->setSynonyms("s1", "s2");
	NextStarSubquery* y3 = new NextStarSubquery(&synonymTable, &pk);
	y3->setSynonyms("s2", 12);
	NextStarSubquery* y4 = new NextStarSubquery(&synonymTable, &pk);
	y4->setSynonyms(4, "s1");
	NextStarSubquery* y5 = new NextStarSubquery(&synonymTable, &pk);
	y5->setSynonyms("s2", "s3");
	NextStarSubquery* y6 = new NextStarSubquery(&synonymTable, &pk);
	y6->setSynonyms("s3", 12);
	NextStarSubquery* y7 = new NextStarSubquery(&synonymTable, &pk);
	y7->setSynonyms(4, "s3");
	NextStarSubquery* y8 = new NextStarSubquery(&synonymTable, &pk);
	y8->setSynonyms("s3", "s4");
	NextStarSubquery* y9 = new NextStarSubquery(&synonymTable, &pk);
	y9->setSynonyms("s4", 12);
	NextStarSubquery* y10 = new NextStarSubquery(&synonymTable, &pk);
	y10->setSynonyms(4, "s2");
	NextStarSubquery* y11 = new NextStarSubquery(&synonymTable, &pk);
	y11->setSynonyms("s2", "s4");
	NextStarSubquery* y12 = new NextStarSubquery(&synonymTable, &pk);
	y12->setSynonyms("s2", 19);
	FollowsSubquery* z1 = new FollowsSubquery(&synonymTable, &pk);
	z1->setSynonyms("a1", "w1");
	ParentSubquery* z2 = new ParentSubquery(&synonymTable, &pk);
	z2->setSynonyms("w1", "i1");
	FollowsStarSubquery* z3 = new FollowsStarSubquery(&synonymTable, &pk);
	z3->setSynonyms("i1", "c1");
	vector<Subquery*> que;
	que.push_back(y1);
	que.push_back(y2);
	que.push_back(y3);
	que.push_back(y4);
	que.push_back(y5);
	que.push_back(y6);
	que.push_back(y7);
	que.push_back(y8);
	que.push_back(y9);
	que.push_back(y10);
	que.push_back(y11);
	que.push_back(y12);
	que.push_back(z1);
	que.push_back(z2);
	que.push_back(z3);
	vector<vector<Subquery*> > q;
	q = qe.makeDisjointSets(que);
	cout << endl;
	for (size_t i = 0; i < q.size(); i++){
		cout << "Disjoint set number " << i << ": " << endl;
		for (size_t j = 0; j < q[i].size(); j++){
			cout << "(";
			switch (q[i][j]->isSyn){
				case 0: cout << q[i][j]->leftIndex << ", " << q[i][j]->rightIndex; break;
				case 1: case 8: cout << q[i][j]->leftIndex << ", " << q[i][j]->rightSynonym; break;
				case 2: case 7: cout << q[i][j]->leftSynonym << ", " << q[i][j]->rightIndex; break;
				case 3: case 4: case 5: case 6: cout << q[i][j]->leftSynonym << ", " << q[i][j]->rightSynonym; break;
			}
			cout << ") ";
		}
		cout << endl;
	}

	Subquery* t1 = new Subquery(&synonymTable, &pk);
	t1->setSynonyms("a", "b");
	Subquery* t2 = new Subquery(&synonymTable, &pk);
	t2->setSynonyms("b", "c");
	Subquery* t3 = new Subquery(&synonymTable, &pk);
	t3->setSynonyms("a", "a");
	Subquery* t4 = new Subquery(&synonymTable, &pk);
	t4->setSynonyms("_", "a");
	Subquery* t5 = new Subquery(&synonymTable, &pk);
	t5->setSynonyms("_", "_");
	Subquery* t6 = new Subquery(&synonymTable, &pk);
	t6->setSynonyms("d", "e");
	Subquery* t7 = new Subquery(&synonymTable, &pk);
	t7->setSynonyms("d", 1);
	Subquery* t8 = new Subquery(&synonymTable, &pk);
	t8->setSynonyms(1, 2);
	Subquery* t9 = new Subquery(&synonymTable, &pk);
	t9->setSynonyms("a", "e");
	Subquery* t10 = new Subquery(&synonymTable, &pk);
	t10->setSynonyms("f", "g");
	Subquery* t11 = new Subquery(&synonymTable, &pk);
	t11->setSynonyms("g", "g");
	Subquery* t12 = new Subquery(&synonymTable, &pk);
	t12->setSynonyms("ga", "y");
	Subquery* t13 = new Subquery(&synonymTable, &pk);
	t13->setSynonyms("y", "olo");
	Subquery* t14 = new Subquery(&synonymTable, &pk);
	t14->setSynonyms("y", "eo");
	Subquery* t15 = new Subquery(&synonymTable, &pk);
	t15->setSynonyms("m", "an");
	Subquery* t16 = new Subquery(&synonymTable, &pk);
	t16->setSynonyms("_", "_");
	Subquery* t17 = new Subquery(&synonymTable, &pk);
	t17->setSynonyms(12, "_");
	Subquery* t18 = new Subquery(&synonymTable, &pk);
	t18->setSynonyms("an", "z");
	Subquery* t19 = new Subquery(&synonymTable, &pk);
	t19->setSynonyms("gg", "gg");
	Subquery* t20 = new Subquery(&synonymTable, &pk);
	t20->setSynonyms("ba", "ck");
	Subquery* t21 = new Subquery(&synonymTable, &pk);
	t21->setSynonyms(14, 14);
	Subquery* t22 = new Subquery(&synonymTable, &pk);
	t22->setSynonyms("ck", 15);
	vector<Subquery*> que1;
	que1.push_back(t1);
	que1.push_back(t2);
	que1.push_back(t3);
	que1.push_back(t4);
	que1.push_back(t5);
	que1.push_back(t6);
	que1.push_back(t7);
	que1.push_back(t8);
	que1.push_back(t9);
	que1.push_back(t10);
	que1.push_back(t11);
	que1.push_back(t12);
	que1.push_back(t13);
	que1.push_back(t14);
	que1.push_back(t15);
	que1.push_back(t16);
	que1.push_back(t17);
	que1.push_back(t18);
	que1.push_back(t19);
	que1.push_back(t20);
	que1.push_back(t21);
	que1.push_back(t22);
	vector<vector<Subquery*> > q1;
	q1 = qe.makeDisjointSets(que1);
	cout << endl;
	for (size_t i = 0; i < q1.size(); i++){
		cout << "Disjoint set number " << i << ": " << endl;
		for (size_t j = 0; j < q1[i].size(); j++){
			cout << "(";
			switch (q1[i][j]->isSyn){
				case 0: cout << q1[i][j]->leftIndex << ", " << q1[i][j]->rightIndex; break;
				case 1: case 8: cout << q1[i][j]->leftIndex << ", " << q1[i][j]->rightSynonym; break;
				case 2: case 7: cout << q1[i][j]->leftSynonym << ", " << q1[i][j]->rightIndex; break;
				case 3: case 4: case 5: case 6: cout << q1[i][j]->leftSynonym << ", " << q1[i][j]->rightSynonym; break;
			}
			cout << ") ";
		}
		cout << endl;
	}
}