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

    void addVarModifiedByThisNode(set<int>);
    set<int> getVarModifiedByThisNode();

    void addVarUsedByThisNode(set<int>);
    set<int> getVarUsedByThisNode();

    void setNextAggNode(AggNode*);
    set<AggNode*> getNextAggNodes();

    //void setBranchingAggNode(AggNode*);
    //std::set<AggNode*> getBranchingAggNode();
    
    void setPrevAggNode(AggNode*);
    set<AggNode*> getPrevAggNodes();
    
private:
    set<int> progLines;
    string type;
    
    set<int> varModified;
    set<int> varUsed;

    set<AggNode*> nextAggNodes;

    //set<AggNode*> branchingAggNodes;

    set<AggNode*> prevAggNodes;
};