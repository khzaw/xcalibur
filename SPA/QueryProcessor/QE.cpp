#pragma once
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <algorithm>

#include "QE.h"
#include "OptimizedQE.h"
#include "Subquery.h"
#include "ResultTuple.h"

using namespace std;

// syn = synonyms required in solution. Put Boolean in here too
QE::QE(vector<string> syn) {
	useOptimizedSolver = true;
	synonyms = syn;
	queries = vector<Subquery*>();
}

void QE::addQuery(Subquery* q) {
	queries.push_back(q);
}

void QE::solve() {
	if (useOptimizedSolver) {
		OptimizedQE solver = OptimizedQE(queries);
		solution = solver.solve();
	} else {
		basicSolve();
	}

	if (synonyms[0] == "BOOLEAN") {
		if (solution->getAllResults().size() == 0) {
			//return false;
		} else {
			//return true;
		}
	} 

	if(solution->getAllResults().size() == 0) {
		//return nothing
	}

	trimSolution();
	// return vector<string>?
}

void QE::basicSolve() {
	for (size_t i = 0; i < queries.size(); i++) {
		ResultTuple* interim = queries[i]->solve();
		if (interim->isBool() && interim->isEmpty()) {
			solution = new ResultTuple();
			return;
		}
		if (i > 0) {
			solution = solution->join(interim);
		} else {
			solution = interim;
		}
	} 
}

void QE::trimSolution() {
	// problem: Select <s1 ,s3> such that follows(s1, s2)
	
	vector<int> syns = vector<int>();
	vector<vector<int>> newSolution = vector<vector<int> >();
	//get index of synonyms for solutions
	for (size_t i = 0; i < synonyms.size(); i++) {
		syns.push_back(solution->getSynonymIndex(synonyms[i]));
	}

	for (size_t i = 0; i < solution->getAllResults().size(); i++) { 
		vector<int> temp = vector<int>();
		for (size_t j = 0; j < syns.size(); j++) {
			temp.push_back(solution->getResultAt(i, syns[j]));
		}
		newSolution.push_back(temp);
	}
}