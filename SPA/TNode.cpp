#include <cstddef>
#include <vector>
#include <string>
#include <typeinfo>
#include <sstream>
#include "TNode.h"


using namespace std;

TNode::TNode(){
}


TNode::TNode(string nodeT, string value, int s,int p) {
    data =  value;
	nodeType = nodeT;
	stmtNum = s;
	procIndex= p;
}

string TNode::getData()  {
    return data;
}


int TNode::getStmtNum()  {
    return stmtNum;
}


int TNode::getProcIndex()  {
    return procIndex;
}


string TNode::getNodeType()  {
    return nodeType;
}


void TNode::setData(string value) {
    data = value;
}


void  TNode::addParent(TNode *p) {
	parent.push_back(p);
}


void TNode::addChild(TNode *c) {
    children.push_back(c);
}

vector<TNode*> TNode::getChildren() {
    return children;
}

TNode* TNode::getChild(int indx) {
    return children[indx];
}

TNode* TNode::getParent(){
    return parent[0];
}

int TNode::getNumChildren() {
    return children.size();
}