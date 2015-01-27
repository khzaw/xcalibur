#include "Uses.h"

using namespace std;

	Uses::Uses(){
		
	}
	
	void Uses::insertUsesStmt(int stmt,int varIndex){
		if(!(isUsesStmt(stmt, varIndex))){
			stmtUses.push_back(make_pair(stmt,varIndex));
		}
   }

	vector<pair<int,int>> Uses::getUsesStmt(){
		return stmtUses;
	}
	
	set<int> Uses::getUsersStmt(int varIndex){
		set<int> result;
		if(varIndex>=varStmtUses.size()){
			return result;
		}
		else{
		return varStmtUses[varIndex];
		}
	}

	set<int> Uses::getUsedVarStmt(int stmt){
	    set<int> result;
		if(stmt>stmtVarUses.size()){
			return result;
		}
		else{
		return stmtVarUses[stmt-1];
		}
	}

   bool Uses::isUsesStmt(int stmt, int varIndex){
	   set<int> varSet = stmtVarUses[stmt-1];
	   std::set<int>::iterator it = varSet.find(varIndex);
	   if( it == varSet.end()){
		   return false;
	   }else{
		   return true;
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
	
	set<int> Uses::getUsersProc(int varIndex){
		set<int> result;
		if(varIndex>=varProcUses.size()){
			return result;
		}
		else{
		return varProcUses[varIndex];
		}
	}

	set<int> Uses::getUsedVarProc(int procIndex){
		set<int> result;
		if(procIndex>=procVarUses.size()){
			return result;
		}
		else{
		return procVarUses[procIndex];
		}
	}

   bool Uses::isUsesProc(int procIndex, int varIndex){
	  set<int> procSet = procVarUses[procIndex];
	   std::set<int>::iterator it = procSet.find(varIndex);
	   if( it == procSet.end()){
		   return false;
	   }else{
		   return true;
	   }
   }

   int Uses::getSizeProcUses() {
	   return procUses.size();
   }

   int Uses::getSizeStmtUses() {
		return stmtUses.size();
   }