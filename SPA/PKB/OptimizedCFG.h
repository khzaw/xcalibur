#pragma once

#include <map>
#include <set>
#include <queue>
#include <stack>

#include "AST.h"
#include "..\Frontend\TNode.h"
#include "AggNode.h"

#include "ProcTable.h"
#include "StatementTable.h"
#include "Parent.h"
#include "Follows.h"
#include "Modifies.h"
#include "Uses.h"

using namespace std;

//class ProcTable;

class OptimizedCFG {
  public:
    OptimizedCFG();
    OptimizedCFG(ProcTable*, StatementTable*, Parent*, Follows*, Modifies*, Uses* );
    
    void construct();
    void constructCFGFromProc(TNode*);

	// CFG construction
    void addLink(int, int);
    bool isNext(int, int);
    bool isPrev(int, int);
    bool isNextStar(int, int);
	  bool isPrevStar(int, int);

	  // Next and NextStar
    set<int> getNext(int);
    set<int> getPrev(int);
	  set<int> getNextStar(int);
	  set<int> getPrevStar(int);

    set<int> getAllNext();
    set<int> getAllPrev();

	  map<int, set<int>> getNextListFwd();
	  map<int, set<int>> getNextListBwd();

    // Affect and AffectStar
    bool isAffects(int, int);
    bool isAffectsStar(int, int);

    // AggNodeMap
    AggNode* getAggNodeOfStmt(int);
    std::map<int, AggNode*> populateAggNodeMap(vector<TNode*>, std::map<int, AggNode*>, AggNode*, AggNode*);
    void printAggNodeMap();

    // ds for Next relationships  
    std::map<int, std::set<int> > NextListFwd;
    std::map<int, std::set<int> > NextListBwd;

	private:

    ProcTable* procTable; //declaration
	  StatementTable* statementTable;//declaration
    Parent* parentTable;
    Follows* followsTable;
    Modifies* modifiesTable;
    Uses* usesTable;
    
    
    
    // methods
    void linkStmtList(vector<TNode*>);
    void pushStmtListOntoStack(std::stack<TNode*>*, vector<TNode*>);
    
    // ds for NextStar, Affect, and AffectStar
    std::map<int, AggNode*> stmtToAggNodeMap;
    
};