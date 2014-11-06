#include "Modifies.h"
#include <utility>
#include <vector>

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
	
	vector<int> Modifies::getModifiersStmt(int varIndex){
		vector<int> listModifiers;
		for(int i=0; i<stmtMod.size();i++){
			if(stmtMod[i].second ==varIndex){
				listModifiers.push_back(stmtMod[i].first);
			}
		}
		return listModifiers;
	}

	vector<int> Modifies::getModifiedVarStmt(int stmt){
		vector<int> listModifiedVar;
		for(int i=0; i<stmtMod.size();i++){
			if(stmtMod[i].first ==stmt){
				listModifiedVar.push_back(stmtMod[i].second);
			}
		}
		return listModifiedVar;
	}

   bool Modifies::isModifiesStmt(int stmt, int varIndex){
	   for(int i=0; i<stmtMod.size();i++){
			if((stmtMod[i].first ==stmt) && (stmtMod[i].second ==varIndex)){
				return true;
			}
		}
	   return false;
   }

   	
   void Modifies::insertModifiesProc(int procIndex,int varIndex){
	    if(!( isModifiesProc(procIndex,varIndex))){
	procMod.push_back(make_pair(procIndex,varIndex));
	  }  
   }

	vector<pair<int,int>> Modifies::getModifiesProc(){
		return procMod;
	}
	
	vector<int> Modifies::getModifiersProc(int procIndex){
		vector<int> listModifiers;
		for(int i=0; i<procMod.size();i++){
			if(procMod[i].second ==procIndex){
				listModifiers.push_back(procMod[i].first);
			}
		}
		return listModifiers;
	}

	vector<int> Modifies::getModifiedVarProc(int procIndex){
		vector<int> listModifiedVar;
		for(int i=0; i<procMod.size();i++){
			if(procMod[i].first ==stmt){
				listModifiedVar.push_back(procMod[i].second);
			}
		}
		return listModifiedVar;
	}

   bool Modifies::isModifiesProc(int procIndex, int varIndex){
	   for(int i=0; i<procMod.size();i++){
			if((procMod[i].first ==procIndex) && (procMod[i].second ==varIndex)){
				return true;
			}
		}
	   return false;
   }


