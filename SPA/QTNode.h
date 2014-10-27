// File name: QTNode.h
//header guard at start of header file
#ifndef QTQTNode_H
#define QTQTNode_H

#include <string>
#include <vector>

using namespace std;

typedef int INDEX;
typedef string STRING;
typedef void VOID;

class QTNode {
	public:
      // Constructor
	  QTNode();
	  QTNode(STRING, QTNode); 
	  
	  // Accessor
	  INDEX getNumChild();
      QTNode getChild(INDEX);
	  STRING getKey();
	  
	  // Mutator
	  VOID setChild(QTNode);
	  VOID setParent(QTNode);
	  VOID setKey(STRING);
   
	private:
      STRING key;
	  QTNode* parent;
	  vector<QTNode> children;
};
#endif