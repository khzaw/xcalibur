#pragma once

#include "Calls.h"
#include "PKBController.h"


CallsExtractor::CallsExtractor(Calls* calls){
	this->calls  = calls;
}

CallsExtractor::CallsExtractor(){

}

CallsExtractor::~CallsExtractor(){
}

void CallsExtractor::construct(){
	buildCallerIndex();
	buildCalleeIndex();
	buildCallerTable();
	buildCalleeTable();
	buildCallerStarTable();
	buildCalleeStarTable();
}

void CallsExtractor::buildCallerTable(){
	    set<int> calleesSet = calls->getAllCallees();
		for(std::set<int>::iterator it=calleesSet.begin(); it != calleesSet.end(); ++it){	
			set<int> callerS = calls->getCallerS(*it);
			calls->insertToCallerTable(callerS);
		}
		//return callerTable;
	}

	void CallsExtractor::buildCalleeTable(){
		set<int> callersSet =  calls->getAllCallers();
		for(std::set<int>::iterator it=callersSet.begin(); it != callersSet.end(); ++it){
			set<int> calleeS = calls->getCalleesS(*it);
		 calls->insertToCalleeTable(calleeS);
		}
	//	return calleeTable;
	}

	void CallsExtractor::buildCalleeStarTable(){
		
		set<int> callersSet = calls->getAllCallers();
		for(std::set<int>::iterator it=callersSet.begin(); it != callersSet.end(); ++it){
			set<int> calleeS = calls->getCalleeStar(*it);
			calls->insertToCalleeStarTable(calleeS);
		}
	//	return calleeStarTable;
	}

	void CallsExtractor::buildCallerStarTable(){
		
		set<int> calleesSet = calls->getAllCallees();
		for(std::set<int>::iterator it=calleesSet.begin(); it != calleesSet.end(); ++it){
			set<int> callerS = calls->getCallerStar(*it);
			calls->insertToCallerStarTable(callerS);
		}
		//return callerStarTable;
	}

	void CallsExtractor::buildCallerIndex(){
		set<int> callerSet = calls->getAllCallers();
		for(std::set<int>::iterator it=callerSet.begin(); it != callerSet.end(); ++it){
			int index = calls->getCallerIndexMapSize();
		calls->insertToCallerIndexMap(std::pair<int,int>(*it,index ));
		}
	}

	void CallsExtractor::buildCalleeIndex(){
		set<int> calleeSet = calls->getAllCallees();
		for(std::set<int>::iterator it=calleeSet.begin(); it != calleeSet.end(); ++it){
			int index = calls->getCalleeIndexMapSize();
			calls->insertToCalleeIndexMap(std::pair<int,int>(*it,index ));
		}
	}
