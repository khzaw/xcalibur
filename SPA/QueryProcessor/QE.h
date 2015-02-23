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
	vector<pair<int, int>> unionOrder;
	void sortQuerySets();
	void solveQuerySets();
	void joinQuerySolutions();
	//bool pairCompare(pair<int, int>&, pair<int, int>&);
	//bool subqueriesCompare(Subquery&, Subquery&);

public:
	QE(vector<string>);
	vector<ResultTuple*> solutions;
	void addQuery(Subquery);
	void solve();
	void unionQuerySets();
	vector<vector<Subquery>> queries;
	void trimSolution();
	map<string, int> disjointCheck;
	void basicSolve();
};

struct pairCompare {
	bool operator()(pair<int, int>& first, pair<int, int>& second) {
	  return  max(first.first, first.second) < max(second.first, second.second);
	}
};

struct subqueriesCompare {
	bool operator()(Subquery& first, Subquery& second) {
		return first.getPriority() < second.getPriority();
	}
};