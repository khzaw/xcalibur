#pragma once
#include <vector>
#include <set>
#include <list>
#include <map>

using namespace std;

class Modifies{

	private:
	//statement modifies
	vector<pair<int,int>> stmtMod; // contains entries of variables modified by stmt 
	vector<set<int>> stmtVarMod; // contains vector of variables modified by the stmt
    vector<set<int>> varStmtMod; // contains vector of statements that modifies the variable(varIndex)
	//procedure modifies
	vector<pair<int,int>> procMod; // contains entries of variables modified by procedure
	vector<set<int>> procVarMod; // contains vector of variables modified by each procedure
	vector<set<int>> varProcMod; // contains vector of procedures that modifies the variable(procIndex)
	
	int stmt;
	int varIndex;
	
	public:
	Modifies();
	//Stmt 
	set<int> getModifiersStmt(int); //O(1) uses VarStmtMod 
	set<int> getModifiedVarStmt(int); //O(1)
	vector<pair<int,int>> getModifiesStmt(); //O(1)
	void insertModifiesStmt(int,int); //O(1)
	bool isModifiesStmt(int,int); //O(1)+O(logn)
	//Procedure
	set<int> getModifiersProc(int); //O(1)
	set<int> getModifiedVarProc(int); //O(1)
	vector<pair<int,int>> getModifiesProc();  //O(1)
	void insertModifiesProc(int,int); //O(1)
	bool isModifiesProc(int,int); //O(1)+O(logn)
	int getSizeStmtModifies(); //O(1)
	int getSizeProcModifies(); //O(1)
};