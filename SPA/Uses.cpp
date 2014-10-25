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
	
	vector<int> Uses::getUsersStmt(int varIndex){
		vector<int> listUsers;
		for(int i=0; i<stmtUses.size();i++){
			if(stmtUses[i].second ==varIndex){
				listUsers.push_back(stmtUses[i].first);
			}
		}
		return listUsers;
	}

	vector<int> Uses::getUsedVarStmt(int stmt){
		vector<int> listUsedVar;
		for(int i=0; i<stmtUses.size();i++){
			if(stmtUses[i].first ==stmt){
				listUsedVar.push_back(stmtUses[i].second);
			}
		}
		return listUsedVar;
	}

   bool Uses::isUsesStmt(int stmt, int varIndex){
	   for(int i=0; i<stmtUses.size();i++){
			if((stmtUses[i].first ==stmt) && (stmtUses[i].second ==varIndex)){
				return true;
			}
		}
	   return false;
   }

   	
   void Uses::insertUsesProc(int procIndex,int varIndex){
	   	if(!(isUsesProc(procIndex, varIndex))){
			 procUses.push_back(make_pair(procIndex,varIndex));
		}
   }

	vector<pair<int,int>> Uses::getUsesProc(){
		return procUses;
	}
	
	vector<int> Uses::getUsersProc(int varIndex){
		vector<int> listUsers;
		for(int i=0; i<procUses.size();i++){
			if(procUses[i].second ==varIndex){
				listUsers.push_back(procUses[i].first);
			}
		}
		return listUsers;
	}

	vector<int> Uses::getUsedVarProc(int procIndex){
		vector<int> listUsedVar;
		for(int i=0; i<procUses.size();i++){
			if(procUses[i].first ==procIndex){
				listUsedVar.push_back(procUses[i].second);
			}
		}
		return listUsedVar;
	}

   bool Uses::isUsesProc(int procIndex, int varIndex){
	   for(int i=0; i<procUses.size();i++){
			if((procUses[i].first ==procIndex) && (procUses[i].second ==varIndex)){
				return true;
			}
		}
	   return false;
   }