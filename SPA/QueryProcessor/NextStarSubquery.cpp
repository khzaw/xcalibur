#pragma once
#include <string>
#include <vector>
#include <map>
#include "Subquery.h"
#include "CacheTable.h"

using namespace std;

class NextStarSubquery : public Subquery {
public:
	bool isConcurrent;
	NextStarSubquery(map<string, string>* m, PKBController* p) : Subquery(m, p){
	
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

		type = 1;
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
		vector<int> Previous;
		
		if (isSyn == 2) {	// NextStar(syn, stmt): Get Previous of stmt
			if (!isConcurrent) {
				tempPrevious = pkb->optimizedCFG->getPrevStar(rightIndex);
				//tempPrevious = pkb->optimizedCFG->getPrevStar(rightIndex);
				Previous.assign(tempPrevious.begin(), tempPrevious.end());
			} else {
				if (CacheTable::instance()->previousStarCache.find(rightIndex) != CacheTable::instance()->previousStarCache.end()) {
					Previous = CacheTable::instance()->previousStarCache.at(rightIndex);
				} else {
					tempPrevious = pkb->optimizedCFG->getPrevStar(rightIndex);
					//tempPrevious = pkb->optimizedCFG->getPrevStar(rightIndex);
					Previous.assign(tempPrevious.begin(), tempPrevious.end());
					CacheTable::instance()->previousStarCache.insert(map<int, vector<int>>::value_type(rightIndex, Previous));
				}
			}
		} else {	// NextStar(syn, _): Get all Previous stmt
			// getAllPrevious Statements
			tempPrevious = pkb->optimizedCFG->getAllPrev();
			Previous.assign(tempPrevious.begin(), tempPrevious.end());
		}

		pair<int, int> p = pair<int, int>();
		p.second = rightIndex;
		for(size_t i = 0; i < Previous.size(); i++) {
			if (isConcurrent && isSyn == 2) {
				p.first = Previous[i];
				CacheTable::instance()->isNextStarCache[p] = true;
			}
			
			vector<int> temp = vector<int>();
			
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
		pair<int, int> p = pair<int, int>();
		p.second = rightIndex;

		int index = tuple->getSynonymIndex(leftSynonym);
		for (size_t i = 0; i < tuple->getAllResults().size(); i++) {
			vector<int> temp = tuple->getAllResults().at(i);
			if (isSyn == 2) {	// NextStar(syn, stmt)
				p.first = temp.at(index);

				if (isConcurrent) {
					try {
						if (CacheTable::instance()->isNextStarCache.at(p)) {
							result->addResultRow(temp);
						}
					} catch (exception& e) {
						if (pkb->optimizedCFG->isNextStar(temp.at(index), rightIndex)) {
						//if (pkb->optimizedCFG->isNextStar(temp.at(index), rightIndex)) {
							result->addResultRow(temp);
							CacheTable::instance()->isNextStarCache[p] = true;
						} else {
							CacheTable::instance()->isNextStarCache[p] = false;
						}
					}

				} else if (pkb->optimizedCFG->isNextStar(temp.at(index), rightIndex)) {
				//} else if (pkb->optimizedCFG->isNextStar(temp.at(index), rightIndex)) {
					result->addResultRow(temp);
				}

			} else {	// NextStar(syn, _)
				if (!pkb->optimizedCFG->getNext(temp.at(index)).empty()) {
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
		vector<int> NextStar;

		if (isSyn == 1) {	// NextStar(stmt, syn): Get NextStar of stmt
			if (!isConcurrent) {
				tempNextStar = pkb->optimizedCFG->getNextStar(leftIndex);
				//tempNextStar = pkb->optimizedCFG->getNextStar(leftIndex);
				NextStar.assign(tempNextStar.begin(), tempNextStar.end());
			} else {
				if (CacheTable::instance()->nextStarCache.find(leftIndex) != CacheTable::instance()->nextStarCache.end()) {
					NextStar = CacheTable::instance()->nextStarCache.at(leftIndex);
				} else {
					tempNextStar = pkb->optimizedCFG->getNextStar(leftIndex);
					//tempNextStar = pkb->optimizedCFG->getNextStar(leftIndex);
					NextStar.assign(tempNextStar.begin(), tempNextStar.end());
					CacheTable::instance()->nextStarCache.insert(map<int, vector<int>>::value_type(leftIndex, NextStar));
				}
			}
		} else {	// NextStar(_, syn): Get all NextStar stmt
			tempNextStar = pkb->optimizedCFG->getAllNext();
			NextStar.assign(tempNextStar.begin(), tempNextStar.end());
		}

		pair<int, int> p = pair<int, int>();
		p.first = leftIndex;
		for(size_t i = 0; i < NextStar.size(); i++) {
			if (isConcurrent && isSyn == 1) {
				p.second = NextStar[i];
				CacheTable::instance()->isNextStarCache[p] = true;
			}
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
		pair<int, int> p = pair<int, int>();
		p.first = leftIndex;

		int index = tuple->getSynonymIndex(rightSynonym);
		for (size_t i = 0; i < tuple->getAllResults().size(); i++) {
			vector<int> temp = tuple->getAllResults().at(i);
			if (isSyn == 1) {	// NextStar(stmt, syn)
				 p.second = temp.at(index);

				if (isConcurrent) {
					try {
						if (CacheTable::instance()->isNextStarCache.at(p)) {
							result->addResultRow(temp);
						}
					} catch (exception& e) {
						if (pkb->optimizedCFG->isNextStar(leftIndex, temp.at(index))) {
						//if (pkb->optimizedCFG->isNextStar(leftIndex, temp.at(index))) {
							result->addResultRow(temp);
							CacheTable::instance()->isNextStarCache[p] = true;
						} else {
							CacheTable::instance()->isNextStarCache[p] = false;
						}
					}

				} else if (pkb->optimizedCFG->isNextStar(leftIndex, temp.at(index))) {
				//} else if (pkb->optimizedCFG->isNextStar(leftIndex, temp.at(index))) {
					result->addResultRow(temp);
				}
			} else {	// NextStar(_, syn)
				if (!pkb->optimizedCFG->getPrev(temp.at(index)).empty()) {
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
		set<int> tempPrevious = pkb->optimizedCFG->getAllPrev();
		vector<int> Previous(tempPrevious.begin(), tempPrevious.end());

		for (size_t i = 0; i < Previous.size(); i++) {
			// synonym type check
			if ((left == "assign" || left == "while" || left == "if" || left == "call")
				&& pkb->statementTable->getTNode(Previous[i])->getNodeType()!=TNODE_NAMES[synToNodeType.at(left)]){
				continue;
			}

			set<int> tempNextStar;
			vector<int> NextStar;
			if (leftSynonym == rightSynonym) {
				if (isConcurrent) {
					try {
						if(CacheTable::instance()->isNextStarCache.at(make_pair(Previous[i], Previous[i]))){
							NextStar.push_back(Previous[i]);
						}
					} catch (exception& e) {
						pair<int, int> p = pair<int, int>(Previous[i], Previous[i]);
						if(pkb->optimizedCFG->isNextStar(Previous[i], Previous[i])) {
							NextStar.push_back(Previous[i]);
							CacheTable::instance()->isNextStarCache[p] = true;
						} else {
							CacheTable::instance()->isNextStarCache[p] = false;
						}
					}
				} else {
					if(pkb->optimizedCFG->isNextStar(Previous[i], Previous[i])) {
						NextStar.push_back(Previous[i]);
					}
				}
			} else {
				if (isConcurrent) {
					try {
						NextStar = CacheTable::instance()->nextStarCache.at(Previous[i]);
					} catch (exception& e) {
						tempNextStar = pkb->optimizedCFG->getNextStar(Previous[i]);
						//tempNextStar = pkb->optimizedCFG->getNextStar(Previous[i]);
						NextStar.assign(tempNextStar.begin(), tempNextStar.end());
						CacheTable::instance()->nextStarCache.insert(map<int, vector<int>>::value_type(Previous[i], NextStar));
					}
				} else {
					tempNextStar = pkb->optimizedCFG->getNextStar(Previous[i]);
					//tempNextStar = pkb->optimizedCFG->getNextStar(Previous[i]);
					NextStar.assign(tempNextStar.begin(), tempNextStar.end());
				}
			}
			

			
			for (size_t j = 0; j < NextStar.size(); j++) {
				if (isConcurrent) {
					pair<int, int> p = pair<int, int>(Previous[i], NextStar[j]);
					CacheTable::instance()->isNextStarCache.insert(make_pair(p, true));
				}
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
		
		return tuple;
	}

	ResultTuple* solveBothSyn(ResultTuple* tuple) {
		ResultTuple* result = new ResultTuple();
		result->setSynonym(tuple->getSynonyms());
		result->setSynonymMap(tuple->getSynonymMap());

		int lIndex = tuple->getSynonymIndex(leftSynonym);
		int rIndex = tuple->getSynonymIndex(rightSynonym);
		vector<vector<int>> allres = tuple->getAllResults();

		pair<int, int> p = pair<int, int>();
		if (lIndex != -1 && rIndex != -1){ //case 1: both are inside
			for (size_t i = 0; i < allres.size(); i++){
				if (isConcurrent) {
					p.first = allres[i][lIndex];
					p.second = allres[i][rIndex];
					
					try {
						if (CacheTable::instance()->isNextStarCache.at(p)) {
							result->addResultRow(allres[i]);
						}
					} catch (exception& e) {
						if (pkb->optimizedCFG->isNextStar(allres[i][lIndex], allres[i][rIndex])){
						//if (pkb->optimizedCFG->isNextStar(allres[i][lIndex], allres[i][rIndex])){
							result->addResultRow(allres[i]);
							CacheTable::instance()->isNextStarCache[p] = true;
						} else {
							CacheTable::instance()->isNextStarCache[p] = false;
						}
					}
				} else {
					if (pkb->optimizedCFG->isNextStar(allres[i][lIndex], allres[i][rIndex])){
					//if (pkb->optimizedCFG->isNextStar(allres[i][lIndex], allres[i][rIndex])){
						result->addResultRow(allres[i]);
					}
				}
			}
		} else if (rIndex == -1) { //case 2: only left is inside
			int index = result->addSynonym(rightSynonym);
			result->addSynonymToMap(rightSynonym, index);
			map<int, vector<int>> prevSolution = map<int, vector<int>>();
			string right = synonymTable->at(rightSynonym);

			for (size_t i = 0; i < tuple->getAllResults().size(); i++) {
				int leftValue = tuple->getResultAt(i, lIndex);
				set<int> tempNextStar;
				vector<int> NextStar;
				
				if (isConcurrent) {
					try {
						NextStar = CacheTable::instance()->nextStarCache.at(leftValue);
					} catch (exception& e) {
						tempNextStar = pkb->optimizedCFG->getNextStar(leftValue);
						//tempNextStar = pkb->optimizedCFG->getNextStar(leftValue);
						NextStar.assign(tempNextStar.begin(), tempNextStar.end());
						CacheTable::instance()->nextStarCache.insert(map<int, vector<int>>::value_type(leftValue, NextStar));
					}
				} else {
					try {
						NextStar = prevSolution.at(leftValue);
					} catch (exception& e) {
						tempNextStar = pkb->optimizedCFG->getNextStar(leftValue);
						//tempNextStar = pkb->optimizedCFG->getNextStar(leftValue);
						NextStar.assign(tempNextStar.begin(), tempNextStar.end());
						prevSolution.insert(map<int, vector<int>>::value_type(leftValue, NextStar));
					}
				}
				
				p.first = leftValue;
				for (size_t j = 0; j < NextStar.size(); j++){
					if (isConcurrent) {
						p.second = NextStar[j];
						CacheTable::instance()->isNextStarCache[p] = true;
					}

					if ((right == "assign" || right == "while" || right == "if" || right == "call")
						&& pkb->statementTable->getTNode(NextStar[j])->getNodeType()!=TNODE_NAMES[synToNodeType.at(right)]){
						continue;
					}
					vector<int> newRow(tuple->getResultRow(i));
					newRow.push_back(NextStar[j]);
					result->addResultRow(newRow);
				}
			}
		} else if (lIndex == -1) { //case 3: only right is inside
			int index = result->addSynonym(leftSynonym);
			result->addSynonymToMap(leftSynonym, index);
			map<int, vector<int>> prevSolution = map<int, vector<int>>();
			string left = synonymTable->at(leftSynonym);

			for (size_t i = 0; i < tuple->getAllResults().size(); i++) {
				int rightValue = tuple->getResultAt(i, rIndex);
				set<int> tempPreviousStar;
				vector<int> PreviousStar;
				
				if (isConcurrent) {
					try {
						PreviousStar = CacheTable::instance()->previousStarCache.at(rightValue);
					} catch (exception& e) {
						tempPreviousStar = pkb->optimizedCFG->getPrevStar(rightValue);
						//tempPreviousStar = pkb->optimizedCFG->getPrevStar(rightValue);
						PreviousStar.assign(tempPreviousStar.begin(), tempPreviousStar.end());
						CacheTable::instance()->previousStarCache.insert(map<int, vector<int>>::value_type(rightValue, PreviousStar));
					}
				} else {
					try {
						PreviousStar = prevSolution.at(rightValue);
					} catch (exception& e) {
						tempPreviousStar = pkb->optimizedCFG->getPrevStar(rightValue);
						//tempPreviousStar = pkb->optimizedCFG->getPrevStar(rightValue);
						PreviousStar.assign(tempPreviousStar.begin(), tempPreviousStar.end());
						prevSolution.insert(map<int, vector<int>>::value_type(rightValue, PreviousStar));
					}
				}
				
				p.second = rightValue;
				for (size_t j = 0; j < PreviousStar.size(); j++){
					if (isConcurrent) {
						p.first = PreviousStar[j];
						CacheTable::instance()->isNextStarCache[p] = true;
					}

					if ((left == "assign" || left == "while" || left == "if" || left == "call")
						&& pkb->statementTable->getTNode(PreviousStar[j])->getNodeType()!=TNODE_NAMES[synToNodeType.at(left)]){
						continue;
					}
					vector<int> newRow(tuple->getResultRow(i));
					newRow.push_back(PreviousStar[j]);
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
			tuple->setEmpty(!pkb->optimizedCFG->isNextStar(leftIndex, rightIndex));
		} else if (isSyn == 7) {	//(_, digit)
			tuple->setEmpty(pkb->optimizedCFG->getPrev(rightIndex).empty());
		} else if (isSyn == 8) {	//(digit, _)
			tuple->setEmpty(pkb->optimizedCFG->getNext(leftIndex).empty());
		} else {	//(_, _)
			tuple->setEmpty(pkb->optimizedCFG->getAllNext().empty());
		}
		return tuple;
	}
};