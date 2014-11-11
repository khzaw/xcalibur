// File name: QueryEvaluator.cpp
#include <string>
#include <map>
#include "QueryTree.h"
#include "QTNode.h"
#include "PKB.h"
#include "PKBController.h"

//For Testing
#include "StatementTable.h"
#include "Follows.h"
#include "Parent.h"
#include "Modifies.h"
#include "Uses.h"
#include "ProcTable.h"
#include "VarTable.h"
#include "ConstantTable.h"

#include "QueryEvaluator.h"
#include <set>
#include <iostream>

using namespace std;

typedef string STRING;

/******* Constructors *******/
QueryEvaluator::QueryEvaluator(){
	pkb = new PKBController();
};

QueryEvaluator::QueryEvaluator(PKBController* newPKB){
	pkb = newPKB;
};

/******* Helper Level 4 *******/
bool QueryEvaluator::checkSynonymInSuchThat(string selectSynonym, QueryTree* suchThatTree){
	bool isSynonymInSuchThat = false;
	for (int i=0; i<suchThatTree->getRootNode()->getNumChild(); i++){
		if (selectSynonym == suchThatTree->getRootNode()->getChild(i)->getKey()){
			isSynonymInSuchThat = true;
			break;
		}
	}
	return isSynonymInSuchThat;
}

/******* Helper Level 3 *******/
vector<int> QueryEvaluator::solveForSelect(string selectSynonym, map<STRING, STRING>* synonymTable, StatementTable* statementTable, ProcTable* procTable, VarTable* varTable, ConstantTable* constantTable) {
	vector<int> answer;
	string sym = synonymTable->at(selectSynonym);
	if(sym == "stmt" || sym == "prog_line") {			     // all the statements
		answer = statementTable->getAllStmtNum();
	} else if(sym == "assign") {	// all the assignment statements
		answer = statementTable->getStmtNumUsingNodeType(TNODE_NAMES[ASSIGN_NODE]);
	} else if(sym == "while") {		// all the while statements
		answer = statementTable->getStmtNumUsingNodeType(TNODE_NAMES[WHILE_NODE]);
	} else if(sym == "variable") {
		answer = varTable->getAllVarNum();
	} else if(sym == "constant") {
		answer = constantTable->getAllConstNum();
	}	
	return answer;
}

vector<vector<int>> QueryEvaluator::solveForSuchThatModifies(map<STRING, STRING>* synonymTable, QueryTree* suchThatTree){
	vector<vector<int>> answer(2);
	synonymTable->insert(make_pair("_", "variable"));
	string leftSynonym = suchThatTree->getRootNode()->getChild(0)->getKey();
	string rightSynonym = suchThatTree->getRootNode()->getChild(1)->getKey();
	Modifies* modifies = &(pkb->modifiesTable);
	StatementTable* statementTable = &(pkb->statementTable);
	VarTable* varTable = &(pkb->varTable);
	if (rightSynonym.empty()){
		return answer;
	}
	if (leftSynonym.empty()&&synonymTable->find(rightSynonym) == synonymTable->end()){ // Follows(INDEX, NAME)
		int leftIndex = suchThatTree->getRootNode()->getChild(0)->getValue();
		if (rightSynonym.length()>=2){
			rightSynonym = rightSynonym.substr(1, rightSynonym.length()-2);
		}
		if (!varTable->containsVar(rightSynonym)){
			return answer;
		}
		int rightIndex = varTable->getVarIndex(rightSynonym);
		if (modifies->isModifiesStmt(leftIndex, rightIndex)){
			answer[0].push_back(leftIndex);
			answer[1].push_back(rightIndex);
			return answer;
		} else {
			return answer;
		}
	} else if (leftSynonym.empty()){ // Follows(INDEX, string)
		if (synonymTable->find(rightSynonym) == synonymTable->end()){ // string is not a synonym
			return answer;
		} else { // string is a synonym
			int leftIndex = suchThatTree->getRootNode()->getChild(0)->getValue();
			vector<int> temp = modifies->getModifiedVarStmt(leftIndex);
			if (synonymTable->at(rightSynonym)=="variable"){
				for (size_t i = 0; i<temp.size(); i++){
					answer[0].push_back(leftIndex);
					answer[1].push_back(temp[i]);
				}
			} else {

			}
			return answer;
		}		
	} else if (synonymTable->find(rightSynonym) == synonymTable->end()){ // Follows(string, NAME)
		if (rightSynonym.length()>=2){
			rightSynonym = rightSynonym.substr(1, rightSynonym.length()-2);
		}
		if (synonymTable->find(leftSynonym) == synonymTable->end()){ // string is not a synonym
			return answer;
		} else if (!varTable->containsVar(rightSynonym)){
			return answer;
		} else { // string is a synonym
			int rightIndex = varTable->getVarIndex(rightSynonym);
			vector<int> temp = modifies->getModifiersStmt(rightIndex);
			if (synonymTable->at(leftSynonym)=="stmt"||synonymTable->at(leftSynonym)=="prog_line"){
				for (size_t i = 0; i<temp.size(); i++){
					answer[0].push_back(temp[i]);
					answer[1].push_back(rightIndex);
				}
			} else if (synonymTable->at(leftSynonym)=="assign"){
				for (size_t i=0; i<temp.size(); i++){
					if (statementTable->getTNode(temp[i])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
						answer[0].push_back(temp[i]);
						answer[1].push_back(rightIndex);
					}
				}
			} else if (synonymTable->at(leftSynonym)=="while"){
				for (size_t i=0; i<temp.size(); i++){
					if (statementTable->getTNode(temp[i])->getNodeType()==TNODE_NAMES[WHILE_NODE]){
						answer[0].push_back(temp[i]);
						answer[1].push_back(rightIndex);	
					}
				}
			} else if (synonymTable->at(leftSynonym)=="if"){
				// not implemented
			} else {

			}
			return answer;
		}		
	} else { // Follows(string, string)
		if (synonymTable->find(leftSynonym) == synonymTable->end()){
			return answer;
		} else {
			if (synonymTable->at(rightSynonym) != "variable"){
				return answer;
			} else {
				vector<int> vars = varTable->getAllVarNum();
				if (synonymTable->at(leftSynonym)=="stmt"||synonymTable->at(leftSynonym)=="prog_line"){
					for (size_t i=0; i<vars.size(); i++){
						vector<int> temp = modifies->getModifiersStmt(vars[i]);
						for (size_t j=0; j<temp.size(); j++){
							answer[0].push_back(temp[j]);
							answer[1].push_back(vars[i]);
						}
					}
				} else if (synonymTable->at(leftSynonym)=="assign"){
					for (size_t i=0; i<vars.size(); i++){
						vector<int> temp = modifies->getModifiersStmt(vars[i]);
						for (size_t j=0; j<temp.size(); j++){
							if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
								answer[0].push_back(temp[j]);
								answer[1].push_back(vars[i]);
							}
						}
					}
				} else if (synonymTable->at(rightSynonym)=="while"){
					for (size_t i=0; i<vars.size(); i++){
						vector<int> temp = modifies->getModifiersStmt(vars[i]);
						for (size_t j=0; j<temp.size(); j++){
							if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[WHILE_NODE]){
								answer[0].push_back(temp[j]);
								answer[1].push_back(vars[i]);
							}
						}
					}
				} else if (synonymTable->at(rightSynonym)=="if"){
					// not implemented
				} else {
					// not valid
				}
			}
		}
	}
	return answer;
}

vector<vector<int>> QueryEvaluator::solveForSuchThatUses(map<STRING, STRING>* synonymTable, QueryTree* suchThatTree){
	vector<vector<int>> answer(2);
	synonymTable->insert(make_pair("_", "variable"));
	string leftSynonym = suchThatTree->getRootNode()->getChild(0)->getKey();
	string rightSynonym = suchThatTree->getRootNode()->getChild(1)->getKey();
	Uses* uses = &(pkb->usesTable);
	StatementTable* statementTable = &(pkb->statementTable);
	VarTable* varTable = &(pkb->varTable);
	if (rightSynonym.empty()){
		return answer;
	}
	if (leftSynonym.empty()&&synonymTable->find(rightSynonym) == synonymTable->end()){ // Follows(INDEX, NAME)
		int leftIndex = suchThatTree->getRootNode()->getChild(0)->getValue();
		if (rightSynonym.length()>=2){
			rightSynonym = rightSynonym.substr(1, rightSynonym.length()-2);
		}
		if (!varTable->containsVar(rightSynonym)){
			return answer;
		}
		int rightIndex = varTable->getVarIndex(rightSynonym);
		if (uses->isUsesStmt(leftIndex, rightIndex)){
			answer[0].push_back(leftIndex);
			answer[1].push_back(rightIndex);
			return answer;
		} else {
			return answer;
		}
	} else if (leftSynonym.empty()){ // Follows(INDEX, string)
		if (synonymTable->find(rightSynonym) == synonymTable->end()){ // string is not a synonym
			return answer;
		} else { // string is a synonym
			int leftIndex = suchThatTree->getRootNode()->getChild(0)->getValue();
			vector<int> temp = uses->getUsedVarStmt(leftIndex);
			if (synonymTable->at(rightSynonym)=="variable"){
				for (size_t i = 0; i<temp.size(); i++){
					answer[0].push_back(leftIndex);
					answer[1].push_back(temp[i]);
				}
			} else {

			}
			return answer;
		}		
	} else if (synonymTable->find(rightSynonym) == synonymTable->end()){ // Follows(string, NAME)
		if (rightSynonym.length()>=2){
			rightSynonym = rightSynonym.substr(1, rightSynonym.length()-2);
		}
		if (synonymTable->find(leftSynonym) == synonymTable->end()){ // string is not a synonym
			return answer;
		} else if (!varTable->containsVar(rightSynonym)){
			return answer;
		} else { // string is a synonym
			int rightIndex = varTable->getVarIndex(rightSynonym);
			vector<int> temp = uses->getUsersStmt(rightIndex);
			if (synonymTable->at(leftSynonym)=="stmt"||synonymTable->at(leftSynonym)=="prog_line"){
				for (size_t i = 0; i<temp.size(); i++){
					answer[0].push_back(temp[i]);
					answer[1].push_back(rightIndex);
				}
			} else if (synonymTable->at(leftSynonym)=="assign"){
				for (size_t i=0; i<temp.size(); i++){
					if (statementTable->getTNode(temp[i])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
						answer[0].push_back(temp[i]);
						answer[1].push_back(rightIndex);
					}
				}
			} else if (synonymTable->at(leftSynonym)=="while"){
				for (size_t i=0; i<temp.size(); i++){
					if (statementTable->getTNode(temp[i])->getNodeType()==TNODE_NAMES[WHILE_NODE]){
						answer[0].push_back(temp[i]);
						answer[1].push_back(rightIndex);	
					}
				}
			} else if (synonymTable->at(leftSynonym)=="if"){
				// not implemented
			} else {

			}
			return answer;
		}		
	} else { // Follows(string, string)
		if (synonymTable->find(leftSynonym) == synonymTable->end()){
			return answer;
		} else {
			if (synonymTable->at(rightSynonym) != "variable"){
				return answer;
			} else {
				vector<int> vars = varTable->getAllVarNum();
				if (synonymTable->at(leftSynonym)=="stmt"||synonymTable->at(leftSynonym)=="prog_line"){
					for (size_t i=0; i<vars.size(); i++){
						vector<int> temp = uses->getUsersStmt(vars[i]);
						for (size_t j=0; j<temp.size(); j++){
							answer[0].push_back(temp[j]);
							answer[1].push_back(vars[i]);
						}
					}
				} else if (synonymTable->at(leftSynonym)=="assign"){
					for (size_t i=0; i<vars.size(); i++){
						vector<int> temp = uses->getUsersStmt(vars[i]);
						for (size_t j=0; j<temp.size(); j++){
							if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
								answer[0].push_back(temp[j]);
								answer[1].push_back(vars[i]);
							}
						}
					}
				} else if (synonymTable->at(rightSynonym)=="while"){
					for (size_t i=0; i<vars.size(); i++){
						vector<int> temp = uses->getUsersStmt(vars[i]);
						for (size_t j=0; j<temp.size(); j++){
							if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[WHILE_NODE]){
								answer[0].push_back(temp[j]);
								answer[1].push_back(vars[i]);
							}
						}
					}
				} else if (synonymTable->at(rightSynonym)=="if"){
					// not implemented
				} else {
					// not valid
				}
			}
		}
	}
	return answer;
}

vector<vector<int>> QueryEvaluator::solveForSuchThatFollows(map<STRING, STRING>* synonymTable, QueryTree* suchThatTree){
	vector<vector<int>> answer(2);
	synonymTable->insert(make_pair("_", "stmt"));
	string leftSynonym = suchThatTree->getRootNode()->getChild(0)->getKey();
	string rightSynonym = suchThatTree->getRootNode()->getChild(1)->getKey();
	Follows* follows = &(pkb->followsTable);
	StatementTable* statementTable = &(pkb->statementTable);
	if (leftSynonym.empty()&&rightSynonym.empty()){ // Follows(INDEX, INDEX)
		int leftIndex = suchThatTree->getRootNode()->getChild(0)->getValue();
		int rightIndex = suchThatTree->getRootNode()->getChild(1)->getValue();
		if (follows->isFollowsTrue(leftIndex, rightIndex)){
			answer[0].push_back(leftIndex);
			answer[1].push_back(rightIndex);
			return answer;
		} else {
			return answer;
		}
	} else if (leftSynonym.empty()){ // Follows(INDEX, string)
		if (synonymTable->find(rightSynonym) == synonymTable->end()){ // string is not a synonym
			return answer;
		} else { // string is a synonym
			int leftIndex = suchThatTree->getRootNode()->getChild(0)->getValue();
			vector<int> temp = follows->getFollowers(leftIndex);
			if (synonymTable->at(rightSynonym)=="stmt"||synonymTable->at(rightSynonym)=="prog_line"){
				for (size_t i = 0; i<temp.size(); i++){
					answer[0].push_back(leftIndex);
					answer[1].push_back(temp[i]);
				}
			} else if (synonymTable->at(rightSynonym)=="assign"){
				for (size_t i=0; i<temp.size(); i++){
					if (statementTable->getTNode(temp[i])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
						answer[0].push_back(leftIndex);
						answer[1].push_back(temp[i]);
					}
				}
			} else if (synonymTable->at(rightSynonym)=="while"){
				for (size_t i=0; i<temp.size(); i++){
					if (statementTable->getTNode(temp[i])->getNodeType()==TNODE_NAMES[WHILE_NODE]){
						answer[0].push_back(leftIndex);
						answer[1].push_back(temp[i]);
					}
				}
			} else if (synonymTable->at(rightSynonym)=="if"){
				// not implemented
			} else {

			}
			return answer;
		}		
	} else if (rightSynonym.empty()){ // Follows(string, INDEX)
		if (synonymTable->find(leftSynonym) == synonymTable->end()){ // string is not a synonym
			return answer;
		} else { // string is a synonym
			int rightIndex = suchThatTree->getRootNode()->getChild(1)->getValue();
			vector<int> temp = follows->getFollowees(rightIndex);
			if (synonymTable->at(leftSynonym)=="stmt"||synonymTable->at(leftSynonym)=="prog_line"){
				for (size_t i = 0; i<temp.size(); i++){
					answer[0].push_back(temp[i]);
					answer[1].push_back(rightIndex);
				}
			} else if (synonymTable->at(leftSynonym)=="assign"){
				for (size_t i=0; i<temp.size(); i++){
					if (statementTable->getTNode(temp[i])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
						answer[0].push_back(temp[i]);
						answer[1].push_back(rightIndex);
					}
				}
			} else if (synonymTable->at(leftSynonym)=="while"){
				for (size_t i=0; i<temp.size(); i++){
					if (statementTable->getTNode(temp[i])->getNodeType()==TNODE_NAMES[WHILE_NODE]){
						answer[0].push_back(temp[i]);
						answer[1].push_back(rightIndex);	
					}
				}
			} else if (synonymTable->at(leftSynonym)=="if"){
				// not implemented
			} else {

			}
			return answer;
		}		
	} else { // Follows(string, string)
		if (synonymTable->find(leftSynonym) == synonymTable->end()||synonymTable->find(rightSynonym) == synonymTable->end()){
			return answer;
		} else if (leftSynonym==rightSynonym){
			return answer;
		}  else {
			if (synonymTable->at(leftSynonym)=="stmt"||synonymTable->at(leftSynonym)=="prog_line"){
				if (synonymTable->at(rightSynonym)=="stmt"||synonymTable->at(rightSynonym)=="prog_line"){
					for (size_t i=1; i<=statementTable->getSize(); i++){
						vector<int> temp = follows->getFollowers(i);
						for (size_t j=0; j<temp.size(); j++){
							answer[0].push_back(i);
							answer[1].push_back(temp[j]);
						}
					}
				} else if (synonymTable->at(rightSynonym)=="assign"){
					for (size_t i=1; i<=statementTable->getSize(); i++){
						vector<int> temp = follows->getFollowers(i);
						for (size_t j=0; j<temp.size(); j++){
							if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
								answer[0].push_back(i);
								answer[1].push_back(temp[j]);
							}
						}
					}
				} else if (synonymTable->at(rightSynonym)=="while"){
					for (int i=1; i<=statementTable->getSize(); i++){
						vector<int> temp = follows->getFollowers(i);
						for (size_t j=0; j<temp.size(); j++){
							if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[WHILE_NODE]){
								answer[0].push_back(i);
								answer[1].push_back(temp[j]);
							}
						}
					}
				} else if (synonymTable->at(rightSynonym)=="if"){
					// not implemented
				} else {
					// not valid
				}
			} else if (synonymTable->at(leftSynonym)=="assign"){
				if (synonymTable->at(rightSynonym)=="stmt"||synonymTable->at(rightSynonym)=="prog_line"){
					for (size_t i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
							vector<int> temp = follows->getFollowers(i);
							for (size_t j=0; j<temp.size(); j++){
								answer[0].push_back(i);
								answer[1].push_back(temp[j]);
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="assign"){
					for (size_t i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
							vector<int> temp = follows->getFollowers(i);
							for (size_t j=0; j<temp.size(); j++){
								if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
									answer[0].push_back(i);
									answer[1].push_back(temp[j]);
								}
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="while"){
					for (size_t i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
							vector<int> temp = follows->getFollowers(i);
							for (size_t j=0; j<temp.size(); j++){
								if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[WHILE_NODE]){
									answer[0].push_back(i);
									answer[1].push_back(temp[j]);
								}
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="if"){
					// not implemented
				} else {
					// none				
				}
			} else if (synonymTable->at(leftSynonym)=="while"){
				if (synonymTable->at(rightSynonym)=="stmt"||synonymTable->at(rightSynonym)=="prog_line"){
					for (size_t i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[WHILE_NODE]){
							vector<int> temp = follows->getFollowers(i);
							for (size_t j=0; j<temp.size(); j++){
								answer[0].push_back(i);
								answer[1].push_back(temp[j]);
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="assign"){
					for (size_t i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[WHILE_NODE]){
							vector<int> temp = follows->getFollowers(i);
							for (size_t j=0; j<temp.size(); j++){
								if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
									answer[0].push_back(i);
									answer[1].push_back(temp[j]);
								}
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="while"){
					for (size_t i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[WHILE_NODE]){
							vector<int> temp = follows->getFollowers(i);
							for (size_t j=0; j<temp.size(); j++){
								if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[WHILE_NODE]){
									answer[0].push_back(i);
									answer[1].push_back(temp[j]);
								}
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="if"){
					// not implemented
				} else {
					// none				
				}
			} else if (synonymTable->at(leftSynonym)=="if"){
				// not implemented
			} else {
				// not valid
			}
			return answer;
		}
	}
	return answer;
}

vector<vector<int>> QueryEvaluator::solveForSuchThatFollowsStar(map<STRING, STRING>* synonymTable, QueryTree* suchThatTree){
	vector<vector<int>> answer(2);	
	synonymTable->insert(make_pair("_", "stmt"));
	string leftSynonym = suchThatTree->getRootNode()->getChild(0)->getKey();
	string rightSynonym = suchThatTree->getRootNode()->getChild(1)->getKey();
	Follows* follows = &(pkb->followsTable);
	StatementTable* statementTable = &(pkb->statementTable);
	if (leftSynonym.empty()&&rightSynonym.empty()){ // Follows*(INDEX, INDEX)
		int leftIndex = suchThatTree->getRootNode()->getChild(0)->getValue();
		int rightIndex = suchThatTree->getRootNode()->getChild(1)->getValue();
		if (follows->isFollowsStarTrue(leftIndex, rightIndex)){
			answer[0].push_back(leftIndex);
			answer[1].push_back(rightIndex);
			return answer;
		} else {
			return answer;
		}
	} else if (leftSynonym.empty()){ // Follows*(INDEX, string)
		if (synonymTable->find(rightSynonym) == synonymTable->end()){ // string is not a synonym
			return answer;
		} else { // string is a synonym
			int leftIndex = suchThatTree->getRootNode()->getChild(0)->getValue();
			vector<int> temp = follows->getFollowersStar(leftIndex);
			if (synonymTable->at(rightSynonym)=="stmt"||synonymTable->at(rightSynonym)=="prog_line"){
				for (size_t i = 0; i<temp.size(); i++){
					answer[0].push_back(leftIndex);
					answer[1].push_back(temp[i]);
				}
			} else if (synonymTable->at(rightSynonym)=="assign"){
				for (size_t i=0; i<temp.size(); i++){
					if (statementTable->getTNode(temp[i])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
						answer[0].push_back(leftIndex);
						answer[1].push_back(temp[i]);
					}
				}
			} else if (synonymTable->at(rightSynonym)=="while"){
				for (size_t i=0; i<temp.size(); i++){
					if (statementTable->getTNode(temp[i])->getNodeType()==TNODE_NAMES[WHILE_NODE]){
						answer[0].push_back(leftIndex);
						answer[1].push_back(temp[i]);
					}
				}
			} else if (synonymTable->at(rightSynonym)=="if"){
				// not implemented
			} else {

			}
			return answer;
		}		
	} else if (rightSynonym.empty()){ // Follows*(string, INDEX)
		if (synonymTable->find(leftSynonym) == synonymTable->end()){ // string is not a synonym
			return answer;
		} else { // string is a synonym
			int rightIndex = suchThatTree->getRootNode()->getChild(1)->getValue();
			vector<int> temp = follows->getFolloweesStar(rightIndex);
			if (synonymTable->at(leftSynonym)=="stmt"||synonymTable->at(leftSynonym)=="prog_line"){
				for (size_t i = 0; i<temp.size(); i++){
					answer[0].push_back(temp[i]);
					answer[1].push_back(rightIndex);
				}
			} else if (synonymTable->at(leftSynonym)=="assign"){
				for (size_t i=0; i<temp.size(); i++){
					if (statementTable->getTNode(temp[i])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
						answer[0].push_back(temp[i]);
						answer[1].push_back(rightIndex);
					}
				}
			} else if (synonymTable->at(leftSynonym)=="while"){
				for (size_t i=0; i<temp.size(); i++){
					if (statementTable->getTNode(temp[i])->getNodeType()==TNODE_NAMES[WHILE_NODE]){
						answer[0].push_back(temp[i]);
						answer[1].push_back(rightIndex);	
					}
				}
			} else if (synonymTable->at(leftSynonym)=="if"){
				// not implemented
			} else {

			}
			return answer;
		}		
	} else { // Follows*(string, string)
		if (synonymTable->find(leftSynonym) == synonymTable->end()||synonymTable->find(rightSynonym) == synonymTable->end()){
			return answer;
		} else if (leftSynonym==rightSynonym){
			return answer;
		}  else {
			if (synonymTable->at(leftSynonym)=="stmt"||synonymTable->at(leftSynonym)=="prog_line"){
				if (synonymTable->at(rightSynonym)=="stmt"||synonymTable->at(rightSynonym)=="prog_line"){
					for (size_t i=1; i<=statementTable->getSize(); i++){
						vector<int> temp = follows->getFollowersStar(i);
						for (size_t j=0; j<temp.size(); j++){
							answer[0].push_back(i);
							answer[1].push_back(temp[j]);
						}
					}
				} else if (synonymTable->at(rightSynonym)=="assign"){
					for (size_t i=1; i<=statementTable->getSize(); i++){
						vector<int> temp = follows->getFollowersStar(i);
						for (size_t j=0; j<temp.size(); j++){
							if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
								answer[0].push_back(i);
								answer[1].push_back(temp[j]);
							}
						}
					}
				} else if (synonymTable->at(rightSynonym)=="while"){
					for (int i=1; i<=statementTable->getSize(); i++){
						vector<int> temp = follows->getFollowersStar(i);
						for (size_t j=0; j<temp.size(); j++){
							if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[WHILE_NODE]){
								answer[0].push_back(i);
								answer[1].push_back(temp[j]);
							}
						}
					}
				} else if (synonymTable->at(rightSynonym)=="if"){
					// not implemented
				} else {
					// not valid
				}
			} else if (synonymTable->at(leftSynonym)=="assign"){
				if (synonymTable->at(rightSynonym)=="stmt"||synonymTable->at(rightSynonym)=="prog_line"){
					for (size_t i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
							vector<int> temp = follows->getFollowersStar(i);
							for (size_t j=0; j<temp.size(); j++){
								answer[0].push_back(i);
								answer[1].push_back(temp[j]);
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="assign"){
					for (size_t i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
							vector<int> temp = follows->getFollowersStar(i);
							for (size_t j=0; j<temp.size(); j++){
								if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
									answer[0].push_back(i);
									answer[1].push_back(temp[j]);
								}
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="while"){
					for (size_t i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
							vector<int> temp = follows->getFollowersStar(i);
							for (size_t j=0; j<temp.size(); j++){
								if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[WHILE_NODE]){
									answer[0].push_back(i);
									answer[1].push_back(temp[j]);
								}
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="if"){
					// not implemented
				} else {
					// none				
				}
			} else if (synonymTable->at(leftSynonym)=="while"){
				if (synonymTable->at(rightSynonym)=="stmt"||synonymTable->at(rightSynonym)=="prog_line"){
					for (size_t i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[WHILE_NODE]){
							vector<int> temp = follows->getFollowersStar(i);
							for (size_t j=0; j<temp.size(); j++){
								answer[0].push_back(i);
								answer[1].push_back(temp[j]);
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="assign"){
					for (size_t i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[WHILE_NODE]){
							vector<int> temp = follows->getFollowersStar(i);
							for (size_t j=0; j<temp.size(); j++){
								if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
									answer[0].push_back(i);
									answer[1].push_back(temp[j]);
								}
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="while"){
					for (size_t i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[WHILE_NODE]){
							vector<int> temp = follows->getFollowersStar(i);
							for (size_t j=0; j<temp.size(); j++){
								if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[WHILE_NODE]){
									answer[0].push_back(i);
									answer[1].push_back(temp[j]);
								}
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="if"){
					// not implemented
				} else {
					// none				
				}
			} else if (synonymTable->at(leftSynonym)=="if"){
				// not implemented
			} else {
				// not valid
			}
			return answer;
		}
	}
	return answer;
}

vector<vector<int>> QueryEvaluator::solveForSuchThatParent(map<STRING, STRING>* synonymTable, QueryTree* suchThatTree){
	vector<vector<int>> answer(2);
	synonymTable->insert(make_pair("_", "stmt"));
	string leftSynonym = suchThatTree->getRootNode()->getChild(0)->getKey();
	string rightSynonym = suchThatTree->getRootNode()->getChild(1)->getKey();
	Parent* parent = &(pkb->parentTable);
	StatementTable* statementTable = &(pkb->statementTable);
	if (leftSynonym.empty()&&rightSynonym.empty()){ // Parent(INDEX, INDEX)
		int leftIndex = suchThatTree->getRootNode()->getChild(0)->getValue();
		int rightIndex = suchThatTree->getRootNode()->getChild(1)->getValue();
		if (parent->isParentTrue(leftIndex, rightIndex)){
			answer[0].push_back(leftIndex);
			answer[1].push_back(rightIndex);
			return answer;
		} else {
			return answer;
		}
	} else if (leftSynonym.empty()){ // Parent(INDEX, string)
		if (synonymTable->find(rightSynonym) == synonymTable->end()){ // string is not a synonym
			return answer;
		} else { // string is a synonym
			int leftIndex = suchThatTree->getRootNode()->getChild(0)->getValue();
			vector<int> temp = parent->getChildren(leftIndex);
			if (synonymTable->at(rightSynonym)=="stmt"||synonymTable->at(rightSynonym)=="prog_line"){
				for (size_t i = 0; i<temp.size(); i++){
					answer[0].push_back(leftIndex);
					answer[1].push_back(temp[i]);
				}
			} else if (synonymTable->at(rightSynonym)=="assign"){
				for (size_t i=0; i<temp.size(); i++){
					if (statementTable->getTNode(temp[i])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
						answer[0].push_back(leftIndex);
						answer[1].push_back(temp[i]);
					}
				}
			} else if (synonymTable->at(rightSynonym)=="while"){
				for (size_t i=0; i<temp.size(); i++){
					if (statementTable->getTNode(temp[i])->getNodeType()==TNODE_NAMES[WHILE_NODE]){
						answer[0].push_back(leftIndex);
						answer[1].push_back(temp[i]);
					}
				}
			} else if (synonymTable->at(rightSynonym)=="if"){
				// not implemented
			} else {

			}
			return answer;
		}		
	} else if (rightSynonym.empty()){ // Parent(string, INDEX)
		if (synonymTable->find(leftSynonym) == synonymTable->end()){ // string is not a synonym
			return answer;
		} else { // string is a synonym
			int rightIndex = suchThatTree->getRootNode()->getChild(1)->getValue();
			vector<int> temp = parent->getParents(rightIndex);
			if (synonymTable->at(leftSynonym)=="stmt"||synonymTable->at(leftSynonym)=="prog_line"){
				for (size_t i = 0; i<temp.size(); i++){
					answer[0].push_back(temp[i]);
					answer[1].push_back(rightIndex);
				}
			} else if (synonymTable->at(leftSynonym)=="assign"){
				for (size_t i=0; i<temp.size(); i++){
					if (statementTable->getTNode(temp[i])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
						answer[0].push_back(temp[i]);
						answer[1].push_back(rightIndex);
					}
				}
			} else if (synonymTable->at(leftSynonym)=="while"){
				for (size_t i=0; i<temp.size(); i++){
					if (statementTable->getTNode(temp[i])->getNodeType()==TNODE_NAMES[WHILE_NODE]){
						answer[0].push_back(temp[i]);
						answer[1].push_back(rightIndex);	
					}
				}
			} else if (synonymTable->at(leftSynonym)=="if"){
				// not implemented
			} else {

			}
			return answer;
		}		
	} else { // Parent(string, string)
		if (synonymTable->find(leftSynonym) == synonymTable->end()||synonymTable->find(rightSynonym) == synonymTable->end()){
			return answer;
		} else if (leftSynonym==rightSynonym){
			return answer;
		}  else {
			if (synonymTable->at(leftSynonym)=="stmt"||synonymTable->at(leftSynonym)=="prog_line"){
				if (synonymTable->at(rightSynonym)=="stmt"||synonymTable->at(rightSynonym)=="prog_line"){
					for (size_t i=1; i<=statementTable->getSize(); i++){
						vector<int> temp = parent->getChildren(i);
						for (size_t j=0; j<temp.size(); j++){
							answer[0].push_back(i);
							answer[1].push_back(temp[j]);
						}
					}
				} else if (synonymTable->at(rightSynonym)=="assign"){
					for (size_t i=1; i<=statementTable->getSize(); i++){
						vector<int> temp = parent->getChildren(i);
						for (size_t j=0; j<temp.size(); j++){
							if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
								answer[0].push_back(i);
								answer[1].push_back(temp[j]);
							}
						}
					}
				} else if (synonymTable->at(rightSynonym)=="while"){
					for (int i=1; i<=statementTable->getSize(); i++){
						vector<int> temp = parent->getChildren(i);
						for (size_t j=0; j<temp.size(); j++){
							if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[WHILE_NODE]){
								answer[0].push_back(i);
								answer[1].push_back(temp[j]);
							}
						}
					}
				} else if (synonymTable->at(rightSynonym)=="if"){
					// not implemented
				} else {
					// not valid
				}
			} else if (synonymTable->at(leftSynonym)=="assign"){
				if (synonymTable->at(rightSynonym)=="stmt"||synonymTable->at(rightSynonym)=="prog_line"){
					for (size_t i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
							vector<int> temp = parent->getChildren(i);
							for (size_t j=0; j<temp.size(); j++){
								answer[0].push_back(i);
								answer[1].push_back(temp[j]);
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="assign"){
					for (size_t i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
							vector<int> temp = parent->getChildren(i);
							for (size_t j=0; j<temp.size(); j++){
								if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
									answer[0].push_back(i);
									answer[1].push_back(temp[j]);
								}
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="while"){
					for (size_t i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
							vector<int> temp = parent->getChildren(i);
							for (size_t j=0; j<temp.size(); j++){
								if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[WHILE_NODE]){
									answer[0].push_back(i);
									answer[1].push_back(temp[j]);
								}
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="if"){
					// not implemented
				} else {
					// none				
				}
			} else if (synonymTable->at(leftSynonym)=="while"){
				if (synonymTable->at(rightSynonym)=="stmt"||synonymTable->at(rightSynonym)=="prog_line"){
					for (size_t i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[WHILE_NODE]){
							vector<int> temp = parent->getChildren(i);
							for (size_t j=0; j<temp.size(); j++){
								answer[0].push_back(i);
								answer[1].push_back(temp[j]);
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="assign"){
					for (size_t i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[WHILE_NODE]){
							vector<int> temp = parent->getChildren(i);
							for (size_t j=0; j<temp.size(); j++){
								if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
									answer[0].push_back(i);
									answer[1].push_back(temp[j]);
								}
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="while"){
					for (size_t i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[WHILE_NODE]){
							vector<int> temp = parent->getChildren(i);
							for (size_t j=0; j<temp.size(); j++){
								if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[WHILE_NODE]){
									answer[0].push_back(i);
									answer[1].push_back(temp[j]);
								}
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="if"){
					// not implemented
				} else {
					// none				
				}
			} else if (synonymTable->at(leftSynonym)=="if"){
				// not implemented
			} else {
				// not valid
			}
			return answer;
		}
	}
	return answer;
}

vector<vector<int>> QueryEvaluator::solveForSuchThatParentStar(map<STRING, STRING>* synonymTable, QueryTree* suchThatTree){
	vector<vector<int>> answer(2);
	synonymTable->insert(make_pair("_", "stmt"));
	string leftSynonym = suchThatTree->getRootNode()->getChild(0)->getKey();
	string rightSynonym = suchThatTree->getRootNode()->getChild(1)->getKey();
	Parent* parent = &(pkb->parentTable);
	StatementTable* statementTable = &(pkb->statementTable);
	if (leftSynonym.empty()&&rightSynonym.empty()){ // Parent*(INDEX, INDEX)
		int leftIndex = suchThatTree->getRootNode()->getChild(0)->getValue();
		int rightIndex = suchThatTree->getRootNode()->getChild(1)->getValue();
		if (parent->isParentStarTrue(leftIndex, rightIndex)){
			answer[0].push_back(leftIndex);
			answer[1].push_back(rightIndex);
			return answer;
		} else {
			return answer;
		}
	} else if (leftSynonym.empty()){ // Parent*(INDEX, string)
		if (synonymTable->find(rightSynonym) == synonymTable->end()){ // string is not a synonym
			return answer;
		} else { // string is a synonym
			int leftIndex = suchThatTree->getRootNode()->getChild(0)->getValue();
			vector<int> temp = parent->getChildrenStar(leftIndex);
			if (synonymTable->at(rightSynonym)=="stmt"||synonymTable->at(rightSynonym)=="prog_line"){
				for (size_t i = 0; i<temp.size(); i++){
					answer[0].push_back(leftIndex);
					answer[1].push_back(temp[i]);
				}
			} else if (synonymTable->at(rightSynonym)=="assign"){
				for (size_t i=0; i<temp.size(); i++){
					if (statementTable->getTNode(temp[i])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
						answer[0].push_back(leftIndex);
						answer[1].push_back(temp[i]);
					}
				}
			} else if (synonymTable->at(rightSynonym)=="while"){
				for (size_t i=0; i<temp.size(); i++){
					if (statementTable->getTNode(temp[i])->getNodeType()==TNODE_NAMES[WHILE_NODE]){
						answer[0].push_back(leftIndex);
						answer[1].push_back(temp[i]);
					}
				}
			} else if (synonymTable->at(rightSynonym)=="if"){
				// not implemented
			} else {

			}
			return answer;
		}		
	} else if (rightSynonym.empty()){ // Parent*(string, INDEX)
		if (synonymTable->find(leftSynonym) == synonymTable->end()){ // string is not a synonym
			return answer;
		} else { // string is a synonym
			int rightIndex = suchThatTree->getRootNode()->getChild(1)->getValue();
			vector<int> temp = parent->getParentStar(rightIndex);
			if (synonymTable->at(leftSynonym)=="stmt"||synonymTable->at(leftSynonym)=="prog_line"){
				for (size_t i = 0; i<temp.size(); i++){
					answer[0].push_back(temp[i]);
					answer[1].push_back(rightIndex);
				}
			} else if (synonymTable->at(leftSynonym)=="assign"){
				for (size_t i=0; i<temp.size(); i++){
					if (statementTable->getTNode(temp[i])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
						answer[0].push_back(temp[i]);
						answer[1].push_back(rightIndex);
					}
				}
			} else if (synonymTable->at(leftSynonym)=="while"){
				for (size_t i=0; i<temp.size(); i++){
					if (statementTable->getTNode(temp[i])->getNodeType()==TNODE_NAMES[WHILE_NODE]){
						answer[0].push_back(temp[i]);
						answer[1].push_back(rightIndex);	
					}
				}
			} else if (synonymTable->at(leftSynonym)=="if"){
				// not implemented
			} else {

			}
			return answer;
		}		
	} else { // Parent*(string, string)
		if (synonymTable->find(leftSynonym) == synonymTable->end()||synonymTable->find(rightSynonym) == synonymTable->end()){
			return answer;
		} else if (leftSynonym==rightSynonym){
			return answer;
		}  else {
			if (synonymTable->at(leftSynonym)=="stmt"||synonymTable->at(leftSynonym)=="prog_line"){
				if (synonymTable->at(rightSynonym)=="stmt"||synonymTable->at(rightSynonym)=="prog_line"){
					for (size_t i=1; i<=statementTable->getSize(); i++){
						vector<int> temp = parent->getChildrenStar(i);
						for (size_t j=0; j<temp.size(); j++){
							answer[0].push_back(i);
							answer[1].push_back(temp[j]);
						}
					}
				} else if (synonymTable->at(rightSynonym)=="assign"){
					for (size_t i=1; i<=statementTable->getSize(); i++){
						vector<int> temp = parent->getChildrenStar(i);
						for (size_t j=0; j<temp.size(); j++){
							if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
								answer[0].push_back(i);
								answer[1].push_back(temp[j]);
							}
						}
					}
				} else if (synonymTable->at(rightSynonym)=="while"){
					for (int i=1; i<=statementTable->getSize(); i++){
						vector<int> temp = parent->getChildrenStar(i);
						for (size_t j=0; j<temp.size(); j++){
							if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[WHILE_NODE]){
								answer[0].push_back(i);
								answer[1].push_back(temp[j]);
							}
						}
					}
				} else if (synonymTable->at(rightSynonym)=="if"){
					// not implemented
				} else {
					// not valid
				}
			} else if (synonymTable->at(leftSynonym)=="assign"){
				if (synonymTable->at(rightSynonym)=="stmt"||synonymTable->at(rightSynonym)=="prog_line"){
					for (size_t i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
							vector<int> temp = parent->getChildrenStar(i);
							for (size_t j=0; j<temp.size(); j++){
								answer[0].push_back(i);
								answer[1].push_back(temp[j]);
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="assign"){
					for (size_t i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
							vector<int> temp = parent->getChildrenStar(i);
							for (size_t j=0; j<temp.size(); j++){
								if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
									answer[0].push_back(i);
									answer[1].push_back(temp[j]);
								}
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="while"){
					for (size_t i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
							vector<int> temp = parent->getChildrenStar(i);
							for (size_t j=0; j<temp.size(); j++){
								if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[WHILE_NODE]){
									answer[0].push_back(i);
									answer[1].push_back(temp[j]);
								}
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="if"){
					// not implemented
				} else {
					// none				
				}
			} else if (synonymTable->at(leftSynonym)=="while"){
				if (synonymTable->at(rightSynonym)=="stmt"||synonymTable->at(rightSynonym)=="prog_line"){
					for (size_t i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[WHILE_NODE]){
							vector<int> temp = parent->getChildrenStar(i);
							for (size_t j=0; j<temp.size(); j++){
								answer[0].push_back(i);
								answer[1].push_back(temp[j]);
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="assign"){
					for (size_t i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[WHILE_NODE]){
							vector<int> temp = parent->getChildrenStar(i);
							for (size_t j=0; j<temp.size(); j++){
								if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
									answer[0].push_back(i);
									answer[1].push_back(temp[j]);
								}
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="while"){
					for (size_t i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[WHILE_NODE]){
							vector<int> temp = parent->getChildrenStar(i);
							for (size_t j=0; j<temp.size(); j++){
								if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[WHILE_NODE]){
									answer[0].push_back(i);
									answer[1].push_back(temp[j]);
								}
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="if"){
					// not implemented
				} else {
					// none				
				}
			} else if (synonymTable->at(leftSynonym)=="if"){
				// not implemented
			} else {
				// not valid
			}
			return answer;
		}
	}
	return answer;
}

/******* Helper Level 2 *******/

vector<vector<int>> QueryEvaluator::solveForSuchThat(map<STRING, STRING>* synonymTable, QueryTree* tree){
	vector<vector<int>> answer;
	string suchThatType = tree->getRootNode()->getKey();
	if (suchThatType == "Modifies"){
		answer = solveForSuchThatModifies(synonymTable, tree);
	} else if (suchThatType == "Uses"){
		answer = solveForSuchThatUses(synonymTable, tree);
	} else if (suchThatType == "Follows"){
		answer = solveForSuchThatFollows(synonymTable, tree);
	} else if (suchThatType == "Follows*"){
		answer = solveForSuchThatFollowsStar(synonymTable, tree);
	} else if (suchThatType == "Parent"){
		answer = solveForSuchThatParent(synonymTable, tree);
	} else if (suchThatType == "Parent*"){
		answer = solveForSuchThatParentStar(synonymTable, tree);
	} else {
		// not implemented yet
	}

	return answer;
}

vector<int> QueryEvaluator::solveForPattern(string selectSynonym, map<STRING, STRING>* synonymTable, QueryTree* tree){
	vector<int> answer;
	AST* ast = &(pkb->ast);
	StatementTable* statementTable = &(pkb->statementTable);
	string pattern = tree->getRootNode()->getChild(2)->getKey();

	cout << pattern << endl;

	return answer;
}

/******* Helper Level 1 *******/
// Method to collect solution from different conditional clauses (such that, with, pattern, etc.) and combine
vector<int> QueryEvaluator::solve(string selectSynonym, map<STRING, STRING>* synonymTable, QueryTree* tree){
	if (tree->getRootNode()->getChild(1)->getNumChild()==0&&tree->getRootNode()->getChild(2)->getNumChild()==0){
		vector<int> answer;
		answer = solveForSelect(selectSynonym, synonymTable, &(pkb->statementTable), &(pkb->procTable), &(pkb->varTable), &(pkb->constantTable));
		return answer;
	} else {
		QueryTree* suchThatSubtree = tree->getSubtreeFromNode(tree->getRootNode()->getChild(1)->getChild(0));
		vector<vector<int>> resultFromSuchThat = solveForSuchThat(synonymTable, suchThatSubtree);
		string leftSynonym = suchThatSubtree->getRootNode()->getChild(0)->getKey();
		string rightSynonym = suchThatSubtree->getRootNode()->getChild(1)->getKey();
		if (selectSynonym == leftSynonym){
			vector<int> answer;
			for (int i=0; i<resultFromSuchThat[0].size(); i++){
				answer.push_back(resultFromSuchThat[0][i]);
			}
			return answer;
		} else if (selectSynonym==rightSynonym){
			vector<int> answer;
			for (int i=0; i<resultFromSuchThat[1].size(); i++){
				answer.push_back(resultFromSuchThat[1][i]);
			}
			return answer;
		} else if (resultFromSuchThat[0].size()>0){
			vector<int> answer;
			if (synonymTable->at(selectSynonym)=="stmt"||synonymTable->at(selectSynonym)=="prog_line"){
				for (int i=1; i<=pkb->statementTable.getSize(); i++){
					answer.push_back(i);
				}
				return answer;
			} else if (synonymTable->at(selectSynonym)=="assign"){
				for (int i=1; i<=pkb->statementTable.getSize(); i++){
					if (pkb->statementTable.getTNode(i)->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
						answer.push_back(i);
					}
				}
				return answer;
			} else if (synonymTable->at(selectSynonym)=="while"){
				for (int i=1; i<=pkb->statementTable.getSize(); i++){
					if (pkb->statementTable.getTNode(i)->getNodeType()==TNODE_NAMES[WHILE_NODE]){
						answer.push_back(i);
					}
				}
				return answer;
			} else if (synonymTable->at(selectSynonym)=="variable"){
				for (int i=0; i<pkb->varTable.getSize(); i++){
					answer.push_back(i);
				}
				return answer;
			} else if (synonymTable->at(selectSynonym)=="constant"){
				for (int i=0; i<pkb->varTable.getSize(); i++){
					answer.push_back(i);
				}
				return answer;
			}
		}
		vector<int> resultFromPattern = solveForPattern(selectSynonym, synonymTable, tree);
		vector<int> answer;
		return answer;
	}
}

/******* Methods *******/
// Method to get and printout final result
list<string> QueryEvaluator::evaluate(map<STRING, STRING>* synonymTable, QueryTree* tree){

	string output = "Hello World!";
	list<string> outputlist;
	string selectSynonym = tree->getRootNode()->getChild(0)->getChild(0)->getKey();
	// Need to check if selectSynonym is inside synonymTable
	// TODO: throws exception
	// tree->printTree();
	if (synonymTable->find(selectSynonym) == synonymTable->end()){
		return outputlist;
	}
	vector<int> answer = solve(selectSynonym, synonymTable, tree);
	cout << "result :: " << answer.size() << endl;
	string temp = "";
	if (synonymTable->at(selectSynonym)=="variable"||
		synonymTable->at(selectSynonym)=="procedure" ||
		synonymTable->at(selectSynonym)=="constant"){
		if (synonymTable->at(selectSynonym)=="variable"){
			for (size_t i=0; i<answer.size(); i++){
				temp = temp + ("" + pkb->varTable.getVarName(answer.at(i)));
				outputlist.push_back(pkb->varTable.getVarName(answer.at(i)));
				if (i!=answer.size()-1){
					temp = temp+",";
				}
			}
		} else if (synonymTable->at(selectSynonym)=="procedure"){
			for (size_t i=0; i<answer.size(); i++){
				temp = temp + ("" + pkb->procTable.getProcName(answer.at(i)));
				if (i!=answer.size()-1){
					temp = temp+",";
				}
				outputlist.push_back(pkb->procTable.getProcName(answer.at(i)));
			}
		} else {
			for (size_t i=0; i<answer.size(); i++){
				/*temp = temp + ("" + pkb->constantTable.getConstant(answer.at(i)));
				if (i!=answer.size()-1){
					temp = temp+",";
				}*/
				outputlist.push_back(to_string((long long)pkb->constantTable.getConstant(answer.at(i))));
			}
		}
	} else {
		for (size_t i=0; i<answer.size(); i++){
			temp = temp + to_string((long long)answer[i]);
			if (i!=answer.size()-1){
				temp = temp+",";
			}
			outputlist.push_back(to_string((long long)answer[i]));
		}
	}
	output = temp;
	return outputlist;
};