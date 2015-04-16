#pragma once
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include "Subquery.h"

using namespace std;

// WithSubquery: Subquery for with relation
// To construct WithSubquery:
// 1. WithSubquery(map<string, string>* SynonymMap, PKBController* PKB) wsubquery
// 2. wsubquery.setSynonyms(leftSyn/Index, rightSyn/Index)
// Examples for setSynonyms():
// with s1.stmt# = 1              |    wsubquery.setSynonyms("s1", 1)
// with s1.stmt# = a1.stmt#       |    wsubquery.setSynonyms("s1", "a1")
// with 3 = w1.stmt#              |    wsubquery.setSynonyms(3, "w1")
// with 3 = 2                     |    wsubquery.setSynonyms(3, 3)
// with p1.procName = v1.varName  |    wsubquery.setSynonyms("p1", "v1")
// with p1.procName = "First"     |    wsubquery.setSynonyms("p1", 1)     // 1 is the index of procedure "First" in procTable
// with v1.varName = "x"          |    wsubquery.setSynonyms("v1", 1)     // 1 is the index of variable "x" in varTable
// with const1.value = 5          |    wsubquery.setSynonyms("const1", 5) // DO NOT use constant index of 5 in constantTable, just use 5

class WithSubquery : public Subquery{
private: 
	string leftAttr;
	string rightAttr;
public:
	WithSubquery(map<string, string>* m, PKBController* p) : Subquery(m, p){
		leftAttr = "";
		rightAttr = "";
	}

	void setAttr(string s, bool isLeft){
		if (isLeft) leftAttr = s;
		else rightAttr = s;
	}

	bool validate() {
		//both synonym
		if (isSyn != 0 && isSyn != 1 && isSyn != 2 && isSyn != 3){
			return false;
		}
		if (isSyn == 1){
			string s1 = synonymTable->at(rightSynonym);
			if (s1 == "procedure" && rightAttr == "procName"){
				return true;
			} else if (s1 == "variable" && rightAttr == "varName"){
				return true;
			} else if ((s1 == "stmt" || s1 == "assign" || s1 == "while" || s1 == "if" || s1 == "stmtLst") && rightAttr == "stmt#"){
				return true;
			} else if (s1 == "prog_line" && (rightAttr == "" || rightAttr == "value")){
				return true;
			} else if (s1 == "call" && (rightAttr == "procName" || rightAttr == "stmt#")){
				return true;
			} else if (s1 == "constant" && rightAttr == "value"){
				return true;
			} else {
				return false;
			}
		}
		if (isSyn == 2) {
			string s1 = synonymTable->at(leftSynonym);
			if (s1 == "procedure" && leftAttr == "procName"){
				return true;
			} else if (s1 == "variable" && leftAttr == "varName"){
				return true;
			} else if ((s1 == "stmt" || s1 == "assign" || s1 == "while" || s1 == "if" || s1 == "stmtLst") && leftAttr == "stmt#"){
				return true;
			} else if (s1 == "prog_line" && (leftAttr == "" || leftAttr == "value")){
				return true;
			} else if (s1 == "call" && (leftAttr == "procName" || leftAttr == "stmt#")){
				return true;
			} else if (s1 == "constant" && leftAttr == "value"){
				return true;
			} else {
				return false;
			}
		}
		if (isSyn == 3) {
			string s1 = synonymTable->at(leftSynonym);
			string s2 = synonymTable->at(rightSynonym);
			if (s1 == "procedure" && leftAttr != "procName"){
				return false;
			} else if (s1 == "variable" && leftAttr != "varName"){
				return false;
			} else if ((s1 == "stmt" || s1 == "assign" || s1 == "while" || s1 == "if" || s1 == "stmtLst") && leftAttr != "stmt#"){
				return false;
			} else if (s1 == "prog_line" && !(leftAttr == "" || leftAttr == "value")){
				return false;
			} else if (s1 == "call" && !(leftAttr == "procName" || leftAttr == "stmt#")){
				return false;
			} else if (s1 == "constant" && leftAttr != "value"){
				return false;
			}
			if (s2 == "procedure" && rightAttr != "procName"){
				return false;
			} else if (s2 == "variable" && rightAttr != "varName"){
				return false;
			} else if ((s2 == "stmt" || s2 == "assign" || s2 == "while" || s2 == "if" || s2 == "stmtLst") && rightAttr != "stmt#"){
				return false;
			} else if (s2 == "prog_line" && !(rightAttr == "" || rightAttr == "value")){
				return false;
			} else if (s2 == "call" && !(rightAttr == "procName" || rightAttr == "stmt#")){
				return false;
			} else if (s2 == "constant" && rightAttr != "value"){
				return false;
			}
			if ((leftAttr == "procName" || leftAttr == "varName") && !(rightAttr == "procName" || rightAttr == "varName")) {
				return false;
			} 
			if ((leftAttr == "value" || leftAttr == "stmt#" || s1 == "prog_line") && !(rightAttr == "value" || rightAttr == "stmt#" || s2 == "prog_line")){
				return false;
			}
		}
		return true;
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
				ans = solveOther();
				break;
		}
		return ans;
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
			default: break;
		}
		return ans;
	}

	void setPriority() {
		priority = 1;
	}

	vector<int> getValues(string syn, string attr, int index){
		vector<int> values = vector<int>();
		if (synonymTable->at(syn)=="procedure"){
			if (index < pkb->procTable->getSize() && index >= 0){
				values.push_back(index);
			}
		} else if (synonymTable->at(syn)=="variable" && index >= 0){
			if (index < pkb->varTable->getSize()){
				values.push_back(index);
			}
		} else if (synonymTable->at(syn)=="constant"){
			if (pkb->constantTable->containsConst(index)){
				values.push_back(pkb->constantTable->getConstIndex(index));
			}
		} else if (synonymTable->at(syn)=="call" && attr == "procName"){
			vector<TNode*> callNodes = pkb->statementTable->getNodesMatchingNodeType("CALL_NODE");
			for (size_t i = 0; i < callNodes.size(); i++){
				if (callNodes[i]->getData() == pkb->procTable->getProcName(index)){
					values.push_back(callNodes[i]->getStmtNum());
				}
			}
		} else {
			if (synonymTable->at(syn)=="stmt" || synonymTable->at(syn) == "prog_line"){
				if (0 < index && index <= pkb->statementTable->getSize()){
					values.push_back(index);
				}
			} else if (synonymTable->at(syn)=="assign" || synonymTable->at(syn) == "while" || synonymTable->at(syn)=="if" || synonymTable->at(syn) == "call"){
				if (0 < index && index <= pkb->statementTable->getSize() && pkb->statementTable->getTNode(index)->getNodeType()==TNODE_NAMES[synToNodeType.at(synonymTable->at(syn))]){
					values.push_back(index);
				}
			}
		}
		return values;
	}

	vector<int> getValues(string targetSyn, string sourceSyn, string targetAttr, string sourceAttr, int sourceIndex){
		vector<int> result = vector<int>();
		string sourceSynType = synonymTable->at(sourceSyn);
		string targetSynType = synonymTable->at(targetSyn);
		if ((sourceSynType == "variable" || sourceSynType == "procedure" || (sourceSynType == "call" && sourceAttr == "procName")) && 
			(targetSynType == "variable" || targetSynType == "procedure" || (targetSynType == "call" && targetAttr == "procName"))){
			string sourceString;
			if (sourceSynType == "variable"){
				sourceString = pkb->varTable->getVarName(sourceIndex);
			}
			if (sourceSynType == "procedure"){
				sourceString = pkb->procTable->getProcName(sourceIndex);
			}
			if (sourceSynType == "call"){
				sourceString = pkb->statementTable->getTNode(sourceIndex)->getData();
			}
			if (targetSynType == "variable"){
				if(pkb->varTable->containsVar(sourceString)){
					result.push_back(pkb->varTable->getVarIndex(sourceString));
				}
			}
			if (targetSynType == "procedure"){
				if(pkb->procTable->containsProc(sourceString)){
					result.push_back(pkb->procTable->getProcIndex(sourceString));
				}
			}
			if (targetSynType == "call"){
				vector<TNode*> callNodes = pkb->statementTable->getNodesMatchingNodeType("CALL_NODE");
				for (size_t i = 0; i < callNodes.size(); i++){
					if (callNodes[i]->getData() == sourceString){
						result.push_back(callNodes[i]->getStmtNum());
					}
				}
			}
		} else if ((sourceSynType=="stmt" || sourceSynType=="assign" || sourceSynType=="call" || sourceSynType=="while" || sourceSynType=="if" || sourceSynType=="constant" || sourceSynType=="prog_line") &&
			(targetSynType=="stmt" || targetSynType=="assign" || targetSynType=="call" || targetSynType=="while" || targetSynType=="if" || targetSynType=="constant" || targetSynType=="prog_line")){
			int sourceNum;
			if (sourceSynType == "constant"){
				sourceNum = pkb->constantTable->getConstant(sourceIndex);	
			} else {
				sourceNum = sourceIndex;
			}
			if (targetSynType == "constant"){
				if (pkb->constantTable->containsConst(sourceNum)){
					result.push_back(pkb->constantTable->getConstIndex(sourceNum));
				}
			} else if (targetSynType == "stmt" || targetSynType == "prog_line"){
				if (sourceNum > 0 && sourceNum <= pkb->statementTable->getSize()){
					result.push_back(sourceNum);
				}
			} else {
				if (sourceNum > 0 && sourceNum <= pkb->statementTable->getSize() && pkb->statementTable->getTNode(sourceNum)->getNodeType()==TNODE_NAMES[synToNodeType.at(targetSynType)]){
					result.push_back(sourceNum);
				}
			}
		}
		return result;
	}

	ResultTuple* solveLeftSyn() {
		ResultTuple* tuple = new ResultTuple();
		int index = tuple->addSynonym(leftSynonym);
		tuple->addSynonymToMap(leftSynonym, index);
		vector<int> values = vector<int>();
		if (isSyn == 2) {	// with syn.attr = varnum: Get syn that have attr equals to varnum
			values = getValues(leftSynonym, leftAttr, rightIndex);
		} else {	// Uses(syn, _): Get all users
			// invalid
		}

		for(size_t i = 0; i < values.size(); i++) {
			vector<int> temp = vector<int>();
			temp.push_back(values.at(i));
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
			if (isSyn == 2) {	// with syn.attr = num
				if ((temp.at(index) == rightIndex && synonymTable->at(leftSynonym)!="constant")) {
					result->addResultRow(temp);
				} else if (synonymTable->at(leftSynonym)=="constant" && pkb->constantTable->containsConst(rightIndex) && pkb->constantTable->getConstant(temp.at(index)) == rightIndex){
					result->addResultRow(temp);
				}
			} else {	// with syn.attr = _
				// invalid
			}
		}
		return result;
	}

	ResultTuple* solveRightSyn() {
		ResultTuple* tuple = new ResultTuple();
		int index = tuple->addSynonym(rightSynonym);
		tuple->addSynonymToMap(rightSynonym, index);
		vector<int> values = vector<int>();
		if (isSyn == 1) {	// with syn.attr = varnum: Get syn that have attr equals to varnum
			values = getValues(rightSynonym, rightAttr, leftIndex);
		} else {	// Uses(syn, _): Get all users
			// invalid
		}

		for(size_t i = 0; i < values.size(); i++) {
			vector<int> temp = vector<int>();
			temp.push_back(values.at(i));
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
			if (isSyn == 1) {	// with num = syn.attr
				if ((temp.at(index) == leftIndex && synonymTable->at(rightSynonym)!="constant")) {
					result->addResultRow(temp);
				} else if (synonymTable->at(rightSynonym)=="constant" && pkb->constantTable->containsConst(leftIndex) && pkb->constantTable->getConstant(temp.at(index)) == leftIndex){
					result->addResultRow(temp);
				}
			} else {	// with syn.attr = _
				// invalid
			}
		}
		return result;
	}

	ResultTuple* solveBothSyn(){
		ResultTuple* tuple = new ResultTuple();
		int index = tuple->addSynonym(leftSynonym);
		tuple->addSynonymToMap(leftSynonym, index);
		index = tuple->addSynonym(rightSynonym);
		tuple->addSynonymToMap(rightSynonym, index);

		string leftSynType = synonymTable->at(leftSynonym);
		string rightSynType = synonymTable->at(rightSynonym);

		vector<pair<int, int> > joinValues;
		if ((leftSynType=="procedure" || leftSynType=="variable" || (leftSynType == "call" && leftAttr == "procName") &&
			(rightSynType=="procedure" || rightSynType=="variable" || (rightSynType == "call" && rightAttr == "procName")))){
			joinValues = getJoinStrings(leftSynonym, rightSynonym);
		} else if ((leftSynType=="stmt" || leftSynType=="assign" || leftSynType=="call" || leftSynType=="while" || leftSynType=="if" || leftSynType=="constant" || leftSynType=="prog_line") &&
			(rightSynType=="stmt" || rightSynType=="assign" || rightSynType=="call" || rightSynType=="while" || rightSynType=="if" || rightSynType=="constant" || rightSynType=="prog_line")){
			joinValues = getJoinNums(leftSynonym, rightSynonym);
		} else {
			// invalid
		}

		for (size_t i = 0; i < joinValues.size(); i++){
			vector<int> row;
			row.push_back(joinValues[i].first);
			row.push_back(joinValues[i].second);
			tuple->addResultRow(row);
		}
		return tuple;
	}

	vector<string> getLeftSynStrings(string syn){
		vector<string> results;
		string synType = synonymTable->at(syn);
		if (synType=="procedure"){
			for (int i = 0; i < pkb->procTable->getSize(); i++){
				results.push_back(pkb->procTable->getProcName(i));
			}
		} else if (synType=="variable"){
			results = pkb->varTable->getAllVar();
		} else if (synType=="call"){
			vector<TNode*> callNodes = pkb->statementTable->getNodesMatchingNodeType("CALL_NODE");
			set<string> tempStrings;
			for (size_t i = 0; i < callNodes.size(); i++){
				tempStrings.insert(callNodes[i]->getData());
			}
			for (std::set<string>::iterator it = tempStrings.begin(); it != tempStrings.end(); ++it){
				results.push_back(*it);
			}
		} else {
			// invalid
		}
		return results;
	}

	vector<int> getLeftSynNums(string syn){
		vector<int> results;
		string synType = synonymTable->at(syn);
		if (synType =="constant"){
			results = pkb->constantTable->getAllConstant();
		} else if (synType=="stmt" || synType=="prog_line"){
			results = pkb->statementTable->getAllStmtNum();
		} else if (synType=="assign" || synType=="while" || synType=="if" || synType=="call"){
			results = pkb->statementTable->getStmtNumUsingNodeType(TNODE_NAMES[synToNodeType.at(synonymTable->at(syn))]);
		} else {
			// invalid
		}
		return results;
	}

	vector<pair<int, int> > getJoinStrings(string syn1, string syn2){
		vector<string> leftStrings = getLeftSynStrings(syn1);
		string syn1Type = synonymTable->at(syn1);
		string syn2Type = synonymTable->at(syn2);
		vector<pair<int, int> > results;
		if (syn2Type == "procedure"){
			for (size_t i = 0; i < leftStrings.size(); i++){
				if (pkb->procTable->containsProc(leftStrings[i])){
					if (syn1Type == "procedure"){
						results.push_back(make_pair(pkb->procTable->getProcIndex(leftStrings[i]), pkb->procTable->getProcIndex(leftStrings[i])));
					} else if (syn1Type == "variable"){
						results.push_back(make_pair(pkb->varTable->getVarIndex(leftStrings[i]), pkb->procTable->getProcIndex(leftStrings[i])));
					} else if (syn1Type == "call"){
						vector<TNode*> callNodes = pkb->statementTable->getNodesMatchingNodeType("CALL_NODE");
						for (size_t j = 0; j < callNodes.size(); j++){
							if (leftStrings[i] == callNodes[j]->getData()){
								results.push_back(make_pair(callNodes[j]->getStmtNum(), pkb->procTable->getProcIndex(leftStrings[i])));
							}
						}
					} else {
						// invalid
					}
				}
			}
		} else if (syn2Type == "variable"){
			for (size_t i = 0; i < leftStrings.size(); i++){
				if (pkb->varTable->containsVar(leftStrings[i])){
					if (syn1Type == "procedure"){
						results.push_back(make_pair(pkb->procTable->getProcIndex(leftStrings[i]), pkb->varTable->getVarIndex(leftStrings[i])));
					} else if (syn1Type == "variable"){
						results.push_back(make_pair(pkb->varTable->getVarIndex(leftStrings[i]), pkb->varTable->getVarIndex(leftStrings[i])));
					} else if (syn1Type == "call"){
						vector<TNode*> callNodes = pkb->statementTable->getNodesMatchingNodeType("CALL_NODE");
						for (size_t j = 0; j < callNodes.size(); j++){
							if (leftStrings[i] == callNodes[j]->getData()){
								results.push_back(make_pair(callNodes[j]->getStmtNum(), pkb->varTable->getVarIndex(leftStrings[i])));
							}
						}
					} else {
						// invalid
					}
				}
			}
		} else if (syn2Type == "call"){
			vector<TNode*> callNodes = pkb->statementTable->getNodesMatchingNodeType("CALL_NODE");
			for (size_t i = 0; i < leftStrings.size(); i++){
				for (size_t j = 0; j < callNodes.size(); j++){
					if (callNodes[j]->getData() == leftStrings[i]){
						if (syn1Type == "procedure"){
							results.push_back(make_pair(pkb->procTable->getProcIndex(leftStrings[i]), callNodes[j]->getStmtNum()));
						} else if (syn1Type == "variable"){
							results.push_back(make_pair(pkb->varTable->getVarIndex(leftStrings[i]), callNodes[j]->getStmtNum()));
						} else if (syn1Type == "call"){
							vector<TNode*> copyCallNodes = pkb->statementTable->getNodesMatchingNodeType("CALL_NODE");
							for (size_t k = 0; k < copyCallNodes.size(); k++){
								if (copyCallNodes[k]->getData() == leftStrings[i]){
									results.push_back(make_pair(copyCallNodes[k]->getStmtNum(),callNodes[j]->getStmtNum()));
								}
							}
						}
					}
				}
			}
		} else {
			// invalid
		}
		return results;
	}

	vector<pair<int, int> > getJoinNums(string syn1, string syn2){
		vector<int> leftNums = getLeftSynNums(syn1);
		string syn1Type = synonymTable->at(syn1);
		string syn2Type = synonymTable->at(syn2);
		vector<pair<int, int> > results;

		if (syn2Type =="constant"){
			for (size_t i = 0; i < leftNums.size(); i++){
				if (pkb->constantTable->containsConst(leftNums[i])){
					if (syn1Type == "constant"){
						results.push_back(make_pair(pkb->constantTable->getConstIndex(leftNums[i]), pkb->constantTable->getConstIndex(leftNums[i])));
					} else {
						results.push_back(make_pair(leftNums[i], pkb->constantTable->getConstIndex(leftNums[i])));
					}
				}
			}
		} else if (syn2Type == "stmt" || syn2Type == "prog_line"){
			for (size_t i = 0; i < leftNums.size(); i++){
				if (leftNums[i] > pkb->statementTable->getSize() || leftNums[i] <= 0){
					continue;
				}
				if (syn1Type == "constant"){
					results.push_back(make_pair(pkb->constantTable->getConstIndex(leftNums[i]), leftNums[i]));
				} else {
					results.push_back(make_pair(leftNums[i], leftNums[i]));
				}
			}
		} else if (syn2Type=="assign" || syn2Type=="while" || syn2Type=="if" || syn2Type=="call"){
			for (size_t i = 0; i < leftNums.size(); i++){
				if (leftNums[i] <= 0 || leftNums[i] > pkb->statementTable->getSize() || pkb->statementTable->getTNode(leftNums[i])->getNodeType()!=TNODE_NAMES[synToNodeType.at(syn2Type)]){
					continue;
				}
				if (syn1Type == "constant"){
					results.push_back(make_pair(pkb->constantTable->getConstIndex(leftNums[i]), leftNums[i]));
				} else {
					results.push_back(make_pair(leftNums[i], leftNums[i]));
				}
			}
		} else {
			// invalid
		}
		return results;
	}

	bool isEqualValues(int row, int index1, int index2, ResultTuple* tuple){
		vector<int> rowValues = tuple->getResultRow(row);
		string leftSynType = synonymTable->at(leftSynonym);
		string rightSynType = synonymTable->at(rightSynonym);
		if ((leftSynType == "variable" || leftSynType == "procedure" || (leftSynType == "call" && leftAttr == "procName")) && 
			(rightSynType == "variable" || rightSynType == "procedure" || (rightSynType == "call" && rightAttr == "procName"))) {
			string leftString, rightString;
			if (leftSynType == "variable"){
				leftString = pkb->varTable->getVarName(tuple->getResultAt(row, index1));
			}
			if (leftSynType == "procedure"){
				leftString = pkb->procTable->getProcName(tuple->getResultAt(row, index1));
			}
			if (leftSynType == "call"){
				leftString = pkb->statementTable->getTNode(tuple->getResultAt(row, index1))->getData();
			}
			if (rightSynType == "variable"){
				rightString = pkb->varTable->getVarName(tuple->getResultAt(row, index2));
			}
			if (rightSynType == "procedure"){
				rightString = pkb->procTable->getProcName(tuple->getResultAt(row, index2));
			}
			if (rightSynType == "call"){
				rightString = pkb->statementTable->getTNode(tuple->getResultAt(row, index2))->getData();
			}
			return leftString == rightString;
		} else if ((leftSynType=="stmt" || leftSynType=="assign" || leftSynType=="call" || leftSynType=="while" || leftSynType=="if" || leftSynType=="constant" || leftSynType=="prog_line") &&
			(rightSynType=="stmt" || rightSynType=="assign" || rightSynType=="call" || rightSynType=="while" || rightSynType=="if" || rightSynType=="constant" || rightSynType=="prog_line")){
			int leftNum, rightNum;
			if (leftSynType == "constant"){
				leftNum = pkb->constantTable->getConstant(tuple->getResultAt(row, index1));	
			} else {
				leftNum = tuple->getResultAt(row, index1);
			}
			if (rightSynType == "constant"){
				rightNum = pkb->constantTable->getConstant(tuple->getResultAt(row, index2));
			} else {
				rightNum = tuple->getResultAt(row, index2);
			}
			return leftNum == rightNum;
		}
		return false;
	}

	ResultTuple* solveBothSyn(ResultTuple* tuple) {
		ResultTuple* result = new ResultTuple();
		result->setSynonym(tuple->getSynonyms());
		result->setSynonymMap(tuple->getSynonymMap());

		int lIndex = tuple->getSynonymIndex(leftSynonym);
		int rIndex = tuple->getSynonymIndex(rightSynonym);
		if (lIndex != -1 && rIndex != -1){ //case 1: both are inside
			for (size_t i = 0; i < tuple->getAllResults().size(); i++){
				if (isEqualValues(i, lIndex, rIndex, tuple)){
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
					vector<int> tempValues = getValues(rightSynonym, leftSynonym, rightAttr, leftAttr, leftValue);
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
					vector<int> tempValues = getValues(leftSynonym, rightSynonym, leftAttr, rightAttr, rightValue);
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

	// BOOLEAN Result
	ResultTuple* solveOther() {
		ResultTuple* tuple = new ResultTuple();
		tuple->setBool(true);
		if(isSyn == 0) {	//(digit, digit)
			tuple->setEmpty(leftIndex != rightIndex);
		}
		return tuple;
	}
};