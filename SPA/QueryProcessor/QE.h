#pragma once
#include <vector>
#include <string>
#include <map>
#include <queue>

#include "Subquery.h"
#include "ResultTuple.h"

using namespace std;

class QE {
private:
	vector<string> synonyms;
	bool useOptimizedSolver;
	PKBController* pkb;

public:
	ResultTuple* solution;
	vector<Subquery*> queries;

	QE(vector<string>, PKBController*);
	void addQuery(Subquery*);
	vector<string> solve();
	void trimSolution();
	void basicSolve();
	vector<string> convert();
};