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
	bool useOptimizedSolver;
	PKBController* pkb;

public:
	map<string, string> synonymTable;
	vector<string> synonyms;
	ResultTuple* solution;
	vector<Subquery*> queries;
	bool validateQueries();
	QE(vector<string>, PKBController*);
	void addQuery(Subquery*);
	
	vector<string> solve();
	void trimSolution();
	void basicSolve();
	vector<string> convert();
	string convertToSolutionString();
};