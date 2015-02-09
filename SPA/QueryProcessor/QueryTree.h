// File name: QueryTree.h
//header guard at start of header file
#ifndef QUERYTREE_H
#define QUERYTREE_H
#include "SPA/QueryProcessor/QTNode.h"

using namespace std;

class QueryTree;

typedef QueryTree QUERYTREE;
typedef QTNode NODE;

class QueryTree {
   public:
      // Constructor
	  QueryTree();
	  QueryTree(NODE*); 
	  
	  // Accessor
      NODE* getRootNode();
	  QUERYTREE* getSubtreeFromNode(NODE*);

	  void printTree();
   
private:
      NODE* rootNode;

};
#endif