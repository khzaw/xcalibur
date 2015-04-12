#include <map>
#include <set>
#include <iostream>

#include "AggNode.h"

AggNode::AggNode() {
}

void AggNode::addProgLine(int line) {
    progLines.insert(line);
}

set<int> AggNode::getProgLines() {
    return progLines;
}

void AggNode::setType(string type) {
  this->type = type;
}

string AggNode::getType() {
  return type;
}

void AggNode::addVarModifiedByThisNode(set<int> vars) {
    varModified.insert(vars.begin(), vars.end());
}

set<int> AggNode::getVarModifiedByThisNode() {
    return varModified;
}

void AggNode::addVarUsedByThisNode(set<int> vars) {
  
  varUsed.insert(vars.begin(), vars.end());

}

set<int> AggNode::getVarUsedByThisNode() {
    return varUsed;
}

void AggNode::setNextAggNode(AggNode* next) {
    nextAggNode1 = next;
}

AggNode* AggNode::getNextAggNode() {
    return nextAggNode1;
}

void AggNode::setBranchingAggNode(AggNode* next) {
    if (nextAggNode1==NULL) nextAggNode1 = next;
    else {
      if (nextAggNode2==NULL) nextAggNode2 = next;
      else std::cout << "Error!" << endl;
    }
}

std::set<AggNode*> AggNode::getBranchingAggNode() {
    std::set<AggNode*> temp_set;
    if (nextAggNode1!=NULL) temp_set.insert(nextAggNode1);
    if (nextAggNode2!=NULL) temp_set.insert(nextAggNode2);

    return temp_set;
}

void AggNode::setPrevAggNode(AggNode* prev) {
    prevAggNode = prev;
}

AggNode* AggNode::getPrevAggNode() {
    return prevAggNode;
}
