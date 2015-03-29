#pragma once
#include <string>
#include <vector>
#include <map>
#include "Subquery.h"

using namespace std;

class FollowsStarSubquery : public Subquery{
public:
	FollowsStarSubquery(map<string, string>* m, PKBController* p) : Subquery(m, p){
	
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
		switch (isSyn) {
			case 1: // (int, syn)
				priority = pkb->statementTable->getSize() - leftIndex;
				break;
			case 2: // (syn, int)
				priority = rightIndex;
				break;
			case 3: { // (syn, syn)
				// or calculate using synonym types?
				int a = pkb->followsTable->getAllFolloweeStmt().size();
				int b = pkb->followsTable->getAllFollowerStmt().size();
				priority = a * b;
					}
				break;
			case 4: // (_, syn)
				priority = pkb->followsTable->getAllFollowerStmt().size();
				break;
			case 5:	// (syn, _)
				priority = pkb->followsTable->getAllFolloweeStmt().size();
				break;
			default: 
				priority = 0;
				break;
		}
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
		set<int> tempFollowees;
		if (isSyn == 2) {	// Follows(syn, stmt): Get followees of stmt
			tempFollowees = pkb->followsTable->evaluateGetFolloweeStar(rightIndex);
		} else {	// Follows(syn, _): Get all followees stmt
			tempFollowees = pkb->followsTable->getAllFolloweeStmt();
		}
		vector<int> followees(tempFollowees.begin(), tempFollowees.end());
		for(size_t i = 0; i < followees.size(); i++) {
			vector<int> temp = vector<int>();
			// synonym type check here
			if ((synonymTable->at(leftSynonym)=="assign" || synonymTable->at(leftSynonym)=="while" || synonymTable->at(leftSynonym)=="if" || synonymTable->at(leftSynonym)=="call")
				&& pkb->statementTable->getTNode(followees[i])->getNodeType()!=TNODE_NAMES[synToNodeType.at(synonymTable->at(leftSynonym))]){
				continue;
			}
			temp.push_back(followees.at(i));
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
			if (isSyn == 2) {	// Follows(syn, stmt)
				if (pkb->followsTable->evaluateIsFollowsStar(temp.at(index), rightIndex)) {
					result->addResultRow(temp);
				}
			} else {	// Follows(syn, _)
				if (!pkb->followsTable->evaluateGetFollowerStar(temp.at(index)).empty()) {
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
		
		set<int> tempFollowers;
		if (isSyn == 1) {	// Follows(stmt, syn): Get followers of stmt
			tempFollowers = pkb->followsTable->evaluateGetFollowerStar(leftIndex);
		} else {	// Follows(_, syn): Get all followers stmt
			tempFollowers = pkb->followsTable->getAllFollowerStmt();
		}
		vector<int> followers(tempFollowers.begin(), tempFollowers.end());
		for(size_t i = 0; i < followers.size(); i++) {
			vector<int> temp = vector<int>();
			// synonym type check here
			if ((synonymTable->at(rightSynonym)=="assign" || synonymTable->at(rightSynonym)=="while" || synonymTable->at(rightSynonym)=="if" || synonymTable->at(rightSynonym)=="call")
				&& pkb->statementTable->getTNode(followers[i])->getNodeType()!=TNODE_NAMES[synToNodeType.at(synonymTable->at(rightSynonym))]){
				continue;
			}
			temp.push_back(followers.at(i));
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
			if (isSyn == 1) {	// Follows(stmt, syn)
				if (pkb->followsTable->evaluateIsFollowsStar(leftIndex, temp.at(index))) {
					result->addResultRow(temp);
				}
			} else {	// Follows(_, syn)
				if (!pkb->followsTable->evaluateGetFolloweeStar(temp.at(index)).empty()) {
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

		// get all followees statement
		// for each followee statement, get its followers
		set<int> tempFollowees = pkb->followsTable->getAllFolloweeStmt();
		vector<int> followees(tempFollowees.begin(), tempFollowees.end());
		for (size_t i = 0; i < followees.size(); i++) {
			// synonym type check
			if ((synonymTable->at(leftSynonym)=="assign" || synonymTable->at(leftSynonym)=="while" || synonymTable->at(leftSynonym)=="if" || synonymTable->at(leftSynonym)=="call")
				&& pkb->statementTable->getTNode(followees[i])->getNodeType()!=TNODE_NAMES[synToNodeType.at(synonymTable->at(leftSynonym))]){
				continue;
			}
			set<int> tempFollowers = pkb->followsTable->evaluateGetFollowerStar(followees[i]);
			vector<int> followers(tempFollowers.begin(), tempFollowers.end()); 
			for (size_t j = 0; j < followers.size(); j++) {
				// synonym type check
				if ((synonymTable->at(rightSynonym)=="assign" || synonymTable->at(rightSynonym)=="while" || synonymTable->at(rightSynonym)=="if" || synonymTable->at(rightSynonym)=="call")
				&& pkb->statementTable->getTNode(followers[j])->getNodeType()!=TNODE_NAMES[synToNodeType.at(synonymTable->at(rightSynonym))]){
					continue;
				}
				vector<int> row = vector<int>();
				row.push_back(followees.at(i));
				row.push_back(followers.at(j));
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
				if (pkb->followsTable->evaluateIsFollowsStar(tuple->getAllResults()[i][lIndex], tuple->getAllResults()[i][rIndex])){
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
					set<int> tV = pkb->followsTable->evaluateGetFollowerStar(leftValue);
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
					set<int> tV = pkb->followsTable->evaluateGetFolloweeStar(rightValue);
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
			tuple->setEmpty(!pkb->followsTable->evaluateIsFollowsStar(leftIndex, rightIndex));
		} else if (isSyn == 7) {	//(_, digit)
			tuple->setEmpty(pkb->followsTable->evaluateGetFolloweeStar(rightIndex).empty());
		} else if (isSyn == 8) {	//(digit, _)
			tuple->setEmpty(pkb->followsTable->evaluateGetFollowerStar(leftIndex).empty());
		} else {	//(_, _)
			tuple->setEmpty(pkb->followsTable->getAllFollowerStmt().empty());
		}
		return tuple;
	}
};