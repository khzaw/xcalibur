#pragma once
#include <vector>
#include <list>
#include <set>


using namespace std;

class Uses{

	private:
    vector<pair<int,int>> stmtUses; // contains entries of variables used by stmt 
	vector<set<int>> stmtVarUses; // contains vector of variables used by the stmt
    vector<set<int>> varStmtUses; // contains vector of statements that uses the variable(varIndex)
	//procedure modifies
	vector<pair<int,int>> procUses; // contains entries of variables used by procedure
	vector<set<int>> procVarUses; // contains vector of variables used by each procedure
	vector<set<int>> varProcUses; // contains vector of procedures that uses the variable(procIndex)
	
	public:
	Uses();
    //Stmt
	set<int> getUsersStmt(int); //O(1)
	set<int> getUsedVarStmt(int); //O(1)
	vector<pair<int,int>> getUsesStmt(); //O(1)
	void insertUsesStmt(int,int); //O(1)
	bool isUsesStmt(int,int); //O(1)+O(logn)
	//Procedure
	set<int> getUsersProc(int);  //O(1)
	set<int> getUsedVarProc(int); //O(1)
	vector<pair<int,int>> getUsesProc(); //O(1)
	void insertUsesProc(int,int); //O(1)
	bool isUsesProc(int,int); //O(1)+O(logn)
	int getSizeStmtUses(); //O(1)
	int getSizeProcUses(); //O(1)
};