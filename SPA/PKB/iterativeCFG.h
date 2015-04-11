#include <map>
#include <set>
#include <queue>
#include <stack>

#include "AST.h"
#include "..\Frontend\TNode.h"

using namespace std;

class iterativeCFG {
  public:
    iterativeCFG();
    iterativeCFG(TNode* root);

    void addLink(int, int);
    bool isNext(int, int);
    bool isPrev(int, int);
    bool isNextStar(int, int);
	bool isPrevStar(int, int);

    set<int> getNext(int);
    set<int> getPrev(int);
	set<int> getNextStar(int);
	set<int> getPrevStar(int);

	map<int, set<int>> getFwdMap;
	map<int, set<int>> getBwdMap;

	
    std::map<int, std::set<int> > AdjListFwd;
    std::map<int, std::set<int> > AdjListBwd;

  private:
    int numLines;
    void linkStmtList(vector<TNode*>);
    void pushStmtListOntoStack(std::stack<TNode*>*, vector<TNode*>);

};