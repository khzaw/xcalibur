#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Calls.h"

using namespace std;

    // constructor 
    Calls::Calls(){
    }

	int Calls::insertCalls(int callerIndex,int calleeIndex){
		/*
		if(Calls::isCalls(callerIndex,calleeIndex)){
			return -1;
		}else{
		*/
			callTable.push_back(make_pair(callerIndex,calleeIndex));
			return 0;
		//}
	}

	
	set<int> Calls::getCallers(int callee){
		 set<int> result;
		int calleeIndex = Calls::getCalleeIndex(callee);
		if(calleeIndex>=callerTable.size()){
			return result;
		}
		else{
		return callerTable[calleeIndex];
		}
	}

	set<int> Calls::getCallees(int caller){
		set<int> result;
		int callerIndex = Calls::getCallerIndex(caller);
		if(callerIndex>=calleeTable.size()){
			return result;
		}
		else{
		return calleeTable[callerIndex];
		}
	}
	

    set<int> Calls::getCalleesStar(int caller){
		set<int> result;
		int callerIndex = Calls::getCallerIndex(caller);
		if(callerIndex>=calleeStarTable.size()){
			return result;
		}
		else{
			
		return calleeStarTable[callerIndex];
		}
    }

	set<int> Calls::getCallersStar(int callee){
	    set<int> result;
		int calleeIndex = Calls::getCalleeIndex(callee);
		if(calleeIndex>=callerStarTable.size()){
			return result;
		}
		else{
		return callerStarTable[calleeIndex];
		}
	}

		set<int> Calls::getAllCallers(){
	    set<int> result;
		for(int i =0;i<callTable.size();i++){
			result.insert(callTable[i].first);
		}
		return result;
	}

		set<int> Calls::getAllCallees(){
	    set<int> result;
		for(int i =0;i<callTable.size();i++){
			result.insert(callTable[i].second);
		}
		return result;
	}

	int Calls::getCallerIndex(int caller){
		std::map<int, int>::iterator it = callerIndexMap.find(caller);
		if(it == callerIndexMap.end()) {	
		return -1;
	} else {
		return it->second;
	}
	}

	int Calls::getCalleeIndex(int callee){
		std::map<int, int>::iterator it = calleeIndexMap.find(callee);
		if(it == calleeIndexMap.end()) {	
		return -1;
	} else {
		return it->second;
	}
	}

	vector<pair<int,int>> Calls::getCallTable(){
		return callTable;
	}

	set<int> Calls::getCalleesS(int procIndex){
		set<int> calleeSet;
		//std::set<int>::iterator it = calleeSet.begin();
		for(int i =0;i<callTable.size();i++){
			if (callTable[i].first == procIndex){
				calleeSet.insert(callTable[i].second);
			}
		}
		return calleeSet;
	}

	set<int> Calls::getCallerS(int procIndex){
		set<int> callerSet;
		//std::set<int>::iterator it = calleeSet.begin();
		for(int i =0;i<callTable.size();i++){
			if (callTable[i].second == procIndex){
				callerSet.insert(callTable[i].first);
			}
		}
		return callerSet;
	}

	set<int> Calls::getCalleeStar(int stmt){
	set<int> calleeSet;
	calleeSet = Calls::recursiveCalleeStar(calleeSet,stmt);
	return calleeSet;
}

	set<int> Calls::recursiveCalleeStar(set<int> &callees,int stmt){
	set<int> calleeSublist ;
	calleeSublist = Calls::getCalleesS(stmt);
	if(calleeSublist.size()==0)
		return callees;
	callees.insert(calleeSublist.begin(), calleeSublist.end());
	for(std::set<int>::iterator it=calleeSublist.begin(); it != calleeSublist.end(); ++it){
		recursiveCalleeStar(callees,*it);
	}
	return callees;
}

	set<int> Calls::getCallerStar(int stmt){
	set<int> callerSet;
	callerSet = Calls::recursiveCallerStar(callerSet,stmt);
	return callerSet;
}

	set<int> Calls::recursiveCallerStar(set<int> &callers,int stmt){
	set<int> callerSublist ;
	callerSublist = Calls::getCallerS(stmt);
	if(callerSublist.size()==0)
		return callers;
	callers.insert(callerSublist.begin(), callerSublist.end());
	for(std::set<int>::iterator it=callerSublist.begin(); it != callerSublist.end(); ++it){
		recursiveCallerStar(callers,*it);
	}
	return callers;
}

	vector<set<int>> Calls::buildCallerTable(){
	    set<int> calleesSet = Calls::getAllCallees();
		for(std::set<int>::iterator it=calleesSet.begin(); it != calleesSet.end(); ++it){	
			set<int> callerS = Calls::getCallerS(*it);
			callerTable.push_back(callerS);
		}
		return callerTable;
	}

	vector<set<int>> Calls::buildCalleeTable(){
		set<int> callersSet = Calls::getAllCallers();
		for(std::set<int>::iterator it=callersSet.begin(); it != callersSet.end(); ++it){
			set<int> calleeS = Calls::getCalleesS(*it);
			calleeTable.push_back(calleeS);
		}
		return calleeTable;
	}

	vector<set<int>> Calls::buildCalleeStarTable(){
		
		set<int> callersSet = Calls::getAllCallers();
		for(std::set<int>::iterator it=callersSet.begin(); it != callersSet.end(); ++it){
			set<int> calleeS = Calls::getCalleeStar(*it);
			calleeStarTable.push_back(calleeS);
		}
		return calleeStarTable;
	}

	vector<set<int>> Calls::buildCallerStarTable(){
		
		set<int> calleesSet = Calls::getAllCallees();
		for(std::set<int>::iterator it=calleesSet.begin(); it != calleesSet.end(); ++it){
			set<int> callerS = Calls::getCallerStar(*it);
			callerStarTable.push_back(callerS);
		}
		return callerStarTable;
	}

	void Calls::buildCallerIndex(){
		set<int> callerSet = getAllCallers();
		for(std::set<int>::iterator it=callerSet.begin(); it != callerSet.end(); ++it){
			int index = callerIndexMap.size();
		callerIndexMap.insert(std::pair<int,int>(*it,index ));
		}
	}

	void Calls::buildCalleeIndex(){
		set<int> calleeSet = getAllCallees();
		for(std::set<int>::iterator it=calleeSet.begin(); it != calleeSet.end(); ++it){
			int index = calleeIndexMap.size();
		calleeIndexMap.insert(std::pair<int,int>(*it,index ));
		}
	}

	bool Calls::isCalls(int caller,int callee){
		int callerIndex = Calls::getCallerIndex(caller);
		int calleeIndex = Calls::getCalleeIndex(callee);
	   set<int> calleeSet = calleeTable[callerIndex];
	   std::set<int>::iterator it = calleeSet.find(callee);
	   if( it == calleeSet.end()){
		   return false;
	   }else{
		   return true;
	   }
	}

	bool Calls::isCallsStar(int caller,int callee){
		int callerIndex = Calls::getCallerIndex(caller);
		int calleeIndex = Calls::getCalleeIndex(callee);
		set<int> calleeSet = calleeStarTable[callerIndex];
	   std::set<int>::iterator it = calleeSet.find(callee);
	   if( it == calleeSet.end()){
		   return false;
	   }else{
		   return true;
	   }
	}

	int Calls::getSize(){
		return callTable.size();
	}