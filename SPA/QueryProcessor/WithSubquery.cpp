#pragma once
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include "Subquery.h"

using namespace std;

class WithSubquery : public Subquery{
public:
	WithSubquery(map<string, string>* m, PKBController* p) : Subquery(m, p){
	
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
				break;
		}
		return ans;
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

	vector<int> getValues(string syn, int index){
		vector<int> values = vector<int>();
		if (synonymTable->at(syn)=="procedure"){
			if (index < pkb->procTable.getSize()){
				values.push_back(index);
			}
		} else if (synonymTable->at(syn)=="variable"){
			if (index < pkb->varTable.getSize()){
				values.push_back(index);
			}
		} else if (synonymTable->at(syn)=="constant"){
			if (pkb->constantTable.containsConst(index)){
				values.push_back(index);
			}
		} else {
			if (synonymTable->at(syn)=="stmt" || synonymTable->at(syn) == "prog_line"){
				if (0 < index && index <= pkb->statementTable.getSize()){
					values.push_back(index);
				}
			} else if (synonymTable->at(syn)=="assign" || synonymTable->at(syn) == "while" || synonymTable->at(syn)=="if" || synonymTable->at(syn) == "call"){
				if (0 < index && index <= pkb->statementTable.getSize() && pkb->statementTable.getTNode(index)->getNodeType()==TNODE_NAMES[synToNodeType.at(synonymTable->at(syn))]){
					values.push_back(index);
				}
			}
		}
		return values;
	}

	ResultTuple* solveLeftSyn() {
		ResultTuple* tuple = new ResultTuple();
		int index = tuple->addSynonym(leftSynonym);
		tuple->addSynonymToMap(leftSynonym, index);
		vector<int> values = vector<int>();
		if (isSyn == 2) {	// with syn.attr = varnum: Get syn that have attr equals to varnum
			values = getValues(leftSynonym, rightIndex);
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
			if (isSyn == 1) {	// with syn.attr = num
				if (temp.at(index) == rightIndex) {
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
		if (isSyn == 2) {	// with syn.attr = varnum: Get syn that have attr equals to varnum
			values = getValues(rightSynonym, leftIndex);
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
				if (temp.at(index) == leftIndex) {
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
		if ((leftSynType=="procedure" || leftSynType=="variable") &&
			(rightSynType=="procedure" || rightSynType=="variable")){
			joinValues = getJoinStrings(leftSynonym, rightSynonym);
		} else if ((leftSynType=="stmt" || leftSynType=="assign" || leftSynType=="call" || leftSynType=="while" || leftSynType=="if" || leftSynType=="constant" || leftSynType=="progline") &&
			(rightSynType=="stmt" || rightSynType=="assign" || rightSynType=="call" || rightSynType=="while" || rightSynType=="if" || rightSynType=="constant" || rightSynType=="progline")){
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
			for (int i = 0; i < pkb->procTable.getSize(); i++){
				results.push_back(pkb->procTable.getProcName(i));
			}
		} else if (synType=="variable"){
			results = pkb->varTable.getAllVar();
		} else {
			// invalid
		}
		return results;
	}

	vector<int> getLeftSynNums(string syn){
		vector<int> results;
		string synType = synonymTable->at(syn);
		if (synType =="constant"){
			results = pkb->constantTable.getAllConstant();
		} else if (synType=="stmt" || synType=="prog_line"){
			results = pkb->statementTable.getAllStmtNum();
		} else if (synType=="assign" || synType=="while" || synType=="if" || synType=="call"){
			results = pkb->statementTable.getStmtNumUsingNodeType(TNODE_NAMES[synToNodeType.at(synonymTable->at(syn))]);
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
				if (pkb->procTable.containsProc(leftStrings[i])){
					if (syn1Type == "procedure"){
						results.push_back(make_pair(pkb->procTable.getProcIndex(leftStrings[i]), pkb->procTable.getProcIndex(leftStrings[i])));
					} else if (syn1Type == "variable"){
						results.push_back(make_pair(pkb->varTable.getVarIndex(leftStrings[i]), pkb->procTable.getProcIndex(leftStrings[i])));
					} else {
						// invalid
					}
				}
			}
		} else if (syn2Type == "variable"){
			for (size_t i = 0; i < leftStrings.size(); i++){
				if (pkb->varTable.containsVar(leftStrings[i])){
					if (syn1Type == "procedure"){
						results.push_back(make_pair(pkb->procTable.getProcIndex(leftStrings[i]), pkb->varTable.getVarIndex(leftStrings[i])));
					} else if (syn1Type == "variable"){
						results.push_back(make_pair(pkb->varTable.getVarIndex(leftStrings[i]), pkb->varTable.getVarIndex(leftStrings[i])));
					} else {
						// invalid
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
				if (pkb->constantTable.containsConst(leftNums[i])){
					if (syn1Type == "constant"){
						results.push_back(make_pair(pkb->constantTable.getConstIndex(leftNums[i]), pkb->constantTable.getConstIndex(leftNums[i])));
					} else {
						results.push_back(make_pair(leftNums[i], pkb->constantTable.getConstIndex(leftNums[i])));
					}
				}
			}
		} else if (syn2Type == "stmt" || syn2Type == "prog_line"){
			for (size_t i = 0; i < leftNums.size(); i++){
				if (leftNums[i] > pkb->statementTable.getSize()){
					continue;
				}
				if (syn1Type == "constant"){
					results.push_back(make_pair(pkb->constantTable.getConstIndex(leftNums[i]), leftNums[i]));
				} else {
					results.push_back(make_pair(leftNums[i], leftNums[i]));
				}
			}
		} else if (syn2Type=="assign" || syn2Type=="while" || syn2Type=="if" || syn2Type=="call"){
			for (size_t i = 0; i < leftNums.size(); i++){
				if (leftNums[i] > pkb->statementTable.getSize() || pkb->statementTable.getTNode(leftNums[i])->getNodeType()!=TNODE_NAMES[synToNodeType.at(syn2Type)]){
					continue;
				}
				if (syn1Type == "constant"){
					results.push_back(make_pair(pkb->constantTable.getConstIndex(leftNums[i]), leftNums[i]));
				} else {
					results.push_back(make_pair(leftNums[i], leftNums[i]));
				}
			}
		} else {
			// invalid
		}
		return results;
	}

	ResultTuple* solveBothSyn(ResultTuple* tuple) {
		ResultTuple* result = new ResultTuple();
		result->setSynonym(tuple->getSynonyms());
		result->setSynonymMap(tuple->getSynonymMap());

		int lIndex = tuple->getSynonymIndex(leftSynonym);
		int rIndex = tuple->getSynonymIndex(rightSynonym);
		if (lIndex != -1 && rIndex != -1){ //case 1: both are inside
			for (size_t i = 0; i < tuple->getAllResults().size(); i++){
				if (lIndex == rIndex){
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
					vector<int> tempValues = getValues(rightSynonym, leftValue);
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
					vector<int> tempValues = getValues(leftSynonym, rightValue);
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