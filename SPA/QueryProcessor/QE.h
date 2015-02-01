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
	map<string, int> disjointCheck;
	vector<pair<int, int>> unionOrder;
	vector<vector<Subquery>> queries;
	vector<ResultTuple*> solutions;
	void unionQuerySets();
	void sortQuerySets();
	void solveQuerySets();
	void joinQuerySolutions();
	bool pairCompare(pair<int, int>&, pair<int, int>&);
	bool subqueriesCompare(Subquery&, Subquery&);

public:
	QE();
	void addQuery(Subquery);
	void solve();

}