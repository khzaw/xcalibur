// File name: QueryTree.cpp
#include "QTNode.h"
#include "QueryTree.h"

using namespace std;

typedef QueryTree QUERYTREE;
typedef QTNode NODE;

/******* Constructors *******/
QueryTree::QueryTree(NODE newRoot){
	rootNode = newRoot;
}

/******* Accessors *******/
NODE QueryTree::getRootNode(){
	return rootNode;
}
QUERYTREE QueryTree::getSubtreeFromNode(NODE node){
	// TODO: traverse from root node, find a node equal to 'node', create new QueryTree with root = node, return QueryTree
}
   