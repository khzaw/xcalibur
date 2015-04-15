#include "Uses.h"
#include <iostream>

using namespace std;

	Uses::Uses(){
		
	}
	
	void Uses::insertUsesStmt(int stmt,int varIndex){
			 // cout << "stmt : " << stmt << ", varIndex " << varIndex << endl;
		if(!(isUsesStmt(stmt, varIndex))){
			stmtUses.push_back(make_pair(stmt,varIndex));
		}
   }

	vector<pair<int,int>> Uses::getUsesStmt(){
		return stmtUses;
	}
	
	 set<int> Uses::getAllUsersStmt(){
	    set<int> result;
		for(size_t i = 0; i < stmtUses.size(); i++){
			result.insert(stmtUses[i].first);
		}
		return result;
	}

	 set<int> Uses::getAllVariablesUsedByProc(int procIndex) {
		 set<int> results;
		 for(size_t i = 0; i < procUses.size(); i++) {
			 results.insert(procUses[i].second);
		 }
		 return results;
	 }

   set<int> Uses::getAllUsedVarStmt(){
	    set<int> result;
		for(size_t i = 0; i < stmtUses.size(); i++){
			result.insert(stmtUses[i].second);
		}
		return result;
	}

     set<int> Uses::getAllUsersProc(){
	    set<int> result;
		for(size_t i = 0; i < procUses.size(); i++){
			result.insert(procUses[i].first);
		}
		return result;
	}

	 set<int> Uses::getAllUsedVarProc(){
	    set<int> result;
		for (size_t i = 0; i<procUses.size(); i++){
			result.insert(procUses[i].second);
		}
		return result;
	}

	 set<int> Uses::getUsersStmt(int varIndex){
		set<int> usersSet;
		//std::set<int>::iterator it = calleeSet.begin();
		for (size_t i = 0; i < stmtUses.size(); i++){
			if (stmtUses[i].second == varIndex){
				usersSet.insert(stmtUses[i].first);
			}
		}
		return usersSet;
	}


	set<int> Uses::getUsedVarStmt(int stmt){
		set<int> usedVarSet;
		
		//std::set<int>::iterator it = calleeSet.begin();
		for(size_t i = 0; i < stmtUses.size(); i++){
			if (stmtUses[i].first == stmt){
			
				usedVarSet.insert(stmtUses[i].second);
			}
		}
		return usedVarSet;
	}

	set<int> Uses::getUsersProc(int varIndex){
		set<int> usersSet;
		//std::set<int>::iterator it = calleeSet.begin();
		for(size_t i = 0; i < procUses.size(); i++){
			if (procUses[i].second == varIndex){
				usersSet.insert(procUses[i].first);
			}
		}
		return usersSet;
	}


	set<int> Uses::getUsedVarProc(int stmt){
		set<int> usedVarSet;
		//std::set<int>::iterator it = calleeSet.begin();
		for (size_t i = 0; i < procUses.size(); i++){
			if (procUses[i].first == stmt){
				usedVarSet.insert(procUses[i].second);
			}
		}
		return usedVarSet;
	}



	int Uses::getStmtIndexSize(){
		return stmtVarIndexMap.size();
	}
	int Uses::getVarStmtIndexSize(){
		return varStmtIndexMap.size();
	}

	int Uses::getProcIndexSize(){
		return procVarIndexMap.size();
	}

	int Uses::getVarProcIndexSize(){
		return varProcIndexMap.size();
	}

	int Uses::getStmtVarIndex(int stmt){
		std::unordered_map<int, int>::iterator it = stmtVarIndexMap.find(stmt);
		if(it == stmtVarIndexMap.end()) {	
		return -1;
	} else {
		return it->second;
	}
	}

    int Uses::getVarStmtIndex(int stmt){
		std::unordered_map<int, int>::iterator it = varStmtIndexMap.find(stmt);
		if(it == varStmtIndexMap.end()) {	
		return -1;
	} else {
		return it->second;
	}
	}

	int Uses::getProcVarIndex(int proc){
		std::unordered_map<int, int>::iterator it = procVarIndexMap.find(proc);
		if(it == procVarIndexMap.end()) {	
		return -1;
	} else {
		return it->second;
	}
	}

	int Uses::getVarProcIndex(int proc){
		std::unordered_map<int, int>::iterator it = varProcIndexMap.find(proc);
		if(it == varProcIndexMap.end()) {	
		return -1;
	} else {
		return it->second;
	}
	}


	set<int> Uses::evaluateGetUsersStmt(int varIndex){
		set<int> result;
			int index = getVarStmtIndex(varIndex);
		if ((size_t)index >= varStmtUses.size()){
			return result;
		}
		else{
		return varStmtUses[index];
		}
	}

	set<int> Uses::evaluateGetUsedVarStmt(int stmt){
	    set<int> result;
		int index = Uses::getStmtVarIndex(stmt);
		if ((size_t)index > stmtVarUses.size()){
			return result;
		}
		else{
		return stmtVarUses[index];
		}
	}

   bool Uses::isUsesStmt(int stmt, int varIndex){
	 for (size_t i = 0; i < stmtUses.size(); i++){
		 if(stmtUses[i].first == stmt && stmtUses[i].second == varIndex){
			 return true;
		 }else{
			 return false;
		 }
	 }
   }

   	
   void Uses::insertUsesProc(int procIndex,int varIndex){
	   	if(!(isUsesProc(procIndex, varIndex))){
			 procUses.push_back(make_pair(procIndex,varIndex));
		}
   }

	vector<pair<int,int>> Uses::getUsesProc(){
		return procUses;
	}
	
	set<int> Uses::evaluateGetUsersProc(int varIndex){
		set<int> result;
		int index = getVarProcIndex(varIndex);
		if ((size_t)index >= varProcUses.size()){
			return result;
		}
		else{
		return varProcUses[index];
		}
	}

	set<int> Uses::evaluateGetUsedVarProc(int procIndex){
		set<int> result;
		int index = getProcVarIndex(procIndex);
		if ((size_t)index >= procVarUses.size()){
			return result;
		}
		else{
		return procVarUses[index];
		}
	}

   bool Uses::isUsesProc(int procIndex, int varIndex){
		 for (size_t i = 0; i < procUses.size(); i++){
		 if(procUses[i].first == procIndex && procUses[i].second == varIndex){
			 return true;
		 }else{
			 return false;
		 }
	 }
   }

   int Uses::getSizeProcUses() {
	   return procUses.size();
   }

   int Uses::getSizeStmtUses() {
		return stmtUses.size();
   }

   

   void Uses::populateStmtBool(){
	   int cols=0;
	   int rows=0;
	   for (size_t i = 0 ; i < stmtUses.size(); i++){
		   if(stmtUses[i].first >= cols){
			   cols = stmtUses[i].first;
		   }
		 if(stmtUses[i].second >= rows){
			   rows = stmtUses[i].second;
		   }
	   }
	 
	   vector< vector< bool > > verified( (cols+1), vector<bool>( (rows+1), false ) );
	   stmtBool = verified;

	   for (size_t i = 0 ; i < stmtUses.size(); i++){
		
		    stmtBool[stmtUses[i].first][stmtUses[i].second] = true;
		
	   }
   }

   void Uses::populateProcBool(){
	   int cols=0;
	   int rows=0;
	   for (size_t i = 0 ; i < procUses.size(); i++){
		   if(procUses[i].first >= cols){
			   cols = procUses[i].first;
		   }
		 if(procUses[i].second >= rows){
			   rows = procUses[i].second;
		   }
	   }
	   vector< vector< bool > > verified( (cols+1), vector<bool>( (rows+1), false ) );
	   procBool = verified;

	   for (size_t i = 0 ; i < procUses.size(); i++){
		    procBool[procUses[i].first][procUses[i].second] = true;
	   }
   }

   bool Uses::evaluateIsUsesStmt(int stmt, int varIndex){
	  // cout << "rows size" << vecBool.size() << "column size " << vecBool[0].size(); 
	   if( (size_t)stmt >= stmtBool.size() || (size_t)varIndex >= stmtBool[0].size()){
		   return false;
	   }else{
	   if(stmtBool[stmt][varIndex]){
		   return true;
	   }else{
		   false;
	   }
	   }
   }

   bool Uses::evaluateIsUsesProc(int proc, int varIndex){
	  // cout << "rows size" << vecBool.size() << "column size " << vecBool[0].size(); 
	   if( (size_t)proc >= procBool.size() || (size_t)varIndex >= procBool[0].size()){
		   return false;
	   }else{
	   if(procBool[proc][varIndex]){
		   return true;
	   }else{
		   false;
	   }
	   }
   }

   void Uses::insertToStmtVarTable(set<int> s){
	   stmtVarUses.push_back(s);
   }
	void Uses::insertToVarStmtTable(set<int> s){
		varStmtUses.push_back(s);
	}
	void Uses::insertToProcVarTable(set<int> s){
		procVarUses.push_back(s);
	}

	void Uses::insertToVarProcTable(set<int> s){
		varProcUses.push_back(s);
	}

	void Uses::insertToStmtVarIndexMap(pair<int,int> p){
		stmtVarIndexMap.insert(p);
	}

	void Uses::insertToVarStmtIndexMap(pair<int,int> p){
		varStmtIndexMap.insert(p);
	}

	void Uses::insertToProcVarIndexMap(pair<int,int> p){
		procVarIndexMap.insert(p);
	}

	void Uses::insertToVarProcIndexMap(pair<int,int> p){
	      varProcIndexMap.insert(p);
	}

 