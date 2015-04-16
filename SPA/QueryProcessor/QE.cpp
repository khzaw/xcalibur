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

	if (queries.size() > 0) {
		if (useOptimizedSolver) {
			OptimizedQE solver = OptimizedQE(queries, synonyms);
			solution = solver.solve();
			//answers = solver.solve2();
		} else {
			basicSolve();
		}
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

		queries[i]->setPriority();
	}

	//check for extra synonyms
	for (size_t i = 0; i < synonyms.size() ; i++) {
		size_t f = synonyms[i].find(".");
		if (f != string::npos) {
			string syn = synonyms[i].substr(0, f);
			if (synMap.find(syn) == synMap.end()) {
				StubSubquery* x = new StubSubquery(&synonymTable, pkb);//new StubSubquery(synonymTable, pkb); 
				x->setSynonyms(syn, 0);
				addQuery(x);
			}
		} else {
			if (synMap.find(synonyms[i]) == synMap.end() && synonyms[i] != "BOOLEAN") {
				StubSubquery* s = new StubSubquery(&synonymTable, pkb);//new StubSubquery(synonymTable, pkb); 
				s->setSynonyms(synonyms[i], 0);
				addQuery(s);
			}
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
		if (queries.size() == 0) {
			ans.push_back("FALSE");
			ans.push_back("TRUE");
			return ans;
		}
		if (solution->isBool()) {
			if (solution->isEmpty()){
				ans.push_back("FALSE");
			} else {
				ans.push_back("TRUE");
			}
			return ans;
		}
		if (solution->getAllResults().size() > 0){
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
		size_t f = synonyms[i].find(".");
		if (f == string::npos) {
			int temp = solution->getSynonymIndex(synonyms[i]);
			index.push_back(temp);
		} else {
			index.push_back(solution->getSynonymIndex(synonyms[i].substr(0, f)));
		}
	}

	int total_size = solution->getAllResults().size();
	for (int i = 0; i < total_size; i++) {
		string s = "";
		for (size_t k = 0; k < index.size(); k++) {
			string syn_type = synonymTable.at(solution->getSynonym(index[k]));
			size_t f = synonyms[index[k]].find(".");
			
			int sol = solution->getResultAt(i, index[k]);
			if (syn_type == "procedure"){
				if (f == string::npos) {
					s += pkb->procTable->getProcName(sol);
				} else {
					string attr = synonyms[index[k]].substr(f, synonyms[index[k]].size());
					//if (attr == "procName") {} else {} 
					s += pkb->procTable->getProcName(sol);
				}
			} else if (syn_type == "variable"){
				if (f == string::npos) {
					s += pkb->varTable->getVarName(sol);
				} else {
					string attr = synonyms[index[k]].substr(f, synonyms[index[k]].size());
					//if (attr == "varnName"){} else {}
					s += pkb->varTable->getVarName(sol);
				}
				
			} else if (syn_type == "constant"){
				if (f == string::npos) {
					s += to_string((long long) pkb->constantTable->getConstant(sol));
				} else {
					string attr = synonyms[index[k]].substr(f, synonyms[index[k]].size());
					//if (attr == "value"){} else {}
					s += to_string((long long) pkb->constantTable->getConstant(sol));
				}
			} else {
				if (f == string::npos) {
					s += to_string((long long) sol);
				} else {
					string attr = synonyms[index[k]].substr(f, synonyms[index[k]].size());
					if (attr == ".stmt#") {
						s += to_string((long long) sol);
					} else if (syn_type == "call" && attr == ".procName") {
						s += pkb->statementTable->getTNode(sol)->getData();
					} else if ((syn_type == "if" || syn_type == "while") && attr == ".varName") {
						s += pkb->statementTable->getTNode(sol)->getData();
					}
				}
			}

			if(k != (index.size() - 1)) {
				s += " "; 
			}
		}
		ans.push_back(s);
	}
	return ans;
}