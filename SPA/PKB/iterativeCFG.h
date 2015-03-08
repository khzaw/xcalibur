#include <map>
#include <set>
#include <queue>
#include <stack>

#include "AST.h"
#include "..\Frontend\TNode.h"

using namespace std;

class CFG {
  public:
    CFG();
    CFG(TNode* root);

    void addLink(int, int);
    bool isNext(int, int);
    bool isPrev(int, int);
    bool isNextT(int, int);

    set<int> getNextOf(int);
    set<int> getPrevOf(int);

  // private:
    std::map<int, std::set<int> > AdjListFwd;
    std::map<int, std::set<int> > AdjListBwd;
    int numLines;
    void linkStmtList(vector<TNode*>);
    void pushStmtListOntoStack(std::stack<TNode*>*, vector<TNode*>);

};