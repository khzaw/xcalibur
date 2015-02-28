#pragma once

#include "FollowsExtractor.h"



FollowsExtractor::FollowsExtractor(Follows* follows){
	this->follows  = follows;
}
FollowsExtractor::FollowsExtractor(){

}

void FollowsExtractor::construct(){
	buildFollowerIndex();
	buildFolloweeIndex();
	buildFollowerTable();
	buildFolloweeTable();
	buildFollowerStarTable();
	buildFolloweeStarTable();	
}

void FollowsExtractor::buildFollowerTable(){
	    set<int> followeesSet = follows->getAllFolloweeStmt();
		for(std::set<int>::iterator it=followeesSet.begin(); it != followeesSet.end(); ++it){	
			set<int> callerS = follows->getFollowers(*it);
			follows->insertToFollowerTable(callerS);
		}
		//return callerTable;
	}

	void FollowsExtractor::buildFolloweeTable(){
		set<int> followersSet =  follows->getAllFollowerStmt();
		for(std::set<int>::iterator it=followersSet.begin(); it != followersSet.end(); ++it){
			set<int> calleeS = follows->getFollowees(*it);
		 follows->insertToFolloweeTable(calleeS);
		}
	//	return calleeTable;
	}

	void FollowsExtractor::buildFolloweeStarTable(){
		
		set<int> followersSet = follows->getAllFollowerStmt();
		for(std::set<int>::iterator it=followersSet.begin(); it != followersSet.end(); ++it){
			set<int> calleeS = follows->getFolloweesStar(*it);
			follows->insertToFolloweeStarTable(calleeS);
		}
	//	return calleeStarTable;
	}

	void FollowsExtractor::buildFollowerStarTable(){
		
		set<int> followeesSet = follows->getAllFolloweeStmt();
		for(std::set<int>::iterator it=followeesSet.begin(); it != followeesSet.end(); ++it){
			set<int> callerS = follows->getFollowersStar(*it);
			follows->insertToFollowerStarTable(callerS);
		}
		//return callerStarTable;
	}

	void FollowsExtractor::buildFollowerIndex(){
		set<int> callerSet = follows->getAllFollowerStmt();
		for(std::set<int>::iterator it=callerSet.begin(); it != callerSet.end(); ++it){
			int index = follows->getFollowerIndexMapSize();
		follows->insertToFollowerIndexMap(std::pair<int,int>(*it,index ));
		}
	}

	void FollowsExtractor::buildFolloweeIndex(){
		set<int> calleeSet = follows->getAllFolloweeStmt();
		for(std::set<int>::iterator it=calleeSet.begin(); it != calleeSet.end(); ++it){
			int index = follows->getFolloweeIndexMapSize();
			follows->insertToFolloweeIndexMap(std::pair<int,int>(*it,index ));
		}
	}
