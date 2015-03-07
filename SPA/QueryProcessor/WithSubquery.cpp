#pragma once
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include "Subquery.h"

using namespace std;

class WithSubquery : public Subquery{
public:
	WithSubquery(map<string, string>* m, PKBController* p) : Subquery(m, p){
	
	}

	ResultTuple* solve(){
		ResultTuple* ans;
		switch (isSyn) {
			case 1: case 4:
				//ans = solveRightSyn();
				break;
			case 2: case 5:
				ans = solveLeftSyn();
				break;
			case 3:
				//ans = solveBothSyn();
				break;
			default:
				//ans = solveOther();
				break;
		}
		return ans;
	}
	
	ResultTuple* solve(ResultTuple* tuple) {
		ResultTuple* ans;
		switch (isSyn) {
			case 1: case 4:
				//ans = solveRightSyn(tuple);
				break;
			case 2: case 5:
				//ans = solveLeftSyn(tuple);
				break;
			case 3:
				//ans = solveBothSyn(tuple);
				break;
			default: break;
		}
		return ans;
	}

	vector<int> getValues(string syn, int index){
		vector<int> values = vector<int>();
		if (synonymTable->at(syn)=="procedure"){
			if (index < pkb->procTable.getSize()){
				values.push_back(index);
			}
		} else if (synonymTable->at(syn)=="variable"){
			if (index < pkb->varTable.getSize()){
				values.push_back(index);
			}
		} else if (synonymTable->at(syn)=="constant"){
			if (pkb->constantTable.containsConst(index)){
				values.push_back(index);
			}
		} else {
			if (synonymTable->at(syn)=="stmt" || synonymTable->at(syn) == "prog_line"){
				if (index < pkb->statementTable.getSize()){
					values.push_back(index);
				}
			} else if (synonymTable->at(syn)=="assign" || synonymTable->at(syn) == "while" || synonymTable->at(syn)=="if" || synonymTable->at(syn) == "call"){
				if (index < pkb->statementTable.getSize() && pkb->statementTable.getTNode(index)->getNodeType()==TNODE_NAMES[synToNodeType.at(synonymTable->at(syn))]){
					values.push_back(index);
				}
			}
		}
		return values;
	}

	ResultTuple* solveLeftSyn() {
		ResultTuple* tuple = new ResultTuple();
		int index = tuple->addSynonym(leftSynonym);
		tuple->addSynonymToMap(leftSynonym, index);
		vector<int> values = vector<int>();
		if (isSyn == 2) {	// with syn.attr = varnum: Get syn that have attr equals to varnum
			values = getValues(leftSynonym, rightIndex);
		} else {	// Uses(syn, _): Get all users
			// invalid
		}

		for(size_t i = 0; i < values.size(); i++) {
			vector<int> temp = vector<int>();
			temp.push_back(values.at(i));
			tuple->addResultRow(temp);
		}
		return tuple;
	}
};