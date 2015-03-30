#pragma once
#include <string>
#include <vector>
#include <map>
#include "Subquery.h"

using namespace std;
// TODO: 77, 119, 236?
class AffectsSubquery : public Subquery {
public:
	AffectsSubquery(map<string, string>* m, PKBController* p) : Subquery(m, p){
	
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
			if (!(s == "assign" || s == "stmt" || s == "prog_line")) {
				return false;
			}
		}
		//left synonym
		if (isSyn == 2 || isSyn == 5 || isSyn == 3) {
			string s = synonymTable->at(leftSynonym);
			if (!(s == "assign" || s == "stmt" || s == "prog_line")) {
				return false;
			}
		}
		return true;
	}

	void setPriority() {
		int magnitude = 20;	//calculated during profiling
		bool isLeftSynStmtOrProgLine = true;
		bool isRightSynStmtOrProgLine = true;
		switch (isSyn) {
			case 1: // (int, syn)
				priority = (pkb->statementTable->getStmtNumUsingNodeType("ASSIGN_NODE")).size();
				break;
			case 2: // (syn, int)
				priority = (pkb->statementTable->getStmtNumUsingNodeType("ASSIGN_NODE")).size();
				break;
			case 3: // (syn, syn)
				priority = (pkb->statementTable->getStmtNumUsingNodeType("ASSIGN_NODE")).size() * (pkb->statementTable->getStmtNumUsingNodeType("ASSIGN_NODE")).size();
				break;
			case 4: // (_, syn)
				priority = (pkb->statementTable->getStmtNumUsingNodeType("ASSIGN_NODE")).size();
				break;
			case 5:	// (syn, _)
				priority = (pkb->statementTable->getStmtNumUsingNodeType("ASSIGN_NODE")).size();
				break;
			default: 
				priority = 0;
				break;
		}

		priority *= magnitude;
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
		set<int> tempPrevious;
		if (isSyn == 2) {	// Affects(syn, stmt): Get Previous of stmt
			tempPrevious = pkb->affectsExtractor->getAffectsBy(rightIndex);
		} else {	// Affects(syn, _): Get all Previous stmt
			// getAllPrevious Statements
			tempPrevious = set<int>();
			vector<int> assStmt = pkb->statementTable->getStmtNumUsingNodeType("ASSIGN_NODE");
			for (size_t i = 0; i < assStmt.size(); i++) {
				for (size_t j = 0; j < assStmt.size(); j++) {
					if (pkb->affectsExtractor->isAffects(assStmt[i], assStmt[j])) {
						tempPrevious.insert(assStmt[i]);
					}
				}
			}
			//tempPrevious = pkb->nextExtractor->getAllPrev();
		}
		vector<int> Previous(tempPrevious.begin(), tempPrevious.end());
		for(size_t i = 0; i < Previous.size(); i++) {
			vector<int> temp = vector<int>();
			
			temp.push_back(Previous.at(i));
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
			if (isSyn == 2) {	// Affects(syn, stmt)
				if (pkb->affectsExtractor->isAffects(temp.at(index), rightIndex)) {
					result->addResultRow(temp);
				}
			} else {	// Affects(syn, _)
				if (!pkb->affectsExtractor->getAffects(temp.at(index)).empty()) {
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
		
		set<int> tempNext;
		if (isSyn == 1) {	// Affects(stmt, syn): Get Affects of stmt
			tempNext = pkb->affectsExtractor->getAffects(leftIndex);
		} else {	// Affects(_, syn): Get all Affected stmt
			tempNext = set<int>();
			vector<int> assStmt = pkb->statementTable->getStmtNumUsingNodeType("ASSIGN_NODE");
			for (size_t i = 0; i < assStmt.size(); i++) {
				for (size_t j = 0; j < assStmt.size(); j++) {
					if (pkb->affectsExtractor->isAffects(assStmt[i], assStmt[j])) {
						tempNext.insert(assStmt[j]);
					}
				}
			}
			//tempNext = pkb->nextExtractor->getAllNext();
		}
		vector<int> Next(tempNext.begin(), tempNext.end());
		for(size_t i = 0; i < Next.size(); i++) {
			vector<int> temp = vector<int>();
			temp.push_back(Next.at(i));
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
			if (isSyn == 1) {	// Affects(stmt, syn)
				if (pkb->affectsExtractor->isAffects(leftIndex, temp.at(index))) {
					result->addResultRow(temp);
				}
			} else {	// Affects(_, syn)
				if (!pkb->affectsExtractor->getAffectsBy(temp.at(index)).empty()) {
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

		vector<int> previous = pkb->statementTable->getStmtNumUsingNodeType("ASSIGN_NODE");
		for (size_t i = 0; i < previous.size(); i++) {
			for (size_t j = 0; j < previous.size(); j++) {
				if (pkb->affectsExtractor->isAffects(previous[i], previous[j])) {
					vector<int> row = vector<int>();
					row.push_back(previous.at(i));
					row.push_back(previous.at(j));
					tuple->addResultRow(row);
				}
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
				if (pkb->affectsExtractor->isAffects(tuple->getAllResults()[i][lIndex], tuple->getAllResults()[i][rIndex])){
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
					set<int> tV = pkb->affectsExtractor->getAffects(leftValue);
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
					set<int> tV = pkb->affectsExtractor->getAffectsBy(rightValue);
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
			tuple->setEmpty(!pkb->affectsExtractor->isAffects(leftIndex, rightIndex));
		} else if (isSyn == 7) {	//(_, digit)
			tuple->setEmpty(pkb->affectsExtractor->getAffectsBy(rightIndex).empty());
		} else if (isSyn == 8) {	//(digit, _)
			tuple->setEmpty(pkb->affectsExtractor->getAffects(leftIndex).empty());
		} else {	//(_, _)
			vector<int> assStmt = pkb->statementTable->getStmtNumUsingNodeType("ASSIGN_NODE");
			for (size_t i = 0; i < assStmt.size(); i++) {
				for (size_t j = 0; j < assStmt.size(); j++) {
					if (pkb->affectsExtractor->isAffects(assStmt[i], assStmt[j])) {
						tuple->setEmpty(false);
						return tuple;
					}
				}
			}
			tuple->setEmpty(true);
		}
		return tuple;
	}
};