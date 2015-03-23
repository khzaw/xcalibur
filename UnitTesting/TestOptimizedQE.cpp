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
	cout << "end" << endl;
}