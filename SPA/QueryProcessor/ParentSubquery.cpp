#pragma once
#include <string>
#include <vector>
#include <map>
#include "SPA/QueryProcessor/Subquery.h"
#include "SPA/PKB/PKBController.h"

using namespace std;

class ParentSubquery : public Subquery{
public:
	ParentSubquery(map<string, string>* m, PKBController* p) : Subquery(m, p){
	}

	ResultTuple* solve(){
		ResultTuple* ans;
		switch (isSyn){
		case 0:
			ans = solveIndexIndex();
			break;
		case 1:
			ans = solveIndexSyn();
			break;
		case 2:
			ans = solveSynIndex();
			break;
		case 3:
			ans = solveSynSyn();
			break;
		default:
			break;
		}
		return ans;
	}

	ResultTuple* solve(ResultTuple*){
		// not implemented
		return &ResultTuple();
	}

	void addToResult(int val1, int val2, ResultTuple* answer){
		vector<int> row;
		row.push_back(val1);
		row.push_back(val2);
		answer->addResultRow(row);
	}

	ResultTuple* solveIndexIndex(){
		ResultTuple* answer = new ResultTuple();
		if (pkb->parentTable.isParentTrue(leftIndex, rightIndex)){
			synonymTable->insert(make_pair(to_string((long long)leftIndex), "number"));
			synonymTable->insert(make_pair(to_string((long long)rightIndex), "number"));
			addToResult(leftIndex, rightIndex, answer);
		}
		return answer;
	}

	ResultTuple* solveIndexSyn(){
		ResultTuple* answer = new ResultTuple();
		if (synonymTable->find(rightSynonym) != synonymTable->end()){ // string is a synonym
			synonymTable->insert(make_pair(to_string((long long)leftIndex), "number"));
			vector<int> temp = pkb->parentTable.getChildren(leftIndex);
			if (synonymTable->at(rightSynonym)=="stmt"||synonymTable->at(rightSynonym)=="prog_line"){
				populateAnswerIndexSyn(temp, answer);
			} else if (synonymTable->at(rightSynonym)=="assign" || synonymTable->at(rightSynonym)=="while" || synonymTable->at(rightSynonym)=="if"){
				populateAnswerIndexSyn(synToNodeType.at(synonymTable->at(rightSynonym)), temp, answer);
			}
		}
		return answer;
	}

	void populateAnswerIndexSyn(vector<int> temp, ResultTuple* answer){
		for (size_t i = 0; i<temp.size(); i++){
			addToResult(leftIndex, temp[i], answer);
		}
	}

	void populateAnswerIndexSyn(TNODE_TYPE nodeName, vector<int> temp, ResultTuple* answer){
		for (size_t i=0; i<temp.size(); i++){
			if (pkb->statementTable.getTNode(temp[i])->getNodeType()==TNODE_NAMES[nodeName]){
				addToResult(leftIndex, temp[i], answer);
			}
		}
	}

	ResultTuple* solveSynIndex(){
		ResultTuple* answer = new ResultTuple();
		if (synonymTable->find(leftSynonym) != synonymTable->end()) { // string is a synonym
			synonymTable->insert(make_pair(to_string((long long)rightIndex), "number"));
			vector<int> temp = pkb->parentTable.getParents(rightIndex);
			if (synonymTable->at(leftSynonym)=="stmt"||synonymTable->at(leftSynonym)=="prog_line"){
				populateAnswerSynIndex(temp, answer);
			} else if (synonymTable->at(leftSynonym)=="assign" || synonymTable->at(leftSynonym)=="while" || synonymTable->at(leftSynonym)=="if"){
				populateAnswerSynIndex(synToNodeType.at((synonymTable->at(rightSynonym))), temp, answer);
			}
		}		
		return answer;
	}

	void populateAnswerSynIndex(vector<int> temp, ResultTuple* answer){
		for (size_t i = 0; i<temp.size(); i++){
			addToResult(temp[i], rightIndex, answer);
		}
	}

	void populateAnswerSynIndex(TNODE_TYPE nodeName, vector<int> temp, ResultTuple* answer){
		for (size_t i=0; i<temp.size(); i++){
			if (pkb->statementTable.getTNode(temp[i])->getNodeType()==TNODE_NAMES[nodeName]){
				addToResult(temp[i], rightIndex, answer);
			}
		}
	}

	ResultTuple* solveSynSyn(){
		ResultTuple* answer = new ResultTuple();
		if (synonymTable->find(leftSynonym) == synonymTable->end()||synonymTable->find(rightSynonym) == synonymTable->end()){
			// invalid condition
		} else if (leftSynonym==rightSynonym&&leftSynonym!="_"){
			// invalid condition
		}  else {
			if (synonymTable->at(leftSynonym)=="stmt"||synonymTable->at(leftSynonym)=="prog_line"){
				if (synonymTable->at(rightSynonym)=="stmt"||synonymTable->at(rightSynonym)=="prog_line"){
					populateAnswerSynSynNoFilter(answer);
				} else if (synonymTable->at(rightSynonym)=="assign" || synonymTable->at(rightSynonym)=="while" || synonymTable->at(rightSynonym)=="if"){
					populateAnswerSynSynRightFilter(synToNodeType.at(synonymTable->at(rightSynonym)), answer);
				} 
			} else if (synonymTable->at(leftSynonym)=="assign" || synonymTable->at(leftSynonym)=="while" || synonymTable->at(leftSynonym)=="if"){
				if (synonymTable->at(rightSynonym)=="stmt"||synonymTable->at(rightSynonym)=="prog_line"){
					populateAnswerSynSynLeftFilter(synToNodeType.at(synonymTable->at(leftSynonym)), answer);
				} else if (synonymTable->at(rightSynonym)=="assign" || synonymTable->at(rightSynonym)=="while" || synonymTable->at(rightSynonym)=="if"){
					populateAnswerSynSynBothFilter(synToNodeType.at(synonymTable->at(leftSynonym)), synToNodeType.at(synonymTable->at(rightSynonym)),answer);
				}
			}
		}
		return answer;
	}

	void populateAnswerSynSynNoFilter(ResultTuple* answer){
		for (int i=1; i<=pkb->statementTable.getSize(); i++){
			vector<int> temp = pkb->parentTable.getChildren(i);
			for (size_t j=0; j<temp.size(); j++){
				addToResult(i, temp[j], answer);
			}
		}
	}

	void populateAnswerSynSynRightFilter(TNODE_TYPE nodeName, ResultTuple* answer){
		for (int i=1; i<=pkb->statementTable.getSize(); i++){
			vector<int> temp = pkb->parentTable.getChildren(i);
			for (size_t j=0; j<temp.size(); j++){
				if (pkb->statementTable.getTNode(temp[j])->getNodeType()==TNODE_NAMES[nodeName]){
					addToResult(i, temp[j], answer);
				}
			}
		}
	}

	void populateAnswerSynSynLeftFilter(TNODE_TYPE nodeName, ResultTuple* answer){
		for (int i=1; i<=pkb->statementTable.getSize(); i++){
			if (pkb->statementTable.getTNode(i)->getNodeType()==TNODE_NAMES[nodeName]){
				vector<int> temp = pkb->parentTable.getChildren(i);
				for (size_t j=0; j<temp.size(); j++){
					addToResult(i, temp[j], answer);
				}
			}						
		}
	}

	void populateAnswerSynSynBothFilter(TNODE_TYPE node1, TNODE_TYPE node2, ResultTuple* answer){
		for (int i=1; i<=pkb->statementTable.getSize(); i++){
			if (pkb->statementTable.getTNode(i)->getNodeType()==TNODE_NAMES[node1]){
				vector<int> temp = pkb->parentTable.getChildren(i);
				for (size_t j=0; j<temp.size(); j++){
					if (pkb->statementTable.getTNode(temp[j])->getNodeType()==TNODE_NAMES[node2]){
						addToResult(i, temp[j], answer);
					}
				}
			}						
		}
	}
};