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
	useOptimizedSolver = false;
	synonyms = syn;
	queries = vector<Subquery*>();
	pkb = p;
}

void QE::addQuery(Subquery* q) {
	queries.push_back(q);
}

string QE::solve() {
	vector<string> answer = vector<string>();
	if (!validateQueries()) {
		return "none";
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
	for (int i = 0; i < queries.size(); i++) {
		if (!queries[i]->validate()) {
			return false;
		}
	}
	return true;
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

string QE::convertSolutionToString() {
	if (synonyms[0] == "BOOLEAN") {
		if (solution->isBool()) {
			return (solution->isEmpty()) ? "FALSE" : "TRUE";
		}
		return (solution->getAllResults().size()) ? "TRUE" : "FALSE"; 
	} 

	if (solution->getAllResults().size() == 0) {
		return "none";
	}
	
	string s = "";
	vector<int> index = vector<int>();
	//get index of synonyms
	for (size_t i = 0; i < synonyms.size(); i++) {
		int temp = solution->getSynonymIndex(synonyms[i]);
		index.push_back(temp);
	}

	int total_size = solution->getAllResults().size();
	for (size_t i = 0; i < total_size; i++) {
		for (int k = 0; k < index.size(); k++) {
			string syn_type = synonymTable.at(solution->getSynonym(index[k]));
			int sol = solution->getResultAt(i, index[k]);
			if (syn_type == "procedure"){
				s += pkb->procTable.getProcName(sol);
			} else if (syn_type == "variable"){
				s += pkb->varTable.getVarName(sol);
			} else if (syn_type == "constant"){
				s += to_string((long long) pkb->constantTable.getConstant(sol));
			} else {
				s += to_string((long long) sol);
			}

			if(k != (index.size() - 1)) {
				s += " "; 
			}
		}

		if (i != (total_size - 1)) {
			s += ", ";
		}
	}
	return s;
}