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
		return (synonymTable->at(leftSynonym) == "assign") ? solveAssign() : solveIfWhile(t);
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
		vector<int> assign = pkb->statementTable.getStmtNumUsingNodeType("assign");
		switch(isSyn) {
			{case 0: case 2: case 7:		//pattern a ("x", ...)
				for (int i = 0; i < assign.size(); i++) {
					if (pkb->modifiesTable.evaluateIsModifiesStmt(assign[i], rightIndex)) {	//if modifies(a[i], "x")
						if(matchPattern(pkb->statementTable.getTNode(assign[i])->getData())) {
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
				for (int i = 0; i < assign.size(); i++) {
					string temp = pkb->statementTable.getTNode(assign[i])->getData();
					if(matchPattern(temp)) {
						vector<int> temp2 = vector<int>();
						temp2.push_back(assign[i]);
						temp2.push_back(pkb->varTable.getVarIndex(temp));
						tuple->addResultRow(temp2);
					}
				}
				break;
			}
			{default:					//pattern a (_, ...)
				for(int i = 0; i < assign.size(); i++) {
					if (matchPattern(pkb->statementTable.getTNode(assign[i])->getData())) {
						for (int j = 0; j < assign.size(); j++) {
							vector<int> temp = vector<int>();
							temp.push_back(assign[i]);
							tuple->addResultRow(temp);
						}
						break;
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
		
		switch(isSyn) {
			{case 0: case 2: case 7:		//pattern a ("x", ...)
				for (int i = 0; i < r->getAllResults().size(); i++) {
					int res = r->getResultAt(index, i);
					if (pkb->modifiesTable.evaluateIsModifiesStmt(res, rightIndex)) {	//if modifies(a[i], "x")
						if(matchPattern(pkb->statementTable.getTNode(res)->getData())) {
							tuple->addResultRow(r->getResultRow(i));
						}
					}
				}
				break;
			}
			{case 1: case 3: case 4:		//pattern a (syn, ...)
				int lIndex = r->getSynonymIndex(leftSynonym);
				int rIndex = r->getSynonymIndex(rightSynonym);
				if (lIndex != -1 && rIndex != -1){ //case 1: both are inside
					tuple = assignBothSyn(tuple, r, lIndex, rIndex);
				} else if (rIndex == -1) { //case 2: only left is inside
					tuple = assignLeftSyn(tuple, r, lIndex);
				} else { //case 3: only right is inside
					tuple = assignRightSyn(tuple, r, rIndex);
				}
			}
			{default:					//pattern a (_, ...)
				for(int i = 0; i < r->getAllResults().size(); i++) {
					int res = r->getResultAt(index, i);
					if (matchPattern(pkb->statementTable.getTNode(res)->getData())) {
						tuple->addResultRow(r->getResultRow(i));
					}
				}
			}
		}
		return tuple;
	}

	ResultTuple* assignRightSyn(ResultTuple* answer, ResultTuple* r, int index) {
		int ind = answer->addSynonym(leftSynonym);
		answer->addSynonymToMap(leftSynonym, ind);
		for (int i = 0; i < r->getAllResults().size(); i++) {
			// can store this in map
			vector<int> assign = pkb->statementTable.getStmtNumUsingNodeType("assign");
			for (int j = 0; j < assign.size(); j++) {
				if (pkb->modifiesTable.evaluateIsModifiesStmt(assign[j], r->getResultAt(i, index)) && 
					matchPattern(pkb->statementTable.getTNode(assign[j])->getData())) {
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
		for (int i = 0; i < r->getAllResults().size(); i++) {
			// can store this in map
			vector<int> var = pkb->varTable.getAllVarNum();
			for (int j = 0; j < var.size(); j++) {
				if (pkb->modifiesTable.evaluateIsModifiesStmt(r->getResultAt(i, index), var[j]) && 
					matchPattern(pkb->statementTable.getTNode(r->getResultAt(i, index))->getData())) {
						answer->addResultRow(r->getResultRow(i));
						answer->addResult(r->getAllResults().size()-1, var[j]);
				}
			}
		}
		return answer;
	}

	ResultTuple* assignBothSyn(ResultTuple* answer, ResultTuple* r, int lIndex, int rIndex) {
		for (int i = 0; i < r->getAllResults().size(); i++) {
			if (pkb->modifiesTable.evaluateIsModifiesStmt(r->getResultAt(i, lIndex), r->getResultAt(i, rIndex)) && 
				matchPattern(pkb->statementTable.getTNode(r->getResultAt(i, lIndex))->getData())) {
					answer->addResultRow(r->getResultRow(i));
			}
		}
		return answer;
	}

	ResultTuple* solveIfWhile() {
		ResultTuple* tuple = new ResultTuple();
		UsesSubquery* s = new UsesSubquery(this->synonymTable, this->pkb);
		switch(isSyn) {
			case 0: case 2: case 7:	//pattern i (int, _) -> if(x)
				s->setSynonyms(leftSynonym, rightIndex);
				break;	
			default :	//pattern i (syn, _) or (_, _)
				s->setSynonyms(leftSynonym, rightSynonym);
		}
		tuple = s->solve();
		return tuple;
	}

	ResultTuple* solveIfWhile(ResultTuple* rt) {
		ResultTuple* tuple = new ResultTuple();
		UsesSubquery* s = new UsesSubquery(this->synonymTable, this->pkb);
		switch(isSyn) {
			case 0: case 2: case 7:	//pattern i (int, _) -> if(x)
				s->setSynonyms(leftSynonym, rightIndex);
				break;	
			default :	//pattern i (syn, _) or (_, _)
				s->setSynonyms(leftSynonym, rightSynonym);
		}
		tuple = s->solve(rt);
		return tuple;
	}
};