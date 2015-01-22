#include "Parent.h"
#include <vector>
#include <algorithm>

using namespace std;

Parent::Parent(){
}

void Parent::insertParent(int stmt1, int stmt2){
	if(!(isParentTrue(stmt1,stmt2))){
	pair<int,int> record(stmt1, stmt2);
	records.push_back(record);
	}
}

vector<int> Parent::getChildren(int stmt){
	vector<int> listChildren;
	for(size_t i=0; i<records.size();i++){
			if(records[i].first==stmt){
				listChildren.push_back(records[i].second);
			}
		}
		return listChildren;
	}
	
vector<int> Parent::getParents(int stmt){
	vector<int> listParents;
	for(size_t i=0; i<records.size();i++){
			if(records[i].second==stmt){
				listParents.push_back(records[i].first);
			}
		}
		return listParents;
	}
	
vector<int> Parent::getChildrenStar(int stmt){
	vector<int> children;
	children = Parent::recursiveChildrenStar(children,stmt);
	return children;
}

vector<int> Parent::recursiveChildrenStar(vector<int> &children,int stmt){
	vector<int> childrenSublist ;
	childrenSublist = Parent::getChildren(stmt);
	if(childrenSublist.size()==0)
		return children;
	children.insert(children.end(), childrenSublist.begin(), childrenSublist.end());
	for(std::vector<int>::iterator it=childrenSublist.begin(); it != childrenSublist.end(); ++it){
		recursiveChildrenStar(children,*it);
	}
	return children;
}

int Parent::getSize(){
	return records.size();
}


vector<int> Parent::getParentStar(int stmt){
	vector<int> parents;
	parents = Parent::recursiveParentStar(parents,stmt);
	return parents;
}

vector<int> Parent::recursiveParentStar(vector<int> &parents,int stmt){
	vector<int> parentsSublist ;
	parentsSublist = Parent::getParents(stmt);
	if(parentsSublist.size()==0)
		return parents;
	parents.insert(parents.end(), parentsSublist.begin(), parentsSublist.end());
	for(std::vector<int>::iterator it=parentsSublist.begin(); it != parentsSublist.end(); ++it){
		recursiveParentStar(parents,*it);
	}
	return parents;
}
	
bool Parent::isParentTrue(int stmt1, int stmt2){
	vector<int> children ;
	children = Parent::getChildren(stmt1);
	for (std::vector<int>::iterator it=children.begin(); it != children.end(); ++it){
		if(*it==stmt2)
			return true;
	}
	return false;
}

bool Parent::isParentStarTrue(int stmt1, int stmt2){
	vector<int> childrenStar ;
	childrenStar = Parent::getChildrenStar(stmt1);
	for (std::vector<int>::iterator it=childrenStar.begin(); it != childrenStar.end(); ++it){
		if(*it==stmt2)
			return true;
	}
	return false;
}

vector<int> Parent::getAllChildrenStmt(){
	vector<int> children ;
	for (size_t i=0; i<records.size();i++){
		if(std::find(children.begin(), children.end(), records[i].second)!=children.end()){
		}else {
	    children.push_back(records[i].second);
        }
	}
	//children.unique();
	return children;
}

vector<int> Parent::getAllParentStmt(){
	vector<int> parents ;
	for (size_t i=0; i<records.size();i++){
		if(std::find(parents.begin(), parents.end(), records[i].first)!=parents.end()){
		}else {
	    parents.push_back(records[i].first);
        }
	}
	
	return parents;
}

