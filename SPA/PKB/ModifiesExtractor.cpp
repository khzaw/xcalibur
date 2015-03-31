#pragma once

#include "ModifiesExtractor.h"


ModifiesExtractor::ModifiesExtractor(Modifies* modifies, ProcTable* procTable, Calls* callsTable) {
	this->modifies  = modifies;
	this->procTable = procTable;
	this->callsTable = callsTable;
}

ModifiesExtractor::ModifiesExtractor(){

}

void ModifiesExtractor::construct(){
	buildCallStmtMod();
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

void ModifiesExtractor::buildCallStmtMod() {

	// for each procedure
	set<int> allProcedures = procTable->getAllProc();
	for(std::set<int>::iterator it = allProcedures.begin(); it != allProcedures.end(); ++it) {
		// get all variables modified by a procedure
		set<int> variablesInProc = modifies->getAllVariablesModifiedByProc(*it);

		// get all caller procedures
		set<int> callerProcedures = callsTable->getCallerS(*it);

		for(std::set<int>::iterator i = callerProcedures.begin(); i != callerProcedures.end(); ++i) {
			for(std::set<int>::iterator j = variablesInProc.begin(); j != variablesInProc.end(); ++j) {
				modifies->insertModifiesProc(*i, *j);
			}
		}


	}

	//for(std::set<int>::iterator it=
	// get all variables modified by a procedure
	// get all caller procedures
	// set modifies
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
