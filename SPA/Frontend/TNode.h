#pragma once
#include <cstddef>
#include <vector>

using namespace std;

enum TNODE_TYPE {
	PROC_NODE,
	VAR_NODE,
	STMTLST_NODE,
	PLUS_NODE,
	WHILE_NODE,
	ASSIGN_NODE,
	CONSTANT_NODE,
	IF_NODE,
	THEN_NODE,
	ELSE_NODE,
	CALL_NODE
};

static string TNODE_NAMES[] = {
	"PROC_NODE",
	"VAR_NODE",
	"STMTLST_NODE",
	"PLUS_NODE",
	"WHILE_NODE",
	"ASSIGN_NODE",
	"CONSTANT_NODE",
	"IF_NODE",
	"THEN_NODE",
	"ELSE_NODE",
	"CALL_NODE"
};

class TNode {

private:

    string data;
	string nodeType;
	int procIndex;
	int stmtNum;
	TNode* parent;
    vector<TNode*> children;
	

public:
	//Constructor
	TNode();
    TNode(string, string,int,int);
	//Accessor for node
	string getData() ;
	int getStmtNum() ;
    int getProcIndex() ;
	string getNodeType() ;
	TNode* getChild(int) ;
    TNode* getParent() ;
	vector<TNode *> getChildren() ;
	int getNumChildren() ;
	//Mutator for node
    void setData(string data);
	void addParent(TNode *p);
    void addChild(TNode *c);
};