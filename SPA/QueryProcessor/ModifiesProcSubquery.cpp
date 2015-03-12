#pragma once
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include "Subquery.h"

using namespace std;

class ModifiesProcSubquery : public Subquery{
public:
	ModifiesProcSubquery(map<string, string>* m, PKBController* p) : Subquery(m, p){
	
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
			if (s != "variable") {
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
		vector<int> modifiers = vector<int>();
		if (isSyn == 2) {	// Modifies(syn, varnum): Get syns that modifies varnum
			set<int> tempModifiers = pkb->modifiesTable.evaluateGetModifiersProc(rightIndex);
			copy(tempModifiers.begin(), tempModifiers.end(), back_inserter(modifiers)); 
		} else {	// Modifies(syn, _): Get all modifiers
			// not sure if this is correct // it's not!
			/*
			vector<pair<int, int>> temp = pkb->modifiesTable.getModifiesProc();
			for (size_t i = 0; i < temp.size(); i++) {
				modifiers.push_back(temp[i].first);
			}
			*/
			// traverse through procTable, check for those that modifies a variable
			for (int i = 0; i < pkb->procTable.getSize(); i++){
				if (pkb->modifiesTable.evaluateGetModifiedVarProc(i).size() > (size_t)0){
					modifiers.push_back(i);
				}
			}
		}

		for(size_t i = 0; i < modifiers.size(); i++) {
			vector<int> temp = vector<int>();
			temp.push_back(modifiers.at(i));
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
			if (isSyn == 2) {	// Modifies(syn, varnum)
				if (pkb->modifiesTable.evaluateIsModifiesProc(temp.at(index), rightIndex)) {
					result->addResultRow(temp);
				}
			} else {	// Modifies(syn, _)
				if (!pkb->modifiesTable.evaluateGetModifiedVarProc(temp.at(index)).empty()) {
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
		
		vector<int> modified;
		if (isSyn == 1) {	// Modifies(proc, varnum): Get Modified var by proc
			set<int> tempModified = pkb->modifiesTable.evaluateGetModifiedVarProc(leftIndex);
			copy(tempModified.begin(), tempModified.end(), back_inserter(modified));
		} else {	// Modifies(_, varnum)
			//invalid
		}

		for(size_t i = 0; i < modified.size(); i++) {
			vector<int> temp = vector<int>();
			temp.push_back(modified.at(i));
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
			if (isSyn == 1) {	// Modifies(stmt, syn)
				if (pkb->modifiesTable.evaluateIsModifiesProc(leftIndex, temp.at(index))) {
					result->addResultRow(temp);
				}
			} else {	// Modifies(_, syn)
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

		// get all modifiers statement
		// for each modifiers statement, get its modified var
		vector<pair<int, int>> procs = pkb->modifiesTable.getModifiesProc();
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
				if (pkb->modifiesTable.evaluateIsModifiesProc(tuple->getAllResults()[i][lIndex], tuple->getAllResults()[i][rIndex])){
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
					set<int> tV = pkb->modifiesTable.evaluateGetModifiedVarProc(leftValue);
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
					set<int> tV = pkb->modifiesTable.evaluateGetModifiersProc(rightValue);
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
			tuple->setEmpty(!pkb->modifiesTable.evaluateIsModifiesProc(leftIndex, rightIndex));
		} else if (isSyn == 7) {	//(_, digit)
			// invalid
		} else if (isSyn == 8) {	//(digit, _)
			tuple->setEmpty(pkb->modifiesTable.evaluateGetModifiedVarProc(leftIndex).empty());
		} else {	//(_, _)
			// invalid
		}
		return tuple;
	}
};