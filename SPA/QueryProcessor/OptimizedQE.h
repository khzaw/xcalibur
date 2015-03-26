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
	ResultTuple* finalSolution;
	vector<vector<Subquery*>> queries;
	vector<string> synonyms;

	OptimizedQE();
	OptimizedQE(vector<Subquery*>, vector<string>);
	ResultTuple* solve();
	vector<ResultTuple*> solve2();
	void splitIntoDisjoint(vector<Subquery*>);
	vector<vector<Subquery*> > makeDisjointSets(vector<Subquery*>);
	void setParent(map<string, string>*, string, string);
	string findParent(string, map<string, string>*);
	void unionQuerySets();
	void sortQuerySets();
	void solveQuerySets();
	void joinQuerySolutions(vector<ResultTuple*>);
	ResultTuple* optimizedJoin(vector<ResultTuple*>);
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