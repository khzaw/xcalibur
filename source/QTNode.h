// File name: QTNode.h
#include <string>
#include <vector>

using namespace std;

class QTNode;

typedef int INDEX;
typedef string STRING;
typedef vector<QTNode> LIST;
typedef QTNode NODE;
typedef void VOID;

class QTNode {
   public:
      // Constructor
	  QTNode(STRING, NODE); 
	  
	  // Accessor
	  INDEX getNumChild();
      NODE getChild(INDEX);
	  STRING getKey();
	  
	  // Mutator
	  VOID setChild(NODE);
	  VOID setParent(NODE);
	  VOID setKey(STRING);
   
private:
      STRING key;
	  NODE* parent;
	  LIST children;
};