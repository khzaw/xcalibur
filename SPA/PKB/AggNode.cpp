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
    nextAggNode = next;
}

AggNode* AggNode::getNextAggNode() {
    return nextAggNode;
}

void AggNode::setBranchingAggNode(AggNode* next) {
    if (branchingAggNode1==NULL) branchingAggNode1 = next;
    else {
      if (branchingAggNode2==NULL) branchingAggNode2 = next;
      else std::cout << "Error!" << endl;
    }
}

std::set<AggNode*> AggNode::getBranchingAggNode() {
    std::set<AggNode*> temp_set;
    if (branchingAggNode1!=NULL) temp_set.insert(branchingAggNode1);
    if (branchingAggNode2!=NULL) temp_set.insert(branchingAggNode2);

    return temp_set;
}

void AggNode::setPrevAggNode(AggNode* prev) {
    prevAggNode = prev;
}

AggNode* AggNode::getPrevAggNode() {
    return prevAggNode;
}
