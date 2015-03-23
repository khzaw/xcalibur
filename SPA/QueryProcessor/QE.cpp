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
QE::QE(vector<string> syn, PKBController* p) {
	useOptimizedSolver = true;
	synonyms = syn;
	queries = vector<Subquery*>();
	pkb = p;
}

void QE::setSynonymTable(map<string, string> s){
	this->synonymTable = s;
}

void QE::addQuery(Subquery* q) {
	queries.push_back(q);
}

list<string> QE::solve() {
	vector<string> answer = vector<string>();
	if (!validateQueries()) {
		list<string> none = list<string>();
		return none;
	}

	if (useOptimizedSolver) {
		OptimizedQE solver = OptimizedQE(queries);
		solution = solver.solve();
	} else {
		basicSolve();
	}

	return convertSolutionToString();
}

bool QE::validateQueries() {
	// can check extra synonyms here.
	for (size_t i = 0; i < queries.size(); i++) {
		if (!queries[i]->validate()) {
			return false;
		}
	}
	return true;
}

void QE::basicSolve() {
	solution = queries[0]->solve();
	for(size_t i = 1; i < queries.size(); i++) {
		if((solution->getSynonymIndex(queries[i]->leftSynonym) != -1) || (solution->getSynonymIndex(queries[i]->rightSynonym) != -1)) {
			solution = queries[i]->solve(solution);
		} else {
			ResultTuple* interim = queries[i]->solve();
			solution = solution->cross(interim);
		}
	}
}

list<string> QE::convertSolutionToString() {
	list<string> ans = list<string>();
	if (synonyms[0] == "BOOLEAN") {
		if (solution->isBool()) {
			if (solution->isEmpty()){
				ans.push_back("FALSE");
			} else {
				ans.push_back("TRUE");
			}
			return ans;
		}
		if (solution->getAllResults().size()){
			ans.push_back("TRUE");
		} else {
			ans.push_back("FALSE");
		}
		return ans;
	} 

	if (solution->getAllResults().size() == 0) {
		return ans;
	}
	vector<int> index = vector<int>();
	//get index of synonyms
	for (size_t i = 0; i < synonyms.size(); i++) {
		int temp = solution->getSynonymIndex(synonyms[i]);
		index.push_back(temp);
	}

	int total_size = solution->getAllResults().size();
	for (int i = 0; i < total_size; i++) {
		string s = "";
		for (size_t k = 0; k < index.size(); k++) {
			string syn_type = synonymTable.at(solution->getSynonym(index[k]));
			int sol = solution->getResultAt(i, index[k]);
			if (syn_type == "procedure"){
				s += pkb->procTable->getProcName(sol);
			} else if (syn_type == "variable"){
				s += pkb->varTable->getVarName(sol);
			} else if (syn_type == "constant"){
				s += to_string((long long) pkb->constantTable->getConstant(sol));
			} else {
				s += to_string((long long) sol);
			}

			if(k != (index.size() - 1)) {
				s += " "; 
			}
		}
		ans.push_back(s);
	}
	return ans;
}
