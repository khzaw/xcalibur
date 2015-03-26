#pragma once
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <algorithm>

#include "QE.h"
#include "OptimizedQE.h"
#include "Subquery.h"
#include "StubSubquery.cpp"
#include "ResultTuple.h"

using namespace std;

// syn = synonyms required in solution. Put Boolean in here too
QE::QE(vector<string> syn, PKBController* p) {
	useOptimizedSolver = true;
	synonyms = syn;
	queries = vector<Subquery*>();
	answers = vector<ResultTuple*>();
	memo = map<int, list<string>>();
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
		OptimizedQE solver = OptimizedQE(queries, synonyms);
		solution = solver.solve();
		//answers = solver.solve2();
	} else {
		basicSolve();
	}

	return convertSolutionToString();
}

bool QE::validateQueries() {
	map<string, int> synMap = map<string, int>();
	for (size_t i = 0; i < queries.size(); i++) {
		switch(queries[i]->isSyn) {
			case 1: case 4:
				synMap.insert(make_pair(queries[i]->rightSynonym, i));
				break;
			case 2: case 5:
				synMap.insert(make_pair(queries[i]->leftSynonym, i));
				break;
			case 3:
				synMap.insert(make_pair(queries[i]->rightSynonym, i));
				synMap.insert(make_pair(queries[i]->leftSynonym, i));
				break;
		}
		
		if (!queries[i]->validate()) {
			return false;
		}
	}

	//check for extra synonyms
	for (size_t i = 0; i < synonyms.size() ; i++) {
		if (synMap.find(synonyms[i]) == synMap.end()) {
			StubSubquery* s = new StubSubquery(&synonymTable, pkb);//new StubSubquery(synonymTable, pkb); 
			s->setSynonyms(synonyms[i], 0);
			addQuery(s);
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

/*
list<string> QE::convertSolutionToString() {
	list<string> ans = list<string>();
	if (synonyms[0] == "BOOLEAN") {
		for (size_t i = 0; i < answers.size(); i++) {
			if (answers[i]->isBool()&& answers[i]->isEmpty()) {
				ans.push_back("FALSE");
				return ans;
			} else if (answers[i]->getAllResults().size() == 0){
				ans.push_back("FALSE");
				return ans;
			}
		}
		ans.push_back("TRUE");
		return ans;
	} 
	
	vector<int> row = vector<int>();
	vector<int> col = vector<int>();
	//get index of synonyms
	for (size_t i = 0; i < synonyms.size(); i++) {
		for (size_t j = 0; j < answers.size(); j++) {
			int ind = answers[j]->getSynonymIndex(synonyms[i]);
			if(ind >= 0) {
				row.push_back(i);
				col.push_back(ind);
				break;
			}
		}
	}

	for (size_t i = 0; i < answers.size(); i++) {
		
	}

	//return getAnswers(row, col, 0, answers.size());
}

list<string> QE::getAnswers(vector<int> row, vector<int> col, int index, int length) {
	list<string> x = list<string>();
	if (index == (answers.size() - 1)) {
		string syn_type = synonymTable.at(answers[row.at(index)]->getSynonym(col.at(index)));
		for (size_t i = 0; i < answers[row.at(index)]->getAllResults().size(); i++) {
			int sol = answers[row.at(index)]->getResultAt(row.at(index), col.at(index));
			if (syn_type == "procedure"){
				x.push_back(pkb->procTable->getProcName(sol));
			} else if (syn_type == "variable"){
				x.push_back(pkb->varTable->getVarName(sol));
			} else if (syn_type == "constant"){
				x.push_back(to_string((long long) pkb->constantTable->getConstant(sol)));
			} else {
				x.push_back(to_string((long long) sol));
			}
		}
		memo.insert(pair<int, list<string>>(length, x));
		return x;
	}

	list<string> l;
	if (memo.find(length) != memo.end()) {
		l = memo.at(length);
	} else {
		l = getAnswers(row, col, index + 1, length - 1);
	}

	for (size_t i = 0; i < answers[row.at(index)]->getAllResults().size(); i++) {
		string syn_type = synonymTable.at(answers[row.at(index)]->getSynonym(col.at(index)));
		string temp = "";
		int sol = answers[row.at(index)]->getResultAt(row.at(index), col.at(index));
		if (syn_type == "procedure"){
			temp += (pkb->procTable->getProcName(sol));
		} else if (syn_type == "variable"){
			temp += (pkb->varTable->getVarName(sol));
		} else if (syn_type == "constant"){
			temp += (to_string((long long) pkb->constantTable->getConstant(sol)));
		} else {
			temp += (to_string((long long) sol));
		}
		
		for (list<string>::iterator j = l.begin(); j != l.end(); j++) {
			x.push_back(temp + " " + *j);
		}
	}
	memo.insert(pair<int, list<string>>(length, x));
	return x;
}

/*
list<string> QE::getAnswers(vector<int> row, vector<int> col, int index) {
	string key = row[index] + "," + col[index];
	list<string> x = list<string>();
	if (index == (answers.size() - 1)) {
		string syn_type = synonymTable.at(answers[row.at(index)]->getSynonym(col.at(index)));
		for (size_t i = 0; i < answers[row.at(index)]->getAllResults().size(); i++) {
			int sol = answers[row.at(index)]->getResultAt(row.at(index), col.at(index));
			if (syn_type == "procedure"){
				x.push_back(pkb->procTable->getProcName(sol));
			} else if (syn_type == "variable"){
				x.push_back(pkb->varTable->getVarName(sol));
			} else if (syn_type == "constant"){
				x.push_back(to_string((long long) pkb->constantTable->getConstant(sol)));
			} else {
				x.push_back(to_string((long long) sol));
			}
		}
		memo.insert(pair<string, list<string>>(key, x));
		return x;
	}

	list<string> l;
	if (memo.find(row[index+1]+","+col[index+1]) != memo.end()) {
		l = memo.at(row[index+1]+","+col[index+1]);
	} else {
		l = getAnswers(row, col, index + 1);
	}
	for (size_t i = 0; i < answers[row.at(index)]->getAllResults().size(); i++) {
		string syn_type = synonymTable.at(answers[row.at(index)]->getSynonym(col.at(index)));
		string temp = "";
		int sol = answers[row.at(index)]->getResultAt(row.at(index), col.at(index));
		if (syn_type == "procedure"){
			temp += (pkb->procTable->getProcName(sol));
		} else if (syn_type == "variable"){
			temp += (pkb->varTable->getVarName(sol));
		} else if (syn_type == "constant"){
			temp += (to_string((long long) pkb->constantTable->getConstant(sol)));
		} else {
			temp += (to_string((long long) sol));
		}
		
		for (list<string>::iterator j = l.begin(); j != l.end(); j++) {
			x.push_back(temp + " " + *j);
		}
	}
	memo.insert(pair<string, list<string>>(key, x));
	return x;
}
*/

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