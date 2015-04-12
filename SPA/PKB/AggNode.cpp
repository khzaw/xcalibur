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
    if (nextAggNodes.size()<2) {
      nextAggNodes.insert(next);
    }
    else cout << "too many next nodes!!!" << endl;
}

set<AggNode*> AggNode::getNextAggNodes() {
    return nextAggNodes;
}

/*
void AggNode::setBranchingAggNode(AggNode* next) {
    if (branchingAggNodes.size()<2) {
      branchingAggNodes.insert(next);
    }
    else cout << "too many branches!!" << endl;

}

std::set<AggNode*> AggNode::getBranchingAggNode() {
    return branchingAggNodes;
}
*/

void AggNode::setPrevAggNode(AggNode* prev) {
    if (prevAggNodes.size()<2) {
        prevAggNodes.insert(prev);
    }
}

set<AggNode*> AggNode::getPrevAggNodes() {
    return prevAggNodes;
}
