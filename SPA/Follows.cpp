#include <string>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <utility>
#include "Follows.h"
using namespace std;

// constructor 
Follows::Follows(){
}

void Follows::insertFollows(int stmt1,int stmt2){
followVec.push_back(make_pair(stmt1,stmt2));
}
set<int> Follows::getFollowee(int){
//#TODO
set<int> followeeSet;
return followeeSet;
}
set<int> Follows::getFollower(int){
//#TODO
set<int> followerSet;
return followerSet;
}

bool Follows::ifFollows(int stmt1,int stmt2){
//#TODO
return NULL;
}

set<int> Follows::getFolloweeStar(int){
//#TODO
set<int> followeeStarSet;
return followeeStarSet;
}
set<int> Follows::getFollowerStar(int){
//#TODO
set<int> followerStarSet;
return followerStarSet;
}

bool Follows::ifFollowsStar(int stmt1, int stmt2){
//#TODO
 return NULL;
}