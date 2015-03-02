#pragma once
#include <vector>
#include <string>
#include <map>
#include <queue>

#include "Subquery.h"
#include "ResultTuple.h"

using namespace std;

class OptimizedQE {
private:
	map<string, int> disjointCheck;
	bool useOptimizedSolver;
	vector<pair<int, int>> unionOrder;
	
	void addQuery(Subquery*);

public:
	vector<ResultTuple*> solutions;
	vector<vector<Subquery*>> queries;

	OptimizedQE(vector<Subquery*>);
	ResultTuple* solve();
	void splitIntoDisjoint(vector<Subquery*>);
	void unionQuerySets();
	void sortQuerySets();
	void solveQuerySets();
	void joinQuerySolutions();
};

struct pairCompare {
	bool operator()(pair<int, int>& first, pair<int, int>& second) {
	  return  max(first.first, first.second) < max(second.first, second.second);
	}
};

struct subqueriesCompare {
	bool operator()(Subquery* first, Subquery* second) {
		return first->getPriority() < second->getPriority();
	}
};