#include <string>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <set>
#include "Parent.h"
using namespace std;

// constructor 
Parent::Parent(){
set<pair<int,int>> set;
}

void Parent::insertParent(int stmt1,int stmt2){
parentVec.push_back(make_pair(stmt1,stmt2));
}

set<int> Parent::getParent(int){
//#TODO
set<int> parentSet;
return parentSet;
}

set<int> Parent::getChild(int){
//#TODO
set<int> childSet;
return childSet;
}

bool Parent::ifParent(int stmt1,int stmt2){
//#TODO
return NULL;
}

set<int> Parent::getParentStar(int){
//#TODO
set<int> parentStarSet;
return parentStarSet;
}
set<int> Parent::getChildStar(int){
//#TODO
set<int> childStarSet;
return childStarSet;
}

bool Parent::ifParentStar(int stmt1, int stmt2){
//#TODO
return NULL;
}