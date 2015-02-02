#pragma once
#include <vector>
#include <set>
#include <list>
#include <map>
#include <unordered_map>

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
	
	unordered_map<int,int> stmtVarIndexMap; 
	unordered_map<int,int> varStmtIndexMap;
	unordered_map<int,int> procVarIndexMap; 
	unordered_map<int,int> varProcIndexMap;
	
	vector<vector<bool>> stmtBool;
	vector<vector<bool>> procBool;
	
	int stmt;
	int varIndex;
	
	public:
	Modifies();
	void populateStmtBool();
	void populateProcBool();
	

	//getters
	set<int> getAllModifiersStmt();
	set<int> getAllModifiedVarStmt();
	set<int> getAllModifiersProc();
	set<int> getAllModifiedVarProc();

	
	set<int> getModifiersStmt(int);
	set<int> getModifiedVarStmt(int);
	set<int> getModifiersProc(int);
	set<int> getModifiedVarProc(int);

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
	
	vector<pair<int,int>> getModifiesStmt(); //O(1)
	void insertModifiesStmt(int,int); //O(1)
	bool isModifiesStmt(int,int); //O(1)+O(logn)
	//Procedure
	
	vector<pair<int,int>> getModifiesProc();  //O(1)
	void insertModifiesProc(int,int); //O(1)
	bool isModifiesProc(int,int); //O(1)+O(logn)
	int getSizeStmtModifies(); //O(1)
	int getSizeProcModifies(); //O(1)

	//for query evaluation
	bool evaluateIsModifiesStmt(int,int);
	bool evaluateIsModifiesProc(int,int);
	set<int> evaluateGetModifiersStmt(int); //O(1)
	set<int> evaluateGetModifiedVarStmt(int); //O(1)
	set<int> evaluateGetModifiersProc(int); //O(1)
	set<int> evaluateGetModifiedVarProc(int); //O(1)
};