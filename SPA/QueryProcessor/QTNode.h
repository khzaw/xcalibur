// File name: QTNode.h
//header guard at start of header file
#ifndef QTNODE_H
#define QTNODE_H

#include <string>
#include <vector>

using namespace std;

typedef int INDEX;
typedef string STRING;

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
	  void addChild(QTNode*);
	  void setParent(QTNode*);
	  void setKey(STRING);
	  void setData(STRING);
   
	private:
      STRING key, data;
	  int value;
	  QTNode* parent;
	  vector<QTNode*> children;
};
#endif