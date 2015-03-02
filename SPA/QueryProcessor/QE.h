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

public:
	ResultTuple* solution;
	vector<Subquery*> queries;

	QE(vector<string>);
	void addQuery(Subquery*);
	void solve();
	void trimSolution();
	void basicSolve();
};