#include <string>
#include <set>
#include "TNode.h"
using namespace std;

//public functions
class AST{
public:
	//Constructor
    AST();
	//Accessor for AST
	string getTNodeType(TNode* n);
    string getTNodeValue(TNode* n);
    int getTNodeStmtNum(TNode* n);
    int getTNodeProcedure(TNode* n);
	TNode* getTNodeParent(TNode* n);
     vector<TNode*> getTNodeChild(TNode* n);
	 //Mutator for AST 
	 template<class T>
	 TNode* createNode(string, T data, int,int);
	 void assignChild(TNode* n, TNode* c);
     void assignParent(TNode* n, TNode* p); 
     bool isNodeType(TNode n,string); 
	 template<class T>
     bool isNodeValue(TNode n,T v); 
     void insertRoot(TNode* n);
     TNode* getRootNode();

private:
vector<TNode *> root;
};