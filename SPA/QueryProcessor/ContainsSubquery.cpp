#pragma once
#include <string>
#include <vector>
#include <map>
#include "Subquery.h"

using namespace std;

class ContainsSubquery : public Subquery{
public:
	ContainsSubquery(map<string, string>* m, PKBController* p) : Subquery(m, p){
	
	}

	ResultTuple* solve(){
		ResultTuple* ans;
		switch (isSyn) {
			case 1:
				ans = solveRightSyn();
				break;
			case 2:
				ans = solveLeftSyn();
				break;
			case 3:
				ans = solveBothSyn();
				break;
			default:
				break;
		}
		return ans;
	}
	
	bool validate() {
		if (isSyn != 1 && isSyn != 2 && isSyn != 3){
			return false;
		}
		if (isSyn == 1){
			string synonymType = synonymTable->at(rightSynonym);
			if (synonymType != "stmtLst" && synonymType != "plus" && synonymType != "minus" 
				&& synonymType != "times" && synonymType != "variable" && synonymType != "constant"){
				return false;
			}
		}
		if (isSyn == 2){
			string synonymType = synonymTable->at(leftSynonym);
			if (synonymType != "stmtLst"){
				return false;
			}
		}
		if (isSyn == 3){
			string lSynonymType = synonymTable->at(leftSynonym);
			string rSynonymType = synonymTable->at(rightSynonym);
			if (lSynonymType == "procedure" && rSynonymType == "stmtLst"){
				return true;
			} else if (lSynonymType == "stmtLst" && (rSynonymType == "stmt" || rSynonymType == "prog_line" || rSynonymType == "assign" || 
													 rSynonymType == "while" || rSynonymType == "if" || rSynonymType == "call")){
				return true;
			} else if (lSynonymType == "assign" && (rSynonymType == "variable" || rSynonymType == "constant" || rSynonymType == "plus" || 
													 rSynonymType == "minus" || rSynonymType == "times")){
				return true;
			} else if ((lSynonymType == "while" || lSynonymType == "if") && (rSynonymType == "stmtLst" || rSynonymType == "variable")){
				return true;
			} else if ((lSynonymType == "stmt" || lSynonymType == "prog_line") && (rSynonymType == "stmtLst" || rSynonymType == "variable" 
				|| rSynonymType == "constant" || rSynonymType == "plus" || rSynonymType == "minus" || rSynonymType == "times")){
				return true;
			} else if ((lSynonymType == "plus" || lSynonymType == "minus" || lSynonymType == "times") && (rSynonymType == "variable" || 
							rSynonymType == "constant" || rSynonymType == "plus" || rSynonymType == "minus" || rSynonymType == "times")){
				return true;
			} else {
				return false;
			}
		}
		return true;
	}

	void setPriority() {
		//TODO: - need priority calculation methods
		priority = 100;
	}

	ResultTuple* solve(ResultTuple* tuple) {
		ResultTuple* ans;
		switch (isSyn) {
			case 1:
				ans = solveRightSyn(tuple);
				break;
			case 2:
				ans = solveLeftSyn(tuple);
				break;
			case 3:
				ans = solveBothSyn(tuple);
				break;
			default:
				break;
		}
		return ans;
	}

	ResultTuple* solveLeftSyn() {
		ResultTuple* tuple = new ResultTuple();
		int index = tuple->addSynonym(leftSynonym);
		tuple->addSynonymToMap(leftSynonym, index);
		set<int> tempStmtLst = pkb->containsTable->getStmtLstContainingStmt(rightIndex);
		vector<int> stmtLst(tempStmtLst.begin(), tempStmtLst.end());
		for(size_t i = 0; i < stmtLst.size(); i++) {
			vector<int> temp = vector<int>();
			temp.push_back(stmtLst.at(i));
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
			if (pkb->containsTable->isContainsStmtLstStmt(temp.at(index), rightIndex)) {
				result->addResultRow(temp);
			}
		}
		return result;
	}

	ResultTuple* solveRightSyn() {
		ResultTuple* tuple = new ResultTuple();
		int index = tuple->addSynonym(rightSynonym);
		tuple->addSynonymToMap(rightSynonym, index);
		
		string rightSynType = synonymTable->at(rightSynonym);
		set<int> tempResults;
		if (rightSynType == "stmtLst"){
			tempResults = pkb->containsTable->getStmtLstContainedInStmt(leftIndex);
		} else if (rightSynType == "plus"){
			tempResults = pkb->containsTable->getPlusContainedInStmt(leftIndex);
		} else if (rightSynType == "minus"){
			tempResults = pkb->containsTable->getMinusContainedInStmt(leftIndex);
		} else if (rightSynType == "times"){
			tempResults = pkb->containsTable->getTimesContainedInStmt(leftIndex);
		} else if (rightSynType == "variable"){
			tempResults = pkb->containsTable->getVarContainedInStmt(leftIndex);
		} else if (rightSynType == "constant"){
			tempResults = pkb->containsTable->getConstContainedInStmt(leftIndex);
		}
		vector<int> results(tempResults.begin(), tempResults.end());
		for(size_t i = 0; i < results.size(); i++) {
			vector<int> temp = vector<int>();
			temp.push_back(results.at(i));
			tuple->addResultRow(temp);
		}
		return tuple;
	}

	ResultTuple* solveRightSyn(ResultTuple* tuple) {
		ResultTuple* result = new ResultTuple();
		result->setSynonym(tuple->getSynonyms());
		result->setSynonymMap(tuple->getSynonymMap());

		string rightSynType = synonymTable->at(rightSynonym);
		int index = tuple->getSynonymIndex(rightSynonym);
		for (size_t i = 0; i < tuple->getAllResults().size(); i++) {
			vector<int> temp = tuple->getAllResults().at(i);
			if (rightSynType == "stmtLst"){
				if (pkb->containsTable->isContainsStmtStmtLst(leftIndex, temp.at(index))){
					result->addResultRow(temp);
				}
			} else if (rightSynType == "plus"){
				if (pkb->containsTable->isContainsStmtPlus(leftIndex, temp.at(index))){
					result->addResultRow(temp);
				}
			} else if (rightSynType == "minus"){
				if (pkb->containsTable->isContainsStmtMinus(leftIndex, temp.at(index))){
					result->addResultRow(temp);
				}
			} else if (rightSynType == "times"){
				if (pkb->containsTable->isContainsStmtTimes(leftIndex, temp.at(index))){
					result->addResultRow(temp);
				}
			} else if (rightSynType == "variable"){
				if (pkb->containsTable->isContainsStmtVar(leftIndex, temp.at(index))){
					result->addResultRow(temp);
				}
			} else if (rightSynType == "constant"){
				if (pkb->containsTable->isContainsStmtConst(leftIndex, temp.at(index))){
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

		string leftSynType = synonymTable->at(leftSynonym);
		string rightSynType = synonymTable->at(rightSynonym);

		if (leftSynType == "procedure"){
			set<int> leftVals = pkb->containsTable->getAllProcStmtLstContainers();
			for (std::set<int>::iterator it1 = leftVals.begin(); it1 != leftVals.end(); ++it1){
				if (rightSynType == "stmtLst"){
					set<int> rightVals = pkb->containsTable->getStmtLstContainedInProc(*it1);
					for (std::set<int>::iterator it2 = rightVals.begin(); it2 != rightVals.end(); ++it2){
						vector<int> row = vector<int>();
						row.push_back(*it1);
						row.push_back(*it2);
						tuple->addResultRow(row);
					}
				}
			} 
		} else if (leftSynType == "stmtLst"){
			set<int> leftVals = pkb->containsTable->getAllStmtLstStmtContainers();
			for (std::set<int>::iterator it1 = leftVals.begin(); it1 != leftVals.end(); ++it1){
				if (rightSynType == "stmt" || rightSynType == "prog_line" || rightSynType == "assign" || rightSynType == "while" || rightSynType == "if" || rightSynType == "call"){
					set<int> rightVals = pkb->containsTable->getStmtContainedInStmtLst(*it1);
					for (std::set<int>::iterator it2 = rightVals.begin(); it2 != rightVals.end(); ++it2){
						if (rightSynType == "assign" || rightSynType == "while" || rightSynType == "if" || rightSynType == "call"){
							if (pkb->statementTable->getTNode(*it2)->getNodeType()!=TNODE_NAMES[synToNodeType.at(rightSynType)]){
								continue;
							}
						}
						vector<int> row = vector<int>();
						row.push_back(*it1);
						row.push_back(*it2);
						tuple->addResultRow(row);
					}
				}
			}
		} else if (leftSynType == "assign" || leftSynType == "while" || leftSynType == "if" || leftSynType == "stmt" || leftSynType == "prog_line"){
			set<int> leftVals = pkb->containsTable->getAllStmtLstStmtContainees();
			for (std::set<int>::iterator it1 = leftVals.begin(); it1 != leftVals.end(); ++it1){
				if (leftSynType == "assign" || leftSynType == "while" || leftSynType == "if"){
					if (pkb->statementTable->getTNode(*it1)->getNodeType()!=TNODE_NAMES[synToNodeType.at(leftSynType)]){
						continue;
					}
				}
				set<int> rightVals;
				if (rightSynType == "variable"){
					rightVals = pkb->containsTable->getVarContainedInStmt(*it1);
				} else if (rightSynType == "constant"){
					rightVals = pkb->containsTable->getConstContainedInStmt(*it1);
				} else if (rightSynType == "plus"){
					rightVals = pkb->containsTable->getPlusContainedInStmt(*it1);
				} else if (rightSynType == "minus"){
					rightVals = pkb->containsTable->getMinusContainedInStmt(*it1);
				} else if (rightSynType == "times"){
					rightVals = pkb->containsTable->getTimesContainedInStmt(*it1);
				} else if (rightSynType == "stmtLst"){
					rightVals = pkb->containsTable->getStmtLstContainedInStmt(*it1);
				}
				for (std::set<int>::iterator it2 = rightVals.begin(); it2 != rightVals.end(); ++it2){
					vector<int> row = vector<int>();
					row.push_back(*it1);
					row.push_back(*it2);
					tuple->addResultRow(row);
				}
			}
		} else if (leftSynType == "plus"){
			set<int> leftVals = pkb->containsTable->getAllStmtPlusContainees();
			for (std::set<int>::iterator it1 = leftVals.begin(); it1 != leftVals.end(); ++it1){
				set<int> rightVals;
				if (rightSynType == "variable"){
					rightVals = pkb->containsTable->getVarContainedInPlus(*it1);
				} else if (rightSynType == "constant"){
					rightVals = pkb->containsTable->getConstContainedInPlus(*it1);
				} else if (rightSynType == "plus"){
					rightVals = pkb->containsTable->getPlusContainedInPlus(*it1);
				} else if (rightSynType == "minus"){
					rightVals = pkb->containsTable->getMinusContainedInPlus(*it1);
				} else if (rightSynType == "times"){
					rightVals = pkb->containsTable->getTimesContainedInPlus(*it1);
				}
				for (std::set<int>::iterator it2 = rightVals.begin(); it2 != rightVals.end(); ++it2){
					vector<int> row = vector<int>();
					row.push_back(*it1);
					row.push_back(*it2);
					tuple->addResultRow(row);
				}
			}
		} else if (leftSynType == "minus"){
			set<int> leftVals = pkb->containsTable->getAllStmtMinusContainees();
			for (std::set<int>::iterator it1 = leftVals.begin(); it1 != leftVals.end(); ++it1){
				set<int> rightVals;
				if (rightSynType == "variable"){
					rightVals = pkb->containsTable->getVarContainedInMinus(*it1);
				} else if (rightSynType == "constant"){
					rightVals = pkb->containsTable->getConstContainedInMinus(*it1);
				} else if (rightSynType == "plus"){
					rightVals = pkb->containsTable->getPlusContainedInMinus(*it1);
				} else if (rightSynType == "minus"){
					rightVals = pkb->containsTable->getMinusContainedInMinus(*it1);
				} else if (rightSynType == "times"){
					rightVals = pkb->containsTable->getTimesContainedInMinus(*it1);
				}
				for (std::set<int>::iterator it2 = rightVals.begin(); it2 != rightVals.end(); ++it2){
					vector<int> row = vector<int>();
					row.push_back(*it1);
					row.push_back(*it2);
					tuple->addResultRow(row);
				}
			}
		} else if (leftSynType == "times"){
			set<int> leftVals = pkb->containsTable->getAllStmtTimesContainees();
			for (std::set<int>::iterator it1 = leftVals.begin(); it1 != leftVals.end(); ++it1){
				set<int> rightVals;
				if (rightSynType == "variable"){
					rightVals = pkb->containsTable->getVarContainedInTimes(*it1);
				} else if (rightSynType == "constant"){
					rightVals = pkb->containsTable->getConstContainedInTimes(*it1);
				} else if (rightSynType == "plus"){
					rightVals = pkb->containsTable->getPlusContainedInTimes(*it1);
				} else if (rightSynType == "minus"){
					rightVals = pkb->containsTable->getMinusContainedInTimes(*it1);
				} else if (rightSynType == "times"){
					rightVals = pkb->containsTable->getTimesContainedInTimes(*it1);
				}
				for (std::set<int>::iterator it2 = rightVals.begin(); it2 != rightVals.end(); ++it2){
					vector<int> row = vector<int>();
					row.push_back(*it1);
					row.push_back(*it2);
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

		string leftSynType = synonymTable->at(leftSynonym);
		string rightSynType = synonymTable->at(rightSynonym);

		int lIndex = tuple->getSynonymIndex(leftSynonym);
		int rIndex = tuple->getSynonymIndex(rightSynonym);

		if (lIndex != -1 && rIndex != -1){ //case 1: both are inside
			for (size_t i = 0; i < tuple->getAllResults().size(); i++){
				if (leftSynType == "procedure" && rightSynType == "stmtLst"){
					if (pkb->containsTable->isContainsProcStmtLst(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
						result->addResultRow(tuple->getResultRow(i));
					}
				} else if (leftSynType == "stmtLst" && (rightSynType == "stmt" || rightSynType == "prog_line" || rightSynType == "assign" ||
					rightSynType == "while" || rightSynType == "if" || rightSynType == "call")){
					if (pkb->containsTable->isContainsStmtLstStmt(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
						result->addResultRow(tuple->getResultRow(i));
					}
				} else if (leftSynType == "stmt" || leftSynType == "prog_line" || leftSynType == "assign" || leftSynType == "while" || leftSynType == "if"){
					if (rightSynType == "variable"){
						if (pkb->containsTable->isContainsStmtVar(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "constant"){
						if (pkb->containsTable->isContainsStmtConst(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "plus"){
						if (pkb->containsTable->isContainsStmtPlus(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "minus"){
						if (pkb->containsTable->isContainsStmtMinus(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "times"){
						if (pkb->containsTable->isContainsStmtTimes(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "stmtLst"){
						if (pkb->containsTable->isContainsStmtStmtLst(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					}
				} else if (leftSynType == "plus"){
					if (rightSynType == "variable"){
						if (pkb->containsTable->isContainsPlusVar(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "constant"){
						if (pkb->containsTable->isContainsPlusConst(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "plus"){
						if (pkb->containsTable->isContainsPlusPlus(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "minus"){
						if (pkb->containsTable->isContainsPlusMinus(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "times"){
						if (pkb->containsTable->isContainsPlusTimes(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					}
				} else if (leftSynType == "minus"){
					if (rightSynType == "variable"){
						if (pkb->containsTable->isContainsMinusVar(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "constant"){
						if (pkb->containsTable->isContainsMinusConst(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "plus"){
						if (pkb->containsTable->isContainsMinusPlus(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "minus"){
						if (pkb->containsTable->isContainsMinusMinus(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "times"){
						if (pkb->containsTable->isContainsMinusTimes(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					}
				} else if (leftSynType == "times"){
					if (rightSynType == "variable"){
						if (pkb->containsTable->isContainsTimesVar(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "constant"){
						if (pkb->containsTable->isContainsTimesConst(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "plus"){
						if (pkb->containsTable->isContainsTimesPlus(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "minus"){
						if (pkb->containsTable->isContainsTimesMinus(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "times"){
						if (pkb->containsTable->isContainsTimesTimes(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					}
				}
			}
		} else if (rIndex == -1) { //case 2: only left is inside
			int index = result->addSynonym(rightSynonym);
			result->addSynonymToMap(rightSynonym, index);
			map<int, vector<int>> prevSolution = map<int, vector<int>>();
			for (size_t i = 0; i < tuple->getAllResults().size(); i++) {
				int leftValue = tuple->getResultAt(i, lIndex);
				if (prevSolution.find(leftValue) == prevSolution.end()){
					set<int> tV;

					if (leftSynType == "procedure" && rightSynType == "stmtLst"){
						tV = pkb->containsTable->getStmtLstContainedInProc(leftValue);
					} else if (leftSynType == "stmtLst" && (rightSynType == "stmt" || rightSynType == "prog_line" || rightSynType == "assign" ||
						rightSynType == "while" || rightSynType == "if" || rightSynType == "call")){
							tV = pkb->containsTable->getStmtContainedInStmtLst(leftValue);
							for (std::set<int>::iterator it = tV.begin(); it!= tV.end();){
								if (rightSynType == "assign" || rightSynType == "while" || rightSynType == "if" || rightSynType == "call"){
									if (pkb->statementTable->getTNode(*it)->getNodeType()!=TNODE_NAMES[synToNodeType.at(rightSynType)]){
										tV.erase(it++);
									} else {
										++it;
									}
								}
							}
					} else if (leftSynType == "stmt" || leftSynType == "prog_line" || leftSynType == "assign" || leftSynType == "while" || leftSynType == "if"){
						if (rightSynType == "variable"){
							tV = pkb->containsTable->getVarContainedInStmt(leftValue);
						} else if (rightSynType == "constant"){
							tV = pkb->containsTable->getConstContainedInStmt(leftValue);
						} else if (rightSynType == "plus"){
							tV = pkb->containsTable->getPlusContainedInStmt(leftValue);
						} else if (rightSynType == "minus"){
							tV = pkb->containsTable->getMinusContainedInStmt(leftValue);
						} else if (rightSynType == "times"){
							tV = pkb->containsTable->getTimesContainedInStmt(leftValue);
						} else if (rightSynType == "stmtLst"){
							tV = pkb->containsTable->getStmtLstContainedInStmt(leftValue);
						}
					} else if (leftSynType == "plus"){
						if (rightSynType == "variable"){
							tV = pkb->containsTable->getVarContainedInPlus(leftValue);
						} else if (rightSynType == "constant"){
							tV = pkb->containsTable->getConstContainedInPlus(leftValue);
						} else if (rightSynType == "plus"){
							tV = pkb->containsTable->getPlusContainedInPlus(leftValue);
						} else if (rightSynType == "minus"){
							tV = pkb->containsTable->getMinusContainedInPlus(leftValue);
						} else if (rightSynType == "times"){
							tV = pkb->containsTable->getTimesContainedInPlus(leftValue);
						}
					} else if (leftSynType == "minus"){
						if (rightSynType == "variable"){
							tV = pkb->containsTable->getVarContainedInMinus(leftValue);
						} else if (rightSynType == "constant"){
							tV = pkb->containsTable->getConstContainedInMinus(leftValue);
						} else if (rightSynType == "plus"){
							tV = pkb->containsTable->getPlusContainedInMinus(leftValue);
						} else if (rightSynType == "minus"){
							tV = pkb->containsTable->getMinusContainedInMinus(leftValue);
						} else if (rightSynType == "times"){
							tV = pkb->containsTable->getTimesContainedInMinus(leftValue);
						}
					} else if (leftSynType == "times"){
						if (rightSynType == "variable"){
							tV = pkb->containsTable->getVarContainedInTimes(leftValue);
						} else if (rightSynType == "constant"){
							tV = pkb->containsTable->getConstContainedInTimes(leftValue);
						} else if (rightSynType == "plus"){
							tV = pkb->containsTable->getPlusContainedInTimes(leftValue);
						} else if (rightSynType == "minus"){
							tV = pkb->containsTable->getMinusContainedInTimes(leftValue);
						} else if (rightSynType == "times"){
							tV = pkb->containsTable->getTimesContainedInTimes(leftValue);
						}
					}

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
					set<int> tV;

					if (leftSynType == "procedure" && rightSynType == "stmtLst"){
						tV = pkb->containsTable->getProcContainingStmtLst(rightValue);
					} else if (leftSynType == "stmtLst" && (rightSynType == "stmt" || rightSynType == "prog_line" || rightSynType == "assign" ||
						rightSynType == "while" || rightSynType == "if" || rightSynType == "call")){
							tV = pkb->containsTable->getStmtLstContainingStmt(rightValue);
					} else if (leftSynType == "stmt" || leftSynType == "prog_line" || leftSynType == "assign" || leftSynType == "while" || leftSynType == "if"){
						if (rightSynType == "variable"){
							tV = pkb->containsTable->getStmtContainingVar(rightValue);
						} else if (rightSynType == "constant"){
							tV = pkb->containsTable->getStmtContainingConst(rightValue);
						} else if (rightSynType == "plus"){
							tV = pkb->containsTable->getStmtContainingPlus(rightValue);
						} else if (rightSynType == "minus"){
							tV = pkb->containsTable->getStmtContainingMinus(rightValue);
						} else if (rightSynType == "times"){
							tV = pkb->containsTable->getStmtContainingTimes(rightValue);
						} else if (rightSynType == "stmtLst"){
							tV = pkb->containsTable->getStmtContainingStmtLst(rightValue);
						}
						for (std::set<int>::iterator it = tV.begin(); it!= tV.end();){
							if (leftSynType == "assign" || leftSynType == "while" || leftSynType == "if"){
								if (pkb->statementTable->getTNode(*it)->getNodeType()!=TNODE_NAMES[synToNodeType.at(leftSynType)]){
									tV.erase(it++);
								} else {
									++it;
								}	
							}
						}
					} else if (leftSynType == "plus"){
						if (rightSynType == "variable"){
							tV = pkb->containsTable->getPlusContainingVar(rightValue);
						} else if (rightSynType == "constant"){
							tV = pkb->containsTable->getPlusContainingConst(rightValue);
						} else if (rightSynType == "plus"){
							tV = pkb->containsTable->getPlusContainingPlus(rightValue);
						} else if (rightSynType == "minus"){
							tV = pkb->containsTable->getPlusContainingMinus(rightValue);
						} else if (rightSynType == "times"){
							tV = pkb->containsTable->getPlusContainingTimes(rightValue);
						}
					} else if (leftSynType == "minus"){
						if (rightSynType == "variable"){
							tV = pkb->containsTable->getMinusContainingVar(rightValue);
						} else if (rightSynType == "constant"){
							tV = pkb->containsTable->getMinusContainingConst(rightValue);
						} else if (rightSynType == "plus"){
							tV = pkb->containsTable->getMinusContainingPlus(rightValue);
						} else if (rightSynType == "minus"){
							tV = pkb->containsTable->getMinusContainingMinus(rightValue);
						} else if (rightSynType == "times"){
							tV = pkb->containsTable->getMinusContainingTimes(rightValue);
						}
					} else if (leftSynType == "times"){
						if (rightSynType == "variable"){
							tV = pkb->containsTable->getTimesContainingVar(rightValue);
						} else if (rightSynType == "constant"){
							tV = pkb->containsTable->getTimesContainingConst(rightValue);
						} else if (rightSynType == "plus"){
							tV = pkb->containsTable->getTimesContainingPlus(rightValue);
						} else if (rightSynType == "minus"){
							tV = pkb->containsTable->getTimesContainingMinus(rightValue);
						} else if (rightSynType == "times"){
							tV = pkb->containsTable->getTimesContainingTimes(rightValue);
						}
					}

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
};