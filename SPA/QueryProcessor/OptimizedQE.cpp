#pragma once
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <algorithm>

#include "OptimizedQE.h"
#include "Subquery.h"
#include "ResultTuple.h"

using namespace std;

// syn = synonyms required in solution. Put Boolean in here too
OptimizedQE::OptimizedQE(vector<Subquery*> syn) {
	disjointCheck = map<string, int>();	//string for synonym, int for positions in the vector which hold the synonym
	queries = vector<vector<Subquery*> >();
	unionOrder = vector<pair<int, int> >();
	solutions = vector<ResultTuple*>();
	splitIntoDisjoint(syn);
	sortQuerySets();
}

void OptimizedQE::splitIntoDisjoint(vector<Subquery*> syn) {
	for (int i = 0; i < syn.size(); i++) {
		addQuery(syn[i]);
	}
	unionQuerySets();
}

void OptimizedQE::addQuery(Subquery* q) {
	//isSyn
	// 1: (int, syn)	4: ("_", syn)
	// 2: (syn, int)	5: (syn, "_")
	// 3: (syn, syn)
	string s1, s2;
	if (q->isSyn == 2 || q->isSyn == 3 || q->isSyn == 5) {
		s1 = q->leftSynonym;
	}
	if (q->isSyn == 1 || q->isSyn == 3 || q->isSyn == 4) {
		s2 = q->rightSynonym;
	}

	if (disjointCheck.find(s1) != disjointCheck.end()) {
		queries.at(disjointCheck[s1]).push_back(q);
		if (q->isSyn == 3 && disjointCheck.find(s2) != disjointCheck.end() && disjointCheck[s1] != disjointCheck[s2]) {
			// both synonyms are already inside
			unionOrder.push_back(make_pair(disjointCheck[s1], disjointCheck[s2]));
		} else if (q->isSyn == 3) {	
			// only left synonym is inside
			disjointCheck.insert(map<string, int>::value_type(s2, disjointCheck[s1]));
		}
	} else if (disjointCheck.find(s2) != disjointCheck.end()) {	
		// only right synonym is inside
		queries.at(disjointCheck[s2]).push_back(q);
		if (q->isSyn == 3) {
			disjointCheck.insert(map<string, int>::value_type(s1, disjointCheck[s2]));
		}
	} else {	// new synonyms
		queries.push_back(vector<Subquery*>());
		int index = queries.size() - 1;
		queries.at(index).push_back(q);
		if (q->isSyn == 2 || q->isSyn == 3 || q->isSyn == 5) { // only left is synonym
			disjointCheck.insert(map<string, int>::value_type(s1, index));
		}
		if (q->isSyn == 1 || q->isSyn == 3 || q->isSyn == 4) {
			disjointCheck.insert(map<string, int>::value_type(s2, index));
		}
	}
}

void OptimizedQE::unionQuerySets() {
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

ResultTuple* OptimizedQE::solve() {
	solveQuerySets();
	joinQuerySolutions();
	return solutions[0];
}

void OptimizedQE::sortQuerySets() {
	// sort each vector
	for (size_t i = 0; i < queries.size(); i++) {
		sort(queries.at(i).begin(), queries.at(i).end(), subqueriesCompare());
	}
}

void OptimizedQE::solveQuerySets() {
	for (size_t i = 0; i < queries.size(); i++) {
		// init
		map<string, int> synonyms = map<string, int>();
		vector<Subquery*> qList = queries.at(i);
		
		// solve the first query
		ResultTuple* result = qList.front()->solve();
		
		int syn = qList.front()->isSyn;
		if (syn == 2 || syn == 3 || syn == 5) { // left is synonym
			synonyms.insert(map<string, int>::value_type(qList.front()->leftSynonym, 1));
		}
		if (syn == 1 || syn == 3 || syn == 4) { // right is synonym
			synonyms.insert(map<string, int>::value_type(qList.front()->rightSynonym, 1));
		}
		qList.erase(qList.begin());

		size_t index = 0;
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

		// boolean results, end prematurely if empty
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

void OptimizedQE::joinQuerySolutions() {
	while (solutions.size() > 1) {
		solutions[0] = solutions[0]->cross(solutions[1]);
		solutions.erase(solutions.begin() + 1);
	}
}
