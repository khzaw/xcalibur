#include <map>
#include <set>
#include <queue>
#include <stack>

#include "PKBController.h"
#include "AST.h"
#include "..\Frontend\TNode.h"
#include "AggNode.h"

using namespace std;

class OptimizedCFG {
  public:
    OptimizedCFG();
    OptimizedCFG(TNode*, PKBController*);

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

	  map<int, set<int>> getNextListFwd;
	  map<int, set<int>> getNextListBwd;

    // Affect and AffectStar
    bool isAffects(int, int);
    bool isAffectsStar(int, int);

    // AggNodeMap
    AggNode* getAggNodeOfStmt(int);
    std::map<int, AggNode*> populateAggNodeMap(vector<TNode*>, std::map<int, AggNode*>, AggNode*, AggNode*);
    void printAggNodeMap();

	private:

    PKBController* pk;
    // ds for Next relationships  
    std::map<int, std::set<int> > NextListFwd;
    std::map<int, std::set<int> > NextListBwd;
    
    // methods
    void linkStmtList(vector<TNode*>);
    void pushStmtListOntoStack(std::stack<TNode*>*, vector<TNode*>);
    
    // ds for NextStar, Affect, and AffectStar
    std::map<int, AggNode*> stmtToAggNodeMap;
    
};