#pragma once
#include <string>
#include <vector>
#include <map>
#include "Subquery.h"

using namespace std;

class ContainsStarSubquery : public Subquery{
public:
	ContainsStarSubquery(map<string, string>* m, PKBController* p) : Subquery(m, p){
	
	}

	ResultTuple* solve(){
		ResultTuple* ans;
		switch (isSyn) {
			case 0:
				ans = solveNoSyn();
				break;
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
		if (isSyn != 0 || isSyn != 1 || isSyn != 2 || isSyn != 3){
			return false;
		}
		if (isSyn == 1){
			string synonymType = synonymTable->at(rightSynonym);
			if (synonymType != "stmtLst" || synonymType != "plus" || synonymType != "minus" 
				|| synonymType != "times" || synonymType != "variable" || synonymType != "constant"
				|| synonymType != "stmt" || synonymType != "prog_line" || synonymType != "assign"
				|| synonymType != "while" || synonymType != "if" || synonymType != "call"){
				return false;
			}
		}
		if (isSyn == 2){
			string synonymType = synonymTable->at(leftSynonym);
			if (synonymType != "stmtLst" || synonymType != "procedure" || synonymType != "stmt" || synonymType != "prog_line"
				|| synonymType != "while" || synonymType != "if"){
				return false;
			}
		}
		if (isSyn == 3){
			string lSynonymType = synonymTable->at(leftSynonym);
			string rSynonymType = synonymTable->at(rightSynonym);
			if (lSynonymType == "procedure" && (rSynonymType == "stmtLst" || rSynonymType == "stmt" || rSynonymType == "prog_line" 
													|| rSynonymType == "assign" || rSynonymType == "while" || rSynonymType == "if" 
													|| rSynonymType == "call" || rSynonymType == "plus" || rSynonymType == "minus"
													|| rSynonymType == "times" || rSynonymType == "variable" || rSynonymType == "constant")){
				return true;
			} else if (lSynonymType == "stmtLst" && (rSynonymType == "stmtLst" || rSynonymType == "stmt" || rSynonymType == "prog_line" 
													|| rSynonymType == "assign" || rSynonymType == "while" || rSynonymType == "if" 
													|| rSynonymType == "call" || rSynonymType == "plus" || rSynonymType == "minus"
													|| rSynonymType == "times" || rSynonymType == "variable" || rSynonymType == "constant")){
				return true;
			} else if (lSynonymType == "assign" && (rSynonymType == "variable" || rSynonymType == "constant" || rSynonymType == "plus" || 
													 rSynonymType == "minus" || rSynonymType == "times")){
				return true;
			} else if ((lSynonymType == "while" || lSynonymType == "if") && (rSynonymType == "stmtLst" || rSynonymType == "stmt" || rSynonymType == "prog_line" 
													|| rSynonymType == "assign" || rSynonymType == "while" || rSynonymType == "if" 
													|| rSynonymType == "call" || rSynonymType == "plus" || rSynonymType == "minus"
													|| rSynonymType == "times" || rSynonymType == "variable" || rSynonymType == "constant")){
				return true;
			} else if ((lSynonymType == "stmt" || lSynonymType == "prog_line") && (rSynonymType == "stmtLst" || rSynonymType == "stmt" || rSynonymType == "prog_line" 
													|| rSynonymType == "assign" || rSynonymType == "while" || rSynonymType == "if" 
													|| rSynonymType == "call" || rSynonymType == "plus" || rSynonymType == "minus"
													|| rSynonymType == "times" || rSynonymType == "variable" || rSynonymType == "constant")){
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

	ResultTuple* solveNoSyn(){
		ResultTuple* result = new ResultTuple();
		result->setBool(true);
		result->setEmpty(pkb->containsTable->isContainsStarStmtStmt(leftIndex, rightIndex));
		return result;
	}

	ResultTuple* solveLeftSyn() {
		ResultTuple* tuple = new ResultTuple();
		int index = tuple->addSynonym(leftSynonym);
		tuple->addSynonymToMap(leftSynonym, index);
		
		string leftSynType = synonymTable->at(leftSynonym);
		set<int> results;
		if (leftSynType == "stmtLst"){
			results = pkb->containsTable->getStmtLstContainingStarStmt(rightIndex);
		} else if (leftSynType == "stmt" || leftSynType == "prog_line" || leftSynType == "while" || leftSynType == "if"){
			results = pkb->containsTable->getStmtContainingStarStmt(rightIndex);
			for (std::set<int>::iterator it = results.begin(); it!= results.end();){
				if (leftSynType == "while" || leftSynType == "if"){
					if (pkb->statementTable->getTNode(*it)->getNodeType()!=TNODE_NAMES[synToNodeType.at(leftSynType)]){
						results.erase(it++);
					} else {
						++it;
					}	
				}
			}
		} else if (leftSynType == "procedure"){
			results = pkb->containsTable->getProcContainingStarStmt(rightIndex);
		}

		vector<int> finalResult(results.begin(), results.end());
		for(size_t i = 0; i < finalResult.size(); i++) {
			vector<int> temp = vector<int>();
			temp.push_back(finalResult.at(i));
			tuple->addResultRow(temp);
		}
		return tuple;
	}

	ResultTuple* solveLeftSyn(ResultTuple* tuple) {
		ResultTuple* result = new ResultTuple();
		result->setSynonym(tuple->getSynonyms());
		result->setSynonymMap(tuple->getSynonymMap());

		string leftSynType = synonymTable->at(leftSynonym);

		int index = tuple->getSynonymIndex(leftSynonym);
		for (size_t i = 0; i < tuple->getAllResults().size(); i++) {
			vector<int> temp = tuple->getAllResults().at(i);
			if (leftSynType == "stmtLst"){
				if (pkb->containsTable->isContainsStarStmtLstStmt(temp.at(index), rightIndex)){
					result->addResultRow(temp);
				}
			} else if (leftSynType == "stmt" || leftSynType == "prog_line" || leftSynType == "while" || leftSynType == "if"){
				if (pkb->containsTable->isContainsStarStmtStmt(temp.at(index), rightIndex)){
					result->addResultRow(temp);
				}
			} else if (leftSynType == "procedure"){
				if (pkb->containsTable->isContainsStarProcStmt(temp.at(index), rightIndex)){
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
		
		string rightSynType = synonymTable->at(rightSynonym);
		set<int> tempResults;
		if (rightSynType == "stmtLst"){
			tempResults = pkb->containsTable->getStmtLstContainedStarInStmt(leftIndex);
		} else if (rightSynType == "plus"){
			tempResults = pkb->containsTable->getPlusContainedStarInStmt(leftIndex);
		} else if (rightSynType == "minus"){
			tempResults = pkb->containsTable->getMinusContainedStarInStmt(leftIndex);
		} else if (rightSynType == "times"){
			tempResults = pkb->containsTable->getTimesContainedStarInStmt(leftIndex);
		} else if (rightSynType == "variable"){
			tempResults = pkb->containsTable->getVarContainedStarInStmt(leftIndex);
		} else if (rightSynType == "constant"){
			tempResults = pkb->containsTable->getConstContainedStarInStmt(leftIndex);
		} else if (rightSynType == "stmt" || rightSynType == "prog_line" || rightSynType == "assign" ||
					rightSynType == "while" || rightSynType == "if" || rightSynType == "call"){
			tempResults = pkb->containsTable->getStmtContainedStarInStmt(leftIndex);
			for (std::set<int>::iterator it = tempResults.begin(); it!= tempResults.end();){
				if (rightSynType == "assign" || rightSynType == "while" || rightSynType == "if" || rightSynType == "call"){
					if (pkb->statementTable->getTNode(*it)->getNodeType()!=TNODE_NAMES[synToNodeType.at(rightSynType)]){
						tempResults.erase(it++);
					} else {
						++it;
					}
				}
			}
		}
		vector<int> results(tempResults.begin(), tempResults.end());
		for(size_t i = 0; i < results.size(); i++) {
			vector<int> temp = vector<int>();
			temp.push_back(results.at(i));
			tuple->addResultRow(temp);
		}
		return tuple;
	}

	ResultTuple* solveRightSyn(ResultTuple* tuple)   {
		ResultTuple* result = new ResultTuple();
		result->setSynonym(tuple->getSynonyms());
		result->setSynonymMap(tuple->getSynonymMap());

		string rightSynType = synonymTable->at(rightSynonym);
		int index = tuple->getSynonymIndex(rightSynonym);
		for (size_t i = 0; i < tuple->getAllResults().size(); i++) {
			vector<int> temp = tuple->getAllResults().at(i);
			if (rightSynType == "stmtLst"){
				if (pkb->containsTable->isContainsStarStmtStmtLst(leftIndex, temp.at(index))){
					result->addResultRow(temp);
				}
			} else if (rightSynType == "plus"){
				if (pkb->containsTable->isContainsStarStmtPlus(leftIndex, temp.at(index))){
					result->addResultRow(temp);
				}
			} else if (rightSynType == "minus"){
				if (pkb->containsTable->isContainsStarStmtMinus(leftIndex, temp.at(index))){
					result->addResultRow(temp);
				}
			} else if (rightSynType == "times"){
				if (pkb->containsTable->isContainsStarStmtTimes(leftIndex, temp.at(index))){
					result->addResultRow(temp);
				}
			} else if (rightSynType == "variable"){
				if (pkb->containsTable->isContainsStarStmtVar(leftIndex, temp.at(index))){
					result->addResultRow(temp);
				}
			} else if (rightSynType == "constant"){
				if (pkb->containsTable->isContainsStarStmtConst(leftIndex, temp.at(index))){
					result->addResultRow(temp);
				}
			}  else if (rightSynType == "stmt" || rightSynType == "prog_line" || rightSynType == "assign" ||
					rightSynType == "while" || rightSynType == "if" || rightSynType == "call"){
				if (pkb->containsTable->isContainsStarStmtStmtLst(leftIndex, temp.at(index))){
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
				set<int> rightVals;
				if (rightSynType == "stmtLst"){
					rightVals = pkb->containsTable->getStmtLstContainedStarInProc(*it1);
				} else if (rightSynType == "stmt" || rightSynType == "prog_line" || rightSynType == "assign"
					|| rightSynType == "while" || rightSynType == "if" || rightSynType == "call"){
					rightVals = pkb->containsTable->getStmtContainedStarInProc(*it1);
					for (std::set<int>::iterator it = rightVals.begin(); it!= rightVals.end();){
						if (rightSynType == "assign" || rightSynType == "while" || rightSynType == "if" || rightSynType == "call"){
							if (pkb->statementTable->getTNode(*it)->getNodeType()!=TNODE_NAMES[synToNodeType.at(rightSynType)]){
								rightVals.erase(it++);
							} else {
								++it;
							}
						}
					}
				} else if (rightSynType == "variable"){
					rightVals = pkb->containsTable->getVarContainedStarInProc(*it1);
				} else if (rightSynType == "constant"){
					rightVals = pkb->containsTable->getConstContainedStarInProc(*it1);
				} else if (rightSynType == "plus"){
					rightVals = pkb->containsTable->getPlusContainedStarInProc(*it1);
				} else if (rightSynType == "minus"){
					rightVals = pkb->containsTable->getMinusContainedStarInProc(*it1);
				} else if (rightSynType == "times"){
					rightVals = pkb->containsTable->getTimesContainedStarInProc(*it1);
				}
				for (std::set<int>::iterator it2 = rightVals.begin(); it2 != rightVals.end(); ++it2){
					vector<int> row = vector<int>();
					row.push_back(*it1);
					row.push_back(*it2);
					tuple->addResultRow(row);
				}
			} 
		} else if (leftSynType == "stmtLst"){
			set<int> leftVals = pkb->containsTable->getAllStmtLstStmtContainers();
			for (std::set<int>::iterator it1 = leftVals.begin(); it1 != leftVals.end(); ++it1){
				set<int> rightVals;
				if (rightSynType == "stmtLst"){
					rightVals = pkb->containsTable->getStmtLstContainedStarInStmtLst(*it1);
				} else if (rightSynType == "stmt" || rightSynType == "prog_line" || rightSynType == "assign"
					|| rightSynType == "while" || rightSynType == "if" || rightSynType == "call"){
					rightVals = pkb->containsTable->getStmtContainedStarInStmtLst(*it1);
					for (std::set<int>::iterator it = rightVals.begin(); it!= rightVals.end();){
						if (rightSynType == "assign" || rightSynType == "while" || rightSynType == "if" || rightSynType == "call"){
							if (pkb->statementTable->getTNode(*it)->getNodeType()!=TNODE_NAMES[synToNodeType.at(rightSynType)]){
								rightVals.erase(it++);
							} else {
								++it;
							}
						}
					}
				} else if (rightSynType == "variable"){
					rightVals = pkb->containsTable->getVarContainedStarInStmtLst(*it1);
				} else if (rightSynType == "constant"){
					rightVals = pkb->containsTable->getConstContainedStarInStmtLst(*it1);
				} else if (rightSynType == "plus"){
					rightVals = pkb->containsTable->getPlusContainedStarInStmtLst(*it1);
				} else if (rightSynType == "minus"){
					rightVals = pkb->containsTable->getMinusContainedStarInStmtLst(*it1);
				} else if (rightSynType == "times"){
					rightVals = pkb->containsTable->getTimesContainedStarInStmtLst(*it1);
				}
				for (std::set<int>::iterator it2 = rightVals.begin(); it2 != rightVals.end(); ++it2){
					vector<int> row = vector<int>();
					row.push_back(*it1);
					row.push_back(*it2);
					tuple->addResultRow(row);
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
					rightVals = pkb->containsTable->getVarContainedStarInStmt(*it1);
				} else if (rightSynType == "constant"){
					rightVals = pkb->containsTable->getConstContainedStarInStmt(*it1);
				} else if (rightSynType == "plus"){
					rightVals = pkb->containsTable->getPlusContainedStarInStmt(*it1);
				} else if (rightSynType == "minus"){
					rightVals = pkb->containsTable->getMinusContainedStarInStmt(*it1);
				} else if (rightSynType == "times"){
					rightVals = pkb->containsTable->getTimesContainedStarInStmt(*it1);
				} else if (rightSynType == "stmtLst"){
					rightVals = pkb->containsTable->getStmtLstContainedStarInStmt(*it1);
				} else if (rightSynType == "stmt" || rightSynType == "prog_line" || rightSynType == "assign"
					|| rightSynType == "while" || rightSynType == "if" || rightSynType == "call"){
					rightVals = pkb->containsTable->getStmtContainedStarInStmt(*it1);
					for (std::set<int>::iterator it = rightVals.begin(); it!= rightVals.end();){
						if (rightSynType == "assign" || rightSynType == "if" || rightSynType == "while" || rightSynType == "call"){
							if (pkb->statementTable->getTNode(*it)->getNodeType()!=TNODE_NAMES[synToNodeType.at(rightSynType)]){
								rightVals.erase(it++);
							} else {
								++it;
							}
						}
					}
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
					rightVals = pkb->containsTable->getVarContainedStarInPlus(*it1);
				} else if (rightSynType == "constant"){
					rightVals = pkb->containsTable->getConstContainedStarInPlus(*it1);
				} else if (rightSynType == "plus"){
					rightVals = pkb->containsTable->getPlusContainedStarInPlus(*it1);
				} else if (rightSynType == "minus"){
					rightVals = pkb->containsTable->getMinusContainedStarInPlus(*it1);
				} else if (rightSynType == "times"){
					rightVals = pkb->containsTable->getTimesContainedStarInPlus(*it1);
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
					rightVals = pkb->containsTable->getVarContainedStarInMinus(*it1);
				} else if (rightSynType == "constant"){
					rightVals = pkb->containsTable->getConstContainedStarInMinus(*it1);
				} else if (rightSynType == "plus"){
					rightVals = pkb->containsTable->getPlusContainedStarInMinus(*it1);
				} else if (rightSynType == "minus"){
					rightVals = pkb->containsTable->getMinusContainedStarInMinus(*it1);
				} else if (rightSynType == "times"){
					rightVals = pkb->containsTable->getTimesContainedStarInMinus(*it1);
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
					rightVals = pkb->containsTable->getVarContainedStarInTimes(*it1);
				} else if (rightSynType == "constant"){
					rightVals = pkb->containsTable->getConstContainedStarInTimes(*it1);
				} else if (rightSynType == "plus"){
					rightVals = pkb->containsTable->getPlusContainedStarInTimes(*it1);
				} else if (rightSynType == "minus"){
					rightVals = pkb->containsTable->getMinusContainedStarInTimes(*it1);
				} else if (rightSynType == "times"){
					rightVals = pkb->containsTable->getTimesContainedStarInTimes(*it1);
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
				if (leftSynType == "procedure"){
					if (rightSynType == "stmtLst"){
						if (pkb->containsTable->isContainsStarProcStmtLst(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "stmt" || rightSynType == "prog_line" || rightSynType == "assign" ||
					rightSynType == "while" || rightSynType == "if" || rightSynType == "call"){
						if (pkb->containsTable->isContainsStarProcStmt(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "variable"){
						if (pkb->containsTable->isContainsStarProcVar(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "constant"){
						if (pkb->containsTable->isContainsStarProcConst(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "plus"){
						if (pkb->containsTable->isContainsStarProcPlus(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "minus"){
						if (pkb->containsTable->isContainsStarProcMinus(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "times"){
						if (pkb->containsTable->isContainsStarProcTimes(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					}
				} else if (leftSynType == "stmtLst"){
					if (rightSynType == "stmtLst"){
						if (pkb->containsTable->isContainsStarStmtLstStmtLst(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "stmt" || rightSynType == "prog_line" || rightSynType == "assign" ||
					rightSynType == "while" || rightSynType == "if" || rightSynType == "call"){
						if (pkb->containsTable->isContainsStarStmtLstStmt(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "variable"){
						if (pkb->containsTable->isContainsStarStmtLstVar(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "constant"){
						if (pkb->containsTable->isContainsStarStmtLstConst(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "plus"){
						if (pkb->containsTable->isContainsStarStmtLstPlus(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "minus"){
						if (pkb->containsTable->isContainsStarStmtLstMinus(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "times"){
						if (pkb->containsTable->isContainsStarStmtLstTimes(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					}
				} else if (leftSynType == "stmt" || leftSynType == "prog_line" || leftSynType == "assign" || leftSynType == "while" || leftSynType == "if"){
					if (rightSynType == "variable"){
						if (pkb->containsTable->isContainsStarStmtVar(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "constant"){
						if (pkb->containsTable->isContainsStarStmtConst(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "plus"){
						if (pkb->containsTable->isContainsStarStmtPlus(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "minus"){
						if (pkb->containsTable->isContainsStarStmtMinus(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "times"){
						if (pkb->containsTable->isContainsStarStmtTimes(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "stmtLst"){
						if (pkb->containsTable->isContainsStarStmtStmtLst(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "stmt" || rightSynType == "prog_line" || rightSynType == "assign" ||
						rightSynType == "while" || rightSynType == "if" || rightSynType == "call"){
						if (pkb->containsTable->isContainsStarStmtStmt(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					}
				} else if (leftSynType == "plus"){
					if (rightSynType == "variable"){
						if (pkb->containsTable->isContainsStarPlusVar(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "constant"){
						if (pkb->containsTable->isContainsStarPlusConst(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "plus"){
						if (pkb->containsTable->isContainsStarPlusPlus(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "minus"){
						if (pkb->containsTable->isContainsStarPlusMinus(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "times"){
						if (pkb->containsTable->isContainsStarPlusTimes(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					}
				} else if (leftSynType == "minus"){
					if (rightSynType == "variable"){
						if (pkb->containsTable->isContainsStarMinusVar(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "constant"){
						if (pkb->containsTable->isContainsStarMinusConst(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "plus"){
						if (pkb->containsTable->isContainsStarMinusPlus(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "minus"){
						if (pkb->containsTable->isContainsStarMinusMinus(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "times"){
						if (pkb->containsTable->isContainsStarMinusTimes(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					}
				} else if (leftSynType == "times"){
					if (rightSynType == "variable"){
						if (pkb->containsTable->isContainsStarTimesVar(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "constant"){
						if (pkb->containsTable->isContainsStarTimesConst(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "plus"){
						if (pkb->containsTable->isContainsStarTimesPlus(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "minus"){
						if (pkb->containsTable->isContainsStarTimesMinus(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "times"){
						if (pkb->containsTable->isContainsStarTimesTimes(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
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

					if (leftSynType == "procedure"){
						if (rightSynType == "stmtLst"){
							tV = pkb->containsTable->getStmtLstContainedStarInProc(leftValue);	
						} else if (rightSynType == "stmt" || rightSynType == "prog_line" || rightSynType == "assign" ||
						rightSynType == "while" || rightSynType == "if" || rightSynType == "call"){
							tV = pkb->containsTable->getStmtContainedStarInProc(leftValue);
							for (std::set<int>::iterator it = tV.begin(); it!= tV.end();){
								if (rightSynType == "assign" || rightSynType == "while" || rightSynType == "if" || rightSynType == "call"){
									if (pkb->statementTable->getTNode(*it)->getNodeType()!=TNODE_NAMES[synToNodeType.at(rightSynType)]){
										tV.erase(it++);
									} else {
										++it;
									}
								}
							}
						} else if (rightSynType == "variable"){
							tV = pkb->containsTable->getVarContainedStarInProc(leftValue);
						} else if (rightSynType == "constant"){
							tV = pkb->containsTable->getConstContainedStarInProc(leftValue);
						} else if (rightSynType == "plus"){
							tV = pkb->containsTable->getPlusContainedStarInProc(leftValue);
						} else if (rightSynType == "minus"){
							tV = pkb->containsTable->getMinusContainedStarInProc(leftValue);
						} else if (rightSynType == "times"){
							tV = pkb->containsTable->getTimesContainedStarInProc(leftValue);
						}
					} else if (leftSynType == "stmtLst"){
						if (rightSynType == "stmtLst"){
							tV = pkb->containsTable->getStmtLstContainedStarInStmtLst(leftValue);	
						} else if (rightSynType == "stmt" || rightSynType == "prog_line" || rightSynType == "assign" ||
						rightSynType == "while" || rightSynType == "if" || rightSynType == "call"){
							tV = pkb->containsTable->getStmtContainedStarInStmtLst(leftValue);
							for (std::set<int>::iterator it = tV.begin(); it!= tV.end();){
								if (rightSynType == "assign" || rightSynType == "while" || rightSynType == "if" || rightSynType == "call"){
									if (pkb->statementTable->getTNode(*it)->getNodeType()!=TNODE_NAMES[synToNodeType.at(rightSynType)]){
										tV.erase(it++);
									} else {
										++it;
									}
								}
							}
						} else if (rightSynType == "variable"){
							tV = pkb->containsTable->getVarContainedStarInStmtLst(leftValue);
						} else if (rightSynType == "constant"){
							tV = pkb->containsTable->getConstContainedStarInStmtLst(leftValue);
						} else if (rightSynType == "plus"){
							tV = pkb->containsTable->getPlusContainedStarInStmtLst(leftValue);
						} else if (rightSynType == "minus"){
							tV = pkb->containsTable->getMinusContainedStarInStmtLst(leftValue);
						} else if (rightSynType == "times"){
							tV = pkb->containsTable->getTimesContainedStarInStmtLst(leftValue);
						}
					} else if (leftSynType == "stmt" || leftSynType == "prog_line" || leftSynType == "assign" || leftSynType == "while" || leftSynType == "if"){
						if (rightSynType == "variable"){
							tV = pkb->containsTable->getVarContainedStarInStmt(leftValue);
						} else if (rightSynType == "constant"){
							tV = pkb->containsTable->getConstContainedStarInStmt(leftValue);
						} else if (rightSynType == "plus"){
							tV = pkb->containsTable->getPlusContainedStarInStmt(leftValue);
						} else if (rightSynType == "minus"){
							tV = pkb->containsTable->getMinusContainedStarInStmt(leftValue);
						} else if (rightSynType == "times"){
							tV = pkb->containsTable->getTimesContainedStarInStmt(leftValue);
						} else if (rightSynType == "stmtLst"){
							tV = pkb->containsTable->getStmtLstContainedStarInStmt(leftValue);
						} else if (rightSynType == "stmt" || rightSynType == "prog_line" || rightSynType == "assign" ||
						rightSynType == "while" || rightSynType == "if" || rightSynType == "call"){
							tV = pkb->containsTable->getStmtContainedStarInStmt(leftValue);
							for (std::set<int>::iterator it = tV.begin(); it!= tV.end();){
								if (rightSynType == "assign" || rightSynType == "while" || rightSynType == "if" || rightSynType == "call"){
									if (pkb->statementTable->getTNode(*it)->getNodeType()!=TNODE_NAMES[synToNodeType.at(rightSynType)]){
										tV.erase(it++);
									} else {
										++it;
									}
								}
							}
						}
					} else if (leftSynType == "plus"){
						if (rightSynType == "variable"){
							tV = pkb->containsTable->getVarContainedStarInPlus(leftValue);
						} else if (rightSynType == "constant"){
							tV = pkb->containsTable->getConstContainedStarInPlus(leftValue);
						} else if (rightSynType == "plus"){
							tV = pkb->containsTable->getPlusContainedStarInPlus(leftValue);
						} else if (rightSynType == "minus"){
							tV = pkb->containsTable->getMinusContainedStarInPlus(leftValue);
						} else if (rightSynType == "times"){
							tV = pkb->containsTable->getTimesContainedStarInPlus(leftValue);
						}
					} else if (leftSynType == "minus"){
						if (rightSynType == "variable"){
							tV = pkb->containsTable->getVarContainedStarInMinus(leftValue);
						} else if (rightSynType == "constant"){
							tV = pkb->containsTable->getConstContainedStarInMinus(leftValue);
						} else if (rightSynType == "plus"){
							tV = pkb->containsTable->getPlusContainedStarInMinus(leftValue);
						} else if (rightSynType == "minus"){
							tV = pkb->containsTable->getMinusContainedStarInMinus(leftValue);
						} else if (rightSynType == "times"){
							tV = pkb->containsTable->getTimesContainedStarInMinus(leftValue);
						}
					} else if (leftSynType == "times"){
						if (rightSynType == "variable"){
							tV = pkb->containsTable->getVarContainedStarInTimes(leftValue);
						} else if (rightSynType == "constant"){
							tV = pkb->containsTable->getConstContainedStarInTimes(leftValue);
						} else if (rightSynType == "plus"){
							tV = pkb->containsTable->getPlusContainedStarInTimes(leftValue);
						} else if (rightSynType == "minus"){
							tV = pkb->containsTable->getMinusContainedStarInTimes(leftValue);
						} else if (rightSynType == "times"){
							tV = pkb->containsTable->getTimesContainedStarInTimes(leftValue);
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

					if (leftSynType == "procedure"){
						if (rightSynType == "stmtLst"){
							tV = pkb->containsTable->getProcContainingStarStmtLst(rightValue);	
						} else if (rightSynType == "stmt" || rightSynType == "prog_line" || rightSynType == "assign" ||
						rightSynType == "while" || rightSynType == "if" || rightSynType == "call"){
							tV = pkb->containsTable->getProcContainingStarStmt(rightValue);
						} else if (rightSynType == "variable"){
							tV = pkb->containsTable->getProcsContainingStarVar(rightValue);
						} else if (rightSynType == "constant"){
							tV = pkb->containsTable->getProcContainingStarConst(rightValue);
						} else if (rightSynType == "plus"){
							tV = pkb->containsTable->getProcContainingStarPlus(rightValue);
						} else if (rightSynType == "minus"){
							tV = pkb->containsTable->getProcContainingStarMinus(rightValue);
						} else if (rightSynType == "times"){
							tV = pkb->containsTable->getProcContainingStarTimes(rightValue);
						}
					} else if (leftSynType == "stmtLst"){
						if (rightSynType == "stmtLst"){
							tV = pkb->containsTable->getStmtLstContainingStarStmtLst(rightValue);	
						} else if (rightSynType == "stmt" || rightSynType == "prog_line" || rightSynType == "assign" ||
						rightSynType == "while" || rightSynType == "if" || rightSynType == "call"){
							tV = pkb->containsTable->getStmtLstContainingStarStmt(rightValue);
						} else if (rightSynType == "variable"){
							tV = pkb->containsTable->getStmtLstContainingStarVar(rightValue);
						} else if (rightSynType == "constant"){
							tV = pkb->containsTable->getStmtLstContainingStarConst(rightValue);
						} else if (rightSynType == "plus"){
							tV = pkb->containsTable->getStmtLstContainingStarPlus(rightValue);
						} else if (rightSynType == "minus"){
							tV = pkb->containsTable->getStmtLstContainingStarMinus(rightValue);
						} else if (rightSynType == "times"){
							tV = pkb->containsTable->getStmtLstContainingStarTimes(rightValue);
						}
					} else if (leftSynType == "stmt" || leftSynType == "prog_line" || leftSynType == "assign" || leftSynType == "while" || leftSynType == "if"){
						if (rightSynType == "variable"){
							tV = pkb->containsTable->getStmtContainingStarVar(rightValue);
						} else if (rightSynType == "constant"){
							tV = pkb->containsTable->getStmtContainingStarConst(rightValue);
						} else if (rightSynType == "plus"){
							tV = pkb->containsTable->getStmtContainingStarPlus(rightValue);
						} else if (rightSynType == "minus"){
							tV = pkb->containsTable->getStmtContainingStarMinus(rightValue);
						} else if (rightSynType == "times"){
							tV = pkb->containsTable->getStmtContainingStarTimes(rightValue);
						} else if (rightSynType == "stmtLst"){
							tV = pkb->containsTable->getStmtContainingStarStmtLst(rightValue);
						} else if (rightSynType == "stmt" || rightSynType == "prog_line" || rightSynType == "assign" ||
						rightSynType == "while" || rightSynType == "if" || rightSynType == "call"){
							tV = pkb->containsTable->getStmtContainingStarStmt(rightValue);
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
							tV = pkb->containsTable->getPlusContainingStarVar(rightValue);
						} else if (rightSynType == "constant"){
							tV = pkb->containsTable->getPlusContainingStarConst(rightValue);
						} else if (rightSynType == "plus"){
							tV = pkb->containsTable->getPlusContainingStarPlus(rightValue);
						} else if (rightSynType == "minus"){
							tV = pkb->containsTable->getPlusContainingStarMinus(rightValue);
						} else if (rightSynType == "times"){
							tV = pkb->containsTable->getPlusContainingStarTimes(rightValue);
						}
					} else if (leftSynType == "minus"){
						if (rightSynType == "variable"){
							tV = pkb->containsTable->getMinusContainingStarVar(rightValue);
						} else if (rightSynType == "constant"){
							tV = pkb->containsTable->getMinusContainingStarConst(rightValue);
						} else if (rightSynType == "plus"){
							tV = pkb->containsTable->getMinusContainingStarPlus(rightValue);
						} else if (rightSynType == "minus"){
							tV = pkb->containsTable->getMinusContainingStarMinus(rightValue);
						} else if (rightSynType == "times"){
							tV = pkb->containsTable->getMinusContainingStarTimes(rightValue);
						}
					} else if (leftSynType == "times"){
						if (rightSynType == "variable"){
							tV = pkb->containsTable->getTimesContainingStarVar(rightValue);
						} else if (rightSynType == "constant"){
							tV = pkb->containsTable->getTimesContainingStarConst(rightValue);
						} else if (rightSynType == "plus"){
							tV = pkb->containsTable->getTimesContainingStarPlus(rightValue);
						} else if (rightSynType == "minus"){
							tV = pkb->containsTable->getTimesContainingStarMinus(rightValue);
						} else if (rightSynType == "times"){
							tV = pkb->containsTable->getTimesContainingStarTimes(rightValue);
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