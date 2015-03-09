#pragma once
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include "Subquery.h"

using namespace std;

class UsesSubquery : public Subquery{
public:
	UsesSubquery(map<string, string>* m, PKBController* p) : Subquery(m, p){
	
	}

	ResultTuple* solve(){
		ResultTuple* ans;
		switch (isSyn) {
			case 1: case 4:
				ans = solveRightSyn();
				break;
			case 2: case 5:
				ans = solveLeftSyn();
				break;
			case 3:
				ans = solveBothSyn();
				break;
			default:
				ans = solveOther();
		}
		return ans;
	}
	
	ResultTuple* solve(ResultTuple* tuple) {
		ResultTuple* ans;
		switch (isSyn) {
			case 1: case 4:
				ans = solveRightSyn(tuple);
				break;
			case 2: case 5:
				ans = solveLeftSyn(tuple);
				break;
			case 3:
				ans = solveBothSyn(tuple);
				break;
			default: break;
		}
		return ans;
	}

	ResultTuple* solveLeftSyn() {
		ResultTuple* tuple = new ResultTuple();
		int index = tuple->addSynonym(leftSynonym);
		tuple->addSynonymToMap(leftSynonym, index);
		vector<int> users = vector<int>();
		if (isSyn == 2) {	// Uses(syn, varnum): Get syns that uses varnum
			set<int> tempUsers = pkb->usesTable.evaluateGetUsersStmt(rightIndex);
			copy(tempUsers.begin(), tempUsers.end(), back_inserter(users));
		} else {	// Uses(syn, _): Get all users
			set<int> tempUsers = pkb->usesTable.getAllUsersStmt();
			copy(tempUsers.begin(), tempUsers.end(), back_inserter(users));
		}

		for(size_t i = 0; i < users.size(); i++) {
			vector<int> temp = vector<int>();
			// synonym type check here
			if ((synonymTable->at(leftSynonym)=="assign" || synonymTable->at(leftSynonym)=="while" || synonymTable->at(leftSynonym)=="if" || synonymTable->at(leftSynonym)=="call")
				&& pkb->statementTable.getTNode(users[i])->getNodeType()!=TNODE_NAMES[synToNodeType.at(synonymTable->at(leftSynonym))]){
				continue;
			}
			temp.push_back(users.at(i));
			tuple->addResultRow(temp);
		}
		return tuple;
	}

	ResultTuple* solveLeftSyn(ResultTuple* tuple) {
		ResultTuple* result = new ResultTuple();
		result->setSynonym(tuple->getSynonyms());
		result->setSynonymMap(tuple->getSynonymMap());

		int index = tuple->getSynonymIndex(leftSynonym);
		for (size_t i = 0; i < tuple->getAllResults().size(); i++) {
			vector<int> temp = tuple->getAllResults().at(i);
			if (isSyn == 2) {	// Uses(syn, varnum)
				if (pkb->usesTable.evaluateIsUsesStmt(temp.at(index), rightIndex)) {
					result->addResultRow(temp);
				}
			} else {	// Uses(syn, _)
				if (!pkb->usesTable.evaluateGetUsedVarStmt(temp.at(index)).empty()) {
					result->addResultRow(temp);
				}
			}
		}
		return result;
	}

	ResultTuple* solveRightSyn() {
		ResultTuple* tuple = new ResultTuple();
		int index = tuple->addSynonym(rightSynonym);
		tuple->addSynonymToMap(rightSynonym, index);
		
		vector<int> used;
		if (isSyn == 1) {	// Uses(stmt, varnum): Get Users of varnum
			set<int> tempUsed = pkb->usesTable.evaluateGetUsersStmt(leftIndex);
			copy(tempUsed.begin(), tempUsed.end(), back_inserter(used));
		} else {	// Uses(_, varnum)
			//invalid
		}

		for(size_t i = 0; i < used.size(); i++) {
			vector<int> temp = vector<int>();
			// synonym type check here
			if ((synonymTable->at(rightSynonym)=="assign" || synonymTable->at(rightSynonym)=="while" || synonymTable->at(rightSynonym)=="if" || synonymTable->at(rightSynonym)=="call")
				&& pkb->statementTable.getTNode(used[i])->getNodeType()!=TNODE_NAMES[synToNodeType.at(synonymTable->at(rightSynonym))]){
				continue;
			}
			temp.push_back(used.at(i));
			tuple->addResultRow(temp);
		}
		return tuple;
	}

	ResultTuple* solveRightSyn(ResultTuple* tuple) {
		ResultTuple* result = new ResultTuple();
		result->setSynonym(tuple->getSynonyms());
		result->setSynonymMap(tuple->getSynonymMap());

		int index = tuple->getSynonymIndex(rightSynonym);
		for (size_t i = 0; i < tuple->getAllResults().size(); i++) {
			vector<int> temp = tuple->getAllResults().at(i);
			if (isSyn == 1) {	// Uses(stmt, syn)
				if (pkb->usesTable.evaluateIsUsesStmt(leftIndex, temp.at(index))) {
					result->addResultRow(temp);
				}
			} else {	// Uses(_, syn)
				//invalid
			}
		}
		return result;
	}

	ResultTuple* solveBothSyn() {
		ResultTuple* tuple = new ResultTuple();
		int index = tuple->addSynonym(leftSynonym);
		tuple->addSynonymToMap(leftSynonym, index);
		index = tuple->addSynonym(rightSynonym);
		tuple->addSynonymToMap(rightSynonym, index);

		// get all users statement
		// for each users statement, get its used var
		vector<pair<int, int>> stmts = pkb->usesTable.getUsesStmt();
		for (size_t i = 0; i < stmts.size(); i++) {
			// synonym type check
			if ((synonymTable->at(leftSynonym)=="assign" || synonymTable->at(leftSynonym)=="while" || synonymTable->at(leftSynonym)=="if" || synonymTable->at(leftSynonym)=="call")
				&& pkb->statementTable.getTNode(stmts[i].first)->getNodeType()!=TNODE_NAMES[synToNodeType.at(synonymTable->at(leftSynonym))]){
				continue;
			}
			vector<int> row = vector<int>();
			row.push_back(stmts[i].first);
			row.push_back(stmts[i].second);
			tuple->addResultRow(row);
		}
		return tuple;
	}

	ResultTuple* solveBothSyn(ResultTuple* tuple) {
		ResultTuple* result = new ResultTuple();
		result->setSynonym(tuple->getSynonyms());
		result->setSynonymMap(tuple->getSynonymMap());

		int lIndex = tuple->getSynonymIndex(leftSynonym);
		int rIndex = tuple->getSynonymIndex(rightSynonym);
		if (lIndex != -1 && rIndex != -1){ //case 1: both are inside
			for (size_t i = 0; i < tuple->getAllResults().size(); i++){
				if (pkb->usesTable.evaluateIsUsesStmt(tuple->getAllResults()[i][lIndex], tuple->getAllResults()[i][rIndex])){
					result->addResultRow(tuple->getResultRow(i));
				}
			}
		} else if (rIndex == -1) { //case 2: only left is inside
			int index = result->addSynonym(rightSynonym);
			result->addSynonymToMap(rightSynonym, index);
			map<int, vector<int>> prevSolution = map<int, vector<int>>();
			for (size_t i = 0; i < tuple->getAllResults().size(); i++) {
				int leftValue = tuple->getResultAt(i, lIndex);
				if (prevSolution.find(leftValue) == prevSolution.end()){
					set<int> tV = pkb->usesTable.evaluateGetUsedVarStmt(leftValue);
					vector<int> tempValues(tV.begin(), tV.end());
					prevSolution.insert(make_pair(leftValue, tempValues));
				}
				vector<int> vals = prevSolution.at(leftValue);
				for (size_t j = 0; j < vals.size(); j++){
					if ((synonymTable->at(rightSynonym)=="assign" || synonymTable->at(rightSynonym)=="while" || synonymTable->at(rightSynonym)=="if" || synonymTable->at(rightSynonym)=="call")
						&& pkb->statementTable.getTNode(vals[j])->getNodeType()!=TNODE_NAMES[synToNodeType.at(synonymTable->at(rightSynonym))]){
						continue;
					}
					vector<int> newRow(tuple->getResultRow(i));
					newRow.push_back(vals[j]);
					result->addResultRow(newRow);
				}
			}
		} else if (lIndex == -1) { //case 3: only right is inside
			int index = result->addSynonym(leftSynonym);
			result->addSynonymToMap(leftSynonym, index);
			map<int, vector<int>> prevSolution = map<int, vector<int>>();
			for (size_t i = 0; i < tuple->getAllResults().size(); i++) {
				int rightValue = tuple->getResultAt(i, rIndex);
				if (prevSolution.find(rightValue) == prevSolution.end()){
					set<int> tV = pkb->usesTable.evaluateGetUsersStmt(rightValue);
					vector<int> tempValues(tV.begin(), tV.end()); 
					prevSolution.insert(make_pair(rightValue, tempValues));
				}
				vector<int> vals = prevSolution.at(rightValue);
				for (size_t j = 0; j < vals.size(); j++){
					if ((synonymTable->at(leftSynonym)=="assign" || synonymTable->at(leftSynonym)=="while" || synonymTable->at(leftSynonym)=="if" || synonymTable->at(leftSynonym)=="call")
						&& pkb->statementTable.getTNode(vals[j])->getNodeType()!=TNODE_NAMES[synToNodeType.at(synonymTable->at(leftSynonym))]){
						continue;
					}
					vector<int> newRow(tuple->getResultRow(i));
					newRow.push_back(vals[j]);
					result->addResultRow(newRow);
				}
			}
		}
		return result;
	}

	// BOOLEAN Result
	ResultTuple* solveOther() {
		ResultTuple* tuple = new ResultTuple();
		tuple->setBool(true);
		if(isSyn == 0) {	//(digit, digit)
			// invalid
		} else if (isSyn == 7) {	//(_, digit)
			// invalid
		} else if (isSyn == 8) {	//(digit, _)
			tuple->setEmpty(pkb->usesTable.evaluateGetUsedVarStmt(leftIndex).empty());
		} else {	//(_, _)
			// invalid
		}
		return tuple;
	}
};