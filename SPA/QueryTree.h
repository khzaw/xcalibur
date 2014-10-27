// File name: QueryTree.h
#include "QTNode.h"

using namespace std;

class QueryTree;

typedef QueryTree QUERYTREE;
typedef QTNode NODE;

class QueryTree {
   public:
      // Constructor
	  QueryTree();
	  QueryTree(NODE); 
	  
	  // Accessor
      NODE getRootNode();
	  QUERYTREE getSubtreeFromNode(NODE);
   
private:
      NODE rootNode;
};