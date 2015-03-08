#pragma once
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include "Subquery.h"

using namespace std;

class UsesProcSubquery : public Subquery{
public:
	UsesProcSubquery(map<string, string>* m, PKBController* p) : Subquery(m, p){
	
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
			set<int> tempUsers = pkb->usesTable.getUsersProc(rightIndex);
			copy(tempUsers.begin(), tempUsers.end(), back_inserter(users)); 
		} else {	// Uses(syn, _): Get all users
			// not sure if this is correct
			vector<pair<int, int>> temp = pkb->usesTable.getUsesProc();
			for (size_t i = 0; i < temp.size(); i++) {
				users.push_back(temp[i].first);
			}
		}

		for(size_t i = 0; i < users.size(); i++) {
			vector<int> temp = vector<int>();
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
				if (pkb->usesTable.isUsesProc(temp.at(index), rightIndex)) {
					result->addResultRow(temp);
				}
			} else {	// Uses(syn, _)
				if (!pkb->usesTable.getUsedVarProc(temp.at(index)).empty()) {
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
		if (isSyn == 1) {	// Uses(proc, varnum): Get Users of varnum
			set<int> tempUsed = pkb->usesTable.getUsersProc(leftIndex);
			copy(tempUsed.begin(), tempUsed.end(), back_inserter(used));
		} else {	// Uses(_, varnum)
			//invalid
		}

		for(size_t i = 0; i < used.size(); i++) {
			vector<int> temp = vector<int>();
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
				if (pkb->usesTable.isUsesProc(leftIndex, temp.at(index))) {
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
		vector<pair<int, int>> procs = pkb->usesTable.getUsesProc();
		for (size_t i = 0; i < procs.size(); i++) {
			vector<int> row = vector<int>();
			row.push_back(procs[i].first);
			row.push_back(procs[i].second);
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
				if (pkb->usesTable.isUsesProc(tuple->getAllResults()[i][lIndex], tuple->getAllResults()[i][rIndex])){
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
					set<int> tV = pkb->usesTable.getUsedVarProc(leftValue);
					vector<int> tempValues(tV.begin(), tV.end());
					prevSolution.insert(make_pair(leftValue, tempValues));
				}
				vector<int> vals = prevSolution.at(leftValue);
				for (size_t j = 0; j < vals.size(); j++){
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
					set<int> tV = pkb->usesTable.getUsersProc(rightValue);
					vector<int> tempValues(tV.begin(), tV.end());
					prevSolution.insert(make_pair(rightValue, tempValues));
				}
				vector<int> vals = prevSolution.at(rightValue);
				for (size_t j = 0; j < vals.size(); j++){
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
			tuple->setEmpty(pkb->usesTable.getUsedVarProc(leftIndex).empty());
		} else {	//(_, _)
			// invalid
		}
		return tuple;
	}
};