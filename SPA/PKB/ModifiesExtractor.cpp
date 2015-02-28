#pragma once

#include "ModifiesExtractor.h"


ModifiesExtractor::ModifiesExtractor(Modifies* modifies){
	this->modifies  = modifies;
}

ModifiesExtractor::ModifiesExtractor(){

}

void ModifiesExtractor::construct(){
	buildStmtVarIndex();
	buildVarStmtIndex();
    buildVarProcIndex();
	buildProcVarIndex();
	buildStmtVarMod();
	buildVarStmtMod();
	buildVarProcMod();
	buildProcVarMod();
	buildStmtBool();
	buildProcBool();
}

void ModifiesExtractor::buildStmtVarMod(){
	    set<int> modifiers = modifies->getAllModifiersStmt();
		for(std::set<int>::iterator it=modifiers.begin(); it != modifiers.end(); ++it){	
			set<int> var = modifies->getModifiedVarStmt(*it);
			modifies->insertToStmtVarTable(var);
		}
		//return callerTable;
	}

	void ModifiesExtractor::buildVarStmtMod(){
		set<int> varSet =  modifies->getAllModifiedVarStmt();
		for(std::set<int>::iterator it=varSet.begin(); it != varSet.end(); ++it){
			set<int> mod = modifies->getModifiersStmt(*it);
		 modifies->insertToVarStmtTable(mod);
		}
	//	return calleeTable;
	}

	void ModifiesExtractor::buildProcVarMod(){
		set<int> modifiers = modifies->getAllModifiersProc();
		for(std::set<int>::iterator it=modifiers.begin(); it != modifiers.end(); ++it){
			set<int> var = modifies->getModifiedVarProc(*it);
			modifies->insertToProcVarTable(var);
		}
	//	return calleeStarTable;
	}

	void ModifiesExtractor::buildVarProcMod(){
		
		set<int> varSet = modifies->getAllModifiedVarProc();
		for(std::set<int>::iterator it=varSet.begin(); it != varSet.end(); ++it){
			set<int> mod = modifies->getModifiersProc(*it);
			modifies->insertToVarProcTable(mod);
		}
		//return callerStarTable;
	}

	void ModifiesExtractor::buildStmtVarIndex(){
		set<int> mod = modifies->getAllModifiersStmt();
		for(std::set<int>::iterator it=mod.begin(); it != mod.end(); ++it){
			int index = modifies->getStmtIndexSize();
		     modifies->insertToStmtVarIndexMap(std::pair<int,int>(*it,index ));
		}
	}

	void ModifiesExtractor::buildVarStmtIndex(){
		set<int> mod = modifies->getAllModifiedVarStmt();
		for(std::set<int>::iterator it=mod.begin(); it != mod.end(); ++it){
			int index = modifies->getVarStmtIndexSize();
			modifies->insertToVarStmtIndexMap(std::pair<int,int>(*it,index ));
		}
	}

	void ModifiesExtractor::buildProcVarIndex(){
		set<int> mod = modifies->getAllModifiersProc();
		for(std::set<int>::iterator it=mod.begin(); it != mod.end(); ++it){
			int index = modifies->getProcIndexSize();
			modifies->insertToProcVarIndexMap(std::pair<int,int>(*it,index ));
		}
	}

	void ModifiesExtractor::buildVarProcIndex(){
		set<int> mod = modifies->getAllModifiedVarProc();
		for(std::set<int>::iterator it=mod.begin(); it != mod.end(); ++it){
			int index = modifies->getVarProcIndexSize();
			modifies->insertToVarProcIndexMap(std::pair<int,int>(*it,index ));
		}
	}

	void ModifiesExtractor::buildStmtBool(){
		modifies->populateStmtBool();
	}

	void ModifiesExtractor::buildProcBool(){
		modifies->populateProcBool();
	}
