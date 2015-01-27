#include "Modifies.h"
#include <utility>
#include <vector>
#include <set>

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

	vector<pair<int,int>> Modifies::getModifiesStmt(){
		return stmtMod;
	}
	
	//Pre condition: varIndex is positive
	set<int> Modifies::getModifiersStmt(int varIndex){
		set<int> result;
		if(varIndex>=varStmtMod.size()){
			return result;
		}
		else{
		return varStmtMod[varIndex];
		}
	}

	//Pre condition: stmt no. is positive
	set<int> Modifies::getModifiedVarStmt(int stmt){
	    set<int> result;
		if(stmt>stmtVarMod.size()){
			return result;
		}
		else{
		return stmtVarMod[stmt-1];
		}
	}

   bool Modifies::isModifiesStmt(int stmt, int varIndex){
	   set<int> varSet = stmtVarMod[stmt-1];
	   std::set<int>::iterator it = varSet.find(varIndex);
	   if( it == varSet.end()){
		   return false;
	   }else{
		   return true;
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
	
	set<int> Modifies::getModifiersProc(int varIndex){
		set<int> result;
		if(varIndex>=varProcMod.size()){
			return result;
		}
		else{
		return varProcMod[varIndex];
		}
	}

	set<int> Modifies::getModifiedVarProc(int procIndex){
		set<int> result;
		if(procIndex>=procVarMod.size()){
			return result;
		}
		else{
		return procVarMod[procIndex];
		}
	}

   bool Modifies::isModifiesProc(int procIndex, int varIndex){
	  set<int> procSet = procVarMod[procIndex];
	   std::set<int>::iterator it = procSet.find(varIndex);
	   if( it == procSet.end()){
		   return false;
	   }else{
		   return true;
	   }
   }


