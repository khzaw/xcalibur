#pragma once
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <algorithm>

#include "OptimizedQE.h"
#include "OptimizedSubquerySolver.h"
#include "Subquery.h"
#include "ResultTuple.h"

using namespace std;

OptimizedQE::OptimizedQE(){
}

// syn = synonyms required in solution. Put Boolean in here too
OptimizedQE::OptimizedQE(vector<Subquery*> subs, vector<string> synos) {
	disjointCheck = map<string, int>();	//string for synonym, int for positions in the vector which hold the synonym
	queries = makeDisjointSets(subs);
	solutions = vector<ResultTuple*>();
	finalSolution = new ResultTuple();
	synonyms = synos;
	sortQuerySets();
}

vector<vector<Subquery*> > OptimizedQE::makeDisjointSets(vector<Subquery*> syn){
	vector<vector<Subquery*> > results;
	set<string> synonyms;
	for_each(syn.begin(), syn.end(), [&](Subquery* s) {
		if (s->isSyn == 1 || s->isSyn == 4){
			synonyms.insert(s->rightSynonym);
		}
		if (s->isSyn == 2 || s->isSyn == 5){
			synonyms.insert(s->leftSynonym);
		}
		if (s->isSyn == 3){
			synonyms.insert(s->leftSynonym);
			synonyms.insert(s->rightSynonym);
		}
	});
	map<string, string> parents;
	for_each(synonyms.begin(), synonyms.end(), [&](string s){
		parents.insert(make_pair(s, s));
	});
	for_each(syn.begin(), syn.end(), [&](Subquery* s) {
		if (s->isSyn == 3){
			if (s->leftSynonym < s->rightSynonym){
				setParent(&parents, s->leftSynonym, s->rightSynonym);
			} else if (s->leftSynonym > s->rightSynonym){
				setParent(&parents, s->rightSynonym, s->leftSynonym);
			}
		}
	});
	int numSet = 0;
	map<string, int> synToSet;
	for_each(synonyms.begin(), synonyms.end(), [&](string s) {
		if (parents.at(s) == s){
			synToSet.insert(make_pair(s, numSet));
			numSet++;
		} else {
			string parent = findParent(s, &parents);
			synToSet.insert(make_pair(s, synToSet.at(parent)));
		}
	});
	for (int i = 0; i < numSet; i++){
		vector<Subquery* > temp;
		results.push_back(temp);
	}
	for_each(syn.begin(), syn.end(), [&](Subquery* s) {
		if (s->isSyn == 1 || s->isSyn == 4){
			int index = synToSet.at(s->rightSynonym);
			results[index].push_back(s);
		} else if (s->isSyn == 2 || s->isSyn == 5){
			int index = synToSet.at(s->leftSynonym);
			results[index].push_back(s);
		} else if (s->isSyn == 3){
			int index = synToSet.at(s->leftSynonym);
			results[index].push_back(s);
		} else {
			vector<Subquery*> temp;
			temp.push_back(s);
			results.push_back(temp);
		}
	});
	return results;
}

void OptimizedQE::setParent(map<string, string>* parents, string parent, string child){
	if (parents->at(child) == child){
		parents->at(child) = parent;
	} else if (parents->at(child) > parent){
		setParent(parents, parent, parents->at(child));
	} else if (parents->at(child) < parent){
		setParent(parents, parents->at(child), parent);
		parents->at(child) = parent;
	}
}

string OptimizedQE::findParent(string child, map<string, string>* parents){
	if (child == parents->at(child)){
		return child;
	} else {
		return findParent(parents->at(child), parents);
	}
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
	OptimizedSubquerySolver qss = OptimizedSubquerySolver();
	//joinQuerySolutions(qss.multithreadSolve(queries));
	//return finalSolution;
	return optimizedJoin(qss.multithreadSolve(queries));
}

vector<ResultTuple*> OptimizedQE::solve2() {
	OptimizedSubquerySolver qss = OptimizedSubquerySolver();
	return qss.multithreadSolve(queries);
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

ResultTuple* OptimizedQE::optimizedJoin(vector<ResultTuple*> r) {
	vector<ResultTuple*> tuples;
	ResultTuple* answer = new ResultTuple();
	for (size_t i = 0; i < r.size(); i++) {
		if ((r[i]->isBool() && r[i]->isEmpty()) || r[i]->getAllResults().empty()) {
			return answer;
		} 

		ResultTuple* rt = new ResultTuple();
		vector<int> synons = vector<int>();
		// check which synonyms are inside
		for (size_t j = 0; j < synonyms.size(); j++) {
			int temp = r[i]->getSynonymIndex(synonyms[j]);
			if (temp >= 0) {
				synons.push_back(temp);
				rt->addSynonymToMap(synonyms[j], rt->addSynonym(synonyms[j]));
			}
		}
		if (synons.size() == 0) {
			continue;
		}

		// reduce the columns for each row
		set<vector<int>> sets = set<vector<int>>();
		for (size_t l = 0; l < r[i]->getAllResults().size(); l++ ) {
			vector<int> oldRow = r[i]->getResultRow(l);
			vector<int> newRow = vector<int>();
			for (size_t m = 0; m < synons.size(); m++) {
				newRow.push_back(oldRow[synons[m]]);
			}
			//rt->addResultRow(newRow);
			sets.insert(newRow);
		}
		for (set<vector<int>>::iterator it = sets.begin(); it != sets.end(); it++) {
			rt->addResultRow(*it);
		}

		tuples.push_back(rt);
	}

	if (tuples.size() == 0) {
		return answer;
	}

	answer = tuples[0];
	for (size_t n = 1; n < tuples.size(); n++) {
		answer = answer->cross(tuples[n]);
	}

	return answer;
}

void OptimizedQE::joinQuerySolutions(vector<ResultTuple*> r) {
	if (r.size() > 0) {
		finalSolution = r[0];
	}
	for (size_t i = 1; i < r.size(); i++) {
		finalSolution = finalSolution->cross(r[i]);
	}
}
