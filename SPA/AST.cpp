#include <string>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <typeinfo>
#include "AST.h"
using namespace std;


AST::AST(){
}

TNode AST::createNode(string nodeT, string data, int s,int p){
TNode n(nodeT,data,s,p);
return n;
}

void AST::insertRoot(TNode *n){
root.push_back(n);
}

TNode*  AST::getRootNode(){
	return root[0];
}

 TNode* AST::assignChild(TNode *n, TNode *c){
	 n->addChild(c);
	 return n;
}

 TNode* AST::assignParent(TNode *n, TNode *p){
	 n->addParent(p);
	 	 return n;
}

 string AST::getTNodeType(TNode *n){
	return n->getNodeType();
}

string AST::getTNodeValue(TNode *n){
	return n->getData();
}

int AST::getTNodeStmtNum(TNode *n){
	return n->getStmtNum();
}

int AST::getTNodeProcedure(TNode *n){
	return n->getProcIndex();
}

TNode* AST::getTNodeParent(TNode *n){
	return n->getParent();
}

TNode* AST::getTNodeChild(TNode *n, int index){
	return n->getChild(index);
}

vector<TNode*> AST::getTNodeChildren(TNode *n){
	return n->getChildren();
}

bool AST::isNodeType(TNode *n,string s){
	return (n->getNodeType() == s);
}

bool AST::isNodeValue(TNode *n,string v){
	return (n->getData() == v);
}