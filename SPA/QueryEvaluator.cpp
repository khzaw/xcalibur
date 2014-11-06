// File name: QueryEvaluator.cpp
#include <string>
#include <map>
#include "QueryTree.h"
#include "QTNode.h"
#include "PKB.h"

//For Testing
#include "StatementTable.h"
#include "Follows.h"
#include "Modifies.h"
#include "ProcTable.h"
#include "VarTable.h"

#include "QueryEvaluator.h"
#include <set>

using namespace std;

typedef string STRING;

/******* Constructors *******/
QueryEvaluator::QueryEvaluator(){

};

QueryEvaluator::QueryEvaluator(PKB* newPKB){
	pkb = newPKB;
};
/******* For Testing *******/
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

vector<int> QueryEvaluator::solveForSuchThatFollows(string selectSynonym, map<STRING, STRING>* synonymTable, QueryTree* suchThatTree, StatementTable* statementTable, Follows* follows, ProcTable* procTable, VarTable* varTable){
	vector<int> answer;
	if (synonymTable->find(selectSynonym)==synonymTable->end()){ // if selectSynonym is not defined
		return answer;
	}
	bool isSynonymInSuchThat = checkSynonymInSuchThat(selectSynonym, suchThatTree);
	if (isSynonymInSuchThat){ // Select synonym such that Follows(synonym, *) (Follows(*, synonym))
		if (selectSynonym == suchThatTree->getRootNode()->getChild(0)->getKey()){ // Select synonym such that Follows(synonym, *)
			string stmtSynonym = suchThatTree->getRootNode()->getChild(1)->getKey();
			if (stmtSynonym.empty()){ // Select synonym such that Follows(synonym, 1)
				int stmtIndex = suchThatTree->getRootNode()->getChild(1)->getValue();
				if(stmtIndex<=statementTable->getSize()){
					if (synonymTable->at(selectSynonym)=="stmt"){
						answer = follows->getFollowees(stmtIndex);
					} else if (synonymTable->at(selectSynonym)=="prog_line"){
						answer = follows->getFollowees(stmtIndex);
					} else if (synonymTable->at(selectSynonym)=="assign"){
						vector<int> temp = follows->getFollowees(stmtIndex);
						for (size_t i=0; i<temp.size(); i++){
							if (statementTable->getTNode(temp.at(i))->getNodeType()=="assign"){
								answer.push_back(temp.at(i));
							}
						}
					} else if (synonymTable->at(selectSynonym)=="while"){
						vector<int> temp = follows->getFollowees(stmtIndex);
						for (size_t i=0; i<temp.size(); i++){
							if (statementTable->getTNode(temp.at(i))->getNodeType()=="while"){
								answer.push_back(temp.at(i));
							}
						}
					} else if (synonymTable->at(selectSynonym)=="if"){
						// not implemented
					} else {
						// throw exception or return empty
					}
				} else {
					// throw exception or return empty
				}
			} else { // Select synonym such that Follows(synonym, another Synonym)
				if (synonymTable->find(stmtSynonym) != synonymTable->end()){
					vector<int> dataFromStmtSynonym;
					if(synonymTable->at(stmtSynonym)=="stmt"){
						dataFromStmtSynonym = follows->getAllFolloweeStmt();
					} else if (synonymTable->at(stmtSynonym)=="prog_line"){
						dataFromStmtSynonym = follows->getAllFolloweeStmt();
					} else if (synonymTable->at(stmtSynonym)=="assign"){
						vector<int> assignList = statementTable->getStmtNumUsingNodeType("assign");
						for (size_t i=0; i<assignList.size(); i++){
							vector<int> result = follows->getFollowees(assignList.at(i));
							dataFromStmtSynonym.insert(dataFromStmtSynonym.end(), result.begin(), result.end());
						}
					} else if (synonymTable->at(stmtSynonym)=="while"){
						vector<int> whileList = statementTable->getStmtNumUsingNodeType("while");
						for (size_t i=0; i<whileList.size(); i++){
							vector<int> result = follows->getFollowees(whileList.at(i));
							dataFromStmtSynonym.insert(dataFromStmtSynonym.end(), result.begin(), result.end());
						}
					} else if (synonymTable->at(stmtSynonym)=="if"){
						// not implemented	
					} else {
						// throw exception
					}
					if (synonymTable->at(selectSynonym)=="stmt"){
						answer = dataFromStmtSynonym;
					} else if (synonymTable->at(selectSynonym)=="prog_line"){
						answer = dataFromStmtSynonym;
					} else if (synonymTable->at(selectSynonym)=="assign"){
						vector<int> temp = dataFromStmtSynonym;
						for (size_t i=0; i<temp.size(); i++){
							if (statementTable->getTNode(temp.at(i))->getNodeType()=="assign"){
								answer.push_back(temp.at(i));
							}
						}
					} else if (synonymTable->at(selectSynonym)=="while"){
						vector<int> temp = dataFromStmtSynonym;
						for (size_t i=0; i<temp.size(); i++){
							if (statementTable->getTNode(temp.at(i))->getNodeType()=="while"){
								answer.push_back(temp.at(i));
							}
						}
					} else if (synonymTable->at(selectSynonym)=="if"){
						// not implemented
					} else {
						// throw exception or return empty
					}
				} else {
					// throw exception
				}
			}
		} else { // Select synonym such that Follows(*, synonym)
			string stmtSynonym = suchThatTree->getRootNode()->getChild(0)->getKey();
			if (stmtSynonym.empty()){ // Select synonym such that Follows(1, synonym)
				int stmtIndex = suchThatTree->getRootNode()->getChild(0)->getValue();
				if(stmtIndex<=statementTable->getSize()){
					if (synonymTable->at(selectSynonym)=="stmt"){
						answer = follows->getFollowers(stmtIndex);
					} else if (synonymTable->at(selectSynonym)=="prog_line"){
						answer = follows->getFollowers(stmtIndex);
					} else if (synonymTable->at(selectSynonym)=="assign"){
						vector<int> temp = follows->getFollowers(stmtIndex);
						for (size_t i=0; i<temp.size(); i++){
							if (statementTable->getTNode(temp.at(i))->getNodeType()=="assign"){
								answer.push_back(temp.at(i));
							}
						}
					} else if (synonymTable->at(selectSynonym)=="while"){
						vector<int> temp = follows->getFollowers(stmtIndex);
						for (size_t i=0; i<temp.size(); i++){
							if (statementTable->getTNode(temp.at(i))->getNodeType()=="while"){
								answer.push_back(temp.at(i));
							}
						}
					} else if (synonymTable->at(selectSynonym)=="if"){
						// not implemented
					} else {
						// throw exception or return empty
					}
				} else {
					// throw exception or return empty
				}
			} else { // Select synonym such that Follows(another Synonym, synonym)
				if (synonymTable->find(stmtSynonym) != synonymTable->end()){
					vector<int> dataFromStmtSynonym;
					if(synonymTable->at(stmtSynonym)=="stmt"){
						dataFromStmtSynonym = follows->getAllFollowerStmt();
					} else if (synonymTable->at(stmtSynonym)=="prog_line"){
						dataFromStmtSynonym = follows->getAllFollowerStmt();
					} else if (synonymTable->at(stmtSynonym)=="assign"){
						vector<int> assignList = statementTable->getStmtNumUsingNodeType("assign");
						for (size_t i=0; i<assignList.size(); i++){
							vector<int> result = follows->getFollowers(assignList.at(i));
							dataFromStmtSynonym.insert(dataFromStmtSynonym.end(), result.begin(), result.end());
						}
					} else if (synonymTable->at(stmtSynonym)=="while"){
						vector<int> whileList = statementTable->getStmtNumUsingNodeType("while");
						for (size_t i=0; i<whileList.size(); i++){
							vector<int> result = follows->getFollowers(whileList.at(i));
							dataFromStmtSynonym.insert(dataFromStmtSynonym.end(), result.begin(), result.end());
						}
					} else if (synonymTable->at(stmtSynonym)=="if"){
						// not implemented	
					} else {
						// throw exception
					}
					if (synonymTable->at(selectSynonym)=="stmt"){
						answer = dataFromStmtSynonym;
					} else if (synonymTable->at(selectSynonym)=="prog_line"){
						answer = dataFromStmtSynonym;
					} else if (synonymTable->at(selectSynonym)=="assign"){
						vector<int> temp = dataFromStmtSynonym;
						for (size_t i=0; i<temp.size(); i++){
							if (statementTable->getTNode(temp.at(i))->getNodeType()=="assign"){
								answer.push_back(temp.at(i));
							}
						}
					} else if (synonymTable->at(selectSynonym)=="while"){
						vector<int> temp = dataFromStmtSynonym;
						for (size_t i=0; i<temp.size(); i++){
							if (statementTable->getTNode(temp.at(i))->getNodeType()=="while"){
								answer.push_back(temp.at(i));
							}
						}
					} else if (synonymTable->at(selectSynonym)=="if"){
						// not implemented
					} else {
						// throw exception or return empty
					}
				} else {
					// throw exception
				}
			}
		}
	} else { // synonym is not in Follows(*, *)
		bool isSuchThatTrue = false;
		string leftSynonym = suchThatTree->getRootNode()->getChild(0)->getKey();
		string rightSynonym = suchThatTree->getRootNode()->getChild(1)->getKey();
		if (leftSynonym.empty()&&rightSynonym.empty()){ // Follows(1, 2);
			int leftStmtIndex = suchThatTree->getRootNode()->getChild(0)->getValue();
			int rightStmtIndex = suchThatTree->getRootNode()->getChild(1)->getValue();
			if (leftStmtIndex>statementTable->getSize()||rightStmtIndex>statementTable->getSize()){
				// throw exception
			} else {
				isSuchThatTrue = follows->isFollowsTrue(leftStmtIndex, rightStmtIndex);
			}
		} else if (leftSynonym.empty()){ // Follows(1, synonym)
			int leftStmtIndex = suchThatTree->getRootNode()->getChild(0)->getValue();
			if (synonymTable->at(rightSynonym)=="stmt"||synonymTable->at(rightSynonym)=="prog_line"){
				for (int i=1; i<=statementTable->getSize(); i++){
					if (follows->isFollowsTrue(leftStmtIndex, i)){
						isSuchThatTrue = true;
						break;
					}
				}
			} else if (synonymTable->at(rightSynonym)=="assign"){
				for (int i=1; i<=statementTable->getSize(); i++){
					if (statementTable->getTNode(i)->getNodeType()=="assign"&&follows->isFollowsTrue(leftStmtIndex, i)){
						isSuchThatTrue = true;
						break;
					}
				}
			} else if (synonymTable->at(rightSynonym)=="while"){
				for (int i=1; i<=statementTable->getSize(); i++){
					if (statementTable->getTNode(i)->getNodeType()=="while"&&follows->isFollowsTrue(leftStmtIndex, i)){
						isSuchThatTrue = true;
						break;
					}
				}		
			} else if (synonymTable->at(rightSynonym)=="if"){
				// not implemented
			} else {
				// throw exception
			}
		} else if (rightSynonym.empty()){ // Follows(synonym, 2)
			int rightStmtIndex = suchThatTree->getRootNode()->getChild(1)->getValue();
			if (synonymTable->at(leftSynonym)=="stmt"||synonymTable->at(leftSynonym)=="prog_line"){
				for (int i=1; i<=statementTable->getSize(); i++){
					if (follows->isFollowsTrue(i, rightStmtIndex)){
						isSuchThatTrue = true;
						break;
					}
				}
			} else if (synonymTable->at(leftSynonym)=="assign"){
				for (int i=1; i<=statementTable->getSize(); i++){
					if (statementTable->getTNode(i)->getNodeType()=="assign"&&follows->isFollowsTrue(i, rightStmtIndex)){
						isSuchThatTrue = true;
						break;
					}
				}
			} else if (synonymTable->at(leftSynonym)=="while"){
				for (int i=1; i<=statementTable->getSize(); i++){
					if (statementTable->getTNode(i)->getNodeType()=="while"&&follows->isFollowsTrue(i, rightStmtIndex)){
						isSuchThatTrue = true;
						break;
					}
				}
			} else if (synonymTable->at(leftSynonym)=="if"){
				// not implemented
			} else {
				// throw exception
			}
		} else { // Follows(synonym1, synonym2)
			if(synonymTable->at(leftSynonym).empty()||synonymTable->at(rightSynonym).empty()){
				// throw exception
			} else if (synonymTable->at(leftSynonym)=="stmt"||synonymTable->at(leftSynonym)=="prog_line"){ // Follows(s1, synonym2)
				if (synonymTable->at(rightSynonym)=="stmt"||synonymTable->at(rightSynonym)=="prog_line"){ // Follows(s1, s2) 
					for (int i=1; i<=statementTable->getSize(); i++){
						for (int j=1; j<=statementTable->getSize(); j++){
							if (follows->isFollowsTrue(i, j)){
								isSuchThatTrue = true;
								break;
							}		
						}
						if (isSuchThatTrue) break;
					}
				} else if (synonymTable->at(rightSynonym)=="assign"){ // Follows(s1, a2)
					for (int i=1; i<=statementTable->getSize(); i++){
							for (int j=1; j<=statementTable->getSize(); j++){
								if (statementTable->getTNode(j)->getNodeType()=="assign"&&follows->isFollowsTrue(i, j)){
									isSuchThatTrue = true;
									break;
								}			
							}
							if (isSuchThatTrue) break;
					}
				} else if (synonymTable->at(rightSynonym)=="while"){ // Follows(s1, w2)
					for (int i=1; i<=statementTable->getSize(); i++){
							for (int j=1; j<=statementTable->getSize(); j++){
								if (statementTable->getTNode(j)->getNodeType()=="while"&&follows->isFollowsTrue(i, j)){
									isSuchThatTrue = true;
									break;
								}			
							}
							if (isSuchThatTrue) break;
					}			
				} else if (synonymTable->at(rightSynonym)=="if"){
					// not implemented
				} else {
					// throw exception
				}
			} else if (synonymTable->at(leftSynonym)=="assign"){ // Follows(a1, synonym2)
				if (synonymTable->at(rightSynonym)=="stmt"||synonymTable->at(rightSynonym)=="prog_line"){ // Follows(a1, s2) 
					for (int i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()=="assign"){
							for (int j=1; j<statementTable->getSize(); j++){
								if (follows->isFollowsTrue(i, j)){
									isSuchThatTrue = true;
									break;
								}			
							}
							if (isSuchThatTrue) break;
						}
						if (isSuchThatTrue) break;
					}
				} else if (synonymTable->at(rightSynonym)=="assign"){ // Follows(a1, a2)
					for (int i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()=="assign"){
							for (int j=1; j<=statementTable->getSize(); j++){
								if (statementTable->getTNode(j)->getNodeType()=="assign"&&follows->isFollowsTrue(i, j)){
									isSuchThatTrue = true;
									break;
								}			
							}
							if (isSuchThatTrue) break;
						}
						if (isSuchThatTrue) break;
					}
				} else if (synonymTable->at(rightSynonym)=="while"){ // Follows(a1, w2)
					for (int i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()=="assign"){
							for (int j=1; j<=statementTable->getSize(); j++){
								if (statementTable->getTNode(j)->getNodeType()=="while"&&follows->isFollowsTrue(i, j)){
									isSuchThatTrue = true;
								}			
							}
							if (isSuchThatTrue) break;
						}
						if (isSuchThatTrue) break;
					}
				} else if (synonymTable->at(rightSynonym)=="if"){
					// not implemented
				} else {
					// throw exception
				}
			} else if (synonymTable->at(leftSynonym)=="while"){ // Follows(w1, synonym2)
				if (synonymTable->at(rightSynonym)=="stmt"||synonymTable->at(rightSynonym)=="prog_line"){ // Follows(w1, s2) 
					for (int i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()=="while"){
							for (int j=1; j<=statementTable->getSize(); j++){
								if (follows->isFollowsTrue(i, j)){
									isSuchThatTrue = true;
								}			
							}
							if (isSuchThatTrue) break;
						}
						if (isSuchThatTrue) break;
					}
				} else if (synonymTable->at(rightSynonym)=="assign"){ // Follows(w1, a2)
					for (int i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()=="while"){
							for (int j=1; j<=statementTable->getSize(); j++){
								if (statementTable->getTNode(j)->getNodeType()=="assign"&&follows->isFollowsTrue(i, j)){
									isSuchThatTrue = true;
								}			
							}
							if (isSuchThatTrue) break;
						}
						if (isSuchThatTrue) break;
					}
				} else if (synonymTable->at(rightSynonym)=="while"){ // Follows(w1, w2)
					for (int i=1; i<=statementTable->getSize(); i++){
						if (statementTable->getTNode(i)->getNodeType()=="while"){
							for (int j=1; j<=statementTable->getSize(); j++){
								if (statementTable->getTNode(j)->getNodeType()=="while"&&follows->isFollowsTrue(i, j)){
									isSuchThatTrue = true;
								}			
							}
							if (isSuchThatTrue) break;
						}
						if (isSuchThatTrue) break;
					}
				} else if (synonymTable->at(rightSynonym)=="if"){
					// not implemented
				} else {
					// throw exception
				}
			} else if (synonymTable->at(leftSynonym)=="if"){
				// not implemented
			} else {
				// throw exception
			}
		}
		if (isSuchThatTrue){
			// fill answer for different type of selectSynonym such as procedure, statement, while, assign, variable, prog_line
			if (synonymTable->at(selectSynonym)=="stmt"||
				synonymTable->at(selectSynonym)=="assign"||
				synonymTable->at(selectSynonym)=="while"||
				synonymTable->at(selectSynonym)=="if"||
				synonymTable->at(selectSynonym)=="prog_line"){
					if (synonymTable->at(selectSynonym)=="stmt"||synonymTable->at(selectSynonym)=="prog_line"){
						for (int i=1; i<=statementTable->getSize(); i++){
							answer.push_back(i);
						}
					} else {
						answer = statementTable->getStmtNumUsingNodeType(synonymTable->at(selectSynonym));
					}					
			} else if (synonymTable->at(selectSynonym)=="variable"){
				for (int i=1; i<=varTable->getSize(); i++){
					answer.push_back(i);
				}
			} else if (synonymTable->at(selectSynonym)=="procedure"){
				for (int i=1; i<=procTable->getSize(); i++){
					answer.push_back(i);
				}
			} else {
				// throw exception
			}
		} else {
			// nothing in answer
		}
	}
	return answer;
}

vector<int> QueryEvaluator::solveForSuchThatModifies(string selectSynonym, map<STRING, STRING>* synonymTable, QueryTree* suchThatTree, StatementTable* statementTable, Modifies* modifies, ProcTable* procTable, VarTable* varTable){
	vector<int> answer;
	if (synonymTable->find(selectSynonym)==synonymTable->end()){ // if selectSynonym is not defined
		return answer;
	}
	bool isSynonymInSuchThat = checkSynonymInSuchThat(selectSynonym, suchThatTree);
	if (isSynonymInSuchThat){ // synonym is contained in such that statement
		if (selectSynonym == suchThatTree->getRootNode()->getChild(0)->getKey()){ // Select synonym such that Modifies(synonym, *)
			string rightSynonym = suchThatTree->getRootNode()->getChild(1)->getKey();
			if(!rightSynonym.empty()){ // Select synonym such that Modifies(synonym, *);
				if (synonymTable->find(rightSynonym) == synonymTable->end()){ // Select synonym such that Modifies(synonym, aString);
					if (varTable->containsVar(rightSynonym)){ // if another synonym is a variable
						int varIndex = varTable->getVarIndex(rightSynonym);
						if (synonymTable->at(selectSynonym)=="procedure"){
							answer = modifies->getModifiersProc(varIndex);
						} else if (synonymTable->at(selectSynonym)=="stmt"){
							answer = modifies->getModifiersStmt(varIndex);
						} else if (synonymTable->at(selectSynonym)=="assign"){
							vector<int> temp = modifies->getModifiersStmt(varIndex);
							for (size_t i=0; i<temp.size(); i++){
								if (statementTable->getTNode(temp.at(i))->getNodeType()=="assign"){
									answer.push_back(temp.at(i));
								}
							}
						} else if (synonymTable->at(selectSynonym)=="while"){
							vector<int> temp = modifies->getModifiersStmt(varIndex);
							for (size_t i=0; i<temp.size(); i++){
								if (statementTable->getTNode(temp.at(i))->getNodeType()=="while"){
									answer.push_back(temp.at(i));
								}
							}
						} else if (synonymTable->at(selectSynonym)=="if"){
							// not implemented
						} else {
							// throw exception
						}
					} else {
						// throw error because another synonym is not found
					}
				} else { // Select synonym such that Modifies(symnonym, another synonym)
					if (synonymTable->at(rightSynonym) == "variable" && varTable->getSize()>=(int)0){
						if (synonymTable->at(selectSynonym) == "procedure"){						
							vector<pair<int, int>> result = modifies->getModifiesProc();
							set<int> temp;
							for (size_t i=0; i<result.size(); i++){
								temp.insert(result.at(i).first);
							}
							vector<int> output(temp.begin(), temp.end());
							answer = output;
						} else if (synonymTable->at(selectSynonym) == "stmt"){
							vector<pair<int, int>> result = modifies->getModifiesStmt();
							set<int> temp;
							for (size_t i=0; i<result.size(); i++){
								temp.insert(result.at(i).first);
							}
							vector<int> output(temp.begin(), temp.end());
							answer = output;
						} else if (synonymTable->at(selectSynonym) == "assign"){
							vector<pair<int, int>> result = modifies->getModifiesStmt();
							set<int> temp;
							for (size_t i=0; i<result.size(); i++){
								if (statementTable->getTNode(result.at(i).first)->getNodeType()=="assign"){
									temp.insert(result.at(i).first);
								}
							}
							vector<int> output(temp.begin(), temp.end());
							answer = output;
						} else if (synonymTable->at(selectSynonym) == "while"){
							vector<pair<int, int>> result = modifies->getModifiesStmt();
							set<int> temp;
							for (size_t i=0; i<result.size(); i++){
								if (statementTable->getTNode(result.at(i).first)->getNodeType()=="while"){
									temp.insert(result.at(i).first);
								}
							}
							vector<int> output(temp.begin(), temp.end());
							answer = output;
						} else if (synonymTable->at(selectSynonym) == "if"){
							// not implemented
						} else {
							// throw exception
						}
					} else {
						// throw exception
					}
				}
			} else {
				// throw exception
			}
		} else if (selectSynonym == suchThatTree->getRootNode()->getChild(1)->getKey()){ // Select synonym such that Modifies(*, synonym)
			if (synonymTable->at(selectSynonym) == "variable"){
				string leftSynonym = suchThatTree->getRootNode()->getChild(0)->getKey();
				if (!leftSynonym.empty()){ // Select synonym such that Modifies(anotherSynonym, synonym)
					if (synonymTable->find(leftSynonym) == synonymTable->end()){ // another synonym not in synonym table
						if (procTable->containsProc(leftSynonym)){ // if another synonym is a procedure
							int procIndex = procTable->getProcIndex(leftSynonym);
							answer = modifies->getModifiedVarProc(procIndex);
						} else {
							// throw error because another synonym is not found
						}
					} else { // another synonym is in synonym table
						if (synonymTable->at(leftSynonym)=="procedure"){
							vector<pair<int, int>> result = modifies->getModifiesProc();
							set<int> temp;
							for (size_t i=0; i<result.size(); i++){
								temp.insert(result.at(i).second);
							}
							vector<int> output(temp.begin(), temp.end());
							answer = output;
						} else if (synonymTable->at(selectSynonym)=="stmt"){
							vector<pair<int, int>> result = modifies->getModifiesStmt();
							set<int> temp;
							for (size_t i=0; i<result.size(); i++){
								temp.insert(result.at(i).second);
							}
							vector<int> output(temp.begin(), temp.end());
							answer = output;
						} else if (synonymTable->at(selectSynonym)=="assign"){
							vector<pair<int, int>> result = modifies->getModifiesStmt();
							set<int> temp;
							for (size_t i=0; i<result.size(); i++){
								if (statementTable->getTNode(result.at(i).first)->getNodeType()=="assign"){
									temp.insert(result.at(i).second);
								}
							}
							vector<int> output(temp.begin(), temp.end());
							answer = output;
						} else if (synonymTable->at(selectSynonym)=="while"){
							vector<pair<int, int>> result = modifies->getModifiesStmt();
							set<int> temp;
							for (size_t i=0; i<result.size(); i++){
								if (statementTable->getTNode(result.at(i).first)->getNodeType()=="while"){
									temp.insert(result.at(i).second);
								}
							}
							vector<int> output(temp.begin(), temp.end());
							answer = output;
						} else if (synonymTable->at(selectSynonym)=="if"){
							// not implemented
						} else {
							// throw exception
						}
					}
				} else { // Select synonym such that Modifies(INDEX, synonym)
					int stmtIndex = suchThatTree->getRootNode()->getChild(0)->getValue();
					if (0<stmtIndex&&stmtIndex<=statementTable->getSize()){
						answer = modifies->getModifiedVarStmt(stmtIndex);
					} else {
						// throw exception
					}
				}
			} else {
				// throw exception
			}
		}
	} else { // synonym is not contained in such that statement
		// evaluate such that statement as boolean and solve for it
		bool isSuchThatTrue = false;
		string varSynonym = suchThatTree->getRootNode()->getChild(1)->getKey();
		if (!varSynonym.empty()){
			if (synonymTable->find(varSynonym) == synonymTable->end()){ // varSynonym is a variable name, Modifies(*, "x")
				if (varTable->containsVar(varSynonym)){
					int varIndex = varTable->getVarIndex(varSynonym);
					string leftSynonym = suchThatTree->getRootNode()->getChild(0)->getKey();
					if (leftSynonym.empty()) { // Modifies(1, "x")
						int stmtNumber = suchThatTree->getRootNode()->getChild(0)->getValue();
						if (0<stmtNumber&&stmtNumber<=statementTable->getSize()){
							isSuchThatTrue = modifies->isModifiesStmt(stmtNumber, varIndex);
						} else {
							// throw exception, or invalid query
						}
					} else { // Modifies(leftSynonym, "x")
						if (synonymTable->find(leftSynonym) == synonymTable->end()){ // Modifies("Procedure First", "x")
							if (procTable->containsProc(leftSynonym)){
								int procIndex = procTable->getProcIndex(leftSynonym);
								isSuchThatTrue = modifies->isModifiesProc(procIndex, varIndex);
							} else {
								// throw error because procedure not found
							}
						} else { // Modifies(leftSynonym, "x")
							if (synonymTable->at(leftSynonym)=="procedure"){ // Modifies(procedure, "x")
								for (int i=0; i<procTable->getSize(); i++){
									if (modifies->isModifiesProc(i, varIndex)){
										isSuchThatTrue = true;
										break;
									}
								}
							} else if (synonymTable->at(leftSynonym)=="stmt"){ // Modifies(statement/while/assign, "x")
								for (int i=1; i<=statementTable->getSize(); i++){
									if (modifies->isModifiesStmt(i, varIndex)){
										isSuchThatTrue = true;
										break;
									}
								}
							} else if (synonymTable->at(leftSynonym)=="assign"){
								for (int i=1; i<=statementTable->getSize(); i++){
									if (statementTable->getTNode(i)->getNodeType()=="assign"&&modifies->isModifiesStmt(i, varIndex)){
										isSuchThatTrue = true;
										break;
									}
								}
							} else if (synonymTable->at(leftSynonym)=="while"){
								for (int i=1; i<=statementTable->getSize(); i++){
									if (statementTable->getTNode(i)->getNodeType()=="while"&&modifies->isModifiesStmt(i, varIndex)){
										isSuchThatTrue = true;
										break;
									}
								}
							} else if (synonymTable->at(leftSynonym)=="if"){
								// not implemented
							} else {
								// throw exception
							}
						}
					}
				} else {
					// throw exception because varSynonym is not found in program
				}
			} else { // varSynonym is a variable entity, Modifies(*, var)
					string leftSynonym = suchThatTree->getRootNode()->getChild(0)->getKey();
					if (leftSynonym.empty()) { // Modifies(1, var)
						int stmtNumber = suchThatTree->getRootNode()->getChild(0)->getValue();
						if (0<stmtNumber&&stmtNumber<=statementTable->getSize()){
							for (int i=0; i<varTable->getSize(); i++){
								if (modifies->isModifiesStmt(stmtNumber, i)){
									isSuchThatTrue = true;
									break;
								}
							}
						} else {
							// throw exception, or invalid query
						}
					} else { // Modifies(leftSynonym, var)
						if (synonymTable->find(leftSynonym) == synonymTable->end()){ // Modifies("Procedure First", var)
							if (procTable->containsProc(leftSynonym)){
								int procIndex = procTable->getProcIndex(leftSynonym);
								for (int i=0; i<varTable->getSize(); i++){
									if (modifies->isModifiesProc(procIndex, i)){
										isSuchThatTrue = true;
										break;
									}
								}
							} else {
								// throw error because procedure not found
							}
						} else { // Modifies(leftSynonym, var)
							if (synonymTable->at(leftSynonym)=="procedure"){ // Modifies(procedure, var)
								for (int i=0; i<procTable->getSize(); i++){
									for (int j=0; j<varTable->getSize(); j++){
										if (modifies->isModifiesProc(i, j)){
											isSuchThatTrue = true;
											break;
										}
									}
									if (isSuchThatTrue) break;
								}
							} else if (synonymTable->at(leftSynonym)=="stmt"){ // Modifies(statement/while/assign/etc., var)
								for (int i=1; i<=statementTable->getSize(); i++){
									for (int j=0; j<varTable->getSize(); j++){
										if (modifies->isModifiesStmt(i, j)){
											isSuchThatTrue = true;
											break;
										}
									}
									if (isSuchThatTrue) break;
								}
							} else if (synonymTable->at(leftSynonym)=="assign"){
								for (int i=1; i<=statementTable->getSize(); i++){
									if (statementTable->getTNode(i)->getNodeType()=="assign"){
										for (int j=0; j<varTable->getSize(); j++){
											if (modifies->isModifiesStmt(i, j)){
												isSuchThatTrue = true;
												break;
											}											
										}
										if (isSuchThatTrue) break;
									}
									if (isSuchThatTrue) break;
								}
							} else if (synonymTable->at(leftSynonym)=="while"){
								for (int i=1; i<=statementTable->getSize(); i++){
									if (statementTable->getTNode(i)->getNodeType()=="while"){
										for (int j=0; j<varTable->getSize(); j++){
											if (modifies->isModifiesStmt(i, j)){
												isSuchThatTrue = true;
												break;
											}											
										}
										if (isSuchThatTrue) break;
									}
									if (isSuchThatTrue) break;
								}
							} else if (synonymTable->at(leftSynonym)=="if"){
								// not implemented
							} else {
								// throw exception							
							}
						}
					}
			} 
		} else {
			// throw exception
		}
		if (isSuchThatTrue){
			// fill answer for different type of selectSynonym such as procedure, statement, while, assign, variable, prog_line
			if (synonymTable->at(selectSynonym)=="stmt"||
				synonymTable->at(selectSynonym)=="assign"||
				synonymTable->at(selectSynonym)=="while"||
				synonymTable->at(selectSynonym)=="if"||
				synonymTable->at(selectSynonym)=="prog_line"){
					if (synonymTable->at(selectSynonym)=="stmt"||synonymTable->at(selectSynonym)=="prog_line"){
						for (int i=1; i<=statementTable->getSize(); i++){
							answer.push_back(i);
						}
					} else {
						answer = statementTable->getStmtNumUsingNodeType(synonymTable->at(selectSynonym));
					}					
			} else if (synonymTable->at(selectSynonym)=="variable"){
				for (int i=0; i<varTable->getSize(); i++){
					answer.push_back(i);
				}
			} else if (synonymTable->at(selectSynonym)=="procedure"){
				for (int i=0; i<procTable->getSize(); i++){
					answer.push_back(i);
				}
			} else {
				// throw exception
			}
		} else {
			// nothing in answer
		}
	}
	return answer;
}

/******* Helper Level 4 *******/
bool checkSynonymInSuchThat(string selectSynonym, QueryTree* suchThatTree){
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
vector<int> solveForIntSuchThatModifies(string selectSynonym, map<STRING, STRING>* synonymTable, QueryTree* suchThatTree){
	vector<int> answer;
	bool isSynonymInSuchThat = checkSynonymInSuchThat(selectSynonym, suchThatTree);
	if (isSynonymInSuchThat){ // synonym is contained in such that statement
		if (selectSynonym == suchThatTree->getRootNode()->getChild(0)->getKey()){ // Select synonym such that Modifies(synonym, *)
			string rightSynonym = suchThatTree->getRootNode()->getChild(0)->getKey();
			if (synonymTable->at(rightSynonym).empty()){ // Select synonym such that Modifies(synonym, aString);
				/*
				if (VarTable.containsVar(rightSynonym){ // if another synonym is a variable
				int varIndex = VarTable.getVarIndex(rightSynonym);
					if (synonymTable->at(selectSynonym)=="procedure"){
						answer = Modifies.getModifiersProc(varIndex);
					} else {
						answer = Modifies.getModifiersStmt(varIndex);
					}
				} else {
				// throw error because another synonym is not found
				}
				*/
			} else { // Select synonym such that Modifies(symnonym, another synonym)
				if (synonymTable->at(selectSynonym) == "procedure"){
					/*
					vector<pair<int, int>>* result = Modifies.getModifiesProc();
					for (int i=0; i<result->size(); i++){
					answer->push_back(result->at(i).first);
					}
					*/
				}
				else {
					/*
					vector<pair<int, int>>* result = Modifies.getModifiesStmt();
					for (int i=0; i<result->size(); i++){
					answer->push_back(result->at(i).first);
					}
					*/
				}
			}
		} else if (selectSynonym == suchThatTree->getRootNode()->getChild(1)->getKey()){ // Select synonym such that Modifies(*, synonym)
			// need assertion, if selectSynonym is variable
			string leftSynonym = suchThatTree->getRootNode()->getChild(0)->getKey();
			if (leftSynonym.empty()){ // Select synonym such that Modifies(anotherSynonym, synonym)
				if (synonymTable->at(leftSynonym).empty()){ // another synonym not in synonym table
					/*
					if (ProcTable.containsProc(leftSynonym){ // if another synonym is a procedure
						int procIndex = ProcTable.getProcIndex(leftSynonym);
						answer = Modifies.getModifiedVarProc(procIndex);
					} else {
						// throw error because another synonym is not found
					}
					*/
				} else {
					if (synonymTable->at(leftSynonym)=="procedure"){
						/*
						vector<pair<int, int>>* result = Modifies.getModifiesProc();
						for (int i=0; i<result->size(); i++){
							answer->push_back(result->at(i).second);
						}
						*/
					} else {
						/*
						vector<pair<int, int>>* result = Modifies.getModifiesStmt();
						for (int i=0; i<result->size(); i++){
							answer->push_back(result->at(i).second);
						}
						*/
					}
				}
			} else { // Select synonym such that Modifies(INDEX, synonym)
				int stmtIndex = suchThatTree->getRootNode()->getChild(0)->getValue();
				/*
					answer = Modifies.getModifiedVarStmt(stmtIndex);
				*/
			}
		}
	} else { // synonym is not contained in such that statement
		// evaluate such that statement as boolean and solve for it
		bool isSuchThatTrue = false;
		string varSynonym = suchThatTree->getRootNode()->getChild(1)->getKey();
		if (synonymTable->at(varSynonym).empty()){ // varSynonym is a variable name, Modifies(*, "x")
			/*
			if (VarTable.containsVar(varSynonym)){
				int varIndex = VarTable.getVarIndex(varSynonym);
				string leftSynonym = suchThatTree->getRootNode()->getChild(0)->getKey();
				if (leftSynonym.empty()) { // Modifies(1, "x")
					int stmtNumber = suchThatTree->getRootNode()->getChild(0)->getValue();
					if (stmtNumber<StatementTable.getSize()){
						isSuchThatTrue = Modifies.isModifiesStmt(stmtNumber, varIndex);
					} else {
						// throw exception, or invalid query
					}
				} else { // Modifies(leftSynonym, "x")
					if (synonymTable->at(leftSynonym).empty()){ Modifies("Procedure First", "x")
						if (ProcTable.containsProc(leftSynonym)){
							int procIndex = ProcTable.getProcIndex(leftSynonym);
							isSuchThatTrue = Modifies.isModifiesProc(procIndex, varIndex);
						} else {
							// throw error because procedure not found
						}
					} else { // Modifies(leftSynonym, "x")
						if (synonymTable->at(leftSynonym)=="procedure"){ // Modifies(procedure, "x")
							for (int i=0; i<ProcTable.getSize(); i++){
								if (Modifies.isModifiesProc(i, varIndex)){
									isSuchThatTrue = true;
									break;
								}
							}
						} else { // Modifies(statement/while/assign, "x")
							for (int i=0; i<StatementTable.getSize(); i++){
								if (Modifies.isModifiesStmt(i, varIndex)){
									isSuchThatTrue = true;
									break;
								}
							}
						}
					}
				}
			} else {
				// throw exception because varSynonym is not found in program
			}
			*/
		} else { // varSynonym is a variable entity, Modifies(*, var)
			/*
				string leftSynonym = suchThatTree->getRootNode()->getChild(0)->getKey();
				if (leftSynonym.empty()) { // Modifies(1, var)
					int stmtNumber = suchThatTree->getRootNode()->getChild(0)->getValue();
					if (stmtNumber<StatementTable.getSize()){
						for (int i=0; i<VarTable.getSize(); i++){
							if (Modifies.isModifiesStmt(stmtNumber, i)){
								isSuchThatTrue = true;
								break;
							}
						}
					} else {
						// throw exception, or invalid query
					}
				} else { // Modifies(leftSynonym, var)
					if (synonymTable->at(leftSynonym).empty()){ Modifies("Procedure First", var)
						if (ProcTable.containsProc(leftSynonym)){
							int procIndex = ProcTable.getProcIndex(leftSynonym);
							for (int i=0; i<VarTable.getSize(); i++){
								if (Modifies.isModifiesProc(procIndex, i)){
									isSuchThatTrue = true;
									break;
								}
							}
						} else {
							// throw error because procedure not found
						}
					} else { // Modifies(leftSynonym, var)
						if (synonymTable->at(leftSynonym)=="procedure"){ // Modifies(procedure, var)
							loop:
							for (int i=0; i<ProcTable.getSize(); i++){
								for (int j=0; j<VarTable.getSize(); j++{
									if (Modifies.isModifiesProc(i, j)){
										isSuchThatTrue = true;
										break loop;
									}
								}
							}
						} else { // Modifies(statement/while/assign, "x")
							loop:
							for (int i=0; i<StatementTable.getSize(); i++){
								for (int j=0; j<VarTable.getSize(); j++{
									if (Modifies.isModifiesStmt(i, j)){
										isSuchThatTrue = true;
										break loop;
									}
								}
							}
						}
					}
				}
			*/
		}
		if (isSuchThatTrue){
			// fill answer for different type of selectSynonym such as procedure, statement, while, assign, variable, prog_line
		} else {
			// nothing in answer
		}
	}
	return answer;
}

vector<int> solveForIntSuchThatUses(string selectSynonym, map<STRING, STRING>* synonymTable, QueryTree* suchThatTree){
	vector<int> answer;
	bool isSynonymInSuchThat = checkSynonymInSuchThat(selectSynonym, suchThatTree);
	if (isSynonymInSuchThat){ // synonym is contained in such that statement
		if (selectSynonym == suchThatTree->getRootNode()->getChild(0)->getKey()){ // Select synonym such that Uses(synonym, *)
			string rightSynonym = suchThatTree->getRootNode()->getChild(0)->getKey();
			if (synonymTable->at(rightSynonym).empty()){ // Select synonym such that Uses(synonym, aString);
				/*
				if (VarTable.containsVar(rightSynonym){ // if another synonym is a variable
				int varIndex = VarTable.getVarIndex(rightSynonym);
					if (synonymTable->at(selectSynonym)=="procedure"){
						answer = Uses.getUsersProc(varIndex);
					} else {
						answer = Uses.getUsersStmt(varIndex);
					}
				} else {
				// throw error because another synonym is not found
				}
				*/
			} else { // Select synonym such that Uses(symnonym, another synonym)
				if (synonymTable->at(selectSynonym) == "procedure"){
					/*
					vector<pair<int, int>>* result = Uses.getUsesProc();
					for (int i=0; i<result->size(); i++){
						answer->push_back(result->at(i).first);
					}
					*/
				}
				else {
					/*
					vector<pair<int, int>>* result = Uses.getUsesStmt();
						for (int i=0; i<result->size(); i++){
					answer->push_back(result->at(i).first);
					}
					*/
				}
			}
		} else if (selectSynonym == suchThatTree->getRootNode()->getChild(1)->getKey()){ // Select synonym such that Uses(*, synonym)
			// need assertion, if selectSynonym is variable
			string leftSynonym = suchThatTree->getRootNode()->getChild(0)->getKey();
			if (leftSynonym.empty()){ // Select synonym such that Uses(anotherSynonym, synonym)
				if (synonymTable->at(leftSynonym).empty()){ // another synonym not in synonym table
					/*
					if (ProcTable.containsProc(leftSynonym){ // if another synonym is a procedure
						int procIndex = ProcTable.getProcIndex(leftSynonym);
						answer = Uses.getUsedVarProc(procIndex);
					} else {
						// throw error because another synonym is not found
					}
					*/
				} else {
					if (synonymTable->at(leftSynonym)=="procedure"){
						/*
						vector<pair<int, int>>* result = Uses.getUsesProc();
						for (int i=0; i<result->size(); i++){
							answer->push_back(result->at(i).second);
						}
						*/
					} else {
						/*
						vector<pair<int, int>>* result = Uses.getUsesStmt();
						for (int i=0; i<result->size(); i++){
							answer->push_back(result->at(i).second);
						}
						*/
					}
				}
			} else { // Select synonym such that Uses(INDEX, synonym)
				int stmtIndex = suchThatTree->getRootNode()->getChild(0)->getValue();
				/*
					answer = Uses.getUsedVarStmt(stmtIndex);
				*/
			}
		}
	} else { // synonym is not contained in such that statement
		// evaluate such that statement as boolean and solve for it
		bool isSuchThatTrue = false;
		string varSynonym = suchThatTree->getRootNode()->getChild(1)->getKey();
		if (synonymTable->at(varSynonym).empty()){ // varSynonym is a variable name, Uses(*, "x")
			/*
			if (VarTable.containsVar(varSynonym)){
				int varIndex = VarTable.getVarIndex(varSynonym);
				string leftSynonym = suchThatTree->getRootNode()->getChild(0)->getKey();
				if (leftSynonym.empty()) { // Uses(1, "x")
					int stmtNumber = suchThatTree->getRootNode()->getChild(0)->getValue();
					if (stmtNumber<StatementTable.getSize()){
						isSuchThatTrue = Uses.isUsesStmt(stmtNumber, varIndex);
					} else {
						// throw exception, or invalid query
					}
				} else { // Uses(leftSynonym, "x")
					if (synonymTable->at(leftSynonym).empty()){ Uses("Procedure First", "x")
						if (ProcTable.containsProc(leftSynonym)){
							int procIndex = ProcTable.getProcIndex(leftSynonym);
							isSuchThatTrue = Uses.isUsesProc(procIndex, varIndex);
						} else {
							// throw error because procedure not found
						}
					} else { // Uses(leftSynonym, "x")
						if (synonymTable->at(leftSynonym)=="procedure"){ // Uses(procedure, "x")
							for (int i=0; i<ProcTable.getSize(); i++){
								if (Uses.isUsesProc(i, varIndex)){
									isSuchThatTrue = true;
									break;
								}
							}
						} else { // Uses(statement/while/assign, "x")
							for (int i=0; i<StatementTable.getSize(); i++){
								if (Uses.isUsesStmt(i, varIndex)){
									isSuchThatTrue = true;
									break;
								}
							}
						}
					}
				}
			} else {
				// throw exception because varSynonym is not found in program
			}
			*/
		} else { // varSynonym is a variable entity, Uses(*, var)
			/*
				string leftSynonym = suchThatTree->getRootNode()->getChild(0)->getKey();
				if (leftSynonym.empty()) { // Uses(1, var)
					int stmtNumber = suchThatTree->getRootNode()->getChild(0)->getValue();
					if (stmtNumber<StatementTable.getSize()){
						for (int i=0; i<VarTable.getSize(); i++){
							if (Uses.isUsesStmt(stmtNumber, i)){
								isSuchThatTrue = true;
								break;
							}
						}
					} else {
						// throw exception, or invalid query
					}
				} else { // Uses(leftSynonym, var)
					if (synonymTable->at(leftSynonym).empty()){ Uses("Procedure First", var)
						if (ProcTable.containsProc(leftSynonym)){
							int procIndex = ProcTable.getProcIndex(leftSynonym);
							for (int i=0; i<VarTable.getSize(); i++){
								if (Uses.isUsesProc(procIndex, i)){
									isSuchThatTrue = true;
									break;
								}
							}
						} else {
							// throw error because procedure not found
						}
					} else { // Uses(leftSynonym, var)
						if (synonymTable->at(leftSynonym)=="procedure"){ // Modifies(procedure, var)
							loop:
							for (int i=0; i<ProcTable.getSize(); i++){
								for (int j=0; j<VarTable.getSize(); j++{
									if (Uses.isUsesProc(i, j)){
										isSuchThatTrue = true;
										break loop;
									}
								}
							}
						} else { // Uses(statement/while/assign, "x")
							loop:
							for (int i=0; i<StatementTable.getSize(); i++){
								for (int j=0; j<VarTable.getSize(); j++{
									if (Uses.isUsesStmt(i, j)){
										isSuchThatTrue = true;
										break loop;
									}
								}
							}
						}
					}
				}
			*/
		}
		if (isSuchThatTrue){
			// fill answer for different type of selectSynonym such as procedure, statement, while, assign, variable, prog_line
		} else {
			// nothing in answer
		}
	}
	return answer;
}

vector<int> solveForIntSuchThatFollows(string selectSynonym, map<STRING, STRING>* synonymTable, QueryTree* suchThatTree){
	vector<int> answer;
	bool isSynonymInSuchThat = checkSynonymInSuchThat(selectSynonym, suchThatTree);
	if (isSynonymInSuchThat){ // Select synonym such that Follows(synonym, *) (Follows(*, synonym))
		if (selectSynonym == suchThatTree->getRootNode()->getChild(0)->getKey()){ // Select synonym such that Follows(synonym, *)
			string stmtSynonym = suchThatTree->getRootNode()->getChild(1)->getKey();
			if (stmtSynonym.empty()){ // Select synonym such that Follows(synonym, 1)
				int stmtIndex = suchThatTree->getRootNode()->getChild(1)->getValue();
				/*
				if(stmtIndex<StatementTable.getSize()){
					answer = Follows.getFollowees(stmtIndex);
				} else {
					// throw exception
				}
				*/
			} else { // Select synonym such that Follows(synonym, another Synonym)
				if (synonymTable->at(stmtSynonym)=="stmt"){
					// answer = Follows.getAllFolloweesStmt();
				} else if (synonymTable->at(stmtSynonym)=="assign"){
					/*
					vector<int> assignList = StatementTable.getStmtNumUsingNodeType("ASSIGN_NODE");
					for (int i=0; i<assignList.size(); i++){
						vector<int> result = Follows.getFollowees(assignList.at(i));
						answer.insert(answer.end(), result.begin(), result.end());
					}
					*/
				} else if (synonymTable->at(stmtSynonym)=="while"){
					/*
					vector<int> whileList = StatementTable.getStmtNumUsingNodeType("WHILE_NODE");
					for (int i=0; i<whileList.size(); i++){
						vector<int> result = Follows.getFollowees(whileList.at(i));
						answer.insert(answer.end(), result.begin(), result.end());
					}
					*/
				} else if (synonymTable->at(stmtSynonym)=="if"){
				    // not implemented	
				} else {
					// throw exception
				}
			}
		} else { // Select synonym such that Follows(*, synonym)
			string stmtSynonym = suchThatTree->getRootNode()->getChild(1)->getKey();
			if (stmtSynonym.empty()){ // Select synonym such that Follows(1, synonym)
				int stmtIndex = suchThatTree->getRootNode()->getChild(1)->getValue();
				/*
				if(stmtIndex<StatementTable.getSize()){
					answer = Follows.getFollowers(stmtIndex);
				} else {
					// throw exception
				}
				*/
			} else { // Select synonym such that Follows(another Synonym, synonym)
				if (synonymTable->at(stmtSynonym)=="stmt"){
					// answer = Follows.getAllFollowersStmt();
				} else if (synonymTable->at(stmtSynonym)=="assign"){
					/*
					vector<int> assignList = StatementTable.getStmtNumUsingNodeType("ASSIGN_NODE");
					for (int i=0; i<assignList.size(); i++){
						vector<int> result = Follows.getFollowers(assignList.at(i));
						answer.insert(answer.end(), result.begin(), result.end());
					}
					*/
				} else if (synonymTable->at(stmtSynonym)=="while"){
					/*
					vector<int> whileList = StatementTable.getStmtNumUsingNodeType("WHILE_NODE");
					for (int i=0; i<whileList.size(); i++){
						vector<int> result = Follows.getFollowers(whileList.at(i));
						answer.insert(answer.end(), result.begin(), result.end());
					}
					*/
				} else if (synonymTable->at(stmtSynonym)=="if"){
				    // not implemented	
				} else {
					// throw exception
				}
			}
		}
	} else { // synonym is not in Follows(*, *)
		bool isSuchThatTrue = false;
		string leftSynonym = suchThatTree->getRootNode()->getChild(0)->getKey();
		string rightSynonym = suchThatTree->getRootNode()->getChild(1)->getKey();
		if (leftSynonym.empty()&&rightSynonym.empty()){ // Follows(1, 2);
			int leftStmtIndex = suchThatTree->getRootNode()->getChild(0)->getValue();
			int rightStmtIndex = suchThatTree->getRootNode()->getChild(1)->getValue();
			/*
			if (leftStmtIndex>StatementTable.getSize()||rightStmtIndex>StatementTable.getSize()){
				// throw exception
			} else {
				isSuchThatTrue = Follows.isFollowsTrue(leftStmtIndex, rightStmtIndex);
			}
			*/
		} else if (leftSynonym.empty()){ // Follows(1, synonym)
			int leftStmtIndex = suchThatTree->getRootNode()->getChild(0)->getValue();
			if (synonymTable->at(rightSynonym)=="stmt"){
				/*
				for (int i=0; i<StatementTable.getSize(); i++){
					if (Follows.isFollowsTrue(leftStmtIndex, i)){
						isSuchThatTrue = true;
						break;
					}
				}
				*/
			} else if (synonymTable->at(rightSynonym)=="assign"){
				/*
				for (int i=0; i<StatementTable.getSize(); i++){
					if (StatementTable.getTNode(i)->getNodeType=="ASSIGN_NODE"&&Follows.isFollowsTrue(leftStmtIndex, i)){
						isSuchThatTrue = true;
						break;
					}
				}
				*/
			} else if (synonymTable->at(rightSynonym)=="while"){
				/*
				for (int i=0; i<StatementTable.getSize(); i++){
					if (StatementTable.getTNode(i)->getNodeType=="WHILE_NODE"&&Follows.isFollowsTrue(leftStmtIndex, i)){
						isSuchThatTrue = true;
						break;
					}
				}
				*/			
			} else if (synonymTable->at(rightSynonym)=="if"){
				// not implemented
			} else {
				// throw exception
			}
		} else if (rightSynonym.empty()){ // Follows(synonym, 2)
			int rightStmtIndex = suchThatTree->getRootNode()->getChild(1)->getValue();
			if (synonymTable->at(leftSynonym)=="stmt"){
				/*
				for (int i=0; i<StatementTable.getSize(); i++){
					if (Follows.isFollowsTrue(i, rightStmtIndex)){
						isSuchThatTrue = true;
						break;
					}
				}
				*/
			} else if (synonymTable->at(leftSynonym)=="assign"){
				/*
				for (int i=0; i<StatementTable.getSize(); i++){
					if (StatementTable.getTNode(i)->getNodeType=="ASSIGN_NODE"&&Follows.isFollowsTrue(i, rightStmtIndex)){
						isSuchThatTrue = true;
						break;
					}
				}
				*/
			} else if (synonymTable->at(leftSynonym)=="while"){
				/*
				for (int i=0; i<StatementTable.getSize(); i++){
					if (StatementTable.getTNode(i)->getNodeType=="WHILE_NODE"&&Follows.isFollowsTrue(i, rightStmtIndex)){
						isSuchThatTrue = true;
						break;
					}
				}
				*/
			} else if (synonymTable->at(leftSynonym)=="if"){
				// not implemented
			} else {
				// throw exception
			}
		} else { // Follows(synonym1, synonym2)
			if(synonymTable->at(leftSynonym).empty()||synonymTable->at(rightSynonym).empty()){
				// throw exception
			} else if (synonymTable->at(leftSynonym)=="stmt"){ // Follows(s1, synonym2)
				if (synonymTable->at(rightSynonym)=="stmt"){ // Follows(s1, s2) 
					/*
					loop:
					for (int i=0; i<StatementTable.getSize(); i++){
						for (int j=0; j<StatementTable.getSize(); j++){
							if (Follows.isFollowsTrue(i, j)){
								isSuchThatTrue = true;
								break loop;
							}			
						}
					}
					*/
				} else if (synonymTable->at(rightSynonym)=="assign"){ // Follows(s1, a2)
					/*
					loop:
					for (int i=0; i<StatementTable.getSize(); i++){
							for (int j=0; j<StatementTable.getSize(); j++){
								if (StatementTable.getTNode(j)->getNodeType=="ASSIGN_NODE"&&Follows.isFollowsTrue(i, j)){
									isSuchThatTrue = true;
									break loop;
								}			
							}
					}
					*/
				} else if (synonymTable->at(rightSynonym)=="while"){ // Follows(s1, w2)
					/*
					loop:
					for (int i=0; i<StatementTable.getSize(); i++){
							for (int j=0; j<StatementTable.getSize(); j++){
								if (StatementTable.getTNode(j)->getNodeType=="WHILE_NODE"&&Follows.isFollowsTrue(i, j)){
									isSuchThatTrue = true;
									break loop;
								}			
							}
					}
					*/				
				} else if (synonymTable->at(rightSynonym)=="if"){
					// not implemented
				} else {
					// throw exception
				}
			} else if (synonymTable->at(leftSynonym)=="assign"){ // Follows(a1, synonym2)
				if (synonymTable->at(rightSynonym)=="stmt"){ // Follows(a1, s2) 
					/*
					loop:
					for (int i=0; i<StatementTable.getSize(); i++){
						if (StatementTable.getTNode(i)->getNodeType=="ASSIGN_NODE"{
							for (int j=0; j<StatementTable.getSize(); j++){
								if (Follows.isFollowsTrue(i, j)){
									isSuchThatTrue = true;
									break loop;
								}			
							}
						}
					}
					*/
				} else if (synonymTable->at(rightSynonym)=="assign"){ // Follows(a1, a2)
					/*
					loop:
					for (int i=0; i<StatementTable.getSize(); i++){
						if (StatementTable.getTNode(i)->getNodeType=="ASSIGN_NODE"{
							for (int j=0; j<StatementTable.getSize(); j++){
								if (StatementTable.getTNode(j)->getNodeType=="ASSIGN_NODE"&&Follows.isFollowsTrue(i, j)){
									isSuchThatTrue = true;
									break loop;
								}			
							}
						}
					}
					*/
				} else if (synonymTable->at(rightSynonym)=="while"){ // Follows(a1, w2)
					/*
					loop:
					for (int i=0; i<StatementTable.getSize(); i++){
						if (StatementTable.getTNode(i)->getNodeType=="ASSIGN_NODE"{
							for (int j=0; j<StatementTable.getSize(); j++){
								if (StatementTable.getTNode(j)->getNodeType=="WHILE_NODE"&&Follows.isFollowsTrue(i, j)){
									isSuchThatTrue = true;
									break loop;
								}			
							}
						}
					}
					*/
				} else if (synonymTable->at(rightSynonym)=="if"){
					// not implemented
				} else {
					// throw exception
				}
			} else if (synonymTable->at(leftSynonym)=="while"){ // Follows(w1, synonym2)
				if (synonymTable->at(rightSynonym)=="stmt"){ // Follows(w1, s2) 
					/*
					loop:
					for (int i=0; i<StatementTable.getSize(); i++){
						if (StatementTable.getTNode(i)->getNodeType=="WHILE_NODE"{
							for (int j=0; j<StatementTable.getSize(); j++){
								if (Follows.isFollowsTrue(i, j)){
									isSuchThatTrue = true;
									break loop;
								}			
							}
						}
					}
					*/
				} else if (synonymTable->at(rightSynonym)=="assign"){ // Follows(w1, a2)
					/*
					loop:
					for (int i=0; i<StatementTable.getSize(); i++){
						if (StatementTable.getTNode(i)->getNodeType=="WHILE_NODE"{
							for (int j=0; j<StatementTable.getSize(); j++){
								if (StatementTable.getTNode(j)->getNodeType=="ASSIGN_NODE"&&Follows.isFollowsTrue(i, j)){
									isSuchThatTrue = true;
									break loop;
								}			
							}
						}
					}
					*/
				} else if (synonymTable->at(rightSynonym)=="while"){ // Follows(w1, w2)
					/*
					loop:
					for (int i=0; i<StatementTable.getSize(); i++){
						if (StatementTable.getTNode(i)->getNodeType=="WHILE_NODE"{
							for (int j=0; j<StatementTable.getSize(); j++){
								if (StatementTable.getTNode(j)->getNodeType=="WHILE_NODE"&&Follows.isFollowsTrue(i, j)){
									isSuchThatTrue = true;
									break loop;
								}			
							}
						}
					}
					*/
				} else if (synonymTable->at(rightSynonym)=="if"){
					// not implemented
				} else {
					// throw exception
				}
			} else if (synonymTable->at(leftSynonym)=="if"){
				// not implemented
			} else {
				// throw exception
			}
		}
		if (isSuchThatTrue){
			// fill answer for different type of selectSynonym such as procedure, statement, while, assign, variable, prog_line
		} else {
			// nothing in answer
		}
	}
	return answer;
}

vector<int> solveForIntSuchThatFollowsStar(string selectSynonym, map<STRING, STRING>* synonymTable, QueryTree* suchThatTree){
	vector<int> answer;
	bool isSynonymInSuchThat = checkSynonymInSuchThat(selectSynonym, suchThatTree);
	if (isSynonymInSuchThat){ // Select synonym such that Follows*(synonym, *)  (Follows*(*, synonym))
		
	} else { // synonym is not in Follows*(*, *)

	}
	return answer;
}

vector<int> solveForIntSuchThatParent(string selectSynonym, map<STRING, STRING>* synonymTable, QueryTree* suchThatTree){
	vector<int> answer;
	bool isSynonymInSuchThat = checkSynonymInSuchThat(selectSynonym, suchThatTree);
	if (isSynonymInSuchThat){ // Select synonym such that Parent(synonym, *)  (Parent(*, synonym))
		
	} else { // synonym is not in Parent(*, *)

	}
	return answer;
}

vector<int> solveForIntSuchThatParentStar(string selectSynonym, map<STRING, STRING>* synonymTable, QueryTree* suchThatTree){
	vector<int> answer;
	bool isSynonymInSuchThat = checkSynonymInSuchThat(selectSynonym, suchThatTree);
	if (isSynonymInSuchThat){ // Select synonym such that Parent*(synonym, *)  (Parent*(*, synonym))
		
	} else { // synonym is not in Parent*(*, *)

	}
	return answer;
}

/******* Helper Level 2 *******/

vector<int> solveForSuchThat(string selectSynonym, map<STRING, STRING>* synonymTable, QueryTree* tree){
	vector<int> answer;
	// only one such that, can make into a loop later
	// for future development with many such that, need to check dependency and start with the lowest first
	// for example, "Select w such that Parent(w, a) and Follows(a, a1) and Modifies(a1, var1) and Uses(if, var1)",
	// we need to evaluate such that from right to left to find w
	QueryTree* suchThatSubtree = tree->getSubtreeFromNode(tree->getRootNode()->getChild(1)->getChild(0));
	string suchThatType = suchThatSubtree->getRootNode()->getKey();
	if (suchThatType == "Modifies"){
		answer = solveForIntSuchThatModifies(selectSynonym, synonymTable, suchThatSubtree);
	} else if (suchThatType == "Uses"){
		answer = solveForIntSuchThatUses(selectSynonym, synonymTable, suchThatSubtree);
	} else if (suchThatType == "Follows"){
		answer = solveForIntSuchThatFollows(selectSynonym, synonymTable, suchThatSubtree);
	} else if (suchThatType == "Follows*"){
		answer = solveForIntSuchThatFollowsStar(selectSynonym, synonymTable, suchThatSubtree);
	} else if (suchThatType == "Parent"){
		answer = solveForIntSuchThatParent(selectSynonym, synonymTable, suchThatSubtree);
	} else if (suchThatType == "Parent*"){
		answer = solveForIntSuchThatParentStar(selectSynonym, synonymTable, suchThatSubtree);
	}

	return answer;
}

vector<int> solveForPattern(string selectSynonym, map<STRING, STRING>* synonymTable, QueryTree* tree){
	vector<int> answer;
	return answer;
}

/******* Helper Level 1 *******/
// Method to collect solution from different conditional clauses (such that, with, pattern, etc.) and combine
vector<int> solve(string selectSynonym, map<STRING, STRING>* synonymTable, QueryTree* tree){
	vector<int> resultFromSuchThat = solveForSuchThat(selectSynonym, synonymTable, tree);
	vector<int> resultFromPattern = solveForPattern(selectSynonym, synonymTable, tree);
	vector<int> answer;
	answer.insert(answer.end(), resultFromSuchThat.begin(), resultFromSuchThat.end());
	answer.insert(answer.end(), resultFromPattern.begin(), resultFromPattern.end());
	return answer;
}

/******* Methods *******/
// Method to get and printout final result
STRING QueryEvaluator::evaluate(map<STRING, STRING>* synonymTable, QueryTree* tree){

	string output = "Hello World!";
	
	string selectSynonym = tree->getRootNode()->getChild(0)->getChild(0)->getKey();
	// Need to check if selectSynonym is inside synonymTable
	// TODO: throws exception
	vector<int> answer = solve(selectSynonym, synonymTable, tree);
	string temp = "";
	if (synonymTable->at(selectSynonym)=="variable"||
		synonymTable->at(selectSynonym)=="procedure"){
		if (synonymTable->at(selectSynonym)=="variable"){
			for (size_t i=0; i<answer.size(); i++){
				//temp = temp + (""+VarTable.getVarName(answer->at(i)));
				if (i!=answer.size()-1){
					temp = temp+", ";
				}
			}
		} else {
			for (size_t i=0; i<answer.size(); i++){
				//temp = temp + (""+ProcTable.getProcName(answer->at(i)));
				if (i!=answer.size()-1){
					temp = temp+", ";
				}
			}
		}
	} else {
		for (size_t i=0; i<answer.size(); i++){
			temp = temp + (""+answer.at(i));
			if (i!=answer.size()-1){
				temp = temp+", ";
			}
		}
	}
	output = temp;
	return output;
};