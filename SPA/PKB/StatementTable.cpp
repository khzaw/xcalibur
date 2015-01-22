#include <string>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <numeric>
#include <typeinfo>
#include "StatementTable.h"
#include "AST.h"
using namespace std;


StatementTable::StatementTable(){

}
// insert node pointer and node type into the table if it does not exist
void StatementTable::insertStatement(TNode* n){
	string s = n->getNodeType();
	statement.push_back(make_pair(n,s)); 
}

TNode* StatementTable::getTNode(int n){
	pair<TNode*,string> stmt = statement[n-1];
	return stmt.first;
}
// returns a vector of node pointers of nodes matching specified node type
vector<TNode*> StatementTable::getNodesMatchingNodeType(string nodeType){
	vector<TNode*> nodes;
	for(size_t i =0;i<statement.size();i++){
	
		if(statement[i].second == nodeType){
			
			nodes.push_back(statement[i].first);
		}
	}
	return nodes;
}


vector<int> StatementTable::getAssignmentNodesNum(string lhs, string queryPattern) {			// lhs = _
	vector<int> nodes;
	// strip out quotes
	if(lhs.length() >= 2) lhs = lhs.substr(1, lhs.length()-2);
	for(size_t i = 0; i < statement.size(); ++i) {
		if(statement[i].second == TNODE_NAMES[ASSIGN_NODE]) {
			if(AST::matchPattern(statement[i].first->getData(), queryPattern)) {
				if(lhs == "_") {
					nodes.push_back(statement[i].first->getStmtNum());
				} else {
					if(statement[i].first->getChild(0)->getData() == lhs) {
						nodes.push_back(statement[i].first->getStmtNum());
					}
				}
			}
		}
	}
	return nodes;
}

// return a vector of all statement numbers
vector<int> StatementTable::getAllStmtNum() {
	vector<int> stmts(getSize());
	iota(stmts.begin(), stmts.end(), 1);
	return stmts;
}
// return a vector of indexes of nodes matching specified node type
vector<int> StatementTable::getStmtNumUsingNodeType(string nodeType){

vector<int> stmtList;
for(size_t i=0;i<statement.size();i++){
	if(statement[i].second == nodeType){
		stmtList.push_back(i+1);
	}
}
return stmtList;
}



// returns the number of statements in program
int StatementTable::getSize(){ 	
	return statement.size();
}
	
// checks if program contains statement of a particular type
bool StatementTable::containsStatement(string nodeType){
	for(size_t i=0;i<statement.size();i++){
		if(statement[i].second == nodeType){
			return true;
		}
	}
	return false;
}

bool StatementTable::containsNodeOfStmtAndNodeType(string nodeType, int stmt){
	for(size_t i=0;i<statement.size();i++){
		if(statement[i].second == nodeType && ((i+1)==stmt)){
			return true;
		}
	}
	return false;

}
