// File name: QTNode.cpp
#include <string>
#include <vector>
#include "QTNode.h"

using namespace std;

typedef int INDEX;
typedef string STRING;
typedef vector<QTNode> LIST;
typedef QTNode NODE;
typedef void VOID;

/******* Constructors *******/
QTNode::QTNode(STRING newKey, NODE newParent){
	key = newKey;
	parent = &newParent;
}

/******* Accessors *******/
INDEX QTNode::getNumChild(){
	return children.size();
}

NODE QTNode::getChild(INDEX index){
	return children.at(index);
}

STRING QTNode::getKey(){
	return key;
}

/******* Mutators *******/
VOID QTNode::setChild(NODE newChild){
	children.push_back(newChild);
}

VOID QTNode::setParent(NODE newParent){
	parent = &newParent;
}

VOID QTNode::setKey(STRING newKey){
	key = newKey;
}