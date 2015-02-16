#pragma once
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <algorithm>

#include "QE.h"
#include "Subquery.h"
#include "ResultTuple.h"

using namespace std;

// syn = synonyms required in solution. Put Boolean in here too
QE::QE(vector<string> syn) {
	synonyms = syn;
	disjointCheck = map<string, int>();	//string for synonym, int for positions in the vector which hold the synonym
	queries = vector<vector<Subquery*> >();
	unionOrder = vector<pair<int, int> >();
	solutions = vector<ResultTuple*>();
}

void QE::addQuery(Subquery* q) {
	if (queries.size() == 0) {
		queries.push_back(vector<Subquery*>());
	}
	queries[0].push_back(q);
}

/*
void QE::addQuery(Subquery q) {
	//isSyn
	// 1: (int, syn)	4: ("_", syn)
	// 2: (syn, int)	5: (syn, "_")
	// 3: (syn, syn)
	string s1, s2;
	if (q.isSyn == 2 || q.isSyn == 3 || q.isSyn == 5) {
		s1 = q.leftSynonym;
	}
	if (q.isSyn == 1 || q.isSyn == 3 || q.isSyn == 4) {
		s2 = q.rightSynonym;
	}

	if (disjointCheck.find(s1) != disjointCheck.end()) {
		queries.at(disjointCheck[s1]).push_back(q);
		if (q.isSyn == 3 && disjointCheck.find(s2) != disjointCheck.end() && disjointCheck[s1] != disjointCheck[s2]) {
			// both synonyms are already inside
			unionOrder.push_back(make_pair(disjointCheck[s1], disjointCheck[s2]));
		} else if (q.isSyn == 3) {	
			// only left synonym is inside
			disjointCheck.insert(map<string, int>::value_type(s2, disjointCheck[s1]));
		}
	} else if (disjointCheck.find(s2) != disjointCheck.end()) {	
		// only right synonym is inside
		queries.at(disjointCheck[s2]).push_back(q);
		if (q.isSyn == 3) {
			disjointCheck.insert(map<string, int>::value_type(s1, disjointCheck[s2]));
		}
	} else {	// new synonyms
		queries.push_back(vector<Subquery>());
		int index = queries.size() - 1;
		queries.at(index).push_back(q);
		if (q.isSyn == 2 || q.isSyn == 3 || q.isSyn == 5) { // only left is synonym
			disjointCheck.insert(map<string, int>::value_type(s1, index));
		}
		if (q.isSyn == 1 || q.isSyn == 3 || q.isSyn == 4) {
			disjointCheck.insert(map<string, int>::value_type(s2, index));
		}
	}
}
*/

void QE::solve() {
	/*
	unionQuerySets();
	sortQuerySets();
	solveQuerySets();
	if (synonyms[0] == "BOOLEAN") {
		if (solutions.size() == 0) {
			//return false;
		} else {
			//return true;
		}
	} 
	if (solutions.size() > 0) {
		joinQuerySolutions();
	}
	*/
	basicSolve();
	if (synonyms[0] == "BOOLEAN") {
		if (solutions[0]->getAllResults().size() == 0) {
			//return false;
		} else {
			//return true;
		}
	} 

	if(solutions[0]->getAllResults().size() == 0) {
		//return nothing
	}

	trimSolution();
	// everything is in solutions[0]
	// return vector<string>?
}

void QE::basicSolve() {
	for (int i = 0; i < queries[0].size(); i++) {
		ResultTuple* interim = queries[0][i]->solve();
		 if (interim->isBool()) {
			 if(interim->isEmpty()) {
				solutions[0] = new ResultTuple();
				return;
			 }
		} else {
			solutions.push_back(interim);
		}
	}
	for (int i = 1; i < solutions.size(); i++) {
		solutions[i] = solutions[0]->join(solutions[i]);
	}
}

void QE::trimSolution() {
	// problem: Select <s1 ,s3> such that follows(s1, s2)
	
	vector<int> syns = vector<int>();
	vector<vector<int>> newSolution = vector<vector<int> >();
	//get index of synonyms for solutions
	for (int i = 0; i < synonyms.size(); i++) {
		syns.push_back(solutions[0]->getSynonymIndex(synonyms[i]));
	}

	for (int i = 0; i < solutions[0]->getAllResults().size(); i++) { 
		vector<int> temp = vector<int>();
		for (int j = 0; j < syns.size(); j++) {
			temp.push_back(solutions[0]->getResultAt(i, syns[j]));
		}
		newSolution.push_back(temp);
	}
}

void QE::unionQuerySets() {
	// merge all common sets
	sort(unionOrder.begin(), unionOrder.end(), pairCompare());
	while (unionOrder.size() > 0) {
		int first = unionOrder.back().first;
		int second = unionOrder.back().second;
		int x = min(first, second);
		int y = max(first, second);
		unionOrder.pop_back();

		queries.at(x).insert(queries.at(x).end(), queries.at(y).begin(), queries.at(y).end());
		queries.erase(queries.end() - 1);
	}
}

void QE::sortQuerySets() {
	// sort each vector
	for (int i = 0; i < queries.size(); i++) {
		sort(queries.at(i).begin(), queries.at(i).end(), subqueriesCompare());
	}
}

void QE::solveQuerySets() {
	for (int i = 0; i < queries.size(); i++) {
		map<string, int> synonyms = map<string, int>();
		vector<Subquery*> qList = queries.at(i);
		ResultTuple* result = qList.front()->solve();
		int syn = qList.front()->isSyn;
		if (syn == 2 || syn == 3 || syn == 5) { // left is synonym
			synonyms.insert(map<string, int>::value_type(qList.front()->leftSynonym, 1));
		}
		if (syn == 1 || syn == 3 || syn == 4) { // right is synonym
			synonyms.insert(map<string, int>::value_type(qList.front()->rightSynonym, 1));
		}
		qList.erase(qList.begin());

		int index = 0;
		while (qList.size() > 0) {
			if (index >= qList.size()) {
				index = 0;
			}
			syn = qList.at(index)->isSyn;
			
			if (syn == 3) {
				if (synonyms.count(qList.at(index)->leftSynonym) == 1 || synonyms.count(qList.at(index)->rightSynonym) == 1) {
					result = qList.at(index)->solve(result);
					synonyms.insert(map<string, int>::value_type(qList.at(index)->leftSynonym, 1));
					synonyms.insert(map<string, int>::value_type(qList.at(index)->rightSynonym, 1));
					qList.erase(qList.begin() + index);
					index = 0;
				} else {
					index++;
				}
			} else if (syn == 2 || syn == 5) { // left is synonym
				if (synonyms.count(qList.at(index)->leftSynonym) == 1) {
					result = qList.at(index)->solve(result);
					qList.erase(qList.begin() + index);
					index = 0;
				} else {
					index++;
				}
			} else if (syn == 1 || syn == 4) { // right is synonym
				if (synonyms.count(qList.at(index)->rightSynonym) == 1) {
					result = qList.at(index)->solve(result);
					qList.erase(qList.begin() + index);
					index = 0;
				} else {
					index++;
				}
			}
		}

		if (result->isBool()) {
			if (result->isEmpty()) {
				solutions = vector<ResultTuple*>();
				return;
			} else {
				continue;
			}
		}
		
		if (result->getAllResults().size() == 0) {
			solutions = vector<ResultTuple*>();
			return;
		}

		solutions.push_back(result);
	}
}

void QE::joinQuerySolutions() {
	while (solutions.size() > 1) {
		solutions[0] = solutions[0]->cross(solutions[1]);
		solutions.erase(solutions.begin() + 1);
	}
}
