#include <map>
#include <set>

using namespace std;

class AggNode {
public:
    AggNode();

    void addProgLine(int);
    set<int> getProgLines();

    void setType(string);
    string getType();

    void addVarModifiedByThisNode(int);
    set<int> getVarModifiedByThisNode();

    void addVarUsedByThisNode(int);
    set<int> getVarUsedByThisNode();

    void setNextAggNode(AggNode*);
    AggNode* getNextAggNode();
    void setBranchingAggNode(AggNode*);
    std::set<AggNode*> getBranchingAggNode();
    
    void setPrevAggNode(AggNode*);
    AggNode* getPrevAggNode();
    
private:
    set<int> progLines;
    string type;
    
    set<int> varModified;
    set<int> varUsed;

    AggNode* nextAggNode;
    AggNode* prevAggNode;

    AggNode* branchingAggNode1;
    AggNode* branchingAggNode2;
};