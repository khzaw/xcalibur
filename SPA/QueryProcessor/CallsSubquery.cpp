#pragma once
#include <string>
#include <vector>
#include <map>
#include "Subquery.h"

using namespace std;

// CallsSubquery: Subquery for Calls relation
// To construct CallsSubquery:
// 1. CallsSubquery(map<string, string>* SynonymMap, PKBController* PKB) csubquery
// 2. csubquery.setSynonyms(leftSyn/Index, rightSyn/Index)
// Examples for setSynonyms():
// Calls(p1, p2)              |    csubquery.setSynonyms("p1", "p2")
// Calls("_", p2)             |    csubquery.setSynonyms("_", "p2")
// Calls("First", p2)         |    csubquery.setSynonyms(1, "p2")   // 1 is the index of procedure "First" in procTable

class CallsSubquery : public Subquery {
public:
	CallsSubquery(map<string, string>* m, PKBController* p) : Subquery(m, p){
	
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

	ResultTuple* solveLeftSyn() {
		ResultTuple* tuple = new ResultTuple();
		int index = tuple->addSynonym(leftSynonym);
		tuple->addSynonymToMap(leftSynonym, index);
		set<int> tempCallers;
		if (isSyn == 2) {	// Calls(syn, stmt): Get callers of stmt
			tempCallers = pkb->callsTable->evaluateGetCallers(rightIndex);
		} else {	// Calls(syn, _): Get all callers stmt
			tempCallers = pkb->callsTable->getAllCallers();
		}
		vector<int> callers(tempCallers.begin(), tempCallers.end());
		for(size_t i = 0; i < callers.size(); i++) {
			vector<int> temp = vector<int>();
			temp.push_back(callers.at(i));
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
			if (isSyn == 2) {	// Calls(syn, stmt)
				if (pkb->callsTable->isCalls(temp.at(index), rightIndex)) {
					result->addResultRow(temp);
				}
			} else {	// Calls(syn, _)
				if (!pkb->callsTable->evaluateGetCallees(temp.at(index)).empty()) {
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
		
		set<int> tempCallees;
		if (isSyn == 1) {	// Calls(stmt, syn): Get callees of stmt
			tempCallees = pkb->callsTable->evaluateGetCallees(leftIndex);
		} else {	// Calls(_, syn): Get all callees stmt
			tempCallees = pkb->callsTable->getAllCallees();
		}
		vector<int> callees(tempCallees.begin(), tempCallees.end());
		for(size_t i = 0; i < callees.size(); i++) {
			vector<int> temp = vector<int>();
			temp.push_back(callees.at(i));
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
			if (isSyn == 1) {	// Calls(stmt, syn)
				if (pkb->callsTable->isCalls(leftIndex, temp.at(index))) {
					result->addResultRow(temp);
				}
			} else {	// Calls(_, syn)
				if (!pkb->callsTable->evaluateGetCallers(temp.at(index)).empty()) {
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

		// get all callers statement
		// for each caller statement, get its callees
		set<int> tempCallers = pkb->callsTable->getAllCallers();
		vector<int> callers(tempCallers.begin(), tempCallers.end());
		for (size_t i = 0; i < callers.size(); i++) {
			set<int> tempCallees = pkb->callsTable->evaluateGetCallees(callers[i]);
			vector<int> callees(tempCallees.begin(), tempCallees.end());
			for (size_t j = 0; j < callees.size(); j++) {
				vector<int> row = vector<int>();
				row.push_back(callers.at(i));
				row.push_back(callees.at(j));
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
				if (pkb->callsTable->isCalls(tuple->getAllResults()[i][lIndex], tuple->getAllResults()[i][rIndex])){
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
					set<int> tV = pkb->callsTable->evaluateGetCallees(leftValue);
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
					set<int> tV = pkb->callsTable->evaluateGetCallers(rightValue);
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
				tuple->setEmpty(!pkb->callsTable->isCalls(leftIndex, rightIndex));
			} else {
				tuple->setEmpty(true);
			}
		} else if (isSyn == 7) {	//(_, digit)
			tuple->setEmpty(pkb->callsTable->evaluateGetCallers(rightIndex).empty());
		} else if (isSyn == 8) {	//(digit, _)
			tuple->setEmpty(pkb->callsTable->evaluateGetCallees(leftIndex).empty());
		} else {	//(_, _)
			tuple->setEmpty(pkb->callsTable->getAllCallees().empty());
		}
		return tuple;
	}
};