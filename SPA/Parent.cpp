#include "Parent.h"
#include <list>

using namespace std;

Parent::Parent(){
}

void Parent::insertParent(int stmt1, int stmt2){
	pair<int,int> record(stmt1, stmt2);
	records.push_back(record);
}

list<int> Parent::getChildren(int stmt){
	list<int> listChildren;
	for(int i=0; i<records.size();i++){
			if(records[i].first==stmt){
				listChildren.push_back(records[i].second);
			}
		}
		return listChildren;
	}
	
list<int> Parent::getParents(int stmt){
	list<int> listParents;
	for(int i=0; i<records.size();i++){
			if(records[i].second==stmt){
				listParents.push_back(records[i].first);
			}
		}
		return listParents;
	}
	
list<int> Parent::getChildrenStar(int stmt){
	list<int> children;
	children = Parent::recursiveChildrenStar(children,stmt);
	return children;
}

list<int> Parent::recursiveChildrenStar(list<int> &children,int stmt){
	list<int> childrenSublist ;
	childrenSublist = Parent::getChildren(stmt);
	if(childrenSublist.size()==0)
		return children;
	children.insert(children.end(), childrenSublist.begin(), childrenSublist.end());
	for(std::list<int>::iterator it=childrenSublist.begin(); it != childrenSublist.end(); ++it){
		recursiveChildrenStar(children,*it);
	}
	return children;
}

list<int> Parent::getParentStar(int stmt){
	list<int> parents;
	parents = Parent::recursiveParentStar(parents,stmt);
	return parents;
}

list<int> Parent::recursiveParentStar(list<int> &parents,int stmt){
	list<int> parentsSublist ;
	parentsSublist = Parent::getParents(stmt);
	if(parentsSublist.size()==0)
		return parents;
	parents.insert(parents.end(), parentsSublist.begin(), parentsSublist.end());
	for(std::list<int>::iterator it=parentsSublist.begin(); it != parentsSublist.end(); ++it){
		recursiveParentStar(parents,*it);
	}
	return parents;
}
	
bool Parent::isParentTrue(int stmt1, int stmt2){
	list<int> children ;
	children = Parent::getChildren(stmt1);
	for (std::list<int>::iterator it=children.begin(); it != children.end(); ++it){
		if(*it==stmt2)
			return true;
	}
	return false;
}

list<int> Parent::getAllChildrenStmt(){
	list<int> children ;
	for (int i=0; i<records.size();i++){
		children.push_back(records[i].second);
	}
	children.unique();
	return children;
}

list<int> Parent::getAllParentStmt(){
	list<int> parents ;
	for (int i=0; i<records.size();i++){
		parents.push_back(records[i].first);
	}
	parents.unique();
	return parents;
}

