#pragma once

#include "Uses.h"
#include "PKBController.h"


UsesExtractor::UsesExtractor(Uses* uses){
	this->uses  = uses;
}

UsesExtractor::UsesExtractor(){

}

UsesExtractor::~UsesExtractor(){
}

void UsesExtractor::construct(){
	buildStmtVarIndex();
	buildVarStmtIndex();
    buildVarProcIndex();
	buildProcVarIndex();
	buildStmtVarUses();
	buildVarStmtUses();
	buildVarProcUses();
	buildProcVarUses();
	buildStmtBool();
	buildProcBool();
}

void UsesExtractor::buildStmtVarUses(){
	    set<int> users = uses->getAllUsersStmt();
		for(std::set<int>::iterator it=users.begin(); it != users.end(); ++it){	
			set<int> var = uses->getUsedVarStmt(*it);
			uses->insertToStmtVarTable(var);
		}
		//return callerTable;
	}

	void UsesExtractor::buildVarStmtUses(){
		set<int> varSet =  uses->getAllUsedVarStmt();
		for(std::set<int>::iterator it=varSet.begin(); it != varSet.end(); ++it){
			set<int> use = uses->getUsersStmt(*it);
		 uses->insertToVarStmtTable(use);
		}
	//	return calleeTable;
	}

	void UsesExtractor::buildProcVarUses(){
		set<int> users = uses->getAllUsersProc();
		for(std::set<int>::iterator it=users.begin(); it != users.end(); ++it){
			set<int> var = uses->getUsedVarProc(*it);
			uses->insertToProcVarTable(var);
		}
	//	return calleeStarTable;
	}

	void UsesExtractor::buildVarProcUses(){
		
		set<int> varSet = uses->getAllUsedVarProc();
		for(std::set<int>::iterator it=varSet.begin(); it != varSet.end(); ++it){
			set<int> use = uses->getUsersProc(*it);
			uses->insertToVarProcTable(use);
		}
		//return callerStarTable;
	}

	void UsesExtractor::buildStmtVarIndex(){
		set<int> use = uses->getAllUsersStmt();
		for(std::set<int>::iterator it=use.begin(); it != use.end(); ++it){
			int index = uses->getStmtIndexSize();
		     uses->insertToStmtVarIndexMap(std::pair<int,int>(*it,index ));
		}
	}

	void UsesExtractor::buildVarStmtIndex(){
		set<int> use = uses->getAllUsedVarStmt();
		for(std::set<int>::iterator it=use.begin(); it != use.end(); ++it){
			int index = uses->getVarStmtIndexSize();
			uses->insertToVarStmtIndexMap(std::pair<int,int>(*it,index ));
		}
	}

	void UsesExtractor::buildProcVarIndex(){
		set<int> use = uses->getAllUsersProc();
		for(std::set<int>::iterator it=use.begin(); it != use.end(); ++it){
			int index = uses->getProcIndexSize();
			uses->insertToProcVarIndexMap(std::pair<int,int>(*it,index ));
		}
	}

	void UsesExtractor::buildVarProcIndex(){
		set<int> use = uses->getAllUsedVarProc();
		for(std::set<int>::iterator it=use.begin(); it != use.end(); ++it){
			int index = uses->getVarProcIndexSize();
			uses->insertToVarProcIndexMap(std::pair<int,int>(*it,index ));
		}
	}

	void UsesExtractor::buildStmtBool(){
		uses->populateStmtBool();
	}

	void UsesExtractor::buildProcBool(){
		uses->populateProcBool();
	}
