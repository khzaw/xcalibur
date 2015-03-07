#include "Modifies.h"
#include <utility>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

	Modifies::Modifies(){
		
	}
	
   void Modifies::insertModifiesStmt(int stmt,int varIndex){
	  if(!( isModifiesStmt(stmt,varIndex))){
	   stmtMod.push_back(make_pair(stmt,varIndex));
	  }
   }

   int Modifies::getSizeStmtModifies() {
	   return stmtMod.size();
   }

   int Modifies::getSizeProcModifies() {
	   return procMod.size();
   }
   set<int> Modifies::getAllModifiersStmt(){
	    set<int> result;
		for(size_t i = 0; i<stmtMod.size(); i++){
			result.insert(stmtMod[i].first);
		}
		return result;
	}

   set<int> Modifies::getAllModifiedVarStmt(){
	    set<int> result;
		for(size_t i =0; i<stmtMod.size(); i++){
			result.insert(stmtMod[i].second);
		}
		return result;
	}

     set<int> Modifies::getAllModifiersProc(){
	    set<int> result;
		for(size_t i = 0; i<procMod.size(); i++){
			result.insert(procMod[i].first);
		}
		return result;
	}

	 set<int> Modifies::getAllModifiedVarProc(){
	    set<int> result;
		for(size_t i =0; i<procMod.size(); i++){
			result.insert(procMod[i].second);
		}
		return result;
	}

	 set<int> Modifies::getModifiersStmt(int varIndex){
		set<int> modifiersSet;
		//std::set<int>::iterator it = calleeSet.begin();
		for(size_t i =0; i<stmtMod.size(); i++){
			if (stmtMod[i].second == varIndex){
				modifiersSet.insert(stmtMod[i].first);
			}
		}
		return modifiersSet;
	}


	set<int> Modifies::getModifiedVarStmt(int stmt){
		set<int> modifiedVarSet;
		
		//std::set<int>::iterator it = calleeSet.begin();
		for(size_t i =0; i<stmtMod.size(); i++){
			if (stmtMod[i].first == stmt){
			
				modifiedVarSet.insert(stmtMod[i].second);
			}
		}
		return modifiedVarSet;
	}

	set<int> Modifies::getModifiersProc(int varIndex){
		set<int> modifiersSet;
		//std::set<int>::iterator it = calleeSet.begin();
		for(size_t i = 0; i<procMod.size(); i++){
			if (procMod[i].second == varIndex){
				modifiersSet.insert(procMod[i].first);
			}
		}
		return modifiersSet;
	}


	set<int> Modifies::getModifiedVarProc(int stmt){
		set<int> modifiedVarSet;
		//std::set<int>::iterator it = calleeSet.begin();
		for(size_t i =0; i<procMod.size(); i++){
			if (procMod[i].first == stmt){
				modifiedVarSet.insert(procMod[i].second);
			}
		}
		return modifiedVarSet;
	}



	vector<pair<int,int>> Modifies::getModifiesStmt(){
		return stmtMod;
	}
	
	int Modifies::getStmtIndexSize(){
		return stmtVarIndexMap.size();
	}
	int Modifies::getVarStmtIndexSize(){
		return varStmtIndexMap.size();
	}

	int Modifies::getProcIndexSize(){
		return procVarIndexMap.size();
	}

	int Modifies::getVarProcIndexSize(){
		return varProcIndexMap.size();
	}

	int Modifies::getStmtVarIndex(int stmt){
		std::unordered_map<int, int>::iterator it = stmtVarIndexMap.find(stmt);
		if(it == stmtVarIndexMap.end()) {	
		return -1;
	} else {
		return it->second;
	}
	}

    int Modifies::getVarStmtIndex(int stmt){
		std::unordered_map<int, int>::iterator it = varStmtIndexMap.find(stmt);
		if(it == varStmtIndexMap.end()) {	
		return -1;
	} else {
		return it->second;
	}
	}

	int Modifies::getProcVarIndex(int proc){
		std::unordered_map<int, int>::iterator it = procVarIndexMap.find(proc);
		if(it == procVarIndexMap.end()) {	
		return -1;
	} else {
		return it->second;
	}
	}

	int Modifies::getVarProcIndex(int proc){
		std::unordered_map<int, int>::iterator it = varProcIndexMap.find(proc);
		if(it == varProcIndexMap.end()) {	
		return -1;
	} else {
		return it->second;
	}
	}

	//Pre condition: varIndex is positive
	set<int> Modifies::evaluateGetModifiersStmt(int varIndex){
		set<int> result;
		int index = getVarStmtIndex(varIndex);
		if((size_t)index >= varStmtMod.size()){
			return result;
		}
		else{
		return varStmtMod[index];
		}
	}

	//Pre condition: stmt no. is positive
	set<int> Modifies::evaluateGetModifiedVarStmt(int stmt){
	    set<int> result;
		
		int index = Modifies::getStmtVarIndex(stmt);
		
		if((size_t)index > stmtVarMod.size()){
			return result;
		}
		else{
		return stmtVarMod[index];
		}
	}

   bool Modifies::isModifiesStmt(int stmt, int varIndex){
	 for(size_t i = 0; i<stmtMod.size(); i++){
		 if(stmtMod[i].first == stmt && stmtMod[i].second == varIndex){
			 return true;
		 }else{
			 return false;
		 }
	 }
   }

   	
   void Modifies::insertModifiesProc(int procIndex,int varIndex){
	    if(!( isModifiesProc(procIndex,varIndex))){
	procMod.push_back(make_pair(procIndex,varIndex));
	  }  
   }

	vector<pair<int,int>> Modifies::getModifiesProc(){
		return procMod;
	}
	
	set<int> Modifies::evaluateGetModifiersProc(int varIndex){
		set<int> result;
		int index = getVarProcIndex(varIndex);
		if ((size_t)index >= varProcMod.size()){
			return result;
		}
		else{
		return varProcMod[index];
		}
	}

	set<int> Modifies::evaluateGetModifiedVarProc(int procIndex){
		set<int> result;

		int index = getProcVarIndex(procIndex);
	
		if ((size_t)index >= procVarMod.size()){
			return result;
		}
		else{
		return procVarMod[index];
		}
	}

   bool Modifies::isModifiesProc(int procIndex, int varIndex){
	 for(size_t i = 0; i < procMod.size(); i++){
		 if(procMod[i].first == procIndex && procMod[i].second == varIndex){
			 return true;
		 }else{
			 return false;
		 }
	 }
   }



   void Modifies::populateStmtBool(){
	   int cols=0;
	   int rows=0;
	   for(size_t i = 0 ; i < stmtMod.size(); i++){
		   if(stmtMod[i].first >= cols){
			   cols = stmtMod[i].first;
		   }
		 if(stmtMod[i].second >= cols){
			   rows = stmtMod[i].second;
		   }
	   }
	 
	   vector< vector< bool > > verified( (cols+1), vector<bool>( (rows+1), false ) );
	   stmtBool = verified;

	   for (size_t i = 0 ; i < stmtMod.size(); i++){
		
		    stmtBool[stmtMod[i].first][stmtMod[i].second] = true;
		
	   }
   }

   void Modifies::populateProcBool(){
	   int cols=0;
	   int rows=0;
	   for (size_t i = 0 ; i < procMod.size(); i++){
		   if(procMod[i].first >= cols){
			   cols = procMod[i].first;
		   }
		 if(procMod[i].second >= cols){
			   rows = procMod[i].second;
		   }
	   }
	   vector< vector< bool > > verified( (cols+1), vector<bool>( (rows+1), false ) );
	   procBool = verified;

	   for (size_t i = 0 ; i < procMod.size(); i++){
		    procBool[procMod[i].first][procMod[i].second] = true;
	   }
   }

   bool Modifies::evaluateIsModifiesStmt(int stmt, int varIndex){
	  // cout << "rows size" << vecBool.size() << "column size " << vecBool[0].size(); 
	   if ( (size_t)stmt > stmtBool.size() || (size_t)varIndex > stmtBool[0].size()){
		   return false;
	   }else{
	   if(stmtBool[stmt][varIndex]){
		   return true;
	   }else{
		   false;
	   }
	   }
   }

   bool Modifies::evaluateIsModifiesProc(int proc, int varIndex){
	  // cout << "rows size" << vecBool.size() << "column size " << vecBool[0].size(); 
	   if( (size_t)proc > procBool.size() || (size_t)varIndex> procBool[0].size()){
		   return false;
	   }else{
	   if(procBool[proc][varIndex]){
		   return true;
	   }else{
		   false;
	   }
	   }
   }

   void Modifies::insertToStmtVarTable(set<int> s){
	   stmtVarMod.push_back(s);
   }
	void Modifies::insertToVarStmtTable(set<int> s){
		varStmtMod.push_back(s);
	}
	void Modifies::insertToProcVarTable(set<int> s){
		procVarMod.push_back(s);
	}

	void Modifies::insertToVarProcTable(set<int> s){	 
		varProcMod.push_back(s);
	}

	void Modifies::insertToStmtVarIndexMap(pair<int,int> p){
		stmtVarIndexMap.insert(p);
	}

	void Modifies::insertToVarStmtIndexMap(pair<int,int> p){
		varStmtIndexMap.insert(p);
	}

	void Modifies::insertToProcVarIndexMap(pair<int,int> p){
		procVarIndexMap.insert(p);
	}

	void Modifies::insertToVarProcIndexMap(pair<int,int> p){
	      varProcIndexMap.insert(p);
	}

 