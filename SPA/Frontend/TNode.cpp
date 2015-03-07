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
	rightSibling = NULL;
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
	parent=p;
}


void TNode::addChild(TNode *c) {
	c->addParent(this);
    children.push_back(c);
}

vector<TNode*> TNode::getChildren() {
    return children;
}

TNode* TNode::getChild(int indx) {
    return children[indx];
}

TNode* TNode::getParent(){
    return parent;
}

int TNode::getNumChildren() {
    return children.size();
}

void TNode::addRightSibling(TNode * sibling){
	rightSibling = sibling;
}

TNode* TNode::getRightSibling(){
	return rightSibling;
}
