#pragma once

#include "ParentExtractor.h"


ParentExtractor::ParentExtractor(Parent* parent){
	this->parent  = parent;
}
ParentExtractor::ParentExtractor(){
}

void ParentExtractor::construct(){
	buildParentIndex();
	buildChildIndex();
	buildChildTable();
	buildParentTable();
	buildChildStarTable();
	buildParentStarTable();
}

void ParentExtractor::buildChildTable(){
	    set<int> followeesSet = parent->getAllParentStmt();
		for(std::set<int>::iterator it=followeesSet.begin(); it != followeesSet.end(); ++it){	
			set<int> callerS = parent->getChildren(*it);
			parent->insertToChildrenTable(callerS);
		}
		//return callerTable;
	}

	void ParentExtractor::buildParentTable(){
		set<int> followersSet =  parent->getAllChildrenStmt();
		for(std::set<int>::iterator it=followersSet.begin(); it != followersSet.end(); ++it){
			set<int> calleeS = parent->getParents(*it);
		 parent->insertToParentTable(calleeS);
		}
	//	return calleeTable;
	}

	void ParentExtractor::buildParentStarTable(){
		
		set<int> followersSet = parent->getAllChildrenStmt();
		for(std::set<int>::iterator it=followersSet.begin(); it != followersSet.end(); ++it){
			set<int> calleeS = parent->getParentStar(*it);
			parent->insertToParentStarTable(calleeS);
		}
	//	return calleeStarTable;
	}

	void ParentExtractor::buildChildStarTable(){
		
		set<int> followeesSet = parent->getAllParentStmt();
		for(std::set<int>::iterator it=followeesSet.begin(); it != followeesSet.end(); ++it){
			set<int> callerS = parent->getChildrenStar(*it);
			parent->insertToChildrenStarTable(callerS);
		}
		//return callerStarTable;
	}

	void ParentExtractor::buildChildIndex(){
		set<int> callerSet = parent->getAllChildrenStmt();
		for(std::set<int>::iterator it=callerSet.begin(); it != callerSet.end(); ++it){
			int index = parent->getChildrenIndexMapSize();
		parent->insertToChildrenIndexMap(std::pair<int,int>(*it,index ));
		}
	}

	void ParentExtractor::buildParentIndex(){
		set<int> calleeSet = parent->getAllParentStmt();
		for(std::set<int>::iterator it=calleeSet.begin(); it != calleeSet.end(); ++it){
			int index = parent->getParentIndexMapSize();
			parent->insertToParentIndexMap(std::pair<int,int>(*it,index ));
		}
	}
