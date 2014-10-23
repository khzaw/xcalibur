#include <string>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <typeinfo>
#include "AST.h"
using namespace std;

/************** Constructors **********************/
// constructor 
AST::AST(){
}

template<class T>
TNode* AST::createNode(string nodeT, T data, int s,int p){
stringstream ss;
ss << data;
string str = ss.str();
TNode* n = new TNode(nodeT, str,s,p);
return n;
}

void AST::insertRoot(TNode* n){
root.push_back(n);
}

TNode*  AST::getRootNode(){
	return root[0];
}

 void AST::assignChild(TNode *n, TNode* c){
	 n->addChild(c);
}

 void AST::assignParent(TNode *n, TNode *p){
	 n->addParent(p);
}

 string AST::getTNodeType(TNode* n){
	return n->getNodeType();
}

string AST::getTNodeValue(TNode* n){
	return n->getData();
}

int AST::getTNodeStmtNum(TNode* n){
	return n->getStmtNum();
}

int AST::getTNodeProcedure(TNode* n){
	return n->getProcIndex();
}

TNode* AST::getTNodeParent(TNode* n){
	return n->getParent();
}

vector<TNode*> AST::getTNodeChild(TNode* n){
	return n->getChildren();
}

bool isNodeType(TNode* n,string s){
	return (n->getNodeType() == s);
}

template<class T>
bool isNodeValue(TNode* n,T v){
	stringstream ss;
    ss << v;
    string str = ss.str();
	return (n->getData() == str);
}