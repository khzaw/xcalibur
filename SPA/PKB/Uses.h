#pragma once
#include <vector>
#include <list>
#include <set>
#include <unordered_map>

using namespace std;

class Uses{

	private:
    vector<pair<int,int>> stmtUses; // contains entries of variables used by stmt 
	vector<set<int>> stmtVarUses; // contains vector of variables used by the stmt
    vector<set<int>> varStmtUses; // contains vector of statements that uses the variable(varIndex)
	//procedure
	vector<pair<int,int>> procUses; // contains entries of variables used by procedure
	vector<set<int>> procVarUses; // contains vector of variables used by each procedure
	vector<set<int>> varProcUses; // contains vector of procedures that uses the variable(procIndex)
	
	unordered_map<int,int> stmtVarIndexMap; 
	unordered_map<int,int> varStmtIndexMap;
	unordered_map<int,int> procVarIndexMap; 
	unordered_map<int,int> varProcIndexMap;
	
	vector<vector<bool>> stmtBool;
	vector<vector<bool>> procBool;

	public:
	Uses();
	void populateStmtBool();
	void populateProcBool();
	

	//getters
	set<int> getAllUsersStmt();
	set<int> getAllUsedVarStmt();
	set<int> getAllUsersProc();
	set<int> getAllUsedVarProc();

	set<int> getUsersStmt(int);
	set<int> getUsedVarStmt(int);
	set<int> getUsersProc(int);
	set<int> getUsedVarProc(int);

	int getStmtVarIndex(int);
    int getVarStmtIndex(int);
	int getProcVarIndex(int);
	int getVarProcIndex(int);

	//setters
	void insertToStmtVarTable(set<int>);
	void insertToVarStmtTable(set<int>);
	void insertToProcVarTable(set<int>);
	void insertToVarProcTable(set<int>);
	void insertToStmtVarIndexMap(pair<int,int>);
	void insertToVarStmtIndexMap(pair<int,int>);
	void insertToProcVarIndexMap(pair<int,int>);
	void insertToVarProcIndexMap(pair<int,int>);


	//size
	int getStmtIndexSize();
	int getVarStmtIndexSize();
	int getProcIndexSize();
	int getVarProcIndexSize();

    //Stmt
	
	vector<pair<int,int>> getUsesStmt(); //O(1)
	void insertUsesStmt(int,int); //O(1)
	bool isUsesStmt(int,int); //O(1)+O(logn)
	//Procedure
	
	vector<pair<int,int>> getUsesProc(); //O(1)
	void insertUsesProc(int,int); //O(1)
	bool isUsesProc(int,int); //O(1)+O(logn)
	int getSizeStmtUses(); //O(1)
	int getSizeProcUses(); //O(1)

	//for query evaluation
	bool evaluateIsUsesStmt(int,int); // O(1)
	bool evaluateIsUsesProc(int,int); // O(1)
	set<int> evaluateGetUsersStmt(int); //O(1)
	set<int> evaluateGetUsedVarStmt(int); //O(1)
	set<int> evaluateGetUsersProc(int);  //O(1)
	set<int> evaluateGetUsedVarProc(int); //O(1)

	set<int> getAllVariablesUsedByProc(int);
};