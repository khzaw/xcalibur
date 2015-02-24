// File name: QueryEvaluator.cpp
#include <string>
#include <map>
#include "QueryTree.h"
#include "QTNode.h"
#include "..\PKB\PKB.h"
#include "..\PKB\PKBController.h"

#include <set>
#include <iostream>
#include <algorithm>

//For Testing
#include "..\PKB\StatementTable.h"
#include "..\PKB\Follows.h"
#include "..\PKB\Parent.h"
#include "..\PKB\Modifies.h"
#include "..\PKB\Uses.h"
#include "..\PKB\ProcTable.h"
#include "..\PKB\VarTable.h"
#include "..\PKB\ConstantTable.h"
#include "QueryEvaluator.h"

using namespace std;

typedef string STRING;

/******* Constructors *******/
QueryEvaluator::QueryEvaluator(){
	pkb = new PKBController();
};

QueryEvaluator::QueryEvaluator(PKBController* newPKB){
	pkb = newPKB;
}
pair<vector<string>, vector<vector<int>>> QueryEvaluator::mergeSolutions(pair<vector<string>, vector<vector<int>>> first, pair<vector<string>, vector<vector<int>>> second) {
	vector<pair<int, int>> equalIndex;	
	vector<int> uniqueIndexInSecond;
	vector<string> solutionSynonyms(first.first.begin(), first.first.end());
	// get the pairs of indexes for the same attributes
	// get the list of all synonyms in the solution
	for(size_t i = 0; i < second.first.size(); i++ ) {
		bool in = false;
		for(size_t j = 0; j < first.first.size(); j++) {
			//cout<<endl  << second.first.at(i) << " " << first.first.at(j) <<endl;
			if(second.first.at(i).compare(first.first.at(j)) == 0) {
				equalIndex.push_back(make_pair(j, i));
				in = true;
				break;
			} 
		}
		if(in == false) {
			uniqueIndexInSecond.push_back(i);
			solutionSynonyms.push_back(second.first.at(i));
		}
	}
	vector<vector<int>> solutionValues(solutionSynonyms.size());
	for(size_t i = 0; i < first.second[0].size(); i ++) {
		for(size_t j = 0; j < second.second[0].size(); j++) {
			bool equal = true;
			// check if similar attributes have equal values
			for(size_t k = 0; k < equalIndex.size(); k++) {
				if (!(first.second[equalIndex.at(k).first].at(i) == second.second[equalIndex.at(k).second].at(j))) {
					equal = false;
					break;
				}
			}

			if(equal) {					//all similar attributes have equal values
				for(size_t a = 0; a < solutionSynonyms.size(); a++) {
					if(a < first.first.size()) {
						// push each attribute of first set
						solutionValues[a].push_back(first.second[a].at(i));
					} else {
						// push each attribute of second set with index in uniqueIndexInSecond
						solutionValues[a].push_back(second.second[uniqueIndexInSecond[a - first.second.size()]].at(j));
					}
				}
			}
		}
	}

	return make_pair(solutionSynonyms, solutionValues);
	
}

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
			set<int> tt = modifies->getModifiedVarStmt(leftIndex);
			vector<int> temp(tt.begin(), tt.end());
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
			set<int> tt = modifies->getModifiersStmt(rightIndex);
			vector<int> temp(tt.begin(), tt.end());
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
						set<int> tt = modifies->getModifiersStmt(vars[i]);
						vector<int> temp(tt.begin(), tt.end());
						for (size_t j=0; j<temp.size(); j++){
							answer[0].push_back(temp[j]);
							answer[1].push_back(vars[i]);
						}
					}
				} else if (synonymTable->at(leftSynonym)=="assign"){
					for (size_t i=0; i<vars.size(); i++){
						set<int> tt = modifies->getModifiersStmt(vars[i]);
						vector<int> temp(tt.begin(), tt.end());
						for (size_t j=0; j<temp.size(); j++){
							if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
								answer[0].push_back(temp[j]);
								answer[1].push_back(vars[i]);
							}
						}
					}
				} else if (synonymTable->at(leftSynonym)=="while"){
					for (size_t i=0; i<vars.size(); i++){
						set<int> tt = modifies->getModifiersStmt(vars[i]);
						vector<int> temp(tt.begin(), tt.end());
						for (size_t j=0; j<temp.size(); j++){
							if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[WHILE_NODE]){
								answer[0].push_back(temp[j]);
								answer[1].push_back(vars[i]);
							}
						}
					}
				} else if (synonymTable->at(leftSynonym)=="if"){
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
			set<int> tt = uses->getUsedVarStmt(leftIndex);
			vector<int> temp(tt.begin(), tt.end());
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
			set<int> tt = uses->getUsersStmt(rightIndex);
			vector<int> temp(tt.begin(), tt.end());
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
						set<int> tt = uses->getUsersStmt(vars[i]);
						vector<int> temp(tt.begin(), tt.end());
						for (size_t j=0; j<temp.size(); j++){
							answer[0].push_back(temp[j]);
							answer[1].push_back(vars[i]);
						}
					}
				} else if (synonymTable->at(leftSynonym)=="assign"){
					for (size_t i=0; i<vars.size(); i++){
						set<int> tt = uses->getUsersStmt(vars[i]);
						vector<int> temp(tt.begin(), tt.end());
						for (size_t j=0; j<temp.size(); j++){
							if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
								answer[0].push_back(temp[j]);
								answer[1].push_back(vars[i]);
							}
						}
					}
				} else if (synonymTable->at(leftSynonym)=="while"){
					for (size_t i=0; i<vars.size(); i++){
						set<int> tt = uses->getUsersStmt(vars[i]);
						vector<int> temp(tt.begin(), tt.end());
						for (size_t j=0; j<temp.size(); j++){
							if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[WHILE_NODE]){
								answer[0].push_back(temp[j]);
								answer[1].push_back(vars[i]);
							}
						}
					}
				} else if (synonymTable->at(leftSynonym)=="if"){
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
			set<int> tt = follows->getFollowers(leftIndex);
			vector<int> temp(tt.begin(), tt.end());
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
			set<int> tt = follows->getFollowees(rightIndex);
			vector<int> temp(tt.begin(), tt.end());
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
		} else if (leftSynonym==rightSynonym&&leftSynonym!="_"){
			return answer;
		}  else {
			if (synonymTable->at(leftSynonym)=="stmt"||synonymTable->at(leftSynonym)=="prog_line"){
				if (synonymTable->at(rightSynonym)=="stmt"||synonymTable->at(rightSynonym)=="prog_line"){
					for (int i=1; i<=statementTable->getSize(); i++){
						set<int> tt = follows->getFollowers(i);
						vector<int> temp(tt.begin(), tt.end());
						for (size_t j=0; j<temp.size(); j++){
							answer[0].push_back(i);
							answer[1].push_back(temp[j]);
						}
					}
				} else if (synonymTable->at(rightSynonym)=="assign"){
					for (int i=1; i<=statementTable->getSize(); i++){
						set<int> tt = follows->getFollowers(i);
						vector<int> temp(tt.begin(), tt.end());
						for (size_t j=0; j<temp.size(); j++){
							if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
								answer[0].push_back(i);
								answer[1].push_back(temp[j]);
							}
						}
					}
				} else if (synonymTable->at(rightSynonym)=="while"){
					for (int i=1; i<=statementTable->getSize(); i++){
						set<int> tt = follows->getFollowers(i);
						vector<int> temp(tt.begin(), tt.end());
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
					for (int i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
							set<int> tt = follows->getFollowers(i);
							vector<int> temp(tt.begin(), tt.end());
							for (size_t j=0; j<temp.size(); j++){
								answer[0].push_back(i);
								answer[1].push_back(temp[j]);
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="assign"){
					for (int i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
							set<int> tt = follows->getFollowers(i);
							vector<int> temp(tt.begin(), tt.end());
							for (size_t j=0; j<temp.size(); j++){
								if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
									answer[0].push_back(i);
									answer[1].push_back(temp[j]);
								}
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="while"){
					for (int i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
							set<int> tt = follows->getFollowers(i);
							vector<int> temp(tt.begin(), tt.end());
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
					for (int i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[WHILE_NODE]){
							set<int> tt = follows->getFollowers(i);
							vector<int> temp(tt.begin(), tt.end());
							for (size_t j=0; j<temp.size(); j++){
								answer[0].push_back(i);
								answer[1].push_back(temp[j]);
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="assign"){
					for (int i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[WHILE_NODE]){
							set<int> tt = follows->getFollowers(i);
							vector<int> temp(tt.begin(), tt.end()); 
							for (size_t j=0; j<temp.size(); j++){
								if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
									answer[0].push_back(i);
									answer[1].push_back(temp[j]);
								}
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="while"){
					for (int i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[WHILE_NODE]){
							set<int> tt = follows->getFollowers(i);
							vector<int> temp(tt.begin(), tt.end());
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
			set<int> tt = follows->getFollowersStar(leftIndex);
			vector<int> temp(tt.begin(), tt.end());
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
			set<int> tt = follows->getFolloweesStar(rightIndex);
			vector<int> temp(tt.begin(), tt.end());
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
		} else if (leftSynonym==rightSynonym&&leftSynonym!="_"){
			return answer;
		}  else {
			if (synonymTable->at(leftSynonym)=="stmt"||synonymTable->at(leftSynonym)=="prog_line"){
				if (synonymTable->at(rightSynonym)=="stmt"||synonymTable->at(rightSynonym)=="prog_line"){
					for (int i=1; i<=statementTable->getSize(); i++){
						set<int> tt = follows->getFollowersStar(i);
						vector<int> temp(tt.begin(), tt.end());
						for (size_t j=0; j<temp.size(); j++){
							answer[0].push_back(i);
							answer[1].push_back(temp[j]);
						}
					}
				} else if (synonymTable->at(rightSynonym)=="assign"){
					for (int i=1; i<=statementTable->getSize(); i++){
						set<int> tt = follows->getFollowersStar(i);
						vector<int> temp(tt.begin(), tt.end());
						for (size_t j=0; j<temp.size(); j++){
							if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
								answer[0].push_back(i);
								answer[1].push_back(temp[j]);
							}
						}
					}
				} else if (synonymTable->at(rightSynonym)=="while"){
					for (int i=1; i<=statementTable->getSize(); i++){
						set<int> tt = follows->getFollowersStar(i);
						vector<int> temp(tt.begin(), tt.end());
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
					for (int i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
							set<int> tt = follows->getFollowersStar(i);
							vector<int> temp(tt.begin(), tt.end());
							for (size_t j=0; j<temp.size(); j++){
								answer[0].push_back(i);
								answer[1].push_back(temp[j]);
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="assign"){
					for (int i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
							set<int> tt = follows->getFollowersStar(i);
							vector<int> temp(tt.begin(), tt.end());
							for (size_t j=0; j<temp.size(); j++){
								if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
									answer[0].push_back(i);
									answer[1].push_back(temp[j]);
								}
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="while"){
					for (int i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
							set<int> tt = follows->getFollowersStar(i);
							vector<int> temp(tt.begin(), tt.end());
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
					for (int i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[WHILE_NODE]){
							set<int> tt = follows->getFollowersStar(i);
							vector<int> temp(tt.begin(), tt.end());
							for (size_t j=0; j<temp.size(); j++){
								answer[0].push_back(i);
								answer[1].push_back(temp[j]);
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="assign"){
					for (int i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[WHILE_NODE]){
							set<int> tt = follows->getFollowersStar(i);
							vector<int> temp(tt.begin(), tt.end());
							for (size_t j=0; j<temp.size(); j++){
								if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
									answer[0].push_back(i);
									answer[1].push_back(temp[j]);
								}
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="while"){
					for (int i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[WHILE_NODE]){
							set<int> tt = follows->getFollowersStar(i);
							vector<int> temp(tt.begin(), tt.end());
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
			set<int> tt = parent->getChildren(leftIndex);
			vector<int> temp(tt.begin(), tt.end());
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
			set<int> tt = parent->getParents(rightIndex);
			vector<int> temp(tt.begin(), tt.end());
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
		} else if (leftSynonym==rightSynonym&&leftSynonym!="_"){
			return answer;
		}  else {
			if (synonymTable->at(leftSynonym)=="stmt"||synonymTable->at(leftSynonym)=="prog_line"){
				if (synonymTable->at(rightSynonym)=="stmt"||synonymTable->at(rightSynonym)=="prog_line"){
					for (int i=1; i<=statementTable->getSize(); i++){
						set<int> tt = parent->getChildren(i);
						vector<int> temp(tt.begin(), tt.end());
						for (size_t j=0; j<temp.size(); j++){
							answer[0].push_back(i);
							answer[1].push_back(temp[j]);
						}
					}
				} else if (synonymTable->at(rightSynonym)=="assign"){
					for (int i=1; i<=statementTable->getSize(); i++){
						set<int> tt = parent->getChildren(i);
						vector<int> temp(tt.begin(), tt.end());
						for (size_t j=0; j<temp.size(); j++){
							if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
								answer[0].push_back(i);
								answer[1].push_back(temp[j]);
							}
						}
					}
				} else if (synonymTable->at(rightSynonym)=="while"){
					for (int i=1; i<=statementTable->getSize(); i++){
						set<int> tt = parent->getChildren(i);
						vector<int> temp(tt.begin(), tt.end());
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
					for (int i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
							set<int> tt = parent->getChildren(i);
							vector<int> temp(tt.begin(), tt.end());
							for (size_t j=0; j<temp.size(); j++){
								answer[0].push_back(i);
								answer[1].push_back(temp[j]);
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="assign"){
					for (int i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
							set<int> tt = parent->getChildren(i);
							vector<int> temp(tt.begin(), tt.end());
							for (size_t j=0; j<temp.size(); j++){
								if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
									answer[0].push_back(i);
									answer[1].push_back(temp[j]);
								}
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="while"){
					for (int i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
							set<int> tt = parent->getChildren(i);
							vector<int> temp(tt.begin(), tt.end());
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
					for (int i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[WHILE_NODE]){
							set<int> tt = parent->getChildren(i);
							vector<int> temp(tt.begin(), tt.end());
							for (size_t j=0; j<temp.size(); j++){
								answer[0].push_back(i);
								answer[1].push_back(temp[j]);
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="assign"){
					for (int i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[WHILE_NODE]){
							set<int> tt = parent->getChildren(i);
							vector<int> temp(tt.begin(), tt.end());
							for (size_t j=0; j<temp.size(); j++){
								if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
									answer[0].push_back(i);
									answer[1].push_back(temp[j]);
								}
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="while"){
					for (int i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[WHILE_NODE]){
							set<int> tt = parent->getChildren(i);
							vector<int> temp(tt.begin(), tt.end());
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
			set<int> tt = parent->getChildrenStar(leftIndex);
			vector<int> temp(tt.begin(), tt.end());
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
			set<int> tt = parent->getParentStar(rightIndex);
			vector<int> temp(tt.begin(), tt.end());
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
		} else if (leftSynonym==rightSynonym&&leftSynonym!="_"){
			return answer;
		}  else {
			if (synonymTable->at(leftSynonym)=="stmt"||synonymTable->at(leftSynonym)=="prog_line"){
				if (synonymTable->at(rightSynonym)=="stmt"||synonymTable->at(rightSynonym)=="prog_line"){
					for (int i=1; i<=statementTable->getSize(); i++){
						set<int> tt = parent->getChildrenStar(i);
						vector<int> temp(tt.begin(), tt.end());
						for (size_t j=0; j<temp.size(); j++){
							answer[0].push_back(i);
							answer[1].push_back(temp[j]);
						}
					}
				} else if (synonymTable->at(rightSynonym)=="assign"){
					for (int i=1; i<=statementTable->getSize(); i++){
						set<int> tt = parent->getChildrenStar(i);
						vector<int> temp(tt.begin(), tt.end());
						for (size_t j=0; j<temp.size(); j++){
							if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
								answer[0].push_back(i);
								answer[1].push_back(temp[j]);
							}
						}
					}
				} else if (synonymTable->at(rightSynonym)=="while"){
					for (int i=1; i<=statementTable->getSize(); i++){
						set<int> tt = parent->getChildrenStar(i);
						vector<int> temp(tt.begin(), tt.end());
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
					for (int i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
							set<int> tt = parent->getChildrenStar(i);
							vector<int> temp(tt.begin(), tt.end());
							for (size_t j=0; j<temp.size(); j++){
								answer[0].push_back(i);
								answer[1].push_back(temp[j]);
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="assign"){
					for (int i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
							set<int> tt = parent->getChildrenStar(i);
							vector<int> temp(tt.begin(), tt.end());
							for (size_t j=0; j<temp.size(); j++){
								if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
									answer[0].push_back(i);
									answer[1].push_back(temp[j]);
								}
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="while"){
					for (int i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
							set<int> tt = parent->getChildrenStar(i);
							vector<int> temp(tt.begin(), tt.end());
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
					for (int i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[WHILE_NODE]){
							set<int> tt = parent->getChildrenStar(i);
							vector<int> temp(tt.begin(), tt.end());
							for (size_t j=0; j<temp.size(); j++){
								answer[0].push_back(i);
								answer[1].push_back(temp[j]);
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="assign"){
					for (int i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[WHILE_NODE]){
							set<int> tt = parent->getChildrenStar(i);
							vector<int> temp(tt.begin(), tt.end());
							for (size_t j=0; j<temp.size(); j++){
								if (statementTable->getTNode(temp[j])->getNodeType()==TNODE_NAMES[ASSIGN_NODE]){
									answer[0].push_back(i);
									answer[1].push_back(temp[j]);
								}
							}
						}						
					}
				} else if (synonymTable->at(rightSynonym)=="while"){
					for (int i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()==TNODE_NAMES[WHILE_NODE]){
							set<int> tt = parent->getChildrenStar(i);
							vector<int> temp(tt.begin(), tt.end());
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
	/*
	 * type 1 = _x_
	 * type 2 = _x+y_
	 */
	vector<int> answer;
	AST* ast = &(pkb->ast);
	StatementTable* statementTable = &(pkb->statementTable);
	if(tree->getRootNode()->getChild(2)->getNumChild() > 0) {
		string queryPattern = tree->getRootNode()->getChild(2)->getChild(0)->getData();
		string leftHandSide = tree->getRootNode()->getChild(2)->getChild(0)->getChild(1)->getKey();
		if(leftHandSide == "_" && queryPattern.empty()) {
			// return all the assignment nodes
			answer = statementTable->getStmtNumUsingNodeType(TNODE_NAMES[ASSIGN_NODE]);
		} else if(leftHandSide == "_" && !queryPattern.empty()) {
			// (_, "_x+y_")
			answer = statementTable->getAssignmentNodesNum(leftHandSide, queryPattern);
		} else if(leftHandSide != "_" && queryPattern.empty()) {
			// ("oSCar", _)
			if(leftHandSide.substr(0, 1) != "\"") {
				if(synonymTable->find(leftHandSide) == synonymTable->end()) {
					return answer;
				}

				if(synonymTable->at(leftHandSide) != "variable") return answer;
				else { // (v, _) case
					answer = statementTable->getStmtNumUsingNodeType(TNODE_NAMES[ASSIGN_NODE]);
					return answer;
				}
			}
			answer = statementTable->getAssignmentNodesNum(leftHandSide, queryPattern);
		} else if(leftHandSide != "_" && !queryPattern.empty()) {
			if(leftHandSide.substr(0, 1) != "\"") {
				if (synonymTable->find(leftHandSide)==synonymTable->end()) { // if leftHandSide is not defined
					return answer;
				}

				if(synonymTable->at(leftHandSide) != "variable") return answer;
				else {
					// (v, _"Romeo"_)
					answer = statementTable->getAssignmentNodesNum("_", queryPattern);
				}

			} else {
				answer = statementTable->getAssignmentNodesNum(leftHandSide, queryPattern);
			}
		}

	}
	return answer;
}

/******* Helper Level 1 *******/
// Method to collect solution from different conditional clauses (such that, with, pattern, etc.) and combine
vector<int> QueryEvaluator::solve(string selectSynonym, map<STRING, STRING>* synonymTable, QueryTree* tree){
	vector<int> answer;
	if (tree->getRootNode()->getChild(1)->getNumChild()==0&&tree->getRootNode()->getChild(2)->getNumChild()==0){
		answer = solveForSelect(selectSynonym, synonymTable, &(pkb->statementTable), &(pkb->procTable), &(pkb->varTable), &(pkb->constantTable));
		return answer;
	} else {		
		vector<vector<int>> resultFromSuchThat;
		vector<string> namesSuchThat;
		vector<vector<int>> forMergeSuchThat;
		if(tree->getRootNode()->getChild(1)->getNumChild() > 0) {
			QueryTree* suchThatSubtree = tree->getSubtreeFromNode(tree->getRootNode()->getChild(1)->getChild(0));
			resultFromSuchThat = solveForSuchThat(synonymTable, suchThatSubtree);
			if (resultFromSuchThat[0].size()==0){
				return answer;
			}
			string leftSynonym = suchThatSubtree->getRootNode()->getChild(0)->getKey();
			string rightSynonym = suchThatSubtree->getRootNode()->getChild(1)->getKey();
			if (leftSynonym == "_"){
				if (synonymTable->find(leftSynonym)!=synonymTable->end()){
					if (synonymTable->at(leftSynonym)=="stmt"){
						namesSuchThat.push_back(to_string((long long)&leftSynonym));
						synonymTable->insert(make_pair(to_string((long long)&leftSynonym), "stmt"));
						forMergeSuchThat.push_back(resultFromSuchThat[0]);
					}
				}
			} else if (synonymTable->find(leftSynonym)!=synonymTable->end()){
				namesSuchThat.push_back(leftSynonym);
				forMergeSuchThat.push_back(resultFromSuchThat[0]);
			} else {
				namesSuchThat.push_back(to_string((long long)&leftSynonym));
				forMergeSuchThat.push_back(resultFromSuchThat[0]);
			}

			if (rightSynonym == "_"){
				if (synonymTable->find(rightSynonym)!=synonymTable->end()){
					if (synonymTable->at(rightSynonym)=="variable"){
						namesSuchThat.push_back(to_string((long long)&rightSynonym));
						synonymTable->insert(make_pair(to_string((long long)&leftSynonym), "variable"));
						forMergeSuchThat.push_back(resultFromSuchThat[1]);
					} else {
						namesSuchThat.push_back(to_string((long long)&leftSynonym));
						synonymTable->insert(make_pair(to_string((long long)&leftSynonym), "stmt"));
						forMergeSuchThat.push_back(resultFromSuchThat[1]);
					}
				}
			} else if (synonymTable->find(rightSynonym)!=synonymTable->end()){
				namesSuchThat.push_back(rightSynonym);
				forMergeSuchThat.push_back(resultFromSuchThat[1]);
			} else {
				namesSuchThat.push_back(to_string((long long)&leftSynonym));
				forMergeSuchThat.push_back(resultFromSuchThat[1]);
			}
		}

		vector<int> resultFromPattern;
		vector<string> namesPattern;
		vector<vector<int>> forMergePattern;
		if(tree->getRootNode()->getChild(2)->getNumChild() > 0) {
			resultFromPattern = solveForPattern(selectSynonym, synonymTable, tree);
			if (resultFromPattern.size()==0){
				return answer;
			}
			string patternAssignName = tree->getRootNode()->getChild(2)->getChild(0)->getChild(0)->getKey();
			namesPattern.push_back(patternAssignName);
			forMergePattern.push_back(resultFromPattern);

			vector<int> patternModifiedVars;
			for (size_t i=0; i<resultFromPattern.size(); i++){
				set<int> tt = pkb->modifiesTable.getModifiedVarStmt(resultFromPattern[i]);
				vector<int> temp(tt.begin(), tt.end());
				for (size_t j=0; j<temp.size(); j++){
					patternModifiedVars.push_back(temp[j]);
				}
			}

			string patternModifiedVarsName = tree->getRootNode()->getChild(2)->getChild(0)->getChild(1)->getKey();
			if (patternModifiedVarsName == "_"){
				namesPattern.push_back("_varP");
				synonymTable->insert(make_pair("_varP", "variable"));
				forMergePattern.push_back(patternModifiedVars);
			} else if (synonymTable->find(patternModifiedVarsName)!=synonymTable->end()){
				namesPattern.push_back(patternModifiedVarsName);
				forMergePattern.push_back(patternModifiedVars);
			}
		}		

		vector<string> mergeOutputNames;
		vector<vector<int>> mergeOutputValues;
		pair<vector<string>, vector<vector<int>>> resultAfterMerge;

		if(forMergeSuchThat.size()>0&&forMergePattern.size()>0){
			resultAfterMerge = mergeSolutions(make_pair(namesSuchThat, forMergeSuchThat), make_pair(namesPattern, forMergePattern));
		} else if (forMergeSuchThat.size()>0){
			resultAfterMerge = make_pair(namesSuchThat, forMergeSuchThat);
		} else if (forMergePattern.size()>0){
			resultAfterMerge = make_pair(namesPattern, forMergePattern);
		} else {
			return answer;
		}
		mergeOutputNames = resultAfterMerge.first;
		mergeOutputValues = resultAfterMerge.second;

		if (find(mergeOutputNames.begin(), mergeOutputNames.end(), selectSynonym) != mergeOutputNames.end()){
			for (size_t i=0; i<mergeOutputNames.size(); i++){
				if (mergeOutputNames[i]==selectSynonym){
					answer = mergeOutputValues[i];
				}
			}
			return answer;
		} else if (mergeOutputValues.size()>0&&mergeOutputValues[0].size()>0){
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
				for (int i=0; i<pkb->constantTable.getSize(); i++){
					answer.push_back(i);
				}
				return answer;
			}
		}		
		return answer;
	}
}

/******* Methods *******/
// Method to get and printout final result
list<string> QueryEvaluator::evaluate(map<STRING, STRING>* synonymTable, QueryTree* tree){

	string output = "Hello World!";
	list<string> outputlist;
	if(tree->getRootNode()->getKey() == "ERROR") {
		return outputlist;
	}
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