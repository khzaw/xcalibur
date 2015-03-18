#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <exception>
#include "Calls.h"

using namespace std;

    // constructor 
    Calls::Calls(){
		callTable = new vector<pair<int, int> >(); // contains entries of callers and callees 
		callerTable = new vector<set<int> >(); // calls |  contains set of callers that calls callees
		calleeTable = new vector<set<int> >(); // calls |  contains set of callees that is called by callers
		callerStarTable = new vector<set<int> >(); // calls*| contains set of callers that calls callees
		calleeStarTable = new vector<set<int> >(); // calls*| contains set of callees that is called by callers
		callerIndexMap = new unordered_map<int,int>(); 
		calleeIndexMap = new unordered_map<int,int>();
    }

	int Calls::insertCalls(int callerIndex,int calleeIndex){
		/*
		if(Calls::isCalls(callerIndex,calleeIndex)){
			return -1;
		}else{
		*/

		// cout << "stmt1 : " << callerIndex << ", " << "stmt2: " << calleeIndex << endl;
			callTable->push_back(make_pair(callerIndex,calleeIndex));
			return 0;
		//}
	}

	
	set<int> Calls::evaluateGetCallers(int callee){
		 set<int> result;
		int calleeIndex = Calls::getCalleeIndex(callee);
		if ((size_t)calleeIndex>=callerTable->size()){
			return result;
		}
		else{
		return callerTable->at(calleeIndex);
		}
	}

	set<int> Calls::evaluateGetCallees(int caller){
		set<int> result;
		int callerIndex = Calls::getCallerIndex(caller);
		if ((size_t)callerIndex>=calleeTable->size()){
			return result;
		}
		else{
		return calleeTable->at(callerIndex);
		}
	}
	

    set<int> Calls::evaluateGetCalleesStar(int caller){
		set<int> result;
		int callerIndex = Calls::getCallerIndex(caller);
		if ((size_t)callerIndex>=calleeStarTable->size()){
			return result;
		}
		else{
			
		return calleeStarTable->at(callerIndex);
		}
    }

	set<int> Calls::evaluateGetCallersStar(int callee){
	    set<int> result;
		int calleeIndex = Calls::getCalleeIndex(callee);
		if ((size_t)calleeIndex>=callerStarTable->size()){
			return result;
		}
		else{
		return callerStarTable->at(calleeIndex);
		}
	}

		set<int> Calls::getAllCallers(){
	    set<int> result;
		for(size_t i =0; i<callTable->size(); i++){
			result.insert(callTable->at(i).first);
		}
		return result;
	}

		set<int> Calls::getAllCallees(){
	    set<int> result;
		for(size_t i = 0; i<callTable->size(); i++){
			result.insert(callTable->at(i).second);
		}
		return result;
	}

	int Calls::getCallerIndex(int caller){
		std::unordered_map<int, int>::iterator it = callerIndexMap->find(caller);
		if(it == callerIndexMap->end()) {	
		return -1;
	} else {
		return it->second;
	}
	}

	int Calls::getCalleeIndex(int callee){
		std::unordered_map<int, int>::iterator it = calleeIndexMap->find(callee);
		if(it == calleeIndexMap->end()) {	
		return -1;
	} else {
		return it->second;
	}
	}

	vector<pair<int,int>>* Calls::getCallTable(){
		return callTable;
	}

	set<int> Calls::getCalleesS(int procIndex){
		set<int> calleeSet;
		//std::set<int>::iterator it = calleeSet.begin();
		for(size_t i = 0; i<callTable->size(); i++){
			if (callTable->at(i).first == procIndex){
				calleeSet.insert(callTable->at(i).second);
			}
		}
		return calleeSet;
	}

	set<int> Calls::getCallerS(int procIndex){
		set<int> callerSet;
		//std::set<int>::iterator it = calleeSet.begin();
		for(size_t i = 0; i<callTable->size(); i++){
			if (callTable->at(i).second == procIndex){
				callerSet.insert(callTable->at(i).first);
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


	bool Calls::isCalls(int caller,int callee){
		int callerIndex = Calls::getCallerIndex(caller);
		int calleeIndex = Calls::getCalleeIndex(callee);
		if (callerIndex == -1 || calleeIndex == -1){
			return false;
		}
		set<int> calleeSet = calleeTable->at(callerIndex);
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
		if (callerIndex == -1 || calleeIndex == -1){
			return false;
		}
		try {
			set<int> calleeSet = calleeStarTable->at(callerIndex);
			std::set<int>::iterator it = calleeSet.find(callee);
			if( it == calleeSet.end()) {
				return false;
			} else {
					return true;
			}
		} catch (exception& e) {
			return false;
		}
	}

	void Calls::insertToCallerTable(set<int> caller){
		callerTable->push_back(caller);
	}

	void Calls::insertToCalleeTable(set<int> callee){
		calleeTable->push_back(callee);
	}

	void Calls::insertToCallerStarTable(set<int> callerStar){
		callerStarTable->push_back(callerStar);
	}

	void Calls::insertToCalleeStarTable(set<int> calleeStar){
		calleeStarTable->push_back(calleeStar);
	}

	void Calls::insertToCallerIndexMap(pair<int,int> caller){
		callerIndexMap->insert(caller);
	}

	void Calls::insertToCalleeIndexMap(pair<int,int> callee){
		calleeIndexMap->insert(callee);
	}

	int Calls::getCalleeIndexMapSize(){

		return calleeIndexMap->size();
	}

	int Calls::getCallerIndexMapSize(){
		
		return callerIndexMap->size();
	}

	int Calls::getSize(){
		return callTable->size();
	}