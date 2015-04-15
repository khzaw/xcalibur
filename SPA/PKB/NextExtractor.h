#pragma once


#include <map>
#include <stack>
#include <set>
#include "CFG.h"
#include "Calls.h"
#include "StatementTable.h"

class ProcTable;

class NextExtractor {
public:
	NextExtractor();
	NextExtractor(ProcTable* procTable,StatementTable* sTable );
	
	 //called by PQL
	bool isNextStar(int progline1, int progline2);
	bool isPrevStar(int progline1, int progline2);
	bool isNext(int progline1, int progline2);
	bool isPrev(int progline1, int progline2);
	set<int> getNext(int progLine);	
	set<int> getPrev(int progLine);
	set<int> getAllNext();
	set<int> getAllPrev();
	set<int> getNextStar(int progLine);
	set<int> getPrevStar(int progLine);
	
  //called by front end controller
	void construct();
	map<int,std::shared_ptr<GNode>> getNodeMap();
	map<int,std::shared_ptr<GNode>> getLastIfNode();
	map<std::shared_ptr<GNode>,int> getFirstIfNode();
	shared_ptr<GNode> getNodeFromMap(int progLine);
	void storeAllNextPrev();
	//Helper method
	vector<std::shared_ptr<CFG>> constructCFG();
	shared_ptr<GNode> converseAST(std::shared_ptr<CFG> cfg, TNode* cur, std::shared_ptr<GNode> parent, shared_ptr<stack<std::shared_ptr<GNode>>> level);
	shared_ptr<GNode> setlink(std::shared_ptr<CFG> cfg, TNode* cur, std::shared_ptr<GNode> parent, shared_ptr<stack<std::shared_ptr<GNode>>> level);
	TNode* getLastRightSibling(TNode* current);
	bool isLastStmt(TNode* cur);
	set<int> getPrevResultSet(vector<shared_ptr<GNode>> prevArray , set<int>); 
	set<int> getNextResultSet(vector<shared_ptr<GNode>> nextArray , set<int>);
	/*
	set<int> findProgLineNum(map<int , shared_ptr<GNode>>, int progLine); // map<stmt,Gnode>, progLine

	
	int getProcIndexOfLastStmt(int stmtNum);
	int getLastStmtOfProc(int procIndex);
	*/

private:

	vector<std::shared_ptr<CFG>> CFGTable;

	ProcTable* procTable; //declaration
	Calls* calls;//declaration
	StatementTable* statementTable;//declaration
  Parent* parentTable;
  Follows* followsTable;
  Modifies* modifiesTable;
  Uses* usesTable;


	map<int,std::shared_ptr<GNode>> nodeMap; // store normal stmt and GNodes
	map<int,std::shared_ptr<GNode>> lastIfNode; //for affects "to check last node of if comparison"
	map<std::shared_ptr<GNode>, int> firstIfNode;//for affects "to check last node of if comparison"
	set<int> allNextStmt;
	set<int> allPrevStmt;
	stack<pair<TNode*,TNode*>> lastIfWhileStmtStack;

};
