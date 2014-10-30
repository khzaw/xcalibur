#include <string>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <typeinfo>
#include "StatementTable.h"
using namespace std;


StatementTable::StatementTable(){

}
// insert node pointer and node type into the table if it does not exist
void StatementTable::insertStatement(TNode* n){
	string s = n->getNodeType();
	statement.push_back(make_pair(n,s)); 
}

TNode* StatementTable::getTNode(int n){
	pair<TNode*,string> stmt = statement[n];
	return stmt.first;
}
// returns a vector of node pointers of nodes matching specified node type
vector<TNode*> StatementTable::getNodesMatchingNodeType(string nodeType){
	vector<TNode*> nodes;
	for(int i =0;i<statement.size();i++){
	
		if(statement[i].second == nodeType){
			
			nodes.push_back(statement[i].first);
		}
	}
	return nodes;
}

// return a vector of indexes of nodes matching specified node type
vector<int> StatementTable::getStmtNumUsingNodeType(string nodeType){

vector<int> stmtList;
for(int i=0;i<statement.size();i++){
	cout << " size is " << statement.size() << endl;
		cout << "statement[i].second" << statement[i].second << endl;
	if(statement[i].second == nodeType){
		stmtList.push_back(i);
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
	for(int i=0;i<statement.size();i++){
		if(statement[i].second == nodeType){
			return true;
		}
	}
	return false;
}
