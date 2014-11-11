// File name: QTNode.h
//header guard at start of header file
#ifndef QTNODE_H
#define QTNODE_H

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
	  QTNode(STRING);
	  QTNode(STRING, STRING);
	  QTNode(int);
	  QTNode(STRING, QTNode*); 
	  QTNode(int, QTNode*);
	  
	  // Accessor
	  INDEX getNumChild();
      QTNode* getChild(INDEX);
	  STRING getKey();
	  STRING getData();
	  int getValue();
	  
	  // Mutator
	  VOID addChild(QTNode*);
	  VOID setParent(QTNode*);
	  VOID setKey(STRING);
	  VOID setData(STRING);
   
	private:
      STRING key, data;
	  int value;
	  QTNode* parent;
	  vector<QTNode*> children;
};
#endif