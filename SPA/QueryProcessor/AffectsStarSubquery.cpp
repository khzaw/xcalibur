#pragma once
#include <string>
#include <vector>
#include <map>
#include "Subquery.h"

using namespace std;
// TODO: 77, 119, 236?
class AffectsStarSubquery : public Subquery {
public:
	AffectsStarSubquery(map<string, string>* m, PKBController* p) : Subquery(m, p){
	
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
		int magnitude = 50;	//calculated during profiling
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
				priority = 1;
				break;
		}

		priority *= magnitude;
	}

	ResultTuple* solveLeftSyn() {
		ResultTuple* tuple = new ResultTuple();
		int index = tuple->addSynonym(leftSynonym);
		tuple->addSynonymToMap(leftSynonym, index);
		vector<int> previous = vector<int>();
		vector<int> assStmt = pkb->statementTable->getStmtNumUsingNodeType("ASSIGN_NODE");
		set<int> tempPrevious = set<int>();
		if (isSyn == 2) {	// AffectsStar(syn, stmt): Get Previous of stmt
			for (size_t i = 0; i < assStmt.size(); i++) {
				if (pkb->affectsExtractor->isAffectsStar(assStmt[i], rightIndex)) {
					tempPrevious.insert(assStmt[i]);
				} 
			}
		} else {	// Affects(syn, _): Get all Previous stmt
			for (size_t i = 0; i < assStmt.size(); i++) {
				for (size_t j = 0; j < assStmt.size(); j++) {
					if (pkb->affectsExtractor->isAffectsStar(assStmt[i], assStmt[j])) {
						tempPrevious.insert(assStmt[i]);
					}
				}
			}
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
			if (isSyn == 2) {	// AffectsStar(syn, stmt)
				if (pkb->affectsExtractor->isAffectsStar(temp.at(index), rightIndex)) {
					result->addResultRow(temp);
				}
			} else {	// AffectsStar(syn, _)
				if (!pkb->affectsExtractor->getAffectsStar(temp.at(index)).empty()) {
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
		if (isSyn == 1) {	// AffectsStar(stmt, syn): Get AffectsStar of stmt
			tempNext = pkb->affectsExtractor->getAffectsStar(leftIndex);
		} else {	// AffectsStar(_, syn): Get all Affected stmt
			tempNext = set<int>();
			vector<int> assStmt = pkb->statementTable->getStmtNumUsingNodeType("ASSIGN_NODE");
			for (size_t i = 0; i < assStmt.size(); i++) {
				for (size_t j = 0; j < assStmt.size(); j++) {
					if (pkb->affectsExtractor->isAffectsStar(assStmt[i], assStmt[j])) {
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
			if (isSyn == 1) {	// AffectsStar(stmt, syn)
				if (pkb->affectsExtractor->isAffectsStar(leftIndex, temp.at(index))) {
					result->addResultRow(temp);
				}
			} else {	// AffectsStar(_, syn)
				if (!pkb->affectsExtractor->getAffectsStarBy(temp.at(index)).empty()) {
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
			set<int> tempAffectsStar = pkb->affectsExtractor->getAffectsStar(previous[i]);
			vector<int> AffectsStar(tempAffectsStar.begin(), tempAffectsStar.end());
			for (size_t j = 0; j < AffectsStar.size(); j++) {
				vector<int> row = vector<int>();
				row.push_back(previous.at(i));
				row.push_back(AffectsStar.at(j));
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
				if (pkb->affectsExtractor->isAffectsStar(tuple->getAllResults()[i][lIndex], tuple->getAllResults()[i][rIndex])){
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
					set<int> tV = pkb->affectsExtractor->getAffectsStar(leftValue);
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
					set<int> tV = pkb->affectsExtractor->getAffectsStarBy(rightValue);
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
			tuple->setEmpty(!pkb->affectsExtractor->isAffectsStar(leftIndex, rightIndex));
		} else if (isSyn == 7) {	//(_, digit)
			tuple->setEmpty(pkb->affectsExtractor->getAffectsStarBy(rightIndex).empty());
		} else if (isSyn == 8) {	//(digit, _)
			tuple->setEmpty(pkb->affectsExtractor->getAffectsStar(leftIndex).empty());
		} else {	//(_, _)
			vector<int> assStmt = pkb->statementTable->getStmtNumUsingNodeType("ASSIGN_NODE");
			for (size_t i = 0; i < assStmt.size(); i++) {
				for (size_t j = 0; j < assStmt.size(); j++) {
					if (pkb->affectsExtractor->isAffectsStar(assStmt[i], assStmt[j])) {
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