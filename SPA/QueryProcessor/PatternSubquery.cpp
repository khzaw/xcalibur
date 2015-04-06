#pragma once
#include <string>
#include <vector>
#include <map>
#include "Subquery.h"
#include "UsesSubquery.cpp"
#include "ModifiesSubquery.cpp"

using namespace std;

class PatternSubquery : public Subquery {
public:
	PatternSubquery(map<string, string>* m, PKBController* p) : Subquery(m, p){}
	PatternSubquery(map<string, string>* m, PKBController* p, bool b) : Subquery(m, p, b){}
	
	ResultTuple* solve(){
		return (synonymTable->at(leftSynonym) == "assign") ? solveAssign() : solveIfWhile();
	}

	ResultTuple* solve(ResultTuple* t){
		return (synonymTable->at(leftSynonym) == "assign") ? solveAssign(t) : solveIfWhile(t);
	}

	bool validate() {
		if (synonymTable->at(leftSynonym) == "assign" || synonymTable->at(leftSynonym) == "while" || synonymTable->at(leftSynonym) == "if") {
			if(isSyn == 1 || isSyn == 4 || isSyn == 3) {
				if (synonymTable->at(rightSynonym) != "variable") {
					return false;
				}
			}
		} else {
			return false;
		}
		return true;
	}

	void setPriority() {
		if (synonymTable->at(leftSynonym) == "assign") {
			priority = pkb->statementTable->getStmtNumUsingNodeType("ASSIGN_NODE").size();
		} else if (synonymTable->at(leftSynonym) == "if") {
			priority = pkb->statementTable->getStmtNumUsingNodeType("IF_NODE").size();
		} else {
			priority = pkb->statementTable->getStmtNumUsingNodeType("WHILE_NODE").size();
		}
	}

	bool matchPattern(string target) {
		if (specialValue == "_") {
			return true;
		}
		if (isUnderscore) {
			return (target.find(specialValue) != std::string::npos);
		} else {
			return (specialValue == target);
		}
	}

	ResultTuple* solveAssign() {
		ResultTuple* tuple = new ResultTuple();
		int index = tuple->addSynonym(leftSynonym);
		tuple->addSynonymToMap(leftSynonym, index);
		vector<int> assign = pkb->statementTable->getStmtNumUsingNodeType("ASSIGN_NODE");
		switch(isSyn) {
			{case 0: case 2: case 7:		//pattern a (int, ...)
				for (size_t i = 0; i < assign.size(); i++) {
					if (pkb->modifiesTable->evaluateIsModifiesStmt(assign[i], rightIndex)) {
						if(matchPattern(pkb->statementTable->getTNode(assign[i])->getData())) {
							vector<int> temp = vector<int>();
							temp.push_back(assign[i]);
							tuple->addResultRow(temp);
						}
					}
				}
				break;
			}
			{case 1: case 3: case 4:		//pattern a (syn, ...)
				// get all assignment statements
				int index2 = tuple->addSynonym(rightSynonym);
				tuple->addSynonymToMap(rightSynonym, index2);
				for (size_t i = 0; i < assign.size(); i++) {
					string temp = pkb->statementTable->getTNode(assign[i])->getData();
					if(matchPattern(temp)) {
						vector<int> temp2 = vector<int>();
						temp2.push_back(assign[i]);
						temp2.push_back(*(pkb->modifiesTable->evaluateGetModifiedVarStmt(assign[i]).begin()));
						tuple->addResultRow(temp2);
					}
				}
				break;
			}
			{default:					//pattern a (_, ...)
				for(size_t i = 0; i < assign.size(); i++) {
					if (matchPattern(pkb->statementTable->getTNode(assign[i])->getData())) {
						/*
						for (size_t j = 0; j < assign.size(); j++) {
							vector<int> temp = vector<int>();
							temp.push_back(assign[i]);
							tuple->addResultRow(temp);
						}
						break;
						*/
						vector<int> temp = vector<int>();
						temp.push_back(assign[i]);
						tuple->addResultRow(temp);
					}
				}
			}
		}
		return tuple;
	}

	ResultTuple* solveAssign(ResultTuple* r) {
		ResultTuple* tuple = new ResultTuple();
		tuple->setSynonym(r->getSynonyms());
		tuple->setSynonymMap(r->getSynonymMap());
		int index = r->getSynonymIndex(leftSynonym);
		
		if (isSyn == 0 || isSyn == 2 || isSyn == 7) { //pattern a ("x", ...)
			for (size_t i = 0; i < r->getAllResults().size(); i++) {
				int res = r->getResultAt(i, index);
				if (pkb->modifiesTable->evaluateIsModifiesStmt(res, rightIndex)) {	//if modifies(a[i], "x")
					if(matchPattern(pkb->statementTable->getTNode(res)->getData())) {
						tuple->addResultRow(r->getResultRow(i));
					}
				}
			}
		} else if (isSyn == 1 || isSyn == 3 || isSyn == 4) { //pattern a (syn, ...)
			int lIndex = r->getSynonymIndex(leftSynonym);
			int rIndex = r->getSynonymIndex(rightSynonym);
			if (lIndex != -1 && rIndex != -1){ //case 1: both are inside
				tuple = assignBothSyn(tuple, r, lIndex, rIndex);
			} else if (rIndex == -1) { //case 2: only left is inside
				tuple = assignLeftSyn(tuple, r, lIndex);
			} else { //case 3: only right is inside
				tuple = assignRightSyn(tuple, r, rIndex);
			}
		} else {
			for(size_t i = 0; i < r->getAllResults().size(); i++) {
				int res = r->getResultAt(i, index);
				if (matchPattern(pkb->statementTable->getTNode(res)->getData())) {
					tuple->addResultRow(r->getResultRow(i));
				}
			}
		}

		return tuple;
	}

	ResultTuple* assignRightSyn(ResultTuple* answer, ResultTuple* r, int index) {
		int ind = answer->addSynonym(leftSynonym);
		answer->addSynonymToMap(leftSynonym, ind);
		for (size_t i = 0; i < r->getAllResults().size(); i++) {
			// can store this in map
			vector<int> assign = pkb->statementTable->getStmtNumUsingNodeType("ASSIGN_NODE");
			for (size_t j = 0; j < assign.size(); j++) {
				if (pkb->modifiesTable->evaluateIsModifiesStmt(assign[j], r->getResultAt(i, index)) && 
					matchPattern(pkb->statementTable->getTNode(assign[j])->getData())) {
						answer->addResultRow(r->getResultRow(i));
						answer->addResult(r->getAllResults().size()-1, assign[j]);
				}
			}
		}
		return answer;
	}

	ResultTuple* assignLeftSyn(ResultTuple* answer, ResultTuple* r, int index) {
		int ind = answer->addSynonym(rightSynonym);
		answer->addSynonymToMap(rightSynonym, ind);
		for (size_t i = 0; i < r->getAllResults().size(); i++) {
			// can store this in map
			vector<int> var = pkb->varTable->getAllVarNum();
			for (size_t j = 0; j < var.size(); j++) {
				if (pkb->modifiesTable->evaluateIsModifiesStmt(r->getResultAt(i, index), var[j]) && 
					matchPattern(pkb->statementTable->getTNode(r->getResultAt(i, index))->getData())) {
						answer->addResultRow(r->getResultRow(i));
						answer->addResult(r->getAllResults().size()-1, var[j]);
				}
			}
		}
		return answer;
	}

	ResultTuple* assignBothSyn(ResultTuple* answer, ResultTuple* r, int lIndex, int rIndex) {
		for (size_t i = 0; i < r->getAllResults().size(); i++) {
			if (pkb->modifiesTable->evaluateIsModifiesStmt(r->getResultAt(i, lIndex), r->getResultAt(i, rIndex)) && 
				matchPattern(pkb->statementTable->getTNode(r->getResultAt(i, lIndex))->getData())) {
					answer->addResultRow(r->getResultRow(i));
			}
		}
		return answer;
	}

	ResultTuple* solveIfWhile() {
		ResultTuple* tuple = new ResultTuple();
		tuple->addSynonymToMap(leftSynonym, tuple->addSynonym(leftSynonym));
		vector<int> nodes = (synonymTable->at(leftSynonym)=="while") ? pkb->statementTable->getStmtNumUsingNodeType("WHILE_NODE") : pkb->statementTable->getStmtNumUsingNodeType("IF_NODE");
		
		if (isSyn == 2) {
			for (size_t i = 0; i < nodes.size(); i++) {
				if (rightIndex == pkb->varTable->getVarIndex((pkb->statementTable->getTNode(nodes[i])->getData()))) {
					vector<int> temp = vector<int>();
					temp.push_back(nodes[i]);
					tuple->addResultRow(temp);
				}
			}
		} else if (isSyn == 3) {
			tuple->addSynonymToMap(rightSynonym, tuple->addSynonym(rightSynonym));
			for (size_t i = 0; i < nodes.size(); i++) {
				vector<int> temp = vector<int>();
				temp.push_back(nodes[i]);
				temp.push_back(pkb->varTable->getVarIndex((pkb->statementTable->getTNode(nodes[i])->getData())));
				tuple->addResultRow(temp);
			}
		} else {
			for (size_t i = 0; i < nodes.size(); i++) {
				vector<int> temp = vector<int>();
				temp.push_back(nodes[i]);
				tuple->addResultRow(temp);
			
			}
		}

		return tuple;
	}

	ResultTuple* solveIfWhile(ResultTuple* rt) {
		ResultTuple* result = new ResultTuple();
		result->setSynonym(rt->getSynonyms());
		result->setSynonymMap(rt->getSynonymMap());

		if (isSyn == 2) { //(Synonym, var_index)
			int index = rt->getSynonymIndex(leftSynonym);
			int size = rt->getAllResults().size();

			for (size_t i = 0; i < size; i++) {
				int cell = rt->getResultAt(i, index);
				if (pkb->varTable->getVarIndex(pkb->statementTable->getTNode(cell)->getData()) == rightIndex) {
					result->addResultRow(rt->getResultRow(i));
				}
			}
		} else if (isSyn == 3) { //(Synonym, Synonym)
			int left = rt->getSynonymIndex(leftSynonym);
			int right = rt->getSynonymIndex(rightSynonym);
			int size = rt->getAllResults().size();

			if (left != -1 && right != -1) {
				for (size_t i = 0; i < size; i++) {
					if (pkb->varTable->getVarIndex(pkb->statementTable->getTNode(rt->getResultAt(i, left))->getData()) == rt->getResultAt(i, right)) {
						result->addResultRow(rt->getResultRow(i));
					}
				}
			} else if (left != -1) {
				rt->addSynonymToMap(rightSynonym, rt->addSynonym(rightSynonym));
				for (size_t i = 0; i < size; i++) {
					int data = pkb->varTable->getVarIndex(pkb->statementTable->getTNode(rt->getResultAt(i, left))->getData());
					vector<int> row = rt->getResultRow(i);
					row.push_back(data);
					result->addResultRow(row);
				}
			} else if (right != -1) {
				rt->addSynonymToMap(leftSynonym, rt->addSynonym(leftSynonym));
				vector<int> nodes = (synonymTable->at(leftSynonym)=="while") ? pkb->statementTable->getStmtNumUsingNodeType("WHILE_NODE") : pkb->statementTable->getStmtNumUsingNodeType("IF_NODE");
				map <int, vector<int>> tempCache = map<int, vector<int>>();
				for (size_t i = 0; i < size; i++) {
					if (tempCache.find(rt->getResultAt(i, right)) != tempCache.end()) {
						vector<int> v = tempCache.at(rt->getResultAt(i, right));
						for (size_t j = 0; j < v.size(); j++) {
							vector<int> row = rt->getResultRow(i);
							row.push_back(v[j]);
							result->addResultRow(row);
						}
					} else {
						vector<int> v = vector<int>();
						for (size_t j = 0; j < nodes.size(); j++) {
							if (pkb->varTable->getVarIndex(pkb->statementTable->getTNode(nodes[j])->getData()) == rt->getResultAt(i, right)) {
								v.push_back(nodes[j]);
								vector<int> row = rt->getResultRow(i);
								row.push_back(nodes[j]);
								result->addResultRow(row);
							}
						}
						tempCache.insert(map<int,vector<int>>::value_type(rt->getResultAt(i, right), v));
					}
				}
			}
		} else { // (Synonym, _)
			// don't have to do anything?
		}

		return rt;
	}
};