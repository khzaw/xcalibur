#pragma once
#include <string>
#include <vector>
#include <map>
#include "Subquery.h"

using namespace std;

class SiblingSubquery : public Subquery{
public:
	SiblingSubquery(map<string, string>* m, PKBController* p) : Subquery(m, p){
	
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
		if (isSyn != 0 && isSyn != 1 && isSyn != 2 && isSyn != 3){
			return false;
		}
		if (isSyn == 1){
			string synonymType = synonymTable->at(rightSynonym);
			if (synonymType != "stmt" && synonymType != "prog_line" && synonymType != "assign"
				&& synonymType != "while" && synonymType != "if" && synonymType != "call"){
				return false;
			}
		}
		if (isSyn == 2){
			string synonymType = synonymTable->at(leftSynonym);
			if (synonymType != "stmt" && synonymType != "prog_line"
				&& synonymType != "while" && synonymType != "if" && synonymType != "call" && synonymType != "assign"){
				return false;
			}
		}
		if (isSyn == 3){
			string lSynonymType = synonymTable->at(leftSynonym);
			string rSynonymType = synonymTable->at(rightSynonym);
			if (lSynonymType == "procedure" && rSynonymType == "procedure"){
				return true;
			} else if (lSynonymType == "stmtLst" && (rSynonymType == "stmtLst" || rSynonymType == "variable")){
				return true;
			} else if ((lSynonymType == "stmt" || lSynonymType == "prog_line" || lSynonymType == "while" || lSynonymType == "if" ||
				lSynonymType == "call" || lSynonymType == "assign") && (rSynonymType == "stmt" || rSynonymType == "prog_line" 
													|| rSynonymType == "assign" || rSynonymType == "while" || rSynonymType == "if" 
													|| rSynonymType == "call")){
				return true;
			} else if ((lSynonymType == "plus" || lSynonymType == "minus" || lSynonymType == "times" || lSynonymType == "constant") && 
				(rSynonymType == "variable" || rSynonymType == "constant" || rSynonymType == "plus" || 
				rSynonymType == "minus" || rSynonymType == "times")){
				return true;
			} else if (lSynonymType == "variable" && (rSynonymType == "stmtLst" || rSynonymType == "variable" || rSynonymType == "constant" 
				|| rSynonymType == "plus" || rSynonymType == "minus" || rSynonymType == "times")){
				return true;
			} else {
				return false;
			}
		}
		return true;
	}

	void setPriority() {
		//TODO: - need priority calculation methods
		priority = pkb->containsTable->getAllProcs().size() + pkb->containsTable->getAllStmtLsts().size()
			+ pkb->containsTable->getAllStmts().size() + pkb->containsTable->getAllVars().size()
			+ pkb->containsTable->getAllConsts().size() + pkb->containsTable->getAllPlus().size()
			+ pkb->containsTable->getAllMinus().size() + pkb->containsTable->getAllTimes().size();
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
		result->setEmpty(!pkb->siblingTable->isSiblingStmtStmt(leftIndex, rightIndex));
		return result;
	}

	ResultTuple* solveLeftSyn() {
		ResultTuple* tuple = new ResultTuple();
		int index = tuple->addSynonym(leftSynonym);
		tuple->addSynonymToMap(leftSynonym, index);
		
		string leftSynType = synonymTable->at(leftSynonym);
		set<int> results = pkb->siblingTable->getStmtSiblingOfStmt(rightIndex);
		for (std::set<int>::iterator it = results.begin(); it!= results.end();){
			if (leftSynType == "assign" || leftSynType == "while" || leftSynType == "if" || leftSynType == "call"){
				if (pkb->statementTable->getTNode(*it)->getNodeType()!=TNODE_NAMES[synToNodeType.at(leftSynType)]){
					results.erase(it++);
				} else {
					++it;
				}	
			} else {
				++it;
			}
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
			if (pkb->siblingTable->isSiblingStmtStmt(temp.at(index), rightIndex)){
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
		set<int> results = pkb->siblingTable->getStmtSiblingOfStmt(leftIndex);
		for (std::set<int>::iterator it = results.begin(); it!= results.end();){
			if (rightSynType == "assign" || rightSynType == "while" || rightSynType == "if" || rightSynType == "call"){
				if (pkb->statementTable->getTNode(*it)->getNodeType()!=TNODE_NAMES[synToNodeType.at(rightSynType)]){
					results.erase(it++);
				} else {
					++it;
				}	
			} else {
				++it;
			}
		}

		vector<int> finalResults(results.begin(), results.end());
		for(size_t i = 0; i < results.size(); i++) {
			vector<int> temp = vector<int>();
			temp.push_back(finalResults.at(i));
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
			if (pkb->siblingTable->isSiblingStmtStmt(leftIndex, temp.at(index))){
				result->addResultRow(temp);
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
			vector<pair<int, int> > results = pkb->siblingTable->getProcProcSibling();
			for (size_t i = 0; i < results.size(); i++){
				vector<int> row = vector<int>();
				row.push_back(results.at(i).first);
				row.push_back(results.at(i).second);
				tuple->addResultRow(row);
			}
		} else if (leftSynType == "stmtLst"){
			if (rightSynType == "stmtLst"){
				vector<pair<int, int> > results = pkb->siblingTable->getStmtLstStmtLstSibling();
				for (size_t i = 0; i < results.size(); i++){
					vector<int> row = vector<int>();
					row.push_back(results.at(i).first);
					row.push_back(results.at(i).second);
					tuple->addResultRow(row);
				}
			} else if (rightSynType == "variable"){
				vector<pair<int, int> > results = pkb->siblingTable->getVarStmtLstSibling();
				for (size_t i = 0; i < results.size(); i++){
					vector<int> row = vector<int>();
					row.push_back(results.at(i).second);
					row.push_back(results.at(i).first);
					tuple->addResultRow(row);
				}
			}
		} else if (leftSynType == "call" || leftSynType == "assign" || leftSynType == "while" || 
			leftSynType == "if" || leftSynType == "stmt" || leftSynType == "prog_line"){
			set<int> leftVals = pkb->siblingTable->getAllStmtSiblingOfStmt();
			for (std::set<int>::iterator it = leftVals.begin(); it!= leftVals.end();){
				if (leftSynType == "assign" || leftSynType == "while" || leftSynType == "if" || leftSynType == "call"){
					if (pkb->statementTable->getTNode(*it)->getNodeType()!=TNODE_NAMES[synToNodeType.at(leftSynType)]){
						leftVals.erase(it++);
					} else {
						++it;
					}	
				} else {
					++it;
				}
			}
			for (std::set<int>::iterator it1 = leftVals.begin(); it1 != leftVals.end(); ++it1){
				set<int> rightVals = pkb->siblingTable->getStmtSiblingOfStmt(*it1);
				for (std::set<int>::iterator it = rightVals.begin(); it!= rightVals.end();){
					if (rightSynType == "assign" || rightSynType == "while" || rightSynType == "if" || rightSynType == "call"){
						if (pkb->statementTable->getTNode(*it)->getNodeType()!=TNODE_NAMES[synToNodeType.at(rightSynType)]){
							rightVals.erase(it++);
						} else {
							++it;
						}	
					} else {
						++it;
					}
				}
				for (std::set<int>::iterator it2 = rightVals.begin(); it2 != rightVals.end(); ++it2){
					vector<int> row = vector<int>();
					row.push_back(*it1);
					row.push_back(*it2);
					tuple->addResultRow(row);
				}
			}
		} else if (leftSynType == "variable"){
			if (rightSynType == "stmtLst"){
				vector<pair<int, int> > results = pkb->siblingTable->getVarStmtLstSibling();
				for (size_t i = 0; i < results.size(); i++){
					vector<int> row = vector<int>();
					row.push_back(results.at(i).first);
					row.push_back(results.at(i).second);
					tuple->addResultRow(row);
				}
			} else if (rightSynType == "variable"){
				vector<pair<int, int> > results = pkb->siblingTable->getVarVarSibling();
				for (size_t i = 0; i < results.size(); i++){
					vector<int> row = vector<int>();
					row.push_back(results.at(i).first);
					row.push_back(results.at(i).second);
					tuple->addResultRow(row);
				}
			} else if (rightSynType == "constant"){
				vector<pair<int, int> > results = pkb->siblingTable->getVarConstSibling();
				for (size_t i = 0; i < results.size(); i++){
					vector<int> row = vector<int>();
					row.push_back(results.at(i).first);
					row.push_back(results.at(i).second);
					tuple->addResultRow(row);
				}
			} else if (rightSynType == "plus"){
				vector<pair<int, int> > results = pkb->siblingTable->getVarPlusSibling();
				for (size_t i = 0; i < results.size(); i++){
					vector<int> row = vector<int>();
					row.push_back(results.at(i).first);
					row.push_back(results.at(i).second);
					tuple->addResultRow(row);
				}
			} else if (rightSynType == "minus"){
				vector<pair<int, int> > results = pkb->siblingTable->getVarMinusSibling();
				for (size_t i = 0; i < results.size(); i++){
					vector<int> row = vector<int>();
					row.push_back(results.at(i).first);
					row.push_back(results.at(i).second);
					tuple->addResultRow(row);
				}
			} else if (rightSynType == "times"){
				vector<pair<int, int> > results = pkb->siblingTable->getVarTimesSibling();
				for (size_t i = 0; i < results.size(); i++){
					vector<int> row = vector<int>();
					row.push_back(results.at(i).first);
					row.push_back(results.at(i).second);
					tuple->addResultRow(row);
				}
			}
		} else if (leftSynType == "constant"){
			if (rightSynType == "variable"){
				vector<pair<int, int> > results = pkb->siblingTable->getVarConstSibling();
				for (size_t i = 0; i < results.size(); i++){
					vector<int> row = vector<int>();
					row.push_back(results.at(i).second);
					row.push_back(results.at(i).first);
					tuple->addResultRow(row);
				}
			} else if (rightSynType == "constant"){
				vector<pair<int, int> > results = pkb->siblingTable->getConstConstSibling();
				for (size_t i = 0; i < results.size(); i++){
					vector<int> row = vector<int>();
					row.push_back(results.at(i).first);
					row.push_back(results.at(i).second);
					tuple->addResultRow(row);
				}
			} else if (rightSynType == "plus"){
				vector<pair<int, int> > results = pkb->siblingTable->getConstPlusSibling();
				for (size_t i = 0; i < results.size(); i++){
					vector<int> row = vector<int>();
					row.push_back(results.at(i).first);
					row.push_back(results.at(i).second);
					tuple->addResultRow(row);
				}
			} else if (rightSynType == "minus"){
				vector<pair<int, int> > results = pkb->siblingTable->getConstMinusSibling();
				for (size_t i = 0; i < results.size(); i++){
					vector<int> row = vector<int>();
					row.push_back(results.at(i).first);
					row.push_back(results.at(i).second);
					tuple->addResultRow(row);
				}
			} else if (rightSynType == "times"){
				vector<pair<int, int> > results = pkb->siblingTable->getConstTimesSibling();
				for (size_t i = 0; i < results.size(); i++){
					vector<int> row = vector<int>();
					row.push_back(results.at(i).first);
					row.push_back(results.at(i).second);
					tuple->addResultRow(row);
				}
			}
		} else if (leftSynType == "plus"){
			if (rightSynType == "variable"){
				vector<pair<int, int> > results = pkb->siblingTable->getVarPlusSibling();
				for (size_t i = 0; i < results.size(); i++){
					vector<int> row = vector<int>();
					row.push_back(results.at(i).second);
					row.push_back(results.at(i).first);
					tuple->addResultRow(row);
				}
			} else if (rightSynType == "constant"){
				vector<pair<int, int> > results = pkb->siblingTable->getConstPlusSibling();
				for (size_t i = 0; i < results.size(); i++){
					vector<int> row = vector<int>();
					row.push_back(results.at(i).second);
					row.push_back(results.at(i).first);
					tuple->addResultRow(row);
				}
			} else if (rightSynType == "plus"){
				vector<pair<int, int> > results = pkb->siblingTable->getPlusPlusSibling();
				for (size_t i = 0; i < results.size(); i++){
					vector<int> row = vector<int>();
					row.push_back(results.at(i).first);
					row.push_back(results.at(i).second);
					tuple->addResultRow(row);
				}
			} else if (rightSynType == "minus"){
				vector<pair<int, int> > results = pkb->siblingTable->getPlusMinusSibling();
				for (size_t i = 0; i < results.size(); i++){
					vector<int> row = vector<int>();
					row.push_back(results.at(i).first);
					row.push_back(results.at(i).second);
					tuple->addResultRow(row);
				}
			} else if (rightSynType == "times"){
				vector<pair<int, int> > results = pkb->siblingTable->getPlusTimesSibling();
				for (size_t i = 0; i < results.size(); i++){
					vector<int> row = vector<int>();
					row.push_back(results.at(i).first);
					row.push_back(results.at(i).second);
					tuple->addResultRow(row);
				}
			}
		} else if (leftSynType == "minus"){
			if (rightSynType == "variable"){
				vector<pair<int, int> > results = pkb->siblingTable->getVarMinusSibling();
				for (size_t i = 0; i < results.size(); i++){
					vector<int> row = vector<int>();
					row.push_back(results.at(i).second);
					row.push_back(results.at(i).first);
					tuple->addResultRow(row);
				}
			} else if (rightSynType == "constant"){
				vector<pair<int, int> > results = pkb->siblingTable->getConstMinusSibling();
				for (size_t i = 0; i < results.size(); i++){
					vector<int> row = vector<int>();
					row.push_back(results.at(i).second);
					row.push_back(results.at(i).first);
					tuple->addResultRow(row);
				}
			} else if (rightSynType == "plus"){
				vector<pair<int, int> > results = pkb->siblingTable->getPlusMinusSibling();
				for (size_t i = 0; i < results.size(); i++){
					vector<int> row = vector<int>();
					row.push_back(results.at(i).second);
					row.push_back(results.at(i).first);
					tuple->addResultRow(row);
				}
			} else if (rightSynType == "minus"){
				vector<pair<int, int> > results = pkb->siblingTable->getMinusMinusSibling();
				for (size_t i = 0; i < results.size(); i++){
					vector<int> row = vector<int>();
					row.push_back(results.at(i).first);
					row.push_back(results.at(i).second);
					tuple->addResultRow(row);
				}
			} else if (rightSynType == "times"){
				vector<pair<int, int> > results = pkb->siblingTable->getMinusTimesSibling();
				for (size_t i = 0; i < results.size(); i++){
					vector<int> row = vector<int>();
					row.push_back(results.at(i).first);
					row.push_back(results.at(i).second);
					tuple->addResultRow(row);
				}
			}
		} else if (leftSynType == "times"){
			if (rightSynType == "variable"){
				vector<pair<int, int> > results = pkb->siblingTable->getVarTimesSibling();
				for (size_t i = 0; i < results.size(); i++){
					vector<int> row = vector<int>();
					row.push_back(results.at(i).second);
					row.push_back(results.at(i).first);
					tuple->addResultRow(row);
				}
			} else if (rightSynType == "constant"){
				vector<pair<int, int> > results = pkb->siblingTable->getConstTimesSibling();
				for (size_t i = 0; i < results.size(); i++){
					vector<int> row = vector<int>();
					row.push_back(results.at(i).second);
					row.push_back(results.at(i).first);
					tuple->addResultRow(row);
				}
			} else if (rightSynType == "plus"){
				vector<pair<int, int> > results = pkb->siblingTable->getPlusTimesSibling();
				for (size_t i = 0; i < results.size(); i++){
					vector<int> row = vector<int>();
					row.push_back(results.at(i).second);
					row.push_back(results.at(i).first);
					tuple->addResultRow(row);
				}
			} else if (rightSynType == "minus"){
				vector<pair<int, int> > results = pkb->siblingTable->getMinusTimesSibling();
				for (size_t i = 0; i < results.size(); i++){
					vector<int> row = vector<int>();
					row.push_back(results.at(i).second);
					row.push_back(results.at(i).first);
					tuple->addResultRow(row);
				}
			} else if (rightSynType == "times"){
				vector<pair<int, int> > results = pkb->siblingTable->getTimesTimesSibling();
				for (size_t i = 0; i < results.size(); i++){
					vector<int> row = vector<int>();
					row.push_back(results.at(i).first);
					row.push_back(results.at(i).second);
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
				if (leftSynType == "procedure" && rightSynType == "procedure"){
					if (pkb->siblingTable->isSiblingProcProc(lIndex, rIndex)){
						result->addResultRow(tuple->getResultRow(i));
					}
				} else if (leftSynType == "stmtLst"){
					if (rightSynType == "stmtLst"){
						if (pkb->siblingTable->isSiblingStmtLstStmtLst(lIndex, rIndex)){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "variable"){
						if (pkb->siblingTable->isSiblingVarStmtLst(rIndex, lIndex)){
							result->addResultRow(tuple->getResultRow(i));
						}
					}
				} else if (leftSynType == "stmt" || leftSynType == "prog_line" || leftSynType == "assign" || 
					leftSynType == "while" || leftSynType == "if" || leftSynType == "call"){
					if (rightSynType == "stmt" || rightSynType == "prog_line" || rightSynType == "assign" || 
					rightSynType == "while" || rightSynType == "if" || rightSynType == "call"){
						if (pkb->siblingTable->isSiblingStmtStmt(lIndex, rIndex)){
							result->addResultRow(tuple->getResultRow(i));
						}
					}
				} else if (leftSynType == "variable"){
					if (rightSynType == "stmtLst"){
						if (pkb->siblingTable->isSiblingVarStmtLst(lIndex, rIndex)){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "variable"){
						if (pkb->siblingTable->isSiblingVarVar(lIndex, rIndex)){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "constant"){
						if (pkb->siblingTable->isSiblingVarConst(lIndex, rIndex)){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "plus"){
						if (pkb->siblingTable->isSiblingVarPlus(lIndex, rIndex)){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "minus"){
						if (pkb->siblingTable->isSiblingVarMinus(lIndex, rIndex)){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "times"){
						if (pkb->siblingTable->isSiblingVarTimes(lIndex, rIndex)){
							result->addResultRow(tuple->getResultRow(i));
						}
					}
				} else if (leftSynType == "constant"){
					if (rightSynType == "variable"){
						if (pkb->siblingTable->isSiblingVarConst(rIndex, lIndex)){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "constant"){
						if (pkb->siblingTable->isSiblingConstConst(lIndex, rIndex)){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "plus"){
						if (pkb->siblingTable->isSiblingConstPlus(lIndex, rIndex)){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "minus"){
						if (pkb->siblingTable->isSiblingConstMinus(lIndex, rIndex)){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "times"){
						if (pkb->siblingTable->isSiblingConstTimes(lIndex, rIndex)){
							result->addResultRow(tuple->getResultRow(i));
						}
					}
				} else if (leftSynType == "plus"){
					if (rightSynType == "variable"){
						if (pkb->siblingTable->isSiblingVarPlus(rIndex, lIndex)){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "constant"){
						if (pkb->siblingTable->isSiblingConstPlus(rIndex, lIndex)){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "plus"){
						if (pkb->siblingTable->isSiblingPlusPlus(lIndex, rIndex)){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "minus"){
						if (pkb->siblingTable->isSiblingPlusMinus(lIndex, rIndex)){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "times"){
						if (pkb->siblingTable->isSiblingPlusTimes(lIndex, rIndex)){
							result->addResultRow(tuple->getResultRow(i));
						}
					}
				} else if (leftSynType == "minus"){
					if (rightSynType == "variable"){
						if (pkb->siblingTable->isSiblingVarMinus(rIndex, lIndex)){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "constant"){
						if (pkb->siblingTable->isSiblingConstMinus(rIndex, lIndex)){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "plus"){
						if (pkb->siblingTable->isSiblingPlusMinus(rIndex, lIndex)){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "minus"){
						if (pkb->siblingTable->isSiblingMinusMinus(lIndex, rIndex)){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "times"){
						if (pkb->siblingTable->isSiblingMinusTimes(lIndex, rIndex)){
							result->addResultRow(tuple->getResultRow(i));
						}
					}
				} else if (leftSynType == "times"){
					if (rightSynType == "variable"){
						if (pkb->siblingTable->isSiblingVarTimes(rIndex, lIndex)){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "constant"){
						if (pkb->siblingTable->isSiblingConstTimes(rIndex, lIndex)){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "plus"){
						if (pkb->siblingTable->isSiblingPlusTimes(rIndex, lIndex)){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "minus"){
						if (pkb->siblingTable->isSiblingMinusTimes(rIndex, lIndex)){
							result->addResultRow(tuple->getResultRow(i));
						}
					} else if (rightSynType == "times"){
						if (pkb->siblingTable->isSiblingTimesTimes(lIndex, rIndex)){
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

					if (leftSynType == "procedure" && rightSynType == "procedure"){
						tV = pkb->siblingTable->getProcsSiblingOfProc(leftValue);
					} else if (leftSynType == "stmtLst"){
						if (rightSynType == "stmtLst"){
							tV = pkb->siblingTable->getStmtLstSiblingOfStmtLst(leftValue);	
						} else if (rightSynType == "variable"){
							tV = pkb->siblingTable->getVarSiblingOfStmtLst(leftValue);
						}
					} else if (leftSynType == "stmt" || leftSynType == "prog_line" || leftSynType == "assign" 
						|| leftSynType == "while" || leftSynType == "if" || leftSynType == "call"){
						if (rightSynType == "stmt" || rightSynType == "prog_line" || rightSynType == "assign" 
						|| rightSynType == "while" || rightSynType == "if" || rightSynType == "call"){
							tV = pkb->siblingTable->getStmtSiblingOfStmt(leftValue);
							for (std::set<int>::iterator it = tV.begin(); it!= tV.end();){
								if (rightSynType == "assign" || rightSynType == "while" || rightSynType == "if" || rightSynType == "call"){
									if (pkb->statementTable->getTNode(*it)->getNodeType()!=TNODE_NAMES[synToNodeType.at(rightSynType)]){
										tV.erase(it++);
									} else {
										++it;
									}
								} else {
									++it;
								}
							}
						}
					} else if (leftSynType == "variable"){
						if (rightSynType == "variable"){
							tV = pkb->siblingTable->getVarSiblingOfVar(leftValue);
						} else if (rightSynType == "stmtLst"){
							tV = pkb->siblingTable->getStmtLstSiblingOfVar(leftValue);
						} else if (rightSynType == "constant"){
							tV = pkb->siblingTable->getConstSiblingOfVar(leftValue);
						} else if (rightSynType == "plus"){
							tV = pkb->siblingTable->getPlusSiblingOfVar(leftValue);
						} else if (rightSynType == "minus"){
							tV = pkb->siblingTable->getMinusSiblingOfVar(leftValue);
						} else if (rightSynType == "times"){
							tV = pkb->siblingTable->getTimesSiblingOfVar(leftValue);
						}
					} else if (leftSynType == "constant"){
						if (rightSynType == "variable"){
							tV = pkb->siblingTable->getVarSiblingOfConst(leftValue);
						} else if (rightSynType == "constant"){
							tV = pkb->siblingTable->getConstSiblingOfConst(leftValue);
						} else if (rightSynType == "plus"){
							tV = pkb->siblingTable->getPlusSiblingOfConst(leftValue);
						} else if (rightSynType == "minus"){
							tV = pkb->siblingTable->getMinusSiblingOfConst(leftValue);
						} else if (rightSynType == "times"){
							tV = pkb->siblingTable->getTimesSiblingOfConst(leftValue);
						}
					} else if (leftSynType == "plus"){
						if (rightSynType == "variable"){
							tV = pkb->siblingTable->getVarSiblingOfPlus(leftValue);
						} else if (rightSynType == "constant"){
							tV = pkb->siblingTable->getConstSiblingOfPlus(leftValue);
						} else if (rightSynType == "plus"){
							tV = pkb->siblingTable->getPlusSiblingOfPlus(leftValue);
						} else if (rightSynType == "minus"){
							tV = pkb->siblingTable->getMinusSiblingOfPlus(leftValue);
						} else if (rightSynType == "times"){
							tV = pkb->siblingTable->getTimesSiblingOfPlus(leftValue);
						}
					} else if (leftSynType == "minus"){
						if (rightSynType == "variable"){
							tV = pkb->siblingTable->getVarSiblingOfMinus(leftValue);
						} else if (rightSynType == "constant"){
							tV = pkb->siblingTable->getConstSiblingOfMinus(leftValue);
						} else if (rightSynType == "plus"){
							tV = pkb->siblingTable->getPlusSiblingOfMinus(leftValue);
						} else if (rightSynType == "minus"){
							tV = pkb->siblingTable->getMinusSiblingOfMinus(leftValue);
						} else if (rightSynType == "times"){
							tV = pkb->siblingTable->getTimesSiblingOfMinus(leftValue);
						}
					} else if (leftSynType == "times"){
						if (rightSynType == "variable"){
							tV = pkb->siblingTable->getVarSiblingOfTimes(leftValue);
						} else if (rightSynType == "constant"){
							tV = pkb->siblingTable->getConstSiblingOfTimes(leftValue);
						} else if (rightSynType == "plus"){
							tV = pkb->siblingTable->getPlusSiblingOfTimes(leftValue);
						} else if (rightSynType == "minus"){
							tV = pkb->siblingTable->getMinusSiblingOfTimes(leftValue);
						} else if (rightSynType == "times"){
							tV = pkb->siblingTable->getTimesSiblingOfTimes(leftValue);
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

					if (rightSynType == "procedure" && leftSynType == "procedure"){
						tV = pkb->siblingTable->getProcsSiblingOfProc(rightValue);
					} else if (rightSynType == "stmtLst"){
						if (leftSynType == "stmtLst"){
							tV = pkb->siblingTable->getStmtLstSiblingOfStmtLst(rightValue);	
						} else if (leftSynType == "variable"){
							tV = pkb->siblingTable->getVarSiblingOfStmtLst(rightValue);
						}
					} else if (rightSynType == "stmt" || rightSynType == "prog_line" || rightSynType == "assign" 
						|| rightSynType == "while" || rightSynType == "if" || rightSynType == "call"){
						if (leftSynType == "stmt" || leftSynType == "prog_line" || leftSynType == "assign" 
						|| leftSynType == "while" || leftSynType == "if" || leftSynType == "call"){
							tV = pkb->siblingTable->getStmtSiblingOfStmt(rightValue);
							for (std::set<int>::iterator it = tV.begin(); it!= tV.end();){
								if (leftSynType == "assign" || leftSynType == "while" || leftSynType == "if" || leftSynType == "call"){
									if (pkb->statementTable->getTNode(*it)->getNodeType()!=TNODE_NAMES[synToNodeType.at(leftSynType)]){
										tV.erase(it++);
									} else {
										++it;
									}
								} else {
									++it;
								}
							}
						}
					} else if (rightSynType == "variable"){
						if (leftSynType == "variable"){
							tV = pkb->siblingTable->getVarSiblingOfVar(rightValue);
						} else if (leftSynType == "stmtLst"){
							tV = pkb->siblingTable->getStmtLstSiblingOfVar(rightValue);
						} else if (leftSynType == "constant"){
							tV = pkb->siblingTable->getConstSiblingOfVar(rightValue);
						} else if (leftSynType == "plus"){
							tV = pkb->siblingTable->getPlusSiblingOfVar(rightValue);
						} else if (leftSynType == "minus"){
							tV = pkb->siblingTable->getMinusSiblingOfVar(rightValue);
						} else if (leftSynType == "times"){
							tV = pkb->siblingTable->getTimesSiblingOfVar(rightValue);
						}
					} else if (rightSynType == "constant"){
						if (leftSynType == "variable"){
							tV = pkb->siblingTable->getVarSiblingOfConst(rightValue);
						} else if (leftSynType == "constant"){
							tV = pkb->siblingTable->getConstSiblingOfConst(rightValue);
						} else if (leftSynType == "plus"){
							tV = pkb->siblingTable->getPlusSiblingOfConst(rightValue);
						} else if (leftSynType == "minus"){
							tV = pkb->siblingTable->getMinusSiblingOfConst(rightValue);
						} else if (leftSynType == "times"){
							tV = pkb->siblingTable->getTimesSiblingOfConst(rightValue);
						}
					} else if (rightSynType == "plus"){
						if (leftSynType == "variable"){
							tV = pkb->siblingTable->getVarSiblingOfPlus(rightValue);
						} else if (leftSynType == "constant"){
							tV = pkb->siblingTable->getConstSiblingOfPlus(rightValue);
						} else if (leftSynType == "plus"){
							tV = pkb->siblingTable->getPlusSiblingOfPlus(rightValue);
						} else if (leftSynType == "minus"){
							tV = pkb->siblingTable->getMinusSiblingOfPlus(rightValue);
						} else if (leftSynType == "times"){
							tV = pkb->siblingTable->getTimesSiblingOfPlus(rightValue);
						}
					} else if (rightSynType == "minus"){
						if (leftSynType == "variable"){
							tV = pkb->siblingTable->getVarSiblingOfMinus(rightValue);
						} else if (leftSynType == "constant"){
							tV = pkb->siblingTable->getConstSiblingOfMinus(rightValue);
						} else if (leftSynType == "plus"){
							tV = pkb->siblingTable->getPlusSiblingOfMinus(rightValue);
						} else if (leftSynType == "minus"){
							tV = pkb->siblingTable->getMinusSiblingOfMinus(rightValue);
						} else if (leftSynType == "times"){
							tV = pkb->siblingTable->getTimesSiblingOfMinus(rightValue);
						}
					} else if (rightSynType == "times"){
						if (leftSynType == "variable"){
							tV = pkb->siblingTable->getVarSiblingOfTimes(rightValue);
						} else if (leftSynType == "constant"){
							tV = pkb->siblingTable->getConstSiblingOfTimes(rightValue);
						} else if (leftSynType == "plus"){
							tV = pkb->siblingTable->getPlusSiblingOfTimes(rightValue);
						} else if (leftSynType == "minus"){
							tV = pkb->siblingTable->getMinusSiblingOfTimes(rightValue);
						} else if (leftSynType == "times"){
							tV = pkb->siblingTable->getTimesSiblingOfTimes(rightValue);
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