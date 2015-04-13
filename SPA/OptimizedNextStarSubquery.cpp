#pragma once
#include <string>
#include <vector>
#include <map>
#include "Subquery.h"
#include "CacheTable.h"
#include "PKB\OptimizedCFG.h"

using namespace std;

class OptimizedNextStarSubquery : public Subquery {
public:
	OptimizedNextStarSubquery(map<string, string>* m, PKBController* p) : Subquery(m, p){
	
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
			if (s == "procedure" || s == "constant" || s == "variable") {
				return false;
			}
		}
		//left synonym
		if (isSyn == 2 || isSyn == 5 || isSyn == 3) {
			string s = synonymTable->at(leftSynonym);
			if (s == "procedure" || s == "constant" || s == "variable") {
				return false;
			}
		}
		return true;
	}

	void setPriority() {
		int magnitude = 50;	//calculated during profiling
		bool isLeftSynStmtOrProgLine = true;
		bool isRightSynStmtOrProgLine = true;
		switch (isSyn) {
			case 1: // (int, syn)
				isRightSynStmtOrProgLine = (synonymTable->at(rightSynonym) == "stmt" || synonymTable->at(rightSynonym) == "prog_line");
				if (isRightSynStmtOrProgLine){
					priority = pkb->statementTable->getAllStmtNum().size();
				} else {
					priority = (pkb->statementTable->getStmtNumUsingNodeType(TNODE_NAMES[synToNodeType.at(synonymTable->at(rightSynonym))])).size();
				}
				priority -= leftIndex;
				break;
			case 2: // (syn, int)
				isLeftSynStmtOrProgLine = (synonymTable->at(leftSynonym) == "stmt" || synonymTable->at(leftSynonym) == "prog_line");
				if (isLeftSynStmtOrProgLine){
					priority = pkb->statementTable->getAllStmtNum().size();
				} else {
					priority = (pkb->statementTable->getStmtNumUsingNodeType(TNODE_NAMES[synToNodeType.at(synonymTable->at(leftSynonym))])).size();
				}
				priority /= rightIndex;
				break;
			case 3: // (syn, syn)
				isLeftSynStmtOrProgLine = (synonymTable->at(leftSynonym) == "stmt" || synonymTable->at(leftSynonym) == "prog_line");
				isRightSynStmtOrProgLine = (synonymTable->at(rightSynonym) == "stmt" || synonymTable->at(rightSynonym) == "prog_line");
				if (isLeftSynStmtOrProgLine && isRightSynStmtOrProgLine){
					priority = pkb->statementTable->getAllStmtNum().size() * pkb->statementTable->getAllStmtNum().size();
				} else if (isLeftSynStmtOrProgLine){
					priority = pkb->statementTable->getAllStmtNum().size() * (pkb->statementTable->getStmtNumUsingNodeType(TNODE_NAMES[synToNodeType.at(synonymTable->at(rightSynonym))])).size();
				} else if (isRightSynStmtOrProgLine){
					priority = (pkb->statementTable->getStmtNumUsingNodeType(TNODE_NAMES[synToNodeType.at(synonymTable->at(leftSynonym))])).size() * pkb->statementTable->getAllStmtNum().size();
				} else {
					priority = (pkb->statementTable->getStmtNumUsingNodeType(TNODE_NAMES[synToNodeType.at(synonymTable->at(leftSynonym))])).size() * (pkb->statementTable->getStmtNumUsingNodeType(TNODE_NAMES[synToNodeType.at(synonymTable->at(rightSynonym))])).size();
				}
				break;
			case 4: // (_, syn)
				isRightSynStmtOrProgLine = (synonymTable->at(rightSynonym) == "stmt" || synonymTable->at(rightSynonym) == "prog_line");
				if (isRightSynStmtOrProgLine){
					priority = pkb->statementTable->getAllStmtNum().size();
				} else {
					priority = (pkb->statementTable->getStmtNumUsingNodeType(TNODE_NAMES[synToNodeType.at(synonymTable->at(rightSynonym))])).size();
				}
				break;
			case 5:	// (syn, _)
				isLeftSynStmtOrProgLine = (synonymTable->at(leftSynonym) == "stmt" || synonymTable->at(leftSynonym) == "prog_line");
				if (isLeftSynStmtOrProgLine){
					priority = pkb->statementTable->getAllStmtNum().size();
				} else {
					priority = (pkb->statementTable->getStmtNumUsingNodeType(TNODE_NAMES[synToNodeType.at(synonymTable->at(leftSynonym))])).size();
				}
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
		string type = synonymTable->at(leftSynonym);

		if (isSyn == 2) {	// NextStar(syn, stmt): Get Previous of stmt
			tempPrevious = cfg->getPrevStar(rightIndex);
			/*
			vector<int> stmts;
			if (type == "stmt" || type == "prog_line") {
				stmts = pkb->statementTable->getAllStmtNum();
			} else {
				stmts = pkb->statementTable->getStmtNumUsingNodeType(TNODE_NAMES[synToNodeType.at(type)]);
			}
			
			for (size_t i = 0; i < stmts.size(); i++) {
				if (tempPrevious.find(stmts[i]) != tempPrevious.end() && cfg->isNextStar(stmts[i], rightIndex)) {
					tempPrevious.insert(stmts[i]);
				}
			}
			*/
		} else {	// NextStar(syn, _): Get all Previous stmt
			// getAllPrevious Statements
			tempPrevious = cfg->getAllPrev();
		}

		vector<int> Previous(tempPrevious.begin(), tempPrevious.end());
		for(size_t i = 0; i < Previous.size(); i++) {
			vector<int> temp = vector<int>();
			// synonym type check here
			if ((type == "assign" || type == "while" || type == "if" || type == "call")
				&& pkb->statementTable->getTNode(Previous[i])->getNodeType() != TNODE_NAMES[synToNodeType.at(type)]){
				continue;
			}
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
			if (isSyn == 2) {	// NextStar(syn, stmt)
				if (cfg->isNextStar(temp.at(index), rightIndex)) {
					result->addResultRow(temp);
				}
			} else {	// NextStar(syn, _)
				if (!cfg->getNext(temp.at(index)).empty()) {
					result->addResultRow(temp);
				}
			}
		}
		return result;
	}

	ResultTuple* solveRightSyn() {
		ResultTuple* tuple = new ResultTuple();
		tuple->addSynonymToMap(rightSynonym, tuple->addSynonym(rightSynonym));
		string type = synonymTable->at(rightSynonym);
		set<int> tempNextStar;

		if (isSyn == 1) {	// NextStar(stmt, syn): Get NextStar of stmt
			tempNextStar = cfg->getNextStar(leftIndex);
			/*
			vector<int> stmts;
			if (type == "stmt" || type == "prog_line") {
				stmts = pkb->statementTable->getAllStmtNum();
			} else {
				stmts = pkb->statementTable->getStmtNumUsingNodeType(TNODE_NAMES[synToNodeType.at(type)]);
			}

			for (size_t i = 0; i < stmts.size(); i++) {
				if (tempNextStar.find(stmts[i]) != tempNextStar.end() && cfg->isNextStar(leftIndex, stmts[i])) {
					tempNextStar.insert(stmts[i]);
				}
			}
			*/
		} else {	// NextStar(_, syn): Get all NextStar stmt
			tempNextStar = cfg->getAllNext();
		}

		vector<int> NextStar(tempNextStar.begin(), tempNextStar.end());
		for(size_t i = 0; i < NextStar.size(); i++) {
			vector<int> temp = vector<int>();
			if ((type == "assign" || type == "while" || type == "if" || type == "call")
				&& pkb->statementTable->getTNode(NextStar[i])->getNodeType() != TNODE_NAMES[synToNodeType.at(type)]){
				continue;
			}
			temp.push_back(NextStar.at(i));
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
			if (isSyn == 1) {	// NextStar(stmt, syn)
				if (cfg->isNextStar(leftIndex, temp.at(index))) {
					result->addResultRow(temp);
				}
			} else {	// NextStar(_, syn)
				if (!cfg->getPrev(temp.at(index)).empty()) {
					result->addResultRow(temp);
				}
			}
		}
		return result;
	}

	ResultTuple* solveBothSyn() {
		ResultTuple* tuple = new ResultTuple();
		tuple->addSynonymToMap(leftSynonym, tuple->addSynonym(leftSynonym));
		tuple->addSynonymToMap(rightSynonym, tuple->addSynonym(rightSynonym));
		string left = synonymTable->at(leftSynonym), right = synonymTable->at(rightSynonym);

		// get all Previous statement
		// for each followee statement, get its NextStar
		map<int, vector<int>>* pcache = CacheTable::getNextStarCache();
		set<int> tempPrevious = cfg->getAllPrev();
		vector<int> Previous(tempPrevious.begin(), tempPrevious.end());

		for (size_t i = 0; i < Previous.size(); i++) {
			// synonym type check
			if ((left == "assign" || left == "while" || left == "if" || left == "call")
				&& pkb->statementTable->getTNode(Previous[i])->getNodeType()!=TNODE_NAMES[synToNodeType.at(left)]){
				continue;
			}
			
			/*
			//Check if cache contains solution to (x, previous[i])
			vector<int> NextStar;
			if (pcache != NULL && pcache->find(Previous[i]) != pcache->end()) {
				NextStar = pcache->at(Previous[i]);
			} else {
				if (pcache == NULL) {
					pcache = new map<int, vector<int>>();
				}
				set<int> tempNextStar = cfg->getNextStar(Previous[i]);
				NextStar = vector<int>(tempNextStar.begin(), tempNextStar.end());
				pcache->insert(map<int, vector<int>>::value_type(Previous[i], NextStar));
			}
			*/
			set<int> tempNextStar = cfg->getNextStar(Previous[i]);
			vector<int> NextStar = vector<int>(tempNextStar.begin(), tempNextStar.end());

			for (size_t j = 0; j < NextStar.size(); j++) {
				// synonym type check
				if ((right == "assign" || right =="while" || right =="if" || right == "call")
				&& pkb->statementTable->getTNode(NextStar[j])->getNodeType()!=TNODE_NAMES[synToNodeType.at(right)]){
					continue;
				}
				vector<int> row = vector<int>();
				row.push_back(Previous.at(i));
				row.push_back(NextStar.at(j));
				tuple->addResultRow(row);
			}
		}
		//CacheTable::updateNextStarCache(pcache);
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
				if (cfg->isNextStar(tuple->getAllResults()[i][lIndex], tuple->getAllResults()[i][rIndex])){
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
					set<int> tV = cfg->getNextStar(leftValue);
					vector<int> tempValues(tV.begin(), tV.end());
					prevSolution.insert(make_pair(leftValue, tempValues));
				}
				vector<int> vals = prevSolution.at(leftValue);
				for (size_t j = 0; j < vals.size(); j++){
					if ((synonymTable->at(rightSynonym)=="assign" || synonymTable->at(rightSynonym)=="while" || synonymTable->at(rightSynonym)=="if" || synonymTable->at(rightSynonym)=="call")
						&& pkb->statementTable->getTNode(vals[j])->getNodeType()!=TNODE_NAMES[synToNodeType.at(synonymTable->at(rightSynonym))]){
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
					set<int> tV = cfg->getPrevStar(rightValue);
					vector<int> tempValues(tV.begin(), tV.end());
					prevSolution.insert(make_pair(rightValue, tempValues));
				}
				vector<int> vals = prevSolution.at(rightValue);
				for (size_t j = 0; j < vals.size(); j++){
					if ((synonymTable->at(leftSynonym)=="assign" || synonymTable->at(leftSynonym)=="while" || synonymTable->at(leftSynonym)=="if" || synonymTable->at(leftSynonym)=="call")
						&& pkb->statementTable->getTNode(vals[j])->getNodeType()!=TNODE_NAMES[synToNodeType.at(synonymTable->at(leftSynonym))]){
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
			tuple->setEmpty(!cfg->isNextStar(leftIndex, rightIndex));
		} else if (isSyn == 7) {	//(_, digit)
			tuple->setEmpty(cfg->getPrev(rightIndex).empty());
		} else if (isSyn == 8) {	//(digit, _)
			tuple->setEmpty(cfg->getNext(leftIndex).empty());
		} else {	//(_, _)
			tuple->setEmpty(cfg->getAllNext().empty());
		}
		return tuple;
	}

  
};