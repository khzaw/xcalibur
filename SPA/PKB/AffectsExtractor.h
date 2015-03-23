#pragma once


#include "Uses.h"
#include "NextExtractor.h"
#include "Modifies.h"
#include "ModifiesExtractor.h"
#include "VarTable.h"
#include "StatementTable.h"
#include <queue>


class AffectsExtractor {

public:
	AffectsExtractor();
    AffectsExtractor(Modifies* modifies,Uses* uses,NextExtractor* nextExtractor ,VarTable* varTable, StatementTable* stmtTable ,Calls* callTable );
    ~AffectsExtractor(void);

//evaluator should only touch these methods//
	bool isAffects(int,int);
	set<int> getAffects(int progLine1); 
	set<int> getAffectsBy(int progLine1); 
	bool isAffectsStar(int,int);
    set<int> getAffectsStar(int progLine1); 
	set<int> getAffectsStarBy(int progLine2); 
//****************************************//
	int getVarModifiedByStmt(int progLineNum);
	set<int> getVarUsesByStmt(int progLineNum);
	
	bool isAffectProcess(int progLine, int modifiedVar, std::map<int, bool> checker, std::queue<shared_ptr<GNode>> newQueue);
	bool isModified(int progLine, queue<shared_ptr<GNode>> queue, std::shared_ptr<GNode> lastIfNode, int modifiedVar, std::map<int, bool> checker); 
	bool isNotWithinIf(set<int> result, int progLine2, int ifStmtNum);
	bool isNotWithinWhileLoop(shared_ptr<GNode> progLineNode, int progLine2);
	set<int> AffectsExtractor::getPrevResultSet(vector<shared_ptr<GNode>> prevArray, set<int> result);

	set<int> getAffectProcess(int modifiedVar, std::shared_ptr<GNode> lastIfNode, std::queue<shared_ptr<GNode>> queue);
	std::queue<shared_ptr<GNode>> addToQueue(shared_ptr<GNode> node, std::map<int, bool> checker, std::queue<shared_ptr<GNode>> queue);

	set<int> getAffectByProcess(int usesVar, int ifStmt, std::queue<shared_ptr<GNode>> queue, int resultSize);
	std::queue<shared_ptr<GNode>> addToByQueue(shared_ptr<GNode> node, std::map<int, bool> checker,std::queue<shared_ptr<GNode>> queue);
	
	void addToIsAffectStarSet(set<int> resultSet);
	void addToAffectStarSet(set<int> resultSet);
	void addToAffectStarBySet(set<int> resultSet);


private:

	Calls* calls;
	Modifies* modifies;
	Uses* uses;
	VarTable* varTable;
	StatementTable* stmtTable;
	NextExtractor* nextExtractor;
	std::map<int,bool> checkerAffectsBy;
	std::map<int,bool> checkerAffects;
	std::stack<int> callStack;
	set<int> getAffectResultSet;
	set<int> getAffectByResultSet;
	set<int> getAffectStarResultSet;
	set<int> getAffectStarByResultSet;
	set<int> isAffectStarResultSet;
	
};
