// File name: QueryTree.cpp
#include <iostream>
#include "QTNode.h"
#include "QueryTree.h"

using namespace std;

typedef QueryTree QUERYTREE;
typedef QTNode NODE;

/******* Constructors *******/
QueryTree::QueryTree(){
	NODE* queryTreeRoot = new NODE("PQL Query");	
	rootNode = queryTreeRoot;
	NODE* resultRoot = new NODE("tuples");
	resultRoot->setParent(rootNode);
	rootNode->addChild(resultRoot);
	NODE* suchthatRoot = new NODE("such that");
	suchthatRoot->setParent(rootNode);
	rootNode->addChild(suchthatRoot);
	NODE* withRoot = new NODE("with");
	withRoot->setParent(rootNode);
	rootNode->addChild(withRoot);
	NODE* patternRoot = new NODE("pattern");
	patternRoot->setParent(rootNode);
	rootNode->addChild(patternRoot);
}
QueryTree::QueryTree(NODE* newRoot){
	rootNode = newRoot;
}

/******* Accessors *******/
NODE* QueryTree::getRootNode(){
	return rootNode;
}
QUERYTREE* QueryTree::getSubtreeFromNode(NODE* node){
	return new QueryTree(node);
}

void QueryTree::printTree() {
	cout << "Tuples: ";
	for(int i = 0; i < rootNode->getChild(0)->getNumChild(); i++) {	
		if (rootNode->getChild(0)->getChild(i)->getKey().empty()) {
			cout << rootNode->getChild(0)->getChild(i)->getValue() << " ";
		} else {
			cout << rootNode->getChild(0)->getChild(i)->getKey() << " ";
		}
	}
	cout << endl;

	cout << "Such that: ";
	for(int i = 0; i < rootNode->getChild(1)->getNumChild(); i++) {	
		cout << rootNode->getChild(1)->getChild(i)->getKey();
		string c1 = rootNode->getChild(1)->getChild(i)->getChild(0)->getKey();
		string c2 = rootNode->getChild(1)->getChild(i)->getChild(1)->getKey();
		if (c1.empty()) {
			cout << "(" << rootNode->getChild(0)->getChild(i)->getChild(0)->getValue();
		} else {
			cout << "(" << c1 ;
		}
		if (c2.empty()) {
			cout << "," << rootNode->getChild(0)->getChild(i)->getChild(1)->getValue();
		} else {
			cout << "," << c2 ;
		}
		cout << ") ";
	}
	cout << endl;

	cout << "Pattern: ";
	for(int i = 0; i < rootNode->getChild(2)->getNumChild(); i++) {	
		if (rootNode->getChild(2)->getChild(i)->getNumChild() == 2) {
			cout << rootNode->getChild(2)->getChild(i)->getKey() << "(";
			cout << rootNode->getChild(2)->getChild(i)->getChild(0)->getKey() << "|";
			cout << rootNode->getChild(2)->getChild(i)->getChild(1)->getKey() << ") ";
		} else {
			cout << rootNode->getChild(2)->getChild(i)->getKey() << "(";
			cout << rootNode->getChild(2)->getChild(i)->getChild(0)->getKey() << "|";
			cout << rootNode->getChild(2)->getChild(i)->getChild(1)->getKey() << ",";
			cout << rootNode->getChild(2)->getChild(i)->getChild(2)->getKey() << ") ";
		}
	}
	cout << endl;

}
   