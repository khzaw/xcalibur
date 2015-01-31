#include "Parent.h"
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>

using namespace std;

Parent::Parent(){
}

void Parent::insertParent(int stmt1, int stmt2){
	if(!(isParentTrue(stmt1,stmt2))){
	pair<int,int> record(stmt1, stmt2);
	parentTable.push_back(record);
	}
}

set<int> Parent::getChildren(int stmt){
	set<int> listChildren;
	for(size_t i=0; i<parentTable.size();i++){
			if(parentTable[i].first==stmt){
				listChildren.insert(parentTable[i].second);
			}
		}
		return listChildren;
	}
	
set<int> Parent::getParents(int stmt){
	set<int> listParent;
	for(size_t i=0; i<parentTable.size();i++){
			if(parentTable[i].second==stmt){
				listParent.insert(parentTable[i].first);
			}
		}
		return listParent;
	}
	
set<int> Parent::getChildrenStar(int stmt){
	set<int> children;
	children = Parent::recursiveChildrenStar(children,stmt);
	return children;
}

set<int> Parent::recursiveChildrenStar(set<int> &children,int stmt){
	set<int> childrenSublist ;
	childrenSublist = Parent::getChildren(stmt);
	if(childrenSublist.size()==0)
		return children;
	children.insert( childrenSublist.begin(), childrenSublist.end());
	for(std::set<int>::iterator it=childrenSublist.begin(); it != childrenSublist.end(); ++it){
		recursiveChildrenStar(children,*it);
	}
	return children;
}

int Parent::getSize(){
	return parentTable.size();
}


set<int> Parent::getParentStar(int stmt){
	set<int> parents;
	parents = Parent::recursiveParentStar(parents,stmt);
	return parents;
}

set<int> Parent::recursiveParentStar(set<int> &parents,int stmt){
	set<int> parentsSublist ;
	parentsSublist = Parent::getParents(stmt);
	if(parentsSublist.size()==0)
		return parents;
	parents.insert(parentsSublist.begin(), parentsSublist.end());
	for(std::set<int>::iterator it=parentsSublist.begin(); it != parentsSublist.end(); ++it){
		recursiveParentStar(parents,*it);
	}
	return parents;
}
	
bool Parent::isParentTrue(int stmt1, int stmt2){
	set<int> children ;
	children = Parent::getChildren(stmt1);
	for (std::set<int>::iterator it=children.begin(); it != children.end(); ++it){
		if(*it==stmt2)
			return true;
	}
	return false;
}

bool Parent::isParentStarTrue(int stmt1, int stmt2){
	set<int> childrenStar ;
	childrenStar = Parent::getChildrenStar(stmt1);
	for (std::set<int>::iterator it=childrenStar.begin(); it != childrenStar.end(); ++it){
		if(*it==stmt2)
			return true;
	}
	return false;
}

set<int> Parent::getAllChildrenStmt(){
	set<int> children;
		//std::set<int>::iterator it = calleeSet.begin();
		for(int i =0;i<parentTable.size();i++){		
				children.insert(parentTable[i].second);
		}
		return children;
}

set<int> Parent::getAllParentStmt(){
		set<int> parent;
		//std::set<int>::iterator it = calleeSet.begin();
		for(int i =0;i<parentTable.size();i++){		
				parent.insert(parentTable[i].first);
		}
		return parent;
}


int Parent::getChildrenIndex(int children){
		std::unordered_map<int, int>::iterator it = childrenMap.find(children);
		if(it == childrenMap.end()) {	
		return -1;
	} else {
		return it->second;
	}
}

int Parent::getParentIndex(int parent){
		std::unordered_map<int, int>::iterator it = parentMap.find(parent);
		if(it == parentMap.end()) {	
		return -1;
	} else {
		return it->second;
	}
}

//======= BUILDING Tables / Map =========== // 
unordered_map<int,int> Parent::buildChildrenIndex(){
		set<int> childrenSet = Parent::getAllChildrenStmt();
		for(std::set<int>::iterator it=childrenSet.begin(); it != childrenSet.end(); ++it){
			int index = childrenMap.size();
		childrenMap.insert(std::pair<int,int>(*it,index ));
		}
		return childrenMap;
	}

unordered_map<int,int> Parent::buildParentIndex(){
		set<int> parentSet = Parent::getAllParentStmt();
		for(std::set<int>::iterator it=parentSet.begin(); it != parentSet.end(); ++it){
			int index = parentMap.size();
		parentMap.insert(std::pair<int,int>(*it,index ));
		}
		return parentMap;
	}

// Parent - > children
vector<set<int>> Parent::buildChildrenTable(){
	 set<int> parentSet = Parent::getAllParentStmt();
	
		for(std::set<int>::iterator it=parentSet.begin(); it != parentSet.end(); ++it){	
			set<int> children = Parent::getChildren(*it);
				
			cTable.push_back(children);
		}
		return cTable;
}

vector<set<int>> Parent::buildParentTable(){
	 set<int> childrenSet = Parent::getAllChildrenStmt();
		for(std::set<int>::iterator it=childrenSet.begin(); it != childrenSet.end(); ++it){	
			set<int> parent = Parent::getParents(*it);
			
			pTable.push_back(parent);
		}
		return pTable;
}

vector<set<int>> Parent::buildParentStarTable(){
		set<int> childrenSet = Parent::getAllChildrenStmt();
		for(std::set<int>::iterator it=childrenSet.begin(); it != childrenSet.end(); ++it){
			set<int> parentStar = Parent::getParentStar(*it);
			
			parentStarTable.push_back(parentStar);
		}
		return parentStarTable;
}

vector<set<int>> Parent::buildChildrenStarTable(){
		set<int> parentSet = Parent::getAllParentStmt();
		for(std::set<int>::iterator it=parentSet.begin(); it != parentSet.end(); ++it){
			set<int> childrenStar = Parent::getChildrenStar(*it);
			
			childrenStarTable.push_back(childrenStar);
		}
		return childrenStarTable;
}

/*
void Parent::printAll() {
	for(size_t i = 0; i < followTable.size(); i++) {
		cout << followTable[i].first << ", " << followTable[i].second << endl;
	}
}
*/

set<int> Parent::evaluateGetChildren(int stmt){
	set<int> results;
	int index = Parent::getParentIndex(stmt);
	if(index == -1 || index >= cTable.size()){
		return results;
	}else{
		results = cTable[index];
		return results;
	}
}
	 set<int> Parent::evaluateGetParent(int stmt){
	set<int> results;
	int index = Parent::getChildrenIndex(stmt);
	if(index == -1 || index >= pTable.size()){
		return results;
	}else{
		results = pTable[index];
		return results;
	}
}

	 set<int> Parent::evaluateGetChildrenStar(int stmt){
	set<int> results;
	int index = Parent::getParentIndex(stmt);
	if(index == -1 || index >= childrenStarTable.size()){
		return results;
	}else{
		results = childrenStarTable[index];
		return results;
	}
}

	 set<int> Parent::evaluateGetParentStar(int stmt){
	 set<int> results;
	int index = Parent::getChildrenIndex(stmt);
	if(index == -1 || index >= parentStarTable.size()){
		return results;
	}else{
		results = parentStarTable[index];
		return results;
	}
	 }

	 bool Parent::evaluateIsParent(int parent,int children){
		 int index = getParentIndex(parent);
		 if(index == -1){
			 return false;
		 }else{
			 set<int> childrenSet = cTable[index]; 
		      std::set<int>::iterator it = childrenSet.find(children);
	   if( it == childrenSet.end()){
		   return false;
	   }else{
		   return true;
	   }
		 }
	 }

	 bool Parent::evaluateIsParentStar(int parent,int children){
		 int index = getParentIndex(parent);
		 if(index == -1){
			 return false;
		 }else{
			 set<int> childrenStarSet = childrenStarTable[index]; 
		      std::set<int>::iterator it = childrenStarSet.find(children);
	   if( it == childrenStarSet.end()){
		   return false;
	   }else{
		   return true;
	   }
		 }
	 }

	 void Parent::insertToChildrenTable(set<int> children){
		cTable.push_back(children);
	}

	void Parent::insertToParentTable(set<int> parent){
		pTable.push_back(parent);
	}

	void Parent::insertToChildrenStarTable(set<int> childrenStar){
		childrenStarTable.push_back(childrenStar);
	}

	void Parent::insertToParentStarTable(set<int> parentStar){
		parentStarTable.push_back(parentStar);
	}

	void Parent::insertToChildrenIndexMap(pair<int,int> children){
		childrenMap.insert(children);
	}

	void Parent::insertToParentIndexMap(pair<int,int> parent){
		parentMap.insert(parent);
	}

	int Parent::getParentIndexMapSize(){

		return parentMap.size();
	}

	int Parent::getChildrenIndexMapSize(){
		
		return childrenMap.size();
	}
