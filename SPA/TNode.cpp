#include <cstddef>
#include <vector>
#include <string>
#include <typeinfo>
#include <sstream>
#include "TNode.h"


using namespace std;

TNode::TNode(){
}


TNode::TNode(string nodeT, string data, int s,int p) {
    this->data =  data;
	this->nodeType = nodeT;
	this->stmtNum = s;
	this->procIndex= p;
}

string TNode::getData()  {
    return this->data;
}


int TNode::getStmtNum()  {
    return this->stmtNum;
}


int TNode::getProcIndex()  {
    return this->procIndex;
}


string TNode::getNodeType()  {
    return this->nodeType;
}


void TNode::setData(string data) {
    this->data = data;
}


void TNode::addParent(TNode *p) {
    parent = p;
}


void TNode::addChild(TNode *c) {
    children.push_back(c);
}


/**
 Need to refine and handle null nodes
template<class T>
TNode<T>* TNode<T>::findChild(const T& data) const {
    for(int i=0; i<children.size(); i++)
        if(children[i]->getData() == data)
            return children[i];
    return ;
}
*/

vector<TNode*> TNode::getChildren() const {
    return children;
}

TNode* TNode::getChild(int indx) const {
    return children[indx];
}

TNode* TNode::getParent() const {
    return parent;
}

int TNode::getNumChildren() const {
    return children.size();
}