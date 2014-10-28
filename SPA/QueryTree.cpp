// File name: QueryTree.cpp
#include "QTNode.h"
#include "QueryTree.h"

using namespace std;

typedef QueryTree QUERYTREE;
typedef QTNode NODE;

/******* Constructors *******/
QueryTree::QueryTree(){
	NODE* queryTreeRoot = new NODE("PQL Query");
	rootNode = *queryTreeRoot;
	NODE* resultRoot = new NODE("tuples", *queryTreeRoot);
	rootNode.addChild(*resultRoot);
	NODE* suchthatRoot = new NODE("such that", *queryTreeRoot);
	rootNode.addChild(*suchthatRoot);
	NODE* withRoot = new NODE("with", *queryTreeRoot);
	rootNode.addChild(*withRoot);
	NODE* patternRoot = new NODE("pattern", *queryTreeRoot);
	rootNode.addChild(*patternRoot);
}
QueryTree::QueryTree(NODE newRoot){
	rootNode = newRoot;
}

/******* Accessors *******/
NODE QueryTree::getRootNode(){
	return rootNode;
}
QUERYTREE QueryTree::getSubtreeFromNode(NODE node){
	return QueryTree(node);
}
   