#pragma once
#include <string>
#include <vector>
#include <map>
#include "Subquery.h"

using namespace std;

class CallsStarSubquery : public Subquery {
public:
	CallsStarSubquery(map<string, string>* m, PKBController* p) : Subquery(m, p){
	
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
	
	bool validate() {
		//right synonym
		if(isSyn == 1 || isSyn == 4 || isSyn == 3) {
			string s = synonymTable->at(rightSynonym);
			if (s != "procedure") {
				return false;
			}
		}
		//left synonym
		if (isSyn == 2 || isSyn == 5 || isSyn == 3) {
			string s = synonymTable->at(leftSynonym);
			if (s != "procedure") {
				return false;
			}
		}
		return true;
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

	void setPriority() {
		switch (isSyn) {
			case 1: // (int, syn)
				priority = pkb->callsTable->evaluateGetCalleesStar(leftIndex).size();
				break;
			case 2: // (syn, int)
				priority = pkb->callsTable->evaluateGetCallersStar(rightIndex).size();
				break;
			case 3: // (syn, syn)
				priority = pkb->callsTable->getStarSize();
				break;
			case 4: // (_, syn)
				priority = pkb->callsTable->getSize();
				break;
			case 5:	// (syn, _)
				priority =  pkb->statementTable->getNodesMatchingNodeType("CALL_NODE").size();
				break;
			default: 
				priority = 0;
				break;
		}
	}

	ResultTuple* solveLeftSyn() {
		ResultTuple* tuple = new ResultTuple();
		int index = tuple->addSynonym(leftSynonym);
		tuple->addSynonymToMap(leftSynonym, index);
		set<int> tempCallersStar;
		if (isSyn == 2) {	// Calls*(syn, stmt): Get callersStar of stmt
			tempCallersStar = pkb->callsTable->evaluateGetCallersStar(rightIndex);
		} else {	// Calls*(syn, _): Get all callers stmt
			tempCallersStar = pkb->callsTable->getAllCallers();
		}
		vector<int> callersStar(tempCallersStar.begin(), tempCallersStar.end());
		for(size_t i = 0; i < callersStar.size(); i++) {
			vector<int> temp = vector<int>();
			temp.push_back(callersStar.at(i));
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
			if (isSyn == 2) {	// Calls*(syn, stmt)
				if (pkb->callsTable->isCallsStar(temp.at(index), rightIndex)) {
					result->addResultRow(temp);
				}
			} else {	// Calls*(syn, _)
				if (!pkb->callsTable->evaluateGetCalleesStar(temp.at(index)).empty()) {
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
		
		set<int> tempCalleesStar;
		if (isSyn == 1) {	// Calls*(stmt, syn): Get calleesStar of stmt
			tempCalleesStar = pkb->callsTable->evaluateGetCalleesStar(leftIndex);
		} else {	// Calls*(_, syn): Get all callees stmt
			tempCalleesStar = pkb->callsTable->getAllCallees();
		}
		vector<int> calleesStar(tempCalleesStar.begin(), tempCalleesStar.end());
		for(size_t i = 0; i < calleesStar.size(); i++) {
			vector<int> temp = vector<int>();
			temp.push_back(calleesStar.at(i));
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
			if (isSyn == 1) {	// Calls*(stmt, syn)
				if (pkb->callsTable->isCallsStar(leftIndex, temp.at(index))) {
					result->addResultRow(temp);
				}
			} else {	// Calls*(_, syn)
				if (!pkb->callsTable->evaluateGetCallersStar(temp.at(index)).empty()) {
					result->addResultRow(temp);
				}
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

		// get all callersStar statement
		// for each caller statement, get its callees
		set<int> tempCallersStar = pkb->callsTable->getAllCallers();
		vector<int> callersStar(tempCallersStar.begin(), tempCallersStar.end());
		for (size_t i = 0; i < callersStar.size(); i++) {
			set<int> tempCalleesStar = pkb->callsTable->evaluateGetCalleesStar(callersStar[i]);
			vector<int> calleesStar(tempCalleesStar.begin(), tempCalleesStar.end());
			for (size_t j = 0; j < calleesStar.size(); j++) {
				vector<int> row = vector<int>();
				row.push_back(callersStar.at(i));
				row.push_back(calleesStar.at(j));
				tuple->addResultRow(row);
			}
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
				if (pkb->callsTable->isCallsStar(tuple->getAllResults()[i][lIndex], tuple->getAllResults()[i][rIndex])){
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
					set<int> tV = pkb->callsTable->evaluateGetCalleesStar(leftValue);
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
					set<int> tV = pkb->callsTable->evaluateGetCallersStar(rightValue);
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
			if (0 <= leftIndex && leftIndex < pkb->procTable->getSize() && 0 <= rightIndex && rightIndex < pkb->procTable->getSize()){
				tuple->setEmpty(!pkb->callsTable->isCallsStar(leftIndex, rightIndex));
			} else {
				tuple->setEmpty(true);
			}
		} else if (isSyn == 7) {	//(_, digit)
			tuple->setEmpty(pkb->callsTable->evaluateGetCallersStar(rightIndex).empty());
		} else if (isSyn == 8) {	//(digit, _)
			tuple->setEmpty(pkb->callsTable->evaluateGetCalleesStar(leftIndex).empty());
		} else {	//(_, _)
			tuple->setEmpty(pkb->callsTable->getAllCallees().empty());
		}
		return tuple;
	}
};