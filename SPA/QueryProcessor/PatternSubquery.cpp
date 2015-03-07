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
			{case 0: case 2: case 7:		//pattern a (int, ...)
				for (size_t i = 0; i < assign.size(); i++) {
					if (pkb->modifiesTable.evaluateIsModifiesStmt(assign[i], rightIndex)) {
						if(matchPattern(pkb->statementTable.getTNode(assign[i])->getData())) {
							// insert
						}
					}
				}
				break;
			}
			{case 1: case 3: case 4:		//pattern a (syn, ...)
				// get all assignment statements
				break;
			}
			{default:					//pattern a (_, ...)
				for(size_t i = 0; i < assign.size(); i++) {
					//check if one pattern matches
					//if match, return all assignment
				}
			}
		}
		return tuple;
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