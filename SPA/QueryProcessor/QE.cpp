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

vector<string> QE::solve() {
	vector<string> answer = vector<string>();
	if (!validateQueries()) {
		answer.push_back("none");
		return answer;
	}
	if (useOptimizedSolver) {
		OptimizedQE solver = OptimizedQE(queries);
		solution = solver.solve();
	} else {
		basicSolve();
	}

	if (synonyms[0] == "BOOLEAN") {
		if (solution->getAllResults().size() == 0) {
			answer.push_back("FALSE");
		} else {
			answer.push_back("TRUE");
		}
		return answer;
	} 

	if(solution->getAllResults().size() == 0) {
		answer.push_back("none");
		return answer;
	}

	//trimSolution();
	return convert();
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

vector<string> QE::convert() {
	vector<string> answer = vector<string>();
	for (size_t i = 0; i < solution->getAllResults().size(); i++) {
		string x = "";
		for (size_t j = 0; j < solution->getResultRow(i).size(); j++) {
			string synonym = solution->getSynonym(j);
			int aSolution = solution->getResultAt(i, j);
			if (synonym == "procedure"){
				x += pkb->procTable.getProcName(aSolution);
			} else if (synonym == "variable"){
				x += pkb->varTable.getVarName(aSolution);
			} else if (synonym == "constant"){
				x += to_string((long long)pkb->constantTable.getConstant(aSolution));
			} else {
				x += to_string((long long)aSolution);
			}
			if(j != solution->getResultRow(i).size() - 1) {
				x += " "; 
			}
		}
		answer.push_back(x);
	}
	return answer;
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
		cout << "syn" << solution->getSynonymIndex(synonyms[i]);
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